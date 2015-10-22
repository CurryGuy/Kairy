#include <Kairy/Graphics/RenderDevice.h>
#include <Kairy/Macros.h>
#include <Kairy/Graphics/ImageLoader.h>
#include <Kairy/System/InputManager.h>
#include <Kairy/Scene/SceneManager.h>
#include <Kairy/Util/Clamp.h>

#ifdef _3DS
#include "base_vsh_shbin.h"
#include "../3DS/VertexPool.h"
#else
#include <Kairy/Util/StringFormat.h>
#include <thread>
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

static std::unique_ptr<RenderDevice> s_sharedRenderDevice = nullptr;

//=============================================================================

RenderDevice* RenderDevice::getInstance()
{
	if (!s_sharedRenderDevice)
	{
		s_sharedRenderDevice.reset(new RenderDevice());
	}

	return s_sharedRenderDevice.get();
}

//=============================================================================

#ifndef _3DS
static void glfwKeyFun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager::getInstance()->setGlfwKey(key, action != GLFW_RELEASE);
}
#endif // _3DS

//=============================================================================

RenderDevice::RenderDevice(void)
    :_initialized(false)
    ,_3dEnabled(false)
    ,_waitVBlank(true)
	,_running(false)
	,_quitOnStart(false)
    ,_currentFps(0)
    ,_fpsCounter(0)
    ,_fpsTimer(0.0f)
    ,_lastTime(0.0)
    ,_currentTime(0.0)
    ,_deltaTime(0.0f)
    ,_targetScreen(Screen::Top)
    ,_targetSide(Side::Left)
    ,_defaultProgram(nullptr)
#ifdef _3DS
    ,_frameBuffer(nullptr)
    ,_depthBuffer(nullptr)
    ,_cmdBuffer(nullptr)
#else
	,_window(nullptr)
#endif // _3DS
{
}

//=============================================================================

RenderDevice::~RenderDevice()
{
}

//=============================================================================

bool RenderDevice::init(Uint32 cmd_size)
{
    if(_initialized)
    {
        return true;
    }

    _initialized = true;
    _cmdSize = cmd_size;
	
#ifdef _3DS

    _frameBuffer = (u32*)vramMemAlign(TOP_SCREEN_WIDTH * TOP_SCREEN_HEIGHT * 8, 0x100);

    if(!_frameBuffer)
    {
        destroy();
        return false;
    }

    _depthBuffer = (u32*)vramMemAlign(TOP_SCREEN_WIDTH * TOP_SCREEN_HEIGHT * 8, 0x100);

    if(!_depthBuffer)
    {
        destroy();
        return false;
    }

    _cmdBuffer = (u32*)linearAlloc(cmd_size * 4);

    if(!_cmdBuffer)
    {
        destroy();
        return false;
    }
	
    gfxInitDefault();
    GPU_Init(nullptr);
    GPU_Reset(nullptr, _cmdBuffer, 0x80000);
    gfxSet3D(false);

	GPU_SetTextureBorderColor(GPU_TEXUNIT0, 0);
	GPU_SetTextureBorderColor(GPU_TEXUNIT1, 0);
	GPU_SetTextureBorderColor(GPU_TEXUNIT2, 0);

    GPUCMD_Finalize();
    GPUCMD_FlushAndRun(nullptr);
    gspWaitForP3D();
	
	aptOpenSession();
	APT_SetAppCpuTimeLimit(nullptr, 30);
	aptCloseSession();

	osSetSpeedupEnable(true);

#else
	glfwInit();

	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	_window = glfwCreateWindow(TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT + BOTTOM_SCREEN_HEIGHT,
		"Kairy", nullptr, nullptr);

	glfwSetKeyCallback(_window, glfwKeyFun);

	glfwMakeContextCurrent(_window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		destroy();
		return false;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, TOP_SCREEN_HEIGHT, TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT);
	glScissor(0, TOP_SCREEN_HEIGHT, TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT);

#endif // _3DS

	_defaultProgram.reset(new ShaderProgram());
	
	if(!_defaultProgram)
	{
		destroy();
		return false;
	}
	
#ifdef _3DS
	if(!_defaultProgram->load(base_vsh_shbin, base_vsh_shbin_size))
	{
		destroy();
		return false;
	}
#else

	constexpr const char* vShaderData =
		"#version 330 core\n"
		"layout (location = 0) in vec3 inPosition;\n"
		"layout (location = 1) in vec4 inColor;\n"
		"layout (location = 2) in vec2 inTexCoords;\n"
		"out vec4 color;\n"
		"out vec2 texCoords;\n"
		"uniform mat4 projection = mat4(1);\n"
		"uniform mat4 modelview = mat4(1);\n"
		"void main() {\n"
		"color = inColor;\n"
		"texCoords = inTexCoords;\n"
		"gl_Position = projection * modelview * vec4(inPosition, 1.0);\n"
		"}\n";

	if (!_defaultProgram->load((byte*)vShaderData, strlen(vShaderData)))
	{
		destroy();
		return false;
	}

#endif // _3DS

    _topProjection = Transform::createOrthographic(0.0f, TOP_SCREEN_WIDTH,
            0.0f, TOP_SCREEN_HEIGHT, 0.0f, 1.0f);
    _botProjection = Transform::createOrthographic(0.0f, BOTTOM_SCREEN_WIDTH,
            0.0f, BOTTOM_SCREEN_HEIGHT, 0.0f, 1.0f);
	_defaultModelview = Transform::createTranslation(0, 0, 0);

	_lastTime = getTicks();

	// Create the scene manager
	SceneManager::getInstance();
	
	_running = true;

    return true;
}

//=============================================================================

void RenderDevice::clear(const Color& color)
{
    if(!_initialized)
        return;

#ifdef _3DS
    GX_SetMemoryFill(nullptr,
            _frameBuffer, color.toUint32(), &_frameBuffer[TOP_SCREEN_WIDTH * TOP_SCREEN_HEIGHT], 0x201,
            _depthBuffer,       0x00000000, &_depthBuffer[TOP_SCREEN_WIDTH * TOP_SCREEN_HEIGHT], 0x201);
    gspWaitForPSC0();
#else
	Vec4 cv = color.toVector();
	glClearColor(cv.x, cv.y, cv.z, cv.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif // _3DS
}

//=============================================================================

void RenderDevice::swapBuffers()
{
    if(!_initialized)
        return;

#ifdef _3DS
    gfxSwapBuffers();

    if(_waitVBlank)
    {
        gspWaitForEvent(GSPEVENT_VBlank0, false);
    }
#else
	glfwSwapBuffers(_window);
	glfwPollEvents();
#endif // _3DS

    _currentTime = getTicks();
	_deltaTime = float(_currentTime - _lastTime);
	_lastTime = _currentTime;

	InputManager::getInstance()->update(_deltaTime);
	
	if(_quitOnStart)
	{
		if(InputManager::getInstance()->isKeyDown(Keys::Start))
		{
			quit();
		}
	}

    _fpsTimer += _deltaTime;
    _fpsCounter++;

    if(_fpsTimer >= 1.0f)
    {
        _currentFps = _fpsCounter;
        _fpsCounter = 0;
        _fpsTimer = 0.0f;

#ifndef _3DS
		glfwSetWindowTitle(_window,
			util::string_format("Kairy - %i FPS", _currentFps).c_str());
#endif // _3DS
    }

#ifndef _3DS
	double xpos = 0.0;
	double ypos = 0.0;
	constexpr double margin = (TOP_SCREEN_WIDTH - BOTTOM_SCREEN_WIDTH) / 2;

	glfwGetCursorPos(_window, &xpos, &ypos);
	bool pressed = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	if (!InputManager::getInstance()->isTouchDown() &&
		(xpos < margin || xpos >= TOP_SCREEN_WIDTH - margin ||
			ypos < TOP_SCREEN_HEIGHT))
	{
		pressed = false;
	}

	ypos -= TOP_SCREEN_HEIGHT;
	xpos -= margin;

	xpos = util::clamp(xpos, 0.0, (double)BOTTOM_SCREEN_WIDTH - 1.0);
	ypos = util::clamp(ypos, 0.0, (double)BOTTOM_SCREEN_HEIGHT - 1.0);

	InputManager::getInstance()->updateTouch(
		pressed, Vec2((float)xpos, (float)ypos),
		_deltaTime);

	// Limit to 60 FPS
	constexpr const double TARGET_TIME = 1.0 / 60.0;
	double wait = TARGET_TIME - _deltaTime;
	
	if (wait > 0.0)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(Uint64(wait * 1000000.0)));
		_lastTime -= wait;
	}
#endif // _3DS
}

//=============================================================================

void RenderDevice::startFrame(void)
{
    if(_initialized)
    {
        startFrame(*_defaultProgram);
    }
}

//=============================================================================

void RenderDevice::startFrame(ShaderProgram& program)
{
#ifdef _3DS
    VertexPool::getInstance()->clear();
#endif // _3DS

    if(!_initialized)
        return;
	
#ifdef _3DS
    GPUCMD_SetBufferOffset(0);

    GPU_SetViewport(
            (u32*)osConvertVirtToPhys((u32)_depthBuffer),
            (u32*)osConvertVirtToPhys((u32)_frameBuffer),
            0, 0, getScreenHeight(), getScreenWidth());

    GPU_DepthMap(-1.0f, 0.0f);
    GPU_SetFaceCulling(GPU_CULL_NONE);
    GPU_SetStencilTest(false, GPU_ALWAYS, 0x00, 0xFF, 0x00);
    GPU_SetStencilOp(GPU_STENCIL_KEEP, GPU_STENCIL_KEEP, GPU_STENCIL_KEEP);
    GPU_SetBlendingColor(0, 0, 0, 0);
    GPU_SetDepthTestAndWriteMask(true, GPU_GEQUAL, GPU_WRITE_ALL);
    u32 tmp[] = { 0 };

    GPUCMD_Add(GPUCMD_HEADER(0, 0x1, GPUREG_0062), tmp, 1);
    GPUCMD_Add(GPUCMD_HEADER(0, 0xF, GPUREG_0118), tmp, 1);

    GPU_SetAlphaBlending(GPU_BLEND_ADD,
            GPU_BLEND_ADD,
            GPU_SRC_ALPHA, GPU_ONE_MINUS_SRC_ALPHA,
            GPU_ONE, GPU_ZERO);
    GPU_SetAlphaTest(true, GPU_ALWAYS, 0x00);

    for(int i = 0; i < 6; ++i)
    {
        setDummyTexEnv(i);
    }
#endif // _3DS

    program.use();

    if(_targetScreen == Screen::Top)
    {
        ShaderProgram::setUniform(UNIFORM_PROJECTION_NAME, _topProjection);
    }
    else
    {
        ShaderProgram::setUniform(UNIFORM_PROJECTION_NAME, _botProjection);
    }

    ShaderProgram::setUniform(UNIFORM_MODELVIEW_NAME, _defaultModelview);
}

//=============================================================================

void RenderDevice::endFrame()
{
    if(!_initialized)
        return;

#ifdef _3DS
    GPU_FinishDrawing();
    GPUCMD_Finalize();
    GPUCMD_FlushAndRun(nullptr);
    gspWaitForP3D();

    int width = getScreenWidth();
    int height = getScreenHeight();
    gfxScreen_t screen = (gfxScreen_t)_targetScreen;
    gfx3dSide_t side = (gfx3dSide_t)_targetSide;

    if(_targetScreen == Screen::Bottom)
    {
        side = GFX_LEFT;
    }

    GX_SetDisplayTransfer(nullptr, _frameBuffer,
            GX_BUFFER_DIM(height, width),
            (u32*)gfxGetFramebuffer(screen, side, nullptr, nullptr),
            GX_BUFFER_DIM(height, width), 0x1000);
    gspWaitForPPF();
#endif // _3DS
}

//=============================================================================

void RenderDevice::setTargetScreen(Screen screen)
{
    _targetScreen = screen;
#ifndef _3DS
	int width = getScreenWidth();
	int height = getScreenHeight();
	int y = _targetScreen == Screen::Top ? height : 0;
	int x = _targetScreen == Screen::Top ? 0 :
		(TOP_SCREEN_WIDTH - BOTTOM_SCREEN_WIDTH) / 2;

	glViewport(x, y, width, height);
	glScissor(x, y, width, height);
#endif // _3DS
}

//=============================================================================

bool RenderDevice::isRunning() const
{
#ifdef _3DS
	return _running && aptMainLoop();
#else
	return _running && !glfwWindowShouldClose(_window);
#endif // _3DS
}

//=============================================================================

void RenderDevice::quit()
{
	_running = false;
}

//=============================================================================

void RenderDevice::setQuitOnStart(bool quitOnStart)
{
	_quitOnStart = quitOnStart;
}

//=============================================================================

void RenderDevice::setTargetSide(Side side)
{
    _targetSide = side;
}

//=============================================================================

int RenderDevice::getScreenWidth() const
{
    return GetScreenWidth(_targetScreen);
}

//=============================================================================

int RenderDevice::getScreenHeight() const
{
    return GetScreenHeight(_targetScreen);
}

//=============================================================================

Vec2 RenderDevice::getScreenSize() const
{
	return Vec2((float)getScreenWidth(), (float)getScreenHeight());
}

//=============================================================================

ShaderProgram * RenderDevice::getDefaultShaderProgram()
{
	return _defaultProgram.get();
}

//=============================================================================

#ifdef _3DS
void RenderDevice::setDummyTexEnv(u8 id)
{
    GPU_SetTexEnv(id,
            GPU_TEVSOURCES(GPU_PREVIOUS, 0, 0),
            GPU_TEVSOURCES(GPU_PREVIOUS, 0, 0),
            GPU_TEVOPERANDS(0, 0, 0),
            GPU_TEVOPERANDS(0, 0, 0),
            GPU_REPLACE,
            GPU_REPLACE,
            0xFFFFFFFF);
}
#endif // _3DS

//=============================================================================

void RenderDevice::set3dEnabled(bool enable)
{
    if(_initialized)
    {
#ifdef _3DS
        gfxSet3D(enable);
#endif // _3DS
        _3dEnabled = enable;
    }
}

//=============================================================================

void RenderDevice::enable3d(void)
{
    if(_initialized)
    {
		_3dEnabled = true;
#ifdef _3DS
        gfxSet3D(true);
#endif // _3DS
    }
}

//=============================================================================

void RenderDevice::disable3d(void)
{
    if(_initialized)
    {
		_3dEnabled = false;
#ifdef _3DS
        gfxSet3D(false);
#endif // _3DS
    }
}

//=============================================================================

bool RenderDevice::is3dEnabled() const
{
    return _3dEnabled;
}

//=============================================================================

void RenderDevice::setWaitVBlank(bool wait)
{
    _waitVBlank = wait;
#ifndef _3DS
	glfwSwapInterval(wait ? 1 : 0);
#endif // _3DS
}

//=============================================================================

int RenderDevice::getCurrentFps() const
{
    return _currentFps;
}

//=============================================================================

float RenderDevice::getDeltaTime() const
{
    return _deltaTime;
}

//=============================================================================

double RenderDevice::getTicks() const
{
#ifdef _3DS
	return svcGetSystemTick() / 268123480.0;
#else
	return glfwGetTime();
#endif // _3DS
}

//=============================================================================

bool RenderDevice::getPixels(std::vector<Color>& outPixels,
        Screen screen,
        Side side)
{
#ifdef _3DS
    u16 width, height;
    u8* buffer = gfxGetFramebuffer((gfxScreen_t)screen, (gfx3dSide_t)side, &width, &height);

    if(!buffer || !width || !height)
    {
        return false;
    }

    u32 pixelsCount = width * height;

    outPixels.resize(pixelsCount);

    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            u32 src_index = x + y * width;
            u32 dst_index = y + (width - 1 - x) * height;

            outPixels[dst_index].r = buffer[src_index * 3 + 2];
            outPixels[dst_index].g = buffer[src_index * 3 + 1];
            outPixels[dst_index].b = buffer[src_index * 3 + 0];
            outPixels[dst_index ].a = Color::OPAQUE;
        }
    }
#else
	int width = GetScreenWidth(screen);
	int height = GetScreenHeight(screen);
	int y = screen == Screen::Top ? height : 0;
	int x = screen == Screen::Top ? 0 :
		(TOP_SCREEN_WIDTH - BOTTOM_SCREEN_WIDTH) / 2;

	outPixels.resize(width * height);
	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &outPixels.front());
#endif // _3DS

    return true;
}

//=============================================================================

bool RenderDevice::takeScreenshot(const std::string& filename,
        ImageFormat format,
        Screen screen, Side side)
{
    std::vector<Color> pixels;
    if(!getPixels(pixels, screen, side))
    {
        return false;
    }

    int width = GetScreenWidth(screen);
    int height = GetScreenHeight(screen);

    return ImageLoader::SaveToFile(filename, format,
            (byte*)&pixels.front(),
            width, height,
            ImageLoader::PixelFormat::RGBA8);
}

//=============================================================================

void RenderDevice::destroy(void)
{
    if(_initialized)
    {
#ifdef _3DS
		gfxExit();
        vramFree(_frameBuffer);
        vramFree(_depthBuffer);
        linearFree(_cmdBuffer);
		osSetSpeedupEnable(false);
#else
		glfwDestroyWindow(_window);
		glfwTerminate();
#endif // _3DS

        _initialized = false;
    }
}

//=============================================================================

NS_KAIRY_END

/******************************************************************************
 *
 * Copyright (C) 2015 Nanni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *****************************************************************************/

#ifndef KAIRY_GRAPHICS_RENDER_DEVICE_H_INCLUDED
#define KAIRY_GRAPHICS_RENDER_DEVICE_H_INCLUDED

#include "Color.h"
#include "ShaderProgram.h"
#include <Kairy/Math/Transform.h>

NS_KAIRY_BEGIN

class RenderDevice
{
public:
    enum
    {
        CMD_SIZE_DEFAULT = 0x80000
    };

	/**
	 * @brief Get the RenderDevice singleton instance.
	 */
	static RenderDevice* getInstance();

	/**
	 * @brief Destructor.
	 */
	virtual ~RenderDevice();

    /**
     * @brief Initialize the render device.
     * @param cmd_size The gpu command buffer size.
     * @return false if an error occurred.
     */
    bool init(Uint32 cmd_size = CMD_SIZE_DEFAULT);

    /**
     * @brief Destroy the render device releasing all the resources.
     * Call it before exiting the application.
     */
    void destroy(void);

    /**
     * @brief Clear the framebuffer with the specified color.
     * @param color The color to clear the framebuffer with.
     */
    void clear(const Color& color = Color::Black);

    /**
     * @brief Swap the buffers.
     */
    void swapBuffers();

    /**
     * @brief Start drawing a frame.
     */
    void startFrame();

    /**
     * @brief Start drawing a frame with a custom
     * shader.
     */
    void startFrame(ShaderProgram& program);

    /**
     * @brief End the drawing of a frame.
     */
    void endFrame();

    /**
     * @brief Set the screen where to draw to.
     * @param screen The target screen (Top or Bottom).
     */
    void setTargetScreen(Screen screen);

    /**
     * @brief Check if the application is running.
     * @return true if the application is running.
     */
    bool isRunning() const;
	
	/**
	 * @brief Force the device to stop running.
	 */
	void quit();

	/**
	 * @brief Set if the device should stop running
	 * if the start button is pressed.
	 */
	void setQuitOnStart(bool quitOnStart);
	
    /**
     * @brief Set the side where to draw to.
     * Used for 3D on the top screen.
     * @param side The target side.
     */
    void setTargetSide(Side side);

    /**
     * @brief Get the width of the target screen.
     */
    int getScreenWidth() const;

    /**
     * @brief Get the height of the target screen.
     */
    int getScreenHeight() const;

	Vec2 getScreenSize() const;

	inline Screen getTargetScreen() const { return _targetScreen; }

	inline Side getTargetSide() const { return _targetSide; }

	/**
	 * @brief Get the default shader program.
	 */
	ShaderProgram* getDefaultShaderProgram();

    /**
     * @brief Set if the 3d should be enabled.
     * @param enable Set it to true if you want to enable 3d.
     */
    void set3dEnabled(bool enable);

    /**
     * @brief Enable or disable the VBlank waiting.
     * @param wait true if you want to enable the VBlank waiting.
     */
    void setWaitVBlank(bool wait);

    /**
     * @brief Enable the 3d.
     */
    void enable3d(void);

    /**
     * @brief Disable the 3d.
     */
    void disable3d(void);

    /**
     * @brief Check if the 3d is enabled.
     * @return true if the 3d is enabled.
     */
    bool is3dEnabled() const;

    /**
     * @brief Get the current fps.
     * @return The current fps.
     */
    int getCurrentFps() const;

    /**
     * @brief Get the time passed since the last time in seconds.
     * @return The delta time.
     */
    float getDeltaTime() const;
	
	/**
	 * @brief Get the current ticks in seconds.
	 */
	double getTicks() const;

    /**
     * @brief Check if the RenderDevice is initialized and can be used.
     * @return true if the device is initialized.
     */
	inline bool isInitialized() const { return _initialized; }

    /**
     * @brief Get the pixels of a specified screen and side.
     * @param outPixels The output pixels vector.
     * @param screen The target screen.
     * @param side The target side.
     * @return false if an error occurred.
     */
    bool getPixels(std::vector<Color>& outPixels, Screen screen,
            Side side = Side::Left);

    /**
     * @brief Take a screenshot of a specified screen and save it to
     * a file.
     * @param filename The file where to save the screenshot.
     * @param format The image format of the screenshot file.
     * @param screen The target screen.
     * @param side The target side.
     * @return true if an error occurred.
     */
    bool takeScreenshot(const std::string& filename, ImageFormat format,
            Screen screen, Side side = Side::Left);

private:
	friend class RenderTexture;

	RenderDevice(void);

#ifdef _3DS
    void setDummyTexEnv(Uint8 id);
#endif // _3DS

    bool _initialized;              ///< Whether the device is initialized or not
    bool _3dEnabled;                ///< Whether the 3d is initialized or not
    bool _waitVBlank;               ///< Whether the VBlank waiting is enabled or not
    bool _running;                  ///< Whether the device is running or not
	bool _quitOnStart;              ///< If the device should stop running at the pression of the start button
	int _currentFps;                ///< The current fps
    int _fpsCounter;                ///< The fps counter increased each frame
    float _fpsTimer;                ///< Timer for updating the current fps
    double _lastTime;               ///< The last frame os time
    double _currentTime;            ///< The current frame os time
    Uint32 _cmdSize;                ///< The gpu command buffer size
    float _deltaTime;               ///< The time passed since the last frame
    Screen _targetScreen;           ///< The target screen
    Side _targetSide;               ///< The target side
    Transform _topProjection;       ///< The top screen projection matrix
    Transform _botProjection;       ///< The bottom screen projection matrix
    Transform _defaultModelview;    ///< The default modelview matrix
	std::unique_ptr<ShaderProgram> _defaultProgram; ///< The default shader program
#ifdef _3DS
    u32* _frameBuffer;              ///< The gpu framebuffer
    u32* _depthBuffer;              ///< The gpu depth buffer
    u32* _cmdBuffer;                ///< The gpu command buffer
#else
	friend class InputManager;
	GLFWwindow* _window;
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_RENDER_DEVICE_H_INCLUDED

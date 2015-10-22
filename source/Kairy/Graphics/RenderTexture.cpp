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

#include <Kairy/Graphics/RenderTexture.h>
#include <Kairy/Graphics/RenderDevice.h>

#ifdef _3DS
#include "../3DS/VertexPool.h"
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

RenderTexture::RenderTexture(void)
	: Texture()
{
	_device = RenderDevice::getInstance();

#ifndef _3DS
	glGenFramebuffers(1, &_fbo);
#endif // _3DS
}

//=============================================================================

RenderTexture::~RenderTexture()
{
#ifndef _3DS
	glDeleteFramebuffers(1, &_fbo);
#endif // _3DS
}

//=============================================================================

void RenderTexture::startFrame()
{
	if (!_device->isInitialized())
	{
		return;
	}

#ifdef _3DS
	GPUCMD_SetBufferOffset(0);

	GPU_SetViewport(
		(u32*)osConvertVirtToPhys((u32)_device->_depthBuffer),
		(u32*)osConvertVirtToPhys((u32)_device->_frameBuffer),
		0, 0, _height, _width);

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

	for (int i = 0; i < 6; ++i)
	{
		_device->setDummyTexEnv(i);
	}
#else
	glDisable(GL_SCISSOR_TEST);
	glViewport(0, 0, _width, _height);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFbo);
	glGetFloatv(GL_COLOR_CLEAR_VALUE, _oldClearColor);
	glGetIntegerv(GL_VIEWPORT, _oldViewport);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _id, 0);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif // _3DS

	_device->getDefaultShaderProgram()->use();

	auto projection = Transform::createOrthographic(0, (float)_width, (float)_height, 0, 0.0f, 1.0f);

	ShaderProgram::setUniform(UNIFORM_PROJECTION_NAME, projection);
	ShaderProgram::setUniform(UNIFORM_MODELVIEW_NAME, Transform::createTranslation(0, 0, 0));
}

//=============================================================================

void RenderTexture::endFrame()
{
	if (!_device->isInitialized())
	{
		return;
	}

#ifdef _3DS
	GPU_FinishDrawing();
	GPUCMD_Finalize();
	GPUCMD_FlushAndRun(nullptr);
	gspWaitForP3D();

	byte* rawPixels = (byte*)linearAlloc(_potWidth * _potHeight * 3);

	GX_SetDisplayTransfer(nullptr, _device->_frameBuffer,
		GX_BUFFER_DIM(_potHeight, _potWidth),
		(u32*)_pixels,
		GX_BUFFER_DIM(_potHeight, _potWidth), 0x100);

	gspWaitForPPF();

	gfxSwapBuffers();

	gspWaitForEvent(GSPEVENT_VBlank0, false);
	
	Uint32 src_index;
	Color pixel;

	for (int x = 0; x < _width; ++x)
	{
		for (int y = 0; y < _height; ++y)
		{
			src_index = y + x * _height;

			pixel.r = rawPixels[src_index * 3 + 0];
			pixel.g = rawPixels[src_index * 3 + 2];
			pixel.b = rawPixels[src_index * 3 + 1];
			pixel.a = 255;

			setPixel(x, y, pixel);
		}
	}

	linearFree(rawPixels);
#else
	GLint oldTexture = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &oldTexture);
	glBindTexture(GL_TEXTURE_2D, _id);

	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);
	
	glEnable(GL_SCISSOR_TEST);
	glViewport(_oldViewport[0], _oldViewport[1], _oldViewport[2], _oldViewport[3]);
	glBindTexture(GL_TEXTURE_2D, oldTexture);
	glBindFramebuffer(GL_FRAMEBUFFER, _oldFbo);
	glClearColor(_oldClearColor[0], _oldClearColor[1], _oldClearColor[2], _oldClearColor[3]);
#endif // _3DS
}

//=============================================================================

NS_KAIRY_END

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
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,-
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*****************************************************************************/

#include <Kairy/Graphics/RectangleShape.h>
#include <Kairy/Graphics/ShaderProgram.h>
#include <Kairy/Graphics/RenderDevice.h>

#ifdef _3DS
#include "../3DS/VertexPool.h"
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

std::shared_ptr<RectangleShape> RectangleShape::create(void)
{
	return std::make_shared<RectangleShape>();
}

//=============================================================================

inline std::shared_ptr<RectangleShape> RectangleShape::create(const Rect & rect)
{
	return std::make_shared<RectangleShape>(rect);
}

//=============================================================================

inline std::shared_ptr<RectangleShape> RectangleShape::create(const Vec2 & size)
{
	return std::make_shared<RectangleShape>(size);
}

//=============================================================================

inline std::shared_ptr<RectangleShape> RectangleShape::create(float x, float y, float width, float height)
{
	return std::make_shared<RectangleShape>(x, y, width, height);
}

//=============================================================================

RectangleShape::RectangleShape(void)
	: OutlinedShape()
{
	setOutlineColor(Color::Transparent);

#ifndef _3DS
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36, nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)(sizeof(float) * 7));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

#endif // _3DS
}

//=============================================================================

RectangleShape::~RectangleShape()
{
}

//=============================================================================

void RectangleShape::draw()
{
	if (!_device->isInitialized() || !_visible)
		return;

	updateTransform();
	
	if (_color.a > 0)
	{
		ShaderProgram::setUniform(UNIFORM_MODELVIEW_NAME, getCombinedTransform());

#ifdef _3DS

		auto vertices = VertexPool::getInstance()->
			pushVertices<VertexPositionTexture>(4);

		vertices[0].position = Vec2(0, 0);
		vertices[1].position = Vec2(_size.x, 0);
		vertices[2].position = Vec2(0, _size.y);
		vertices[3].position = Vec2(_size.x, _size.y);

		vertices[0].texcoord = Vec2::Zero;
		vertices[1].texcoord = Vec2::Zero;
		vertices[2].texcoord = Vec2::Zero;
		vertices[3].texcoord = Vec2::Zero;

		//=========================================================================

		GPU_SetTexEnv(0,
			GPU_TEVSOURCES(GPU_CONSTANT, GPU_CONSTANT, GPU_CONSTANT),
			GPU_TEVSOURCES(GPU_CONSTANT, GPU_CONSTANT, GPU_CONSTANT),
			GPU_TEVOPERANDS(0, 0, 0),
			GPU_TEVOPERANDS(0, 0, 0),
			GPU_REPLACE, GPU_REPLACE,
			_color.r | _color.g << 8 | _color.b << 16 | _color.a << 24);

		u32 bufferOffsets[] = { 0x00 };
		u64 bufferPermutations[] = { 0x10 };
		u8 bufferNumAttributes[] = { 2 };

		GPU_SetAttributeBuffers(
			2,
			(u32*)osConvertVirtToPhys((u32)vertices),
			GPU_ATTRIBFMT(0, 2, GPU_FLOAT) |
			GPU_ATTRIBFMT(1, 2, GPU_FLOAT),
			0xFFFC,
			0x10,
			1,
			bufferOffsets,
			bufferPermutations,
			bufferNumAttributes);

		GPU_DrawArray(GPU_TRIANGLE_STRIP, 0, 4);

#else
		Vec4 c = _color.toVector();

		float vertices[] =
		{
			0, 0, -0.5f, c.x, c.y, c.z, c.w, 0, 0,
			_size.x, 0, -0.5f, c.x, c.y, c.z, c.w, 0, 0,
			0, _size.y, -0.5f, c.x, c.y, c.z, c.w, 0, 0,
			_size.x, _size.y, -0.5f, c.x, c.y, c.z, c.w, 0, 0
		};

		glUniform1i(ShaderProgram::getCurrentProgram()->
			getUniformLocation("textureEnabled"), false);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 36, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
#endif // _3DS
	}

	if (getOutlineColor().a > 0)
	{
		_outline.setTransform(getCombinedTransform());

		_outline.setLine(0, 0, _size.x, 0);
		_outline.draw();
		_outline.setLine(_size.x, 0, _size.x, _size.y);
		_outline.draw();
		_outline.setLine(0, _size.y, _size.x, _size.y);
		_outline.draw();
		_outline.setLine(0, 0, 0, _size.y);
		_outline.draw();
	}

	Node::draw();
}

//=============================================================================

NS_KAIRY_END

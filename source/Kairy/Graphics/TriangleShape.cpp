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

#include <Kairy/Graphics/TriangleShape.h>
#include <Kairy/Graphics/ShaderProgram.h>
#include <Kairy/Graphics/RenderDevice.h>

#ifdef _3DS
#include "../3DS/VertexPool.h"
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

TriangleShape::TriangleShape(void)
	: OutlinedShape()
{
	setOutlineColor(Color::Transparent);

#ifndef _3DS
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 27, nullptr, GL_DYNAMIC_DRAW);
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

std::shared_ptr<TriangleShape> TriangleShape::create(void)
{
	return std::make_shared<TriangleShape>();
}

//=============================================================================

std::shared_ptr<TriangleShape> TriangleShape::create(const Vec2 & v1, const Vec2 & v2, const Vec2 & v3)
{
	return std::make_shared<TriangleShape>(v1, v2, v3);
}

//=============================================================================

kairy::TriangleShape::TriangleShape(const Vec2& v1, const Vec2& v2, const Vec2& v3)
	: TriangleShape()
{
	setVertices(v1, v2, v3);
}

//=============================================================================

TriangleShape::~TriangleShape()
{
}

//=============================================================================

void TriangleShape::setVertices(const Vec2 & v1, const Vec2 & v2, const Vec2 & v3)
{
	_vertices[0] = v1;
	_vertices[1] = v2;
	_vertices[2] = v3;

	float minX = std::min({ v1.x, v2.x, v3.x });
	float minY = std::min({ v1.y, v2.y, v3.y });
	float maxX = std::max({ v1.x, v2.x, v3.x });
	float maxY = std::max({ v1.y, v2.y, v3.y });

	setSize(Vec2(maxX - minX, maxY - minY));
}

//=============================================================================

void TriangleShape::draw()
{
	if (!_device->isInitialized() || !_visible)
		return;
	
	if (_color.a > 0)
	{
		ShaderProgram::setUniform(UNIFORM_MODELVIEW_NAME, getCombinedTransform());

#ifdef _3DS

		auto vertices = VertexPool::getInstance()->
			pushVertices<VertexPositionTexture>(3);

		vertices[0].position = _vertices[0];
		vertices[1].position = _vertices[1];
		vertices[2].position = _vertices[2];

		vertices[0].texcoord = Vec2::Zero;
		vertices[1].texcoord = Vec2::Zero;
		vertices[2].texcoord = Vec2::Zero;

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

		GPU_DrawArray(GPU_TRIANGLE_STRIP, 0, 3);

#else
		Vec4 c = _color.toVector();

		float vertices[] =
		{
			_vertices[0].x, _vertices[0].y, -0.5f, c.x, c.y, c.z, c.w, 0, 0,
			_vertices[1].x, _vertices[1].y, -0.5f, c.x, c.y, c.z, c.w, 0, 0,
			_vertices[2].x, _vertices[2].y, -0.5f, c.x, c.y, c.z, c.w, 0, 0
		};

		glUniform1i(ShaderProgram::getCurrentProgram()->
			getUniformLocation("textureEnabled"), false);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 27, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
		glBindVertexArray(0);
#endif // _3DS
	}

	if (getOutlineColor().a > 0)
	{
		_outline.setTransform(getCombinedTransform());

		_outline.setLine(_vertices[0], _vertices[1]);
		_outline.draw();
		_outline.setLine(_vertices[1], _vertices[2]);
		_outline.draw();
		_outline.setLine(_vertices[2], _vertices[0]);
		_outline.draw();
	}

	Node::draw();
}

//=============================================================================

NS_KAIRY_END

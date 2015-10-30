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

#include <Kairy/Graphics/LineShape.h>
#include <Kairy/Graphics/ShaderProgram.h>
#include <Kairy/Graphics/RenderDevice.h>

#ifdef _3DS
#include "../3DS/VertexPool.h"
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

inline std::shared_ptr<LineShape> LineShape::create(void)
{
	return std::make_shared<LineShape>();
}

//=============================================================================

inline std::shared_ptr<LineShape> LineShape::create(float x0, float y0, float x1, float y1, float thickness)
{
	return std::make_shared<LineShape>(x0, y0, x1, y1, thickness);
}

//=============================================================================

inline std::shared_ptr<LineShape> LineShape::create(const Vec2 & start, const Vec2 & end, float thickness)
{
	return std::make_shared<LineShape>(start, end, thickness);
}

//=============================================================================

LineShape::LineShape(void) :
	Shape()
{
	_thickness = 1.0f;

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

LineShape::~LineShape()
{
}

//=============================================================================

inline void LineShape::updateTransform()
{
	if (_transformUpdated)
	{
		auto centerInPixels = _center * (_start + _end);

		auto&& translation = Transform::createTranslation(_position);
		auto&& scale = Transform::createScale(_scaleX, _scaleY);

		if (_flipX)
			scale.setValue(0, 0, scale.getValue(0, 0) * -1.0f);

		if (_flipY)
			scale.setValue(1, 1, scale.getValue(1, 1) * -1.0f);

		auto&& rotation = Transform::createRotation(util::deg_to_rad(_angle));

		auto&& rotScale =
			Transform::createTranslation(centerInPixels) *
			scale *
			rotation *
			Transform::createTranslation(-centerInPixels);

		auto&& skew = Transform::createSkewX(util::deg_to_rad(_skewX)) *
			Transform::createSkewY(util::deg_to_rad(_skewY));

		_transform = translation * rotScale * skew;

		_transformUpdated = false;
	}
}

//=============================================================================

void LineShape::draw()
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

		vertices[0].position = Vec2(_start.x + _thickness, _start.y + _thickness);
		vertices[1].position = Vec2(_start.x - _thickness, _start.y - _thickness);
		vertices[2].position = Vec2(_end.x + _thickness, _end.y + _thickness);
		vertices[3].position = Vec2(_end.x - _thickness, _end.y - _thickness);

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
			_start.x, _start.y, -0.5f, c.x, c.y, c.z, c.w, 0, 0,
			_end.x, _end.y, -0.5f, c.x, c.y, c.z, c.w, 0, 0
		};

		glUniform1i(ShaderProgram::getCurrentProgram()->
			getUniformLocation("textureEnabled"), false);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 18, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		float prevThickness = 0.0f;

		glGetFloatv(GL_LINE_WIDTH, &prevThickness);
		glLineWidth(_thickness);

		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);

		glLineWidth(prevThickness);

#endif // _3DS
	}

	Node::draw();
}

//=============================================================================

NS_KAIRY_END

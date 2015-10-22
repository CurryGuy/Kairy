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

#include <Kairy/Graphics/CircleShape.h>
#include <Kairy/Graphics/ShaderProgram.h>
#include <Kairy/Graphics/RenderDevice.h>

#ifdef _3DS
#include "../3DS/VertexPool.h"
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

CircleShape::CircleShape()
	: Shape()
{
	_segments = 60;
	setRadius(1.0f);

#ifndef _3DS
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9 * MAX_SEGMENTS, nullptr, GL_DYNAMIC_DRAW);
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

CircleShape::~CircleShape()
{
}

//=============================================================================

void CircleShape::draw()
{
	if (!_device->isInitialized() || !_visible)
		return;

	updateTransform();

	if (_color.a > 0)
	{
		ShaderProgram::setUniform(UNIFORM_MODELVIEW_NAME, getCombinedTransform());

#ifdef _3DS

		auto vertices = VertexPool::getInstance()->
			pushVertices<VertexPositionTexture>(_segments + 2);

		float deltaAngle = (2.0f * (float)M_PI) / (float)_segments;

		vertices[0].position = Vec2(0, 0);
		vertices[0].texcoord = Vec2::Zero;

		for (int i = 1; i <= _segments; ++i)
		{
			float theta = deltaAngle * (i - 1);

			float x = _radius * std::cos(theta);
			float y = _radius * std::sin(theta);

			vertices[i].position = Vec2(x, y);
			vertices[i].texcoord = Vec2::Zero;
		}

		vertices[_segments + 1] = vertices[1];

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

		GPU_DrawArray(GPU_TRIANGLE_FAN, 0, _segments + 2);

#else
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
			Vec2 texcoord;
		};

		std::vector<Vertex> vertices(_segments + 2);

		Vec4 c = _color.toVector();

		float deltaAngle = (2.0f * (float)M_PI) / (float)_segments;

		vertices[0].position = Vec3(0, 0, -0.5f);
		vertices[0].color = c;
		vertices[0].texcoord = Vec2::Zero;

		for (int i = 1; i <= _segments; ++i)
		{
			float theta = deltaAngle * (i - 1);

			float x = _radius * std::cos(theta);
			float y = _radius * std::sin(theta);

			vertices[i].position = Vec3(x, y, -0.5f);
			vertices[i].color = c;
			vertices[i].texcoord = Vec2::Zero;
		}

		vertices[_segments + 1] = vertices[1];

		glUniform1i(ShaderProgram::getCurrentProgram()->
			getUniformLocation("textureEnabled"), false);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex),
			vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
		glBindVertexArray(0);
#endif // _3DS
	}

	Node::draw();
}

//=============================================================================

void CircleShape::updateTransform()
{
	if (_transformUpdated)
	{
		auto centerInPixels = _center * getSize()
			- Vec2(_radius, _radius);

		auto translation = Transform::createTranslation(_position);
		auto scale = Transform::createScale(_scaleX, _scaleY);
		auto rotation = Transform::createTranslation(centerInPixels) *
			Transform::createRotation(util::deg_to_rad(_angle)) *
			Transform::createTranslation(-centerInPixels);
		auto skew = Transform::createSkewX(util::deg_to_rad(_skewX)) *
			Transform::createSkewY(util::deg_to_rad(_skewY));

		_transform = translation * scale * rotation * skew;

		_transformUpdated = false;
	}
}

//=============================================================================

NS_KAIRY_END

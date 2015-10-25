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

#include <Kairy/Graphics/Sprite.h>
#include <Kairy/Graphics/ShaderProgram.h>
#include <Kairy/Graphics/RenderDevice.h>

#ifdef _3DS
#include "../3DS/VertexPool.h"
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

std::shared_ptr<Sprite> Sprite::create(void)
{
	return std::make_shared<Sprite>();
}

//=============================================================================

std::shared_ptr<Sprite> Sprite::create(const byte * buffer, Uint32 buffer_size, Texture::Location location)
{
	auto sprite = std::make_shared<Sprite>();

	if (!sprite || !sprite->loadTexture(buffer, buffer_size, location))
	{
		return nullptr;
	}

	return sprite;
}

//=============================================================================

std::shared_ptr<Sprite> Sprite::create(const byte * pixels, int width, int height, Texture::Location location)
{
	auto sprite = std::make_shared<Sprite>();

	if (!sprite || !sprite->loadTexture(pixels, width, height, location))
	{
		return nullptr;
	}

	return sprite;
}

//=============================================================================

std::shared_ptr<Sprite> Sprite::create(const std::string & filename, Texture::Location location)
{
	auto sprite = std::make_shared<Sprite>();

	if (!sprite || !sprite->loadTexture(filename, location))
	{
		return nullptr;
	}

	return sprite;
}

//=============================================================================

std::shared_ptr<Sprite> Sprite::create(const std::string & zipfile, const std::string & filename, Texture::Location location)
{
	auto sprite = std::make_shared<Sprite>();

	if (!sprite || !sprite->loadTexture(zipfile, filename, location))
	{
		return nullptr;
	}

	return sprite;
}

//=============================================================================

std::shared_ptr<Sprite> Sprite::create(int width, int height, const Color & color, Texture::Location location)
{
	auto sprite = std::make_shared<Sprite>();

	if (!sprite || !sprite->createTexture(width, height, color, location))
	{
		return nullptr;
	}

	return sprite;
}

//=============================================================================

Sprite::Sprite(void)
	: Node()
{
	init();
}

//=============================================================================

Sprite::Sprite(const byte* buffer, Uint32 buffer_size, Texture::Location location)
{
	_texture.load(buffer, buffer_size, location);

	init();
}

//=============================================================================

Sprite::Sprite(const byte* pixels, int width, int height, Texture::Location location)
{
	_texture.load(pixels, width, height, location);

	init();
}

//=============================================================================

Sprite::Sprite(const std::string& filename, Texture::Location location)
{
	_texture.load(filename, location);

	init();
}

//=============================================================================

Sprite::Sprite(const std::string & zipfile, const std::string & filename,
	Texture::Location location)
{
	_texture.load(zipfile, filename, location);

	init();
}

//=============================================================================

Sprite::Sprite(int width, int height, const Color& color, Texture::Location location)
{
	_texture.create(width, height, color, location);

	init();
}

//=============================================================================

Sprite::~Sprite()
{
}

//=============================================================================

void Sprite::draw()
{
	if (!_device->isInitialized() || !_visible ||
		_size.x == 0.0f || _size.y == 0.0f ||
		_texture.getRealWidth() == 0 || _texture.getRealHeight() == 0)
	{
		return;
	}
	
	updateTransform();

	if (_color.a > 0)
	{
		//=========================================================================
		// Setting up the vertices
		//=========================================================================

		auto u0 = _textureRect.getLeft() / (float)_texture.getRealWidth();
		auto u1 = _textureRect.getRight() / (float)_texture.getRealWidth();
		auto v0 = _textureRect.getTop() / (float)_texture.getRealHeight();
		auto v1 = _textureRect.getBottom() / (float)_texture.getRealHeight();

		ShaderProgram::setUniform(UNIFORM_MODELVIEW_NAME, getCombinedTransform());

#ifdef _3DS
		auto vertices = (VertexPositionTexture*)VertexPool::getInstance()->
			pushVertices(sizeof(VertexPositionTexture), 4);

		vertices[0].position = Vec2(0, 0);
		vertices[1].position = Vec2(_size.x, 0);
		vertices[2].position = Vec2(0, _size.y);
		vertices[3].position = Vec2(_size.x, _size.y);

		vertices[0].texcoord = Vec2(u0, 1 - v0);
		vertices[1].texcoord = Vec2(u1, 1 - v0);
		vertices[2].texcoord = Vec2(u0, 1 - v1);
		vertices[3].texcoord = Vec2(u1, 1 - v1);

		//=========================================================================

		GPU_SetTexEnv(0,
			GPU_TEVSOURCES(GPU_TEXTURE0, GPU_CONSTANT, GPU_CONSTANT),
			GPU_TEVSOURCES(GPU_TEXTURE0, GPU_CONSTANT, GPU_CONSTANT),
			GPU_TEVOPERANDS(0, 0, 0),
			GPU_TEVOPERANDS(0, 0, 0),
			GPU_MODULATE, GPU_MODULATE,
			_color.r | _color.g << 8 | _color.b << 16 | _color.a << 24);

		u32 bufferOffsets[] = { 0x00 };
		u64 bufferPermutations[] = { 0x10 };
		u8 bufferNumAttributes[] = { 2 };

		_texture.bind();

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
			0, 0, -0.5f, c.x, c.y, c.z, c.w, u0, v0,
			_size.x, 0, -0.5f, c.x, c.y, c.z, c.w, u1, v0,
			0, _size.y, -0.5f, c.x, c.y, c.z, c.w, u0, v1,
			_size.x, _size.y, -0.5f, c.x, c.y, c.z, c.w, u1, v1
		};

		glUniform1i(ShaderProgram::getCurrentProgram()->
			getUniformLocation("textureEnabled"), true);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 36, vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_texture.bind();

		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

#endif // _3DS
	}

	Node::draw();
}

//=============================================================================

Sprite& Sprite::updateTextureRect()
{
	if (_textureRect.width == 0 || _textureRect.height == 0)
	{
		setTextureRect(0, 0,
			(float)getTextureWidth(), (float)getTextureHeight());
	}

	return *this;
}

//=============================================================================

bool Sprite::loadTexture(const std::string& filename, Texture::Location location)
{
	bool ret = _texture.load(filename, location);
	updateTextureRect();
	return ret;
}

//=============================================================================

bool Sprite::loadTexture(const std::string & zipfile, const std::string & filename, Texture::Location location)
{
	bool ret = _texture.load(zipfile, filename, location);
	updateTextureRect();
	return ret;
}

//=============================================================================

bool Sprite::loadTexture(const byte* pixels, int width, int height, Texture::Location location)
{
	bool ret = _texture.load(pixels, width, height, location);
	updateTextureRect();
	return ret;
}

//=============================================================================

bool Sprite::loadTexture(const byte* buffer, Uint32 buffer_size, Texture::Location location)
{
	bool ret = _texture.load(buffer, buffer_size, location);
	updateTextureRect();
	return ret;
}

//=============================================================================

bool Sprite::createTexture(int width, int height, const Color& color, Texture::Location location)
{
	bool ret = _texture.create(width, height, color, location);
	updateTextureRect();
	return ret;
}

//=============================================================================

void Sprite::init()
{
	updateTextureRect();

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

NS_KAIRY_END


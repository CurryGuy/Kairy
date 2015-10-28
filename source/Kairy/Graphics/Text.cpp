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

#include <Kairy/Graphics/Text.h>
#include <Kairy/Graphics/RenderDevice.h>

NS_KAIRY_BEGIN

//=============================================================================

std::shared_ptr<Text> Text::create(void)
{
	return std::make_shared<Text>();
}

//=============================================================================

std::shared_ptr<Text> Text::create(float size)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(size))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

std::shared_ptr<Text> Text::create(const std::string & filename)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(filename))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

std::shared_ptr<Text> Text::create(const std::string & filename, float size)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(filename, size))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

std::shared_ptr<Text> Text::createTTF(float size)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(size))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

std::shared_ptr<Text> Text::createTTF(const std::string & filename, float size)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(filename, size))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

std::shared_ptr<Text> Text::createTTF(const byte * buffer, float size)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(buffer, size))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

std::shared_ptr<Text> Text::createBMF(const std::string & filename)
{
	auto text = std::make_shared<Text>();

	if (!text || !text->loadFont(filename))
	{
		return nullptr;
	}

	return text;
}

//=============================================================================

Text::Text(void)
	: Node()
	, _lineWidth(0)
	, _useKerning(true)
{
}

//=============================================================================

Text::Text(const std::string & filename)
	: Text()
{
	loadFont(filename);
}

//=============================================================================

Text::Text(float size)
	: Text()
{
	loadFont(size);
}

//=============================================================================

Text::Text(const std::string & filename, float size)
	: Text()
{
	loadFont(filename, size);
}

//=============================================================================

Text::~Text()
{
}

//=============================================================================

bool Text::loadFont(const std::string & filename)
{
	return _font.loadBmf(filename);
}

//=============================================================================

bool Text::loadFont(const std::string & filename, float size)
{
	return _font.loadTtf(filename, size);
}

//=============================================================================

bool Text::loadFont(const byte * buffer, float size)
{
	return _font.loadTtf(buffer, size);
}

//=============================================================================

bool Text::loadFont(float size)
{
	return _font.loadTtf(size);
}

//=============================================================================

Vec2 Text::measureString(const std::string& str)
{
	float x = 0.0f;
	float y = 0.0f;
	
	Uint32 currentChar;
	Font::Character character;

	for (auto& c : str)
	{
		if (c == '\t')
		{
			incrementX(x, y, _font._base * 4.0f);
			continue;
		}
		else if (c == '\n')
		{
			y += getLineHeight();
			x = 0.0f;
			continue;
		}

		currentChar = Uint32(c);

		auto charIt = _font._characters.find(currentChar);

		if (charIt != _font._characters.end())
		{
			character = charIt->second;
		}
		else
		{
			incrementX(x, y, (float)_font._base);
			continue;
		}

		if (_lineWidth > 0 && x + character.xadvance >= _lineWidth)
		{
			x = 0.0f;
			y += getLineHeight();
		}

		x += character.xadvance;
	}

	return Vec2(x, y + getLineHeight());
}

//=============================================================================

void Text::draw()
{
	if(!_device->isInitialized() || !_visible)
	{
		return;
	}

	Node::draw();
}

//=============================================================================

void Text::incrementX(float& x, float& y, float amount)
{
	if (_lineWidth > 0 && x + amount >= _lineWidth)
	{
		x = 0.0f;
		y += _font._lineHeight * _scale;
	}

	x += amount;
}

//=============================================================================

void Text::updateCharacters()
{
	for (auto& character : _characters)
	{
		removeChild(character.get());
	}

	_characters.clear();

	int previousChar = 0;

	float x = 0.0f;
	float y = 0.0f;

	Uint32 currentChar;
	Font::Character character;

	for (Uint32 i = 0; i < _str.length(); ++i)
	{
		if (_str[i] == '\t')
		{
			incrementX(x, y, _font._base * 4.0f);
			continue;
		}
		else if (_str[i] == '\n')
		{
			y += getLineHeight();
			x = 0.0f;
			continue;
		}

		currentChar = Uint32(_str[i]);

		auto charIt = _font._characters.find(currentChar);

		if (charIt != _font._characters.end())
		{
			character = charIt->second;
		}
		else
		{
			incrementX(x, y, (float)_font._base);
			continue;
		}

		auto& page = _font._pages[character.page];

		int kerning = 0;

		auto kernIt = character.kernings.find(previousChar);

		if (kernIt != character.kernings.end())
		{
			kerning = kernIt->second;
		}

		if (_lineWidth > 0 && x + character.xadvance >= _lineWidth)
		{
			x = 0.0f;
			y += getLineHeight();
		}

		float px = x + character.xoffset;
		float py = y + character.yoffset;

		if (_useKerning)
		{
			px += kerning;
		}

		auto charSprite = std::make_shared<Sprite>();

		charSprite->getTexture() = *page;
		charSprite->setTextureRect((float)character.x, (float)character.y,
			(float)character.width, (float)character.height);

		charSprite->setPosition(px, py);
		charSprite->setColor(_color);
		charSprite->setTag(i);

		addChild(charSprite);
		_characters.push_back(charSprite);

		x += character.xadvance;

		previousChar = currentChar;
	}
}

//=============================================================================

NS_KAIRY_END


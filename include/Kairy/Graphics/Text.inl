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

//=============================================================================

inline void Text::setColor(const Color& color)
{
	Node::setColor(color);
	
	for(auto& c : _characters)
	{
		c->setColor(color);
	}
}

//=============================================================================

inline Text& Text::setString(const std::string& str)
{
	if (str != _str)
	{
		_str = str;
		setSize(measureString(str));
		updateCharacters();
	}

    return *this;
}

//=============================================================================

inline std::string Text::getString() const
{
    return _str;
}

//=============================================================================

inline Text& Text::setLineWidth(int width)
{
    _lineWidth = width;
	updateCharacters();
    return *this;
}

//=============================================================================

inline int Text::getLineWidth() const
{
    return _lineWidth;
}

//=============================================================================

inline Font& Text::getFont()
{
    return _font;
}

//=============================================================================

inline int Text::getLineHeight() const
{
	return _font.getLineHeight();
}

//=============================================================================

inline Text& Text::setUseKerning(bool useKerning)
{
    _useKerning = useKerning;
    return *this;
}

//=============================================================================

inline bool Text::getUseKerning() const
{
    return _useKerning;
}

//=============================================================================

inline std::shared_ptr<Sprite> Text::getCharacter(Uint32 index)
{
	if (index < _characters.size())
		return _characters[index];

	return nullptr;
}

//=============================================================================

inline Vec2 Text::measureString(void)
{
	return measureString(_str);
}

//=============================================================================

inline void Text::draw(const std::string& str)
{
	setString(str);
	draw();
}

//=============================================================================

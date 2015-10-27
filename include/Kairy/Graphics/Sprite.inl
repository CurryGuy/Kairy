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

inline Texture& Sprite::getTexture()
{
    return _texture;
}

//=============================================================================

inline void Sprite::setTexture(const Texture & texture)
{
	_texture = texture;
}

//=============================================================================

inline int Sprite::getTextureWidth() const
{
    return _texture.getWidth();
}

//=============================================================================

inline int Sprite::getTextureHeight() const
{
    return _texture.getHeight();
}

//=============================================================================

inline Vec2 Sprite::getTextureSize() const
{
    return Vec2(
		(float)_texture.getWidth(),
		(float)_texture.getHeight());
}

//=============================================================================

inline Rect Sprite::getTextureRect() const
{
    return _textureRect;
}

//=============================================================================

inline Sprite& Sprite::setTextureRect(const Rect& rect)
{
    _textureRect = rect;
	setSize(_textureRect.getSize());
    return *this;
}

//=============================================================================

inline Sprite& Sprite::setTextureRect(float x, float y, float width, float height)
{
    _textureRect = Rect(x, y, width, height);
	setSize(_textureRect.getSize());
    return *this;
}

//=============================================================================

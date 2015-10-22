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

inline void Drawable::setColor(const Color & color)
{
	_color = color;
}

//=============================================================================

inline void Drawable::setColor(byte r, byte g, byte b, byte a)
{
	_color = Color(r, g, b, a);
}

//=============================================================================

inline Color Drawable::getColor() const
{
	return _color;
}

//=============================================================================

inline void Drawable::setOpacity(byte opacity)
{
	_color.a = opacity;
}

//=============================================================================

inline byte Drawable::getOpacity() const
{
	return _color.a;
}

//=============================================================================

inline bool Drawable::isVisible() const
{
	return _visible;
}

//=============================================================================

inline void Drawable::setVisible(bool visible)
{
	if (visible)
		show();
	else
		hide();
}

//=============================================================================

inline void Drawable::show()
{
	_visible = true;
}

//=============================================================================

inline void Drawable::hide()
{
	_visible = false;
}

//=============================================================================

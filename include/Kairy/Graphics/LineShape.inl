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

//=============================================================================

inline LineShape::LineShape(float x0, float y0, float x1, float y1, float thickness)
	: LineShape(Vec2(x0, y0), Vec2(x1, y1), thickness)
{
}

//=============================================================================

inline LineShape::LineShape(const Vec2& start, const Vec2& end, float thickness)
	: LineShape()
{
	_thickness = thickness;
	setLine(start, end);
}

//=============================================================================

inline LineShape& LineShape::setStart(const Vec2& start)
{
	return setLine(start, _end);
}

//=============================================================================

inline LineShape& LineShape::setEnd(const Vec2& end)
{
	return setLine(_start, end);
}

//=============================================================================

inline LineShape& LineShape::setLine(const Vec2 & start, const Vec2 & end)
{
	_start = start;
	_end = end;
	_size = Vec2((_end - _start).length(), _thickness);
	return *this;
}

//=============================================================================

inline LineShape& LineShape::setLine(float x0, float y0, float x1, float y1)
{
	return setLine(Vec2(x0, y0), Vec2(x1, y1));
}

//=============================================================================

inline float LineShape::getThickness() const
{
	return _thickness;
}

//=============================================================================

inline LineShape& LineShape::setThickness(float thickness)
{
	_thickness = std::max(thickness, 0.0f);
	_size.y = _thickness;
	return *this;
}

//=============================================================================

inline Vec2 LineShape::getStart() const
{
	return _start;
}

//=============================================================================

inline Vec2 LineShape::getEnd() const
{
	return _end;
}

//=============================================================================

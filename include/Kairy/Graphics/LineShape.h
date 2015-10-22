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

#ifndef KAIRY_GRAPHICS_LINE_SHAPE_H_INCLUDED
#define KAIRY_GRAPHICS_LINE_SHAPE_H_INCLUDED

#include "Shape.h"

NS_KAIRY_BEGIN

class LineShape : public Shape
{
public:

	LineShape(void);
	
	inline LineShape(float x0, float y0, float x1, float y1, float thickness = 1.0f);

	inline LineShape(const Vec2& start, const Vec2& end, float thickness = 1.0f);

	virtual ~LineShape();

	inline LineShape& setStart(const Vec2& start);

	inline LineShape& setEnd(const Vec2& end);

	inline LineShape& setLine(const Vec2& start, const Vec2& end);

	inline LineShape& setLine(float x0, float y0, float x1, float y1);

	inline float getThickness() const;

	inline LineShape& setThickness(float thickness);

	inline Vec2 getStart() const;

	inline Vec2 getEnd() const;

	virtual void updateTransform() override;

	virtual void draw() override;

private:
	Vec2 _start;
	Vec2 _end;
	float _thickness;
};

#include "LineShape.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_LINE_SHAPE_H_INCLUDED

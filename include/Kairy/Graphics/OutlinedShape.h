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

#ifndef KAIRY_GRAPHICS_OUTLINED_SHAPE_H_INCLUDED
#define KAIRY_GRAPHICS_OUTLINED_SHAPE_H_INCLUDED

#include "LineShape.h"

NS_KAIRY_BEGIN

class OutlinedShape : public Shape
{
public:

	inline OutlinedShape(void);

	inline virtual ~OutlinedShape(void);

	inline void setOutlineThickness(float thickness);

	inline float getOutlineThickness() const;

	inline void setOutlineColor(const Color& color);

	inline Color getOutlineColor() const;

protected:
	LineShape _outline;
};

#include "OutlinedShape.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_OUTLINED_SHAPE_H_INCLUDED

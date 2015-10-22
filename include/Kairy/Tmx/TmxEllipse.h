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

#ifndef KAIRY_TMX_TMX_ELLIPSE_H_INCLUDED
#define KAIRY_TMX_TMX_ELLIPSE_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class TmxEllipse
{
public:
    TmxEllipse(void)
        :_centerX(0)
        ,_centerY(0)
        ,_radiusX(0)
        ,_radiusY(0)
    {
    }

    TmxEllipse(int centerX, int centerY, int radiusX, int radiusY)
        :_centerX(centerX)
        ,_centerY(centerY)
        ,_radiusX(radiusX)
        ,_radiusY(radiusY)
    {
    }

    inline int getCenterX() const
    {
        return _centerX;
    }

    inline int getCenterY() const
    {
        return _centerY;
    }

    inline int getRadiusX() const
    {
        return _radiusX;
    }

    inline int getRadiusY() const
    {
        return _radiusY;
    }

private:
    int _centerX;
    int _centerY;
    int _radiusX;
    int _radiusY;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_ELLIPSE_H_INCLUDED

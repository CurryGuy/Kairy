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

#ifndef KAIRY_MATH_TRANSFORM_H_INCLUDED
#define KAIRY_MATH_TRANSFORM_H_INCLUDED

#include "Rect.h"

NS_KAIRY_BEGIN

class Transform
{
public:
    static Transform createOrthographic(float left, float right, float bottom,
                                        float  top, float  near, float far);

    inline static Transform createTranslation(float x, float y, float z);
    inline static Transform createTranslation(float x, float y);
    inline static Transform createTranslation(const Vec2& position);

    inline static Transform createRotation(float radians);

    inline static Transform createScale(float x, float y);
    inline static Transform createScale(float scale);

	inline static Transform createSkewX(float radians);
	inline static Transform createSkewY(float radians);

	inline static Transform createFlipX();
	inline static Transform createFlipY();

    inline Transform(void);

    inline void setZero(void);

    inline void setIdentity(void);

    inline float getValue(int x, int y) const;

    inline void setValue(int x, int y, float value);

	inline Vec2 transformVec2(const Vec2& vec);

	Rect transformRect(const Rect& rect);

    inline Transform& combine(const Transform& other);

    inline Transform operator*(const Transform& other) const;

private:
    float _m[4][4];
};

#include "Transform.inl"

NS_KAIRY_END

#endif // KAIRY_MATH_TRANSFORM_H_INCLUDED

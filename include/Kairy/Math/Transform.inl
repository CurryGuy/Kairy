#include "Transform.h"
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

inline Transform Transform::createTranslation(float x, float y, float z)
{
	Transform ret;

	ret._m[0][3] = x;
	ret._m[1][3] = y;
	ret._m[2][3] = z;

	return ret;
}

//=============================================================================

inline Transform Transform::createTranslation(float x, float y)
{
	Transform ret;

	ret._m[0][3] = x;
	ret._m[1][3] = y;
	ret._m[2][3] = 0.0f;

	return ret;
}

//=============================================================================

inline Transform Transform::createTranslation(const Vec2& position)
{
	Transform ret;

	ret._m[0][3] = position.x;
	ret._m[1][3] = position.y;
	ret._m[2][3] = 0.0f;

	return ret;
}

//=============================================================================

inline Transform Transform::createRotation(float radians)
{
	Transform ret;

	float cos = std::cos(radians);
	float sin = std::sin(radians);

	ret._m[0][0] = cos;;
	ret._m[0][1] = -sin;
	ret._m[1][0] = sin;
	ret._m[1][1] = cos;

	return ret;
}

//=============================================================================

inline Transform Transform::createScale(float x, float y)
{
	Transform ret;

	ret._m[0][0] = x;
	ret._m[1][1] = y;
	ret._m[2][2] = 1.0f;
	ret._m[3][3] = 1.0f;

	return ret;
}

//=============================================================================

inline Transform Transform::createScale(float scale)
{
	Transform ret;

	ret._m[0][0] = scale;
	ret._m[1][1] = scale;
	ret._m[2][2] = scale;
	ret._m[3][3] = 1.0f;

	return ret;
}

//=============================================================================

inline Transform Transform::createSkewX(float radians)
{
	Transform ret;

	ret._m[0][1] = std::tan(radians);

	return ret;
}

//=============================================================================

inline Transform Transform::createSkewY(float radians)
{
	Transform ret;

	ret._m[1][0] = std::tan(radians);

	return ret;
}

//=============================================================================

inline Transform Transform::createFlipX()
{
	Transform ret;

	ret._m[1][1] = -1.0f;

	return ret;
}

//=============================================================================

inline Transform Transform::createFlipY()
{
	Transform ret;

	ret._m[0][0] = -1.0f;

	return ret;
}

//=============================================================================

inline Transform::Transform(void)
{
	setIdentity();
}

//=============================================================================

inline void Transform::setZero()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			_m[i][j] = 0.0f;
		}
	}
}

//=============================================================================

inline void Transform::setIdentity()
{
	setZero();

	for (int i = 0; i < 4; ++i)
	{
		_m[i][i] = 1.0f;
	}
}

//=============================================================================

inline float Transform::getValue(int x, int y) const
{
	if (x >= 0 && y >= 0 && x < 4 && y < 4)
	{
		return _m[y][x];
	}
	return 0.0f;
}

//=============================================================================

inline void Transform::setValue(int x, int y, float value)
{
	if (x >= 0 && y >= 0 && x < 4 && y < 4)
	{
		_m[y][x] = value;
	}
}

//=============================================================================

inline Vec2 Transform::transformVec2(const Vec2 & vec)
{
	return Vec2(
		vec.x * _m[0][0] + vec.y * _m[0][1] + _m[0][3],
		vec.x * _m[1][0] + vec.y * _m[1][1] + _m[1][3]);
}

//=============================================================================

inline Transform& Transform::combine(const Transform& other)
{
	Transform ret;
	ret.setZero();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				ret._m[i][j] += _m[i][k] * other._m[k][j];
			}
		}
	}

	*this = ret;

	return *this;
}

//=============================================================================

inline Transform Transform::operator*(const Transform& other) const
{
	Transform ret = *this;
	return ret.combine(other);
}

//=============================================================================

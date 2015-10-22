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

#include <Kairy/Math/Transform.h>

NS_KAIRY_BEGIN

//=============================================================================

Transform Transform::createOrthographic(float left, float right, float bottom,
                                        float top, float near, float far)
{
#ifdef _3DS
    Transform ret;

    Transform ortho;
    ortho._m[0][0] = 2.0f / (right - left);
    ortho._m[0][3] = -(right + left) / (right - left);
    ortho._m[1][1] = 2.0f / (top - bottom);
    ortho._m[1][3] = -(top + bottom) / (top - bottom);
    ortho._m[2][2] = -2.0f / (far - near);
    ortho._m[2][3] = (far + near) / (far - near);
    ortho._m[3][3] = 1.0f;

    Transform fixDepth;

    fixDepth._m[2][2] = 0.5f;
    fixDepth._m[2][3] = -0.5f;

    Transform swapXY;

    swapXY._m[0][0] = 0.0f;
    swapXY._m[0][1] = 1.0f;
    swapXY._m[1][0] = 1.0f;
    swapXY._m[1][1] = 0.0f;

    ret = swapXY * createRotation(M_PI) * fixDepth * ortho;

    return ret;
#else

	float width = right - left;
	float height = bottom - top;
	float depth = far - near;

	Transform ret;
	ret.setZero();

	ret._m[0][0] = 2.0f / width;
	ret._m[0][3] = -(right + left)/width;
	ret._m[1][1] = 2.0f / height;
	ret._m[1][3] = -(top + bottom) / height;
	ret._m[2][2] = -2.0f / depth;
	ret._m[2][3] = -(far + near) / depth;
	ret._m[3][3] = 1.0f;

	return ret;

#endif // _3DS
}

//=============================================================================

Rect Transform::transformRect(const Rect & rect)
{
	Vec2 corners[4];

	corners[0] = Vec2(rect.getLeft(), rect.getTop());
	corners[1] = Vec2(rect.getLeft(), rect.getBottom());
	corners[2] = Vec2(rect.getRight(), rect.getTop());
	corners[3] = Vec2(rect.getRight(), rect.getBottom());

	for (auto& corner : corners)
		corner = transformVec2(corner);

	float left = corners[0].x;
	float right = corners[0].x;
	float top = corners[0].y;
	float bottom = corners[0].y;

	for (auto& corner : corners)
	{
		if (corner.x < left) left = corner.x;
		else if (corner.x > right) right = corner.x;

		if (corner.y < top) top = corner.y;
		else if (corner.y > bottom) bottom = corner.y;
	}

	return Rect(left, top, right - left, bottom - top);
}

//=============================================================================

NS_KAIRY_END

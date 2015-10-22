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

#include <Kairy/Math/Vec3.h>
#include <Kairy/Math/Vec4.h>

NS_KAIRY_BEGIN

//=============================================================================
// Constants
//=============================================================================

const Vec3 Vec3::Zero (0.0f, 0.0f, 0.0f);
const Vec3 Vec3::One  (1.0f, 1.0f, 0.0f);
const Vec3 Vec3::UnitX(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::UnitY(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::UnitZ(0.0f, 0.0f, 1.0f);

//=============================================================================

Vec3::Vec3(const Vec4& v4)
{
	x = v4.x;
	y = v4.y;
	z = v4.z;
}

//=============================================================================

float Vec3::length() const
{
    return std::sqrt(x*x + y*y + z*z);
}

//=============================================================================

float Vec3::lengthSquared() const
{
    return x*x + y*y + z*z;
}

//=============================================================================

Vec3& Vec3::normalize()
{
    float len = length();

    if(len != 0 && len != 1)
    {
        x /= len;
        y /= len;
        z /= len;
    }

    return *this;
}

//=============================================================================

Vec3 Vec3::normalized() const
{
    Vec3 ret = *this;
    ret.normalize();
    return ret;
}

//=============================================================================

float Vec3::distance(const Vec3& other) const
{
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

//=============================================================================

float Vec3::distance(float x, float y, float z) const
{
    float dx = x - this->x;
    float dy = y - this->y;
    float dz = z - this->z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}
//=============================================================================

bool Vec3::isPerpendicular(const Vec3& other) const
{
    return dot(other) == 0.0f;
}

//=============================================================================

bool Vec3::hasSameDirection(const Vec3& other) const
{
    return dot(other) > 0.0f;
}

//=============================================================================

bool Vec3::hasOppositeDirection(const Vec3& other) const
{
    return dot(other) < 0.0f;
}

//=============================================================================

std::string Vec3::toString() const
{
    char buffer[512];
    snprintf(buffer, 512, "(%f, %f, %f)", x, y, z);
    return std::string(buffer);
}

//=============================================================================

NS_KAIRY_END

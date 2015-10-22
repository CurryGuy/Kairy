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

#include <Kairy/Math/Vec4.h>

NS_KAIRY_BEGIN

//=============================================================================
// Constants
//=============================================================================

const Vec4 Vec4::Zero (0.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::One  (1.0f, 1.0f, 0.0f, 1.0f);
const Vec4 Vec4::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
const Vec4 Vec4::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
const Vec4 Vec4::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
const Vec4 Vec4::UnitW(0.0f, 0.0f, 0.0f, 1.0f);

//=============================================================================

float Vec4::length() const
{
    return std::sqrt(x*x + y*y + z*z + w*w);
}

//=============================================================================

float Vec4::lengthSquared() const
{
    return x*x + y*y + z*z + w*w;
}

//=============================================================================

Vec4& Vec4::normalize()
{
    float len = length();

    if(len != 0 && len != 1)
    {
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }

    return *this;
}

//=============================================================================

Vec4 Vec4::normalized() const
{
    Vec4 ret = *this;
    ret.normalize();
    return ret;
}

//=============================================================================

float Vec4::distance(const Vec4& other) const
{
    float dx = other.x - x;
    float dy = other.y - y;
    float dz = other.z - z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

//=============================================================================

float Vec4::distance(float x, float y, float z, float w) const
{
    float dx = x - this->x;
    float dy = y - this->y;
    float dz = z - this->z;

    return std::sqrt(dx*dx + dy*dy + dz*dz);
}
//=============================================================================

bool Vec4::isPerpendicular(const Vec4& other) const
{
    return dot(other) == 0.0f;
}

//=============================================================================

bool Vec4::hasSameDirection(const Vec4& other) const
{
    return dot(other) > 0.0f;
}

//=============================================================================

bool Vec4::hasOppositeDirection(const Vec4& other) const
{
    return dot(other) < 0.0f;
}

//=============================================================================

std::string Vec4::toString() const
{
    char buffer[512];
    snprintf(buffer, 512, "(%f, %f, %f, %f)", x, y, z, w);
    return std::string(buffer);
}

//=============================================================================

NS_KAIRY_END

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

#include <Kairy/Math/Vec2.h>
#include <Kairy/Util/ToString.h>

NS_KAIRY_BEGIN

//=============================================================================
// Constants
//=============================================================================

const Vec2 Vec2::Zero        (0.0f, 0.0f);
const Vec2 Vec2::One         (1.0f, 1.0f);
const Vec2 Vec2::UnitX       (1.0f, 0.0f);
const Vec2 Vec2::UnitY       (0.0f, 1.0f);
const Vec2 Vec2::Middle      (0.5f, 0.5f);
const Vec2 Vec2::TopLeft     (0.0f, 0.0f);
const Vec2 Vec2::TopRight    (1.0f, 0.0f);
const Vec2 Vec2::TopMiddle   (0.5f, 0.0f);
const Vec2 Vec2::BottomLeft  (0.0f, 1.0f);
const Vec2 Vec2::BottomRight (1.0f, 1.0f);
const Vec2 Vec2::BottomMiddle(0.5f, 1.0f);
const Vec2 Vec2::MiddleLeft  (0.0f, 0.5f);
const Vec2 Vec2::MiddleRight (1.0f, 0.5f);

//=============================================================================

float Vec2::length() const
{
    return std::sqrt(x*x + y*y);
}

//=============================================================================

float Vec2::lengthSquared() const
{
    return x*x + y*y;
}

//=============================================================================

Vec2& Vec2::normalize()
{
    float len = length();

    if(len != 0 && len != 1)
    {
        x /= len;
        y /= len;
    }

    return *this;
}

//=============================================================================

Vec2 Vec2::normalized() const
{
    Vec2 ret = *this;
    ret.normalize();
    return ret;
}

//=============================================================================

float Vec2::distance(const Vec2& other) const
{
    float dx = other.x - x;
    float dy = other.y - y;

    return std::sqrt(dx*dx + dy*dy);
}

//=============================================================================

float Vec2::distance(float x, float y) const
{
    float dx = x - this->x;
    float dy = y - this->y;

    return std::sqrt(dx*dx + dy*dy);
}

//=============================================================================

float Vec2::angle() const
{
    return std::atan2(y, x);
}

//=============================================================================

float Vec2::angle(const Vec2& other) const
{
    return std::acos(dot(other));
}

//=============================================================================

Vec2& Vec2::rotate(float radians)
{
    float cos = std::cos(radians);
    float sin = std::sin(radians);

    float newX = x * cos - y * sin;
    float newY = x * sin + y * cos;

    x = newX;
    y = newY;

    return *this;
}

//=============================================================================

bool Vec2::isOnLine(const Vec2& other) const
{
    return (x * other.y - y * other.x) == 0.0f;
}

//=============================================================================

bool Vec2::isPerpendicular(const Vec2& other) const
{
    return dot(other) == 0.0f;
}

//=============================================================================

bool Vec2::hasSameDirection(const Vec2& other) const
{
    return dot(other) > 0.0f;
}

//=============================================================================

bool Vec2::hasOppositeDirection(const Vec2& other) const
{
    return dot(other) < 0.0f;
}

//=============================================================================

std::string Vec2::toString() const
{
    char buffer[512];
    snprintf(buffer, 512, "(%f, %f)", x, y);
    return std::string(buffer);
}

//=============================================================================

NS_KAIRY_END

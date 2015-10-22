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

inline Vec2::Vec2(void)
    :x(0.0f)
    ,y(0.0f)
{
}

//=============================================================================

inline Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

//=============================================================================

inline Vec2::Vec2(float v)
    :x(v)
    ,y(v)
{
}

//=============================================================================

inline Vec2& Vec2::negate()
{
    x = -x;
    y = -y;

    return *this;
}

//=============================================================================

inline void Vec2::set(float v)
{
    x = v;
    y = v;
}

//=============================================================================

inline void Vec2::set(float x, float y)
{
    this->x = x;
    this->y = y;
}

//=============================================================================

inline void Vec2::set(const Vec2& other)
{
    x = other.x;
    y = other.y;
}

//=============================================================================

inline void Vec2::setZero()
{
    x = 0.0f;
    y = 0.0f;
}

//=============================================================================

inline void Vec2::setOne()
{
    x = 1.0f;
    y = 1.0f;
}

//=============================================================================

inline float Vec2::max() const
{
    return std::max(x, y);
}

//=============================================================================

inline float Vec2::dot(const Vec2& other) const
{
    return x * other.x + y * other.y;
}

//=============================================================================

inline bool Vec2::isZero() const
{
    return x == 0.0f && y == 0.0f;
}

//=============================================================================

inline bool Vec2::isOne() const
{
    return x == 1.0f && y == 1.0f;
}

//=============================================================================

inline bool Vec2::equals(const Vec2& other) const
{
    return x == other.x && y == other.y;
}

//=============================================================================

inline bool Vec2::isUnit() const
{
    return length() == 1.0f;
}

//=============================================================================

inline Vec2& Vec2::add(float x, float y)
{
    this->x += x;
    this->y += y;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::add(const Vec2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::sub(float x, float y)
{
    this->x -= x;
    this->y -= y;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::sub(const Vec2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::scale(float x, float y)
{
    this->x *= x;
    this->y *= y;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::scale(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::scale(const Vec2& other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

//=============================================================================

inline Vec2 Vec2::operator+(const Vec2& other) const
{
    return Vec2(x + other.x, y + other.y);
}

//=============================================================================

inline Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2(x - other.x, y - other.y);
}

//=============================================================================

inline Vec2 Vec2::operator*(const Vec2& other) const
{
    return Vec2(x * other.x, y * other.y);
}

//=============================================================================

inline Vec2 Vec2::operator/(const Vec2& other) const
{
    if(other.x != 0.0f && other.y != 0.0f)
    {
        return Vec2(x / other.x, y / other.y);
    }

    return *this;
}

//=============================================================================

inline Vec2 Vec2::operator+(float scalar) const
{
    return Vec2(x + scalar, y + scalar);
}

//=============================================================================

inline Vec2 Vec2::operator-(float scalar) const
{
    return Vec2(x - scalar, y - scalar);
}

//=============================================================================

inline Vec2 Vec2::operator*(float scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

//=============================================================================

inline Vec2 Vec2::operator/(float scalar) const
{
    if(scalar != 0.0f)
    {
        return Vec2(x / scalar, y / scalar);
    }

    return *this;
}

//=============================================================================

inline Vec2& Vec2::operator+=(const Vec2& other)
{
    return add(other);
}

//=============================================================================

inline Vec2& Vec2::operator-=(const Vec2& other)
{
    return sub(other);
}

//=============================================================================

inline Vec2& Vec2::operator*=(const Vec2& other)
{
    return scale(other);
}

//=============================================================================

inline Vec2& Vec2::operator/=(const Vec2& other)
{
    if(other.x != 0.0f && other.y != 0.0f)
    {
        x /= other.x;
        y /= other.y;
    }

    return *this;
}

//=============================================================================

inline Vec2& Vec2::operator+=(float scalar)
{
    x += scalar;
    y += scalar;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::operator-=(float scalar)
{
    x -= scalar;
    y -= scalar;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

//=============================================================================

inline Vec2& Vec2::operator/=(float scalar)
{
    if(scalar != 0.0f)
    {
        x /= scalar;
        y /= scalar;
    }

    return *this;
}

//=============================================================================

inline Vec2 Vec2::operator-(void) const
{
    return Vec2(-x, -y);
}

//=============================================================================

inline bool Vec2::operator==(const Vec2& other) const
{
    return equals(other);
}

//=============================================================================

inline bool Vec2::operator!=(const Vec2& other) const
{
    return !equals(other);
}

//=============================================================================

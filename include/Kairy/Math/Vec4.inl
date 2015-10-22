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

inline Vec4::Vec4(void)
:x(0.0f)
,y(0.0f)
,z(0.0f)
,w(0.0f)
{
}

//=============================================================================

inline Vec4::Vec4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

//=============================================================================

inline Vec4::Vec4(float v)
:x(v)
,y(v)
,z(v)
,w(v)
{
}

//=============================================================================

inline Vec4::Vec4(const Vec3& v3, float w)
{
    this->x = v3.x;
    this->y = v3.y;
    this->z = v3.z;
    this->w = w;
}

//=============================================================================

inline Vec4& Vec4::negate()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;

    return *this;
}

//=============================================================================

inline void Vec4::set(float v)
{
    x = v;
    y = v;
    z = v;
    w = v;
}

//=============================================================================

inline void Vec4::set(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

//=============================================================================

inline void Vec4::set(const Vec3& v3, float w)
{
    this->x = v3.x;
    this->y = v3.y;
    this->z = v3.z;
    this->w = w;
}

//=============================================================================

inline void Vec4::set(const Vec4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

//=============================================================================

inline void Vec4::setZero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}

//=============================================================================

inline void Vec4::setOne()
{
    x = 1.0f;
    y = 1.0f;
    z = 1.0f;
    w = 1.0f;
}

//=============================================================================

inline float Vec4::max() const
{
    return std::max(std::max(x, y), std::max(z, w));
}

//=============================================================================

inline float Vec4::dot(const Vec4& other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

//=============================================================================

inline bool Vec4::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

//=============================================================================

inline bool Vec4::isOne() const
{
    return x == 1.0f && y == 1.0f && z == 1.0f && w == 1.0f;
}

//=============================================================================

inline bool Vec4::equals(const Vec4& other) const
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

//=============================================================================

inline bool Vec4::isUnit() const
{
    return length() == 1.0f;
}

//=============================================================================

inline Vec4& Vec4::add(float x, float y, float z, float w)
{
    this->x += x;
    this->y += y;
    this->z += z;
    this->w += w;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::add(const Vec4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::sub(float x, float y, float z, float w)
{
    this->x -= x;
    this->y -= y;
    this->z -= z;
    this->w -= w;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::sub(const Vec4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::scale(float x, float y, float z, float w)
{
    this->x *= x;
    this->y *= y;
    this->z *= z;
    this->w *= w;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::scale(const Vec4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

//=============================================================================

inline Vec4 Vec4::operator+(const Vec4& other) const
{
    return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

//=============================================================================

inline Vec4 Vec4::operator-(const Vec4& other) const
{
    return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

//=============================================================================

inline Vec4 Vec4::operator*(const Vec4& other) const
{
    return Vec4(x * other.x, y * other.y, z * other.z, w * other.w);
}

//=============================================================================

inline Vec4 Vec4::operator/(const Vec4& other) const
{
    if(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f)
    {
        return Vec4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    return *this;
}

//=============================================================================

inline Vec4 Vec4::operator+(float scalar) const
{
    return Vec4(x + scalar, y + scalar, z + scalar, w + scalar);
}

//=============================================================================

inline Vec4 Vec4::operator-(float scalar) const
{
    return Vec4(x - scalar, y - scalar, z - scalar, w - scalar);
}

//=============================================================================

inline Vec4 Vec4::operator*(float scalar) const
{
    return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

//=============================================================================

inline Vec4 Vec4::operator/(float scalar) const
{
    if(scalar != 0.0f)
    {
        return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    return *this;
}

//=============================================================================

inline Vec4& Vec4::operator+=(const Vec4& other)
{
    return add(other);
}

//=============================================================================

inline Vec4& Vec4::operator-=(const Vec4& other)
{
    return sub(other);
}

//=============================================================================

inline Vec4& Vec4::operator*=(const Vec4& other)
{
    return scale(other);
}

//=============================================================================

inline Vec4& Vec4::operator/=(const Vec4& other)
{
    if(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f && other.w != 0.0f)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
    }

    return *this;
}

//=============================================================================

inline Vec4& Vec4::operator+=(float scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::operator-=(float scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

//=============================================================================

inline Vec4& Vec4::operator/=(float scalar)
{
    if(scalar != 0.0f)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    }

    return *this;
}

//=============================================================================

inline Vec4 Vec4::operator-(void) const
{
    return Vec4(-x, -y, -z, -w);
}

//=============================================================================

inline bool Vec4::operator==(const Vec4& other) const
{
    return equals(other);
}

//=============================================================================

inline bool Vec4::operator!=(const Vec4& other) const
{
    return !equals(other);
}

//=============================================================================

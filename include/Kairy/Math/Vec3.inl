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

inline Vec3::Vec3(void)
:x(0.0f)
,y(0.0f)
,z(0.0f)
{
}

//=============================================================================

inline Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//=============================================================================

inline Vec3::Vec3(float v)
:x(v)
,y(v)
,z(v)
{
}

//=============================================================================

inline Vec3::Vec3(const Vec2& v2, float z)
{
    this->x = v2.x;
    this->y = v2.y;
    this->z = z;
}

//=============================================================================

inline Vec3& Vec3::negate()
{
    x = -x;
    y = -y;
    z = -z;

    return *this;
}

//=============================================================================

inline void Vec3::set(float v)
{
    x = v;
    y = v;
    z = v;
}

//=============================================================================

inline void Vec3::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

//=============================================================================

inline void Vec3::set(const Vec2& v2, float z)
{
    this->x = v2.x;
    this->y = v2.y;
    this->z = z;
}

//=============================================================================

inline void Vec3::set(const Vec3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

//=============================================================================

inline void Vec3::setZero()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

//=============================================================================

inline void Vec3::setOne()
{
    x = 1.0f;
    y = 1.0f;
    z = 1.0f;
}

//=============================================================================

inline float Vec3::max() const
{
    return std::max(std::max(x, y), z);
}

//=============================================================================

inline float Vec3::dot(const Vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

//=============================================================================

inline Vec3 Vec3::cross(const Vec3& other) const
{
    return Vec3(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
}

//=============================================================================

inline bool Vec3::isZero() const
{
    return x == 0.0f && y == 0.0f && z == 0.0f;
}

//=============================================================================

inline bool Vec3::isOne() const
{
    return x == 1.0f && y == 1.0f && z == 1.0f;
}

//=============================================================================

inline bool Vec3::equals(const Vec3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

//=============================================================================

inline bool Vec3::isUnit() const
{
    return length() == 1.0f;
}

//=============================================================================

inline Vec3& Vec3::add(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::add(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::sub(float x, float y, float z)
{
    this->x -= x;
    this->y -= y;
    this->z -= z;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::sub(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::scale(float x, float y, float z)
{
    this->x *= x;
    this->y *= y;
    this->z *= z;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::scale(const Vec3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

//=============================================================================

inline Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

//=============================================================================

inline Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

//=============================================================================

inline Vec3 Vec3::operator*(const Vec3& other) const
{
    return Vec3(x * other.x, y * other.y, z * other.z);
}

//=============================================================================

inline Vec3 Vec3::operator/(const Vec3& other) const
{
    if(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f)
    {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    return *this;
}

//=============================================================================

inline Vec3 Vec3::operator+(float scalar) const
{
    return Vec3(x + scalar, y + scalar, z + scalar);
}

//=============================================================================

inline Vec3 Vec3::operator-(float scalar) const
{
    return Vec3(x - scalar, y - scalar, z - scalar);
}

//=============================================================================

inline Vec3 Vec3::operator*(float scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}

//=============================================================================

inline Vec3 Vec3::operator/(float scalar) const
{
    if(scalar != 0.0f)
    {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    return *this;
}

//=============================================================================

inline Vec3& Vec3::operator+=(const Vec3& other)
{
    return add(other);
}

//=============================================================================

inline Vec3& Vec3::operator-=(const Vec3& other)
{
    return sub(other);
}

//=============================================================================

inline Vec3& Vec3::operator*=(const Vec3& other)
{
    return scale(other);
}

//=============================================================================

inline Vec3& Vec3::operator/=(const Vec3& other)
{
    if(other.x != 0.0f && other.y != 0.0f && other.z != 0.0f)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

    return *this;
}

//=============================================================================

inline Vec3& Vec3::operator+=(float scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::operator-=(float scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

//=============================================================================

inline Vec3& Vec3::operator/=(float scalar)
{
    if(scalar != 0.0f)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }

    return *this;
}

//=============================================================================

inline Vec3 Vec3::operator-(void) const
{
    return Vec3(-x, -y, -z);
}

//=============================================================================

inline bool Vec3::operator==(const Vec3& other) const
{
    return equals(other);
}

//=============================================================================

inline bool Vec3::operator!=(const Vec3& other) const
{
    return !equals(other);
}

//=============================================================================

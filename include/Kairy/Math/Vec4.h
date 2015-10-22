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

#ifndef KAIRY_GRAPHICS_VEC4_H_INCLUDED
#define KAIRY_GRAPHICS_VEC4_H_INCLUDED

#include "Vec3.h"

NS_KAIRY_BEGIN

class Vec3;

/** @class Vec4
    @brief Represents a 4-dimensional vector.
*/
class Vec4
{
public:

    // Commonly used vectors
    static const Vec4 Zero;
    static const Vec4 One;
    static const Vec4 UnitX;
    static const Vec4 UnitY;
    static const Vec4 UnitZ;
    static const Vec4 UnitW;

    /**
     * @brief Default constructor.
     * Construct the vector with its coordinates equal to 0.
     */
    inline Vec4(void);

    /**
     * @brief Construct the vector from its coordinates
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param z The z coordinate.
     * @param w The w coordinate.
     */
    inline Vec4(float x, float y, float z, float w);

    /**
     * @brief Construct the vector with all its coordinates
     * equal to v.
     * @param v The value to assign all the coordinates
     */
    inline Vec4(float v);

    /**
     * @brief Construct the vector with the x, y and z coordinates
     * of the given Vec2.
     * @param v3 The Vec3 containing the x, y and z coordinates.
     * @param z The w coordinate.
     */
    inline Vec4(const Vec3& v3, float w);

    /**
     * @brief Returns the length of the vector.
     * @return The vector length.
     */
    float length() const;

    /**
     * @brief Returns the squared length of the vector.
     * @return The squared length.
     */
    float lengthSquared() const;

    /**
     * @brief Normalize the vector.
     * @return A reference to this vector.
     */
    Vec4& normalize();

    /**
     * @brief Return a normalized copy of the vector.
     * @return Return the normalized vector.
     */
    Vec4 normalized() const;

    /**
     * @brief Negate the components of the vector.
     * @return A reference to this vector.
     */
    inline Vec4& negate();

    /**
     * @brief Set the coordinates of the vector to v.
     * @param v The value to set the coordinates to.
     */
    inline void set(float v);

    /**
     * @brief Set the coordinates of the vector.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param z The z coordinate.
     * @param w The w coordinate.
     */
    inline void set(float x, float y, float z, float w);

    /**
     * @brief Set the x, y and z coordinate equal to the ones
     * of the given Vec3.
     * @param v2 The Vec3 containing the x, y and z coordinates.
     * @param z The z coordinate.
     */
    inline void set(const Vec3& v2, float w);

    /**
     * @brief Set the coordinates of the vector to those in
     * the specified vector.
     * @param other The vector to copy.
     */
    inline void set(const Vec4& other);

    /**
     * @brief Set the coordinates of the vector to 0.
     */
    inline void setZero();

    /**
     * @brief Set the coordinates of the vector to 1.
     */
    inline void setOne();

    /**
     * @brief Returns the distance between this vector and an other.
     * @param other The other vector.
     * @return The distance between this vector and other.
     */
    float distance(const Vec4& other) const;

    /**
     * @brief Returns the distance between this vector and an other.
     * @param x The x coordinate of the other vector.
     * @param y The y coordinate of the other vector.
     * @param z The z coordinate of the other vector.
     * @param w The w coordinate of the other vector.
     * @return The distance between this vector and the vector with
     * the specified x, y, z and w coordinates.
     */
    float distance(float x, float y, float z, float w) const;

    /**
     * @brief Returns the value of the higher coordinate.
     * @return The value of the higher coordinate.
     */
    inline float max() const;

    /**
     * @brief Returns the dot product between this vector and an other.
     * @param other The other vector.
     * @return The dot product between this vector and other.
     */
    inline float dot(const Vec4& other) const;

    /**
     * @brief Checks if the coordinates of the vector are equal to zero.
     * @return True if the coordinates of the vector are equal to zero.
     */
    inline bool isZero() const;

    /**
     * @brief Checks if the coordinates of the vector are equal to one.
     * @return True if the coordinates of the vector are equal to one.
     */
    inline bool isOne() const;

    /**
     * @brief Checks if this vector is equal to an other.
     * @param other The other vector.
     * @return True if this vector and other are equal.
     */
    inline bool equals(const Vec4& other) const;

    /**
     * @brief Check if the vector is a unit vector.
     * @return True if the length of the vector is equal to one.
     */
    inline bool isUnit() const;

    /**
     * @brief Checks if this vector is perpendicular to an other.
     * @param other The other vector.
     * @return True if this vector is perpendicular to other.
     */
    bool isPerpendicular(const Vec4& other) const;

    /**
     * @brief Checks if this vector and an other have the same direction.
     * @param other The other vector.
     * @return True if this vector and other have the same direction.
     */
    bool hasSameDirection(const Vec4& other) const;

    /**
     * @brief Checks if this vector and an other have the opposite direction.
     * @param other The other vector.
     * @return True if this vector and other have the opposite direction.
     */
    bool hasOppositeDirection(const Vec4& other) const;

    /**
     * @brief Return a string representation of the vector.
     * @return A string representing the vector.
     */
    std::string toString() const;

    inline Vec4& add(float x, float y, float z, float w);

    inline Vec4& add(const Vec4& other);

    inline Vec4& sub(float x, float y, float z, float w);

    inline Vec4& sub(const Vec4& other);

    inline Vec4& scale(float x, float y, float z, float w);

    inline Vec4& scale(float scalar);

    inline Vec4& scale(const Vec4& other);

    inline Vec4 operator+(const Vec4& other) const;
    inline Vec4 operator-(const Vec4& other) const;
    inline Vec4 operator*(const Vec4& other) const;
    inline Vec4 operator/(const Vec4& other) const;

    inline Vec4 operator+(float scalar) const;
    inline Vec4 operator-(float scalar) const;
    inline Vec4 operator*(float scalar) const;
    inline Vec4 operator/(float scalar) const;

    inline Vec4& operator+=(const Vec4& other);
    inline Vec4& operator-=(const Vec4& other);
    inline Vec4& operator*=(const Vec4& other);
    inline Vec4& operator/=(const Vec4& other);

    inline Vec4& operator+=(float scalar);
    inline Vec4& operator-=(float scalar);
    inline Vec4& operator*=(float scalar);
    inline Vec4& operator/=(float scalar);

    inline Vec4 operator-(void) const;

    inline bool operator==(const Vec4& other) const;
    inline bool operator!=(const Vec4& other) const;

	union { float x, r; }; ///< The x coordinate
	union { float y, g; }; ///< The y coordinate
	union { float z, b; }; ///< The z coordinate
	union { float w, a; }; ///< The w coordinate
};

#include "Vec4.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_VEC4_H_INCLUDED

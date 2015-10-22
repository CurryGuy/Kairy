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

#ifndef KAIRY_GRAPHICS_VEC3_H_INCLUDED
#define KAIRY_GRAPHICS_VEC3_H_INCLUDED

#include "Vec2.h"

NS_KAIRY_BEGIN

class Vec4;

/** @class Vec3
    @brief Represents a 3-dimensional vector.
*/
class Vec3
{
public:

    // Commonly used vectors
    static const Vec3 Zero;
    static const Vec3 One;
    static const Vec3 UnitX;
    static const Vec3 UnitY;
    static const Vec3 UnitZ;

    /**
     * @brief Default constructor.
     * Construct the vector with its coordinates equal to 0.
     */
    inline Vec3(void);

    /**
     * @brief Construct the vector from its coordinates
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param z The z coordinate.
     */
    inline Vec3(float x, float y, float z);

    /**
     * @brief Construct the vector with all its coordinates
     * equal to v.
     * @param v The value to assign all the coordinates
     */
    inline Vec3(float v);

    /**
     * @brief Construct the vector with the x and y coordinates
     * of the given Vec2.
     * @param v2 The Vec2 containing the x and y coordinates.
     * @param z The z coordinate.
     */
    inline Vec3(const Vec2& v2, float z);
	
	/**
	 * @brief Construct the vector from a vec4.
	 * @param v4 The vector4.
	 */
	Vec3(const Vec4& v4);

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
    Vec3& normalize();

    /**
     * @brief Return a normalized copy of the vector.
     * @return Return the normalized vector.
     */
    Vec3 normalized() const;

    /**
     * @brief Negate the components of the vector.
     * @return A reference to this vector.
     */
    inline Vec3& negate();

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
     */
    inline void set(float x, float y, float z);

    /**
     * @brief Set the x and y coordinate equal to the ones
     * of the given Vec2.
     * @param v2 The Vec2 containing the x and y coordinates.
     * @param z The z coordinate.
     */
    inline void set(const Vec2& v2, float z);

    /**
     * @brief Set the coordinates of the vector to those in
     * the specified vector.
     * @param other The vector to copy.
     */
    inline void set(const Vec3& other);

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
    float distance(const Vec3& other) const;

    /**
     * @brief Returns the distance between this vector and an other.
     * @param x The x coordinate of the other vector.
     * @param y The y coordinate of the other vector.
     * @param z The z coordinate of the other vector.
     * @return The distance between this vector and the vector with
     * the specified x, y and z coordinates.
     */
    float distance(float x, float y, float z) const;

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
    inline float dot(const Vec3& other) const;

    /**
     * @brief Returns the cross product between this vector and an other.
     * @param other The other vector.
     * @return The cross product between this vector and other.
     */
    inline Vec3 cross(const Vec3& other) const;

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
    inline bool equals(const Vec3& other) const;

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
    bool isPerpendicular(const Vec3& other) const;

    /**
     * @brief Checks if this vector and an other have the same direction.
     * @param other The other vector.
     * @return True if this vector and other have the same direction.
     */
    bool hasSameDirection(const Vec3& other) const;

    /**
     * @brief Checks if this vector and an other have the opposite direction.
     * @param other The other vector.
     * @return True if this vector and other have the opposite direction.
     */
    bool hasOppositeDirection(const Vec3& other) const;

    /**
     * @brief Return a string representation of the vector.
     * @return A string representing the vector.
     */
    std::string toString() const;

    inline Vec3& add(float x, float y, float z);

    inline Vec3& add(const Vec3& other);

    inline Vec3& sub(float x, float y, float z);

    inline Vec3& sub(const Vec3& other);

    inline Vec3& scale(float x, float y, float z);

    inline Vec3& scale(float scalar);

    inline Vec3& scale(const Vec3& other);

    inline Vec3 operator+(const Vec3& other) const;
    inline Vec3 operator-(const Vec3& other) const;
    inline Vec3 operator*(const Vec3& other) const;
    inline Vec3 operator/(const Vec3& other) const;

    inline Vec3 operator+(float scalar) const;
    inline Vec3 operator-(float scalar) const;
    inline Vec3 operator*(float scalar) const;
    inline Vec3 operator/(float scalar) const;

    inline Vec3& operator+=(const Vec3& other);
    inline Vec3& operator-=(const Vec3& other);
    inline Vec3& operator*=(const Vec3& other);
    inline Vec3& operator/=(const Vec3& other);

    inline Vec3& operator+=(float scalar);
    inline Vec3& operator-=(float scalar);
    inline Vec3& operator*=(float scalar);
    inline Vec3& operator/=(float scalar);

    inline Vec3 operator-(void) const;

    inline bool operator==(const Vec3& other) const;
    inline bool operator!=(const Vec3& other) const;

	union { float x, r; }; ///< The x coordinate
	union { float y, g; }; ///< The y coordinate
	union { float z, b; }; ///< The z coordinate
};

#include "Vec3.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_VEC3_H_INCLUDED

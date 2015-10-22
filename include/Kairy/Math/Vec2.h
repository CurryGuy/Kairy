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

#ifndef KAIRY_GRAPHICS_VEC2_H_INCLUDED
#define KAIRY_GRAPHICS_VEC2_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

/** @class Vec2
    @brief Represents a 2-dimensional vector.
*/
class Vec2
{
public:

    // Commonly used vectors
    static const Vec2 Zero;
    static const Vec2 One;
    static const Vec2 UnitX;
    static const Vec2 UnitY;
    static const Vec2 Middle;
    static const Vec2 TopLeft;
    static const Vec2 TopRight;
    static const Vec2 TopMiddle;
    static const Vec2 BottomLeft;
    static const Vec2 BottomRight;
    static const Vec2 BottomMiddle;
    static const Vec2 MiddleLeft;
    static const Vec2 MiddleRight;

    /**
     * @brief Default constructor.
     * Construct the vector with its coordinates equal to 0.
     */
    inline Vec2(void);

    /**
     * @brief Construct the vector from its coordinates
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    inline Vec2(float x, float y);

    /**
     * @brief Construct the vector with both its coordinates
     * equal to v.
     * @param v The value to assign to both the x and y coordinates
     */
    inline Vec2(float v);

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
    Vec2& normalize();

    /**
     * @brief Return a normalized copy of the vector.
     * @return Return the normalized vector.
     */
    Vec2 normalized() const;

    /**
     * @brief Negate the components of the vector.
     * @return A reference to this vector.
     */
    inline Vec2& negate();

    /**
     * @brief Set the coordinates of the vector to v.
     * @param v The value to set the coordinates to.
     */
    inline void set(float v);

    /**
     * @brief Set the coordinates of the vector.
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    inline void set(float x, float y);

    /**
     * @brief Set the coordinates of the vector to those in
     * the specified vector.
     * @param other The vector to copy.
     */
    inline void set(const Vec2& other);

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
    float distance(const Vec2& other) const;

    /**
     * @brief Returns the distance between this vector and an other.
     * @param x The x coordinate of the other vector.
     * @param y The y coordinate of the other vector.
     * @return The distance between this vector and the vector with
     * the specified x and y coordinates.
     */
    float distance(float x, float y) const;

    /**
     * @brief Returns the angle (in radians) between this vector and the x axis
     * @return The angle in radians.
     */
    float angle() const;

    /**
     * @brief Returns the angle between this vector and an other.
     * @param other The other vector.
     * @return The angle in radians.
     */
    float angle(const Vec2& other) const;

    /**
     * @brief Rotate this vector by the specified amount.
     * @param radians The angle in radians.
     * @return A reference to this vector.
     */
    Vec2& rotate(float radians);

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
    inline float dot(const Vec2& other) const;

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
    inline bool equals(const Vec2& other) const;

    /**
     * @brief Check if the vector is a unit vector.
     * @return True if the length of the vector is equal to one.
     */
    inline bool isUnit() const;

    bool isOnLine(const Vec2& other) const;

    /**
     * @brief Checks if this vector is perpendicular to an other.
     * @param other The other vector.
     * @return True if this vector is perpendicular to other.
     */
    bool isPerpendicular(const Vec2& other) const;

    /**
     * @brief Checks if this vector and an other have the same direction.
     * @param other The other vector.
     * @return True if this vector and other have the same direction.
     */
    bool hasSameDirection(const Vec2& other) const;

    /**
     * @brief Checks if this vector and an other have the opposite direction.
     * @param other The other vector.
     * @return True if this vector and other have the opposite direction.
     */
    bool hasOppositeDirection(const Vec2& other) const;

    /**
     * @brief Return a string representation of the vector.
     * @return A string representing the vector.
     */
    std::string toString() const;

    inline Vec2& add(float x, float y);

    inline Vec2& add(const Vec2& other);

    inline Vec2& sub(float x, float y);

    inline Vec2& sub(const Vec2& other);

    inline Vec2& scale(float x, float y);

    inline Vec2& scale(float scalar);

    inline Vec2& scale(const Vec2& other);

    inline Vec2 operator+(const Vec2& other) const;
    inline Vec2 operator-(const Vec2& other) const;
    inline Vec2 operator*(const Vec2& other) const;
    inline Vec2 operator/(const Vec2& other) const;

    inline Vec2 operator+(float scalar) const;
    inline Vec2 operator-(float scalar) const;
    inline Vec2 operator*(float scalar) const;
    inline Vec2 operator/(float scalar) const;

    inline Vec2& operator+=(const Vec2& other);
    inline Vec2& operator-=(const Vec2& other);
    inline Vec2& operator*=(const Vec2& other);
    inline Vec2& operator/=(const Vec2& other);

    inline Vec2& operator+=(float scalar);
    inline Vec2& operator-=(float scalar);
    inline Vec2& operator*=(float scalar);
    inline Vec2& operator/=(float scalar);

    inline Vec2 operator-(void) const;

    inline bool operator==(const Vec2& other) const;
    inline bool operator!=(const Vec2& other) const;

	union { float x, u; }; ///< The x coordinate
	union { float y, v; }; ///< The y coordinate
};

#include "Vec2.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_VEC2_H_INCLUDED

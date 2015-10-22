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

#ifndef KAIRY_MATH_RECT_H_INCLUDED
#define KAIRY_MATH_RECT_H_INCLUDED

#include "Vec2.h"

NS_KAIRY_BEGIN

/**
 * @class Rect
 * @brief A 2D rectangle with a position and a dimension.
 */
class Rect
{
public:
    static const Rect Zero;

    /**
     * @brief Default constructor.
     * Constructs a rectangle with all its components set to 0.
     */
    Rect(void);

    /**
     * @brief Constructs a rectangle by its components.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     */
    Rect(float x, float y, float width, float height);

    /**
     * @brief Constructs a rectangle by its origin and size.
     * @param origin The origin of the rectangle.
     * @param size The size of the rectangle.
     */
    Rect(const Vec2& origin, const Vec2& size);

    /**
     * @brief Get the left side of the rectangle.
     * @return The left side of the rectangle.
     */
    inline float getLeft() const;

    /**
     * @brief Get the right side of the rectangle.
     * @return The right side of the rectangle.
     */
    inline float getRight() const;

    /**
     * @brief Get the top side of the rectangle.
     * @return The top side of the rectangle.
     */
    inline float getTop() const;

    /**
     * @brief Get the bottom side of the rectangle.
     * @return The bottom side of the rectangle.
     */
    inline float getBottom() const;

    /**
     * @brief Set the origin of the rectangle.
     * @param x, The x coordinate of the origin.
     * @param y The y coordinate of the origin.
     * @return A reference to this rectangle.
     */
    inline Rect& setOrigin(float x, float y);

    /**
     * @brief Set the origin of the rectangle.
     * @param origin The origin of the rectangle.
     * @return A reference to this rectangle.
     */
    inline Rect& setOrigin(const Vec2& origin);

    /**
     * @brief Set the center of the rectangle.
     * @param centerX The x coordinate of the center of the rectangle.
     * @param centerY The y coordinate of the center of the rectangle.ù
     * @return A reference to this rectangle.
     */
    inline Rect& setCenter(float centerX, float centerY);

    /**
     * @brief Set the center of the rectangle.
     * @param center The center of the rectangle.
     * @return A reference to this rectangle.
     */
    inline Rect& setCenter(const Vec2& center);

    /**
     * @brief Set the rectangle size.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @return A reference to this rectangle.
     */
    inline Rect& setSize(float width, float height);

    /**
     * @brief Set the size of the rectangle.
     * @param size The size of the rectangle.
     * @return A reference to this rectangle.
     */
    inline Rect& setSize(const Vec2& size);

    /**
     * @brief Get the origin of the rectangle.
     * @return The origin of the rectangle.
     */
    inline Vec2 getOrigin() const;

    /**
     * @brief Get size of the rectangle.
     * @return The size of the rectangle.
     */
    inline Vec2 getSize() const;

    /**
     * @brief Get the center of the rectangle.
     * @return The center of the rectangle.
     */
    inline Vec2 getCenter() const;

    /**
     * @brief Get the aspect ratio of the rectangle.
     * @return The width of the rectangle divided by the height.
     */
    inline float getAspectRatio() const;

    /**
     * @brief Calculate the area of the rectangle.
     * @return The area of the rectangle.
     */
    inline float area() const;

    /**
     * @brief Calculate the perimeter of the rectangle.
     * @return The perimeter of the rectangle.
     */
    inline float perimeter() const;

    /**
     * @brief Set the components of the rectangle.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @return A reference to this rectangle.
     */
    inline Rect& set(float x, float y, float width, float height);

    /**
     * @brief Set the rectangle equal to an other rectangle.
     * @param other The other rectangle.
     * @return A reference to this rectangle.
     */
    inline Rect& set(const Rect& other);

    /**
     * @brief Check if the rectangle contains the specified point.
     * @param x The x coordinate of the point.
     * @param y The y coordinate of the point.
     * @return true if the rectangle contains the point.
     */
    inline bool containsPoint(float x, float y) const;

    /**
     * @brief Check if the rectangle contains the specified point.
     * @param point The point.
     * @return true if the rectangle contains the point.
     */
    inline bool containsPoint(const Vec2& point) const;

    /**
     * @brief Check if the rectangle contains an other rectangle.
     * @param other The other rectangle.
     * @return true if the other rectangle is contained in this rectangle.
     */
    inline bool containsRect(const Rect& other) const;

    /**
     * @brief Check if this rectangle intersects with an other.
     * @param other The other rectangle.
     * @return true if the other rectangle intersects with this rectangle.
     */
    inline bool intersects(const Rect& other) const;

    /**
     * @brief Calculate the intersection between this rectangle and an other.
     * @param other The other rectangle.
     * @param intersection The output intersection.
     * @return true if the other rectangle intersects with this rectangle.
     */
    bool intersects(const Rect& other, Rect& intersection) const;

    /**
     * @brief Check if this rectangle is equal to an other.
     * @param other The other rectangle.
     * @return true if this rectangle is equal to the other.
     */
    inline bool equals(const Rect& other) const;

    /**
     * @brief Return a string representation of the rectangle.
     */
    std::string toString() const;

    // Operators
    inline bool operator==(const Rect& other) const;
    inline bool operator!=(const Rect& other) const;
    inline Rect operator*(const Rect& other) const;
    inline Rect operator/(const Rect& other) const;
    inline Rect operator*(float scalar) const;
    inline Rect operator/(float scalar) const;

    float x;      ///< X coordinate of the rectangle
    float y;      ///< Y coordinate of the rectangle
    float width;  ///< Width of the rectangle
    float height; ///< Height of the rectangle
};

#include "Rect.inl"

NS_KAIRY_END

#endif // KAIRY_MATH_RECT_H_INCLUDED

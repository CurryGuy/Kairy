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

#ifndef KAIRY_GRAPHICS_COLOR_H_INCLUDED
#define KAIRY_GRAPHICS_COLOR_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class Vec3;
class Vec4;

/** @class Color
    @brief A color composed of 4 components.
    Each component is a byte [0-255].
*/
class Color
{
public:
    // Constants
    enum
    {
        /** The maximum value a component can have.
          * A color with an alpha value of 255 will be
          * fully opaque.
          */
        OPAQUE = 255
    };

    // Commonly used colors.
    static const Color White;
    static const Color Yellow;
    static const Color Blue;
    static const Color Green;
    static const Color Red;
    static const Color Magenta;
    static const Color Black;
    static const Color Orange;
    static const Color Gray;
    static const Color Cyan;
    static const Color Transparent;

	/**
	 * @brief Returns a random color.
	 */
	static Color Random();

    /**
     * @brief Default constructor
     * Constructs a fully opaque black color.
     * The same as: Color(0, 0, 0, 255);
     */
    Color(void);

    /**
     * @brief Constructs the color from its components.
     * Each component is in the range [0-255].
     *
     * @param r The red component
     * @param g The green component
     * @param b The blue component
     * @param a The alpha component
     */
    Color(byte r, byte g, byte b, byte a = OPAQUE);

    /**
     * @brief Constructs the color from an other color
     * and a desired alpha value.
     * @param other The color to copy.
     * @param a The alpha component.
     */
    Color(const Color& other, byte a);

    /**
     * @brief Constructs the color from a 32-bit unsigned integer
     *
     * @param color A value containing all the 4 components in
     * RGBA order.
     */
    explicit Color(Uint32 color);

	/**
	 * @brief Blend this color with an other one and return the blending result.
	 * @param other The color to blend with this color.
	 * @return The result of the blending.
	 */
	Color blend(const Color& other) const;

	Color mix(const Color& other, float amount) const;

    /**
     * @brief Set each component of the color.
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    void set(byte r, byte g, byte b, byte a = OPAQUE);

    /**
     * @brief Convert HSB to RGB
     * @param hue must be in [0, 360]
     * @param saturation must be in [0, 1]
     * @param brightness must be in [0, 1]
     */
    void setHSB(float hue, float saturation, float brightness);

    /**
     * @brief Convert HSL to RGB
     * @param hue must be in [0, 360]
     * @param saturation must be in [0, 1]
     * @param luminance must be in [0, 1]
     */
    void setHSL(float hue, float saturation, float luminance);

    /**
     * @brief Convert CMYK to RGB
     * @param c must be in [0, 1]
     * @param m must be in [0, 1]
     * @param y must be in [0, 1]
     * @param k must be in [0, 1]
     */
    void setCMYK(float c, float m, float y, float k);

    /**
     * @brief Convert YUV to RGB
     * @param y must be in [0, 1]
     * @param u must be in [-0.436, 0.436]
     * @param v must be in [-0.615, 0.615]
     */
    void setYUV(float y, float u, float v);

    /**
     * @brief Convert the color to a 32-bit unsigned integer
     */
    Uint32 toUint32() const;

    /**
     * @brief Convert the color to a 4-components vector.
     * Each channel will have a value in the range [0-1].
     * @return The color as a 4-components vector.
     */
    Vec4 toVector() const;

    /**
     * @brief Convert the color to the HSB color space.
     * @return The HSB color.
     */
    Vec3 toHSB() const;

    /**
     * @brief Convert the color to the HSL color space.
     * @return The HSL color.
     */
    Vec3 toHSL() const;

    /**
     * @brief Convert the color to the CMYK color space.
     * @return The CMYK color.
     */
    Vec4 toCMYK() const;

    /**
     * @brief Convert the color to the YUV444 color space.
     * @return The YUV color.
     */
    Vec3 toYUV() const;

    /**
     * @brief Check if the color is equal to an other.
     * @return true if the colors are equal, false otherwise
     */
    bool equals(const Color& other) const;

    /**
     * @brief Return a literal representation of the color.
     * @return The string representing the color
     */
    std::string toString() const;

    byte r; ///< The red channel
    byte g; ///< The green channel
    byte b; ///< The blue channel
    byte a; ///< The alpha channel

    // Operators
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(const Color& other) const;

    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);
    Color& operator*=(const Color& other);
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_COLOR_H_INCLUDED

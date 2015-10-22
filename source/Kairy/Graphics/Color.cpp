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

#include <Kairy/Graphics/Color.h>
#include <Kairy/Math/Vec3.h>
#include <Kairy/Math/Vec4.h>
#include <Kairy/System/Random.h>

NS_KAIRY_BEGIN

//=============================================================================
// Constants
//=============================================================================

const Color Color::White       (255, 255, 255);
const Color Color::Yellow      (255, 255,   0);
const Color Color::Blue        (  0,   0, 255);
const Color Color::Green       (  0, 255,   0);
const Color Color::Red         (255,   0,   0);
const Color Color::Magenta     (255,   0, 255);
const Color Color::Black       (  0,   0,   0);
const Color Color::Orange      (255, 127,   0);
const Color Color::Gray        (166, 166, 166);
const Color Color::Cyan        (  0, 255, 255);
const Color Color::Transparent (  0,   0,   0, 0);

//=============================================================================

Color Color::Random()
{
	auto random = Random::getInstance();

	return Color(
		random->nextInt(0, OPAQUE),
		random->nextInt(0, OPAQUE),
		random->nextInt(0, OPAQUE));
}

//=============================================================================

Color::Color(void)
:r(0)
,g(0)
,b(0)
,a(OPAQUE)
{
}

//=============================================================================

Color::Color(byte r, byte g, byte b, byte a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

//=============================================================================

Color::Color(const Color& other, byte a)
{
    set(other.r, other.g, other.b, a);
}

//=============================================================================

Color::Color(Uint32 color)
{
    r = (color >> 24) & OPAQUE;
    g = (color >> 16) & OPAQUE;
    b = (color >>  8) & OPAQUE;
    a = (color >>  0) & OPAQUE;
}

//=============================================================================

Color Color::blend(const Color& other) const
{
	Color res;

	float a0 = a / (float)OPAQUE;
	float a1 = other.a / (float)OPAQUE;

	res.r = (byte)(a0 * r + a1 * (1 - a0) * other.r);
	res.g = (byte)(a0 * g + a1 * (1 - a0) * other.g);
	res.b = (byte)(a0 * b + a1 * (1 - a0) * other.b);
	res.a = (byte)(OPAQUE * (a0 + a1 * (1 - a0)));

	return res;
}

//=============================================================================

Color Color::mix(const Color & other, float amount) const
{
	Color diff = other - *this;

	diff.r = byte(diff.r * amount);
	diff.g = byte(diff.g * amount);
	diff.b = byte(diff.b * amount);
	diff.a = byte(diff.a * amount);

	return *this + diff;
}

//=============================================================================

void Color::set(byte r, byte g, byte b, byte a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

//=============================================================================

void Color::setHSB(float hue, float saturation, float brightness)
{
    if(hue < 0 || hue > 360 ||
       saturation < 0 || saturation > 1 ||
       brightness < 0 || brightness > 1)
    {
        return;
    }

    float res_r = 0.0f;
    float res_g = 0.0f;
    float res_b = 0.0f;

    if(saturation == 0.0f)
    {
        res_r = res_g = res_b = brightness;
    }
    else
    {
        if(hue == 360.0f)
        {
            hue = 0.0f;
        }

        float sectorPos = hue / 60.0f;
        int sectorNumber = int(std::floor(sectorPos));
        float fractionalSector = sectorPos - sectorNumber;

        float p = brightness * (1.0f - saturation);
        float q = brightness * (1.0f - (saturation * fractionalSector));
        float t = brightness * (1.0f - (saturation * (1.0f - fractionalSector)));

        switch(sectorNumber)
        {
            case 0: res_r = brightness; res_g = t; res_b = p; break;
            case 1: res_r = q; res_g = brightness; res_b = p; break;
            case 2: res_r = p; res_g = brightness; res_b = t; break;
            case 3: res_r = p; res_g = q; res_b = brightness; break;
            case 4: res_r = t; res_g = p; res_b = brightness; break;
            default: res_r = brightness; res_g = p; res_b = q; break;
        }
    }

    this->r = byte(res_r * (float)OPAQUE + 0.5f);
    this->g = byte(res_g * (float)OPAQUE + 0.5f);
    this->b = byte(res_b * (float)OPAQUE + 0.5f);
}

//=============================================================================

void Color::setHSL(float hue, float saturation, float luminance)
{
    if(hue < 0 || hue > 360 ||
       saturation < 0 || saturation > 1 ||
       luminance < 0 || luminance > 1)
    {
        return;
    }

    if(saturation == 0.0f)
    {
        this->r = byte(luminance * (float)OPAQUE + 0.5f);
        this->g = byte(luminance * (float)OPAQUE + 0.5f);
        this->b = byte(luminance * (float)OPAQUE + 0.5f);
    }
    else
    {
        float q;
        float p;

        if(luminance < 0.5f)
        {
            q = luminance * (1.0f + saturation);
        }
        else
        {
            q = luminance + saturation - (luminance * saturation);
        }

        p = (2.0f * luminance) - q;

        float hk = hue / 360.0f;

        float t[3] =
        {
            hk + (1.0f / 3.0f),
            hk,
            hk - (1.0f / 3.0f)
        };

        for(int i = 0; i < 3; ++i)
        {
            if(t[i] < 0)
            {
                t[i] += 1.0f;
            }

            if(t[i] > 1)
            {
                t[i] -= 1.0f;
            }

            if((t[i] * 6.0f) < 1)
            {
                t[i] = p + ((q - p) * 6.0f * t[i]);
            }
            else if((t[i] * 2.0f) < 1)
            {
                t[i] = q;
            }
            else if((t[i] * 3.0f) < 2)
            {
                t[i] = p + (q - p) * ((2.0f / 3.0f) - t[i]) * 6.0f;
            }
            else
            {
                t[i] = p;
            }
        }

        this->r = byte(t[0] * (float)OPAQUE + 0.5f);
        this->g = byte(t[1] * (float)OPAQUE + 0.5f);
        this->b = byte(t[2] * (float)OPAQUE + 0.5f);
    }
}

//=============================================================================

void Color::setCMYK(float c, float m, float y, float k)
{
    if(c < 0 || c > 1 || m < 0 || m > 1 ||
       y < 0 || y > 1 || k < 0 || k > 1)
    {
        return;
    }

    this->r = byte((1.0f - c) * (1.0f - k) * (float)OPAQUE + 0.5f);
    this->g = byte((1.0f - m) * (1.0f - k) * (float)OPAQUE + 0.5f);
    this->b = byte((1.0f - y) * (1.0f - k) * (float)OPAQUE + 0.5f);
}

//=============================================================================

void Color::setYUV(float y, float u, float v)
{
    if(y < 0 || y > 1 ||
       u < -0.436f || u > 0.436f ||
       v < -0.615f || v > 0.615f)
    {
        return;
    }

    this->r = byte((y + 1.139837398373983740f * v) * (float)OPAQUE + 0.5f);
    this->g = byte((y - 0.3946517043589703515f * u - 0.5805986066674976801f * v) * (float)OPAQUE + 0.5f);
    this->b = byte((y + 2.032110091743119266f * u) * (float)OPAQUE + 0.5f);
}

//=============================================================================

Uint32 Color::toUint32() const
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

//=============================================================================

Vec4 Color::toVector() const
{
    return Vec4(r / (float)OPAQUE,
                g / (float)OPAQUE,
                b / (float)OPAQUE,
                a / (float)OPAQUE);
}

//=============================================================================

Vec3 Color::toHSB() const
{
    float red = r / (float)OPAQUE;
    float green = g / (float)OPAQUE;
    float blue = b / (float)OPAQUE;

    float max = std::max(red, std::max(green, blue));
    float min = std::min(red, std::min(green, blue));

    float diff = max - min;

    if(diff == 0.0f)
    {
        diff = 0.00000001f;
    }

    float h = 0.0f;

    if(max == red && green >= blue)
    {
        h = 60.0f * (green - blue) / diff;
    }
    else if(max == red && green < blue)
    {
        h = 60.0f * (green - blue) / diff + 360.0f;
    }
    else if(max == green)
    {
        h = 60.0f * (blue - red) / diff + 120.0f;
    }
    else if(max == blue)
    {
        h = 60.0f * (red - green) / diff + 240.0f;
    }

    float s = (max == 0.0f) ? 0.0f : (1.0f - (max/min));

    return Vec3(h, s, max);
}

//=============================================================================

Vec3 Color::toHSL() const
{
    float h = 0.0f;
    float s = 0.0f;
    float l = 0.0f;

    float red = r / (float)OPAQUE;
    float green = g / (float)OPAQUE;
    float blue = b / (float)OPAQUE;

    float max = std::max(red, std::max(green, blue));
    float min = std::min(red, std::min(green, blue));

    float diff = max - min;

    if(diff == 0.0f)
    {
        diff = 0.00000001f;
    }

    if(max == min)
    {
        h = 0.0f;
    }
    else if(max == red && green >= blue)
    {
        h = 60.0f * (green - blue) / diff;
    }
    else if(max == red && green < blue)
    {
        h = 60.0f * (blue - red) / diff + 120.0f;
    }
    else if(max == blue)
    {
        h = 60.0f * (red - green) / diff + 240.0f;
    }

    l = (max + min) / 2.0f;

    if(l == 0.0f || max == min)
    {
        s = 0.0f;
    }
    else if(l > 0.0f && l <= 0.5f)
    {
        s = (max-min) / (max+min);
    }
    else if(l > 0.5f)
    {
        s = (max - min) / (2.0f - (max + min));
    }

    return Vec3(h, s, l);
}

//=============================================================================

Vec4 Color::toCMYK() const
{
    float c = (OPAQUE - r) / (float)OPAQUE;
    float m = (OPAQUE - g) / (float)OPAQUE;
    float y = (OPAQUE - b) / (float)OPAQUE;
    float k = std::min(c, std::min(m, y));

    if(k == 1.0f)
    {
        return Vec4::UnitW;
    }
    else
    {
        return Vec4((c-k)/(1-k), (m-k)/(1-k), (y-k)/(1-k), k);
    }
}

//=============================================================================

Vec3 Color::toYUV() const
{
    float red = r / (float)OPAQUE;
    float green = g / (float)OPAQUE;
    float blue = b / (float)OPAQUE;

    float y = 0.299f * red + 0.587f * green + 0.114f * blue;
    float u = -0.14713f * red - 0.28886f * green + 0.436f * blue;
    float v = 0.615f * red - 0.51499f * green - 0.10001f * blue;

    return Vec3(y, u, v);
}

//=============================================================================

bool Color::equals(const Color& other) const
{
    return
        r == other.r &&
        g == other.g &&
        b == other.b &&
        a == other.a;
}

//=============================================================================

std::string Color::toString() const
{
    char buffer[512];
    snprintf(buffer, 512, "(%i, %i, %i, %i)",
             int(r), int(g), int(b), int(a));
    return std::string(buffer);
}

//=============================================================================

bool Color::operator==(const Color& other) const
{
    return equals(other);
}

//=============================================================================

bool Color::operator!=(const Color& other) const
{
    return !equals(other);
}

//=============================================================================

Color Color::operator+(const Color& other) const
{
    return Color(std::min(r + other.r, 255),
                 std::min(g + other.g, 255),
                 std::min(b + other.b, 255),
                 std::min(a + other.a, 255));
}

//=============================================================================

Color Color::operator-(const Color& other) const
{
    return Color(std::max(r - other.r, 0),
                 std::max(g - other.g, 0),
                 std::max(b - other.b, 0),
                 std::max(a - other.a, 0));
}

//=============================================================================

Color Color::operator*(const Color& other) const
{
    return Color(r * other.r / 255,
                 g * other.g / 255,
                 b * other.b / 255,
                 a * other.a / 255);
}

//=============================================================================

Color& Color::operator+=(const Color& other)
{
    r = std::min(r + other.r, 255);
    g = std::min(g + other.g, 255);
    b = std::min(b + other.b, 255);
    a = std::min(a + other.a, 255);

    return *this;
}

//=============================================================================

Color& Color::operator-=(const Color& other)
{
    r = std::max(r - other.r, 0);
    g = std::max(g - other.g, 0);
    b = std::max(b - other.b, 0);
    a = std::max(a - other.a, 0);

    return *this;
}

//=============================================================================

Color& Color::operator*=(const Color& other)
{
    r = r * other.r / 255;
    g = g * other.g / 255;
    b = b * other.b / 255;
    a = a * other.a / 255;

    return *this;
}

//=============================================================================

NS_KAIRY_END

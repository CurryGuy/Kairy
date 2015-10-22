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

inline Rect::Rect(void)
    :x(0.0f)
    ,y(0.0f)
    ,width(0.0f)
    ,height(0.0f)
{
}

//=============================================================================

inline Rect::Rect(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

//=============================================================================

inline Rect::Rect(const Vec2& origin, const Vec2& size)
{
    setOrigin(origin);
    setSize(size);
}

//=============================================================================

inline float Rect::getLeft() const
{
    return std::min(x, x + width);
}

//=============================================================================

inline float Rect::getRight() const
{
    return std::max(x, x + width);
}

//=============================================================================

inline float Rect::getTop() const
{
    return std::min(y, y + height);
}

//=============================================================================

inline float Rect::getBottom() const
{
    return std::max(y, y + height);
}

//=============================================================================

inline Rect& Rect::setOrigin(float x, float y)
{
    this->x = x;
    this->y = y;
    return *this;
}

//=============================================================================

inline Rect& Rect::setOrigin(const Vec2& origin)
{
    x = origin.x;
    y = origin.y;
    return *this;
}

//=============================================================================

inline Rect& Rect::setCenter(float centerX, float centerY)
{
    x = centerX - width / 2.0f;
    y = centerY - height / 2.0f;
    return *this;
}

//=============================================================================

inline Rect& Rect::setCenter(const Vec2& center)
{
    x = center.x - width / 2.0f;
    y = center.y - height / 2.0f;
    return *this;
}

//=============================================================================

inline Rect& Rect::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
    return *this;
}

//=============================================================================

inline Rect& Rect::setSize(const Vec2& size)
{
    width = size.x;
    height = size.y;
    return *this;
}

//=============================================================================

inline Vec2 Rect::getOrigin() const
{
    return Vec2(x, y);
}

//=============================================================================

inline Vec2 Rect::getSize() const
{
    return Vec2(width, height);
}

//=============================================================================

inline Vec2 Rect::getCenter() const
{
    return Vec2(x + width / 2.0f, y + height / 2.0f);
}

//=============================================================================

inline float Rect::getAspectRatio() const
{
    if(height != 0.0f)
    {
        return width / height;
    }
    return 0.0f;
}

//=============================================================================

inline float Rect::area() const
{
    return width * height;
}

//=============================================================================

inline float Rect::perimeter() const
{
    return width * 2 + height * 2;
}

//=============================================================================

inline Rect& Rect::set(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    return *this;
}

//=============================================================================

inline Rect& Rect::set(const Rect& other)
{
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
    return *this;
}

//=============================================================================

inline bool Rect::containsPoint(float x, float y) const
{
	return x >= getLeft() && x <= getRight() &&
		y >= getTop() && y <= getBottom();
}

//=============================================================================

inline bool Rect::containsPoint(const Vec2& point) const
{
    return containsPoint(point.x, point.y);
}

//=============================================================================

inline bool Rect::containsRect(const Rect& other) const
{
    return other.getLeft() > getLeft() && other.getLeft() < getRight() &&
            other.getRight() > getLeft() && other.getRight() < getRight() &&
            other.getTop() > getTop() && getTop() < other.getBottom() &&
            other.getBottom() > getTop() && other.getBottom() < getBottom();
}

//=============================================================================

inline bool Rect::intersects(const Rect& other) const
{
    return getLeft() < other.getRight() &&
            getRight() > other.getLeft() &&
            getTop() < other.getBottom() &&
            getRight() > other.getTop();
}

//=============================================================================

inline bool Rect::equals(const Rect& other) const
{
    return x == other.x &&
            y == other.y &&
            width == other.width &&
            height == other.height;
}

//=============================================================================

inline bool Rect::operator==(const Rect& other) const
{
    return equals(other);
}

//=============================================================================

inline bool Rect::operator!=(const Rect& other) const
{
    return !equals(other);
}

//=============================================================================

inline Rect Rect::operator*(const Rect& other) const
{
    return Rect(x*other.x,y*other.y,width*other.width,height*other.height);
}

//=============================================================================

inline Rect Rect::operator/(const Rect& other) const
{
    if(other.x != 0 && other.y != 0 && other.width != 0 && other.height != 0)
    {
        return Rect(x/other.x,y/other.y,width/other.width,height/other.height);
    }
    return Rect::Zero;
}

//=============================================================================

inline Rect Rect::operator*(float scalar) const
{
    return Rect(x*scalar,y*scalar,width*scalar,height*scalar);
}

//=============================================================================

inline Rect Rect::operator/(float scalar) const
{
    if(scalar != 0)
    {
        return Rect(x/scalar,y/scalar,width/scalar,height/scalar);
    }
    return Rect::Zero;
}

//=============================================================================

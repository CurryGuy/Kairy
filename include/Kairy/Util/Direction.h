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

#ifndef KAIRY_UTIL_DIRECTION_H_INCLUDED
#define KAIRY_UTIL_DIRECTION_H_INCLUDED

#include <Kairy/Math/Vec2.h>

NS_KAIRY_BEGIN

enum class Direction
{
	Down,
	Left,
	Right,
	Up
};

inline Vec2 GetDirectionVector(Direction dir)
{
	switch (dir)
	{
	case Direction::Down: return Vec2(0, 1);
	case Direction::Left: return Vec2(-1, 0);
	case Direction::Right: return Vec2(1, 0);
	default: return Vec2(0, -1);
	}
}

inline Direction GetOppositeDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::Down: return Direction::Up;
	case Direction::Left: return Direction::Right;
	case Direction::Right: return Direction::Left;
	default: return Direction::Down;
	}
}

NS_KAIRY_END

#endif // KAIRY_UTIL_DIRECTION_H_INCLUDED

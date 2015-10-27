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

#ifndef KAIRY_COMMON_H_INCLUDED
#define KAIRY_COMMON_H_INCLUDED

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <functional>
#include <vector>
#include <map>
#include <memory>
#include <array>

#ifdef _3DS
#include <3ds.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define M_PI 3.14159265358979323846
#endif // _3DS

//=============================================================================
// Version macros
//=============================================================================
#define KAIRY_VERSION_MAJOR 1
#define KAIRY_VERSION_MINOR 0
#define KAIRY_VERSION_PATCH 0

#define NS_KAIRY_BEGIN namespace kairy {
#define NS_KAIRY_END }
#define USING_NS_KAIRY using namespace kairy

#define TOP_SCREEN_WIDTH 400
#define TOP_SCREEN_HEIGHT 240
#define BOTTOM_SCREEN_WIDTH 320
#define BOTTOM_SCREEN_HEIGHT 240

#define DEFAULT_DEPTH 0.5f

#define UNIFORM_PROJECTION_NAME "projection"
#define UNIFORM_MODELVIEW_NAME "modelview"

NS_KAIRY_BEGIN

enum class Screen
{
    Top = 0,
    Bottom = 1
};

enum class Side
{
    Left = 0,
    Right = 1
};

inline int GetScreenWidth(Screen screen)
{
    return screen == Screen::Top ?
            TOP_SCREEN_WIDTH :
            BOTTOM_SCREEN_WIDTH;
}

inline int GetScreenHeight(Screen screen)
{
    return screen == Screen::Top ?
            TOP_SCREEN_HEIGHT :
            BOTTOM_SCREEN_HEIGHT;
}

enum class ImageFormat
{
    Png,
    Bmp,
    Tga,
    Jpg
};

enum class PixelFormat
{
	RGB8,
	RGBA8
};

using Int8 = signed char;
using Uint8 =  unsigned char;
using Int16 = signed short;
using Uint16 = unsigned short;
using Int32 =  signed int;
using Uint32 = unsigned int;
using Int64 =  signed long long;
using Uint64 =  unsigned long long;
using byte = unsigned char;

NS_KAIRY_END

#endif // KAIRY_COMMON_H_INCLUDED

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

#ifndef KAIRY_UTIL_ENDIAN_H_INCLUDED
#define KAIRY_UTIL_ENDIAN_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

namespace util
{

inline int bytesToIntLE(const byte* bytes)
{
    return bytes[0] |
            bytes[1] << 8 |
            bytes[2] << 16 |
            bytes[3] << 24;
}

inline Uint32 bytesToUintLE(const byte* bytes)
{
    return bytes[0] |
            bytes[1] << 8 |
            bytes[2] << 16 |
            bytes[3] << 24;
}

inline short bytesToShortLE(const byte* bytes)
{
    return bytes[0] | bytes[1] << 8;
}

inline Uint16 bytesToUshortLE(const byte* bytes)
{
    return bytes[0] | bytes[1] << 8;
}

inline int bytesToIntBE(const byte* bytes)
{
    return bytes[3] |
            bytes[2] << 8 |
            bytes[1] << 16 |
            bytes[0] << 24;
}

inline Uint32 bytesToUintBE(const byte* bytes)
{
    return bytes[3] |
            bytes[2] << 8 |
            bytes[1] << 16 |
            bytes[0] << 24;
}

inline short bytesToShortBE(const byte* bytes)
{
    return bytes[1] | bytes[0] << 8;
}

inline Uint16 bytesToUshortBE(const byte* bytes)
{
    return bytes[1] | bytes[0] << 8;
}

} /* namespace util */

NS_KAIRY_END

#endif // KAIRY_UTIL_ENDIAN_H_INCLUDED

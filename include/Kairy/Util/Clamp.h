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

#ifndef KAIRY_UTIL_CLAMP_H_INCLUDED
#define KAIRY_UTIL_CLAMP_H_INCLUDED

#include <Kairy/Common.h>
#include <algorithm>

NS_KAIRY_BEGIN

namespace util
{
    /**
     * @brief Restricts a value to be within a specified range.
     * @param v The value
     * @param min The minimum
     * @param max The maximum
     * @return The clamped value
     */
    template<typename T>
    inline const T& clamp(const T& v, const T& min, const T& max)
    {
        return std::min(std::max(v, min), max);
    }
} /* namespace util */

NS_KAIRY_END

#endif // KAIRY_UTIL_CLAMP_H_INCLUDED

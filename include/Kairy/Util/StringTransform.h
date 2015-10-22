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

#ifndef KAIRY_UTIL_STRING_TRANSFORM_H_INCLUDED
#define KAIRY_UTIL_STRING_TRANSFORM_H_INCLUDED

#include <Kairy/Common.h>
#include <algorithm>

NS_KAIRY_BEGIN

namespace util
{
/**
 * @brief Returns a copy of the string converted to lowercase.
 * @param str The string to convert.
 * @return The lowercase string.
 */
inline std::string tolower_string(const std::string& str)
{
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

/**
 * @brief Returns a copy of the string converted to uppercase.
 * @param str The string to convert.
 * @return The uppercase string.
 */
inline std::string toupper_string(const std::string& str)
{
    std::string upper = str;
    std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    return upper;
}

/**
 * @brief Returns a capitalized copy of the string.
 * @param str The string to capitalize.
 * @return The capitalized string.
 */
inline std::string capitalize_string(const std::string& str)
{
    std::string capitalized = tolower_string(str);
    capitalized[0] = ::toupper(capitalized[0]);
    return capitalized;
}

inline void string_replace(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
    {
        return;
    }

    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void string_remove(std::string& str, const std::string& chars)
{
    for(Uint32 i = 0; i < chars.length(); ++i)
    {
        str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
    }
}

} /* namespace util */

NS_KAIRY_END

#endif // KAIRY_UTIL_STRING_TRANSFORM_H_INCLUDED

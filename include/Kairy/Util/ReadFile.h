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

#ifndef KAIRY_UTIL_READ_FILE_H_INCLUDED
#define KAIRY_UTIL_READ_FILE_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

namespace util
{
    inline bool ReadAllBytes(const std::string& filename, std::vector<byte>& outBytes)
    {
        FILE* fp = fopen(filename.c_str(), "rb");
        if(!fp) return false;
        fseek(fp, 0, SEEK_END);
        std::size_t len = ftell(fp);
        rewind(fp);
        outBytes.resize(len);
        std::size_t ret = fread(&outBytes.front(), 1, len, fp);
        fclose(fp);
        return ret == len;
    }

} /* namespace util */

NS_KAIRY_END

#endif // KAIRY_UTIL_READ_FILE_H_INCLUDED

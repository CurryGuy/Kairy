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

#ifndef KAIRY_SYSTEM_FILEIO_H_INCLUDED
#define KAIRY_SYSTEM_FILEIO_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class FileIo
{
public:

    static void openSdArchive();

    static void closeSdArchive();

    static bool createDirectory(const std::string& dir);

    static bool deleteDirectory(const std::string& dir);

    static bool deleteFile(const std::string& file);

    static bool exists(const std::string& path);

    static bool getFiles(const std::string& dir, std::vector<std::string>& outFiles);

    static bool move(const std::string& src, const std::string& dst);

    static std::string getCurrentDirectory();

    static bool setCurrentDirectory(const std::string& dir);

private:
    FileIo(void) = default;
    FileIo(const FileIo&) = default;
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_DIRECTORY_H_INCLUDED

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

#ifndef KAIRY_SYSTEM_FILE_H_INCLUDED
#define KAIRY_SYSTEM_FILE_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class File
{
public:

	static std::string getExtension(const std::string& filename);

	static bool copy(const std::string& src, const std::string& dst);

	static bool createFile(const std::string& filename);

	static bool createFile(const std::string& filename, Uint32 size);

	static bool deleteFile(const std::string& filename);

	static bool exists(const std::string& filename);

	static bool move(const std::string& src, const std::string& dst);

	static bool readAllBytes(const std::string& filename, std::vector<byte>& outBytes);

	static bool readAllText(const std::string& filename, std::string& outText);

	static bool readAllLines(const std::string& filename, std::vector<std::string>& outLines);

	static bool writeAllBytes(const std::string& filename, const std::vector<byte>& bytes);

	static bool writeAllText(const std::string& filename, const std::string& text);

	static bool writeAllLines(const std::string& filename, const std::vector<std::string>& lines);

	File(void) = delete;
	File(const File&) = delete;

private:
#ifdef _3DS
	static void openSdArchive();
	static void closeSdArchive();
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_FILE_H_INCLUDED

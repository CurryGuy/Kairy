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

#include <Kairy/System/File.h>
#ifndef _3DS
#include <boost/filesystem.hpp>
#endif // _3DS

NS_KAIRY_BEGIN

#ifdef _3DS
static FS_archive sdmc_archive;
#endif // _3DS

//=============================================================================

bool File::copy(const std::string& src, const std::string& dst)
{
	std::ifstream ss(src, std::ios::binary);
	std::ofstream ds(dst, std::ios::binary);

	if (!ss.is_open() || !ds.is_open())
	{
		return false;
	}

	std::istreambuf_iterator<char> ss_begin(ss);
	std::istreambuf_iterator<char> ss_end;
	std::ostreambuf_iterator<char> ds_begin(ds);

	std::copy(ss_begin, ss_end, ds_begin);

	return true;
}

//=============================================================================

bool File::createFile(const std::string & filename)
{
	return std::ofstream(filename).is_open();
}

//=============================================================================

bool File::createFile(const std::string & filename, Uint32 size)
{
	std::ofstream stream(filename);

	if (!stream.is_open() || size == 0)
		return false;

	stream.seekp(size - 1);
	stream.write("", 1);

	return true;
}

//=============================================================================

bool File::deleteFile(const std::string & filename)
{
#ifdef _3DS
	openSdArchive();
	Result ret = FSUSER_DeleteFile(nullptr, sdmc_archive,
		FS_makePath(PATH_CHAR, filename.c_str()));
	closeSdArchive();
	return ret == 0;
#else
	return boost::filesystem::remove(filename);
#endif // _3DS
}

//=============================================================================

bool File::exists(const std::string & filename)
{
	return std::ifstream(filename).is_open();
}

//=============================================================================

bool File::move(const std::string & src, const std::string & dst)
{
	if (!copy(src, dst))
	{
		return false;
	}

	return deleteFile(src);
}

//=============================================================================

bool File::readAllBytes(const std::string & filename, std::vector<byte>& outBytes)
{
	std::ifstream stream(filename, std::ios::binary);

	if (!stream.is_open())
	{
		return false;
	}

	stream.seekg(0, std::ios::end);
	auto size = std::size_t(stream.tellg());
	stream.seekg(0);

	outBytes.resize(size);

	stream.read((char*)&outBytes[0], size);

	return true;
}

//=============================================================================

bool File::readAllText(const std::string & filename, std::string & outText)
{
	std::ifstream stream(filename, std::ios::binary);

	if (!stream.is_open())
	{
		return false;
	}

	stream.seekg(0, std::ios::end);
	auto size = std::size_t(stream.tellg());
	stream.seekg(0);

	outText.resize(size + 1);

	stream.read(&outText[0], size);

	outText[size] = '\0';

	return true;
}

//=============================================================================

bool File::readAllLines(const std::string & filename, std::vector<std::string>& outLines)
{
	std::ifstream stream(filename);

	if (!stream.is_open())
	{
		return false;
	}

	outLines.clear();

	std::string line;

	while (std::getline(stream, line))
	{
		outLines.push_back(line);
	}

	return true;
}

//=============================================================================

bool File::writeAllBytes(const std::string & filename, const std::vector<byte>& bytes)
{
	std::ofstream stream(filename, std::ios::binary);

	if (!stream.is_open())
	{
		return false;
	}

	stream.write((const char*)bytes.data(), bytes.size());

	return true;
}

//=============================================================================

bool File::writeAllText(const std::string & filename, const std::string & text)
{
	std::ofstream stream(filename);

	if (!stream.is_open())
	{
		return false;
	}

	stream << text;

	return true;
}

//=============================================================================

bool File::writeAllLines(const std::string & filename, const std::vector<std::string>& lines)
{
	std::ofstream stream(filename);

	if (!stream.is_open())
	{
		return false;
	}

	for (auto& line : lines)
	{
		stream << line << std::endl;
	}

	return true;
}

//=============================================================================

#ifdef _3DS

void File::openSdArchive()
{
	sdmc_archive.id = ARCH_SDMC;
	sdmc_archive.lowPath = (FS_path) { PATH_EMPTY, 1, (u8*)"" };
	FSUSER_OpenArchive(nullptr, &sdmc_archive);
}

//=============================================================================

void File::closeSdArchive()
{
	FSUSER_CloseArchive(nullptr, &sdmc_archive);
}

#endif // _3DS

//=============================================================================

NS_KAIRY_END

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

#include <Kairy/System/Directory.h>
#ifdef _3DS
#include <unistd.h>
#else
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#endif // _3DS

NS_KAIRY_BEGIN

#ifdef _3DS
static FS_archive sdmc_archive;
#endif // _3DS

//=============================================================================

bool Directory::createDirectory(const std::string& dir)
{

#ifdef _3DS
	openSdArchive();

	std::vector<std::string> levels;
	std::string::size_type index = 0;

	do
	{
		index = dir.find_first_of("\\/", index + 1);
		auto end = (index == std::string::npos) ? dir.length() : index;
		levels.push_back(dir.substr(0, end));
	} while (index != std::string::npos);

	for (auto& level : levels)
	{
		FSUSER_CreateDirectory(nullptr, sdmc_archive,
			FS_makePath(PATH_CHAR, level.c_str()));
	}

	closeSdArchive();

	return true;
#else
	return boost::filesystem::create_directories(dir);
#endif // _3DS
}

//=============================================================================//=============================================================================

bool Directory::deleteDirectory(const std::string & dir)
{
#ifdef _3DS
	openSdArchive();

	Result ret = FSUSER_DeleteDirectoryRecursively(nullptr,
		sdmc_archive, FS_makePath(PATH_CHAR, dir.c_str())) == 0;

	closeSdArchive();
	
	return ret == 0;
#else
	return boost::filesystem::remove_all(dir) != 0;
#endif // _3DS
}

//=============================================================================

std::string Directory::getCurrentDirectory()
{
#ifdef _3DS
	char buffer[512];
	getcwd(buffer, 512);
	return std::string(buffer);
#else
	return boost::filesystem::current_path().string();
#endif // _3DS
}

//=============================================================================

bool Directory::setCurrentDirectory(const std::string & dir)
{
#ifdef _3DS
	return chdir(dir.c_str()) == 0;
#else
	boost::filesystem::current_path(dir);
	return true;
#endif // _3DS
}

//=============================================================================

bool Directory::exists(const std::string & dir)
{
#ifdef _3DS
	openSdArchive();

	Handle handle;
	Result ret;

	ret = FSUSER_OpenDirectory(nullptr, &handle,
		sdmc_archive, FS_makePath(PATH_CHAR, dir.c_str()));

	if (ret == 0)
	{
		FSDIR_Close(handle);
		closeSdArchive();
		return true;
	}

	closeSdArchive();

	return false;
#else
	if (!boost::filesystem::is_directory(dir))
		return false;
	return boost::filesystem::exists(dir);
#endif // _3DS
}

//=============================================================================

bool Directory::getFiles(const std::string & dir, std::vector<std::string>& outFiles)
{
	outFiles.clear();

#ifdef _3DS
	openSdArchive();

	Handle handle;
	Result ret;

	ret = FSUSER_OpenDirectory(nullptr, &handle,
		sdmc_archive, FS_makePath(PATH_CHAR, dir.c_str()));

	if (ret != 0)
	{
		closeSdArchive();
		return false;
	}

	FS_dirent entry;

	u32 entriesRead = 1;
	char filename[1024]{ 0 };

	for (;;)
	{
		entriesRead = 0;
		FSDIR_Read(handle, &entriesRead, 1, &entry);

		if (entriesRead != 0)
		{
			u32 len = 0;
			auto* p = entry.name;
			while (*p++) ++len;
			auto size = utf16_to_utf8((uint8_t*)filename, entry.name, len);
			filename[size] = '\0';
			outFiles.push_back(std::string(filename));
		}
		else
		{
			break;
		}
	}

	FSDIR_Close(handle);

	closeSdArchive();

	return true;
#else
	if (!boost::filesystem::is_directory(dir))
		return false;

	for (auto& entry : boost::make_iterator_range(
		boost::filesystem::directory_iterator(dir), {}))
	{
		if (boost::filesystem::is_regular_file(entry))
			outFiles.push_back(entry.path().string());
	}

	return true;

#endif // _3DS
}

//=============================================================================

bool Directory::copy(const std::string & src, const std::string & dst)
{
#ifdef _3DS
	return false;
#else
	boost::filesystem::copy_directory(src, dst);
	return true;
#endif // _3DS
}

//=============================================================================

bool Directory::move(const std::string & src, const std::string & dst)
{
	copy(src, dst);
	return deleteDirectory(src);
}

//=============================================================================

bool Directory::rename(const std::string & oldDir, const std::string & newDir)
{
#ifdef _3DS
	openSdArchive();

	Result ret = FSUSER_RenameDirectory(nullptr, sdmc_archive,
		FS_makePath(PATH_CHAR, oldDir.c_str()),
		sdmc_archive,
		FS_makePath(PATH_CHAR, newDir.c_str()));

	closeSdArchive();

	return ret == 0;
#else
	boost::filesystem::rename(oldDir, newDir);
	return true;
#endif // _3DS
}

//=============================================================================

#ifdef _3DS

void Directory::openSdArchive()
{
	sdmc_archive.id = ARCH_SDMC;
	sdmc_archive.lowPath = (FS_path) { PATH_EMPTY, 1, (u8*)"" };
	FSUSER_OpenArchive(nullptr, &sdmc_archive);
}

//=============================================================================

void Directory::closeSdArchive()
{
	FSUSER_CloseArchive(nullptr, &sdmc_archive);
}

#endif // _3DS

//=============================================================================

NS_KAIRY_END

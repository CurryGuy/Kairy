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

#include <Kairy/System/FileIo.h>
#ifdef _3DS
#include <unistd.h>
#endif // _3DS

NS_KAIRY_BEGIN

#ifdef _3DS
static FS_archive sdmc_archive;
#endif

//=============================================================================

void FileIo::openSdArchive()
{
#ifdef _3DS
    sdmc_archive.id = ARCH_SDMC;
    sdmc_archive.lowPath = (FS_path) { PATH_EMPTY, 1, (u8*)"" };
    FSUSER_OpenArchive(nullptr, &sdmc_archive);
#endif
}

void FileIo::closeSdArchive()
{
#ifdef _3DS
    FSUSER_CloseArchive(nullptr, &sdmc_archive);
#endif
}

//=============================================================================

bool FileIo::createDirectory(const std::string& dir)
{
    bool ret = false;

#ifdef _3DS
    openSdArchive();

    std::vector<std::string> levels;
    std::string::size_type index = 0;

    do
    {
        index = dir.find_first_of("\\/", index + 1);
        auto end = (index == std::string::npos) ? dir.length() : index;
        levels.push_back(dir.substr(0, end));
    }
    while(index != std::string::npos);

    for(auto& level : levels)
    {
        ret = FSUSER_CreateDirectory(nullptr, sdmc_archive, FS_makePath(PATH_CHAR, level.c_str())) == 0;
    }

    closeSdArchive();
#endif // _3DS

    return ret;
}

//=============================================================================

bool FileIo::deleteDirectory(const std::string& dir)
{
    bool ret = false;

#ifdef _3DS
    openSdArchive();

    ret = FSUSER_DeleteDirectoryRecursively(nullptr, sdmc_archive, FS_makePath(PATH_CHAR, dir.c_str())) == 0;

    closeSdArchive();
#endif // _3DS

    return ret;
}

//=============================================================================

bool FileIo::deleteFile(const std::string& file)
{
    bool ret = false;

#ifdef _3DS
    openSdArchive();

    ret = FSUSER_DeleteFile(nullptr, sdmc_archive, FS_makePath(PATH_CHAR, file.c_str())) == 0;

    closeSdArchive();
#endif // _3DS

    return ret;
}

//=============================================================================

bool FileIo::exists(const std::string &path)
{
#ifdef _3DS
    openSdArchive();

    Handle handle;
    Result ret;

    ret = FSUSER_OpenFile(NULL, &handle, sdmc_archive, FS_makePath(PATH_CHAR, path.c_str()), FS_OPEN_READ, FS_ATTRIBUTE_NONE);
    if(ret == 0)
    {
        ret = FSFILE_Close(handle);
        closeSdArchive();
        return ret == 0;
    }

    ret = FSUSER_OpenDirectory(NULL, &handle, sdmc_archive, FS_makePath(PATH_CHAR, path.c_str()));
    if(ret == 0)
    {
        ret = FSDIR_Close(handle);
        closeSdArchive();
        return ret == 0;
    }

    closeSdArchive();
#endif // _3DS

    return false;
}

//=============================================================================

std::string FileIo::getCurrentDirectory()
{
    char buffer[512];
#ifdef _3DS
    getcwd(buffer, 512);
#endif // _3DS
    return std::string(buffer);
}

//=============================================================================

NS_KAIRY_END

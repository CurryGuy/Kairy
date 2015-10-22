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

#include <Kairy/Graphics/ImageLoader.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "jpge.h"
#include "lodepng.h"

NS_KAIRY_BEGIN

//=============================================================================

byte* ImageLoader::LoadFromFile(const std::string& filename,
        int& outWidth, int& outHeight,
        PixelFormat format)
{
    int req_comp = format == PixelFormat::RGB8 ? STBI_rgb : STBI_rgb_alpha;
    return stbi_load(filename.c_str(), &outWidth, &outHeight, nullptr, req_comp);
}

//=============================================================================

byte* ImageLoader::LoadFromMemory(const byte* buffer,
        Uint32 buffer_size,
        int& outWidth, int& outHeight,
        PixelFormat format)
{
    int req_comp = format == PixelFormat::RGB8 ? STBI_rgb : STBI_rgb_alpha;
    return stbi_load_from_memory(buffer, buffer_size, &outWidth, &outHeight, nullptr, req_comp);
}

//=============================================================================

bool ImageLoader::SaveToFile(const std::string& filename,
        ImageFormat imageFormat,
        const byte* pixels,
        int width, int height,
        PixelFormat pixelFormat)
{
    if(!pixels || width == 0 || height == 0)
    {
        return false;
    }

    int n = pixelFormat == PixelFormat::RGB8 ? 3 : 4;

    switch(imageFormat)
    {
    case ImageFormat::Png:
        return lodepng_encode32_file(filename.c_str(), pixels, width, height) == 0;
    case ImageFormat::Bmp:
    {
        FILE* fp = fopen(filename.c_str(), "wb");
        if(!fp) return false;
        auto wb = [fp](byte b)
        {
            fwrite(&b, 1, 1, fp);
        };
        bool ret = WriteBMP(wb, pixels, width, height, n);
        fclose(fp);
        return ret;
    }
    case ImageFormat::Tga:
    {
        FILE* fp = fopen(filename.c_str(), "wb");
        if(!fp) return false;
        auto wb = [fp](byte b)
        {
            fwrite(&b, 1, 1, fp);
        };
        bool ret = WriteTGA(wb, pixels, width, height, n);
        fclose(fp);
        return ret;
    }
    case ImageFormat::Jpg:
        return jpge::compress_image_to_jpeg_file(filename.c_str(),
                width, height, n,
                pixels);
    default:
        return false;
    }

    return true;
}

//=============================================================================

bool ImageLoader::SaveToMemory(std::vector<byte>& outBuffer,
        ImageFormat imageFormat,
        const byte* pixels,
        int width, int height,
        PixelFormat pixelFormat)
{
    if(!pixels || width == 0 || height == 0)
    {
        return false;
    }

    int n = pixelFormat == PixelFormat::RGB8 ? 3 : 4;

    if(imageFormat == ImageFormat::Png)
    {
        size_t buffer_size = 0;
        unsigned char* buffer = nullptr;
        bool result;

        if(pixelFormat == PixelFormat::RGB8)
        {
            result = lodepng_encode24(&buffer, &buffer_size, pixels, width, height) != 0;
        }
        else
        {
            result = lodepng_encode32(&buffer, &buffer_size, pixels, width, height) != 0;
        }

        if(!result)
        {
            return false;
        }

        outBuffer = std::vector<byte>(buffer, buffer + buffer_size);

        free(buffer);

        return true;
    }
    else if(imageFormat == ImageFormat::Jpg)
    {
        outBuffer.resize(width * height * 3);
        int outSize = 0;
        if(!jpge::compress_image_to_jpeg_file_in_memory(
                &outBuffer.front(), outSize, width, height, n, pixels))
        {
            return false;
        }
        outBuffer.resize(outSize);
    }
    else if(imageFormat == ImageFormat::Tga)
    {
        outBuffer.clear();
        auto wb = [&outBuffer](byte b)
        {
            outBuffer.push_back(b);
        };
        return WriteTGA(wb, pixels, width, height, n);
    }
    else if(imageFormat == ImageFormat::Bmp)
    {
        outBuffer.clear();
        auto wb = [&outBuffer](byte b)
        {
            outBuffer.push_back(b);
        };
        return WriteBMP(wb, pixels, width, height, n);
    }

    return false;
}

//=============================================================================

bool ImageLoader::WriteTGA(const std::function<void(byte)>& writeByte,
        const byte* pixels,
        int width, int height, int depth)
{
    if(!pixels || width == 0 || height == 0 ||
            (depth != 3 && depth != 4) || !writeByte)
    {
        return false;
    }

    byte header[18] =
    {
        0,    // id
        0,    // map type
        2,    // image type
        0, 0, // map first
        0, 0, // map len
        0,    // map entry size
        0, 0, // x
        0, 0, // y
        byte(width), byte(width >> 8), // width
        byte(height), byte(height >> 8), // height
        byte(depth * 8),
        /*0x20*/0
    };

    byte footer[26] =
            "\0\0\0\0"
            "\0\0\0\0"
            "TRUEVISION-XFILE"
            ".";

    for(int i = 0; i < 18; ++i)
    {
        writeByte(header[i]);
    }

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            Uint32 src_index = x + (height - 1 - y) * width;

            writeByte(pixels[src_index * depth + 2]);
            writeByte(pixels[src_index * depth + 1]);
            writeByte(pixels[src_index * depth + 0]);
            if(depth == 4)
                writeByte(pixels[src_index * 4 + 3]);
        }
    }

    for(int i = 0; i < 26; ++i)
    {
        writeByte(footer[i]);
    }

    return true;
}

//=============================================================================

bool ImageLoader::WriteBMP(const std::function<void(byte)>& writeByte,
        const byte* pixels,
        int width, int height, int depth)
{
    if(!writeByte || !pixels || width == 0 || height == 0 ||
            (depth != 3 && depth != 4))
    {
        return false;
    }

    byte header_file[14] =
    {
        'B', 'M',
        0, 0, 0, 0,
        0, 0,
        0, 0,
        40 + 14, 0, 0, 0
    };

    byte header_info[40] =
    {
        40, 0, 0, 0,
        0, 0, 0, 0, // width
        0, 0, 0, 0, // height
        1, 0,
        24, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0x13, 0x0B, 0, 0,
        0x13, 0x0B, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    Uint32 padSize = (4 - (width * 3) % 4) % 4;
    Uint32 sizeData = width * height + height * padSize;
    Uint32 sizeAll = sizeData + 14 + 40;

    header_file[2] = sizeAll & 0xFF;
    header_file[3] = (sizeAll >>  8) & 0xFF;
    header_file[4] = (sizeAll >> 16) & 0xFF;
    header_file[5] = (sizeAll >> 24) & 0xFF;

    header_info[4] = width & 0xFF;
    header_info[5] = (width >> 8) & 0xFF;
    header_info[6] = (width >> 16) & 0xFF;
    header_info[7] = (width >> 24) & 0xFF;

    header_info[8] = height & 0xFF;
    header_info[9] = (height >> 8) & 0xFF;
    header_info[10] = (height >> 16) & 0xFF;
    header_info[11] = (height >> 24) & 0xFF;

    header_info[20] = sizeData & 0xFF;
    header_info[21] = (sizeData >> 8) & 0xFF;
    header_info[22] = (sizeData >> 16) & 0xFF;
    header_info[23] = (sizeData >> 24) & 0xFF;

    for(int i = 0; i < 14; ++i)
    {
        writeByte(header_file[i]);
    }

    for(int i = 0; i < 40; ++i)
    {
        writeByte(header_info[i]);
    }

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            Uint32 src_index = x + (height - 1 - y) * width;
            writeByte(pixels[src_index * depth + 2]);
            writeByte(pixels[src_index * depth + 1]);
            writeByte(pixels[src_index * depth + 0]);
        }
    }

    return true;
}

//=============================================================================

void ImageLoader::FreeImage(byte* pixels)
{
    stbi_image_free(pixels);
}

//=============================================================================

NS_KAIRY_END

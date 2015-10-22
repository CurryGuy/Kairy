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

#ifndef KAIRY_GRAPHICS_IMAGE_LOADER_H_INCLUDED
#define KAIRY_GRAPHICS_IMAGE_LOADER_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class ImageLoader
{
public:
    enum class PixelFormat
    {
        RGB8,
        RGBA8
    };

    static byte* LoadFromFile(const std::string& filename,
            int& outWidth, int& outHeight,
            PixelFormat format);

    static byte* LoadFromMemory(const byte* buffer,
            Uint32 buffer_size,
            int& outWidth, int& outHeight,
            PixelFormat format);

    static bool SaveToFile(const std::string& filename,
            ImageFormat imageFormat,
            const byte* pixels,
            int width, int height,
            PixelFormat pixelFormat);

    static bool SaveToMemory(std::vector<byte>& outBuffer,
            ImageFormat imageFormat,
            const byte* pixels,
            int width, int height,
            PixelFormat pixelFormat);

    static bool WriteTGA(const std::function<void(byte)>& writeByte,
            const byte* pixels,
            int width, int height, int depth);

    static bool WriteBMP(const std::function<void(byte)>& writeByte,
            const byte* pixels,
            int width, int height, int depth);

    static void FreeImage(byte* pixels);

private:
    ImageLoader() = default;
    ImageLoader(const ImageLoader&) = default;
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_IMAGE_LOADER_H_INCLUDED

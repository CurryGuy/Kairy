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

#include <Kairy/Graphics/Image.h>
#include <Kairy/Graphics/ImageLoader.h>
#include <Kairy/Graphics/Texture.h>
#include <Kairy/Ext/hqx/hqx.h>
#include <Kairy/Util/Radians.h>
#include <Kairy/Util/Zip.h>

NS_KAIRY_BEGIN

//=============================================================================

Image::Image(void)
    :_width(0)
    ,_height(0)
{
}

//=============================================================================

Image::Image(const std::string& filename)
    : Image()
{
    load(filename);
}

//=============================================================================

Image::Image(const std::string& filename, const Rect& region)
	: Image()
{
	load(filename);
	crop(region);
}

//=============================================================================

Image::Image(const std::string & zipfile, const std::string & filename)
	: Image()
{
	load(zipfile, filename);
}

//=============================================================================

Image::Image(const byte* buffer, Uint32 bufferSize)
    : Image()
{
    load(buffer, bufferSize);
}

//=============================================================================

Image::Image(int width, int height, const Color& color)
    : Image()
{
    create(width, height, color);
}

//=============================================================================

Image::Image(const byte* pixels, int width, int height)
    : Image()
{
    load(pixels, width, height);
}

//=============================================================================

Image::Image(const Image& other)
    : Image()
{
    _width = other._width;
    _height = other._height;
    _pixels.resize(other._width * other._height);
    std::copy(other._pixels.begin(), other._pixels.end(), _pixels.begin());
}

//=============================================================================

bool Image::load(const std::string& filename)
{
    int width = 0;
    int height = 0;
    byte* pixels = ImageLoader::LoadFromFile(filename, width, height,
            PixelFormat::RGBA8);

    bool ret = load(pixels, width, height);
    ImageLoader::FreeImage(pixels);

    return ret;
}

//=============================================================================

bool Image::load(const std::string & zipfile, const std::string & filename)
{
	std::vector<byte> data;

	util::GetZipFileData(zipfile, filename, data);

	return load(data.data(), data.size());
}

//=============================================================================

bool Image::load(const byte* buffer, Uint32 bufferSize)
{
    int width = 0;
    int height = 0;
    byte* pixels = ImageLoader::LoadFromMemory(buffer, bufferSize,
            width, height, PixelFormat::RGBA8);

    bool ret = load(pixels, width, height);
    ImageLoader::FreeImage(pixels);

    return ret;
}

//=============================================================================

bool Image::load(const byte* pixels, int width, int height)
{
    if(!pixels || width == 0 || height == 0)
    {
        return false;
    }

    Uint32 pixelsCount = width * height;

    _pixels.resize(pixelsCount);

    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            int index = x + y * width;

            _pixels[index].r = pixels[index * 4 + 0];
            _pixels[index].g = pixels[index * 4 + 1];
            _pixels[index].b = pixels[index * 4 + 2];
            _pixels[index].a = pixels[index * 4 + 3];
        }
    }

    _width = width;
    _height = height;

    return true;
}

//=============================================================================

bool Image::create(int width, int height, const Color& color)
{
    _pixels.resize(width * height, color);
    _width = width;
    _height = height;
    return true;
}

//=============================================================================

bool Image::save(const std::string& filename, const Color& trans)
{
    if(filename.length() < 2)
    {
        return false;
    }

    auto dotIndex = filename.find_last_of('.');
    if(dotIndex == std::string::npos)
        dotIndex = 0;
    std::string ext = filename.substr(dotIndex + 1, filename.length() - 1);
    ImageFormat format;

    if(ext == "bmp")
    {
        format = ImageFormat::Bmp;
    }
    else if(ext == "jpg")
    {
        format = ImageFormat::Jpg;
    }
    else if(ext == "tga")
    {
        format = ImageFormat::Tga;
    }
    else
    {
        format = ImageFormat::Png;
    }

    return save(filename, format, trans);
}

//=============================================================================

bool Image::save(const std::string& filename, ImageFormat format, const Color& trans)
{
    std::vector<Color> pixels;

    if(!getPixels(pixels))
    {
        return false;
    }

    if(format == ImageFormat::Bmp ||
            format == ImageFormat::Jpg)
    {
        for(auto& pixel : pixels)
        {
            if(pixel.a != Color::OPAQUE)
                pixel = Color(trans, Color::OPAQUE);
        }
    }

    return ImageLoader::SaveToFile(filename, format,
            (byte*)&pixels.front(),
            _width, _height,
            PixelFormat::RGBA8);
}

//=============================================================================

bool Image::save(std::vector<byte>& outBuffer, ImageFormat format, const Color& trans)
{
    std::vector<Color> pixels;

    if(!getPixels(pixels))
    {
        return false;
    }

    if(format == ImageFormat::Bmp ||
            format == ImageFormat::Jpg)
    {
        for(auto& pixel : pixels)
        {
            if(pixel.a != Color::OPAQUE)
                pixel = Color(trans, Color::OPAQUE);
        }
    }

    return ImageLoader::SaveToMemory(outBuffer, format,
            (byte*)&pixels.front(),
            _width, _height,
            PixelFormat::RGBA8);
}

//=============================================================================

bool Image::toTexture(Texture& texture) const
{
    return texture.load((byte*)&_pixels.front(), _width, _height);
}

//=============================================================================

void Image::setPixel(int x, int y, const Color& pixel)
{
    if(x >= 0 && y >= 0 && x < _width && y < _height)
    {
        _pixels[x + y * _width] = pixel;
    }
}

//=============================================================================

Color Image::getPixel(int x, int y) const
{
    if(x >= 0 && y >= 0 && x < _width && y < _height)
    {
        return _pixels[x + y * _width];
    }

    return Color::Transparent;
}

//=============================================================================

void Image::clear(const Color& color)
{
    for(std::size_t i = 0; i < _pixels.size(); ++i)
    {
        _pixels[i] = color;
    }
}

//=============================================================================

bool Image::getPixels(std::vector<Color>& outPixels)
{
    outPixels.resize(_pixels.size());

    for(std::size_t i = 0; i < _pixels.size(); ++i)
    {
        outPixels[i] = _pixels[i];
    }

    return true;
}

//=============================================================================

bool Image::getPixels(std::vector<Color>& outPixels, const Rect& region)
{
    if(_width == 0 || _height == 0 ||
            region.getLeft() < 0 || region.getTop() < 0 ||
            region.getRight() > _width || region.getBottom() > _height)
    {
        return false;
    }

    int left = (int)region.getLeft();
    int top = (int)region.getTop();
    int right = (int)region.getRight();
    int bottom = (int)region.getBottom();

    outPixels.clear();

    for(int y = top; y < bottom; ++y)
    {
        for(int x = left; x < right; ++x)
        {
            outPixels.push_back(getPixel(x, y));
        }
    }

    return true;
}

//=============================================================================

bool Image::crop(const Rect& region)
{
    std::vector<Color> pixels;
    if(!getPixels(pixels, region))
    {
        return false;
    }

    _width = (int)region.width;
    _height = (int)region.height;
    _pixels.resize(pixels.size());
    std::copy(pixels.begin(), pixels.end(), _pixels.begin());

    return true;
}

//=============================================================================

void Image::drawLine(int startX, int startY, int endX, int endY, const Color& color)
{
    const bool steep = (std::abs(endY - startY) > std::abs(endX - startX));

    if(steep)
    {
        std::swap(startX, startY);
        std::swap(endX, endY);
    }

    if(startX > endX)
    {
        std::swap(startX, endX);
        std::swap(startY, endY);
    }

    const int dx = endX - startX;
    const int dy = std::abs(endY - startY);

    int error = dx / 2;
    const int ystep = (startY < endY) ? 1 : -1;
    int y = startY;

    const int maxX = endX;

    for(int x = startX; x < maxX; ++x)
    {
        if(steep)
        {
            setPixel(y, x, color);
        }
        else
        {
            setPixel(x, y, color);
        }

        error -= dy;

        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}

//=============================================================================

void Image::drawRect(const Rect& rect, const Color& color)
{
	int left = (int)rect.getLeft();
	int top = (int)rect.getTop();
	int right = (int)rect.getRight();
	int bottom = (int)rect.getBottom();

    drawLine(left, top, right - 1, top, color);
    drawLine(right - 1, top, right - 1, bottom - 1, color);
    drawLine(left, bottom - 1, right - 1, bottom - 1, color);
    drawLine(left, top, left, bottom - 1, color);
}

//=============================================================================

void Image::fillRect(const Rect& rect, const Color& color)
{
    int startX = (int)rect.getLeft();
    int startY = (int)rect.getTop();
    int endX = (int)rect.getRight();
    int endY = (int)rect.getBottom();

    for(int x = startX; x < endX; ++x)
    {
        for(int y = startY; y < endY; ++y)
        {
            setPixel(x, y, color);
        }
    }
}

//=============================================================================

void Image::drawCirlce(int x, int y, int radius, const Color& color)
{
	int sx = radius;
	int sy = 0;
	int decisionOver2 = 1 - x;

	while (sy <= sx)
	{
		setPixel(sx + x, sy + x, color);
		setPixel(sy + x, sx + y, color);
		setPixel(-sx + x, sy + y, color);
		setPixel(-sy + x, sx + y, color);
		setPixel(-sx + x, -sy + y, color);
		setPixel(-sy + x, -sx + y, color);
		setPixel(sx + x, -sy + y, color);
		setPixel(sy + x, -sx + y, color);

		++sy;

		if (decisionOver2 <= 0)
		{
			decisionOver2 += 2 * sy + 1;
		}
		else
		{
			--sx;
			decisionOver2 += 2 * (sy - sx) + 1;
		}
	}
}

//=============================================================================

void Image::fillCircle(int x, int y, int radius, const Color& color)
{
	int radius2 = radius * radius;
	int area = radius2 << 2;
	int rr = radius << 1;

	for (int i = 0; i < area; ++i)
	{
		int tx = (i % rr) - radius;
		int ty = (i / rr) - radius;

		if (tx * tx + ty * ty <= radius2)
		{
			setPixel(x + tx, y + ty, color);
		}
	}
}

//=============================================================================

bool Image::scaleHq2x(void)
{
	if (_pixels.size() == 0)
	{
		return false;
	}

	int newWidth = _width * 2;
	int newHeight = _height * 2;

	std::vector<Color> newPixels(newWidth * newHeight);

	hq2x_32((uint32_t*)&_pixels.front(), (uint32_t*)&newPixels.front(), _width, _height);

	_pixels.resize(newWidth * newHeight);
	std::copy(newPixels.begin(), newPixels.end(), _pixels.begin());
	_width = newWidth;
	_height = newHeight;

    return true;
}

//=============================================================================

bool Image::scaleHq3x(void)
{
	if (_pixels.size() == 0)
	{
		return false;
	}

	int newWidth = _width * 3;
	int newHeight = _height * 3;

	std::vector<Color> newPixels(newWidth * newHeight);

	hq3x_32((uint32_t*)&_pixels.front(), (uint32_t*)&newPixels.front(), _width, _height);

	_pixels.resize(newWidth * newHeight);
	std::copy(newPixels.begin(), newPixels.end(), _pixels.begin());
	_width = newWidth;
	_height = newHeight;

    return true;
}

//=============================================================================

bool Image::scaleHq4x(void)
{
	if (_pixels.size() == 0)
	{
		return false;
	}

	int newWidth = _width * 4;
	int newHeight = _height * 4;

	std::vector<Color> newPixels(newWidth * newHeight);

	hq4x_32((uint32_t*)&_pixels.front(), (uint32_t*)&newPixels.front(), _width, _height);

	_pixels.resize(newWidth * newHeight);
	std::copy(newPixels.begin(), newPixels.end(), _pixels.begin());
	_width = newWidth;
	_height = newHeight;

    return true;
}

//=============================================================================

bool Image::scaleNearest(int newWidth, int newHeight)
{
    if(newWidth == 0 || newHeight == 0 || _pixels.size() == 0)
    {
        return false;
    }

    if(newWidth == _width && newHeight == _height)
    {
        return true;
    }

    std::vector<Color> newPixels(newWidth * newHeight);

    float x_ratio = _width / (float)newWidth;
    float y_ratio = _height / (float)newHeight;
    float px, py;

    for(int y = 0; y < newHeight; ++y)
    {
        for(int x = 0; x < newWidth; ++x)
        {
            px = std::floor(x * x_ratio);
            py = std::floor(y * y_ratio);

            newPixels[x + y * newWidth] = _pixels[int(px + py * _width)];
        }
    }

    _pixels.resize(newWidth * newHeight);
    std::copy(newPixels.begin(), newPixels.end(), _pixels.begin());

    _width = newWidth;
    _height = newHeight;

    return true;
}

//=============================================================================

bool Image::scaleBilinear(int newWidth, int newHeight)
{
	if (newWidth == _width && newHeight == _height)
	{
		return true;
	}

	if (_pixels.size() == 0)
	{
		return false;
	}

	std::vector<Color> newPixels(newWidth * newHeight);

	float x_ratio = ((float)(_width - 1) / newWidth);
	float y_ratio = ((float)(_height - 1) / newHeight);
	Color a, b, c, d;
	int x, y;
	float w, h;

	for (int i = 0; i < newWidth; ++i)
	{
		for (int j = 0; j < newHeight; ++j)
		{
			x = (int)(x_ratio * i);
			y = (int)(y_ratio * j);

			w = (x_ratio * i) - x;
			h = (y_ratio * j) - y;

			a = getPixel(x, y);
			b = getPixel(x + 1, y);
			c = getPixel(x, y + 1);
			d = getPixel(x + 1, y + 1);

			byte cr = (byte)(a.r * (1 - w) * (1 - h) + b.r * (w)* (1 - h) + c.r * (h)* (1 - w) + d.r * (w * h));
			byte cg = (byte)(a.g * (1 - w) * (1 - h) + b.g * (w)* (1 - h) + c.g * (h)* (1 - w) + d.g * (w * h));
			byte cb = (byte)(a.b * (1 - w) * (1 - h) + b.b * (w)* (1 - h) + c.b * (h)* (1 - w) + d.b * (w * h));

			newPixels[i + j * newWidth] = Color(cr, cg, cb);
		}
	}

	_pixels.resize(newWidth * newHeight);
	std::copy(newPixels.begin(), newPixels.end(), _pixels.begin());
	_width = newWidth;
	_height = newHeight;

	return true;
}

//=============================================================================

bool Image::flipX()
{
	for (int x = 0; x < _width; ++x)
	{
		for (int y = 0; y < _height/2; ++y)
		{
			std::swap(_pixels[x + y * _width], _pixels[x + (_height - y - 1) * _width]);
		}
	}

	return true;
}

//=============================================================================

bool Image::flipY()
{
	for (int x = 0; x < _width / 2; ++x)
	{
		for (int y = 0; y < _height; ++y)
		{
			std::swap(_pixels[x + y * _width], _pixels[_width - x - 1 + y * _width]);
		}
	}

	return true;
}

//=============================================================================

bool Image::rotate(float angle)
{
	if (_width == 0 || _height == 0)
	{
		return false;
	}

	float radians = util::deg_to_rad(angle);
	float cosine = std::cos(radians);
	float sine = std::sin(radians);

	float x1 = -_height * sine;
	float y1 = _height * cosine;
	float x2 = _width * cosine - _height * sine;
	float y2 = _height * cosine + _width * sine;
	float x3 = _width * cosine;
	float y3 = _width * sine;

	float minX = std::min({ 0.0f, x1, x2, x3 });
	float minY = std::min({ 0.0f, y1, y2, y3 });
	float maxX = std::max({ x1, x2, x3 });
	float maxY = std::max({ x1, y2, y3 });

	int newWidth = (int)std::ceil(std::fabs(maxX) - minX);
	int newHeight = (int)std::ceil(std::fabs(maxY) - minY);

	std::vector<Color> newPixels(newWidth * newHeight);

	for (int x = 0; x < newWidth; ++x)
	{
		for (int y = 0; y < newHeight; ++y)
		{
			int srcX = (int)((x + minX) * cosine + (y + minY) * sine);
			int srcY = (int)((y + minY) * cosine - (x + minX) * sine);

			newPixels[x + y * newWidth] = getPixel(srcX, srcY);
		}
	}

	_pixels.resize(newPixels.size());
	std::copy(newPixels.begin(), newPixels.end(), _pixels.begin());
	_width = newWidth;
	_height = newHeight;

	return true;
}

//=============================================================================

void Image::invertColors()
{
	for (auto& pixel : _pixels)
	{
		pixel = Color(255 - pixel.r, 255 - pixel.g, 255 - pixel.b, pixel.a);
	}
}

//=============================================================================

void Image::drawImage(int x, int y, const Image& image)
{
	drawImage(x, y, image, Rect(0, 0, (float)image.getWidth(), (float)image.getHeight()));
}

//=============================================================================

void Image::drawImage(int x, int y, const Image& image, const Rect& source)
{
	int startX = (int)source.getLeft();
	int startY = (int)source.getTop();
	int endX = (int)source.getRight();
	int endY = (int)source.getBottom();
	Color pixel, result;

	for (int i = startX; i < endX; ++i)
	{
		for (int j = startY; j < endY; ++j)
		{
			pixel = image.getPixel(i, j);
			result = pixel.blend(getPixel(x + i, y + j));
			setPixel(x + i, y + j, result);
		}
	}
}

//=============================================================================

bool Image::equals(const Image& other) const
{
    if(_pixels.size() != other._pixels.size())
    {
        return false;
    }

    for(std::size_t i = 0; i < _pixels.size(); ++i)
    {
        if(_pixels[i] != other._pixels[i])
        {
            return false;
        }
    }

    return true;
}

//=============================================================================

bool Image::operator==(const Image& other) const
{
    return equals(other);
}

//=============================================================================

bool Image::operator!=(const Image& other) const
{
    return equals(other);
}

//=============================================================================

NS_KAIRY_END

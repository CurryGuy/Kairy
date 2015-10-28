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

#ifndef KAIRY_GRAPHICS_IMAGE_H_INCLUDED
#define KAIRY_GRAPHICS_IMAGE_H_INCLUDED

#include "Color.h"
#include <Kairy/Math/Rect.h>

NS_KAIRY_BEGIN

class Texture;

class Image
{
public:
	Image(void);

	Image(const std::string& filename);

	Image(const std::string& filename, const Rect& region);

	Image(const std::string& zipfile, const std::string& filename);

	Image(const byte* buffer, Uint32 bufferSize);

	Image(int width, int height, const Color& color = Color::Transparent);

	Image(const byte* pixels, int width, int height);

	Image(const Image& other);

	bool load(const std::string& filename);

	bool load(const std::string& zipfile, const std::string& filename);

	bool load(const byte* buffer, Uint32 bufferSize);

	bool load(const byte* pixels, int width, int height);

	bool create(int width, int height, const Color& color = Color::Transparent);

	bool save(const std::string& filename, const Color& trans = Color::Magenta);

	bool save(const std::string& filename, ImageFormat format,
		const Color& trans = Color::Magenta);

	bool save(std::vector<byte>& outBuffer, ImageFormat format = ImageFormat::Png,
		const Color& trans = Color::Magenta);

	bool toTexture(Texture& texture) const;

	inline int getWidth() const { return _width; }

	inline int getHeight() const { return _height; }

	void setPixel(int x, int y, const Color& pixel);

	Color getPixel(int x, int y) const;

	void clear(const Color& color = Color::Transparent);

	bool getPixels(std::vector<Color>& outPixels);

	bool getPixels(std::vector<Color>& outPixels, const Rect& region);

	bool crop(const Rect& region);

	void drawLine(int startX, int startY, int endX, int endY, const Color& color);

	void drawRect(const Rect& rect, const Color& color);

	void fillRect(const Rect& rect, const Color& color);

	void drawCirlce(int x, int y, int radius, const Color& color);

	void fillCircle(int x, int y, int radius, const Color& color);

	bool scaleHq2x(void);

	bool scaleHq3x(void);

	bool scaleHq4x(void);

	bool scaleNearest(int newWidth, int newHeight);

	bool scaleBilinear(int newWidth, int newHeight);

	bool flipX();

	bool flipY();

	bool rotate(float angle);

	void invertColors();

	void drawImage(int x, int y, const Image& image);

	void drawImage(int x, int y, const Image& image, const Rect& source);

	bool equals(const Image& other) const;

	bool operator ==(const Image& other) const;
	bool operator !=(const Image& other) const;

private:
	std::vector<Color> _pixels;
	int _width;
	int _height;
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_IMAGE_H_INCLUDED

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

#include <Kairy/Graphics/Texture.h>
#include <Kairy/Graphics/ImageLoader.h>
#include <Kairy/System/ResourceManager.h>
#include <Kairy/Util/Npot.h>
#include <Kairy/Util/Clamp.h>
#include <Kairy/Util/Zip.h>
#include <Kairy/Util/ToString.h>
#include <Kairy/Math/Rect.h>
#include <Kairy/Ext/hqx/hqx.h>
#include <Kairy/Graphics/RenderDevice.h>

NS_KAIRY_BEGIN

//=============================================================================

#ifdef _3DS
// Grabbed from CTRCommon
inline u32 gpuTextureIndex(u32 x, u32 y, u32 w, u32 h)
{
	return (((y >> 3) * (w >> 3) + (x >> 3)) << 6) + ((x & 1) |
		((y & 1) << 1) | ((x & 2) << 1) | ((y & 2) << 2) |
		((x & 4) << 2) | ((y & 4) << 3));
}
#endif // _3DS

//=============================================================================

Texture* Texture::s_bindedTexture = nullptr;
bool Texture::s_defaultAaEnabled = true;
Uint32 Texture::s_memResCounter = 0;

//=============================================================================

static const std::string kMemResPrefix = "mem_";

//=============================================================================

void Texture::deleteResourceData(ResourceData & data)
{
#ifdef _3DS
	if (data.pixels)
	{
		if (data.location == Location::Ram)
			linearFree(data.pixels);
		else
			vramFree(data.pixels);
	}
#else
	if (data.pixels)
		delete[] data.pixels;
	glDeleteTextures(1, &data.id);
	data.id = 0;
#endif // _3DS
	data.pixels = nullptr;

	if (data.memory)
	{
		s_memResCounter--;
	}
}

//=============================================================================

ResourceManager<Texture::ResourceData>
Texture::s_resourceManager(Texture::deleteResourceData);

//=============================================================================

bool Texture::preload(const std::string & filename, Location location)
{
	int width = 0;
	int height = 0;
	byte* loadedPixels = ImageLoader::LoadFromFile(filename, width, height, ImageLoader::PixelFormat::RGBA8);

	if (!loadedPixels || width == 0 || height == 0)
	{
		return false;
	}

	Uint32 pixelsSize = width * height * 4;

	byte* pixels = nullptr;

#ifdef _3DS
	if (location == Location::Ram)
		pixels = (byte*)linearMemAlign(pixelsSize, 0x80);
	else
		pixels = (byte*)vramMemAlign(pixelsSize, 0x80);
#else
	pixels = new byte[pixelsSize];
#endif // _3DS

	if (!pixels)
	{
		ImageLoader::FreeImage(loadedPixels);
		return false;
	}

	memcpy(pixels, loadedPixels, pixelsSize);
	ImageLoader::FreeImage(loadedPixels);

	ResourceData data;
	
	data.width = width;
	data.height = height;
	data.location = location;
	data.pixels = pixels;

#ifndef _3DS
	glGenTextures(1, &data.id);
#endif // _3DS

	std::string resourceName = filename + (location == Location::Ram ? 'r' : 'v');

	s_resourceManager.preloadResource(resourceName, data);

	return true;
}

//=============================================================================

bool Texture::unloadPreloaded(const std::string & filename, Location location)
{
	std::string resourceName = filename + (location == Location::Ram ? 'r' : 'v');
	return s_resourceManager.unloadPreloaded(resourceName);
}

//=============================================================================

Texture::Texture(void)
	:_location(Location::Ram)
	, _width(0)
	, _height(0)
	, _potWidth(0)
	, _potHeight(0)
	, _aaEnabled(s_defaultAaEnabled)
	, _repeated(false)
	, _paramsUpdated(true)
	, _pixels(nullptr)
#ifndef _3DS
	, _id(0)
	, _pixelsUpdated(true)
#endif // _3DS
{
}

//=============================================================================

Texture::Texture(const std::string& filename, Location location)
	: Texture()
{
	load(filename, location);
}

//=============================================================================

Texture::Texture(const std::string & zipfile, const std::string & filename,
	Location location)
	: Texture()
{
	load(zipfile, filename, location);
}

//=============================================================================

Texture::Texture(const byte* buffer, Uint32 buffer_size, Location location)
	:Texture()
{
	load(buffer, buffer_size, location);
}

//=============================================================================

Texture::Texture(const byte* pixels, int width, int height, Location location)
	:Texture()
{
	load(pixels, width, height, location);
}

//=============================================================================

Texture::Texture(int width, int height, const Color& color, Location location)
{
	create(width, height, color, location);
}

//=============================================================================

Texture::Texture(const Texture& other)
	: Texture()
{
	auto resName = other._resourceName;

	if (s_resourceManager.hasResource(resName))
	{
		ResourceData data;
		
		if (s_resourceManager.loadResource(resName, data))
		{
			loadResourceData(data);
			_resourceName = resName;
		}
	}
}

//=============================================================================

Texture::~Texture(void)
{
	unload();

	if (s_bindedTexture == this)
	{
		s_bindedTexture = nullptr;
	}
}

//=============================================================================

bool Texture::load(const std::string& filename, Location location)
{
	unload();

	std::string resourceName = filename + (location == Location::Ram ? 'r' : 'v');
	ResourceData data;

	if (s_resourceManager.hasResource(filename))
	{	
		s_resourceManager.loadResource(resourceName, data);

		loadResourceData(data);

		_resourceName = resourceName;

		return true;
	}

	int width = 0;
	int height = 0;
	byte* pixels = ImageLoader::LoadFromFile(filename, width, height,
		ImageLoader::PixelFormat::RGBA8);
	bool ret = loadPixels(pixels, width, height, location);
	ImageLoader::FreeImage(pixels);

	if (ret)
	{
		data = createResourceData();
		s_resourceManager.addResource(resourceName, data);
		_resourceName = resourceName;
	}

	return ret;
}

//=============================================================================

bool Texture::load(const std::string & zipfile, const std::string & filename, Location location)
{
	std::vector<byte> data;
	
	if (!util::GetZipFileData(zipfile, filename, data))
	{
		return false;
	}

	return load(data.data(), data.size(), location);
}

//=============================================================================

bool Texture::load(const byte* buffer, Uint32 buffer_size, Location location)
{
	int width, height;
	byte* pixels = ImageLoader::LoadFromMemory(buffer, buffer_size, width,
		height, ImageLoader::PixelFormat::RGBA8);

	bool ret = load(pixels, width, height, location);
	ImageLoader::FreeImage(pixels);

	return ret;
}

//=============================================================================

bool Texture::load(const byte* pixels, int width, int height, Location location)
{
	if (!pixels || width == 0 || height == 0 ||
		!RenderDevice::getInstance()->isInitialized())
	{
		return false;
	}

	bool ret = loadPixels(pixels, width, height, location);

	if (ret)
	{
		auto data = createResourceData();
		data.memory = true;
		setMemResourceName();
		s_resourceManager.addResource(_resourceName, data);
	}

	return ret;
}

//=============================================================================

bool Texture::create(int width, int height, const Color& color, Location location)
{
	std::vector<Color> pixels(width * height, color);
	return load((byte*)&pixels.front(), width, height, location);
}

//=============================================================================

bool Texture::getPixels(std::vector<Color>& outPixels) const
{
	if (!_pixels || _width == 0 || _height == 0)
	{
		return false;
	}

	outPixels.resize(_width * _height);

	for (int y = 0; y < _height; ++y)
	{
		for (int x = 0; x < _width; ++x)
		{
			outPixels[x + y * _width] = getPixel(x, y);
		}
	}

	return true;
}

//=============================================================================

bool Texture::getPixels(std::vector<Color>& outPixels, const Rect& region) const
{
	if (!_pixels || _width == 0 || _height == 0 ||
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

	for (int y = top; y < bottom; ++y)
	{
		for (int x = left; x < right; ++x)
		{
			outPixels.push_back(getPixel(x, y));
		}
	}

	return true;
}

//=============================================================================

bool Texture::save(const std::string& filename, ImageFormat format, const Color& trans) const
{
	std::vector<Color> pixels;

	if (!getPixels(pixels))
	{
		return false;
	}

	if (format == ImageFormat::Bmp ||
		format == ImageFormat::Jpg)
	{
		for (auto& pixel : pixels)
		{
			if (pixel.a != Color::OPAQUE)
				pixel = Color(trans, Color::OPAQUE);
		}
	}

	return ImageLoader::SaveToFile(filename, format,
		(byte*)&pixels.front(),
		_width, _height,
		ImageLoader::PixelFormat::RGBA8);
}

//=============================================================================

bool Texture::save(const std::string& filename, const Color& trans) const
{
	if (filename.length() < 2)
	{
		return false;
	}

	auto dotIndex = filename.find_last_of('.');
	if (dotIndex == std::string::npos)
		dotIndex = 0;
	std::string ext = filename.substr(dotIndex + 1, filename.length() - 1);
	ImageFormat format;

	if (ext == "bmp")
	{
		format = ImageFormat::Bmp;
	}
	else if (ext == "jpg")
	{
		format = ImageFormat::Jpg;
	}
	else if (ext == "tga")
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

bool Texture::save(std::vector<byte>& outBuffer,
	ImageFormat format,
	const Color& trans) const
{
	std::vector<Color> pixels;

	if (!getPixels(pixels))
	{
		return false;
	}

	if (format == ImageFormat::Bmp ||
		format == ImageFormat::Jpg)
	{
		for (auto& pixel : pixels)
		{
			if (pixel.a != Color::OPAQUE)
				pixel = Color(trans, Color::OPAQUE);
		}
	}

	return ImageLoader::SaveToMemory(outBuffer, format,
		(byte*)&pixels.front(),
		_width, _height,
		ImageLoader::PixelFormat::RGBA8);
}

//=============================================================================

void Texture::setPixel(int x, int y, const Color& color)
{
	if (x >= 0 && y >= 0 && x < _width && y < _height)
	{
		Uint32 index;
#ifdef _3DS
		index = gpuTextureIndex(x, y, _potWidth, _potHeight);
#else
		index = x + y * _potWidth;
		_pixelsUpdated = true;
#endif // _3DS

		_pixels[index * 4 + 3] = color.r;
		_pixels[index * 4 + 2] = color.g;
		_pixels[index * 4 + 1] = color.b;
		_pixels[index * 4 + 0] = color.a;
	}
}

//=============================================================================

Color Texture::getPixel(int x, int y) const
{
	Color color;

	if (x >= 0 && y >= 0 && x < _width && y < _height)
	{
		Uint32 index;

#ifdef _3DS
		index = gpuTextureIndex(x, y, _potWidth, _potHeight);
#else
		index = x + y * _potWidth;
#endif // _3DS

		color.r = _pixels[index * 4 + 0];
		color.g = _pixels[index * 4 + 1];
		color.b = _pixels[index * 4 + 2];
		color.a = _pixels[index * 4 + 3];
	}

	return color;
}

//=============================================================================

void Texture::clear(const Color& color)
{
	for (int x = 0; x < _width; ++x)
	{
		for (int y = 0; y < _height; ++y)
		{
			setPixel(x, y, color);
		}
	}
}

//=============================================================================

bool Texture::scaleHq2x(void)
{
	std::vector<Color> pixels;
	if (!getPixels(pixels))
	{
		return false;
	}

	int width = _width;
	int height = _height;
	int newWidth = width * 2;
	int newHeight = height * 2;
	Location location = _location;

	unload();

	std::vector<Color> outPixels(newWidth * newHeight);

	hq2x_32((uint32_t*)&pixels.front(), (uint32_t*)&outPixels.front(), width, height);

	pixels.clear();

	return load((byte*)&outPixels.front(), newWidth, newHeight, location);
}

//=============================================================================

bool Texture::scaleHq3x(void)
{
	std::vector<Color> pixels;
	if (!getPixels(pixels))
	{
		return false;
	}

	int width = _width;
	int height = _height;
	int newWidth = width * 3;
	int newHeight = height * 3;
	Location location = _location;

	unload();

	std::vector<Color> outPixels(newWidth * newHeight);

	hq3x_32((uint32_t*)&pixels.front(), (uint32_t*)&outPixels.front(), width, height);

	pixels.clear();

	return load((byte*)&outPixels.front(), newWidth, newHeight, location);
}

//=============================================================================

bool Texture::scaleHq4x(void)
{
	std::vector<Color> pixels;
	if (!getPixels(pixels))
	{
		return false;
	}

	int width = _width;
	int height = _height;
	int newWidth = width * 4;
	int newHeight = height * 4;
	Location location = _location;

	unload();

	std::vector<Color> outPixels(newWidth * newHeight);

	hq4x_32((uint32_t*)&pixels.front(), (uint32_t*)&outPixels.front(), width, height);

	pixels.clear();

	return load((byte*)&outPixels.front(), newWidth, newHeight, location);
}

//=============================================================================

void Texture::enableAntialiasing(bool enable)
{
	_aaEnabled = enable;
	_paramsUpdated = true;
}

//=============================================================================

void Texture::setRepeated(bool repeated)
{
	_repeated = repeated;
	_paramsUpdated = true;
}

//=============================================================================

bool Texture::changeLocation(Location newLocation)
{
#ifdef _3DS
	if (newLocation != _location)
	{
		byte* newPixels = nullptr;
		Uint32 pixelsSize = _potWidth * _potHeight * 4;

		if (newLocation == Location::Ram &&
			linearSpaceFree() > pixelsSize)
		{
			newPixels = (byte*)linearMemAlign(pixelsSize, 0x80);
		}
		else if (vramSpaceFree() > pixelsSize)
		{
			newPixels = (byte*)vramMemAlign(pixelsSize, 0x80);
		}

		if (!newPixels)
		{
			return false;
		}

		memcpy(newPixels, _pixels, pixelsSize);

		if (_location == Location::Ram)
		{
			linearFree(_pixels);
		}
		else
		{
			vramFree(_pixels);
		}

		_pixels = newPixels;
		_location = newLocation;
	}
#endif // _3DS

	return true;
}

//=============================================================================

void Texture::unload()
{
	if (_pixels)
	{
		s_resourceManager.removeResource(_resourceName);

		_pixels = nullptr;
		_location = Location::Ram;
		_width = 0;
		_height = 0;
		_potWidth = 0;
		_potHeight = 0;
		_resourceName = "";
	}
}

//=============================================================================

void Texture::bind(int unit)
{
	if (_pixels && _width > 0 && _height > 0 && unit >= 0 && unit < 3)
	{
#ifdef _3DS
		if (s_bindedTexture == nullptr || s_bindedTexture->_pixels != _pixels || _paramsUpdated)
		{
			GPU_TEXUNIT tex_unit = GPU_TEXUNIT(1 << unit);

			u32 filter = _aaEnabled ? GPU_LINEAR : GPU_NEAREST;
			u32 repeat = _repeated ? GPU_REPEAT : GPU_CLAMP_TO_BORDER;
			u32 params =
				GPU_TEXTURE_MIN_FILTER(filter) |
				GPU_TEXTURE_MAG_FILTER(filter) |
				GPU_TEXTURE_WRAP_S(repeat) |
				GPU_TEXTURE_WRAP_T(repeat);

			GPU_SetTextureEnable(tex_unit);
			GPU_SetTexture(tex_unit,
				(u32*)osConvertVirtToPhys((u32)_pixels),
				_potWidth, _potHeight,
				params,
				GPU_RGBA8);

			_paramsUpdated = false;
		}
#else
		if (s_bindedTexture == nullptr || s_bindedTexture->_pixels != _pixels ||
			_paramsUpdated || _pixelsUpdated)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, _id);

			if (_pixelsUpdated)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _potWidth, _potHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);
				_pixelsUpdated = false;
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _aaEnabled ? GL_LINEAR : GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _aaEnabled ? GL_LINEAR : GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeated ? GL_REPEAT : GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeated ? GL_REPEAT : GL_CLAMP_TO_BORDER);
			GLfloat borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

			_paramsUpdated = false;
		}
#endif // _3DS

		s_bindedTexture = this;
	}
}

//=============================================================================

Texture & Texture::operator=(const Texture & other)
{
	unload();

	auto resName = other._resourceName;

	if (s_resourceManager.hasResource(resName))
	{
		ResourceData data;

		if (s_resourceManager.loadResource(resName, data))
		{
			loadResourceData(data);
			_resourceName = resName;
		}
	}

	return *this;
}

//=============================================================================

void Texture::loadResourceData(const ResourceData & data)
{
#ifndef _3DS
	_id = data.id;
#endif // _3DS

	_pixels = data.pixels;
	_width = data.width;
	_height = data.height;
	_location = data.location;
	_potWidth = util::clamp<int>(util::npot(data.width), MIN_SIZE, MAX_SIZE);
	_potHeight = util::clamp<int>(util::npot(data.height), MIN_SIZE, MAX_SIZE);
}

//=============================================================================

void Texture::setMemResourceName()
{
	_resourceName = kMemResPrefix + util::to_string(s_memResCounter++);
}

//=============================================================================

Texture::ResourceData Texture::createResourceData()
{
	ResourceData data;
	
#ifndef _3DS
	data.id = _id;
#endif // _3DS
	data.width = _width;
	data.height = _height;
	data.location = _location;
	data.pixels = _pixels;

	return data;
}

//=============================================================================

bool Texture::loadPixels(const byte * pixels, int width, int height, Location location)
{
	int potWidth = util::clamp<int>(util::npot(width), MIN_SIZE, MAX_SIZE);
	int potHeight = util::clamp<int>(util::npot(height), MIN_SIZE, MAX_SIZE);

	Uint32 pixelsSize = potWidth * potHeight * 4;

	if (width != _width || height != _height || location != _location)
	{
		unload();

#ifdef _3DS
		if (location == Location::Ram &&
			linearSpaceFree() > pixelsSize)
		{
			_pixels = (byte*)linearMemAlign(pixelsSize, 0x80);
		}
		else if (vramSpaceFree() > pixelsSize)
		{
			_pixels = (byte*)vramMemAlign(pixelsSize, 0x80);
		}
#else
		_pixels = new byte[pixelsSize];
		_pixelsUpdated = true;
#endif // _3DS

		if (_pixels == nullptr)
		{
			return false;
		}
	}

	_location = location;
	_width = std::min(width, potWidth);
	_height = std::min(height, potHeight);
	_potWidth = potWidth;
	_potHeight = potHeight;

#ifndef _3DS
	glGenTextures(1, &_id);
#endif // _3DS

	for (int x = 0; x < potWidth; ++x)
	{
		for (int y = 0; y < potHeight; ++y)
		{
			Uint32 dst_index, src_index;

#ifdef _3DS
			dst_index = gpuTextureIndex(x, y, potWidth, potHeight);
#else
			dst_index = x + y * potWidth;
#endif // _3DS

			if (x < width && y < height)
			{
				src_index = x + y * width;
#ifdef _3DS
				_pixels[dst_index * 4 + 3] = pixels[src_index * 4 + 0];
				_pixels[dst_index * 4 + 2] = pixels[src_index * 4 + 1];
				_pixels[dst_index * 4 + 1] = pixels[src_index * 4 + 2];
				_pixels[dst_index * 4 + 0] = pixels[src_index * 4 + 3];
#else
				_pixels[dst_index * 4 + 0] = pixels[src_index * 4 + 0];
				_pixels[dst_index * 4 + 1] = pixels[src_index * 4 + 1];
				_pixels[dst_index * 4 + 2] = pixels[src_index * 4 + 2];
				_pixels[dst_index * 4 + 3] = pixels[src_index * 4 + 3];
#endif // _3DS
			}
			else
			{
				((Uint32*)_pixels)[dst_index] = 0;
			}
		}
	}

#ifndef _3DS
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _potWidth, _potHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _aaEnabled ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _aaEnabled ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeated ? GL_REPEAT : GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeated ? GL_REPEAT : GL_CLAMP_TO_BORDER);

	glBindTexture(GL_TEXTURE_2D, 0);

	_pixelsUpdated = false;
#endif // _3DS

	return true;
}

//=============================================================================

NS_KAIRY_END

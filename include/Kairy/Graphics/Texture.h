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

#ifndef KAIRY_GRAPHICS_TEXTURE_H_INCLUDED
#define KAIRY_GRAPHICS_TEXTURE_H_INCLUDED

#include "Color.h"

NS_KAIRY_BEGIN

template<typename T>
class ResourceManager;

class Rect;

class Texture
{
public:
	// Constants
	enum
	{
		MIN_SIZE = 8,
		MAX_SIZE = 1024
	};

	/**
	 * @brief The location of the texture's pixels.
	 */
	enum class Location
	{
		Ram,
		Vram,

		Default = Ram // Change this if needed
	};

	/**
	 * @brief Return a pointer to the currently binded texture.
	 */
	inline static Texture* getBindedTexture() { return s_bindedTexture; }

	/**
	 * @brief Check if the antialiasing is enabled by default.
	 * @return true if the antialiasing is enabled by default.
	 */
	inline static bool isAaEnabledByDefault() { return s_defaultAaEnabled; }

	/**
	 * @brief Set if the antialiasing should be enabled by default or not.
	 * @param enabled If the antialiasing should be enabled or not.
	 */
	inline static void setAaEnabledByDefault(bool enabled) { s_defaultAaEnabled = enabled; }

	/**
	 * @brief Preload a texture.
	 * @param filename The texture file to load.
	 * @param location Where the texture will be allocated.
	 */
	static bool preload(const std::string& filename, Location location = Location::Default);

	/**
	 * @brief Unload a previously preloaded texture.
	 * @param filename The texture file to unload.
	 * @param location Where the texture was loaded.
	 */
	static bool unloadPreloaded(const std::string& filename, Location location = Location::Default);

	/**
	 * @brief Default constructor.
	 * Constructs an empty texture that is unusable until you
	 * call a load or create function.
	 */
	Texture(void);

	/**
	 * @brief Copy constructor.
	 */
	Texture(const Texture& other);

	/**
	 * @brief Constructs a texture loading it from a file.
	 * @param filename The texture file to load.
	 * @param location Where the texture will be allocated.
	 */
	Texture(const std::string& filename, Location location = Location::Default);

	Texture(const std::string& zipfile, const std::string& filename,
		Location location = Location::Default);

	/**
	 * @brief Constructs a texture loading it from a buffer.
	 * @param buffer The texture file buffer.
	 * @param buffer_size The texture buffer size.
	 * @param location Where the texture will be allocated.
	 */
	Texture(const byte* buffer, Uint32 buffer_size, Location location = Location::Default);

	/**
	 * @brief Constructs a texture loading it from RGBA8 pixels.
	 * @param pixels The pixels to load to the texture.
	 * @param width The texture width.
	 * @param height The texture height.
	 * @param location Where the texture will be allocated.
	 */
	Texture(const byte* pixels, int width, int height, Location location = Location::Default);

	/**
	 * @brief Constructs a rectangular texture with the specified
	 * dimensions and fill it with the given color.
	 * @param width The texture width.
	 * @param height The texture height.
	 * @param color The color to use to fill the texture.
	 * @param location Where the texture will be allocated.
	 */
	Texture(int width, int height, const Color& color = Color::Transparent,
		Location location = Location::Default);

	/**
	 * @brief Destructor.
	 */
	virtual ~Texture();

	/**
	 * @brief Load the texture from a file.
	 * @param filename The texture file.
	 * @param location Where the texture will be allocated.
	 * @return false if an error occurred.
	 */
	bool load(const std::string& filename, Location location = Location::Default);

	bool load(const std::string& zipfile, const std::string& filename,
		Location location = Location::Default);

	/**
	 * @brief Load the texture from a buffer.
	 * @param buffer The texture file buffer.
	 * @param buffer_size The texture buffer size.
	 * @param location Where the texture will be allocated.
	 * @return false if an error occurred.
	 */
	bool load(const byte* buffer, Uint32 buffer_size, Location location = Location::Default);

	/**
	 * @brief Load the texture from the given RGBA8 pixels.
	 * @param pixels The RGBA8 texture pixels.
	 * @param width The texture width.
	 * @param height The texture height.
	 * @param location Where the texture will be allocated.
	 * @return false if an error occurred.
	 */
	bool load(const byte* pixels, int width, int height, Location location = Location::Default);

	/**
	 * @brief Create a rectangular texture with the specified dimensions
	 * and fill it with the given color.
	 * @param width The texture width.
	 * @param height The texture height.
	 * @param color The color to use to fill the texture.
	 * @param location Where the texture will be allocated.
	 * @return false if an error occurred.
	 */
	bool create(int width, int height, const Color& color = Color::Transparent, Location = Location::Default);

	/**
	 * @brief Get the texture pixels in a RGBA8 format.
	 * @param outPixels The output pixels vector.
	 * @return false if an error occurred.
	 */
	bool getPixels(std::vector<Color>& outPixels) const;

	/**
	 * @brief Get the texture pixels in a RGBA8 format in
	 * a specified region.
	 * @param outPixels The output pixels vector.
	 * @param region The region rect.
	 * @return false if an error occurred.
	 */
	bool getPixels(std::vector<Color>& outPixels, const Rect& region) const;

	/**
	 * @brief Save the texture to a file of the specified format.
	 * @param filename The image file.
	 * @param format The desired image format.
	 * @param trans If the image format doesn't support
	 * transparency, all the transparent pixels will be replaced
	 * with this color.
	 * @return false if an error occurred.
	 */
	bool save(const std::string& filename, ImageFormat format,
		const Color& trans = Color::Magenta) const;

	/**
	 * @brief Save the texture to a file.
	 * @param filename The image file.
	 * @param trans If the image format doesn't support
	 * transparency, all the transparent pixels will be replaced
	 * with this color.
	 * @return false if an error occurred.
	 */
	bool save(const std::string& filename, const Color& trans = Color::Magenta) const;

	/**
	 * @brief Save the texture to a file buffer of the specified format.
	 * NOTE: Only Png is supported right now.
	 * @param outBuffer The output file buffer.
	 * @param format The desired image format.
	 * @param trans If the image format doesn't support
	 * transparency, all the transparent pixels will be replaced
	 * with this color.
	 * @return false if an error occurred.
	 */
	bool save(std::vector<byte>& outBuffer, ImageFormat format = ImageFormat::Png,
		const Color& trans = Color::Magenta) const;

	/**
	 * @brief Set the color of a pixel of the texture.
	 * @param x The pixel x position.
	 * @param y The pixel y position.
	 * @param color The color to assing to the pixel.
	 */
	void setPixel(int x, int y, const Color& color);

	/**
	 * @brief Get the color of a pixel of the texture.
	 * @param x The pixel x position.
	 * @param y The pixel y position.
	 * @return The color of the pixel.
	 */
	Color getPixel(int x, int y) const;

	/**
	 * @brief Fill the texture with the given color.
	 * @param color The color to use to fill the texture.
	 */
	void clear(const Color& color = Color::Transparent);

	bool scaleHq2x(void);

	bool scaleHq3x(void);

	bool scaleHq4x(void);

	/**
	 * @brief Get the texture width.
	 * @return The texture width in pixels.
	 */
	inline int getWidth() const { return _width; }

	/**
	 * @brief Get the texture height.
	 * @return The texture height in pixels.
	 */
	inline int getHeight() const { return _height; }

	/**
	 * @brief Get the real width of the texture.
	 * @return The power of two width of the texture.
	 */
	inline int getRealWidth() const { return _potWidth; }

	/**
	 * @brief Get the real height of the texture.
	 * @return The power of two height of the texture.
	 */
	inline int getRealHeight() const { return _potHeight; }

	/**
	 * @brief Get where the texture is allocated.
	 * @return The texture location.
	 */
	inline Location getLocation() const { return _location; }

	/**
	 * @brief Enable or disable the antialiasing.
	 * @param enable If true the texture will use the linear
	 * scaling algorithm, else it will use the the nearest algorithm.
	 */
	void enableAntialiasing(bool enable);

	/**
	 * @brief Set if the texture should be repeated.
	 * @param repeated If the texture should be repeated or not when
	 * the texture rect is bigger than the texture size.
	 */
	void setRepeated(bool repeated);

	/**
	 * @brief Change the location of the texture.
	 * @param newLocation The new location of the texture's pixels.
	 * @return false if an error occurred.
	 */
	bool changeLocation(Location newLocation);

	/**
	 * @brief Unload the texture destroying its pixels
	 * and making its width and height equals to zero.
	 * After that call the texture is unusable for drawing.
	 */
	void unload();

	/**
	 * @brief Bind the texture GPU making it usable for drawing.
	 * The texture is binded to the given unit.
	 * @param unit The unit index.
	 */
	void bind(int unit = 0);

	Texture& operator=(const Texture& other);

private:

	struct ResourceData
	{
		ResourceData(void)
			: memory(false)
			, width(0)
			, height(0)
			, location(Location::Default)
			, pixels(nullptr)
		{}

		bool memory;
		int width;
		int height;
		Location location;
		byte* pixels;
#ifndef _3DS
		GLuint id;
#endif // _3DS
	};

	void loadResourceData(const ResourceData&);
	void setMemResourceName();
	ResourceData createResourceData();

	static ResourceManager<ResourceData> s_resourceManager;
	static void deleteResourceData(ResourceData&);
	static Uint32 s_memResCounter;

protected:
	bool loadPixels(const byte* pixels, int width, int height, Location location);

	static Texture* s_bindedTexture; ///< The currently binded texture
	static bool s_defaultAaEnabled; ///< If the antialiasing is enabled by default

	Location _location;  ///< The location of the texture pixels (Ram or Vram)
	int _width;          ///< The texture width
	int _height;         ///< The texture height
	int _potWidth;       ///< The power of two width of the texture
	int _potHeight;      ///< The power of two height of the texture
	bool _aaEnabled;     ///< Wheter the texture is antialiased or not
	bool _repeated;      ///< Wheter the texture is repeated or not
	bool _paramsUpdated; ///< True if the texture parameters changed
	std::string _resourceName; ///< The name of the texture in the resource manager
	byte* _pixels;       ///< The pixels of the texture

#ifndef _3DS
	GLuint _id;
	bool _pixelsUpdated;
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_TEXTURE_H_INCLUDED

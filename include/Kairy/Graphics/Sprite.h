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

#ifndef KAIRY_GRAPHICS_SPRITE_H_INCLUDED
#define KAIRY_GRAPHICS_SPRITE_H_INCLUDED

#include "Node.h"
#include "Texture.h"

NS_KAIRY_BEGIN

/**
 * @class Sprite
 * @brief Represent a 2D sprite.
 */
class Sprite : public Node
{
public:
    /**
     * @brief Default constructor.
     * Constructs an empty sprite. You must load its
     * texture for being able to draw it.
     */
    Sprite(void);

    /**
     * @brief Constructs a sprite loading its texture
     * from the given texture file buffer.
     * @param buffer The texture file buffer.
     * @param buffer_size The size of the file buffer.
     * @param location Where the pixels of the texture will be allocated.
     */
    Sprite(const byte* buffer, Uint32 buffer_size,
           Texture::Location location = Texture::Location::Default);

    /**
     * @brief Constructs a sprite loading its texture
     * from the given RGBA8 pixels.
     * @param pixels The RGBA8 pixels.
     * @param width The texture pixels width.
     * @param height The texture pixels height.
     * @param location Where the pixels of the texture will be allocated.
     */
    Sprite(const byte* pixels, int width, int height,
           Texture::Location location = Texture::Location::Default);

    /**
     * @brief Constructs a sprite loading its texture from
     * the specified file.
     * @param filename The texture file to load.
     * @param location Where the pixels of the texture will be allocated.
     */
    Sprite(const std::string& filename,
           Texture::Location location = Texture::Location::Default);

	Sprite(const std::string& zipfile, const std::string& filename,
		Texture::Location location = Texture::Location::Default);

    /**
     * @brief Constructs a sprite creating its texture
     * from the given width, height and color.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param color The color to use to fill the texture.
     * @param location Where the pixels of the texture will be allocated.
     */
    Sprite(int width, int height, const Color& color,
           Texture::Location location = Texture::Location::Default);

    /**
     * @brief Destructor.
     */
    virtual ~Sprite();

    /**
     * @brief Get the texture of the sprite.
     * @return A reference to the texture of the sprite.
     */
    inline Texture& getTexture();

    /**
     * @brief Get the width of the texture.
     * @return The width of the texture.
     */
    inline int getTextureWidth() const;

    /**
     * @brief Get the height of the texture.
     * @return The height of the texture.
     */
    inline int getTextureHeight() const;

    /**
     * @brief Get the size of the texture.
     * @return The size of the texture.
     */
    inline Vec2 getTextureSize() const;

    /**
     * @brief Get the texture source rectangle.
     * @return The texture rect.
     */
    inline Rect getTextureRect() const;

    /**
     * @brief Set the texture source rect.
     * @param rect The texture rect.
     * @return A reference to this sprite.
     */
    inline Sprite& setTextureRect(const Rect& rect);

    /**
     * @brief Set the texture source rect.
     * @param x The x coordinate of the rect.
     * @param y The y coordinate of the rect.
     * @param width The width of the rect.
     * @param height The height of the rect.
     * @return A referencet to this sprite.
     */
    inline Sprite& setTextureRect(float x, float y, float width, float height);

    /**
     * @brief Update the texture rect making it cover
     * all the texture.
     * @return A reference to this sprite.
     */
    Sprite& updateTextureRect();

    /**
     * @brief Load the texture of the sprite from the specified file.
     * @param filename The texture file.
     * @param location Where the pixels of the texture will be allocated.
     * @return false if an error occurred.
     */
    bool loadTexture(const std::string& filename,
                     Texture::Location location = Texture::Location::Default);

    /**
     * @brief Load the texture of the sprite from the given
     * RGBA8 pixels.
     * @param pixels The RGBA8 pixels.
     * @param width The texture width.
     * @param height The texture height.
     * @param location Where the pixels of the texture will be allocated.
     * @return false if an error occurred.
     */
    bool loadTexture(const byte* pixels, int width, int height,
                     Texture::Location location = Texture::Location::Default);

    /**
     * @brief Load the texture of the sprite from the given
     * texture file buffer.
     * @param buffer The texture file buffer.
     * @param buffer_size The texture buffer size.
     * @param location Where the pixels of the texture will be allocated.
     * @return false if an error occurred.
     */
    bool loadTexture(const byte* buffer, Uint32 buffer_size,
                     Texture::Location location = Texture::Location::Default);

    /**
     * @brief Create the texture of the sprite from the given width,
     * height and color.
     * @param width The width of the texture.
     * @param height The height of the texture.
     * @param color The color to use to fill the texture.
     * @return false if an error occurred.
     */
    bool createTexture(int width, int height, const Color& color,
                       Texture::Location location = Texture::Location::Default);

	/**
	 * Draws the sprite.
	 */
	virtual void draw() override;

protected:
    void init();

    Texture _texture;  ///< Sprite texture
    Rect _textureRect; ///< Texture source rect
};

#include "Sprite.inl"

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_SPRITE_H_INCLUDED

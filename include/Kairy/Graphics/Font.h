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

#ifndef KAIRY_GRAPHICS_FONT_H_INCLUDED
#define KAIRY_GRAPHICS_FONT_H_INCLUDED

#include "Sprite.h"

NS_KAIRY_BEGIN

class Font
{
public:

    Font(void);
	
	Font(float size);

	Font(const std::string& filename);

	Font(const std::string& filename, float size);

    virtual ~Font();

    bool loadBmf(const std::string& filename,
              Texture::Location location = Texture::Location::Default);

    bool loadBmfBin(const std::string& filename,
            Texture::Location location = Texture::Location::Default);

    bool loadBmfXml(const std::string& filename,
            Texture::Location location = Texture::Location::Default);

    bool loadTtf(const std::string& filename, float size,
            Texture::Location location = Texture::Location::Default);
			
	bool loadTtf(const byte* buffer, float size,
			Texture::Location location = Texture::Location::Default);
			
	bool loadTtf(float size,
			Texture::Location location = Texture::Location::Default);

    void unload();

    inline std::string getName() const { return _name; }

    inline float getSize() const { return _size; }
	
	inline int getLineHeight() const { return _lineHeight; }

public:
	bool loadStb(void* stb, float size, Texture::Location location);
	
	
    friend class Text;

    struct Character
    {
        int x;
        int y;
        int width;
        int height;
        int xoffset;
        int yoffset;
        int xadvance;
        int page;

        std::map<Uint32, Uint32> kernings;
    };

    std::vector<std::unique_ptr<Texture>> _pages;
    std::map<Uint32, Character> _characters;
    int _base;
    int _lineHeight;
    std::string _name;
    float _size;
};

NS_KAIRY_END

#endif // KAIRY_GRAPHICS_FONT_H_INCLUDED

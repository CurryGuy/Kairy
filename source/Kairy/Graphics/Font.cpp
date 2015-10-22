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

#include <Kairy/Graphics/Font.h>
#include <Kairy/Ext/tinyxml2.h>
#include <Kairy/Macros.h>
#define STB_TRUETYPE_IMPLEMENTATION
//#define STBTT_RASTERIZER_VERSION 1
//#define STBTT_MAX_OVERSAMPLE 128
#include "stb_truetype.h"
#include <Kairy/Util/ReadFile.h>
#include <Kairy/Util/Endian.h>
#include <Kairy/Graphics/Image.h>
#include "arial.h"

NS_KAIRY_BEGIN

//=============================================================================

Font::Font()
    :_base(0)
    ,_lineHeight(0)
{
}

//=============================================================================

Font::Font(float size)
	: Font()
{
	loadTtf(size);
}

//=============================================================================

Font::Font(const std::string & filename)
	: Font()
{
	loadBmf(filename);
}

//=============================================================================

Font::Font(const std::string & filename, float size)
	: Font()
{
	loadTtf(filename, size);
}

//=============================================================================

Font::~Font()
{
	unload();
}

//=============================================================================

struct BmfHeader
{
    byte signature[3];
    byte version;
};

struct BmfBlockHeader
{
    byte id;
    byte size[4];
};

struct BmfBlockInfo
{
    byte fontSize[2];
    byte bitField;
    byte charSet;
    byte stretchH[2];
    byte aa;
    byte paddingUp;
    byte paddingRight;
    byte paddingDown;
    byte paddingLeft;
    byte spacingHoriz;
    byte spacingVert;
    byte outline;
};

struct BmfBlockCommon
{
    byte lineHeight[2];
    byte base[2];
    byte scaleW[2];
    byte scaleH[2];
    byte pages[2];
    byte bitField;
    byte alphaChnl;
    byte redChnl;
    byte greenChnl;
    byte blueChnl;
};

struct BmfBlockChar
{
    byte id[4];
    byte x[2];
    byte y[2];
    byte width[2];
    byte height[2];
    byte xoffset[2];
    byte yoffset[2];
    byte xadvance[2];
    byte page;
    byte chnl;
};

struct BmfBlockKerning
{
    byte first[4];
    byte second[4];
    byte amount[2];
};

//=============================================================================

static const byte constexpr BMF_BLOCK_INFO_ID = 1;
static const byte constexpr BMF_BLOCK_COMMON_ID = 2;
static const byte constexpr BMF_BLOCK_PAGES_ID = 3;
static const byte constexpr BMF_BLOCK_CHARS_ID = 4;
static const byte constexpr BMF_BLOCK_KERNINGS_ID = 5;

//=============================================================================

bool Font::loadBmfBin(const std::string& filename, Texture::Location location)
{
    unload();

    std::string path;
    auto separatorPos = filename.find_last_of("/\\");
    if(separatorPos != std::string::npos)
    {
        path = filename.substr(0, separatorPos + 1);
    }

    FILE* fp = fopen(filename.c_str(), "rb");

    if(fp == nullptr)
    {
        return false;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    BmfHeader header;
    BmfBlockHeader blockHeader;
    BmfBlockInfo blockInfo;
    BmfBlockCommon blockCommon;
    BmfBlockChar blockChar;
    BmfBlockKerning blockKerning;

    fread(&header, sizeof(BmfHeader), 1, fp);

    if(header.signature[0] != 'B' &&
       header.signature[1] != 'M' &&
       header.signature[2] != 'F' &&
       header.version != 3)
    {
        fclose(fp);
        return false;
    }

    while(ftell(fp) < file_size)
    {
        fread(&blockHeader, sizeof(BmfBlockHeader), 1, fp);
        Uint32 blockSize = util::bytesToUintLE(blockHeader.size);

        switch(blockHeader.id)
        {
        case BMF_BLOCK_INFO_ID:
            {
                // Get font name
                fread(&blockInfo, sizeof(BmfBlockInfo), 1, fp);
                int nameLength = blockSize - sizeof(BmfBlockInfo);
                _name.resize(nameLength);
                fread(&_name[0], nameLength, 1, fp);
            }
            break;
        case BMF_BLOCK_COMMON_ID:
            {
                fread(&blockCommon, sizeof(BmfBlockCommon), 1, fp);
                _lineHeight = util::bytesToUshortLE(blockCommon.lineHeight);
                _base = util::bytesToUshortLE(blockCommon.base);
            }
            break;
        case BMF_BLOCK_PAGES_ID:
            {
                Uint32 i = 0;
                std::string page;
                while(i < blockSize)
                {
                    char c;
                    fread(&c, 1, 1, fp);
                    ++i;
                    page += c;
                    if(c == '\0')
                    {
						std::unique_ptr<Texture> texture(new Texture());

                        if(!texture || !texture->load(path + page, location))
                        {
                            fclose(fp);
                            return false;
                        }

						_pages.push_back(std::move(texture));

                        page = "";
                    }
                }
            }
            break;
        case BMF_BLOCK_CHARS_ID:
            {
                int charactesCount = blockSize / sizeof(BmfBlockChar);
                for(int i = 0; i < charactesCount; ++i)
                {
                    fread(&blockChar, sizeof(BmfBlockChar), 1, fp);

                    Uint32 id = util::bytesToUintLE(blockChar.id);

                    Character c;
                    c.x = util::bytesToUshortLE(blockChar.x);
                    c.y = util::bytesToUshortLE(blockChar.y);
                    c.width = util::bytesToUshortLE(blockChar.width);
                    c.height = util::bytesToUshortLE(blockChar.height);
                    c.xoffset = util::bytesToShortLE(blockChar.xoffset);
                    c.yoffset = util::bytesToShortLE(blockChar.yoffset);
                    c.xadvance = util::bytesToShortLE(blockChar.xadvance);
                    c.page = blockChar.page;

                    _characters[id] = c;
                }
            }
            break;
        case BMF_BLOCK_KERNINGS_ID:
            {
                int kerningsCount = blockSize / sizeof(BmfBlockKerning);

                for(int i = 0; i < kerningsCount; ++i)
                {
                    fread(&blockKerning, sizeof(BmfBlockKerning), 1, fp);

                    Uint32 first = util::bytesToUintLE(blockKerning.first);
                    Uint32 second = util::bytesToUintLE(blockKerning.second);
                    short amount = util::bytesToShortLE(blockKerning.amount);
                    _characters[first].kernings[second] = amount;
                }
            }
            break;
        default:
            fclose(fp);
            return false;
        }
    }

    fclose(fp);

    return true;
}

//=============================================================================

bool Font::loadBmfXml(const std::string& filename, Texture::Location location)
{
    unload();

    std::string path;
    auto separatorPos = filename.find_last_of("/\\");
    if(separatorPos != std::string::npos)
    {
        path = filename.substr(0, separatorPos + 1);
    }

    tinyxml2::XMLDocument document;

    if(document.LoadFile(filename.c_str()) !=
            tinyxml2::XML_NO_ERROR)
    {
        return false;
    }

    auto fontElement = document.FirstChildElement("font");

    if(!fontElement)
    {
        return false;
    }

    auto infoElement = fontElement->FirstChildElement("info");
    auto commonElement = fontElement->FirstChildElement("common");
    auto pagesElement = fontElement->FirstChildElement("pages");
    auto charsElement = fontElement->FirstChildElement("chars");
    auto kerningsElement = fontElement->FirstChildElement("kernings");

    if(!infoElement || !commonElement || !pagesElement || !charsElement)
    {
        return false;
    }

    _name = infoElement->Attribute("face");
    _lineHeight = commonElement->IntAttribute("lineHeight");
    _base = commonElement->IntAttribute("base");

    int pagesCount = commonElement->IntAttribute("pages");

    _pages.resize(pagesCount);

    auto pageElement = pagesElement->FirstChildElement("page");

    while(pageElement)
    {
        int id = pageElement->IntAttribute("id");
        std::string file = pageElement->Attribute("file");

		_pages[id].reset(new Texture());

        if(!_pages[id] || !_pages[id]->load(path + file, location))
        {
            return false;
        }

        pageElement = pageElement->NextSiblingElement();
    }

    auto charElement = charsElement->FirstChildElement("char");

    while(charElement)
    {
        Character c;

        Uint32 id = charElement->UnsignedAttribute("id");

        c.x = charElement->IntAttribute("x");
        c.y = charElement->IntAttribute("y");
        c.width = charElement->IntAttribute("width");
        c.height = charElement->IntAttribute("height");
        c.xoffset = charElement->IntAttribute("xoffset");
        c.yoffset = charElement->IntAttribute("yoffset");
        c.xadvance = charElement->IntAttribute("xadvance");
        c.page = charElement->IntAttribute("page");

        _characters[id] = c;

        charElement = charElement->NextSiblingElement();
    }

    if(kerningsElement)
    {
        auto kerningElement = kerningsElement->FirstChildElement("kerning");

        while(kerningElement)
        {
            Uint32 first = kerningElement->UnsignedAttribute("first");
            Uint32 second = kerningElement->UnsignedAttribute("second");
            int amount = kerningElement->IntAttribute("amount");

            auto it = _characters.find(first);

            if(it != _characters.end())
            {
                it->second.kernings[second] = amount;
            }

            kerningElement = kerningElement->NextSiblingElement();
        }
    }

    return true;
}

//=============================================================================

bool Font::loadTtf(const std::string& filename, float size, Texture::Location location)
{
	unload();
	
	std::vector<byte> fontData;

    if(!util::ReadAllBytes(filename, fontData))
    {
        return false;
    }
	
	int fontOffset = stbtt_GetFontOffsetForIndex(fontData.data(), 0);
	
	stbtt_fontinfo info;
	stbtt_InitFont(&info, fontData.data(), fontOffset);
	
	return loadStb(&info, size, location);
}

//=============================================================================

bool Font::loadTtf(const byte* buffer, float size, Texture::Location location)
{
	unload();
	
	if(!buffer)
	{
		return false;
	}
	
	int fontOffset = stbtt_GetFontOffsetForIndex(buffer, 0);
	
	stbtt_fontinfo info;
	stbtt_InitFont(&info, buffer, fontOffset);
	
	return loadStb(&info, size, location);
}

//=============================================================================

bool Font::loadTtf(float size, Texture::Location location)
{
	return loadTtf(arial_ttf, size, location);
}

//=============================================================================

bool Font::loadStb(void* stb, float size, Texture::Location location)
{
	int pageWidth = 512;
	int pageHeight = 512;
	int startingCodepoint = 32;
	int endingCodepoint = 128;

    auto& info = *static_cast<stbtt_fontinfo*>(stb);
	
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);
	float fontScale = stbtt_ScaleForPixelHeight(&info, size);

	_lineHeight = int((ascent - descent + lineGap) * fontScale);

	// Caching glyph indices
	std::map<int, int> glyphIndices;
	for (int i = startingCodepoint; i <= endingCodepoint; ++i)
	{
		glyphIndices[i] = stbtt_FindGlyphIndex(&info, i);
	}

	Image pageImage(pageWidth, pageHeight, Color::Transparent);

	int x = 0;
	int y = 0;
	int maxWidth = 0;

	for (int codepoint = startingCodepoint; codepoint <= endingCodepoint; ++codepoint)
	{
		int width = 0, height = 0;
		int xoff = 0, yoff = 0;

		int glyphIndex = glyphIndices[codepoint];

		unsigned char* bitmap = stbtt_GetGlyphBitmap(&info, 0, fontScale,
			glyphIndex, &width, &height, &xoff, &yoff);

		// TODO: Handle this in a better way
		if (!bitmap)
			continue;

		if (width > maxWidth)
			maxWidth = width;

		if (x + width >= pageWidth)
		{
			x = 0;

			if (y + _lineHeight >= pageHeight)
			{
				std::unique_ptr<Texture> page(new Texture());

				pageImage.toTexture(*page);
				pageImage.clear(Color::Transparent);
				_pages.push_back(std::move(page));
				y = 0;
			}
			else
			{
				y += _lineHeight;
			}
		}

		Image glyphImage(width, height, Color::Transparent);

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				byte gray = bitmap[i + j * width];
				glyphImage.setPixel(i, j, Color(gray, gray, gray, gray));
			}
		}
		
		stbtt_FreeBitmap(bitmap, nullptr);

		int advance = 0;
		int bearingX = 0;

		stbtt_GetGlyphHMetrics(&info, glyphIndex, &advance, &bearingX);

		pageImage.drawImage(x, y, glyphImage);

		Character ch;

		ch.page = (int)_pages.size();
		ch.height = height;
		ch.width = width;
		ch.x = x;
		ch.y = y;
		ch.xoffset = (int)std::ceil(bearingX * fontScale);
		ch.yoffset = (int)std::ceil(ascent * fontScale) + yoff;
		ch.xadvance = (int)std::ceil(advance * fontScale);
		
		for (int codepoint2 = startingCodepoint; codepoint2 <= endingCodepoint; ++codepoint2)
		{
			int glyphIndex2 = glyphIndices[codepoint2];
			int kerning = stbtt_GetGlyphKernAdvance(&info, glyphIndex, glyphIndex2);

			if (kerning > 0)
			{
				ch.kernings[Uint32(codepoint2)] = (int)std::ceil(kerning * fontScale);
			}
		}

		_characters[Uint32(codepoint)] = ch;

		x += width;
	}

	std::unique_ptr<Texture> page(new Texture());
	pageImage.toTexture(*page);
	_pages.push_back(std::move(page));

	_base = maxWidth;

    return true;
}

//=============================================================================

bool Font::loadBmf(const std::string& filename, Texture::Location location)
{
    // Check binary BMF
    FILE* fp = fopen(filename.c_str(), "rb");

    if(!fp)
    {
        return false;
    }

    byte sig[3];
    fread(sig, 1, 3, fp);
    fclose(fp);

    if(sig[0] == 'B' && sig[1] == 'M' && sig[2] == 'F')
    {
        return loadBmfBin(filename, location);
    }

    return loadBmfXml(filename, location);
}

//=============================================================================

void Font::unload()
{
    _pages.clear();
    _characters.clear();
    _base = 0;
    _lineHeight = 0;
    _name = "";
}

//=============================================================================

NS_KAIRY_END

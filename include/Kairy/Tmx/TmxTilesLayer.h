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

#ifndef KAIRY_TMX_TMX_TILES_LAYER_H_INCLUDED
#define KAIRY_TMX_TMX_TILES_LAYER_H_INCLUDED

#include "TmxMapTile.h"
#include "TmxProperties.h"

NS_KAIRY_BEGIN

class TmxTilesLayer
{
public:
    enum class Encoding
    {
        Xml,
        Base64,
        Csv
    };

    enum class Compression
    {
        None,
        Zlib,
        Gzip
    };

    TmxTilesLayer();

    inline Encoding getEncoding() const { return _encoding; }

    inline Compression getCompression() const { return _compression; }

    inline std::string getName() const { return _name; }

    inline int getIndex() const { return _index; }

    inline int getX() const { return _x; }

    inline int getY() const { return _y; }

    inline int getWidth() const { return _width; }

    inline int getHeight() const { return _height; }

    inline float getOpacity() const { return _opacity; }

    inline bool isVisible() const { return _visible; }

    inline const TmxProperties& getProperties() const { return _properties; }

    inline const std::vector<TmxMapTile>& getTiles() const { return _tiles; }

	inline int getTilesCount() const { return (int)_tiles.size(); }

	TmxMapTile getTile(int x, int y) const;

public:
    bool parseElement(void*);
    bool parseXmlData(void*);
    bool parseBase64Data(void*);
    bool parseCsv(void*);

    Encoding _encoding;
    Compression _compression;
    std::string _name;
    int _index;
    int _x;
    int _y;
    int _width;
    int _height;
    float _opacity;
    bool _visible;
    TmxProperties _properties;
    std::vector<TmxMapTile> _tiles;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_TILES_LAYER_H_INCLUDED

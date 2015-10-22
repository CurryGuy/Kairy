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

#ifndef KAIRY_TMX_TMX_TILESET_H_INCLUDED
#define KAIRY_TMX_TMX_TILESET_H_INCLUDED

#include "TmxTilesetTile.h"
#include "TmxTerrainType.h"

NS_KAIRY_BEGIN

class TmxTileset
{
public:
    TmxTileset();

    inline int getFirstGid() const { return _firstGid; }

    inline std::string getSource() const { return _source; }

    inline std::string getName() const { return _name; }

	inline std::string getPath() const { return _path; }

    inline int getTileWidth() const { return _tileWidth; }

    inline int getTileHeight() const { return _tileHeight; }

    inline int getSpacing() const { return _spacing; }

    inline int getMargin() const { return _margin; }

    inline int getOffsetX() const { return _offsetX; }

    inline int getOffsetY() const { return _offsetY; }

    inline int getTileCount() const { return _tileCount; }

    inline const TmxProperties& getProperties() const { return _properties; }

    inline const TmxImage& getImage() const { return _image; }

    inline const std::vector<TmxTerrainType>& getTerrainTypes() const { return _terrainTypes; }

    inline const std::vector<TmxTilesetTile>& getTiles() const { return _tiles; }

public:
    bool parseElement(void*,const std::string&);

    int _firstGid;
    std::string _source;
    std::string _name;
	std::string _path;
    int _tileWidth;
    int _tileHeight;
    int _spacing;
    int _margin;
    int _offsetX;
    int _offsetY;
    int _tileCount;

    TmxProperties _properties;
    TmxImage _image;
    std::vector<TmxTerrainType> _terrainTypes;
    std::vector<TmxTilesetTile> _tiles;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_TILESET_H_INCLUDED

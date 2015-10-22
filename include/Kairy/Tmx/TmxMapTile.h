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

#ifndef KAIRY_TMX_TMX_MAP_TILE_H_INCLUDED
#define KAIRY_TMX_TMX_MAP_TILE_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class TmxMapTile
{
public:
    enum
    {
        FlippedHorzFlag = 0x80000000,
        FlippedVertFlag = 0x40000000,
        FlippedDiagFlag = 0x20000000
    };

    TmxMapTile(Uint32 gid);

	TmxMapTile(void)
		: _gid(0)
		, _id(-1)
		, _tilesetIndex(-1)
		, _flippedVert(false)
		, _flippedHorz(false)
		, _flippedDiag(false)
	{
	}

    inline Uint32 getGid() const { return _gid; }

    inline int getId() const { return _id; }

    inline int getTilesetIndex() const { return _tilesetIndex; }

    inline bool isFlippedVertically() const { return _flippedVert; }

    inline bool isFlippedHorizontally() const { return _flippedHorz; }

    inline bool isFlippedDiagonally() const { return _flippedDiag; }

private:
    friend class TmxMap;

    Uint32 _gid;
    int _id;
    int _tilesetIndex;
    bool _flippedVert;
    bool _flippedHorz;
    bool _flippedDiag;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_MAP_TILE_H_INCLUDED

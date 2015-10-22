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

#ifndef KAIRY_TMX_TMX_TILESET_TILE_H_INCLUDED
#define KAIRY_TMX_TMX_TILESET_TILE_H_INCLUDED

#include "TmxAnimation.h"
#include "TmxProperties.h"
#include "TmxObjectGroup.h"
#include "TmxImage.h"

NS_KAIRY_BEGIN

class TmxTilesetTile
{
public:

    TmxTilesetTile() : _id(-1), _probability(0) {}

    inline int getId() const { return _id; }

    inline std::string getTerrain() const { return _terrain; }

    inline float getProbality() const { return _probability; }

    inline const TmxAnimation& getAnimation() const { return _animation; }

    inline const TmxProperties& getProperties() const { return _properties; }

    inline const TmxObjectGroup& getObjectGroup() const { return _objectGroup; }

    inline const TmxImage& getImage() const { return _image; }

private:
    friend class TmxTileset;

    bool parseElement(void*);

    int _id;
    std::string _terrain;
    float _probability;
    TmxAnimation _animation;
    TmxProperties _properties;
    TmxObjectGroup _objectGroup;
    TmxImage _image;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_TILESET_TILE_H_INCLUDED

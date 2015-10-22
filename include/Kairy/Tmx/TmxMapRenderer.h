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

#ifndef KAIRY_TMX_TMX_MAP_RENDERER_H_INCLUDED
#define KAIRY_TMX_TMX_MAP_RENDERER_H_INCLUDED

#include "TmxMap.h"
#include <Kairy/Graphics/Sprite.h>

NS_KAIRY_BEGIN

class TmxMapRenderer : public Node
{
public:
    TmxMapRenderer(void);

    TmxMapRenderer(const TmxMap& map,
            Texture::Location location = Texture::Location::Default);

    virtual ~TmxMapRenderer();

	virtual void draw() override;

    void draw(int layerIndex);

    virtual void update(float dt) override;

    int getTileId(int layer, int x, int y) const;

    void setTileId(int layer, int x, int y, int id);

    bool setMap(const TmxMap& map,
            Texture::Location location = Texture::Location::Default);

	inline int getMapWidth() const { return _mapWidth; }

	inline int getMapHeight() const { return _mapHeight; }

	inline int getMapWidthInPixels() const { return _mapWidth * _tileWidth; }

	inline int getMapHeightInPixels() const { return _mapHeight * _tileHeight; }

	inline int getTileWidth() const { return _tileWidth; }

	inline int getTileHeight() const { return _tileHeight; }

	inline int getLayersCount() const { return (int)_layers.size();  }

	inline int getChildsLayer() const { return _childsLayer; }

	inline void setChildsLayer(int index) { _childsLayer = index; }

	inline Rect& getCamera() { return _camera; }

	inline void setCamera(const Rect& camera) { _camera = camera; }

protected:
    struct Tile
    {
        short id;
        short tilesetIndex;
    };

    struct Layer
    {
        std::vector<Tile> tiles;
        byte opacity;
    };

    struct AnimationFrame
    {
        short id;
        float duration;
    };

    struct Animation
    {
        std::vector<AnimationFrame> frames;
        Uint16 currentFrame;
        float animTime;
    };

    struct Tileset
    {
        Sprite sprite;
        Uint16 tileWidth;
        Uint16 tileHeight;
        Uint16 columns;
		Uint16 margin;
		Uint16 spacing;

        std::map<short, Animation> animations;
    };

    int _mapWidth;
    int _mapHeight;
	int _childsLayer;
	Rect _camera;
    Uint16 _tileWidth;
    Uint16 _tileHeight;
    bool _loaded;
	TmxMap::Orientation _type;

    short getTileAnimId(const Tile& tile);

    std::vector<std::unique_ptr<Tileset>> _tilesets;
    std::vector<Layer> _layers;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_MAP_RENDERER_H_INCLUDED

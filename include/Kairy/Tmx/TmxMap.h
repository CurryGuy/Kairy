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

#ifndef KAIRY_TMX_TMX_MAP_H_INCLUDED
#define KAIRY_TMX_TMX_MAP_H_INCLUDED

#include "TmxTilesLayer.h"
#include "TmxTileset.h"
#include "TmxImageLayer.h"
#include "TmxObjectGroup.h"

NS_KAIRY_BEGIN

class TmxMap
{
public:
    enum class Orientation
    {
        Orthogonal,
        Isometric,
        Staggered
    };

	struct TileCollision
	{
		int id;
		int tileset;
		TmxObjectGroup objGroup;
	};

    TmxMap(void);

    TmxMap(const std::string& filename);

    inline std::string getPath() const { return _path; }

    inline float getVersion() const { return _version; }

    inline int getWidth() const { return _width; }

    inline int getHeight() const { return _height; }

    inline int getTileWidth() const { return _tileWidth; }

    inline int getTileHeight() const { return _tileHeight; }

    inline Color getBackgroundColor() const { return _bgColor; }

    inline Orientation getOrientation() const { return _orientation; }

	inline int getTilesetsCount() const { return (int)_tilesets.size(); }

	inline int getLayersCount() const { return (int)_layers.size(); }

	inline int getObjectGroupsCount() const { return (int)_layers.size(); }

	inline int getImageLayersCount() const { return (int)_imageLayers.size(); }

    inline const TmxProperties& getProperties() const { return _properties; }

    inline const std::vector<TmxTileset>& getTilesets() const { return _tilesets; }

    inline const std::vector<TmxTilesLayer>& getLayers() const { return _layers; }

    inline const std::vector<TmxObjectGroup>& getObjectGroups() const { return _objGroups; }

    inline const std::vector<TmxImageLayer>& getImageLayers() const { return _imageLayers; }

    const TmxTileset* getTileset(Uint32 index) const;

    const TmxTilesLayer* getLayer(Uint32 index) const;

    const TmxObjectGroup* getObjectGroup(Uint32 index) const;

    const TmxImageLayer* getImageLayer(Uint32 index) const;

    const TmxTilesLayer* getLayer(const std::string& name) const;

    const TmxObjectGroup* getObjectGroup(const std::string& name) const;

    const TmxImageLayer* getImageLayer(const std::string& name) const;

    int getTilesetIndexByGid(Uint32 gid) const;

	std::vector<TileCollision> getTileCollisions() const;

	std::vector<bool> getTilesWithCollision() const;

    bool load(const std::string& filename);

    bool load(const std::string& buffer, const std::string& path);

private:
    bool load(void*,const std::string&);

    std::string _path;
    float _version;
    int _width;
    int _height;
    int _tileWidth;
    int _tileHeight;
    Color _bgColor;
    Orientation _orientation;
    TmxProperties _properties;
    std::vector<TmxTileset> _tilesets;
    std::map<std::string, int> _layersIn;
    std::vector<TmxTilesLayer> _layers;
    std::map<std::string, int> _objGroupsIn;
    std::vector<TmxObjectGroup> _objGroups;
    std::map<std::string, int> _imageLayersIn;
    std::vector<TmxImageLayer> _imageLayers;
};

NS_KAIRY_END

#endif // KAIRY_TMX_TMX_MAP_H_INCLUDED

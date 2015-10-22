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

#include <Kairy/Tmx/TmxMap.h>
#include <Kairy/Ext/tinyxml2.h>

NS_KAIRY_BEGIN

//=============================================================================

TmxMap::TmxMap(void)
    :_version(0.0f)
    ,_width(0)
    ,_height(0)
    ,_tileWidth(0)
    ,_tileHeight(0)
    ,_bgColor(Color::Transparent)
    ,_orientation(Orientation::Isometric)
{
}

//=============================================================================

TmxMap::TmxMap(const std::string& filename)
    :TmxMap()
{
    load(filename);
}

//=============================================================================

const TmxTileset* TmxMap::getTileset(Uint32 index) const
{
    if(index >= _tilesets.size())
    {
        return nullptr;
    }
    return &_tilesets[index];
}

//=============================================================================

const TmxTilesLayer* TmxMap::getLayer(Uint32 index) const
{
    if(index >= _layers.size())
    {
        return nullptr;
    }
    return &_layers[index];
}

//=============================================================================

const TmxObjectGroup* TmxMap::getObjectGroup(Uint32 index) const
{
    if(index >= _objGroups.size())
    {
        return nullptr;
    }
    return &_objGroups[index];
}

//=============================================================================

const TmxImageLayer* TmxMap::getImageLayer(Uint32 index) const
{
    if(index >= _imageLayers.size())
    {
        return nullptr;
    }
    return &_imageLayers[index];
}

//=============================================================================

const TmxTilesLayer* TmxMap::getLayer(const std::string& name) const
{
    auto it = _layersIn.find(name);

    if(it == _layersIn.end())
    {
        return false;
    }

    return &_layers[it->second];
}

//=============================================================================

const TmxObjectGroup* TmxMap::getObjectGroup(const std::string& name) const
{
    auto it = _objGroupsIn.find(name);

    if(it == _objGroupsIn.end())
    {
        return false;
    }

    return &_objGroups[it->second];
}

//=============================================================================

const TmxImageLayer* TmxMap::getImageLayer(const std::string& name) const
{
    auto it = _imageLayersIn.find(name);

    if(it == _imageLayersIn.end())
    {
        return false;
    }

    return &_imageLayers[it->second];
}

//=============================================================================

bool TmxMap::load(const std::string& filename)
{
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

    auto mapElement = document.FirstChildElement("map");

    return load(mapElement, path);
}

//=============================================================================

bool TmxMap::load(const std::string& buffer, const std::string& path)
{
    tinyxml2::XMLDocument document;

    if(document.Parse(buffer.c_str(), buffer.length()) !=
            tinyxml2::XML_NO_ERROR)
    {
        return false;
    }

    auto mapElement = document.FirstChildElement("map");

    return load(mapElement, path);
}

//=============================================================================

bool TmxMap::load(void* p, const std::string& path)
{
    _layers.clear();
    _layersIn.clear();
    _tilesets.clear();
    _objGroups.clear();
    _objGroupsIn.clear();
    _imageLayers.clear();
    _imageLayersIn.clear();
    _properties.clear();

    _version = 0.0f;
    _width = 0;
    _height = 0;
    _tileWidth = 0;
    _tileHeight = 0;
    _orientation = Orientation::Orthogonal;
    _bgColor = Color::Transparent;
    _path = "";

    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    element->QueryFloatAttribute("version", &_version);
    element->QueryIntAttribute("width", &_width);
    element->QueryIntAttribute("height", &_height);
    element->QueryIntAttribute("tilewidth", &_tileWidth);
    element->QueryIntAttribute("tileheight", &_tileHeight);

    if(element->Attribute("backgroundcolor"))
    {
		std::string colorStr = element->Attribute("backgroundcolor");
		if (colorStr.length() > 0)
		{
			colorStr = colorStr.substr(1, colorStr.length() - 1);
			std::stringstream ss;
			ss << std::hex << colorStr;
			Uint32 colorValue = 0;
			ss >> colorValue;
			_bgColor = Color(colorValue << 8 | 0xFF);
		}
    }

    if(element->Attribute("orientation"))
    {
        std::string orientationStr = element->Attribute("orientation");

        if(orientationStr == "isometric")
        {
            _orientation = Orientation::Isometric;
        }
        else if(orientationStr == "staggered")
        {
            _orientation = Orientation::Staggered;
        }
    }

    auto childElement = element->FirstChildElement();

    int layerIndex = 0;

    while(childElement)
    {
        std::string name = childElement->Name();

        if(name == "tileset")
        {
            _tilesets.push_back(TmxTileset());
            if(!_tilesets.back().parseElement(childElement, path))
            {
                return false;
            }
        }
        else if(name == "layer")
        {
            _layers.push_back(TmxTilesLayer());
            if(!_layers.back().parseElement(childElement))
            {
                return false;
            }
            _layersIn[_layers.back().getName()] = _layers.size() - 1;
            _layers.back()._index = layerIndex++;
        }
        else if(name == "imagelayer")
        {
            _imageLayers.push_back(TmxImageLayer());
            if(!_imageLayers.back().parseElement(childElement))
            {
                return false;
            }
            _imageLayersIn[_imageLayers.back().getName()] = _imageLayers.size() - 1;
            _imageLayers.back()._index = layerIndex++;
        }
        else if(name == "objectgroup")
        {
            _objGroups.push_back(TmxObjectGroup());
            if(!_objGroups.back().parseElement(childElement))
            {
                return false;
            }
            _objGroupsIn[_objGroups.back().getName()] = _objGroups.size() - 1;
            _objGroups.back()._index = layerIndex++;
        }

        childElement = childElement->NextSiblingElement();
    }

    for(auto& layer : _layers)
    {
        for(auto& tile : layer._tiles)
        {
            int tilesetIndex = getTilesetIndexByGid(tile.getGid());

            if(tilesetIndex >= 0)
            {
                tile._id = tile._gid - _tilesets[tilesetIndex].getFirstGid();
                tile._tilesetIndex = tilesetIndex;
            }
        }
    }

	auto propertiesElement = element->FirstChildElement("properties");
	_properties.parseElement(propertiesElement);

    _path = path;

    return true;
}

//=============================================================================

int TmxMap::getTilesetIndexByGid(Uint32 gid) const
{
    for(int i = (int)_tilesets.size() - 1; i >= 0; --i)
    {
        if(gid >= (Uint32)_tilesets[i].getFirstGid())
        {
            return i;
        }
    }

    return -1;
}

//=============================================================================

std::vector<TmxMap::TileCollision> TmxMap::getTileCollisions() const
{
	std::vector<TileCollision> collisions;

	for (int i = 0; i < getTilesetsCount(); ++i)
	{
		auto& tileset = _tilesets[i];

		for (auto& tile : tileset.getTiles())
		{
			auto& objGroup = tile.getObjectGroup();

			if (objGroup.getObjectsCount() > 0)
			{
				TileCollision collision;
				collision.tileset = i;
				collision.id = tile.getId();
				collision.objGroup = objGroup;

				collisions.push_back(collision);
			}
		}
	}

	return collisions;
}

//=============================================================================

std::vector<bool> TmxMap::getTilesWithCollision() const
{
	std::vector<bool> tiles(_width * _height, false);
	std::vector<TileCollision> tileCollisions = getTileCollisions();

	for (auto& layer : _layers)
	{
		for (int i = 0; i < getLayersCount(); ++i)
		{
			int x = i % _width;
			int y = i / _width;

			auto tile = layer.getTile(x, y);

			for (auto tileCollision : tileCollisions)
			{
				if (tile.getId() == tileCollision.id &&
					tile.getTilesetIndex() == tileCollision.tileset)
				{
					tiles[x + y * _width] = true;
					break;
				}
			}
		}
	}

	return tiles;
}

//=============================================================================

NS_KAIRY_END

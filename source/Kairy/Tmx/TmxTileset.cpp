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

#include <Kairy/Tmx/TmxTileset.h>
#include <Kairy/Ext/tinyxml2.h>

NS_KAIRY_BEGIN

TmxTileset::TmxTileset()
    :_firstGid(0)
    ,_tileWidth(0)
    ,_tileHeight(0)
    ,_spacing(0)
    ,_margin(0)
    ,_offsetX(0)
    ,_offsetY(0)
{
}

bool TmxTileset::parseElement(void* p, const std::string& path)
{
    _terrainTypes.clear();
    _tiles.clear();

    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

	_path = "";

    tinyxml2::XMLDocument tsxDocument;

    if(element->Attribute("source"))
    {
        _source = element->Attribute("source");

		std::string tsxPath = path + _source;

        if(tsxDocument.LoadFile(tsxPath.c_str())
                != tinyxml2::XML_NO_ERROR)
        {
            return false;
        }

        element = tsxDocument.FirstChildElement("tileset");

		auto separatorPos = tsxPath.find_last_of("/\\");

		if (separatorPos != std::string::npos)
		{
			_path = tsxPath.substr(0, separatorPos + 1);
		}
    }
    else
    {
        _source = "";
    }

    if(element->Attribute("name"))
    {
        _name = element->Attribute("name");
    }
    else
    {
        _name = "";
    }

    _firstGid = 1;
    _tileWidth = 0;
    _tileHeight = 0;
    _spacing = 0;
    _margin = 0;
    _offsetX = 0;
    _offsetY = 0;
    _tileCount = 0;

    element->QueryIntAttribute("firstgid", &_firstGid);
    element->QueryIntAttribute("tilewidth", &_tileWidth);
    element->QueryIntAttribute("tileheight", &_tileHeight);
    element->QueryIntAttribute("spacing", &_spacing);
    element->QueryIntAttribute("margin", &_margin);
    element->QueryIntAttribute("tilecount", &_tileCount);

    auto propertiesElement = element->FirstChildElement("properties");
    auto imageElement = element->FirstChildElement("image");
    auto terrainTypesElement = element->FirstChildElement("terraintypes");
    auto tileElement = element->FirstChildElement("tile");
    auto tileOffsetElement = element->FirstChildElement("tileoffset");

    if(tileOffsetElement)
    {
        tileOffsetElement->QueryIntAttribute("x", &_offsetX);
        tileOffsetElement->QueryIntAttribute("y", &_offsetY);
    }

    _image.parseElement(imageElement);
    _properties.parseElement(propertiesElement);

    while(tileElement)
    {
        _tiles.push_back(TmxTilesetTile());
        _tiles.back().parseElement(tileElement);

        tileElement = tileElement->NextSiblingElement("tile");
    }

    if(terrainTypesElement)
    {
        auto terrainTypeElement = terrainTypesElement->FirstChildElement("terrain");

        while(terrainTypeElement)
        {
            _terrainTypes.push_back(TmxTerrainType());
            _terrainTypes.back().parseElement(terrainTypeElement);

            terrainTypeElement = terrainTypeElement->NextSiblingElement("terraintype");
        }
    }

    return true;
}

NS_KAIRY_END

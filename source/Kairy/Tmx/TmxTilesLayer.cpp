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

#include <Kairy/Tmx/TmxTilesLayer.h>
#include <Kairy/Ext/tinyxml2.h>
#include <Kairy/Ext/base64.h>
#include <Kairy/Util/Endian.h>
#include <Kairy/Util/StringTransform.h>
#include <Kairy/Ext/miniz.h>

NS_KAIRY_BEGIN

//=============================================================================

TmxTilesLayer::TmxTilesLayer()
    :_encoding(Encoding::Xml)
    ,_compression(Compression::None)
    ,_index(-1)
    ,_x(0)
    ,_y(0)
    ,_width(0)
    ,_height(0)
    ,_opacity(1.0f)
    ,_visible(true)
{
}

//=============================================================================

 TmxMapTile TmxTilesLayer::getTile(int x, int y) const
 {
	 if (x >= 0 && y >= 0 && x < _width && y < _height)
		 return _tiles[x + y * _width];
	 return TmxMapTile();
 }

 //=============================================================================

 bool TmxTilesLayer::parseElement(void* p)
{
    _tiles.clear();

    _x = 0;
    _y = 0;
    _width = 0;
    _height = 0;
    _opacity = 1.0f;
    _visible = true;
    _index = -1;

    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    if(element->Attribute("name"))
    {
        _name = element->Attribute("name");
    }
    else
    {
        _name = "";
    }

    element->QueryIntAttribute("x", &_x);
    element->QueryIntAttribute("y", &_y);
    element->QueryIntAttribute("width", &_width);
    element->QueryIntAttribute("height", &_height);
    element->QueryFloatAttribute("opacity", &_opacity);
    element->QueryBoolAttribute("visible", &_visible);

	auto propertiesElement = element->FirstChildElement("properties");
	_properties.parseElement(propertiesElement);

    auto dataElement = element->FirstChildElement("data");

    if(!dataElement)
    {
        return false;
    }

    if(dataElement->Attribute("encoding"))
    {
        std::string encodingStr = dataElement->Attribute("encoding");
        if(encodingStr == "base64")
        {
            _encoding = Encoding::Base64;
        }
        else if(encodingStr == "csv")
        {
            _encoding = Encoding::Csv;
        }
        else
        {
            _encoding = Encoding::Xml;
        }
    }
    else
    {
        _encoding = Encoding::Xml;
    }

    if(dataElement->Attribute("compression"))
    {
        std::string compressionStr = dataElement->Attribute("compression");

        if(compressionStr == "zlib")
        {
            _compression = Compression::Zlib;
        }
        else if(compressionStr == "gzip")
        {
            _compression = Compression::Gzip;
        }
        else
        {
            _compression = Compression::None;
        }
    }
    else
    {
        _compression = Compression::None;
    }

    if(_encoding == Encoding::Base64)
    {
        return parseBase64Data(dataElement);
    }
    else if(_encoding == Encoding::Csv)
    {
        return parseCsv(dataElement);
    }
    else
    {
        return parseXmlData(dataElement);
    }
}

//=============================================================================

bool TmxTilesLayer::parseXmlData(void* p)
{
    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    auto tileElement = element->FirstChildElement("tile");

    while(tileElement)
    {
        Uint32 gid = 0;
        tileElement->QueryUnsignedAttribute("gid", &gid);

        _tiles.push_back(TmxMapTile(gid));

        tileElement = tileElement->NextSiblingElement("tile");
    }

    return true;
}

//=============================================================================

bool TmxTilesLayer::parseBase64Data(void* p)
{
    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element || !element->GetText())
    {
        return false;
    }

    std::string rawData = element->GetText();
    util::string_remove(rawData, "\n\t ");
    std::string decData = base64_decode(rawData);
    std::string clearData;

    if(_compression == Compression::None)
    {
        clearData = decData;
    }
    else if(_compression == Compression::Zlib)
    {
		uLongf outlen = _width * _height * 4;
		clearData.resize(outlen);
		uncompress((Bytef*)&clearData[0], &outlen,
			(const Bytef*)decData.data(), decData.size());
    }
	else
	{
		z_stream z;

		memset(&z, 0, sizeof(z_stream));

		uLongf outlen = _width * _height * 4;
		clearData.resize(outlen);

		z.next_in = (Bytef*)decData.data();
		z.avail_in = decData.size();
		z.next_out = (Bytef*)&clearData[0];
		z.avail_out = clearData.size();

		int ret = inflateInit2(&z, 15 + 32);

		if (ret != Z_OK)
		{
			return false;
		}

		ret = inflate(&z, Z_SYNC_FLUSH);
		
		inflateEnd(&z);

		if (ret != Z_OK && ret != Z_STREAM_END)
		{	
			return false;
		}
	}

	decData = "";

    Uint32 ints = clearData.size() / 4;

    for(Uint32 i = 0; i < ints; ++i)
    {
        Uint32 gid = util::bytesToUintLE((byte*)&clearData[i * 4]);
        _tiles.push_back(TmxMapTile(gid));
    }

    return true;
}

//=============================================================================

bool TmxTilesLayer::parseCsv(void* p)
{
    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element || !element->GetText())
    {
        return false;
    }

    std::string rawData = element->GetText();
    util::string_remove(rawData, "\n\t ");

    std::stringstream ss(rawData);
	rawData = "";
    std::string gid;

    while(std::getline(ss, gid, ','))
    {
        _tiles.push_back(TmxMapTile(atoi(gid.c_str())));
    }

    return true;
}

//=============================================================================

NS_KAIRY_END

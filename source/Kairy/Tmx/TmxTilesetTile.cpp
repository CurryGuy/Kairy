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

#include <Kairy/Tmx/TmxTilesetTile.h>
#include <Kairy/Ext/tinyxml2.h>

NS_KAIRY_BEGIN

bool TmxTilesetTile::parseElement(void* p)
{
    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    if(element->Attribute("terrain"))
    {
        _terrain = element->Attribute("terrain");
    }
    else
    {
        _terrain = "";
    }

    _id = -1;
    _probability = 0.0f;

    element->QueryIntAttribute("id", &_id);
    element->QueryFloatAttribute("probability", &_probability);

    auto propertiesElement = element->FirstChildElement("properties");
    auto imageElement = element->FirstChildElement("image");
    auto animationElement = element->FirstChildElement("animation");
    auto objectGroupElement = element->FirstChildElement("objectgroup");

    _image.parseElement(imageElement);
    _animation.parseElement(animationElement);
    _properties.parseElement(propertiesElement);
    _objectGroup.parseElement(objectGroupElement);

    return true;
}

NS_KAIRY_END

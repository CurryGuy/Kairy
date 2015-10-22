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

#include <Kairy/Tmx/TmxImageLayer.h>
#include <Kairy/Ext/tinyxml2.h>
#include <Kairy/Util/Clamp.h>

NS_KAIRY_BEGIN

//=============================================================================

TmxImageLayer::TmxImageLayer(void)
    :_index(-1)
    ,_x(0)
    ,_y(0)
    ,_width(0)
    ,_height(0)
    ,_opacity(1.0f)
    ,_visible(true)
{
}

//=============================================================================

bool TmxImageLayer::parseElement(void* p)
{
    auto element = static_cast<tinyxml2::XMLElement*>(p);

    _index = -1;
    _x = 0;
    _y = 0;
    _width = 0;
    _height = 0;
    _opacity = 1.0f;
    _visible = true;
    _properties.clear();

    if(!element)
    {
        return false;
    }

    auto imageElement = element->FirstChildElement("image");
    auto propertiesElement = element->FirstChildElement("properties");

    _image.parseElement(imageElement);
    _properties.parseElement(propertiesElement);

    element->QueryIntAttribute("x", &_x);
    element->QueryIntAttribute("y", &_y);
    element->QueryIntAttribute("width", &_width);
    element->QueryIntAttribute("height", &_height);
    element->QueryBoolAttribute("visible", &_visible);
    element->QueryFloatAttribute("opacity", &_opacity);

    _opacity = util::clamp(_opacity, 0.0f, 1.0f);

    return true;
}

//=============================================================================

NS_KAIRY_END

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

#include <Kairy/Tmx/TmxObject.h>
#include <Kairy/Ext/tinyxml2.h>

NS_KAIRY_BEGIN

TmxObject::TmxObject()
:_id(0)
,_x(0)
,_y(0)
,_width(0)
,_height(0)
,_visible(true)
,_rotation(0.0f)
,_shape(Shape::Rectangle)
{
}

bool TmxObject::parseElement(void* p)
{
    _id = 0;
    _x = 0;
    _y = 0;
    _width = 0;
    _height = 0;
    _rotation = 0.0f;
    _visible = true;
    _gid = 0;
    _shape = Shape::Rectangle;
    _name = "";
    _type = "";
    _properties.clear();

    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    if(element->Attribute("name"))
    {
        _name = element->Attribute("name");
    }

    if(element->Attribute("type"))
    {
        _type = element->Attribute("type");
    }

    element->QueryIntAttribute("id", &_id);
    element->QueryIntAttribute("x", &_x);
    element->QueryIntAttribute("y", &_y);
    element->QueryIntAttribute("width", &_width);
    element->QueryIntAttribute("height", &_height);
    element->QueryFloatAttribute("rotation", &_rotation);
    element->QueryBoolAttribute("visible", &_visible);
    element->QueryUnsignedAttribute("gid", &_gid);

    auto propertiesElement = element->FirstChildElement("properties");
    auto imageElement = element->FirstChildElement("image");
    auto ellipseElement = element->FirstChildElement("ellipse");
    auto polygonElement = element->FirstChildElement("polygon");
    auto polylineElement = element->FirstChildElement("polyline");

    _properties.parseElement(propertiesElement);
    _image.parseElement(imageElement);

    _ellipse = TmxEllipse(_x, _y, _width, _height);
    _polygon.parseElement(polygonElement);
    _polyline.parseElement(polylineElement);

    if(ellipseElement)
    {
        _shape = Shape::Ellipse;
    }
    else if(polygonElement)
    {
        _shape = Shape::Polygon;
    }
    else if(polylineElement)
    {
        _shape = Shape::Polyline;
    }

    return true;
}

NS_KAIRY_END

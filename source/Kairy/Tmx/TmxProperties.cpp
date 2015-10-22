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

#include <Kairy/Tmx/TmxProperties.h>
#include <Kairy/Ext/tinyxml2.h>

NS_KAIRY_BEGIN

//=============================================================================

bool TmxProperties::hasProperty(const std::string& name) const
{
    return _prop.find(name) != _prop.end();
}

//=============================================================================

Value TmxProperties::getProperty(const std::string& name) const
{
    auto it = _prop.find(name);
    if(it != _prop.end())
        return it->second;
    return Value();
}

//=============================================================================

void TmxProperties::addProperty(const std::string& name, const std::string& val)
{
    if(!hasProperty(name))
    {
        _prop[name] = val;
    }
}

//=============================================================================

bool TmxProperties::parseElement(void* p)
{
    clear();

    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    auto propertyElement = element->FirstChildElement("property");

    while(propertyElement)
    {
        if(!propertyElement->Attribute("name") ||
                !propertyElement->Attribute("value"))
        {
            return false;
        }

        addProperty(propertyElement->Attribute("name"),
                propertyElement->Attribute("value"));

        propertyElement = propertyElement->NextSiblingElement("property");
    }

    return true;
}

//=============================================================================

NS_KAIRY_END

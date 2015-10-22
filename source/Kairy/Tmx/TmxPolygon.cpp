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

#include <Kairy/Tmx/TmxPolygon.h>
#include <Kairy/Ext/tinyxml2.h>
#include <regex>

NS_KAIRY_BEGIN

bool TmxPolygon::parseElement(void* p)
{
    _points.clear();

    auto element = static_cast<tinyxml2::XMLElement*>(p);

    if(!element)
    {
        return false;
    }

    auto pointsElement = element->FirstChildElement("points");

    if(!pointsElement)
    {
        return false;
    }

    if(!pointsElement->GetText())
    {
        return false;
    }

    std::string points = pointsElement->GetText();

    std::regex r("(?<x>\\d+),(?<y>\\d+)");

    int x, y;

    std::sregex_iterator it(points.begin(), points.end(), r);
    std::sregex_iterator end;

    for(; it != end; ++it)
    {
        x = 0;
        y = 0;

        std::smatch match = *it;

        x = atoi(match.str(0).c_str());
        y = atoi(match.str(1).c_str());

        _points.push_back(TmxPoint(x, y));
    }

    return true;
}

NS_KAIRY_END

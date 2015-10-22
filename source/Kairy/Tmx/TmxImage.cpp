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

#include <Kairy/Tmx/TmxImage.h>
#include <Kairy/Ext/tinyxml2.h>

NS_KAIRY_BEGIN

//=============================================================================

bool TmxImage::parseElement(void* p)
{
	_width = 0;
	_height = 0;
	_filename = "";
	_format = "";
	_transColor = Color::Transparent;

	auto element = static_cast<tinyxml2::XMLElement*>(p);

	if (!element)
	{
		return false;
	}

	if (!element->Attribute("source"))
	{
		return false;
	}

	_filename = element->Attribute("source");

	if (element->Attribute("format"))
	{
		_format = element->Attribute("format");
	}

	element->QueryIntAttribute("width", &_width);
	element->QueryIntAttribute("height", &_height);

	if (element->Attribute("trans"))
	{
		std::stringstream ss;
		ss << std::hex << element->Attribute("trans");
		Uint32 colorValue = 0;
		ss >> colorValue;
		_transColor = Color(colorValue);
	}

	return true;
}

//=============================================================================

NS_KAIRY_END
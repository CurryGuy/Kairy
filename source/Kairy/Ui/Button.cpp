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

#include <Kairy/Ui/Button.h>

NS_KAIRY_BEGIN

//=============================================================================

Button::Button(void)
	: Control()
{
	_normalImage = std::make_shared<Sprite>();
	_clickedImage = std::make_shared<Sprite>();
	_disabledImage = std::make_shared<Sprite>();

	_normalImage->setName("normal");
	_clickedImage->setName("clicked");
	_disabledImage->setName("disabled");

	_normalImage->setVisible(true);
	_clickedImage->setVisible(false);
	_disabledImage->setVisible(false);

	addChild(_normalImage);
	addChild(_clickedImage);
	addChild(_disabledImage);
}

//=============================================================================

Button::Button(
	const std::string & normalImage,
	const std::string & clickedImage,
	const std::string & disabledImage)
	: Button()
{
	setImages(normalImage, clickedImage, disabledImage);
}

//=============================================================================

bool Button::setImages(
	const std::string & normalImage,
	const std::string & clickedImage,
	const std::string & disabledImage)
{
	if (!_normalImage->loadTexture(normalImage))
	{
		return false;
	}

	if (!_clickedImage->loadTexture(clickedImage.empty() ?
		normalImage : clickedImage))
	{
		return false;
	}

	if (!_disabledImage->loadTexture(disabledImage.empty() ?
		normalImage : disabledImage))
	{
		return false;
	}

	float width = std::max({
		_normalImage->getSize().x,
		_clickedImage->getSize().x,
		_disabledImage->getSize().x
	});

	float height = std::max({
		_normalImage->getSize().y,
		_clickedImage->getSize().y,
		_disabledImage->getSize().y
	});

	setSize(Vec2(width, height));

	return true;
}

//=============================================================================

void Button::onTouchDown(const Vec2 & position, float dt)
{
	Control::onTouchDown(position, dt);

	if (_touched)
	{
		_normalImage->setVisible(false);
		_clickedImage->setVisible(true);
	}
}

//=============================================================================

void Button::onTouchUp(const Vec2 & position, float dt)
{
	Control::onTouchUp(position, dt);

	_normalImage->setVisible(true);
	_clickedImage->setVisible(false);
}

//=============================================================================

void Button::setEnabled(bool enabled)
{
	Control::setEnabled(enabled);

	_disabledImage->setVisible(!enabled);
}

//=============================================================================

void Button::setColor(const Color & color)
{
	Node::setColor(color);

	_normalImage->setColor(color);
	_clickedImage->setColor(color);
	_disabledImage->setColor(color);
}

//=============================================================================

NS_KAIRY_END

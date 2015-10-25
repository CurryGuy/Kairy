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

#include <Kairy/Ui/ImageView.h>

NS_KAIRY_BEGIN

//=============================================================================

std::shared_ptr<ImageView> ImageView::create(void)
{
	return std::make_shared<ImageView>();
}

//=============================================================================

std::shared_ptr<ImageView> ImageView::create(const std::string & image)
{
	auto imageView = std::make_shared<ImageView>();

	if (!imageView || !imageView->setImage(image))
	{
		return nullptr;
	}

	return imageView;
}

//=============================================================================

ImageView::ImageView(void)
	: Control()
{
	_image = std::make_shared<Sprite>();

	_image->setName("image");

	addChild(_image);
}

//=============================================================================

ImageView::ImageView(const std::string & image)
	: ImageView()
{
	setImage(image);
}

//=============================================================================

bool ImageView::setImage(const std::string & image)
{
	return _image->loadTexture(image);
}

//=============================================================================

std::shared_ptr<Sprite> ImageView::getSprite() const
{
	return _image;
}

//=============================================================================

void ImageView::setColor(const Color & color)
{
	Node::setColor(color);

	_image->setColor(color);
}

//=============================================================================

NS_KAIRY_END

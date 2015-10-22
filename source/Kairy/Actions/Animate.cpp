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

#include <Kairy/Actions/Animate.h>
#include <Kairy/Graphics/Sprite.h>

NS_KAIRY_BEGIN

//======================================================================

Animate::Animate(const Animation& animation)
{
	_animation = animation;
}

//======================================================================

void Animate::start(Node* target)
{
	auto sprite = static_cast<Sprite*>(target);

	if (sprite)
	{
		_sprite = sprite;
		_animation.start();

		Action::start(target);
	}
}

//======================================================================

void Animate::stop(void)
{
	_animation.stop();

	Action::stop();
}

//======================================================================

void Animate::update(float dt)
{
	if (_animation.hasPlayedOnce())
	{
		if (_animation.getType() == Animation::Type::PlayOnce ||
			_animation.getType() == Animation::Type::Reverse)
		{
			stop();
			return;
		}
	}

	_animation.update(dt);
	_sprite->setTextureRect(_animation.getCurrentFrame());
}

//======================================================================

NS_KAIRY_END

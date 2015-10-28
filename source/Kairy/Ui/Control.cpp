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

#include <Kairy/Ui/Control.h>

NS_KAIRY_BEGIN

//=============================================================================

Control::Control()
	: Node()
	, _enabled(true)
	, _touched(false)
	, _clickCallback(nullptr)
{
	setTouchEnabled(true);
}

//=============================================================================

void Control::setClickCallback(const ClickCallback& callback)
{
	_clickCallback = callback;
}

//=============================================================================

void Control::setEnabled(bool enabled)
{
	_enabled = enabled;
}

//=============================================================================

bool Control::isEnabled() const
{
	return _enabled;
}

//=============================================================================

bool Control::onTouchDown(const Vec2& position, float dt)
{
	bool ret = Node::onTouchDown(position, dt);

	if (_enabled && ret)
	{
		_touched = true;
	}

	return ret;
}

//=============================================================================

void Control::onTouchUp(const Vec2& position, float dt)
{
	Node::onTouchUp(position, dt);

	if (_enabled && _touched)
	{
		if (getBoundingBox().containsPoint(position))
		{
			if (_clickCallback)
				_clickCallback(dt);
		}

		_touched = false;
	}
}

//=============================================================================

void Control::onTouchMoved(const Vec2& position, float dt)
{
	Node::onTouchMoved(position, dt);
}

//=============================================================================

NS_KAIRY_END

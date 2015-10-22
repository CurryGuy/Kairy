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

#include <Kairy/Graphics/Animation.h>

NS_KAIRY_BEGIN

//=============================================================================

Animation::Animation(void)
	: _type(Type::Loop)
	, _delay(Time::Zero)
	, _animTime(0.0f)
	, _frameIndex(0)
	, _playedOnce(false)
	, _paused(false)
	, _stopped(false)
	, _forward(true)
{
}

//=============================================================================

Animation::Animation(const Rect & region, const Vec2 & frameSize, const Time& delay, Type type)
	: Animation()
{
	_delay = delay;
	_type = type;

	setFrames(region, frameSize);
}

//=============================================================================

Animation::Animation(const std::vector<Rect>& frames, const Time& delay, Type type)
{
	_delay = delay;
	_type = type;
	setFrames(frames);
}

//=============================================================================

void Animation::setFrames(const std::vector<Rect>& frames)
{
	_frames = frames;
}

//=============================================================================

void Animation::setFrames(const Rect & region, const Vec2 & frameSize)
{
	_frames.clear();

	int startX = (int)region.getLeft();
	int startY = (int)region.getTop();
	int endX = (int)region.getRight();
	int endY = (int)region.getBottom();
	int width = (int)frameSize.x;
	int height = (int)frameSize.y;

	for (int y = startY; y < endY; y += height)
	{
		for (int x = startX; x < endX; x += width)
		{
			Rect frame((float)x, (float)y,
				(float)width, (float)height);
			_frames.push_back(frame);
		}
	}
}

//=============================================================================

int Animation::getFrameIndex() const
{
	switch (_type)
	{
	case Type::Loop:
	case Type::PlayOnce:
		return _frameIndex;
	case Type::PingPong:
		if (_forward)
			return _frameIndex;
		else
			return getFramesCount() - 1 - _frameIndex;
	case Type::Reverse:
	case Type::ReverseLoop:
		return getFramesCount() - 1 - _frameIndex;
	default:
		return -1;
	}
}

//=============================================================================

Rect Animation::getCurrentFrame() const
{
	int index = getFrameIndex();

	if (index < 0 || index >= getFramesCount())
		return Rect();

	return _frames[getFrameIndex()];
}

//=============================================================================

Rect Animation::getFrame(int index) const
{
	if (index < 0 || index >= getFramesCount())
		return Rect();

	return _frames[index];
}

//=============================================================================

void Animation::pause()
{
	if (!_paused)
	{
		_paused = true;
	}
}

//=============================================================================

void Animation::stop()
{
	if (!_stopped)
	{
		_stopped = true;
		_paused = false;
		_forward = true;
		_playedOnce = false;
		_frameIndex = 0;
		_animTime = 0.0f;
	}
}

//=============================================================================

void Animation::start()
{
	_paused = false;
	_stopped = false;
}

//=============================================================================

void Animation::update(float dt)
{
	if ((_type == Type::PlayOnce || _type == Type::Reverse) &&
		_playedOnce)
	{
		return;
	}

	if (_paused || _stopped)
	{
		return;
	}

	_animTime += dt;

	if (_animTime >= _delay.asSeconds())
	{
		_frameIndex++;

		if (_frameIndex == (int)_frames.size())
		{
			_playedOnce = true;
			_frameIndex = 0;

			if (_type == Type::PingPong)
				_forward = !_forward;
		}

		_animTime = 0.0f;
	}
}

//=============================================================================

NS_KAIRY_END

#include "Timer.h"
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

//=============================================================================

Timer::Timer(void)
	: _autoRestart(true)
	, _enabled(true)
	, _start(Time::getCurrentTime())
	, _interval(Time::seconds(0))
	, _callback(nullptr)
{
}

//=============================================================================

inline void Timer::update(float dt)
{
	if (getElapsedTime() >= _interval && _enabled)
	{
		if (_callback)
			_callback(dt);
		if (_autoRestart)
			restart();
	}
}

//=============================================================================

inline Time Timer::restart()
{
	Time elapsed = getElapsedTime();
	_start = Time::getCurrentTime();
	return elapsed;
}

//=============================================================================

inline Time Timer::getStartingTime() const
{
	return _start;
}

//=============================================================================

inline Time Timer::getElapsedTime() const
{
	return Time::getCurrentTime() - _start;
}

//=============================================================================

inline Time Timer::getTimeTo(const Time & time)
{
	if (time < _start)
		return Time::seconds(0);
	return time - _start;
}

//=============================================================================

inline void Timer::setInterval(const Time & interval)
{
	_interval = interval;
}

//=============================================================================

inline void Timer::setCallback(const Callback & callback)
{
	_callback = callback;
}

//=============================================================================

inline void Timer::setCallback(const Callback & callback, const Time & interval)
{
	_callback = callback;
	_interval = interval;
}

//=============================================================================

inline void Timer::setEnabled(bool enabled)
{
	_enabled = enabled;
}

//=============================================================================

inline void Timer::enable()
{
	_enabled = true;
}

//=============================================================================

inline void Timer::disable()
{
	_enabled = false;
}

//=============================================================================

inline bool Timer::isEnabled() const
{
	return _enabled;
}

//=============================================================================

inline void Timer::setAutoRestart(bool autoRestart)
{
	_autoRestart = autoRestart;
}

//=============================================================================

inline bool Timer::getAutoRestart() const
{
	return _autoRestart;
}

//=============================================================================

inline bool Timer::restartIfElapsed(const Time & elapsed)
{
	bool ret = getElapsedTime() >= elapsed;
	if (ret)
		restart();
	return ret;
}

//=============================================================================

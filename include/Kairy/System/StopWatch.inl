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

inline StopWatch::StopWatch(void)
	: _start(Time::getCurrentTime())
	, _time(Time::Zero)
	, _running(false)
{
}

//=============================================================================

inline Time StopWatch::getElapsedTime() const
{
	if (_running)
	{
		return _time + (Time::getCurrentTime() - _start);
	}
	else
	{
		return _time;
	}
}

//=============================================================================

inline bool StopWatch::isRunning() const
{
	return _running;
}

//=============================================================================

inline void StopWatch::start()
{
	if (!_running)
	{
		_running = true;
		_start = Time::getCurrentTime();
	}
}

//=============================================================================

inline void StopWatch::stop()
{
	if (_running)
	{
		_running = false;
		_time = _time + (Time::getCurrentTime() - _start);
	}
}

//=============================================================================

inline Time StopWatch::reset()
{
	Time elapsed = getElapsedTime();
	_time = Time::Zero;
	_running = false;
	return elapsed;
}

//=============================================================================

inline Time StopWatch::restart()
{
	Time elapsed = reset();
	start();
	return elapsed;
}

//=============================================================================

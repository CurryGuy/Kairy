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

inline Time Time::seconds(float seconds)
{
	return Time(Uint64(seconds * 1000000000.0));
}

//=============================================================================

inline Time Time::milliseconds(Uint64 ms)
{
	return Time(ms * 1000000);
}

//=============================================================================

inline Time Time::microseconds(Uint64 micro)
{
	return Time(micro * 1000);
}

//=============================================================================

inline Time Time::nanoseconds(Uint64 nano)
{
	return Time(nano);
}

//=============================================================================

inline Time::Time()
	: _nano(0)
{
}

//=============================================================================

inline float Time::asSeconds() const
{
	return float(_nano / 1000000000.0);
}

//=============================================================================

inline Uint64 Time::asMilliseconds() const
{
	return Uint64(_nano / 1000000);
}

//=============================================================================

inline Uint64 Time::asMicroseconds() const
{
	return Uint64(_nano / 1000);
}

//=============================================================================

inline Uint64 Time::asNanoseconds() const
{
	return _nano;
}

//=============================================================================

inline bool Time::equals(const Time & other) const
{
	return _nano == other._nano;
}

//=============================================================================

inline bool Time::operator==(const Time & other) const
{
	return equals(other);
}

//=============================================================================

inline bool Time::operator!=(const Time & other) const
{
	return !equals(other);
}

//=============================================================================

inline bool Time::operator<(const Time & other) const
{
	return _nano < other._nano;
}

//=============================================================================

inline bool Time::operator>(const Time & other) const
{
	return _nano > other._nano;
}

//=============================================================================

inline bool Time::operator<=(const Time & other) const
{
	return _nano <= other._nano;
}

//=============================================================================

inline bool Time::operator>=(const Time & other) const
{
	return _nano >= other._nano;
}

//=============================================================================

inline Time Time::operator+(const Time & other) const
{
	return Time(_nano + other._nano);
}

//=============================================================================

inline Time Time::operator-(const Time & other) const
{
	return Time(_nano - other._nano);
}

//=============================================================================

inline Time::Time(Uint64 nano)
	: _nano(nano)
{
}

//=============================================================================

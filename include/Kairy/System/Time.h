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

#ifndef KAIRY_SYSTEM_TIME_H_INCLUDED
#define KAIRY_SYSTEM_TIME_H_INCLUDED

#include <Kairy/Common.h>

NS_KAIRY_BEGIN

class Time
{
public:
	static const Time Zero;

	static Time getCurrentTime();

	inline static Time seconds(float seconds);
	inline static Time milliseconds(Uint64 ms);
	inline static Time microseconds(Uint64 micro);
	inline static Time nanoseconds(Uint64 nano);

    inline Time();

    inline float asSeconds() const;

    inline Uint64 asMilliseconds() const;

    inline Uint64 asMicroseconds() const;

    inline Uint64 asNanoseconds() const;

    inline bool equals(const Time& other) const;

    inline bool operator==(const Time& other) const;
    inline bool operator!=(const Time& other) const;
    inline bool operator<(const Time& other) const;
    inline bool operator>(const Time& other) const;
    inline bool operator<=(const Time& other) const;
    inline bool operator>=(const Time& other) const;
    inline Time operator+(const Time& other) const;
    inline Time operator-(const Time& other) const;

private:
	inline Time(Uint64 nano);

	Uint64 _nano;
};

#include "Time.inl"

NS_KAIRY_END

#endif // KAIRY_SYSTEM_TIME_H_INCLUDED

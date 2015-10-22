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

#ifndef KAIRY_SYSTEM_RANDOM_H_INCLUDED
#define KAIRY_SYSTEM_RANDOM_H_INCLUDED

#include <Kairy/Common.h>
#include <Kairy/Ext/SFMT/SFMT.h>

NS_KAIRY_BEGIN

class Random
{
public:

	static Random* getInstance();

	Random(void);

	Random(Uint32 seed);

	void setSeed(Uint32 seed);

	inline Uint32 getSeed() const { return _seed; }

	int nextInt() const;

	int nextInt(int max) const;

	int nextInt(int min, int max) const;

	Uint32 nextUint() const;

	Uint32 nextUint(Uint32 max) const;

	Uint32 nextUint(Uint32 min, Uint32 max) const;

	Uint64 nextUint64() const;

	Uint64 nextUint64(Uint64 min, Uint64 max) const;

	float nextFloat() const;

	double nextDouble() const;

	bool nextBoolean() const;

private:
	Uint32 _seed;
	mutable sfmt_t _sfmt;
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_RANDOM_H_INCLUDED

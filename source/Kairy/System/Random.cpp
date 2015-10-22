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

#include <Kairy/System/Random.h>
#include <chrono>

NS_KAIRY_BEGIN

//=============================================================================

static std::unique_ptr<Random> s_sharedRandom = nullptr;

//=============================================================================

Random * Random::getInstance()
{
	if (!s_sharedRandom)
	{
		s_sharedRandom.reset(new Random());
	}

	return s_sharedRandom.get();
}

//=============================================================================

Random::Random(void)
{
	setSeed((Uint32)std::chrono::system_clock::now().time_since_epoch().count());
}

//=============================================================================

Random::Random(Uint32 seed)
{
	setSeed(seed);
}

//=============================================================================

void Random::setSeed(Uint32 seed)
{
	sfmt_init_gen_rand(&_sfmt, seed);
	_seed = seed;
}

//=============================================================================

int Random::nextInt() const
{
	return int(sfmt_genrand_uint32(&_sfmt) & ~(1 << 31));
}

//=============================================================================

int Random::nextInt(int max) const
{
	return nextInt() % max;
}

//=============================================================================

int Random::nextInt(int min, int max) const
{
	return nextInt() % (max - 1 - min) + min;
}

//=============================================================================

Uint32 Random::nextUint() const
{
	return sfmt_genrand_uint32(&_sfmt);
}

//=============================================================================

Uint32 Random::nextUint(Uint32 max) const
{
	return sfmt_genrand_uint32(&_sfmt) % max;
}

//=============================================================================

Uint32 Random::nextUint(Uint32 min, Uint32 max) const
{
	return sfmt_genrand_uint32(&_sfmt) % (max - 1 - min) + min;
}

//=============================================================================

Uint64 Random::nextUint64() const
{
	return sfmt_genrand_uint64(&_sfmt);
}

//=============================================================================

Uint64 Random::nextUint64(Uint64 min, Uint64 max) const
{
	return sfmt_genrand_uint64(&_sfmt) % (max - 1 - min) + min;
}

//=============================================================================

float Random::nextFloat() const
{
	return (float)sfmt_genrand_real1(&_sfmt);
}

//=============================================================================

double Random::nextDouble() const
{
	return sfmt_genrand_real1(&_sfmt);
}

//=============================================================================

bool Random::nextBoolean() const
{
	return nextInt(2) == 0;
}

//=============================================================================

NS_KAIRY_END

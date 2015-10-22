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

#ifndef KAIRY_SYSTEM_THREAD_H_INCLUDED
#define KAIRY_SYSTEM_THREAD_H_INCLUDED

#include "Time.h"

#ifndef _3DS
#include <thread>
#endif // _3DS

NS_KAIRY_BEGIN

class Thread
{
public:
	enum class Priority
	{
		Hightest = 0x00,
		High = 0x10,
		Default = 0x18,
		Low = 0x30,
		Lowest = 0x3F
	};

	enum class CpuCore
	{
		Default = -2,
		Any = -1,
		AppCore = 0,
		SysCore = 1
	};

	typedef std::function<void(void*)> Callback;

	Thread(void);

	Thread(const Callback& callback);

	virtual ~Thread();

    bool start(void* userdata,
		Priority priority = Priority::Default,
		CpuCore core = CpuCore::Default);

	inline bool start() { return start(nullptr); }

	inline Priority getPriority() const { return _priority; }

	inline CpuCore getCore() const { return _core; }

	void setPriority(Priority priority);

    void join();

	static void sleep(const Time& time);

private:
	Callback _callback;
	Priority _priority;
	CpuCore _core;

#ifdef _3DS
	
	static void svcThreadFunc(void*);
	
	enum { STACK_SIZE = 1024 * 2 };
	
	void* _userdata;

	Handle _handle;
	u32* _stack;
#else
	std::thread _thread;
#endif // _3DS
};

NS_KAIRY_END

#endif // KAIRY_SYSTEM_THREAD_H_INCLUDED

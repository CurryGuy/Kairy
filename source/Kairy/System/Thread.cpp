#include <Kairy/System/Thread.h>

#ifdef _3DS
#include <malloc.h>
#endif // _3DS

NS_KAIRY_BEGIN

//=============================================================================

Thread::Thread(void)
{
	_callback = nullptr;
	_priority = Priority::Default;
	_core = CpuCore::Default;

#ifdef _3DS
	_stack = (u32*)memalign(32, sizeof(u32) * STACK_SIZE);
	_handle = 0;
#endif // _3DS
}

//=============================================================================

Thread::Thread(const Callback & callback)
	: Thread()
{
	_callback = callback;
}

//=============================================================================

Thread::~Thread()
{
	join();
#ifdef _3DS
	free(_stack);
#endif // _3DS
}

//=============================================================================

bool Thread::start(void* userdata, Priority priority, CpuCore core)
{
	join();
	
	if (!_callback)
		return false;

#ifdef _3DS	
	_userdata = userdata;
	_priority = priority;
	_core = core;

	svcCreateThread(&_handle, &Thread::svcThreadFunc,
		(u32)this, &_stack[STACK_SIZE/sizeof(u32)], (int)priority, (int)core);
#else
	_thread = std::thread(_callback, userdata);
#endif // _3DS

	return true;
}

//=============================================================================

void Thread::setPriority(Priority priority)
{
#ifdef _3DS
	if (_handle != 0)
	{
		svcSetThreadPriority(_handle, (int)priority);
		_priority = priority;
	}
#else
	(void)priority;
#endif // _3DS
}

//=============================================================================

void Thread::join()
{	
#ifdef _3DS
	if(_handle != 0)
	{
		svcWaitSynchronization(_handle, U64_MAX);
		svcCloseHandle(_handle);
	}
#else
	if (_thread.joinable())
	{
		_thread.join();
	}
#endif // _3DS
}

//=============================================================================

void Thread::sleep(const Time& time)
{
#ifdef _3DS
	svcSleepThread(time.asNanoseconds());
#else
	std::this_thread::sleep_for(
		std::chrono::nanoseconds(time.asNanoseconds()));
#endif // _3DS
}

//=============================================================================

#ifdef _3DS
void Thread::svcThreadFunc(void* userdata)
{
	auto thread = static_cast<Thread*>(userdata);
	
	if(thread && thread->_callback)
	{
		thread->_callback(thread->_userdata);
	}
	
	svcExitThread();
}
#endif // _3DS

//=============================================================================

NS_KAIRY_END

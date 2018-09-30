#include <infra/Config.h>
#include <infra/Thread.h>

#if !defined(WIN32)
#    include <pthread.h>
#endif

#ifdef ANDROID
#    include <sys/time.h>
#    include <sys/resource.h>
#    ifndef ANDROID_PRIORITY_URGENT_DISPLAY
#        define ANDROID_PRIORITY_URGENT_DISPLAY -8  // see include/system/thread_defs.h
#    endif
#    ifndef ANDROID_PRIORITY_DISPLAY
#        define ANDROID_PRIORITY_DISPLAY -4  // see include/system/thread_defs.h
#    endif
#    ifndef ANDROID_PRIORITY_NORMAL
#        define ANDROID_PRIORITY_NORMAL 0 // see include/system/thread_defs.h
#    endif
#elif defined(__linux__)
// There is no glibc wrapper for gettid on linux so we need to syscall it.
#    include <unistd.h>
#    include <sys/syscall.h>
#    define gettid() syscall(SYS_gettid)
#endif

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif

namespace mud
{
	void set_thread_name(const char* name)
	{
#if defined(__linux__)
		pthread_setname_np(pthread_self(), name);
#elif defined(__APPLE__)
		pthread_setname_np(name);
#else
		// TODO: implement setting thread name on WIN32 
#endif
	}

	void set_thread_priority(ThreadPriority priority)
	{
#ifdef ANDROID
		int androidPriority = 0;
		switch(priority) {
		case Priority::NORMAL:
			androidPriority = ANDROID_PRIORITY_NORMAL;
			break;
		case Priority::DISPLAY:
			androidPriority = ANDROID_PRIORITY_DISPLAY;
			break;
		case Priority::URGENT_DISPLAY:
			androidPriority = ANDROID_PRIORITY_URGENT_DISPLAY;
			break;
		}
		setpriority(PRIO_PROCESS, 0, androidPriority);
#endif
		//SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
	}

	void set_thread_affinity(uint32_t mask)
	{
#if defined(__linux__)
		int bit = 0;
		cpu_set_t set;
		CPU_ZERO(&set);
		while(mask) {
			if(mask & 1) {
				CPU_SET(bit, &set);
			}
			bit++;
			mask >>= 1;
		}
		sched_setaffinity(gettid(), sizeof(set), &set);
#else
		//SetThreadAffinityMask(GetCurrentThread(), mask);
#endif
	}
}

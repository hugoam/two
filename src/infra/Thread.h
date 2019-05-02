#pragma once

#include <infra/Forward.h>

#include <stl/stddef.h>
#include <stdint.h>

namespace two
{
	export_ TWO_INFRA_EXPORT void set_thread_name(const char* name);

	export_ enum class ThreadPriority
	{
		Normal,
		Display,
		UrgentDisplay
	};

	export_ TWO_INFRA_EXPORT void set_thread_priority(ThreadPriority priority);
	export_ TWO_INFRA_EXPORT void set_thread_affinity(uint32_t mask);
}

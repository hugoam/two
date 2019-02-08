#ifndef USE_STL
#ifdef MUD_MODULES
module mud.jobs;
#else
#include <stl/vector.hpp>
#include <jobs/Api.h>
#endif

namespace stl
{
	using namespace mud;
	//template class MUD_JOBS_EXPORT vector<JobSystem::ThreadState>;
}
#endif

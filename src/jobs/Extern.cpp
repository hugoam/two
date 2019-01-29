#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#include <jobs/Extern.h>
#endif

using namespace mud;
namespace tinystl
{
	//template class MUD_JOBS_EXPORT vector<JobSystem::ThreadState>;
}

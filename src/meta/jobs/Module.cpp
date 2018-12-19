#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#include <meta/jobs/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/jobs/Convert.h>
#endif
#define MUD_JOBS_REFLECTION_IMPL
#include <meta/jobs/Meta.h>

namespace mud
{
	mud_jobs::mud_jobs()
		: Module("mud::jobs")
	{
        // ensure dependencies are instantiated

        // setup reflection meta data
		mud_jobs_meta(*this);
	}
}

#ifdef MUD_JOBS_MODULE
extern "C"
Module& getModule()
{
	return mud_jobs::m();
}
#endif

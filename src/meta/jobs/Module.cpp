#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#include <meta/infra/Module.h>
#include <meta/jobs/Module.h>
#endif

#include <jobs/Api.h>

#ifndef MUD_MODULES
#include <meta/jobs/Convert.h>
#endif
#define MUD_JOBS_REFLECTION_IMPL
#include <meta/jobs/Meta.h>

namespace mud
{
	mud_jobs::mud_jobs()
		: Module("mud::jobs", { &mud_infra::m() })
	{
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

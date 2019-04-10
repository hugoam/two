#include <mud/jobs.refl.h>
#include <mud/jobs.h>
#include <mud/infra.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.jobs;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;


namespace mud
{
	void mud_jobs_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::JobSystem
	{
		Type& t = type<mud::JobSystem>();
		static Meta meta = { t, &namspc({ "mud" }), "JobSystem", sizeof(mud::JobSystem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::JobSystem>());
	}
}

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

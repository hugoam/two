#include <mud/jobs.refl.h>
#include <mud/jobs.h>
#include <mud/infra.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#endif


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
		static Meta meta = { type<mud::JobSystem>(), &namspc({ "mud" }), "JobSystem", sizeof(mud::JobSystem), TypeClass::Object };
		static Class cls = { type<mud::JobSystem>(),
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::JobSystem>();
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

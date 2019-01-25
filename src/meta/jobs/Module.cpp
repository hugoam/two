#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/jobs/Module.h>
#include <meta/jobs/Convert.h>
#endif

#include <jobs/Api.h>

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
		static Class cls = { t,
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

#include <two/infra.h>

module;
module two.jobs.meta;

using namespace two;


namespace two
{
	void two_jobs_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::JobSystem
	{
		Type& t = type<two::JobSystem>();
		static Meta meta = { t, &namspc({ "two" }), "JobSystem", sizeof(two::JobSystem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::JobSystem>());
	}
}

namespace two
{
	two_jobs::two_jobs()
		: Module("two::jobs", { &two_infra::m(), &two_type::m() })
	{
		// setup reflection meta data
		two_jobs_meta(*this);
	}
}

#ifdef TWO_JOBS_MODULE
extern "C"
Module& getModule()
{
	return two_jobs::m();
}
#endif

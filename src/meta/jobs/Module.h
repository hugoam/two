#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#endif

#include <jobs/Forward.h>
#include <jobs/Types.h>
#include <jobs/Api.h>

#include <meta/jobs/Convert.h>

#ifndef MUD_JOBS_REFL_EXPORT
#define MUD_JOBS_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_JOBS_REFL_EXPORT mud_jobs : public Module
	{
	private:
		mud_jobs();
		
	public:
		static mud_jobs& m() { static mud_jobs instance; return instance; }
	};
}

#ifdef MUD_JOBS_MODULE
extern "C"
MUD_JOBS_REFL_EXPORT Module& getModule();
#endif

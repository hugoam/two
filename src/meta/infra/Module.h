#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#endif

#include <infra/Forward.h>
#include <infra/Types.h>
#include <infra/Api.h>

#include <meta/infra/Convert.h>

#ifndef MUD_INFRA_REFL_EXPORT
#define MUD_INFRA_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_INFRA_REFL_EXPORT mud_infra : public Module
	{
	private:
		mud_infra();
		
	public:
		static mud_infra& m() { static mud_infra instance; return instance; }
	};
}

#ifdef MUD_INFRA_MODULE
extern "C"
MUD_INFRA_REFL_EXPORT Module& getModule();
#endif

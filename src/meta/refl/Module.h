#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#endif

#include <refl/Forward.h>
#include <refl/Types.h>
#include <refl/Api.h>

#include <meta/refl/Convert.h>

#ifndef MUD_REFL_REFL_EXPORT
#define MUD_REFL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_REFL_REFL_EXPORT mud_refl : public Module
	{
	private:
		mud_refl();
		
	public:
		static mud_refl& m() { static mud_refl instance; return instance; }
	};
}

#ifdef MUD_REFL_MODULE
extern "C"
MUD_REFL_REFL_EXPORT Module& getModule();
#endif

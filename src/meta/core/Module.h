#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gfx/Module.h>
#include <meta/gfx-ui/Module.h>
#endif

#include <core/Forward.h>
#include <core/Types.h>
#include <core/Api.h>

#include <meta/core/Convert.h>

#ifndef MUD_CORE_REFL_EXPORT
#define MUD_CORE_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_CORE_REFL_EXPORT mud_core : public Module
	{
	private:
		mud_core();
		
	public:
		static mud_core& m() { static mud_core instance; return instance; }
	};
}

#ifdef MUD_CORE_MODULE
extern "C"
MUD_CORE_REFL_EXPORT Module& getModule();
#endif

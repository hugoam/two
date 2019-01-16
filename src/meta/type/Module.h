#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <type/Forward.h>
#include <type/Types.h>

#ifndef MUD_TYPE_REFL_EXPORT
#define MUD_TYPE_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_TYPE_REFL_EXPORT mud_type : public Module
	{
	private:
		mud_type();
		
	public:
		static mud_type& m() { static mud_type instance; return instance; }
	};
}

#ifdef MUD_TYPE_MODULE
extern "C"
MUD_TYPE_REFL_EXPORT Module& getModule();
#endif

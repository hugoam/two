#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <noise/Forward.h>
//#include <noise/Types.h>

#ifndef MUD_NOISE_REFL_EXPORT
#define MUD_NOISE_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_NOISE_REFL_EXPORT mud_noise : public Module
	{
	private:
		mud_noise();
		
	public:
		static mud_noise& m() { static mud_noise instance; return instance; }
	};
}

#ifdef MUD_NOISE_MODULE
extern "C"
MUD_NOISE_REFL_EXPORT Module& getModule();
#endif

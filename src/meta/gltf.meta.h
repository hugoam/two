#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gltf/Forward.h>
//#include <gltf/Types.h>

#ifndef MUD_GLTF_REFL_EXPORT
#define MUD_GLTF_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GLTF_REFL_EXPORT mud_gltf : public mud::Module
	{
	private:
		mud_gltf();
		
	public:
		static mud_gltf& m() { static mud_gltf instance; return instance; }
	};
}

#ifdef MUD_GLTF_MODULE
extern "C"
MUD_GLTF_REFL_EXPORT Module& getModule();
#endif

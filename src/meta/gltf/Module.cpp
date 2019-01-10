#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gltf;
#else
#include <meta/gltf/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/gltf/Convert.h>
#endif
#define MUD_GLTF_REFLECTION_IMPL
#include <meta/gltf/Meta.h>

namespace mud
{
	mud_gltf::mud_gltf()
		: Module("mud::gltf", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_gltf_meta(*this);
	}
}

#ifdef MUD_GLTF_MODULE
extern "C"
Module& getModule()
{
		return mud_gltf::m();
}
#endif

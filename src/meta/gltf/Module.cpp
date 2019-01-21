#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gltf;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/gltf/Module.h>
#include <meta/gltf/Convert.h>
#endif

#include <gltf/Api.h>
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

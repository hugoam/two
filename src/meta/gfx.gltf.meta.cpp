#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-gltf;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gltf.meta.h>
#include <meta/gfx.gltf.meta.h>
#endif

namespace mud
{
	mud_gfx_gltf::mud_gfx_gltf()
		: Module("mud::gfx-gltf", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m(), &mud_gltf::m() })
	{}
}

#ifdef MUD_GFX_GLTF_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_gltf::m();
}
#endif

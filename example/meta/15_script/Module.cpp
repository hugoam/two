#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module ._15_script;
#else
#include <meta/15_script/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/15_script/Convert.h>
#endif
#define _15_SCRIPT_REFLECTION_IMPL
#include <meta/15_script/Meta.h>

	_15_script::_15_script()
		: Module("_15_script")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_pool::m();
        mud_refl::m();
        mud_proto::m();
        mud_tree::m();
        mud_srlz::m();
        mud_math::m();
        mud_geom::m();
        mud_procgen::m();
        mud_lang::m();
        mud_ctx::m();
        mud_ui::m();
        mud_uio::m();
        //mud_snd::m();
        //mud_ctx_glfw::m();
        mud_ui_vg::m();
        mud_bgfx::m();
        mud_gfx::m();
        mud_gfx_pbr::m();
        mud_gfx_obj::m();
        mud_gfx_gltf::m();
        mud_gfx_ui::m();
        mud_tool::m();
        mud_procgen_gfx::m();

        // setup reflection meta data
		_15_script_meta(*this);
	}

#ifdef _15_SCRIPT_MODULE
extern "C"
Module& getModule()
{
	return _15_script::m();
}
#endif

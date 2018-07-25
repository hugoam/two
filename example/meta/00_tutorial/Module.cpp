#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module ._00_tutorial;
#else
#include <meta/00_tutorial/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/00_tutorial/Convert.h>
#endif
#define _00_TUTORIAL_REFLECTION_IMPL
#include <meta/00_tutorial/Meta.h>

	_00_tutorial::_00_tutorial()
		: Module("_00_tutorial")
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
        mud_snd::m();
        mud_ctx_glfw::m();
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
		_00_tutorial_meta(*this);
	}

#ifdef _00_TUTORIAL_MODULE
extern "C"
Module& getModule()
{
	return _00_tutorial::m();
}
#endif

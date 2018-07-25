
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/obj/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/proto/Module.h>
#include <meta/tree/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/procgen/Module.h>
#include <meta/lang/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/snd/Module.h>
#include <meta/ctx-glfw/Module.h>
#include <meta/ui-vg/Module.h>
#include <meta/bgfx/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-obj/Module.h>
#include <meta/gfx-gltf/Module.h>
#include <meta/gfx-ui/Module.h>
#include <meta/tool/Module.h>
#include <meta/procgen-gfx/Module.h>
#endif
        
#include <00_tutorial/Forward.h>
#include <00_tutorial/Types.h>
#include <00_tutorial/Api.h>

#include <meta/00_tutorial/Convert.h>

#ifndef _00_TUTORIAL_REFL_EXPORT
#define _00_TUTORIAL_REFL_EXPORT MUD_IMPORT
#endif

	export_ class _00_TUTORIAL_REFL_EXPORT _00_tutorial : public Module
	{
	private:
		_00_tutorial();

	public:
		static _00_tutorial& m() { static _00_tutorial instance; return instance; }
	};

#ifdef _00_TUTORIAL_MODULE
extern "C"
_00_TUTORIAL_REFL_EXPORT Module& getModule();
#endif

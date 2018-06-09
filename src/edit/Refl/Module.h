
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <srlz/Refl/Module.h>
#include <math/Refl/Module.h>
#include <geom/Refl/Module.h>
#include <lang/Refl/Module.h>
#include <ui/Refl/Module.h>
#include <uio/Refl/Module.h>
#include <gfx/Refl/Module.h>
#include <gfx-pbr/Refl/Module.h>
#endif
        
#include <edit/Forward.h>
#include <edit/Types.h>
#include <edit/Api.h>

#include <edit/Refl/Convert.h>

#ifndef MUD_EDIT_REFL_EXPORT
#define MUD_EDIT_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_EDIT_REFL_EXPORT mudedit : public Module
	{
	private:
		mudedit();

	public:
		static mudedit& m() { static mudedit instance; return instance; }
	};
}

#ifdef MUD_EDIT_MODULE
extern "C"
MUD_EDIT_REFL_EXPORT Module& getModule();
#endif

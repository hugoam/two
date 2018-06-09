
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/lang/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#endif
        
#include <edit/Forward.h>
#include <edit/Types.h>
#include <edit/Api.h>

#include <meta/edit/Convert.h>

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

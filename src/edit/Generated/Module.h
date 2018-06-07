
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <lang/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <gfx-pbr/Generated/Module.h>
#endif
        
#include <edit/Generated/Forward.h>
#include <edit/Generated/Types.h>
#include <edit/Api.h>

#include <edit/Generated/Convert.h>

namespace mud
{
	export_ class MUD_EDIT_EXPORT mudedit : public Module
	{
	private:
		mudedit();

	public:
		static mudedit& m() { static mudedit instance; return instance; }
	};
}

#ifdef MUD_EDIT_MODULE
extern "C"
MUD_EDIT_EXPORT Module& getModule();
#endif

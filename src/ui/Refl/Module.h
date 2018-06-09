
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <srlz/Refl/Module.h>
#include <math/Refl/Module.h>
#include <ctx/Refl/Module.h>
#endif
        
#include <ui/Forward.h>
#include <ui/Types.h>
#include <ui/Api.h>

#include <ui/Refl/Convert.h>

#ifndef MUD_UI_REFL_EXPORT
#define MUD_UI_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UI_REFL_EXPORT mudui : public Module
	{
	private:
		mudui();

	public:
		static mudui& m() { static mudui instance; return instance; }
	};
}

#ifdef MUD_UI_MODULE
extern "C"
MUD_UI_REFL_EXPORT Module& getModule();
#endif

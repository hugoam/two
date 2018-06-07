
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <ctx/Generated/Module.h>
#endif
        
#include <ui/Generated/Forward.h>
#include <ui/Generated/Types.h>
#include <ui/Api.h>

#include <ui/Generated/Convert.h>

namespace mud
{
	export_ class MUD_UI_EXPORT mudui : public Module
	{
	private:
		mudui();

	public:
		static mudui& m() { static mudui instance; return instance; }
	};
}

#ifdef MUD_UI_MODULE
extern "C"
MUD_UI_EXPORT Module& getModule();
#endif

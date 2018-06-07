
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#endif
        
#include <lang/Generated/Forward.h>
#include <lang/Generated/Types.h>
#include <lang/Api.h>

#include <lang/Generated/Convert.h>

namespace mud
{
	export_ class MUD_LANG_EXPORT mudlang : public Module
	{
	private:
		mudlang();

	public:
		static mudlang& m() { static mudlang instance; return instance; }
	};
}

#ifdef MUD_LANG_MODULE
extern "C"
MUD_LANG_EXPORT Module& getModule();
#endif

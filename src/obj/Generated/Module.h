
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#endif
        
#include <obj/Generated/Forward.h>
#include <obj/Generated/Types.h>
#include <obj/Api.h>

#include <obj/Generated/Convert.h>

namespace mud
{
	export_ class MUD_OBJ_EXPORT mudobj : public Module
	{
	private:
		mudobj();

	public:
		static mudobj& m() { static mudobj instance; return instance; }
	};
}

#ifdef MUD_OBJ_MODULE
extern "C"
MUD_OBJ_EXPORT Module& getModule();
#endif

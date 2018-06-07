
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <lang/Generated/Module.h>
#include <ui/Generated/Module.h>
#endif
        
#include <uio/Generated/Forward.h>
#include <uio/Generated/Types.h>
#include <uio/Api.h>

#include <uio/Generated/Convert.h>

namespace mud
{
	export_ class MUD_UIO_EXPORT muduio : public Module
	{
	private:
		muduio();

	public:
		static muduio& m() { static muduio instance; return instance; }
	};
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_EXPORT Module& getModule();
#endif

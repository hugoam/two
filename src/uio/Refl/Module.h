
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <lang/Refl/Module.h>
#include <ui/Refl/Module.h>
#endif
        
#include <uio/Forward.h>
#include <uio/Types.h>
#include <uio/Api.h>

#include <uio/Refl/Convert.h>

#ifndef MUD_UIO_REFL_EXPORT
#define MUD_UIO_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UIO_REFL_EXPORT muduio : public Module
	{
	private:
		muduio();

	public:
		static muduio& m() { static muduio instance; return instance; }
	};
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_REFL_EXPORT Module& getModule();
#endif

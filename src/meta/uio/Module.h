#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <uio/Forward.h>
#include <uio/Types.h>

#ifndef MUD_UIO_REFL_EXPORT
#define MUD_UIO_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UIO_REFL_EXPORT mud_uio : public Module
	{
	private:
		mud_uio();
		
	public:
		static mud_uio& m() { static mud_uio instance; return instance; }
	};
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_REFL_EXPORT Module& getModule();
#endif

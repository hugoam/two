#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <ctx/Forward.h>
//#include <ctx/Types.h>

#ifndef MUD_CTX_REFL_EXPORT
#define MUD_CTX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_CTX_REFL_EXPORT mud_ctx : public Module
	{
	private:
		mud_ctx();
		
	public:
		static mud_ctx& m() { static mud_ctx instance; return instance; }
	};
}

#ifdef MUD_CTX_MODULE
extern "C"
MUD_CTX_REFL_EXPORT Module& getModule();
#endif

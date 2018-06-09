
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
#include <meta/math/Module.h>
#endif
        
#include <ctx/Forward.h>
#include <ctx/Types.h>
#include <ctx/Api.h>

#include <meta/ctx/Convert.h>

#ifndef MUD_CTX_REFL_EXPORT
#define MUD_CTX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_CTX_REFL_EXPORT mudctx : public Module
	{
	private:
		mudctx();

	public:
		static mudctx& m() { static mudctx instance; return instance; }
	};
}

#ifdef MUD_CTX_MODULE
extern "C"
MUD_CTX_REFL_EXPORT Module& getModule();
#endif

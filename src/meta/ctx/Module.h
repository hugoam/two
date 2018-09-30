
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
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

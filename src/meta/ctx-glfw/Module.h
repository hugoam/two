
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#endif
        
#include <ctx-glfw/Forward.h>
#include <ctx-glfw/Types.h>
#include <ctx-glfw/Api.h>

#include <meta/ctx-glfw/Convert.h>

#ifndef MUD_CTX_GLFW_REFL_EXPORT
#define MUD_CTX_GLFW_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_CTX_GLFW_REFL_EXPORT mud_ctx_glfw : public Module
	{
	private:
		mud_ctx_glfw();

	public:
		static mud_ctx_glfw& m() { static mud_ctx_glfw instance; return instance; }
	};
}

#ifdef MUD_CTX_GLFW_MODULE
extern "C"
MUD_CTX_GLFW_REFL_EXPORT Module& getModule();
#endif

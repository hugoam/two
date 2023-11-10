
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/ecs/Module.h>
#include <meta/tree/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/lang/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/snd/Module.h>
#include <meta/bgfx/Module.h>
#include <meta/gfx/Module.h>
#endif
        
#include <15_script/Forward.h>
#include <15_script/Types.h>
#include <15_script/Api.h>

#include <meta/15_script/Convert.h>

#ifndef _15_SCRIPT_REFL_EXPORT
#define _15_SCRIPT_REFL_EXPORT MUD_IMPORT
#endif

	export_ class _15_SCRIPT_REFL_EXPORT _15_script : public Module
	{
	private:
		_15_script();

	public:
		static _15_script& m() { static _15_script instance; return instance; }
	};

#ifdef _15_SCRIPT_MODULE
extern "C"
_15_SCRIPT_REFL_EXPORT Module& getModule();
#endif

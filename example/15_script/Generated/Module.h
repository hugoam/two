
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <edit/Generated/Module.h>
#include <procgen/Generated/Module.h>
#include <procgen-gfx/Generated/Module.h>
#endif
        
#include <15_script/Generated/Forward.h>
#include <15_script/Generated/Types.h>
#include <15_script/Api.h>

#include <15_script/Generated/Convert.h>

	export_ class _15_SCRIPT_EXPORT ex_15_script : public Module
	{
	private:
		ex_15_script();

	public:
		static ex_15_script& m() { static ex_15_script instance; return instance; }
	};

#ifdef _15_SCRIPT_MODULE
extern "C"
_15_SCRIPT_EXPORT Module& getModule();
#endif

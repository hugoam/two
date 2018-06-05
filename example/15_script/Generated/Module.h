
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <edit/Generated/Module.h>
#include <gen/Generated/Module.h>
#endif
        
#include <15_script/Generated/Forward.h>
#include <15_script/Generated/Types.h>

#include <15_script/15_script.h>

	export_ class _15_SCRIPT_EXPORT ex_15_script : public Module
	{
	private:
		ex_15_script();

	public:
		static ex_15_script& m() { static ex_15_script instance; return instance; }
	};

#ifdef _EX_15_SCRIPT_MODULE
extern "C"
_15_SCRIPT_EXPORT Module& getModule();
#endif

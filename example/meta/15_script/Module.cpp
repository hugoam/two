#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module ._15_script;
#else
#include <meta/15_script/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/15_script/Convert.h>
#endif
#define _15_SCRIPT_REFLECTION_IMPL
#include <meta/15_script/Meta.h>

	_15_script::_15_script()
		: Module("_15_script")
	{
        // ensure dependencies are instantiated

        // setup reflection meta data
		_15_script_meta(*this);
	}

#ifdef _15_SCRIPT_MODULE
extern "C"
Module& getModule()
{
	return _15_script::m();
}
#endif

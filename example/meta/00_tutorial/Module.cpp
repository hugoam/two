#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module ._00_tutorial;
#else
#include <meta/00_tutorial/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/00_tutorial/Convert.h>
#endif
#define _00_TUTORIAL_REFLECTION_IMPL
#include <meta/00_tutorial/Meta.h>

	_00_tutorial::_00_tutorial()
		: Module("_00_tutorial")
	{
        // ensure dependencies are instantiated

        // setup reflection meta data
		_00_tutorial_meta(*this);
	}

#ifdef _00_TUTORIAL_MODULE
extern "C"
Module& getModule()
{
	return _00_tutorial::m();
}
#endif

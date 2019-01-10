#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tree;
#else
#include <meta/tree/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/tree/Convert.h>
#endif
#define MUD_TREE_REFLECTION_IMPL
#include <meta/tree/Meta.h>

namespace mud
{
	mud_tree::mud_tree()
		: Module("mud::tree", { &mud_infra::m() })
	{
		// setup reflection meta data
		mud_tree_meta(*this);
	}
}

#ifdef MUD_TREE_MODULE
extern "C"
Module& getModule()
{
		return mud_tree::m();
}
#endif

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tree;
#else
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#endif

namespace mud
{
	mud_tree::mud_tree()
		: Module("mud::tree", { &mud_infra::m() })
	{}
}

#ifdef MUD_TREE_MODULE
extern "C"
Module& getModule()
{
		return mud_tree::m();
}
#endif

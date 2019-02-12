#include <mud/tree.refl.h>
#include <mud/infra.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>


#ifdef MUD_MODULES
module mud.tree;
#else
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

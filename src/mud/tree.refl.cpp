#include <mud/tree.refl.h>
#include <mud/tree.h>
#include <mud/infra.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.tree;
#else
#endif


using namespace mud;


namespace mud
{
	void mud_tree_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

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

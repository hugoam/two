#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tree;
#else
#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/tree/Convert.h>
#endif

#include <tree/Api.h>

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

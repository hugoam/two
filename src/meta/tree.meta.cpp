#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.tree.meta;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/tree.meta.h>
#endif

namespace two
{
	two_tree::two_tree()
		: Module("two::tree", { &two_infra::m() })
	{}
}

#ifdef TWO_TREE_MODULE
extern "C"
Module& getModule()
{
	return two_tree::m();
}
#endif

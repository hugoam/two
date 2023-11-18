#include <two/tree.refl.h>
#include <two/infra.refl.h>
#include <two/refl.h>
#include <two/infra.h>


module two.tree;

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

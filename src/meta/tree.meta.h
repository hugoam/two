#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_TREE_META_EXPORT
#define TWO_TREE_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_TREE_META_EXPORT two_tree : public two::Module
	{
	private:
		two_tree();
		
	public:
		static two_tree& m() { static two_tree instance; return instance; }
	};
}

#ifdef TWO_TREE_MODULE
extern "C"
TWO_TREE_META_EXPORT Module& getModule();
#endif

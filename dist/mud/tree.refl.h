#pragma once

#include <mud/tree.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <tree/Types.h>

#ifndef MUD_TREE_REFL_EXPORT
#define MUD_TREE_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_TREE_REFL_EXPORT mud_tree : public mud::Module
	{
	private:
		mud_tree();
		
	public:
		static mud_tree& m() { static mud_tree instance; return instance; }
	};
}

#ifdef MUD_TREE_MODULE
extern "C"
MUD_TREE_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}

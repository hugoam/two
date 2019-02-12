#pragma once

#include <mud/pool.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <pool/Types.h>

#ifndef MUD_POOL_REFL_EXPORT
#define MUD_POOL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_POOL_REFL_EXPORT mud_pool : public mud::Module
	{
	private:
		mud_pool();
		
	public:
		static mud_pool& m() { static mud_pool instance; return instance; }
	};
}

#ifdef MUD_POOL_MODULE
extern "C"
MUD_POOL_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}

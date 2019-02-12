#pragma once

#include <mud/refl.h>
#include <mud/type.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <type/Types.h>

#ifndef MUD_TYPE_REFL_EXPORT
#define MUD_TYPE_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_TYPE_REFL_EXPORT mud_type : public mud::Module
	{
	private:
		mud_type();
		
	public:
		static mud_type& m() { static mud_type instance; return instance; }
	};
}

#ifdef MUD_TYPE_MODULE
extern "C"
MUD_TYPE_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}

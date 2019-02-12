#pragma once

#include <mud/ecs.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <ecs/Types.h>

#ifndef MUD_ECS_REFL_EXPORT
#define MUD_ECS_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_ECS_REFL_EXPORT mud_ecs : public mud::Module
	{
	private:
		mud_ecs();
		
	public:
		static mud_ecs& m() { static mud_ecs instance; return instance; }
	};
}

#ifdef MUD_ECS_MODULE
extern "C"
MUD_ECS_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}

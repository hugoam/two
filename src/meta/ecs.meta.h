#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <ecs/Forward.h>
//#include <ecs/Types.h>

#ifndef TWO_ECS_REFL_EXPORT
#define TWO_ECS_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_ECS_REFL_EXPORT two_ecs : public two::Module
	{
	private:
		two_ecs();
		
	public:
		static two_ecs& m() { static two_ecs instance; return instance; }
	};
}

#ifdef TWO_ECS_MODULE
extern "C"
TWO_ECS_REFL_EXPORT Module& getModule();
#endif

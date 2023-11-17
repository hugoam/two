#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_ECS_META_EXPORT
#define TWO_ECS_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_ECS_META_EXPORT two_ecs : public two::Module
	{
	private:
		two_ecs();
		
	public:
		static two_ecs& m() { static two_ecs instance; return instance; }
	};
}

#ifdef TWO_ECS_MODULE
extern "C"
TWO_ECS_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}

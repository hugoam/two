#pragma once

#include <two/refl.h>
#include <two/type.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <type/Types.h>

#ifndef TWO_TYPE_REFL_EXPORT
#define TWO_TYPE_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_TYPE_REFL_EXPORT two_type : public two::Module
	{
	private:
		two_type();
		
	public:
		static two_type& m() { static two_type instance; return instance; }
	};
}

#ifdef TWO_TYPE_MODULE
extern "C"
TWO_TYPE_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}

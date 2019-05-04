#pragma once

#include <two/srlz.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <srlz/Types.h>

#ifndef TWO_SRLZ_REFL_EXPORT
#define TWO_SRLZ_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_SRLZ_REFL_EXPORT two_srlz : public two::Module
	{
	private:
		two_srlz();
		
	public:
		static two_srlz& m() { static two_srlz instance; return instance; }
	};
}

#ifdef TWO_SRLZ_MODULE
extern "C"
TWO_SRLZ_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}

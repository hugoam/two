#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_SRLZ_META_EXPORT
#define TWO_SRLZ_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_SRLZ_META_EXPORT two_srlz : public two::Module
	{
	private:
		two_srlz();
		
	public:
		static two_srlz& m() { static two_srlz instance; return instance; }
	};
}

#ifdef TWO_SRLZ_MODULE
extern "C"
TWO_SRLZ_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
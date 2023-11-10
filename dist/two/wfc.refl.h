#pragma once

#include <two/wfc.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <wfc/Types.h>

#ifndef TWO_WFC_REFL_EXPORT
#define TWO_WFC_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_WFC_REFL_EXPORT two_wfc : public two::Module
	{
	private:
		two_wfc();
		
	public:
		static two_wfc& m() { static two_wfc instance; return instance; }
	};
}

#ifdef TWO_WFC_MODULE
extern "C"
TWO_WFC_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::Result& val) { val = two::Result(enu<two::Result>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Result& val, string& str) { str = enu<two::Result>().name(uint32_t(val)); };
	
	
}

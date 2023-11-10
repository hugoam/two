#pragma once

#include <two/fract.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <fract/Types.h>

#ifndef TWO_FRACT_REFL_EXPORT
#define TWO_FRACT_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_FRACT_REFL_EXPORT two_fract : public two::Module
	{
	private:
		two_fract();
		
	public:
		static two_fract& m() { static two_fract instance; return instance; }
	};
}

#ifdef TWO_FRACT_MODULE
extern "C"
TWO_FRACT_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::PatternSampling& val) { val = two::PatternSampling(enu<two::PatternSampling>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PatternSampling& val, string& str) { str = enu<two::PatternSampling>().name(uint32_t(val)); };
	
	
}

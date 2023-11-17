#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_REFL_META_EXPORT
#define TWO_REFL_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_REFL_META_EXPORT two_refl : public two::Module
	{
	private:
		two_refl();
		
	public:
		static two_refl& m() { static two_refl instance; return instance; }
	};
}

#ifdef TWO_REFL_MODULE
extern "C"
TWO_REFL_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::TypeClass& val) { val = two::TypeClass(enu<two::TypeClass>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::TypeClass& val, string& str) { str = enu<two::TypeClass>().name(uint32_t(val)); };
	
	
}

#pragma once

#include <two/lang.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <lang/Types.h>

#ifndef TWO_LANG_REFL_EXPORT
#define TWO_LANG_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_LANG_REFL_EXPORT two_lang : public two::Module
	{
	private:
		two_lang();
		
	public:
		static two_lang& m() { static two_lang instance; return instance; }
	};
}

#ifdef TWO_LANG_MODULE
extern "C"
TWO_LANG_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::Language& val) { val = two::Language(enu<two::Language>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Language& val, string& str) { str = enu<two::Language>().name(uint32_t(val)); };
	
	
}

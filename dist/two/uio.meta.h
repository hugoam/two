#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_UIO_META_EXPORT
#define TWO_UIO_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_UIO_META_EXPORT two_uio : public two::Module
	{
	private:
		two_uio();
		
	public:
		static two_uio& m() { static two_uio instance; return instance; }
	};
}

#ifdef TWO_UIO_MODULE
extern "C"
TWO_UIO_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::EditNestMode& val) { val = two::EditNestMode(enu<two::EditNestMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::EditNestMode& val, string& str) { str = enu<two::EditNestMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::EditorHint& val) { val = two::EditorHint(enu<two::EditorHint>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::EditorHint& val, string& str) { str = enu<two::EditorHint>().name(uint32_t(val)); };
	
	
}

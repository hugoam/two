#pragma once

#include <mud/uio.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <uio/Types.h>

#ifndef MUD_UIO_REFL_EXPORT
#define MUD_UIO_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UIO_REFL_EXPORT mud_uio : public mud::Module
	{
	private:
		mud_uio();
		
	public:
		static mud_uio& m() { static mud_uio instance; return instance; }
	};
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::EditNestMode& val) { val = mud::EditNestMode(enu<mud::EditNestMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EditNestMode& val, string& str) { str = enu<mud::EditNestMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::EditorHint& val) { val = mud::EditorHint(enu<mud::EditorHint>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EditorHint& val, string& str) { str = enu<mud::EditorHint>().name(uint32_t(val)); };
	
	
}

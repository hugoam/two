#pragma once

#include <mud/refl.h>
#include <mud/ctx.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <ctx/Types.h>

#ifndef MUD_CTX_REFL_EXPORT
#define MUD_CTX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_CTX_REFL_EXPORT mud_ctx : public mud::Module
	{
	private:
		mud_ctx();
		
	public:
		static mud_ctx& m() { static mud_ctx instance; return instance; }
	};
}

#ifdef MUD_CTX_MODULE
extern "C"
MUD_CTX_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::DeviceType& val) { val = mud::DeviceType(enu<mud::DeviceType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::DeviceType& val, string& str) { str = enu<mud::DeviceType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::EventType& val) { val = mud::EventType(enu<mud::EventType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EventType& val, string& str) { str = enu<mud::EventType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::InputMod& val) { val = mud::InputMod(enu<mud::InputMod>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::InputMod& val, string& str) { str = enu<mud::InputMod>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Key& val) { val = mud::Key(enu<mud::Key>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Key& val, string& str) { str = enu<mud::Key>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::MouseButtonCode& val) { val = mud::MouseButtonCode(enu<mud::MouseButtonCode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::MouseButtonCode& val, string& str) { str = enu<mud::MouseButtonCode>().name(uint32_t(val)); };
	
	
}

#pragma once

#include <two/refl.h>
#include <two/ctx.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <ctx/Types.h>

#ifndef TWO_CTX_REFL_EXPORT
#define TWO_CTX_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_CTX_REFL_EXPORT two_ctx : public two::Module
	{
	private:
		two_ctx();
		
	public:
		static two_ctx& m() { static two_ctx instance; return instance; }
	};
}

#ifdef TWO_CTX_MODULE
extern "C"
TWO_CTX_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::Key& val) { val = two::Key(enu<two::Key>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Key& val, string& str) { str = enu<two::Key>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::MouseButtonCode& val) { val = two::MouseButtonCode(enu<two::MouseButtonCode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::MouseButtonCode& val, string& str) { str = enu<two::MouseButtonCode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::InputMod& val) { val = two::InputMod(enu<two::InputMod>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::InputMod& val, string& str) { str = enu<two::InputMod>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::DeviceType& val) { val = two::DeviceType(enu<two::DeviceType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::DeviceType& val, string& str) { str = enu<two::DeviceType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::EventType& val) { val = two::EventType(enu<two::EventType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::EventType& val, string& str) { str = enu<two::EventType>().name(uint32_t(val)); };
	
	
}

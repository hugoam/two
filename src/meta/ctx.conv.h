#pragma once

#ifndef TWO_MODULES
#include <ctx/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
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

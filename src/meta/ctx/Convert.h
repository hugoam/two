#pragma once

#include <ctx/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::DeviceType& val) { val = static_cast<mud::DeviceType>(enu<mud::DeviceType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::DeviceType& val, string& str) { str = enu<mud::DeviceType>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::EventType& val) { val = static_cast<mud::EventType>(enu<mud::EventType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EventType& val, string& str) { str = enu<mud::EventType>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::InputMod& val) { val = static_cast<mud::InputMod>(enu<mud::InputMod>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::InputMod& val, string& str) { str = enu<mud::InputMod>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Key& val) { val = static_cast<mud::Key>(enu<mud::Key>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Key& val, string& str) { str = enu<mud::Key>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::MouseButtonCode& val) { val = static_cast<mud::MouseButtonCode>(enu<mud::MouseButtonCode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::MouseButtonCode& val, string& str) { str = enu<mud::MouseButtonCode>().m_map[size_t(val)]; };
	
	
}

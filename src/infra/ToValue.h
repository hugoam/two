//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <infra/Base.h>
#include <infra/String.h>

#include <cstdlib>

namespace mud
{
#ifdef MUD_STRING_TINYSTL
	export_ template <> inline void to_value(const string& str, bool& val) { val = atoi(str.c_str()) != 0; } //str == "true" ? true : false; }
	export_ template <> inline void to_value(const string& str, float& val) { val = float(atof(str.c_str())); }
	export_ template <> inline void to_value(const string& str, double& val) { sscanf(str.c_str(), "%lf", &val); }
	export_ template <> inline void to_value(const string& str, char& val) { val = char(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, short& val) { val = short(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, int& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, long& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, llong& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, uchar& val) { val = uchar(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, ushort& val) { val = ushort(atoi(str.c_str())); }
	export_ template <> inline void to_value(const string& str, uint& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, ulong& val) { val = atoi(str.c_str()); }
	export_ template <> inline void to_value(const string& str, ullong& val) { val = atoi(str.c_str()); }
#else
	export_ template <> inline void to_value(const string& str, bool& val) { val = std::stoi(str) != 0; } //str == "true" ? true : false; }
	export_ template <> inline void to_value(const string& str, float& val) { val = std::stof(str); }
	export_ template <> inline void to_value(const string& str, double& val) { val = std::stod(str); }
	export_ template <> inline void to_value(const string& str, char& val) { val = char(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, short& val) { val = short(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, int& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, long& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, llong& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, uchar& val) { val = uchar(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, ushort& val) { val = ushort(std::stoi(str)); }
	export_ template <> inline void to_value(const string& str, uint& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, ulong& val) { val = std::stoi(str); }
	export_ template <> inline void to_value(const string& str, ullong& val) { val = std::stoi(str); }
#endif
}

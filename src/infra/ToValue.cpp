//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.infra;
#else
#include <cstdlib>
#include <infra/ToValue.h>
#endif

namespace two
{
#ifdef TWO_MODULES
	using std::string;
#endif

#ifndef USE_STL
	template <> void to_value(const string& str, bool& val) { val = atoi(str.c_str()) != 0; } //str == "true" ? true : false; }
	template <> void to_value(const string& str, char& val) { val = char(atoi(str.c_str())); }
	template <> void to_value(const string& str, schar& val) { val = schar(atoi(str.c_str())); }
	template <> void to_value(const string& str, short& val) { val = short(atoi(str.c_str())); }
	template <> void to_value(const string& str, int& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, long& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, llong& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, uchar& val) { val = uchar(atoi(str.c_str())); }
	template <> void to_value(const string& str, ushort& val) { val = ushort(atoi(str.c_str())); }
	template <> void to_value(const string& str, uint& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, ulong& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, ullong& val) { val = atoi(str.c_str()); }
	template <> void to_value(const string& str, float& val) { val = float(atof(str.c_str())); }
	template <> void to_value(const string& str, double& val) { val = atof(str.c_str()); } //sscanf(str.c_str(), "%lf", &val); }
	template <> void to_value(const string& str, ldouble& val) { val = atof(str.c_str()); }
#else
	template <> void to_value(const string& str, bool& val) { val = std::stoi(str) != 0; } //str == "true" ? true : false; }
	template <> void to_value(const string& str, char& val) { val = char(std::stoi(str)); }
	template <> void to_value(const string& str, schar& val) { val = schar(std::stoi(str)); }
	template <> void to_value(const string& str, short& val) { val = short(std::stoi(str)); }
	template <> void to_value(const string& str, int& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, long& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, llong& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, uchar& val) { val = uchar(std::stoi(str)); }
	template <> void to_value(const string& str, ushort& val) { val = ushort(std::stoi(str)); }
	template <> void to_value(const string& str, uint& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, ulong& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, ullong& val) { val = std::stoi(str); }
	template <> void to_value(const string& str, float& val) { val = std::stof(str); }
	template <> void to_value(const string& str, double& val) { val = std::stod(str); }
	template <> void to_value(const string& str, ldouble& val) { val = std::stod(str); }
#endif
}

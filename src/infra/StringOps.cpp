//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.infra;
#else
#include <stl/algorithm.h>
#include <infra/Config.h>
#include <infra/StringOps.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <infra/NonCopy.h>
#endif

#include <cctype>

namespace mud
{
	const size_t g_num_precision = 3;

	void split(const string& str, const string& separator, array<string> output)
	{
		size_t start = 0;
		size_t next = str.find(separator, start);

		size_t index = 0;
		while(next != string::npos && index < output.size())
		{
			output[index++].assign(str.data() + start, next - start);
			start = next + 1;
			next = str.find(separator, start);
		}
		if(index < output.size())
			output[index++].assign(str.data() + start, str.size() - start);
	}

	vector<string> split(const string& str, const string& separator)
	{
		vector<string> result;
		
		if(str.size() == 0)
			return result;

		size_t cur_pos = 0;
		size_t last_pos = 0;

		while (cur_pos != string::npos)
		{
			cur_pos = str.find(separator, last_pos);
			result.push_back(str.substr(last_pos, cur_pos - last_pos));
			last_pos = cur_pos + separator.size();
		}

		return result;
	}

	//string join(array<string> strings, string separator)
	string join(const vector<string>& strings, string separator)
	{
		if(strings.size() == 0) return "";
		string result;
		for(const string& s : strings)
		{
			result += s;
			result += separator;
		}
		result.erase(result.size() - separator.size(), separator.size());
		return result;
	}

	string replace(const string& original, const string& before, const string& after)
	{
		string retval;
		retval.reserve(original.size());

		size_t current = 0;
		size_t next = original.find(before, current);
		while(next != string::npos)
		{
			retval.append(original.begin() + current, original.begin() + next);
			retval.append(after);
			current = next + before.size();
			next = original.find(before, current);
		}
		retval.append(original.substr(current));
		return retval;
	}

	string to_lower(const string& original)
	{
		string result = original;
		transform(result.begin(), result.end(), result.begin(), [](char c) { return char(tolower(c)); });
		return result;
	}

	string to_upper(const string& original)
	{
		string result = original;
		transform(result.begin(), result.end(), result.begin(), [](char c) { return char(toupper(c)); });
		return result;
	}

	string to_pascalcase(const string& name)
	{
		string result = name;
		result[0] = char(::toupper(name[0]));
		for (size_t pos = result.find("_"); pos != string::npos; pos = result.find("_", pos))
		{
			result.erase(pos, 1);
			result[pos] = char(::toupper(result[pos]));
		}
		return result;
	}

	string to_camelcase(const string& name)
	{
		string result = name;
		for(size_t pos = result.find("_"); pos != string::npos; pos = result.find("_", pos))
		{
			result.erase(pos, 1);
			result[pos] = char(::toupper(result[pos]));
		}
		return result;
	}
}

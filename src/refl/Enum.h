//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <refl/Meta.h>
#include <refl/Convert.h>
#include <infra/String.h>
#include <infra/StringConvert.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Enum
	{
	public:
		Enum(Type& type, bool scoped, const std::vector<cstring>& names, const std::vector<uint32_t>& indices, const std::vector<Var>& values);

		Type& m_type;

		bool m_scoped = true;
		std::vector<cstring> m_names;
		std::vector<uint32_t> m_indices;
		std::vector<Var> m_values;
		std::vector<cstring> m_map;

		uint32_t value(cstring name);
		uint32_t index(cstring name);
	};

	export_ inline size_t enum_index(Ref value)
	{
		return enu(value).index(to_string(value).c_str());
	}

	export_ inline void enum_set_index(Ref value, size_t index)
	{
		copy_construct(value, enu(value).m_values[index]);
	}

	export_ inline Var enum_value(Type& type, size_t index)
	{
		Var value = meta(type).m_empty_var; enum_set_index(value, index); return value;
	}
}

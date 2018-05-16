//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Reflect/Meta.h>
#include <obj/String/String.h>
#include <obj/String/StringConvert.h>

/* std */
#include <vector>

namespace mud
{
	class _refl_ MUD_OBJ_EXPORT Enum
	{
	public:
		Enum(Type& type, bool scoped, const std::vector<cstring>& names, const std::vector<size_t>& indices, const std::vector<Var>& values);

		Type& m_type;

		bool m_scoped = true;
		std::vector<cstring> m_names;
		std::vector<size_t> m_indices;
		std::vector<Var> m_values;
		std::vector<cstring> m_map;

		uint32_t value(cstring name);
		size_t index(cstring name);
	};

	inline size_t enum_index(Ref value)
	{
		return enu(value).index(to_string(value).c_str());
	}

	inline void enum_set_index(Ref value, size_t index)
	{
		copy_construct(value, enu(value).m_values[index]);
	}

	inline Var enum_value(Type& type, size_t index)
	{
		Var value = type.m_meta->m_empty_var(); enum_set_index(value, index); return value;
	}
}

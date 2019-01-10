//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
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
		Enum(Type& type, bool scoped, const std::vector<cstring>& names, const std::vector<uint32_t>& values, const std::vector<Var>& vars);

		Type& m_type;

		bool m_scoped = true;
		std::vector<cstring> m_names;
		std::vector<uint32_t> m_values;
		std::vector<Var> m_vars;
		std::vector<cstring> m_reverse;

		uint32_t value(cstring name);
		uint32_t value(const Var& value);
		uint32_t index(cstring name);
		uint32_t index(const Var& value);
		cstring name(uint32_t value) { return m_reverse[value]; }
		Var var(uint32_t value);
		//Var varn(uint32_t index) { Var value = meta(m_type).m_empty_var; copy_construct(value, m_vars[index]); return value; }
		Var varn(uint32_t index) { return m_vars[index]; }
		void varn(uint32_t index, Ref value) { copy_construct(value, m_vars[index]); }
	};
}

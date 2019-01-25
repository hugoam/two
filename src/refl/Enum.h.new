//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <infra/Array.h>
#include <refl/Forward.h>
#include <refl/Meta.h>

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Enum
	{
	public:
		Enum(Type& type, bool scoped, array<cstring> names, array<uint32_t> values, array<void*> vars);

		Type& m_type;

		bool m_scoped = true;
		array<cstring> m_names;
		array<uint32_t> m_values;
		array<void*> m_vars;
		vector<cstring> m_reverse;

		uint32_t value(cstring name);
		uint32_t value(Ref value);
		uint32_t index(cstring name);
		uint32_t index(Ref value);
		cstring name(uint32_t value) { return m_reverse[value]; }
		Ref var(uint32_t value);
		//Var varn(uint32_t index) { Var value = meta(m_type).m_empty_var; copy_construct(value, m_vars[index]); return value; }
		Ref varn(uint32_t index) { return Ref(m_vars[index], m_type); }
		void varn(uint32_t index, Ref value) { copy_construct(value, this->varn(index)); }
	};
}

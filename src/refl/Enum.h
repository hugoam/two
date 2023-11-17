//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>

namespace two
{
	export_ class refl_ TWO_REFL_EXPORT Enum
	{
	public:
		Enum(Type& type, bool scoped, span<cstring> names, span<uint32_t> values, span<void*> vars);

		Type& m_type;

		bool m_scoped = true;
		span<cstring> m_names;
		span<uint32_t> m_values;
		span<void*> m_vars;
		vector<cstring> m_reverse;

		uint32_t value(cstring name);
		uint32_t value(Ref value);
		uint32_t index(cstring name);
		uint32_t index(Ref value);
		cstring name(uint32_t value) { return m_reverse[value]; }
		Ref var(uint32_t value);
		//Var varn(uint32_t index) { const Var& value = meta(m_type).m_empty_var; copy_construct(value, m_vars[index]); return value; }
		Ref varn(uint32_t index) { return Ref(m_vars[index], m_type); }
		void varn(uint32_t index, Ref value) { copy_construct(value, this->varn(index)); }
	};
}

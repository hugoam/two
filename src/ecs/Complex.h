//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/span.h>
#include <infra/Generic.h>
#include <type/Ref.h>
#include <type/Proto.h>
#endif
#include <ecs/Forward.h>

namespace two
{
	export_ class refl_ TWO_ECS_EXPORT Complex
	{
	public:
		constr_ Complex(uint32_t id, Type& type);
		constr_ Complex(uint32_t id, Type& type, span<Ref> parts);
		virtual ~Complex();

		template <class... T_Parts>
		Complex(uint32_t id, Type& type, T_Parts&&... parts)
			: Complex(id, type)
		{
			swallow{ (this->add_part(Ref(&parts, two::type<type_class<T_Parts>>())), 1)... };
		}

		attr_ uint32_t m_id;
		attr_ Type& m_type;
		attr_ Prototype& m_prototype;

		attr_ vector<Ref> m_parts;

		meth_ void setup(span<Ref> parts);

		meth_ void add_part(Ref part) { m_parts[m_prototype.part_index(type(part))] = part; }
		meth_ bool has_part(Type& type) { return m_prototype.has_part(type); }
		meth_ Ref part(Type& type) { return m_parts[m_prototype.part_index(type)]; }
		meth_ Ref try_part(Type& type) { if(has_part(type)) return this->part(type); else return Ref(); }
	};

	export_ template <class T>
	inline bool is(Complex& complex) { return complex.m_type.template is<T>() || complex.has_part(type<T>()); }

	export_ template <class T>
	inline T& as(Complex& complex) { return *static_cast<T*>(complex.part(type<T>()).m_value); }

	export_ template <class T>
	inline T* try_as(Complex& complex) { return is<T>(complex) ? *as<T>(complex) : nullptr; }
}

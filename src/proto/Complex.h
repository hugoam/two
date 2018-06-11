//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Generic.h>
#include <obj/Ref.h>
#include <proto/Proto.h>
#include <proto/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	class Construct;

	export_ class refl_ MUD_PROTO_EXPORT Complex
	{
	public:
		Complex(Id id, Type& type, Prototype& prototype);
		virtual ~Complex();

		attr_ Id m_id;
		attr_ Type& m_type;
		attr_ Prototype& m_prototype;

		Construct* m_construct;
		std::vector<void*> m_parts;

		void add_part(Type& type, void* pointer) { m_parts[m_prototype.part_index(type)] = pointer; }
		bool has_part(Type& type) { return m_prototype.has_part(type); }
		Ref partref(Type& type) { return Ref(m_parts[m_prototype.part_index(type)], type); }
		void* part(Type& type) { return m_parts[m_prototype.part_index(type)]; }

	public:
		template <class T>
		inline bool isa() { return is<T>(*this) || this->has_part(type<T>()); }

		template <class T>
		inline T& part() { return *static_cast<T*>(this->part(type<T>())); }
	};

	export_ template <class T>
	inline bool isa(Complex& complex) { return is<T>(complex) || complex.has_part(type<T>()); }

	export_ class refl_ MUD_OBJ_EXPORT Construct
	{
	public:
		Construct(Complex& stem, Prototype& prototype);
		virtual ~Construct();

		template <typename... T_Parts>
		void index(T_Parts&&... parts)
		{
			swallow { (m_stem.add_part(type<typename type_class<T_Parts>::type>(), &parts), 1)... };
		}

		attr_ Type& m_type;
		Complex& m_stem;
		Prototype& m_prototype;
	};
}

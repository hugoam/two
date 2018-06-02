//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>

#include <obj/Cls.h>
#include <obj/TypeOf.h>

namespace mud
{
	using cstring = const char*;

	export_ class _refl_ MUD_OBJ_EXPORT Ref
	{
	public:
		Ref() : m_type(nullptr), m_value(nullptr) {}
		Ref(Type& type) : m_type(&type), m_value(nullptr) {}
		Ref(void* value, Type& type) : m_type(&type), m_value(value) {}
		template <class T>
		Ref(T* object) : m_type(&typeof<T>(object)), m_value(object) {}
		template <class T>
		Ref(const T* object) : m_type(&typeof<T>(object)), m_value(const_cast<T*>(object)) {}

		inline bool operator==(const Ref& other) const { return m_type == other.m_type && m_value == other.m_value; }
		inline operator bool() const { return m_value != nullptr; }

		inline Type& type() const { return *m_type; }
		//inline Meta& meta() const { return *m_type->m_meta; }

		Type* m_type;
		void* m_value;
	};

	export_ template <class T>
	Ref ref(T& value) { return Ref(&value); }

	export_ template <class T>
	Ref ref(const T& value) { return Ref(&value); }

	export_ template <class T>
	Ref ref(T* value) { return Ref(value); }

	export_ template <class T>
	Ref ref(const T* value) { return Ref(value); }
}

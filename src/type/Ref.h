//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Forward.h>

#include <type/Cls.h>
#include <type/TypeOf.h>

namespace mud
{
	using cstring = const char*;

	export_ class refl_ struct_ MUD_TYPE_EXPORT Ref
	{
	public:
		Ref() : m_type(nullptr), m_value(nullptr) {}
		Ref(void* value, Type& type) : m_type(&type), m_value(value) {}
		explicit Ref(Type& type) : m_type(&type), m_value(nullptr) {}
		template <class T>
		explicit Ref(T* object) : m_type(&type_of<T>(object)), m_value(object) {}
		template <class T>
		explicit Ref(const T* object) : m_type(&type_of<T>(object)), m_value(const_cast<T*>(object)) {}

		inline bool operator==(const Ref& other) const { return m_type == other.m_type && m_value == other.m_value; }
		inline bool operator!=(const Ref& other) const { return m_type != other.m_type || m_value != other.m_value; }
		inline explicit operator bool() const { return m_value != nullptr; }

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

	export_ inline Type& type(Ref ref) { return *ref.m_type; }
}

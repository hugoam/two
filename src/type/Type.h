//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/stddef.h>
#include <stdint.h>
#include <type/Forward.h>
#include <type/Cls.h>

namespace two // export_ namespace two// @todo evaluate export at namespace level ?
{
	export_ using cstring = const char*;

	export_ struct TWO_TYPE_EXPORT Address
	{
		char value[16];
		bool operator==(const Address& other) const;
	};

	export_ class refl_ TWO_TYPE_EXPORT Type
	{
	public:
		explicit Type();
		explicit Type(const char* name, size_t size = 0);
		explicit Type(const char* name, Type& base, size_t size = 0);
		~Type();

		Type(Type&) = delete;
		Type& operator=(const Type&) = delete;

		Type(Type&&) = delete;

		attr_ uint32_t m_id;
		attr_ cstring m_name;
		attr_ size_t m_size;
		attr_ Type* m_base = nullptr;

		bool is(const Type& type) const;

		template <class T>
		inline bool is() const { return this->is(two::type<T>()); }

		static Type& type() { static Type ty(0); return ty; }

		size_t m_debug_count;
		size_t m_debug_memory;

	private:
		Type(int);
	};

	export_ template <> inline Type& type<Type>() { return Type::type(); }

	template <class T>
	struct Typed
	{
		static Type& type()
		{
			static_assert(sizeof(T) == 0, "Types must be declared by defining a type<T>() function");
			static Type ty("INVALID"); return ty;
		}
	};

	export_ template <class T>
	inline Type& type() { return Typed<T>::type(); }

	export_ template <class T, class U>
	inline bool is(const U& object) { return object.m_type.template is<T>(); }

	export_ template <class T, class U>
	inline T* try_as(U& object) { if(object.m_type.template is<T>()) return &static_cast<T&>(object); else return nullptr; }

	export_ template <class T, class U>
	inline const T* try_as(const U& object) { if(object.m_type.template is<T>()) return &static_cast<const T&>(object); else return nullptr; }
	
	export_ template <class T, class U>
	constexpr size_t member_offset(U T::*member)
	{
		return (char*)&((T*)nullptr->*member) - (char*)nullptr;
	}

	export_ template <class T_Method>
	Address member_address(T_Method p)
	{
		Address result = {};
		for(size_t i = 0; i < sizeof p; ++i)
			result.value[i] = reinterpret_cast<char*>(&p)[i];
		return result;
	}
}

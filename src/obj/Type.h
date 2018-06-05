//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Cls.h>

#ifndef MUD_CPP_20
#include <cstddef>
#endif

namespace mud // export_ namespace mud// @todo evaluate export at namespace level ?
{
	using Id = unsigned int;
	using cstring = const char*;

	class Meta;

	export_ struct Address
	{
		char value[16];
		bool operator==(const Address& other) const;
	};

	export_ enum class _refl_ TypeKind : unsigned int
	{
		Type,
		Prototype
	};

	export_ class _refl_ MUD_OBJ_EXPORT Type
	{
	public:
		explicit Type(const char* name, TypeKind kind = TypeKind::Type);
		explicit Type(const char* name, Type& base, TypeKind kind = TypeKind::Type);
		~Type();

		Type(Type&) = delete;
		Type& operator=(const Type&) = delete;

		Type(Type&&) = delete;

		_attr_ Id m_id;
		_attr_ Type& m_type;
		_attr_ TypeKind m_kind;
		_attr_ cstring m_name;
		_attr_ Type* m_base = nullptr;

		_attr_ Meta* m_meta = nullptr;
		_attr_ Class* m_class = nullptr;
		_attr_ Enum* m_enum = nullptr;
		_attr_ Convert* m_convert = nullptr;

		bool is(Type& type) const;

		template <class T>
		inline bool is() const { return this->is(mud::type<T>()); }

		static Type& type() { static Type ty(0); return ty; }

		size_t debugTotalCount;
		size_t debugTotalMemory;

	private:
		Type(int);
	};

	export_ template <> inline Type& type<Type>() { return Type::type(); }

	export_ template <class T>
	Type& type()
	{
		static_assert(sizeof(T) == 0, "Types must be declared by defining a type<T>() function");
		static Type ty("INVALID"); return ty;
	}

	export_ template <class T>
	inline Meta& meta() { return *type<T>().m_meta; }

	export_ template <class T>
	inline Class& cls() { return *type<T>().m_class; }

	export_ template <class T>
	inline Enum& enu() { return *type<T>().m_enum; }

	export_ template <class T, class U>
	inline bool is(const U& object) { return object.m_type.template is<T>(); }

	export_ template <class T_Method>
	Address member_address(T_Method p)
	{
		Address result;
		for(size_t i = 0; i < sizeof p; ++i)
			result.value[i] = reinterpret_cast<char *>(&p)[i];
		return result;
	}
}

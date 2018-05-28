//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <obj/Unique.h>

namespace mud
{
	class _refl_ MUD_OBJ_EXPORT None
	{
	public:
		bool operator==(const None& other) const { UNUSED(other); return true; }
	};

	template <> MUD_OBJ_EXPORT Type& type<None>();

	class MUD_OBJ_EXPORT Any
	{
	public:
		virtual ~Any() {}

		virtual Ref ref() const = 0;
		virtual void assign(Ref ref) = 0;
		virtual void assign(const Any& other) = 0;
		virtual bool compare(const Any& other) const = 0;
		virtual unique_ptr<Any> clone() const = 0;
	};

	class MUD_OBJ_EXPORT Val
	{
	public:
		Val(Type& type, unique_ptr<Any> ref) : m_type(&type), m_any(std::move(ref)) {}
		Val();

		Val(Val&& other) : m_type(other.m_type), m_any(std::move(other.m_any)) {}
		Val(const Val& other) : m_type(other.m_type), m_any(other.m_any ? other.m_any->clone() : nullptr) {}
		Val& operator=(const Val& rhs) { if(m_type == rhs.m_type) m_any->assign(*rhs.m_any); else Val(rhs).swap(*this); return *this; }

		Val& swap(Val& rhs) { std::swap(m_any, rhs.m_any); std::swap(m_type, rhs.m_type); return *this; }

		Ref ref() const { return m_any->ref(); }
		void set(Ref value) { m_any->assign(value); }
		void clear() { if(m_type != &type<None>()) *this = Val(); }

		bool operator==(const Val& other) const { return m_type == other.m_type && m_any->compare(*other.m_any); }
		operator bool() const { return m_type == &type<None>(); }

		Type* m_type;
		unique_ptr<Any> m_any;
	};

	enum VarMode : unsigned int
	{
		VAL,
		REF
	};

	class _refl_ MUD_OBJ_EXPORT Var
	{
	public:
		Var() : m_mode(VAL), m_val(), m_ref(m_val.ref()) {}
		Var(const Val& val) : m_mode(VAL), m_val(val), m_ref(m_val.ref()) {}
		Var(const Ref& ref) : m_mode(REF), m_ref(ref) {}

		Var(const Var& other) : m_mode(other.m_mode), m_val(other.m_val), m_ref(m_mode == VAL ? m_val.ref() : other.m_ref) {}
		Var& operator=(const Var& other) { m_mode = other.m_mode; if(m_mode == VAL) { m_val = other.m_val; m_ref = m_val.ref(); } else m_ref = other.m_ref; return *this; }
		Var& operator=(const Ref& ref) { m_mode = REF; m_ref = ref; return *this; }

		VarMode m_mode;
		Val m_val;
		Ref m_ref;

		bool operator==(const Var& other) const { return m_mode == other.m_mode && (m_mode == VAL ? m_val == other.m_val : m_ref == other.m_ref); }

		inline Type& type() const { return *m_ref.m_type; }
		inline bool null() const { return m_mode == VAL ? false : m_ref.m_value == nullptr; }
		inline bool none() const { return m_mode == VAL ? m_val.m_type == &mud::type<None>() : false; }
		inline void set(Ref value) { if(m_mode == VAL) m_val.set(value); else m_ref = value; }
		inline void clear() { m_mode = VAL; m_val.clear(); }

		inline operator const Ref&() const { return m_ref; }
		inline operator Ref&() { return m_ref; }
	};
}

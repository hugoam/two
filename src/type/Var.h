//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/swap.h>
#include <type/Ref.h>
#include <type/Unique.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

namespace mud
{
	export_ class MUD_TYPE_EXPORT AnyHandler
	{
	public:
		virtual Ref ref(const Any& any) const { UNUSED(any); return Ref(); }
		virtual void assign(Any& any, Ref ref) const { UNUSED(any); UNUSED(ref); }
		virtual void assign(Any& any, const Any& other) const { UNUSED(any); UNUSED(other); }
		virtual bool compare(const Any& any, const Any& other) const { UNUSED(any); UNUSED(other); return true; }

		virtual void destroy(Any& any) const { UNUSED(any); }
		virtual void copy(Any& any, const Any& other) const { UNUSED(any); UNUSED(other); }
		virtual void move(Any& any, Any& other) const { UNUSED(any); UNUSED(other); }

		static AnyHandler none;
	};

	export_ class MUD_TYPE_EXPORT Any
	{
	public:
		Any() : m_handler(&AnyHandler::none) {}
		~Any() { m_handler->destroy(*this); }

		Any(Any&& other) : Any() { other.m_handler->move(*this, other); }
		Any(const Any& other) : Any() { other.m_handler->copy(*this, other); }

		Any& operator=(const Any& rhs) { if(m_handler == rhs.m_handler) m_handler->assign(*this, rhs); else Any(rhs).swap(*this); return *this; }
		Any& operator=(Ref ref) { m_handler->assign(*this, ref); return *this; }

		Any& swap(Any& other) { using mud::swap; swap(m_handler, other.m_handler); swap(m_pointer, other.m_pointer); swap(m_storage, other.m_storage); return *this; }

		Ref ref() const { return m_handler->ref(*this); }
		bool operator==(const Any& other) const { return m_handler == other.m_handler && m_handler->compare(*this, other); }
		operator bool() const { return m_handler != &AnyHandler::none; }

		const AnyHandler* m_handler;
		void* m_pointer = nullptr;
		struct Storage { uint8_t m_bytes[sizeof(void*)*3]; };
		Storage m_storage;
	};

	export_ enum VarMode : unsigned int
	{
		VAL,
		REF
	};

	export_ class refl_ MUD_TYPE_EXPORT Var
	{
	public:
		Var() : m_mode(VAL), m_any(), m_ref() {}
		Var(const Any& val) : m_mode(VAL), m_any(val), m_ref(m_any.ref()) {}
		Var(const Ref& ref) : m_mode(REF), m_ref(ref) {}

		Var(const Var& other) : m_mode(other.m_mode), m_any(other.m_any), m_ref(m_mode == VAL ? m_any.ref() : other.m_ref) {}
		Var& operator=(const Var& other) { m_mode = other.m_mode; if (m_mode == VAL) { m_any = other.m_any; m_ref = m_any.ref(); } else m_ref = other.m_ref; return *this; }
		Var& operator=(const Ref& ref) { m_mode = REF; m_ref = ref; return *this; }

		VarMode m_mode;
		Any m_any;
		Ref m_ref;

		bool operator==(const Var& other) const { return m_mode == other.m_mode && (m_mode == VAL ? m_any == other.m_any : m_ref == other.m_ref); }

		explicit operator bool() const { return this->none(); }

		inline void copy(const Ref& ref) { if(m_mode == VAL) m_any = ref; else m_ref = ref; }

		inline bool null() const { return m_mode == VAL ? false : m_ref.m_value == nullptr; }
		inline bool none() const { return m_mode == VAL ? !m_any : false; }
		inline void set(Ref value) { if(m_mode == VAL) m_any = value; else m_ref = value; }
		inline void clear() { m_mode = VAL; m_any = Any(); }

		inline operator const Ref&() const { return m_ref; }
		inline operator Ref&() { return m_ref; }
	};

	export_ inline Type& type(const Var& var) { return *var.m_ref.m_type; }
}

#pragma once

#include <mud/infra.h>



#include <stl/new.h>
#include <stl/move.h>


#include <stl/move.h>
#include <stl/traits.h>


#include <stl/stddef.h>
#include <stdint.h>



#ifndef MUD_TYPE_EXPORT
#define MUD_TYPE_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum VarMode : unsigned int;
    
    struct Address;
    class Type;
    class Ref;
    class None;
    class Any;
    class Var;
    class DoubleDispatch;
    class Indexer;
    class Index;
	class Prototype;
}

#ifdef MUD_META_GENERATOR
#include <stl/string.h>
#include <stl/vector.h>
namespace stl
{
	export_ extern template class refl_ seque_ vector<string>;
	export_ extern template class refl_ seque_ vector<mud::Ref>;
}
#endif



export_ namespace mud
{}

namespace mud
{
	export_ constexpr unsigned int c_max_types = 1000U;

	class Type;

	export_ template <class T>
	Type& type();

	export_ template <class T, class U>
	inline T& as(U& object) { return static_cast<T&>(object); }

	export_ template <class T, class U>
	inline const T& as(const U& object) { return static_cast<const T&>(object); }
}

namespace mud // export_ namespace mud// @todo evaluate export at namespace level ?
{
	export_ using cstring = const char*;

	export_ struct MUD_TYPE_EXPORT Address
	{
		char value[16];
		bool operator==(const Address& other) const;
	};

	export_ class refl_ MUD_TYPE_EXPORT Type
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
		inline bool is() const { return this->is(mud::type<T>()); }

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

	export_ template <class T_Method>
	Address member_address(T_Method p)
	{
		Address result = {};
		for(size_t i = 0; i < sizeof p; ++i)
			result.value[i] = reinterpret_cast<char *>(&p)[i];
		return result;
	}
}




#include <stl/traits.h>

namespace mud
{
	class Type;

	export_ template <class T>
	using unqual_type = remove_cv<remove_reference<T>>;

	export_ template <class T>
	using type_class = remove_pointer<unqual_type<T>>;
	
	inline void sink_type(Type&) {}

	export_ template <class T, typename = int>
	constexpr bool is_typed = false;

	export_ template <class T>
	constexpr bool is_typed<T, decltype(sink_type(declval<T>().m_type), 0)> = true;

	export_ template <class T>
	inline enable_if<!is_typed<T>,
		Type&> type_of(const T& value) { UNUSED(value); return type<T>(); }

	export_ template <class T>
	inline enable_if<is_typed<T>,
		Type&> type_of(const T& value) { return value.m_type; }

	export_ template <class T>
	inline enable_if<!is_typed<T>,
		Type&> type_of(const T* value) { UNUSED(value); return type<T>(); }

	export_ template <class T>
	inline enable_if<is_typed<T>,
		Type&> type_of(const T* value) { if(value) return value->m_type; return type<T>(); }
}

namespace mud
{
	using cstring = const char*;

	export_ class refl_ struct_ MUD_TYPE_EXPORT Ref
	{
	public:
		constr_ Ref() : m_type(nullptr), m_value(nullptr) {}
		constr_ Ref(void* value, const Type& type) : m_type(&type), m_value(value) {}
		explicit Ref(const Type& type) : m_type(&type), m_value(nullptr) {}
		template <class T>
		explicit Ref(T* object) : m_type(&type_of<T>(object)), m_value(object) {}
		template <class T>
		explicit Ref(const T* object) : m_type(&type_of<T>(object)), m_value(const_cast<T*>(object)) {}

		inline bool operator==(const Ref& other) const { return m_type == other.m_type && m_value == other.m_value; }
		inline bool operator!=(const Ref& other) const { return m_type != other.m_type || m_value != other.m_value; }
		inline explicit operator bool() const { return m_value != nullptr; }

		attr_ const Type* m_type;
		attr_ void* m_value;
	};

	export_ template <class T>
	Ref ref(T& value) { return Ref(&value); }

	export_ template <class T>
	Ref ref(const T& value) { return Ref(&value); }

	export_ template <class T>
	Ref ref(T* value) { return Ref(value); }

	export_ template <class T>
	Ref ref(const T* value) { return Ref(value); }

	export_ inline const Type& type(Ref ref) { return *ref.m_type; }
}
//#include <type/Types.h>

#include <cassert>

namespace mud
{
	export_ template <class T>
	inline void type_check(const Ref& ref) { UNUSED(ref); assert(type(ref).is<T>()); }
	
	export_ template <class T>
	inline enable_if<!is_pointer<T> || is_same<T, cstring>, T&>
		val(Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline enable_if<is_pointer<T> && !is_same<T, cstring>, T>
		val(Ref& ref) { type_check<remove_pointer<T>>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline enable_if<!is_pointer<T> || is_same<T, cstring>, const T&>
		val(const Ref& ref) { type_check<T>(ref); return *(T*)(ref.m_value); }

	export_ template <class T>
	inline enable_if<is_pointer<T> && !is_same<T, cstring>, T>
		val(const Ref& ref) { type_check<remove_pointer<T>>(ref); return (T)(ref.m_value); }

	export_ template <class T>
	inline void setval(Ref& ref, T& value) { ref.m_value = &value; ref.m_type = &type_of<T>(value); }
	
	export_ template <class T>
	inline void setval(Ref& ref, T* value) { ref.m_value = (void*)value; ref.m_type = &type_of<T>(value); }
	
	export_ template <>
	inline Ref& val<Ref>(Ref& ref) { return ref; }

	export_ template <>
	inline const Ref& val<Ref>(const Ref& ref) { return ref; }
	
	export_ template <>
	inline void* val<void*>(Ref& ref) { return ref.m_value; }

	export_ template <>
	inline void* val<void*>(const Ref& ref) { return ref.m_value; }

	template <class T>
	export_ inline T* try_val(Ref object) { if(object && type(object).template is<T>()) return &val<T>(object); else return nullptr; }
}


#ifndef MUD_MODULES
#endif

#if defined __GNUC__
#   pragma GCC system_header
#endif

namespace mud
{
	export_ template <class T>
	inline enable_if<is_comparable<T>, bool>
		any_compare(const T& first, const T& second) { return first == second; }

	export_ template <class T>
	inline enable_if<!is_comparable<T>, bool>
		any_compare(const T& first, const T& second) { return &first == &second; }

	export_ template <class T>
	inline enable_if<is_copy_assignable<T>, void>
		any_assign(T& val, const T& other) { val = other; }

	export_ template <class T>
	inline enable_if<!is_copy_assignable<T>, void>
		any_assign(T& val, const T& other) { UNUSED(val); UNUSED(other); }

	export_ template <class T>
	inline enable_if<is_copy_constructible<T>, T>
		any_copy(const T& val) { return T(val); }

	export_ template <class T>
	inline enable_if<!is_copy_constructible<T>, T>
		any_copy(const T& val) { UNUSED(val); return T(); }

	export_ template <class T>
	inline enable_if<is_trivially_destructible<T>, void>
		any_destruct(T& val) { UNUSED(val); }
	
	export_ template <class T>
	inline enable_if<!is_trivially_destructible<T>, void>
		any_destruct(T& val) { val.~T(); }
}


#include <stdint.h>
#include <stl/swap.h>

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
		Var& operator=(const Var& other) { m_mode = other.m_mode; if(m_mode == VAL) { m_any = other.m_any; m_ref = m_any.ref(); } else m_ref = other.m_ref; return *this; }
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

	export_ inline const Type& type(const Var& var) { return *var.m_ref.m_type; }
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_TYPE_EXPORT Type& type<bool>();
    export_ template <> MUD_TYPE_EXPORT Type& type<char>();
    export_ template <> MUD_TYPE_EXPORT Type& type<const char*>();
    export_ template <> MUD_TYPE_EXPORT Type& type<double>();
    export_ template <> MUD_TYPE_EXPORT Type& type<float>();
    export_ template <> MUD_TYPE_EXPORT Type& type<int>();
    export_ template <> MUD_TYPE_EXPORT Type& type<ldouble>();
    export_ template <> MUD_TYPE_EXPORT Type& type<llong>();
    export_ template <> MUD_TYPE_EXPORT Type& type<long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<schar>();
    export_ template <> MUD_TYPE_EXPORT Type& type<short>();
    export_ template <> MUD_TYPE_EXPORT Type& type<stl::string>();
    export_ template <> MUD_TYPE_EXPORT Type& type<uchar>();
    export_ template <> MUD_TYPE_EXPORT Type& type<uint>();
    export_ template <> MUD_TYPE_EXPORT Type& type<ullong>();
    export_ template <> MUD_TYPE_EXPORT Type& type<ulong>();
    export_ template <> MUD_TYPE_EXPORT Type& type<ushort>();
    export_ template <> MUD_TYPE_EXPORT Type& type<void>();
    export_ template <> MUD_TYPE_EXPORT Type& type<void*>();
    
    export_ template <> MUD_TYPE_EXPORT Type& type<stl::vector<mud::Ref>>();
    export_ template <> MUD_TYPE_EXPORT Type& type<stl::vector<stl::string>>();
    
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Index>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Prototype>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Ref>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Var>();
}

namespace mud
{
	export_ template <class T, bool onlyref = is_object_pointer<T> || !is_copyable<T>>
	constexpr bool ValueSemantic = true;

	export_ template <class T>
	constexpr bool ValueSemantic<T, true> = false;

	template <class T>
	constexpr bool IsSmallObject = sizeof(T) <= sizeof(void*)*3;

	export_ template <class T, bool small = IsSmallObject<T>>
	class TAnyHandlerImpl : public AnyHandler
	{
	public:
		template <class U>
		static void create(Any& any, const AnyHandler& handler, U&& value) { any.m_pointer = new T(static_cast<U&&>(value)); any.m_handler = &handler; }

		static inline T& value(Any& any) { return *static_cast<T*>(any.m_pointer); }
		static inline const T& value(const Any& any) { return *static_cast<const T*>(any.m_pointer); }

		virtual void destroy(Any& any) const { delete static_cast<T*>(any.m_pointer); }
		virtual void copy(Any& any, const Any& other) const { create(any, *this, value(other));  }
		virtual void move(Any& any, Any& other) const { any.swap(other); }
	};

	export_ template <class T>
	class TAnyHandlerImpl<T, true> : public AnyHandler
	{
	public:
		template <class U>
		static void create(Any& any, const AnyHandler& handler, U&& value) { new (stl::placeholder(), (void*)&any.m_storage) T(static_cast<U&&>(value)); any.m_handler = &handler; }

		static inline T& value(Any& any) { return *static_cast<T*>((void*)&any.m_storage); }
		static inline const T& value(const Any& any) { return *static_cast<const T*>((void*)&any.m_storage); }

		virtual void destroy(Any& any) const { any_destruct<T>(value(any)); }
		virtual void copy(Any& any, const Any& other) const { create(any, *this, value(other)); }
		virtual void move(Any& any, Any& other) const
		{
			using mud::move;
			create(any, *this, move(value(other)));
			destroy(other);
		}
	};

	export_ template <class T>
	class TAnyHandler : public TAnyHandlerImpl<T>
	{
	public:
		template <class U>
		static Any create(U&& value) { Any any; TAnyHandlerImpl<T>::create(any, me, static_cast<U&&>(value)); return any; }

		virtual Ref ref(const Any& any) const { return Ref(&const_cast<T&>(this->value(any))); }
		virtual void assign(Any& any, Ref ref) const { any_assign<T>(this->value(any), val<T>(ref)); }
		virtual void assign(Any& any, const Any& other) const { any_assign<T>(this->value(any), this->value(other)); }
		virtual bool compare(const Any& any, const Any& other) const { return any_compare<T>(this->value(any), this->value(other)); }

		static TAnyHandler<T> me;
	};

	template <class T>
	TAnyHandler<T> TAnyHandler<T>::me;

	export_ template <class T>
	inline T& val(Any& v) { return TAnyHandler<T>::value(v); }

	export_ template <class T>
	inline const T& val(const Any& v) { return TAnyHandler<T>::value(v); }

	export_ template <class T, class U>
	inline void setval(Any& v, U&& value) { TAnyHandler<T>::value(v) = value; }
	
	export_ template <class T>
	inline T& val(Var& var) { return val<T>(var.m_ref); }

	export_ template <class T>
	inline T val(const Var& var) { return val<T>(var.m_ref); }
	
	export_ template <>
	inline void*& val(Var& var) { return var.m_ref.m_value; }

	export_ template <>
	inline void* val(const Var& var) { return var.m_ref.m_value; }

	export_ template <>
	inline cstring& val(Var& var) { return (cstring&)var.m_ref.m_value; }

	export_ template <>
	inline cstring val(const Var& var) { return (cstring)var.m_ref.m_value; }

	export_ template <class T, class U>
	inline enable_if<ValueSemantic<T>, void>
		setval(Var& var, U&& value) { if(var.m_mode == VAL) { setval<T>(var.m_any, value); /*setval(var.m_ref, val<T>(var.m_any));*/ } else setval<T>(var.m_ref, value); }

	export_ template <class T, class U>
	inline enable_if<!ValueSemantic<T>, void>
		setval(Var& var, U&& value) { setval(var.m_ref, static_cast<U&&>(value)); }

	export_ template <class T, class U>
	inline Var make_any(U&& value) { return TAnyHandler<T>::create(static_cast<U&&>(value)); }
	
	export_ template <class T, class U>
	inline enable_if<ValueSemantic<T>, Var>
		var_value(U&& value) { return make_any<T>(static_cast<U&&>(value)); }

	export_ template <class T, class U>
	inline enable_if<!ValueSemantic<T>, Var>
		var_value(U&& value) { return Ref(&value); }

	export_ template <class T, class U>
	inline enable_if<!is_object_pointer<T>, Var>
		make_var(U&& value) { return var_value<unqual_type<T>>(static_cast<T&&>(value)); }

	export_ template <class T, class U>
	inline enable_if<is_object_pointer<T>, Var>
		make_var(U&& value) { return Ref(value); }

	export_ template <class T>
	inline Var var(T&& value) { return make_var<T>(static_cast<T&&>(value)); }

	export_ template <>
	inline Var var(Ref&& ref) { return Var(ref); }

	export_ inline Var var(cstring value) { return Ref(const_cast<char*>(value), type<cstring>()); }
}
//#include <type/Any.h>



namespace mud
{
	export_ template <class T_Return, class... Args>
	class Dispatch
	{
	public:
		using HandlerFunc = T_Return(*)(void*, Ref, Args...);
		struct Func { void* f = nullptr; HandlerFunc handler = nullptr; };

		Dispatch() {}

		void function(Type& type, HandlerFunc func)
		{
			m_branches[type.m_id] = { nullptr, func };
		}

		template <class T>
		void function(HandlerFunc func)
		{
			m_branches[type<T>().m_id] = { nullptr, func };
		}

		T_Return dispatch(Ref ref, Args... args)
		{
			const Func& func = m_branches[ref.m_type->m_id];
			return func.handler(func.f, ref, static_cast<Args&&>(args)...);
		}

		bool check(Type& type)
		{
			return m_branches[type.m_id].handler != nullptr;
		}

		bool check(Ref ref)
		{
			return m_branches[ref.m_type->m_id].handler != nullptr;
		}

		Func m_branches[c_max_types] = {};
	};
}




#include <stl/vector.h>

namespace mud
{
	export_ class MUD_TYPE_EXPORT DoubleDispatch
	{
	public:
		DoubleDispatch()
			: m_branches()
		{}

		void resize(Type& first, Type& second)
		{
			if(first.m_id + 1U > m_branches.size())
				m_branches.resize(first.m_id + 1U);
			if(second.m_id + 1U > m_branches[first.m_id].size())
				m_branches[first.m_id].resize(second.m_id + 1U);
		}

		void dispatch(Ref first, Ref second)
		{
			return m_branches[first.m_type->m_id][second.m_type->m_id](first, second);
		}

		bool check(Ref first, Ref second)
		{
			return check(*first.m_type, *second.m_type);
		}

		bool check(const Type& first, const Type& second)
		{
			if(m_branches.size() > first.m_id && m_branches[first.m_id].size() > second.m_id)
				return m_branches[first.m_id][second.m_id] != nullptr;
			return false;
		}

		vector<vector<void (*)(Ref, Ref)>> m_branches;
	};
}

namespace mud
{
	export_ template <class T, class T_Function, class T_Return, class... Args>
	void dispatch_branch(Dispatch<T_Return, Args...>& dispatch, T_Function func)
	{
		auto handler = +[](void* f, Ref ref, Args... args) -> T_Return { return ((T_Function)(f))(val<T>(ref), static_cast<Args&&>(args)...); };
		dispatch.m_branches[type<T>().m_id] = { (void*)func, handler };
	}

	export_ template <class T, class T_Function, class T_Return, class... Args>
	void dispatch_ref_branch(Dispatch<T_Return, Args...>& dispatch, T_Function func)
	{
		auto handler = +[](void* f, Ref ref, Args... args) -> T_Return { return ((T_Function)(f))(ref, val<T>(ref), static_cast<Args&&>(args)...); };
		dispatch.m_branches[type<T>().m_id] = { (void*)func, handler };
	}

	export_ template <class T_First, class T_Second, void(*func)(T_First&, T_Second&)>
	void dispatch_branch(DoubleDispatch& dispatch)
	{
		dispatch.resize(type<T_First>(), type<T_Second>());
		dispatch.m_branches[type<T_First>().m_id][type<T_Second>().m_id] = [](Ref first, Ref second) { func(val<T_First>(first), val<T_Second>(second)); };
	}
}


#include <stdint.h>
#include <stl/vector.h>


#include <stl/memory.h>

#ifdef MUD_TRACK_MEMORY
#include <stl/traits.h>
#include <stl/function.h>
#endif

namespace mud
{
#ifdef MUD_TRACK_MEMORY
	template <class T>
	struct object_ptr_tracker
	{
		static void increment() { type<T>().debugTotalCount += 1; type<T>().debugTotalMemory += sizeof(T); }
		static void decrement() { type<T>().debugTotalCount -= 1; type<T>().debugTotalMemory -= sizeof(T); }
	};

	template <class T>
	void delete_tracked(void* object)
	{
		object_ptr_tracker<T>::decrement();
		delete static_cast<T*>(object);
	}

	template <class T>
	using object = unique<T, function<void(void*)>>;

	template <class T, class... Types>
	inline object<T> oconstruct(Types&&... args)
	{
		object_ptr_tracker<T>::increment();
		return (object<T>(new T(static_cast<Types&&>(args)...), &delete_tracked<T>));
	}
#else
	export_ template <class T>
	using object = unique<T>;

	export_ template <class T, typename... Args>
	object<T> oconstruct(Args&&... args)
	{
		return construct<T>(static_cast<Args&&>(args)...);
	}
#endif
}

namespace mud
{
	export_ class refl_ MUD_TYPE_EXPORT Indexer
	{
	public:
		Indexer(const Type& type) : m_type(&type), m_objects(1, Ref{ type }), m_count(0), m_next(0) {}

		attr_ const Type* m_type;
		attr_ vector<Ref> m_objects;

		inline uint32_t alloc() { return m_next++; }
		inline void add(uint32_t id, Ref object) { this->resize(id); m_objects[id] = object; ++m_count; }
		inline uint32_t index(uint32_t id, Ref object) { if(id == UINT32_MAX) id = this->alloc(); this->add(id, object); return id; }
		inline uint32_t index(Ref object) { uint32_t id = this->alloc(); this->add(id, object); return id; }
		inline void remove(uint32_t id) { m_objects[id] = Ref(m_type); --m_count; }

		inline void resize(uint32_t id) { if(id >= m_objects.size()) m_objects.resize(id+1); }

		template <class Visitor>
		inline void iterate(Visitor visitor) const { for(Ref object : m_objects) if(object.m_value) visitor(object); }
		inline bool has(uint32_t id) const { return m_objects[id].m_value != nullptr; }

		inline void clear() { m_objects.clear(); m_count = 0; }

	public:
		size_t m_count;
		uint32_t m_next;
	};

	export_ class refl_ MUD_TYPE_EXPORT Index //
	{
	public:
		Index() : m_indexers(c_max_types) {}

		Index(const Index& other) = delete;
		Index& operator=(const Index& other) = delete;

		meth_ Indexer& indexer(const Type& type)
		{
			if(!m_indexers[type.m_id])
				m_indexers[type.m_id] = make_unique<Indexer>(type);
			return *m_indexers[type.m_id];
		}

		vector<unique<Indexer>> m_indexers;

		attr_ static Index me;
	};

	export_ inline Indexer& indexer(const Type& type) { return Index::me.indexer(type); }
	export_ inline uint32_t index(const Type& type, uint32_t id, Ref object) { return Index::me.indexer(type).index(id, object); }
	export_ inline uint32_t index(const Type& type, Ref object) { return Index::me.indexer(type).index(object); }
	export_ inline void unindex(const Type& type, uint32_t id) { Index::me.indexer(type).remove(id); }

	export_ func_ inline Ref indexed(const Type& type, uint32_t id) { return Index::me.indexer(type).m_objects[id]; }
}
//#include <type/TypeUtils.h>


#include <stl/vector.h>
#include <stl/string.h>
//#include <type/Types.h>

namespace mud // export_ namespace mud// @todo evaluate export at namespace level ?
{
#if 1
	export_ template <class T>
	struct Typed<span<T>>
	{
		static inline Type& type() { static string name = "span<" + string(mud::type<type_class<T>>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<span<cstring>>
	{
		static inline Type& type() { static Type ty("span<cstring>"); return ty; }
	};

	export_ template <class T>
	struct Typed<vector<T>>
	{
		static inline Type& type() { static string name = "vector<" + string(mud::type<type_class<T>>().m_name) + ">"; static Type ty(name.c_str()); return ty; }
	};
	
	export_ template <>
	struct Typed<vector<cstring>>
	{
		static inline Type& type() { static Type ty("vector<cstring>"); return ty; }
	};
#endif

	export_ template <class... Args>
	inline vector<Type*> type_vector()
	{
		return{ &type<Args>()... };
	}
}


#include <stl/vector.h>
#include <stl/span.h>

namespace mud
{
	/*	A Prototype represent a fixed layout of parts for an object, allowing for fast part query 
			It is a broader definition of a type, different from the C++ class, it defines a finite object
			with a finite set of capabilities, which is a sum of components : its parts

			The parts are members of a prototype, whereas additionnal components are called plugs, 
			and are not part of the object in itself : they can be here or not here, whereas the parts are always here
	*/

	export_ class refl_ MUD_TYPE_EXPORT Prototype
	{
	public:
		Prototype(Type& type, span<Type*> parts);

		Type& m_type;
		vector<Type*> m_parts;

		void add_part(Type& type);

		inline bool has_part(const Type& type) { return (m_hash_parts[type.m_id] != 0); }
		inline size_t part_index(const Type& type) { return m_hash_parts[type.m_id]; }

	protected:
		vector<size_t> m_hash_parts;
	};

	export_ extern MUD_TYPE_EXPORT vector<Prototype*> g_prototypes;

	inline Prototype& proto(Type& type) { return *g_prototypes[type.m_id]; }
}


#include <stl/stddef.h>

namespace mud
{
	//! LocklessQueue template: as provid3ed by Lf3THn4D
	//! Only 1 thread can push and 1 thread can pop it.
	template <class T>
	class LocklessQueue
	{
	private:
		T* m_buffer = nullptr;
		size_t m_head = 0;
		size_t m_tail = 0;
		size_t m_size;

	public:
		inline LocklessQueue(size_t size)
			: m_size(size + 1)
		{
			m_buffer = new/*low*/T[m_size];
		}

		inline ~LocklessQueue() { delete[] m_buffer; }

		inline bool empty() const { return (m_head == m_tail); }

		inline bool push(const T& obj)
		{
			size_t next_head = (m_head + 1) % m_size;
			if(next_head == m_tail) return false;
			m_buffer[m_head] = obj;
			m_head = next_head;
			return true;
		}


		inline bool pop(T& obj)
		{
			if(m_tail == m_head) return false;
			obj = m_buffer[m_tail];
			m_tail = (m_tail + 1) % m_size;
			return true;
		}
	};
}


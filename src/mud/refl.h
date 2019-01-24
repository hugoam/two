#pragma once

#include <mud/pool.h>
#include <mud/infra.h>
#include <mud/type.h>


#include <stl/vector.h>



#ifndef MUD_REFL_EXPORT
#define MUD_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class ConstructorIndex : unsigned int;
    enum class TypeClass : unsigned int;
    
    
    class Param;
    class Signature;
    class Callable;
    class Function;
	struct Operator;
    class Method;
    class Constructor;
    class CopyConstructor;
    class Destructor;
    struct Call;
    class Meta;
    class Static;
    class Member;
    class Class;
    class Convert;
    class TypeConverter;
    class Enum;
    class Injector;
    class Creator;
    class Iterable;
    class Sequence;
    class Namespace;
    class Module;
    class System;
	class Prototype;
}



#include <stl/vector.h>
#include <stl/memory.h>

namespace mud
{
	export_ using cstring = const char*;

	export_ using FunctionPointer = void* (*)();

	export_ using ConstructorFunc = void(*)(Ref, array<Var>);
	export_ using CopyConstructorFunc = void(*)(Ref, Ref);
	export_ using DestructorFunc = void(*)(Ref);
	export_ using MethodFunc = void(*)(Ref, array<Var>, Var&);
	export_ using FunctionFunc = void(*)(array<Var>, Var&);

	export_ class refl_ MUD_REFL_EXPORT Param
	{
	public:
		enum Flags
		{
			None = 0,
			Nullable = (1 << 0),
			Reference = (1 << 1),
			Default = (1 << 2),
			Output = (1 << 3)
		};

	public:
		Param(cstring name, Var value, Flags flags = None);
		
		size_t m_index;
		cstring m_name;
		Var m_value;
		Flags m_flags;

		bool nullable() const { return (m_flags & Nullable) != 0; }
		bool reference() const { return (m_flags & Reference) != 0; }
		bool defaulted() const { return (m_flags & Default) != 0; }
		bool output() const { return (m_flags & Output) != 0; }
	};

	export_ class refl_ MUD_REFL_EXPORT Signature
	{
	public:
		Signature(const vector<Param>& params = {}, const Var& returnval = Var());

		vector<Param> m_params;
		Var m_returnval;
	};

	
	export_ class refl_ MUD_REFL_EXPORT Callable
	{
	public:
		Callable(cstring name, const vector<Param>& params = {}, Var returnval = Var());
		virtual ~Callable() {}

		void setup();

		bool validate(array<Var> args, size_t offset = 0) const;

		virtual void operator()(array<Var> args) const { Var none; return (*this)(args, none); }
		virtual void operator()(array<Var> args, Var& result) const = 0;

		uint32_t m_index;
		cstring m_name;

		Var m_returnval;

		vector<Param> m_params;
		size_t m_num_defaults;
		size_t m_num_required;

		vector<Var> m_arguments;

		bool checkArgs(const vector<Var>& args) const { for(const Param& param : m_params) if(!type(args[param.m_index]).is(type(param.m_value))) return false; return true; }
	};

	export_ class refl_ MUD_REFL_EXPORT Function final : public Callable
	{
	public:
		Function(Namespace* location, cstring name, FunctionPointer identity, FunctionFunc function, const vector<Param>& params = {}, Var returnval = Var());

		virtual void operator()(array<Var> args, Var& result) const { return m_call(args, result); }

		Namespace* m_namespace;
		FunctionPointer m_identity;
		FunctionFunc m_call;
	};

	export_ struct refl_ MUD_REFL_EXPORT Operator
	{
		attr_ Function* m_function;
		attr_ Type* m_type;
		attr_ cstring m_name;
		attr_ cstring m_sign;
		explicit operator bool() { return m_function != nullptr; }
	};

	export_ MUD_REFL_EXPORT Operator as_operator(Function& function);

	export_ class refl_ MUD_REFL_EXPORT Method final : public Callable
	{
	public:
		Method(Type& object_type, cstring name, Address address, MethodFunc method, const vector<Param>& params = {}, Var returnval = Var());

		virtual void operator()(array<Var> args, Var& result) const { return m_call(args[0], array<Var>{ args, 1 }, result); }

		Type* m_object_type;
		Address m_address;
		MethodFunc m_call;
	};

	export_ enum class ConstructorIndex : unsigned int
	{
		Default = 0,
		Proto = 0,
		ProtoParts = 1
	};

	export_ class refl_ MUD_REFL_EXPORT Constructor final : public Callable
	{
	public:
		Constructor(Type& object_type, ConstructorFunc func, const vector<Param>& params = {});
		Constructor(Type& object_type, cstring name, ConstructorFunc func, const vector<Param>& params = {});

		virtual void operator()(array<Var> args, Var& result) const { UNUSED(result); m_call(args[0], array<Var>{ args, 1 }); }

		size_t m_index;
		Type* m_object_type;
		ConstructorFunc m_call;
	};

	export_ class refl_ MUD_REFL_EXPORT CopyConstructor final : public Callable
	{
	public:
		CopyConstructor(Type& object_type, CopyConstructorFunc func);

		virtual void operator()(array<Var> args, Var& result) const { UNUSED(result); m_call(args[0], args[1]); }

		Type* m_object_type;
		CopyConstructorFunc m_call;
	};

	export_ class refl_ MUD_REFL_EXPORT Destructor final: public Callable
	{
	public:
		Destructor(Type& object_type, DestructorFunc func);

		virtual void operator()(array<Var> args, Var& result) const { UNUSED(result); m_call(args[0]); }

		Type* m_object_type;
		DestructorFunc m_call;
	};

	export_ struct refl_ MUD_REFL_EXPORT Call
	{
	public:
		constr_ Call();
		constr_ Call(const Callable& callable, vector<Var> arguments);
		Call(const Callable& callable);
		Call(const Callable& callable, Ref object);

		bool validate();

		const Var& operator()();
		const Var& operator()(Ref object);

		const Callable* m_callable = nullptr;
		attr_ vector<Var> m_arguments;
		attr_ Var m_result;
	};

	export_ template<typename T_Function>
	inline FunctionPointer funcptr(T_Function func) { return reinterpret_cast<FunctionPointer>(func); }

	export_ template <typename T_Function>
	inline Function& func(T_Function func);
}




#include <stl/vector.h>

#include <cstdlib>

namespace mud
{
	using cstring = const char*;

	export_ enum class refl_ TypeClass : unsigned int
	{
		None = 0,
		Object = 1,
		Struct = 2,
		Sequence = 4,
		BaseType = 5,
		Enum = 6
	};

	export_ template<typename T, typename U> constexpr uintptr_t member_offset(U T::*member)
	{
		return (char*)&((T*)nullptr->*member) - (char*)nullptr;
	}

	export_ template<typename T_Object, typename T_Base> uintptr_t base_offset()
	{
		void* mem = malloc(sizeof(T_Object));
		uintptr_t offset = (char*)static_cast<T_Base*>((T_Object*)mem) - (char*)(T_Object*)mem;
		free(mem);
		return offset;
	}

	export_ class refl_ MUD_REFL_EXPORT Meta
	{
	public:
		Meta(Type& type, Namespace* location, cstring name, size_t size, TypeClass type_class, bool is_array = false);

		Type* m_type;
		Namespace* m_namespace = nullptr;
		cstring m_name;
		size_t m_size;
		TypeClass m_type_class;
		bool m_is_array = false;

		Ref m_empty_ref;
		Var m_empty_var;

		using CopyConstruct = Var(*)(Ref); CopyConstruct m_copy_construct;
		using CopyAssign = void(*)(Ref, Ref); CopyAssign m_copy_assign;
	};
	
	export_ extern MUD_REFL_EXPORT vector<Meta*> g_meta;
	export_ extern MUD_REFL_EXPORT vector<Class*> g_class;
	export_ extern MUD_REFL_EXPORT vector<Enum*> g_enu;
	export_ extern MUD_REFL_EXPORT vector<Convert*> g_convert;
	export_ extern MUD_REFL_EXPORT vector<Iterable*> g_iterable;
	export_ extern MUD_REFL_EXPORT vector<Sequence*> g_sequence;

	export_ inline Meta& meta(Type& type) { return *g_meta[type.m_id]; }
	export_ inline Class& cls(Type& type) { return *g_class[type.m_id]; }
	export_ inline Enum& enu(Type& type) { return *g_enu[type.m_id]; }
	export_ inline Convert& convert(Type& type) { return *g_convert[type.m_id]; }
	export_ inline Iterable& iter(Type& type) { return *g_iterable[type.m_id]; }
	export_ inline Sequence& sequence(Type& type) { return *g_sequence[type.m_id]; }

	export_ template <class T>
	inline Meta& meta() { return meta(type<T>()); }

	export_ template <class T>
	inline Class& cls() { return cls(type<T>()); }

	export_ template <class T>
	inline Enum& enu() { return enu(type<T>()); }

	export_ inline bool is_base_type(Type& ty) { return meta(ty).m_type_class == TypeClass::BaseType; }
	export_ inline bool is_enum(Type& ty) { return meta(ty).m_type_class == TypeClass::Enum; }
	export_ inline bool is_basic(Type& ty) { return meta(ty).m_type_class == TypeClass::BaseType || meta(ty).m_type_class == TypeClass::Enum; }
	export_ inline bool is_struct(Type& ty) { return meta(ty).m_type_class == TypeClass::Struct; }
	export_ inline bool is_object(Type& ty) { return meta(ty).m_type_class == TypeClass::Object; }
	export_ inline bool is_sequence(Type& ty) { return meta(ty).m_type_class == TypeClass::Sequence; }
	export_ inline bool is_class(Type& ty) { return meta(ty).m_type_class < TypeClass::Sequence; }

	export_ inline bool is_array(Type& ty) { return meta(ty).m_is_array; }

	export_ inline bool is_iterable(Type& ty) { return g_iterable[ty.m_id] != nullptr; }
	//export_ inline bool is_sequence(Type& ty) { return g_sequence[ty.m_id] != nullptr; }

	export_ inline Meta& meta(const Ref& ref) { return meta(type(ref)); }
	export_ inline Meta& meta(const Var& var) { return meta(*var.m_ref.m_type); }

	export_ inline Class& cls(const Ref& ref) { return cls(type(ref)); }
	export_ inline Class& cls(const Var& var) { return cls(*var.m_ref.m_type); }

	export_ inline Enum& enu(const Ref& ref) { return enu(type(ref)); }
	export_ inline Enum& enu(const Var& var) { return enu(*var.m_ref.m_type); }

	export_ inline Iterable& iter(const Ref& ref) { return iter(type(ref)); }
	export_ inline Iterable& iter(const Var& var) { return iter(*var.m_ref.m_type); }

	export_ inline Sequence& sequence(const Ref& ref) { return sequence(type(ref)); }
	export_ inline Sequence& sequence(const Var& var) { return sequence(*var.m_ref.m_type); }

	export_ MUD_REFL_EXPORT void copy_construct(Ref dest, Ref source);

	export_ inline Var construct(Type& type)
	{
		return meta(type).m_empty_var;
	}

	export_ MUD_REFL_EXPORT void assign(Ref first, Ref second);
	export_ MUD_REFL_EXPORT void assign_pointer(Ref first, Ref second);
	export_ MUD_REFL_EXPORT bool compare(Ref first, Ref second);

	export_ MUD_REFL_EXPORT bool is_related(Type& input, Type& output);

	export_ MUD_REFL_EXPORT bool convert(Var& input, Type& output, Var& result, bool ref = false);
	export_ MUD_REFL_EXPORT bool convert(Ref input, Type& output, Var& result);
	export_ MUD_REFL_EXPORT Var convert(Ref input, Type& output);

	export_ MUD_REFL_EXPORT bool can_convert(Type& input, Type& output);
	export_ MUD_REFL_EXPORT bool can_convert(Ref input, Type& output);
}

namespace mud
{
	using MemberGet = Ref(*)(Ref);

	export_ class refl_ MUD_REFL_EXPORT Static
	{
	public:
		Static(Type& parent_type, cstring name, Ref value);

		Type* m_parent_type;
		cstring m_name;
		Ref m_value;
	};

	export_ class refl_ MUD_REFL_EXPORT Member
	{
	public:
		enum Flags
		{
			None = 0,
			Pointer = (1 << 0),
			NonMutable = (1 << 1),
			Structure = (1 << 2),
			Component = (1 << 3),
			Link = (1 << 4),
			Value = (1 << 5),
			Id = (1 << 6),
		};

	public:
		Member(Type& object_type, Address address, Type& type, cstring name, Var default_value, Flags flags = Flags::None, MemberGet get = nullptr);
		~Member();

		int m_index;
		Type* m_object_type;
		Address m_address;
		size_t m_offset;
		Type* m_type;
		cstring m_name;
		Var m_default_value;
		Flags m_flags;
		MemberGet m_get;

		Meta& meta() { return mud::meta(*m_type); }
		Class& cls() { return mud::cls(*m_type); }

		bool is_pointer() const { return (m_flags & Pointer) != 0; }
		bool is_mutable() const { return (m_flags & NonMutable) == 0; }
		bool is_structure() const { return (m_flags & Structure) != 0; }
		bool is_component() const { return (m_flags & Component) != 0; }
		bool is_link() const { return (m_flags & Link) != 0; }
		bool is_value() const { return (m_flags & Value) != 0; }

		inline Ref ref(Ref object) const { return Ref((void*)((char*)object.m_value + m_offset), *m_type); }

		inline Ref get(Ref object) const
		{
			if(m_get) return m_get(object);
			Ref ref = this->ref(object);
			if(this->is_pointer())
				return Ref(*(void**)ref.m_value, *m_type);
			else
				return ref;
		}

		inline Var get_value(Ref object) const
		{
			Var result = m_default_value;
			result.copy(this->get(object));
			return result;
		}

		inline void set(Ref object, Ref value) const
		{
			Ref ref = this->ref(object);
			if(this->is_pointer())
				*(void**)ref.m_value = value.m_value;
			else
				assign(ref, value);
		}

		inline Ref cast(Ref object) const;
		inline Ref cast_get(Ref object) const;
		inline Var safe_get(Ref object) const;
		inline void cast_set(Ref object, Ref value) const;
	};

	export_ template <typename T_Value, typename T>
	Member& member(T_Value T::*mem) { return cls<T>().member(member_address(mem)); }

	export_ template <typename T_Return, typename T, typename... T_Params>
	Member& member(T_Return(T::*meth)(T_Params...)) { return cls<T>().member(member_address(meth)); }

	export_ template <typename T_Return, typename T, typename... T_Params>
	Member& member(T_Return(T::*meth)(T_Params...) const) { return cls<T>().member(member_address(meth)); }
}

namespace mud
{
	export_ using cstring = const char*;

	export_ class refl_ MUD_REFL_EXPORT Class
	{
	public:
		Class(Type& type);
		Class(
			Type& type,
			vector<Type*> bases,
			vector<size_t> bases_offsets,
			vector<Constructor> constructors,
			vector<CopyConstructor> copy_constructors,
			vector<Member> members,
			vector<Method> methods,
			vector<Static> static_members
		);
		~Class();

		void inherit(vector<Type*> types);
		void setup_class();

		Ref upcast(Ref object, Type& base);
		Ref downcast(Ref object, Type& derived);

		Member& member(cstring name);
		Method& method(cstring name);
		Static& static_member(cstring name);
		Operator& op(cstring name);

		bool has_member(cstring name);
		bool has_method(cstring name);

		Member& member(Address address);
		Method& method(Address address);

		bool has_member(Address address);
		bool has_method(Address address);

		template <class T> inline Member& member(T member) { return this->member(member_address(member)); }
		template <class T> inline Method& method(T method) { return this->method(member_address(method)); }

		const Constructor* constructor(ConstructorIndex index) const;
		const Constructor* constructor(size_t arguments) const;

		bool is(Type& component);
		Ref as(Ref object, Type& component);

	public:
		Type* m_type;
		Meta* m_meta;
		Type* m_root;

		vector<Type*> m_bases;
		vector<size_t> m_bases_offsets;

		bool m_nested = false;

		// Reflection
		vector<Constructor> m_constructors;
		vector<CopyConstructor> m_copy_constructors; // in a vector until we update to c++17 optional
		vector<Destructor> m_destructor; // in a vector until we update to c++17 optional
		vector<Member> m_members;
		vector<Method> m_methods;

		vector<Operator> m_operators;

		vector<Static> m_static_members;
		vector<Function> m_static_functions;

		Member* m_id_member = nullptr;
		Member* m_type_member = nullptr;
		Member* m_name_member = nullptr;

		vector<cstring> m_field_names;
		vector<Var> m_field_values;

		// Deep Reflection
		vector<Member*> m_components;
		vector<Member*> m_deep_members;
		vector<Method*> m_deep_methods;

		// Sequence
		Type* m_content = nullptr;
		bool m_content_pointer = false;

		// Implementation
		using MakePool = unique<Pool>(*)(); MakePool m_make_pool;
	};

	inline Ref Member::cast(Ref object) const
	{
		Ref target = object;
		if(object.m_type != m_object_type && g_class[type(object).m_id])
			target = mud::cls(object).upcast(object, *m_object_type);
		return target;
	}

	inline Ref Member::cast_get(Ref object) const
	{
		return this->get(cast(object));
	}

	inline Var Member::safe_get(Ref object) const
	{
		Var result = m_default_value;
		result.copy(this->get(cast(object)));
		return result;
	}

	inline void Member::cast_set(Ref object, Ref value) const
	{
		this->set(cast(object), value);
	}

	export_ inline bool is_root_type(Type& ty) { return !g_class[ty.m_id] || cls(ty).m_root == &ty; }

	export_ template <class T>
	T& upcast(Ref value) { Ref base = cls(value).upcast(value, type<T>()); return val<T>(base); }

	export_ template<typename T_Return, typename T, typename... T_Params>
	inline Method& method(T_Return(T::*meth)(T_Params...)) { return cls<T>().method(member_address(meth)); }
}



namespace mud
{
	using ToStringFunc = void(*)(Ref, string&);
	using FromStringFunc = void(*)(const string&, Ref);

	export_ class refl_ MUD_REFL_EXPORT Convert
	{
	public:
		ToStringFunc m_to_string;
		FromStringFunc m_from_string;
	};

	export_ MUD_REFL_EXPORT string to_name(Type& type, Ref value);
	export_ inline string to_name(Ref value) { return to_name(type(value), value); }

	export_ template <>
	inline void to_string<Ref>(const Ref& object, string& str) { convert(*object.m_type).m_to_string(object, str); }

	export_ template <>
	inline void to_string<Var>(const Var& value, string& str) { convert(type(value)).m_to_string(value, str); }

	export_ template <class T_Source, class T_Dest>
	void convert(T_Source& from, T_Dest& to)
	{
		to = static_cast<T_Dest>(from);
	}

	export_ template <class T_Source, class T_Dest>
	void copy_convert(T_Source& from, T_Dest& to)
	{
		to = T_Dest(from);
	}

	export_ class MUD_REFL_EXPORT TypeConverter : public DoubleDispatch, public LazyGlobal<TypeConverter>
	{
	public:
		TypeConverter();

		bool check(Type& input, Type& output);
		bool check(Ref input, Type& output);
		Var convert(Ref input, Type& output);
		void convert(Ref input, Type& output, Var& result);

		template <class T_First, class T_Second>
		void default_converter()
		{
			dispatch_branch<T_First, T_Second, copy_convert<T_First, T_Second>>(*this);
			dispatch_branch<T_Second, T_First, copy_convert<T_Second, T_First>>(*this);
		}
	};
}



#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Enum
	{
	public:
		Enum(Type& type, bool scoped, const vector<cstring>& names, const vector<uint32_t>& values, const vector<Var>& vars);

		Type& m_type;

		bool m_scoped = true;
		vector<cstring> m_names;
		vector<uint32_t> m_values;
		vector<Var> m_vars;
		vector<cstring> m_reverse;

		uint32_t value(cstring name);
		uint32_t value(const Var& value);
		uint32_t index(cstring name);
		uint32_t index(const Var& value);
		cstring name(uint32_t value) { return m_reverse[value]; }
		Var var(uint32_t value);
		//Var varn(uint32_t index) { Var value = meta(m_type).m_empty_var; copy_construct(value, m_vars[index]); return value; }
		Var varn(uint32_t index) { return m_vars[index]; }
		void varn(uint32_t index, Ref value) { copy_construct(value, m_vars[index]); }
	};
}


#include <stl/vector.h>

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Injector : public Call
	{
	public:
		Injector(const Constructor& constructor);
		Injector(Type& type, size_t arguments);
		Injector(Type& type, ConstructorIndex constructor = ConstructorIndex::Default);

		Type& m_object_type;
		const Constructor& m_constructor;
		
		void inject(Var& value);
		Ref inject(Pool& pool);

		Var injectvar();
		Ref injectpool();

		void destroy(Ref object);
	};

	export_ class refl_ MUD_REFL_EXPORT Creator : public NonCopy
	{
	public:
		Creator(Type& type);

		attr_ Type& m_type;
		attr_ bool m_construct;
		attr_ Type* m_prototype;
		attr_ Injector& injector() const { return *m_injector; }

		object<Injector> m_injector;

		void set_prototype(Type& prototype);
	};
}



namespace mud
{
	export_ class MUD_REFL_EXPORT Iterable
	{
	public:
		using Size = size_t(*)(Ref); Size size;
		using At = Ref(*)(Ref, size_t); At at;

		template <class T_Visitor>
		void iterate(Ref vec, T_Visitor visitor) const
		{
			size_t count = this->size(vec);
			for(size_t i = 0; i < count; ++i)
				visitor(this->at(vec, i));
		}

		template <class T_Visitor>
		void iteratei(Ref vec, T_Visitor visitor) const
		{
			size_t count = this->size(vec);
			for(size_t i = 0; i < count; ++i)
				visitor(i, this->at(vec, i));
		}
	};

	export_ class MUD_REFL_EXPORT Sequence
	{
	public:
		using Add = void(*)(Ref, Ref); Add add;
		using Remove = void(*)(Ref, Ref); Remove remove;
	};
}





namespace mud
{
}


#include <stl/vector.h>
#include <stl/string.h>

namespace mud
{
	using cstring = const char*;

	export_ class refl_ MUD_REFL_EXPORT Namespace
	{
	public:
		Namespace(cstring name = nullptr, Namespace* parent = nullptr);

		bool is_root() { return m_name[0] == 0; }

		cstring m_name;
		Namespace* m_parent;
		vector<cstring> m_path;
	};

	export_ MUD_REFL_EXPORT Namespace& namspc(vector<cstring> path);
}



namespace mud
{
	export_ template <class T>
	typename enable_if<is_comparable<T>::value, void>::type vector_remove_any(vector<T>& vector, T value) { vector_remove(vector, value); }

	export_ template <class T>
	typename enable_if<!is_comparable<T>::value, void>::type vector_remove_any(vector<T>& vector, T& value) { vector_remove_object(vector, value); }
}

namespace mud
{
	export_ template <typename T_Value, typename T_Member, typename T>
	inline auto member_getter(T_Member T::*mem) { return [mem](Ref object, Var& v) { setval<T_Value>(v, val<T>(object).*mem); }; }

	export_ template <typename T_Value, typename T_Return, typename T>
	inline auto member_getter(T_Return(T::*func)()) { return [func](Ref object, Var& v) { setval<T_Value>(v, (val<T>(object).*func)()); }; }

	export_ template <typename T_Value, typename T_Return, typename T>
	inline auto member_getter(T_Return(T::*func)() const) { return [func](Ref object, Var& v) { setval<T_Value>(v, (val<T>(object).*func)()); }; }

	export_ template <typename T_Value, typename T_Member, typename T>
	inline auto member_setter(T_Member T::*mem) { return [mem](Ref object, const Var& v) { val<T>(object).*mem = val<T_Value>(v); }; }

	export_ template <typename T_Value, typename T_Param, typename T>
	inline auto member_setter(void(T::*func)(T_Param)) { return [func](Ref object, const Var& v) { (val<T>(object).*func)(val<T_Value>(v)); }; }

	export_ template <class T>
	void init_store() {}
		
	export_ template <class T, class U>
	void init_vector() { static Iterable iterable = { [](Ref vec) { return val<T>(vec).size(); },
													  [](Ref vec, size_t i) -> Ref { return mud::ref(val<T>(vec)[i]); } };
						 static Sequence sequence = { [](Ref vec, Ref value) { val<T>(vec).push_back(val<U>(value)); },
													  [](Ref vec, Ref value) { vector_remove_any(val<T>(vec), val<U>(value)); } };
						 g_iterable[type<T>().m_id] = &iterable;
						 g_sequence[type<T>().m_id] = &sequence; }

	//virtual bool has(Ref ref) const { for(const T& value : m_vector) if(any_compare<T>(val<T>(ref), value)) return true; return false; }

	export_ template <class T>
	void init_string() { static Convert convert = { [](Ref ref, string& str) { to_string<T>(val<T>(ref), str); },
													[](const string& str, Ref ref) { to_value<T>(str, val<T>(ref)); } };
						 g_convert[type<T>().m_id] = &convert; }

	export_ template <>
	MUD_REFL_EXPORT void init_string<void>();
	
	export_ template <>
	MUD_REFL_EXPORT void init_string<void*>();

	export_ template <>
	MUD_REFL_EXPORT void init_string<cstring>();

	export_ template <class T>
	void init_pool() { cls<T>().m_make_pool = []() -> unique<Pool> { return make_unique<TPool<T>>(); }; }

	export_ template <class T>
	inline typename enable_if<is_default_constructible<T>::value, void>::type
		init_default_value() { meta<T>().m_empty_var = var(T()); meta<T>().m_empty_ref = Ref(type<T>()); }

	export_ template <class T>
	inline typename enable_if<!is_default_constructible<T>::value, void>::type
		init_default_value() { meta<T>().m_empty_var = Ref(type<T>()); meta<T>().m_empty_ref = Ref(type<T>()); }
	
	export_ template <>
	inline void	init_default_value<Ref>() { meta<Ref>().m_empty_var = Ref(); meta<Ref>().m_empty_ref = Ref(); }

	export_ template <class T>
	inline typename enable_if<is_copy_assignable<T>::value, void>::type
		init_assign() { meta<T>().m_copy_assign = [](Ref first, Ref second) { val<T>(first) = val<T>(second); }; }

	export_ template <class T>
	inline typename enable_if<!is_copy_assignable<T>::value, void>::type
		init_assign() {}

	export_ template <class T>
		inline typename enable_if<is_trivially_destructible<T>::value, void>::type
		init_destructor() {}

	export_ template <class T>
		inline typename enable_if<!is_trivially_destructible<T>::value, void>::type
		init_destructor() { cls<T>().m_destructor.push_back({ type<T>(), [](Ref ref) { val<T>(ref).~T(); } }); }
	
	export_ template <>
	MUD_REFL_EXPORT void init_assign<void*>();

	export_ template <>
	MUD_REFL_EXPORT void init_assign<cstring>();

	export_ template <class T>
	void meta_type()
	{
		init_default_value<T>();
		init_assign<T>();
	}

	export_ template <class T>
	void meta_basetype()
	{
		meta_type<T>();
		init_string<T>();
	}

	export_ template <class T, class U>
	void meta_sequence()
	{
		meta_type<T>();
	}
	
	export_ template <class T, class U>
	void meta_vector()
	{
		meta_type<T>();
		init_vector<T, U>();
	}

	export_ template <class T>
	void meta_class()
	{
		meta_type<T>();
		init_destructor<T>();
		cls<T>().setup_class();
	}

	export_ template <class T>
	void meta_enum()
	{
		meta_type<T>();
		init_string<T>();
	}
}


#include <stl/vector.h>

#include <cstdint>

namespace mud
{
	export_ using cstring = const char*;
	
	export_ class refl_ MUD_REFL_EXPORT Module
	{
	public:
		Module(cstring name, vector<Module*> deps);

		attr_ cstring m_name;
		attr_ vector<Module*> m_deps;
		attr_ vector<Type*> m_types;
		attr_ vector<Function*> m_functions;

		attr_ cstring m_path;
		void* m_handle;
		uint64_t m_last_modified;
	};

#ifdef _WIN32
	typedef Module& (__cdecl *GetModule)(void);
#else
	typedef Module& (*GetModule)(void);
#endif
}


#include <stl/vector.h>

namespace mud
{
	export_ using cstring = const char*;
	export_ using FunctionPointer = void* (*)();
	
	export_ MUD_REFL_EXPORT Module* load_module(cstring path);
	export_ MUD_REFL_EXPORT void unload_module(Module& m);
	export_ MUD_REFL_EXPORT void reload_module(Module& m);
	export_ MUD_REFL_EXPORT FunctionPointer module_function(Module& module, cstring name);

	export_ class refl_ MUD_REFL_EXPORT System
	{
	public:
		System();

		vector<Namespace> m_namespaces; // @todo fix reflection
		attr_ vector<Module*> m_modules;
		attr_ vector<Type*> m_types;
		//attr_ vector<Prototype*> m_prototypes;
		attr_ vector<Function*> m_functions;

		void launch_process(cstring path, cstring args);

		void load_modules(vector<Module*> modules);

		Module* open_module(cstring path);
		void load_module(Module& m);
		void unload_module(Module& m);
		Module& reload_module(Module& m);
		bool has_module(Module& m);

		vector<cstring> meta_symbols();

		void dump_meta_info();
		void dump_memory_usage();

		Namespace& get_namespace(vector<cstring> path);
		Function& function(FunctionPointer pointer);

		Type* find_type(cstring name);
		Function* find_function(cstring name);
		Function* find_function(cstring nemespace, cstring name);

		static System& instance() { static System instance; return instance; }
	};

	export_ func_ inline System& system() { return System::instance(); }

	export_ template <typename T_Function>
	inline Function& func(T_Function func) { return System::instance().function(reinterpret_cast<FunctionPointer>(func)); }
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_REFL_EXPORT Type& type<mud::TypeClass>();
    
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Call>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Callable>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Class>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Convert>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Creator>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Enum>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Member>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Meta>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Module>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Namespace>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Operator>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Param>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Signature>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Static>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::System>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Constructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::CopyConstructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Destructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Function>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Injector>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Method>();
    
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Call*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Callable*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Class*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Convert*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Creator*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Enum*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Member*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Meta*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Module*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Namespace*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Operator*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Param*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Signature*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Static*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::System*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Constructor*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::CopyConstructor*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Destructor*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Function*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Injector*>>;
    export_ template struct MUD_REFL_EXPORT Typed<vector<mud::Method*>>;
}



#include <stl/function.h>

namespace mud
{
	export_ using VirtualMethod = function<void(Method&, Ref, array<Var>)>;

	export_ template <> MUD_REFL_EXPORT Type& type<VirtualMethod>();
}

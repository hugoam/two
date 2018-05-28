//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Type.h>
#include <obj/Array.h>
#include <obj/Var.h>
#include <obj/Strung.h>

#include <functional>
#include <vector>
#include <memory>

namespace mud
{
	typedef void* (*FunctionPointer)();

	using ConstructorFunc = void(*)(Ref, array<Var>);
	using CopyConstructorFunc = void(*)(Ref, Ref);
	using DestructorFunc = void(*)(Ref);
	using MethodFunc = void(*)(Ref, array<Var>, Var&);
	using FunctionFunc = void(*)(array<Var>, Var&);

	class _refl_ MUD_OBJ_EXPORT Param
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

	typedef std::vector<Param> ParamVector;

	class _refl_ MUD_OBJ_EXPORT Signature
	{
	public:
		Signature(const ParamVector& params = {}, const Var& returnval = Var());

		ParamVector m_params;
		Var m_returnval;
	};

	class _refl_ MUD_OBJ_EXPORT Callable
	{
	public:
		Callable(cstring name, const ParamVector& params = {}, Var returnval = Var());

		void setup();

		bool validate(array<Var> args) const;

		virtual void operator()(array<Var> args) const { Var none; return (*this)(args, none); }
		virtual void operator()(array<Var> args, Var& result) const = 0;

		uint32_t m_index;
		cstring m_name;
		Var m_returnval;
		ParamVector m_params;
		size_t m_num_defaults;

		std::vector<Var> m_arguments;

		bool checkArgs(const std::vector<Var>& args) const { for(const Param& param : m_params) if(&args[param.m_index].type() != &param.m_value.type()) return false; return true; }
	};

	class _refl_ MUD_OBJ_EXPORT Function : public Callable
	{
	public:
		Function(Namespace* location, cstring name, FunctionPointer identity, FunctionFunc function, const ParamVector& params = {}, Var returnval = Var());

		virtual void operator()(array<Var> args, Var& result) const { return m_call(args, result); }

		Namespace* m_namespace;
		FunctionPointer m_identity;
		FunctionFunc m_call;
	};

	class _refl_ MUD_OBJ_EXPORT Method : public Callable
	{
	public:
		Method(Type& object_type, cstring name, Address address, MethodFunc method, const ParamVector& params = {}, Var returnval = Var());

		virtual void operator()(array<Var> args, Var& result) const { return m_call(args[0], array<Var>{ args, 1 }, result); }

		Type* m_object_type;
		Address m_address;
		MethodFunc m_call;
	};

	enum class ConstructorIndex : unsigned int
	{
		Default = 0,
		Proto = 0,
		ProtoParts = 1
	};

	class _refl_ MUD_OBJ_EXPORT Constructor : public Callable
	{
	public:
		Constructor(Type& object_type, ConstructorFunc func, const ParamVector& params = {});

		virtual void operator()(array<Var> args, Var& result) const { UNUSED(result); m_call(args[0], array<Var>{ args, 1 }); }

		Type* m_object_type;
		ConstructorFunc m_call;
	};

	class _refl_ MUD_OBJ_EXPORT CopyConstructor : public Callable
	{
	public:
		CopyConstructor(Type& object_type, CopyConstructorFunc func);

		virtual void operator()(array<Var> args, Var& result) const { UNUSED(result); m_call(args[0], args[1]); }

		Type* m_object_type;
		CopyConstructorFunc m_call;
	};

	class _refl_ MUD_OBJ_EXPORT Destructor : public Callable
	{
	public:
		Destructor(Type& object_type, DestructorFunc func);

		virtual void operator()(array<Var> args, Var& result) const { UNUSED(result); m_call(args[0]); }

		Type* m_object_type;
		DestructorFunc m_call;
	};

	struct _refl_ MUD_OBJ_EXPORT Call
	{
	public:
		_constr_ Call();
		_constr_ Call(const Callable& callable, std::vector<Var> arguments);
		Call(const Callable& callable);
		Call(const Callable& callable, Ref object);

		bool validate();

		const Var& operator()();
		const Var& operator()(Ref object);

		/*_attr_*/ const Callable* m_callable = nullptr;
		_attr_ std::vector<Var> m_arguments;
		_attr_ Var m_result;
	};

	template<typename T_Function>
	inline FunctionPointer function_id(T_Function func) { return reinterpret_cast<FunctionPointer>(func); }

	template<typename T_Return, typename T, typename... T_Params>
	inline Method& method(T_Return(T::*meth)(T_Params...)) { return type<T>().m_meta->method(member_address(meth)); }

	template <typename T_Function>
	inline Function& function(T_Function func);
}

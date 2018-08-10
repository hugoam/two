//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Array.h>
#include <infra/Strung.h>
#include <refl/Forward.h>
#include <obj/Type.h>
#include <obj/Var.h>

#ifndef MUD_CPP_20
#include <functional>
#include <vector>
#include <memory>
#endif

namespace mud
{
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
		Signature(const std::vector<Param>& params = {}, const Var& returnval = Var());

		std::vector<Param> m_params;
		Var m_returnval;
	};

	
	export_ class refl_ MUD_REFL_EXPORT Callable
	{
	public:
		Callable(cstring name, const std::vector<Param>& params = {}, Var returnval = Var());
		virtual ~Callable() {}

		void setup();

		bool validate(array<Var> args, size_t offset = 0) const;

		virtual void operator()(array<Var> args) const { Var none; return (*this)(args, none); }
		virtual void operator()(array<Var> args, Var& result) const = 0;

		uint32_t m_index;
		cstring m_name;
		Var m_returnval;
		std::vector<Param> m_params;
		size_t m_num_defaults;

		std::vector<Var> m_arguments;

		bool checkArgs(const std::vector<Var>& args) const { for(const Param& param : m_params) if(!type(args[param.m_index]).is(type(param.m_value))) return false; return true; }
	};

	export_ class refl_ MUD_REFL_EXPORT Function final : public Callable
	{
	public:
		Function(Namespace* location, cstring name, FunctionPointer identity, FunctionFunc function, const std::vector<Param>& params = {}, Var returnval = Var());

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
		Method(Type& object_type, cstring name, Address address, MethodFunc method, const std::vector<Param>& params = {}, Var returnval = Var());

		virtual void operator()(array<Var> args, Var& result) const { return m_call(args[0], array<Var>{ args, 1 }, result); }

		Type* m_object_type;
		Address m_address;
		MethodFunc m_call;
	};

	export_ using VirtualMethod = std::function<void(Method&, Ref, array<Var>)>;

	export_ template <> MUD_REFL_EXPORT Type& type<VirtualMethod>();

	export_ enum class ConstructorIndex : unsigned int
	{
		Default = 0,
		Proto = 0,
		ProtoParts = 1
	};

	export_ class refl_ MUD_REFL_EXPORT Constructor final : public Callable
	{
	public:
		Constructor(Type& object_type, ConstructorFunc func, const std::vector<Param>& params = {});

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
		constr_ Call(const Callable& callable, std::vector<Var> arguments);
		Call(const Callable& callable);
		Call(const Callable& callable, Ref object);

		bool validate();

		const Var& operator()();
		const Var& operator()(Ref object);

		const Callable* m_callable = nullptr;
		attr_ std::vector<Var> m_arguments;
		attr_ Var m_result;
	};

	export_ template<typename T_Function>
	inline FunctionPointer function_id(T_Function func) { return reinterpret_cast<FunctionPointer>(func); }

	export_ template <typename T_Function>
	inline Function& function(T_Function func);
}

//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <type/Type.h>
#include <type/Ref.h>
#include <refl/Forward.h>

#include <cstdint>

namespace mud
{
	export_ using cstring = const char*;

	export_ using FunctionPointer = void* (*)();

	export_ using ConstructorFunc = void(*)(void*, array<void*>);
	export_ using CopyConstructorFunc = void(*)(void*, void*);
	export_ using DestructorFunc = void(*)(void*);
	export_ using MethodFunc = void(*)(void*, array<void*>, void*&);
	export_ using FunctionFunc = void(*)(array<void*>, void*&);

	export_ struct refl_ MUD_REFL_EXPORT QualType
	{
		enum Flags
		{
			None = 0,
			Pointer = (1 << 0),
			Reference = (1 << 1),
			Const = (1 << 2),
		};

		Type* m_type;
		Flags m_flags;

		bool isvoid() const;

		bool operator==(const QualType& other) const;
		bool operator!=(const QualType& other) const;
	};

	export_ extern Type* g_void;
	export_ extern QualType g_qvoid;

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
		Param() {}
		Param(cstring name, Type& type, Flags flags = None, void* default_val = nullptr);
		
		size_t m_index = 0;
		cstring m_name = nullptr;
		Type* m_type = nullptr;
		Flags m_flags = None;
		void* m_default = nullptr;

		Ref default_val() const { return Ref(m_default, *m_type); }

		bool nullable() const { return (m_flags & Nullable) != 0; }
		bool reference() const { return (m_flags & Reference) != 0; }
		bool defaulted() const { return (m_flags & Default) != 0; }
		bool output() const { return (m_flags & Output) != 0; }
	};

	export_ class refl_ MUD_REFL_EXPORT Signature
	{
	public:
		Signature(const vector<Param>& params = {}, QualType return_type = g_qvoid);

		vector<Param> m_params;
		QualType m_return_type;
	};

	
	export_ class refl_ MUD_REFL_EXPORT Callable
	{
	public:
		Callable(cstring name, const vector<Param>& params = {}, QualType return_type = g_qvoid);
		virtual ~Callable() {}

		void setup();

		bool validate(array<void*> args, size_t offset = 0) const;

		void operator()(array<Ref> args) const;
		void operator()(array<Ref> args, Ref& result) const;

		//virtual void operator()(array<void*> args) const; // { Var none; return (*this)(args, none); }
		//virtual void operator()(array<void*> args, void*& result) const = 0;

		uint32_t m_index;
		cstring m_name;

		vector<Param> m_params;
		QualType m_return_type;
		size_t m_num_defaults;
		size_t m_num_required;

		//vector<Var> m_arguments;

		//bool checkArgs(const vector<Var>& args) const; // { for (const Param& param : m_params) if (!type(args[param.m_index]).is(type(param.m_value))) return false; return true; }
	};

	export_ class refl_ MUD_REFL_EXPORT Function final : public Callable
	{
	public:
		Function();
		Function(Namespace* location, cstring name, FunctionPointer identity, FunctionFunc function, const vector<Param>& params = {}, QualType return_type = g_qvoid);

		virtual void operator()(array<void*> args, void*& result) const; // { return m_call(args, result); }

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
		Method();
		Method(Type& object_type, cstring name, Address address, MethodFunc method, const vector<Param>& params = {}, QualType return_type = g_qvoid);

		virtual void operator()(array<void*> args, void*& result) const; // { return m_call(args[0], array<void*>{ args, 1 }, result); }

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
		Constructor();
		Constructor(Type& object_type, ConstructorFunc func, const vector<Param>& params = {});
		Constructor(Type& object_type, cstring name, ConstructorFunc func, const vector<Param>& params = {});

		virtual void operator()(array<void*> args, void*& result) const; // { UNUSED(result); m_call(args[0], array<void*>{ args, 1 }); }

		size_t m_index;
		Type* m_object_type;
		ConstructorFunc m_call;
	};

	export_ class refl_ MUD_REFL_EXPORT CopyConstructor final : public Callable
	{
	public:
		CopyConstructor();
		CopyConstructor(Type& object_type, CopyConstructorFunc func);

		virtual void operator()(array<void*> args, void*& result) const; // { UNUSED(result); m_call(args[0], args[1]); }

		Type* m_object_type;
		CopyConstructorFunc m_call;
	};

	export_ class refl_ MUD_REFL_EXPORT Destructor final: public Callable
	{
	public:
		Destructor();
		Destructor(Type& object_type, DestructorFunc func);

		virtual void operator()(array<void*> args, void*& result) const; // { UNUSED(result); m_call(args[0]); }

		Type* m_object_type;
		DestructorFunc m_call;
	};

	export_ template<typename T_Function>
	inline FunctionPointer funcptr(T_Function func) { return reinterpret_cast<FunctionPointer>(func); }

	export_ template <typename T_Function>
	inline Function& func(T_Function func);
}

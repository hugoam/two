//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <stl/algorithm.h>
#include <type/Types.h>
#include <refl/Method.h>
#include <refl/Meta.h>
#include <refl/Class.h>
#include <refl/VirtualMethod.h>
#endif

namespace mud
{
	bool QualType::isvoid() const { return m_type == &type<void>(); }

	bool QualType::operator==(const QualType& other) const { return m_flags == other.m_flags && m_type == other.m_type; }
	bool QualType::operator!=(const QualType& other) const { return !(*this == other); }

	QualType g_qvoid = { &type<void>(), QualType::None };

	//template class function<void(Method&, Ref, span<Var>)>;

	template <> Type& type<VirtualMethod>() { static Type ty("VirtualMethod"); return ty; }

	Param::Param(cstring name, Type& type, Flags flags, void* default_val)
		: m_name(name)
		, m_type(&type)
		, m_flags(flags)
		, m_default(default_val)
	{
		//if(value == Ref())
		//	m_flags = static_cast<Flags>(m_flags | Nullable);
	}

	Signature::Signature(const vector<Param>& params, QualType return_type)
		: m_params(params)
		, m_return_type(return_type)
	{}

	static uint32_t s_callable_index = 0;

	Callable::Callable() {}
	Callable::Callable(cstring name, const vector<Param>& params, QualType return_type)
		: m_index(++s_callable_index)
		, m_name(name)
		, m_params(params)
		, m_return_type(return_type)
		, m_num_defaults(0)
	{
		this->setup();
	}

	void Callable::setup()
	{
		for(size_t i = 0; i < m_params.size(); ++i)
		{
			m_params[i].m_index = i;

			if(m_num_defaults == 0 && m_params[i].defaulted())
				m_num_defaults = m_params.size() - i;
		}
		
		m_num_required = m_params.size() - m_num_defaults;
	}

	bool Callable::validate(span<Var> args, size_t offset) const
	{
		if(args.m_count < m_params.size() - m_num_defaults)
			return false;

		bool valid = true;
		for(size_t i = offset; i < m_params.size(); ++i)
		{
			valid &= m_params[i].m_type->is(type(args[i]));
			valid &= m_params[i].nullable() || !args[i].null();
		}
		return valid;
	}

	void Callable::operator()(span<void*> args) const
	{
		void* none;
		return (*this)(args, none);
	}

	void Callable::operator()(span<void*> args, void*& result) const
	{
		UNUSED(args); UNUSED(result);
	}

	Function::Function() {}
	Function::Function(Namespace* location, cstring name, FunctionPointer identity, FunctionFunc trigger, const vector<Param>& params, QualType return_type)
		: Callable(name, params, return_type)
		, m_namespace(location)
		, m_identity(identity)
		, m_call(trigger)
	{
		Operator op = as_operator(*this);
		if(op && is_class(*op.m_type))
		{
			cls(*op.m_type).m_operators.push_back(op);
		}
	}

	void Function::operator()(span<void*> args, void*& result) const
	{
		return m_call(args, result);
	}

	Operator as_operator(Function& function)
	{
		if(function.m_name == string("add"))
		{
			return { &function, function.m_params[0].m_type, function.m_name, "+" };
		}
		else if(function.m_name == string("subtract"))
		{
			return { &function, function.m_params[0].m_type, function.m_name, "-" };
		}
		else if(function.m_name == string("multiply"))
		{
			return { &function, function.m_params[0].m_type, function.m_name, "*" };
		}
		else if(function.m_name == string("divide"))
		{
			return { &function, function.m_params[0].m_type, function.m_name,  "/" };
		}
		else return {};
	}

	Method::Method() {}
	Method::Method(Type& object_type, cstring name, Address address, MethodFunc trigger, const vector<Param>& params, QualType return_type)
		: Callable(name, merge({ 1, { "self", object_type } }, params), return_type)
		, m_object_type(&object_type)
		, m_address(address)
		, m_call(trigger)
	{}

	void Method::operator()(span<void*> args, void*& result) const
	{
		return m_call(args[0], span<void*>{ args, 1 }, result);
	}

	Constructor::Constructor() {}
	Constructor::Constructor(Type& object_type, ConstructorFunc constructor, const vector<Param>& params)
		: Callable(object_type.m_name, merge({ 1, { "self", object_type } }, params))
		, m_object_type(&object_type)
		, m_call(constructor)
	{}

	Constructor::Constructor(Type& object_type, cstring name, ConstructorFunc constructor, const vector<Param>& params)
		: Callable(name, merge({ 1, { "self", object_type } }, params))
		, m_object_type(&object_type)
		, m_call(constructor)
	{}

	void Constructor::operator()(span<void*> args, void*& result) const
	{
		UNUSED(result); m_call(args[0], span<void*>{ args, 1 });
	}

	CopyConstructor::CopyConstructor() {}
	CopyConstructor::CopyConstructor(Type& object_type, CopyConstructorFunc constructor)
		: Callable(object_type.m_name, { 1, { "self", object_type } })
		, m_object_type(&object_type)
		, m_call(constructor)
	{}

	void CopyConstructor::operator()(span<void*> args, void*& result) const
	{
		UNUSED(result); m_call(args[0], args[1]);
	}

	Destructor::Destructor() {}
	Destructor::Destructor(Type& object_type, DestructorFunc destructor)
		: Callable(object_type.m_name, { 1, { "self", object_type } })
		, m_object_type(&object_type)
		, m_call(destructor)
	{}

	void Destructor::operator()(span<void*> args, void*& result) const
	{
		UNUSED(result); m_call(args[0]);
	}
}

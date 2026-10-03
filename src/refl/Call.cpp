//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.refl;

namespace two
{
	vector<Var> arguments(const Callable& callable)
	{
		vector<Var> args;
		for(const Param& p : callable.m_params)
			args.push_back(p.storage_var());
		return args;
	}

	Var QualType::storage_var() const
	{
		Var value = meta(*m_type).m_empty_var;
		if(!value) value = Ref(*m_type);
		return value;
	}

	Var Param::storage_var() const
	{
		Var value = meta(*m_type).m_empty_var;
		if(!value) value = Ref(*m_type);
		if(defaulted())
			value.copy(Ref(m_default, *m_type));
		return value;
	}

	Call::Call()
	{}

	Call::Call(const Callable& callable, vector<Var> args)
		: m_callable(&callable)
		, m_args(args)
		, m_vargs(args.size(), nullptr)
	{
		if(!callable.m_return_type.isvoid())
			m_args.push_back(callable.m_return_type.storage_var());
		this->prepare();
	}

	Call::Call(const Callable& callable)
		: Call(callable, arguments(callable))//, callable.m_args)
	{}

	Call::Call(const Callable& callable, Ref object)
		: Call(callable)
	{
		m_args[0] = object;
		this->prepare();
	}

	Call::Call(const Call& other)
		: m_callable(other.m_callable)
		, m_args(other.m_args)
	{
		this->prepare();
	}

	Call& Call::operator=(const Call& other)
	{
		m_callable = other.m_callable;
		m_args = other.m_args;
		this->prepare();
		return *this;
	}

	void Call::prepare()
	{
		m_vargs.resize(m_args.size(), nullptr);
		for(size_t i = 0; i < m_args.size(); ++i)
			m_vargs[i] = m_args[i].m_ref.m_value;
	}

	bool Call::validate() { return m_callable && m_callable->validate(m_args); }

	const Var& Call::operator()()
	{
		(*m_callable)(m_vargs, result().m_ref.m_value);
		return result();
	}

	const Var& Call::operator()(Ref object)
	{
		m_args[0] = object; m_vargs[0] = object.m_value;
		(*m_callable)(m_vargs, result().m_ref.m_value);
		return result();
	}
}

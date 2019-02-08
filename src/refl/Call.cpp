//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <stl/algorithm.h>
#include <refl/Call.h>
#include <refl/Meta.h>
//#include <refl/Class.h>
//#include <refl/VirtualMethod.h>
#endif

namespace mud
{
	vector<Var> arguments(const Callable& callable)
	{
		vector<Var> args;
		for(const Param& p : callable.m_params)
		{
			Var t = meta(*p.m_type).m_empty_var;
			if(p.defaulted())
				args.push_back(Ref(p.m_default, *p.m_type));
			else if(is_base_type(*p.m_type))
				args.push_back(meta(*p.m_type).m_empty_var);
			else
				args.push_back(Ref(*p.m_type));
		}
		return args;
	}

	Call::Call()
	{}

	Call::Call(const Callable& callable, vector<Var> args)
		: m_callable(&callable)
		, m_args(args)
		, m_vargs(args.size(), nullptr)
	{
		if(!callable.m_return_type.isvoid())
		{
			Type& return_type = *callable.m_return_type.m_type;
			if(is_base_type(return_type))
				m_result = meta(return_type).m_empty_var;
			else
				m_result = Ref(return_type);
		}
		this->prepare();
	}

	Call::Call(const Callable& callable)
		: Call(callable, arguments(callable))//, callable.m_args)
	{}

	Call::Call(const Callable& callable, Ref object)
		: Call(callable)
	{
		m_args[0] =  object;
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
		(*m_callable)(m_vargs, m_result.m_ref.m_value);
		return m_result;
	}

	const Var& Call::operator()(Ref object)
	{
		m_args[0] = object; m_vargs[0] = object.m_value;
		(*m_callable)(m_vargs, m_result.m_ref.m_value);
		return m_result;
	}
}

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
	Call::Call()
	{}

	Call::Call(const Callable& callable, vector<Var> args)
		: m_callable(&callable)
		, m_args(args)
		, m_result(meta(*callable.m_return_type.m_type).m_empty_var)
	{}

	Call::Call(const Callable& callable)
		: Call(callable, vector<Var>{})//, callable.m_args)
	{}

	Call::Call(const Callable& callable, Ref object)
		: Call(callable)
	{
		m_args[0] =  object;
	}

	void Call::prepare()
	{
		for (size_t i = 0; i < m_args.size(); ++i)
			m_vargs[i] = m_args[i].m_ref.m_value;
	}

	bool Call::validate() { return m_callable && m_callable->validate(m_args); }

	const Var& Call::operator()() { (*m_callable)(m_vargs, m_result.m_ref.m_value); return m_result; }
	const Var& Call::operator()(Ref object) { m_args[0] = object; (*m_callable)(m_vargs, m_result.m_ref.m_value); return m_result; }
}

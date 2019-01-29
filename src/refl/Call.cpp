//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <infra/Vector.h>
#include <refl/Call.h>
#include <refl/Meta.h>
//#include <refl/Class.h>
//#include <refl/VirtualMethod.h>
#endif

namespace mud
{
	Call::Call()
	{}

	Call::Call(const Callable& callable, vector<Var> arguments)
		: m_callable(&callable)
		, m_arguments(arguments)
		, m_result(meta(*callable.m_return_type.m_type).m_empty_var)
	{}

	Call::Call(const Callable& callable)
		: Call(callable, vector<Var>{})//, callable.m_arguments)
	{}

	Call::Call(const Callable& callable, Ref object)
		: Call(callable)
	{
		m_arguments[0] =  object;
	}

	//bool Call::validate() { return m_callable && m_callable->validate(to_array(m_arguments)); }

	//const Var& Call::operator()() { (*m_callable)(to_array(m_arguments), m_result); return m_result; }
	//const Var& Call::operator()(Ref object) { m_arguments[0] = object; (*m_callable)(to_array(m_arguments), m_result); return m_result; }
}

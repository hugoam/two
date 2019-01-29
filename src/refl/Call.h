//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <type/Var.h>
#include <refl/Forward.h>
#include <refl/Method.h>

namespace mud
{
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
}

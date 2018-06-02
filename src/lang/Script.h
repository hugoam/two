//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Reflect/Method.h>
#include <lang/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <string>
#endif

namespace mud
{
	using string = std::string;

	export_ class _refl_ MUD_LANG_EXPORT Script : public Callable
	{
	public:
		_constr_ Script(cstring name, const Signature& signature = {});
		~Script();

		_attr_ uint32_t m_index;
		_attr_ string m_name;
		_attr_ bool m_locked;

		Signature m_signature;

		string m_script;

		LuaInterpreter* m_interpreter;

		using Callable::operator();
		virtual void operator()(array<Var> args, Var& result) const;
	};
}

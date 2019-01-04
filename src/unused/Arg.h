//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Any.h>
#include <obj/Reflect/Class.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	struct MUD_TYPE_EXPORT Arg
	{
		template <class T_Value, class T_Object, class T_Arg>
		Arg(T_Value T_Object::* mem, T_Arg val) : object_type(&type<T_Object>()), member(member_address(mem)), value(make_var<T_Value>(T_Value(val))) {}

		Arg(Type* type, Address mem, Var val) : object_type(type), member(mem), value(val) {}

		Type* object_type;
		Address member;
		Var value;
	};

	struct MUD_TYPE_EXPORT Args
	{
		Args() : m_args() {}
		Args(std::vector<Arg> args) : m_args(args) {}
		std::vector<Arg> m_args;
	};

	inline void set_args(Ref object, const Args& args)
	{
		for(const Arg& arg : args.m_args)
			if(arg.object_type == &object.type())
			{
				Member& member = cls(object).member(arg.member);
				member.set(object, arg.value.m_ref);
			}
	}
}

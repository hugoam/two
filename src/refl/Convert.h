//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <refl/Meta.h>
#include <obj/DoubleDispatch.h>
#include <obj/DispatchDecl.h>
#include <infra/Global.h>
#include <infra/String.h>

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Convert
	{
	public:
		std::function<void(const Var&, string&)> m_to_string;
		std::function<void(const string&, Ref)> m_from_string;
	};

	export_ MUD_REFL_EXPORT string to_name(Type& type, Ref value);
	export_ inline string to_name(Ref value) { return to_name(type(value), value); }

	export_ template <>
	inline void to_string<Ref>(const Ref& object, string& str) { convert(*object.m_type).m_to_string(object, str); }

	export_ template <>
	inline void to_string<Var>(const Var& value, string& str) { convert(type(value)).m_to_string(value, str); }

	export_ template <class T_Source, class T_Dest>
	void convert(T_Source& from, T_Dest& to)
	{
		to = static_cast<T_Dest>(from);
	}

	export_ template <class T_Source, class T_Dest>
	void copy_convert(T_Source& from, T_Dest& to)
	{
		to = T_Dest(from);
	}

	export_ class MUD_REFL_EXPORT TypeConverter : public DoubleDispatch, public LazyGlobal<TypeConverter>
	{
	public:
		TypeConverter();

		bool check(Type& input, Type& output);
		bool check(Ref input, Type& output);
		Var convert(Ref input, Type& output);
		void convert(Ref input, Type& output, Var& result);

		template <class T_First, class T_Second>
		void default_converter()
		{
			dispatch_branch<T_First, T_Second, copy_convert<T_First, T_Second>>(*this);
			dispatch_branch<T_Second, T_First, copy_convert<T_Second, T_First>>(*this);
		}
	};
}

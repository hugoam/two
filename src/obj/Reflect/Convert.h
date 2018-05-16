//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Reflect/Meta.h>
#include <obj/Util/DoubleDispatch.h>
#include <obj/Util/DispatchDecl.h>
#include <obj/Util/Global.h>
#include <obj/String/String.h>

namespace mud
{
	class _refl_ MUD_OBJ_EXPORT Convert
	{
	public:
		std::function<void(const Var&, string&)> m_to_string;
		std::function<void(const string&, Ref)> m_from_string;
	};

	string to_name(Type& type, Ref value);

	template <> inline void to_string<Ref>(const Ref& object, string& str) { object.type().m_convert->m_to_string(object, str); }
	template <> inline void to_string<Var>(const Var& value, string& str) { value.type().m_convert->m_to_string(value, str); }

	template <class T_Source, class T_Dest>
	void convert(T_Source& from, T_Dest& to)
	{
		to = static_cast<T_Dest>(from);
	}

	template <class T_Source, class T_Dest>
	void copy_convert(T_Source& from, T_Dest& to)
	{
		to = T_Dest(from);
	}

	class MUD_OBJ_EXPORT TypeConverter : public DoubleDispatch, public LazyGlobal<TypeConverter>
	{
	public:
		TypeConverter();

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

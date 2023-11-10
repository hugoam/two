//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <infra/Global.h>
#include <infra/StringOps.h>
#include <type/DoubleDispatch.h>
#include <type/DispatchDecl.h>
#endif
#include <refl/Forward.h>
#include <refl/Meta.h>

namespace two
{
	export_ TWO_REFL_EXPORT string to_name(const Type& type, Ref value);
	export_ inline string to_name(Ref value) { return to_name(type(value), value); }

	export_ template <>
	inline void to_string<Ref>(const Ref& object, string& str) { convert(*object.m_type).m_to_string(object.m_value, str); }

#ifndef TWO_MODULES
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
#endif

	export_ class TWO_REFL_EXPORT TypeConverter : public DoubleDispatch, public LazyGlobal<TypeConverter>
	{
	public:
		TypeConverter();

		bool check(const Type& input, const Type& output);
		bool check(Ref input, const Type& output);
		Var convert(Ref input, const Type& output);
		void convert(Ref input, const Type& output, Var& result);

		template <class T_First, class T_Second>
		void default_converter()
		{
#ifndef TWO_MODULES
			// @todo modules
			dispatch_branch<T_First, T_Second, copy_convert<T_First, T_Second>>(*this);
			dispatch_branch<T_Second, T_First, copy_convert<T_Second, T_First>>(*this);
#endif
		}
	};
}

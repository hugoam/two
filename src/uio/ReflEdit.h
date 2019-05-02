//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/algorithm.h>
#include <type/Ref.h>
#include <refl/Enum.h>
#include <ui/Ui.h>
#endif
#include <uio/Forward.h>

namespace two
{
namespace ui
{
	template <class T>
	inline bool enum_input(Widget& parent, T& value)
	{
		Enum& e = enu<T>();
		uint32_t index = e.index(Ref(&value));
		//ui::radio_switch(parent, e.m_names, index);
		if(ui::dropdown_input(parent, e.m_names, index))
		{
			e.varn(index, Ref(&value));
			return true;
		}
		return false;
	}

	template <class T>
	inline bool enum_field(Widget& parent, cstring name, T& value, bool reverse = false) { return do_field([&](Widget& self) { return enum_input<T>(self, value); }, parent, name, reverse); }
}

	export_ TWO_UIO_EXPORT void set_meta_palette(span<uint32_t> palette);

	export_ TWO_UIO_EXPORT void meta_description(Widget& parent, Type& type);

	export_ TWO_UIO_EXPORT void meta_constructors(Widget& parent, Class& cls);
	export_ TWO_UIO_EXPORT void meta_methods(Widget& parent, Class& cls);
	export_ TWO_UIO_EXPORT void meta_fields(Widget& parent, Class& cls);

	export_ TWO_UIO_EXPORT void meta_enum(Widget& parent, Enum& enu);

	export_ TWO_UIO_EXPORT void meta_synopsis(Widget& parent, Function& function);
	export_ TWO_UIO_EXPORT void meta_synopsis(Widget& parent, Method& method);
	export_ TWO_UIO_EXPORT void meta_synopsis(Widget& parent, Type& type);

	export_ TWO_UIO_EXPORT void class_edit(Widget& parent, Class& cls);
	export_ TWO_UIO_EXPORT void meta_edit(Widget& parent, Type& type);

	export_ TWO_UIO_EXPORT void meta_browser(Widget& parent, Module& m);
	export_ TWO_UIO_EXPORT void meta_browser(Widget& parent);

	export_ TWO_UIO_EXPORT void type_browser(Widget& parent);
}

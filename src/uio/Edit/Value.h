//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Global.h>
#include <obj/Dispatch.h>
#include <math/Stat.h>
#endif
#include <uio/Forward.h>
#include <uio/Edit/Inspector.h>

namespace mud
{
	export_ class MUD_UIO_EXPORT DispatchInput : public Dispatch<bool, Widget&>, public LazyGlobal<DispatchInput>
	{
	public:
		DispatchInput();
	};

	export_ MUD_UIO_EXPORT bool type_selector(Widget& parent, size_t& type, array<Type*> types);

	export_ MUD_UIO_EXPORT bool value_edit(Widget& parent, Ref& value);
	export_ MUD_UIO_EXPORT bool none_edit(Widget& parent, Ref& value);
	export_ MUD_UIO_EXPORT bool enum_edit(Widget& parent, Ref& value);
	export_ MUD_UIO_EXPORT bool object_link_edit(Widget& parent, Ref& value);
	export_ MUD_UIO_EXPORT bool sequence_element_edit(Widget& parent, Ref& value);
	export_ MUD_UIO_EXPORT bool sequence_edit(Widget& parent, Ref& value, EditorHint hint = EditorHint::Rows);

	export_ MUD_UIO_EXPORT bool any_edit(Widget& parent, Ref& ref, bool link = false, EditorHint hint = EditorHint::Rows);

	export_ MUD_UIO_EXPORT bool field_edit(Widget& parent, cstring name, Ref& ref, bool nullable);
	export_ MUD_UIO_EXPORT bool modal_edit(Widget& parent, uint32_t mode, cstring name, Ref& ref, bool nullable, bool confirm = false);

	export_ template <class T_Value>
	bool select_value(Widget& parent, uint32_t mode, T_Value& value, bool confirm = true)
	{
		Ref ref = Ref(&value);
		return modal_edit(parent, mode, type<T_Value>().m_name, ref, false, confirm);
	}
}

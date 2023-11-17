//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Forward.h>
#include <uio/Inspector.h>

namespace two
{
	export_ class TWO_UIO_EXPORT DispatchInput : public Dispatch<bool, Widget&>, public Global<DispatchInput>
	{
	public:
		DispatchInput();
	};

	export_ TWO_UIO_EXPORT bool type_selector(Widget& parent, uint32_t& type, span<Type*> types);

	export_ TWO_UIO_EXPORT bool value_edit(Widget& parent, Ref& value);
	export_ TWO_UIO_EXPORT bool none_edit(Widget& parent, Ref& value);
	export_ TWO_UIO_EXPORT bool enum_edit(Widget& parent, Ref& value);
	export_ TWO_UIO_EXPORT bool object_link_edit(Widget& parent, Ref& value);
	export_ TWO_UIO_EXPORT bool sequence_element_edit(Widget& parent, Ref& value);
	export_ TWO_UIO_EXPORT bool sequence_edit(Widget& parent, Ref& value, EditorHint hint = EditorHint::Rows);

	export_ TWO_UIO_EXPORT bool any_edit(Widget& parent, Ref& ref, bool link = false, EditorHint hint = EditorHint::Rows);

	export_ TWO_UIO_EXPORT bool field_edit(Widget& parent, cstring name, Ref& ref, bool nullable);
	export_ TWO_UIO_EXPORT bool modal_edit(Widget& parent, uint32_t mode, cstring name, Ref& ref, bool nullable, bool confirm = false);

	export_ template <class T_Value>
	bool select_value(Widget& parent, uint32_t mode, T_Value& value, bool confirm = true)
	{
		Ref ref = Ref(&value);
		return modal_edit(parent, mode, type<T_Value>().m_name, ref, false, confirm);
	}
}

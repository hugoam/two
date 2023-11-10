//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <ecs/Entity.h>
#endif
#include <uio/Forward.h>

namespace two
{
	export_ enum class refl_ EditNestMode : unsigned int
	{
		Inline,
		Modal,
		Embed
	};

	struct TWO_UIO_EXPORT EditSpec
	{
		EditSpec() {}
		EditSpec(Class& cls);
		bool m_setup = false;
		EditNestMode m_nest_mode[2] = { EditNestMode::Inline, EditNestMode::Inline };
	};

	extern TWO_UIO_EXPORT vector<EditSpec> g_edit_specs;
	
	export_ enum class refl_ EditorHint : unsigned int
	{
		Table,
		Rows,
		Inline
	};

	export_ TWO_UIO_EXPORT func_ bool object_edit_inline(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT func_ bool object_edit_rows(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT func_ bool object_edit_columns(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT func_ bool object_edit_table(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT func_ bool object_edit_expandbox(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT func_ bool object_edit(Widget& parent, Ref object, EditorHint hint = EditorHint::Table);

	export_ TWO_UIO_EXPORT func_ bool entity_edit(Widget& parent, Entity entity, EditorHint hint = EditorHint::Table);

	export_ TWO_UIO_EXPORT func_ bool inspector(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT func_ bool inspector(Widget& parent, Entity entity);
	export_ TWO_UIO_EXPORT func_ bool inspector(Widget& parent);
	export_ TWO_UIO_EXPORT func_ void multi_inspector(Widget& parent, Type& type, vector<Var>& objects, size_t& selected);

	export_ TWO_UIO_EXPORT func_ void multi_object_edit(Widget& parent, Type& type, vector<Ref> objects);

	template <class T_Object>
	T_Object* deref(unique<T_Object>& element) { return element.get(); }

#ifdef TWO_MEMORY_TRACKING
	template <class T_Object>
	T_Object* deref(object<T_Object>& element) { return element.get(); }
#endif

	template <class T_Object>
	T_Object* deref(T_Object* element) { return element; }

	template <class T_Object, class T_Container>
	void multi_object_edit_container(Widget& parent, T_Container& container)
	{
		vector<Ref> objects;
		for(auto& element : container)
			objects.push_back(deref<T_Object>(element));
		multi_object_edit(parent, type<T_Object>(), objects);
	}
}

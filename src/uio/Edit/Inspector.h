//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Forward.h>
#include <uio/Unode.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ enum class refl_ EditNestMode : unsigned int
	{
		Inline,
		Modal,
		Embed
	};

	struct MUD_UIO_EXPORT EditSpec
	{
		EditSpec() {}
		EditSpec(Class& cls);
		bool m_setup = false;
		EditNestMode m_nest_mode[2] = { EditNestMode::Inline, EditNestMode::Inline };
	};

	export_ extern MUD_UIO_EXPORT std::vector<EditSpec> g_edit_specs;
	
	export_ enum class refl_ EditorHint : unsigned int
	{
		Table,
		Rows,
		Inline
	};

	export_ MUD_UIO_EXPORT func_ bool object_edit_inline(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT func_ bool object_edit_rows(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT func_ bool object_edit_columns(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT func_ bool object_edit_table(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT func_ bool object_edit_expandbox(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT func_ bool object_edit(Widget& parent, Ref object, EditorHint hint = EditorHint::Table);

	export_ MUD_UIO_EXPORT func_ bool entity_edit(Widget& parent, Entity entity, EditorHint hint = EditorHint::Table);

	export_ MUD_UIO_EXPORT func_ bool inspector(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT func_ bool inspector(Widget& parent, Entity entity);
	export_ MUD_UIO_EXPORT func_ bool inspector(Widget& parent);
	export_ MUD_UIO_EXPORT func_ void multi_inspector(Widget& parent, Type& type, std::vector<Var>& objects, size_t& selected);

	export_ MUD_UIO_EXPORT func_ void multi_object_edit(Widget& parent, Type& type, std::vector<Ref> objects);

	//template <class T_Object>
	//T_Object* deref(std::pair<const string, unique_ptr<T_Object>>& element) { return element.second.get(); }

	template <class T_Object>
	T_Object* deref(unique_ptr<T_Object>& element) { return element.get(); }

#ifdef MUD_MEMORY_TRACKING
	template <class T_Object>
	T_Object* deref(object_ptr<T_Object>& element) { return element.get(); }
#endif

	template <class T_Object>
	T_Object* deref(T_Object* element) { return element; }

	template <class T_Object, class T_Container>
	void multi_object_edit_container(Widget& parent, T_Container& container)
	{
		std::vector<Ref> objects;
		for(auto& element : container)
			objects.push_back(deref<T_Object>(element));
		multi_object_edit(parent, type<T_Object>(), objects);
	}
}

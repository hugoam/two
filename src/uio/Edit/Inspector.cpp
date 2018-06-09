//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <infra/Vector.h>
#include <obj/Any.h>
#ifdef MUD_PROTO
#include <proto/Complex.h>
#endif
#include <refl/Class.h>
#include <uio/Edit/Inspector.h>
#include <ui/Structs/Container.h>
#include <uio/Edit/Value.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Injector.h>
#include <uio/Edit/Reflection.h>
#endif

namespace mud
{
	struct EditState : public NodeState
	{
		Ref object = {};
	};

	inline Ref safe_target(Member& member, Ref object)
	{
		Ref target = object;
		if(object.m_type != member.m_object_type && g_class[object.type().m_id])
			target = cls(object).upcast(object, *member.m_object_type);
		return target;
	}

	inline Var get_safe(Member& member, Ref object)
	{
		Var result = member.m_default_value;
		result = member.get(safe_target(member, object));
		return result;
	}

	inline void set_safe(Member& member, Ref object, Ref value)
	{
		member.set(safe_target(member, object), value);
	}

	bool member_edit(Widget& parent, Ref object, Member& member, EditorHint hint = EditorHint::Inline)
	{
		Var value = get_safe(member, object);
		bool changed = any_edit(parent, value.m_ref, member.is_link(), hint);

		if(changed && member.is_mutable())
			set_safe(member, object, value);
		
		return changed;
	}

	bool member_named_edit(Widget& parent, Ref object, Member& member)
	{
		Widget& self = ui::table_row(parent);
		ui::label(self, member.m_name);
		return member_edit(self, object, member);
	}

	bool member_toggle_edit(Widget& parent, Ref object, Member& member)
	{
		Widget& self = ui::row(parent);
		if(ui::modal_button(self, self, "Edit", 1))
		{
			Widget& modal = ui::modal(self.parent_modal());
			return member_edit(modal, object, member, EditorHint::Table);
		}
		return false;
	}

	bool member_nested_edit(Widget& parent, Ref object, Member& member)
	{
		Widget& row = ui::row(parent);
		Widget* body = ui::tree_node(row, member.m_name, false, true).m_body;
		if(body)
			return member_edit(*body, object, member, EditorHint::Rows);
		return false;
	}

	bool nested_object(Member& member)
	{
		return (is_struct(*member.m_type)|| is_object(*member.m_type)) && !member.is_link();
	}

	bool object_edit_rows(Widget& parent, Ref object)
	{
		bool changed = false;
		for(Member& member : cls(object).m_members)
			//if(nested_object(member))
			//	changed |= member_nested_edit(parent, object, member);
			//else
				changed |= member_named_edit(parent, object, member);
		
		return changed;
	}

	bool object_edit_inrow(Widget& row, Ref object)
	{
		bool changed = false;
		for(Member& member : cls(object).m_members)
			if(nested_object(member) && !DispatchInput::me().check(member.m_default_value))
				//changed |= member_toggle_edit(row, object, member);
				changed |= member_nested_edit(row, object, member);
			else
				changed |= member_edit(row, object, member);

		return changed;
	}

	bool object_edit_inline(Widget& parent, Ref object)
	{
		Widget& row = ui::widget(parent, styles().wrap_button);
		return object_edit_inrow(row, object);
	}

	Widget& object_edit_inline_item(Widget& parent, Ref object)
	{
		Widget& row = ui::table_row(parent);
		object_edit_inrow(row, object);
		return row;
	}

	bool object_edit_columns(Widget& parent, Ref object)
	{
		static float columns[2] = { 0.4f, 0.6f };
		Widget& self = ui::columns(parent, { columns, 2 });
		return object_edit_rows(self, object);
	}

	bool object_edit_table(Widget& parent, Ref object)
	{
		static cstring columns[2] = { "field", "value" };
		static float spans[2] = { 0.4f, 0.6f };
		Widget& self = ui::table(parent, { columns, 2 }, { spans, 2 });
		bool changed = object_edit_rows(self, object);

#ifdef MUD_PROTO
		if(meta(object).m_type_class == TypeClass::Complex)
		{
			Complex& modular = val<Complex>(object);

			for(Type* type : modular.m_prototype.m_parts)
			{
				Widget* part_node = ui::tree_node(parent, type->m_name, false, true).m_body;
				if(part_node)
					changed |= object_edit_rows(*part_node, modular.part(*type));
			}
		}
#endif

		return changed;
	}

	bool object_edit_expandbox(Widget& parent, Ref object)
	{
		Widget* body = ui::expandbox(parent, object.m_type->m_name, true).m_body;
		if(body)
			return object_edit_columns(*body, object);
		return false;
	}

	bool object_edit(Widget& parent, Ref object, EditorHint hint)
	{
		if(hint == EditorHint::Table)
			return object_edit_table(parent, object);
		else if(hint == EditorHint::Rows)
			return object_edit_rows(parent, object);
		else //if(hint == EditorHint::Inline)
			return object_edit_inline(parent, object);
	}

	bool inspector(Widget& parent, Ref object)
	{
		Section& self = section(parent, "Inspector", {}, true);
		return object_edit_table(*self.m_body, object);
	}

	bool inspector(Widget& parent)
	{
		Section& self = section(parent, "Inspector", {}, true);
		EditState& state = self.state<EditState>();
		if(state.object)
			return object_edit(*self.m_body, state.object);
		return false;
	}

	void multi_object_edit(Widget& parent, Type& type, std::vector<Ref> objects)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		Widget& table = ui::table(*scroll_sheet.m_body, to_array(cls(type).m_field_names), {});

		for(Ref object : objects)
			object_edit_inline(table, object);
	}

	enum LibraryModes
	{
		LIBRARY_CREATE = 1 << 0,
		LIBRARY_TYPE_INFO = 1 << 1,
	};

	void multi_inspector(Widget& parent, Type& type, std::vector<Var>& objects, size_t& selected)
	{
		Section& self = section(parent, (string(meta(type).m_name) + " Library").c_str());

		if(ui::modal_button(self, *self.m_toolbar, "Type Info", LIBRARY_TYPE_INFO))
		{
			Widget& modal = ui::auto_modal(self, LIBRARY_TYPE_INFO, { 600, 400 });
			meta_edit(*modal.m_body, type);
		}

		if(ui::button(*self.m_toolbar, "Add").activated())
			objects.push_back(meta(type).m_empty_var());

		if(ui::modal_button(self, *self.m_toolbar, "Create", LIBRARY_CREATE))
		{
			Widget& modal = ui::auto_modal(self, LIBRARY_CREATE);
			bool done = object_creator(modal, type);
			UNUSED(done);
		}

		Widget& board = ui::board(*self.m_body);

		ScrollSheet& scroll_sheet = ui::scroll_sheet(board);
		Widget& table = ui::table(*scroll_sheet.m_body, to_array(cls(type).m_field_names), {});

		for(size_t i = 0; i < objects.size(); ++i)
		{
			Widget& row = object_edit_inline_item(table, objects[i]);
			row.setState(SELECTED, selected == i);
			if(row.activated())
				selected = i;
		}
	}
}

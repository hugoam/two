//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.uio;
#else
#include <tree/Graph.hpp>
#include <stl/algorithm.h>
#include <type/Any.h>
#include <ecs/ECS.hpp>
#include <refl/Class.h>
#include <uio/Inspector.h>
#include <ui/ContainerStruct.h>
#include <uio/ValueEdit.h>
#include <ui/Section.h>
#include <uio/InjectorEdit.h>
#include <uio/ReflEdit.h>
#endif

//#define EDIT_MEMBER_REF

namespace two
{
	vector<EditSpec> g_edit_specs = vector<EditSpec>(c_max_types);

	EditSpec::EditSpec(Class& cls)
		: m_setup(true)
	{
		bool big_struct = is_struct(*cls.m_type) && cls.m_members.size() > 4;
		if(big_struct || is_object(*cls.m_type))
			m_nest_mode[0] = EditNestMode::Embed;
		else
			m_nest_mode[0] = EditNestMode::Inline;

		//bool custom_edit = DispatchInput::me.check(*cls.m_type);
		//m_row_mode = big_struct || is_object(*cls.m_type) ? EditNestMode::Embed : EditNestMode::Inline;
	}

	struct EditState : public NodeState
	{
		Ref object = {};
	};

	bool member_edit(Widget& parent, Ref object, Member& member, EditorHint hint = EditorHint::Inline)
	{
#ifdef EDIT_MEMBER_REF
		Ref value = member.cast_get(object);
		bool changed = any_edit(parent, value, member.is_link() | member.is_pointer(), hint);
#else
		//Var value = member.safe_get(object);
		Var value = member.get(object);
		bool changed = any_edit(parent, value.m_ref, member.is_link() | member.is_pointer(), hint);

		if(changed && member.is_mutable() && !member.is_component())
			member.cast_set(object, value);
#endif
		
		return changed;
	}

	bool member_edit_row(Widget& parent, Ref object, Member& member)
	{
		Widget& self = ui::table_row(parent);
		ui::label(self, member.m_name);
		return member_edit(self, object, member);
	}

	bool member_edit_toggle(Widget& parent, Ref object, Member& member)
	{
		Widget& self = ui::row(parent);
		if(ui::modal_button(self, self, "Edit", 1))
		{
			Widget& modal = ui::modal(self.parent_modal());
			return member_edit(modal, object, member, EditorHint::Table);
		}
		return false;
	}

	bool member_edit_embed(Widget& parent, Ref object, Member& member)
	{
		return member_edit(parent, object, member, EditorHint::Rows);
	}

	bool member_edit_nested(Widget& parent, Ref object, Member& member)
	{
		//Widget& row = ui::table_row(parent);
		Widget& row = ui::table_separator(parent);
		Widget* body = ui::tree_node(row, member.m_name, false, true).m_body;
		if(body)
			return member_edit(*body, object, member, EditorHint::Rows);
		return false;
	}

	EditNestMode nest_edit_mode(Member& member, size_t mode)
	{
		if(member.is_component()) return EditNestMode::Embed;
		if(member.is_link() || is_basic(*member.m_type)) return EditNestMode::Inline;

		if(!g_edit_specs[member.m_type->m_id].m_setup)
			g_edit_specs[member.m_type->m_id] = { cls(*member.m_type) };

		return g_edit_specs[member.m_type->m_id].m_nest_mode[mode];
	}

	bool object_edit_rows(Widget& parent, Table& table, Ref object)
	{
		UNUSED(parent);
		bool changed = false;

		auto member_edit = [&](Member& member)
		{
			EditNestMode mode = nest_edit_mode(member, 0);
			if(mode == EditNestMode::Embed)
				changed |= member_edit_nested(table, object, member);
			else if(mode == EditNestMode::Modal)
				changed |= member_edit_toggle(table, object, member);
			else
				changed |= member_edit_row(table, object, member);
		};

		for(Member& member : cls(object).m_members)
			if(!member.is_component() && member.is_mutable())
				member_edit(member);

		for(Member& member : cls(object).m_members)
			if(member.is_component() && member.is_mutable())
				member_edit(member);

		return changed;
	}

	bool object_edit_rows(Widget& parent, Ref object)
	{
		return object_edit_rows(parent, as<Table>(parent), object);
	}

	bool object_edit_inrow(Widget& row, Ref object)
	{
		bool changed = false;

		auto member_edit = [&](Member& member)
		{
			EditNestMode mode = nest_edit_mode(member, 1);
			if(mode == EditNestMode::Embed)
				changed |= member_edit_embed(row, object, member);
			else if(mode == EditNestMode::Modal)
				changed |= member_edit_toggle(row, object, member);
			else
				changed |= two::member_edit(row, object, member);
		};

		for(Member& member : cls(object).m_members)
			if(!member.is_component() && member.is_mutable())
				member_edit(member);

		for(Member& member : cls(object).m_members)
			if(member.is_component() && member.is_mutable())
				member_edit(member);

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
		static float columns[2] = { 0.33f, 0.67f };
		Table& self = ui::columns(parent, { columns, 2 });
		return object_edit_rows(parent, self, object);
	}

	bool object_edit_table(Widget& parent, Ref object)
	{
		static cstring columns[2] = { "field", "value" };
		static float spans[2] = { 0.4f, 0.6f };
		Table& self = ui::table(parent, { columns, 2 }, { spans, 2 });
		return object_edit_rows(parent, self, object);
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
			return object_edit_columns(parent, object);
		else if(hint == EditorHint::Rows)
			return object_edit_columns(parent, object);
		else if(hint == EditorHint::Inline || true)
			return object_edit_inline(parent, object);
	}

	bool entity_edit(Widget& parent, Entity entity, EditorHint hint)
	{
		UNUSED(hint);
		bool changed = false;

		static cstring columns[2] = { "field", "value" };
		static float spans[2] = { 0.4f, 0.6f };
		Table& self = ui::table(parent, { columns, 2 }, { spans, 2 });

		EntityStream& stream = s_ecs[entity.m_ecs]->stream(entity.m_stream);
		uint32_t index = stream.m_handles[entity.m_handle];
		for(auto& buffer : stream.m_buffers)
		{
			Widget& row = ui::table_separator(self);
			Widget* body = ui::tree_node(row, buffer->m_type->m_name, false, true).m_body;
			if(body)
				changed |= object_edit_columns(*body, buffer->get(index));
		}

		return changed;
	}

	bool inspector(Widget& parent, Entity entity)
	{
		Section& self = section(parent, "Entity Inspector", true);
		return entity_edit(*self.m_body, entity);
	}

	bool inspector(Widget& parent, Ref object)
	{
		Section& self = section(parent, "Inspector", true);
		if(object.m_type->is<EntityRef>())
			return inspector(parent, { UINT8_MAX, UINT16_MAX, as_ent(object) });
		else
			return object_edit_columns(*self.m_body, object);
	}

	bool inspector(Widget& parent)
	{
		Section& self = section(parent, "Inspector", true);
		EditState& state = self.state<EditState>();
		if(state.object)
			return object_edit_columns(*self.m_body, state.object);
		return false;
	}

	void multi_object_edit(Widget& parent, Type& type, vector<Ref> objects)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		Widget& table = ui::table(*scroll_sheet.m_body, cls(type).m_field_names, {});

		for(Ref object : objects)
			object_edit_inline(table, object);
	}

	void multi_inspector(Widget& parent, Type& type, vector<Var>& objects, size_t& selected)
	{
		enum Modes { CREATE = 1 << 0, TYPE_INFO = 1 << 1 };

		Section& self = section(parent, (string(type.m_name) + " Library").c_str());

		if(ui::modal_button(self, *self.m_toolbar, "Type Info", TYPE_INFO))
		{
			Widget& modal = ui::auto_modal(self, TYPE_INFO, { 600, 400 });
			meta_edit(*modal.m_body, type);
		}

		if(ui::button(*self.m_toolbar, "Add").activated())
			objects.push_back(meta(type).m_empty_var);

		if(ui::modal_button(self, *self.m_toolbar, "Create", CREATE))
		{
			Widget& modal = ui::auto_modal(self, CREATE);
			bool done = object_creator(modal, type);
			UNUSED(done);
		}

		Widget& board = ui::board(*self.m_body);

		ScrollSheet& scroll_sheet = ui::scroll_sheet(board);
		Widget& table = ui::table(*scroll_sheet.m_body, cls(type).m_field_names, {});

		for(size_t i = 0; i < objects.size(); ++i)
		{
			Widget& row = object_edit_inline_item(table, objects[i]);
			row.set_state(SELECTED, selected == i);
			if(row.activated())
				selected = i;
		}
	}
}

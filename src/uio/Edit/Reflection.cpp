//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <uio/Unode.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>

#include <obj/Vector.h>
#include <obj/Reflect/Class.h>
#include <obj/System/System.h>
#include <obj/Reflect/Convert.h>
#include <obj/Generated/Convert.h>
#include <obj/Complex.h>

#include <uio/Edit/Section.h>
#include <uio/Edit/Method.h>

#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Input.h>

namespace mud
{
	struct MetaStyles
	{
		Style element = { "Element", styles().row, { [](Layout& l) { l.m_spacing = vec2{ 5.f, 0.f }; } }, {} };

#if 0
		Style frame = { "Frame", styles().sheet, { { { &InkStyle::m_empty = false }, { &InkStyle::m_background_colour, to_colour(25, 26, 31) } } } };

		Style type = { "Type", styles().label, { { { &InkStyle::m_empty = false }, { &InkStyle::m_text_font, "veramono-bold" }, { &InkStyle::m_text_colour, to_colour(255, 0, 78) }, { &InkStyle::m_text_size, 18.f } } } };
		Style identifier = { "Identifier", styles().label, { { { &InkStyle::m_empty = false }, { &InkStyle::m_text_font, "veramono-bold" }, { &InkStyle::m_text_colour, to_colour(106, 176, 255) }, { &InkStyle::m_text_size, 18.f } } } };
		Style syntax = { "Syntax", styles().label, { { { &InkStyle::m_empty = false }, { &InkStyle::m_text_font, "veramono-bold" }, { &InkStyle::m_text_colour, Colour::White }, { &InkStyle::m_text_size, 18.f } } } };
		Style argument = { "Argument", styles().label, { { { &InkStyle::m_empty = false }, { &InkStyle::m_text_font, "veramono-bold" }, { &InkStyle::m_text_colour, to_colour(227, 131, 228) }, { &InkStyle::m_text_size, 18.f } } } };
#else
		Style frame = { "Frame", styles().sheet, {}, {} };

		Style type = { "Type", styles().label, {}, { [](InkStyle& l) { l.m_empty = false; l.m_text_colour = to_colour(125, 125, 125); l.m_text_size = 16.f; } } };
		Style identifier = { "Identifier", styles().label, {}, { [](InkStyle& l) { l.m_empty = false; l.m_text_colour = to_colour(106, 176, 255); l.m_text_size = 16.f; } } };
		Style syntax = { "Syntax", styles().label, {}, { [](InkStyle& l) { l.m_empty = false; l.m_text_colour = Colour::White; l.m_text_size = 16.f; } } };
		Style argument = { "Argument", styles().label, {}, { [](InkStyle& l) { l.m_empty = false; l.m_text_colour = Colour::White; l.m_text_size = 16.f; } } };
#endif
	};

	MetaStyles& meta_info_styles() { static MetaStyles styles; return styles; }

namespace ui
{
	template <class T>
	inline bool enum_input(Widget& parent, T& value)
	{
		size_t index = enum_index(&value);
		//ui::radio_switch(parent, meta(value).m_enum_names, index);
		if(ui::dropdown_input(parent, to_array(type<T>().m_enum->m_names), index))
		{
			enum_set_index(&value, index);
			return true;
		}
		return false;
	}

	template <class T>
	inline bool enum_field(Widget& parent, cstring name, T& value, bool reverse = false) { return field([&](Widget& self) { return enum_input<T>(self, value); }, parent, name, reverse); }

	void field_label(Widget& parent, cstring field, cstring value)
	{
		Widget& self = row(parent);
		label(self, field);
		label(self, value);
	}
}

	void meta_description(Widget& parent, Type& type)
	{
		static float columns[2] = { 0.2f, 0.8f };
		Table& self = ui::columns(parent, { columns, 2 });
		ui::field_label(self, "name", type.m_meta->m_name);
		ui::field_label(self, "namespace", type.m_meta->m_namespace->m_name ? type.m_meta->m_namespace->m_name : "");
		ui::enum_field<TypeClass>(self, "type class", type.m_meta->m_type_class);
		ui::input_field<size_t>(self, "size", type.m_meta->m_size);
	}

	void meta_callable(Widget& parent, Callable& callable, bool skip_first = false, bool returns = true)
	{
		Widget& row = ui::widget(parent, meta_info_styles().element);
		//ui::item(row, meta_info_styles().syntax, "Function");
		if(returns)
			ui::item(row, meta_info_styles().type, callable.m_returnval.type().m_name);
		ui::item(row, meta_info_styles().identifier, callable.m_name);
		ui::item(row, meta_info_styles().syntax, "(");
		for(Param& param : callable.m_params)
		{
			if(skip_first && param.m_index == 0)
				continue;
			ui::item(row, meta_info_styles().type, param.m_value == Ref() ? "Ref" : param.m_value.type().m_name);
			ui::item(row, meta_info_styles().argument, param.m_name);
			if(&param != &callable.m_params.back())
				ui::item(row, meta_info_styles().syntax, ",");
		}
		ui::item(row, meta_info_styles().syntax, ")");
	}

	void meta_function(Widget& parent, Function& function)
	{
		return meta_callable(parent, function);
	}

	void meta_method(Widget& parent, Method& method)
	{
		return meta_callable(parent, method, true);
	}

	void meta_constructors(Widget& parent, Type& type)
	{
		Widget& self = ui::sheet(parent);

		for(Constructor& constructor : type.m_class->m_constructors)
			meta_callable(self, constructor, true, false);
	}

	void meta_methods(Widget& parent, Type& type)
	{
		Widget& self = ui::sheet(parent);

		for(Method& method : type.m_class->m_methods)
			meta_method(self, method);
	}

	void meta_fields(Widget& parent, Type& type)
	{
		Widget& self = ui::columns(parent, carray<float, 2>{ 0.3f, 0.7f });

		for(Member& member : type.m_class->m_members)
		{
			Widget& row = ui::widget(self, meta_info_styles().element);
			ui::item(row, meta_info_styles().type, member.m_type->m_name);
			ui::item(row, meta_info_styles().syntax, member.m_name);
		}
	}

	void meta_synopsis(Widget& parent, Function& function)
	{
		return meta_function(parent, function);
	}

	void meta_synopsis(Widget& parent, Method& method)
	{
		return meta_method(parent, method);
	}

	void meta_synopsis(Widget& parent, Type& type)
	{
		Widget& row = ui::widget(parent, meta_info_styles().element);
		ui::item(row, meta_info_styles().syntax, "Type");
		ui::item(row, meta_info_styles().type, type.m_name);
		//meta_description(parent, type);
		if(!type.m_class->m_methods.empty())
			meta_methods(parent, type);
		if(!type.m_class->m_members.empty())
			meta_fields(parent, type);
		//return meta_function(parent, function);
	}

	bool type_browser(Widget& parent, Type*& selected)
	{
		Widget& list = *ui::scroll_sheet(parent).m_body;

		for(Module* module : system().m_modules)
			for(Type* type : module->m_types)
			{
				cstring elements[1] = { type->m_name };
				if(ui::multi_button(list, { elements, 1 }).activated())
				{		
					selected = type;
					return true;
				}
			}
		return false;
	}

	enum MetaEditModes
	{
		META_BROWSE = 1 << 0,
	};

	struct MetaEditState : public NodeState
	{
		MetaEditState() {}
		MetaEditState(Type& type) : m_type(&type) {}
		Type* m_type = nullptr;
	};

	void meta_edit(Widget& parent, Type& type)
	{
		Section& self = section(parent, ("Type Info : " + string(type.m_meta->m_name)).c_str());
		MetaEditState& state = self.state<MetaEditState>(type);

		if(ui::modal_button(self, *self.m_toolbar, "Browse", META_BROWSE))
		{
			Widget& modal = ui::modal(parent.parent_modal(), { 400, 800 });
			bool done = type_browser(*modal.m_body, state.m_type);
			if(done || !modal.m_open)
				self.m_switch &= ~META_BROWSE;
		}

		if(Widget* container = ui::expandbox(*self.m_body, "Description").m_body)
			meta_description(*container, *state.m_type);

		if(Widget* container = ui::expandbox(*self.m_body, "Constructors").m_body)
			meta_constructors(*container, *state.m_type);

		if(Widget* container = ui::expandbox(*self.m_body, "Methods").m_body)
			meta_methods(*container, *state.m_type);

		if(Widget* container = ui::expandbox(*self.m_body, "Fields").m_body)
			meta_fields(*container, *state.m_type);
	}

	void meta_browser(Widget& parent, Module& module)
	{
		UNUSED(parent); UNUSED(module);
	}

	void meta_browser(Widget& parent)
	{
		static Type* selected_type = nullptr;
		static Function* selected_function = nullptr;

		//Widget& self = ui::dockspace(parent);
		Widget& self = ui::board(parent);

		Widget& meta_list = *ui::scroll_sheet(self).m_body;

		for(Module* module : System::instance().m_modules)
		{
			for(Type* type : module->m_types)
			{
				if(ui::button(meta_list, type->m_name).activated())
					selected_type = type;
			}

			for(Function& function : module->m_functions)
			{
				if(ui::button(meta_list, function.m_name).activated())
					selected_function = &function;
			}
		}

		if(selected_type)
			meta_edit(self, *selected_type);
		if(selected_function)
			meta_function(self, *selected_function);
	}

	void type_browser(Widget& parent)
	{
		static Type* selected = nullptr;

		Widget& self = ui::board(parent);
		Widget& list = *ui::scroll_sheet(self).m_body;

		for(Module* module : system().m_modules)
			for(Type* type : module->m_types)
			{
				if(ui::button(list, type->m_name).activated())
					selected = type;
			}

		if(selected)
			meta_edit(self, *selected);
	}
}

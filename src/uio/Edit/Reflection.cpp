//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <infra/Vector.h>
//#include <obj/Complex.h>
#include <refl/Class.h>
#include <refl/System.h>
#include <refl/Convert.h>
#include <refl/Module.h>
#include <meta/obj/Convert.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Input.h>
#include <uio/Types.h>
#include <uio/Edit/Reflection.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Method.h>
#endif

namespace mud
{
	struct MetaStyles
	{
		Style element = { "Element", styles().row, [](Layout& l) { l.m_spacing = vec2{ 5.f, 0.f }; } };

#if 1
		Style frame = { "Frame", styles().sheet, {}, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = to_colour(25, 26, 31); } };

		Style type = { "Type", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_font = "veramono-bold"; l.m_text_colour = to_colour(255, 0, 78); l.m_text_size = 18.f; } };
		Style identifier = { "Identifier", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_font = "veramono-bold"; l.m_text_colour = to_colour(106, 176, 255); l.m_text_size = 18.f; } };
		Style syntax = { "Syntax", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_font = "veramono-bold"; l.m_text_colour = Colour::White; l.m_text_size = 18.f; } };
		Style argument = { "Argument", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_font = "veramono-bold"; l.m_text_colour = to_colour(227, 131, 228); l.m_text_size = 18.f; } };
#else
		Style frame = { "Frame", styles().sheet, {}, {} };

		Style type = { "Type", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_colour = to_colour(125, 125, 125); l.m_text_size = 16.f; } };
		Style identifier = { "Identifier", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_colour = to_colour(106, 176, 255); l.m_text_size = 16.f; } };
		Style syntax = { "Syntax", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_colour = Colour::White; l.m_text_size = 16.f; } };
		Style argument = { "Argument", styles().label, {}, [](InkStyle& l) { l.m_empty = false; l.m_text_colour = Colour::White; l.m_text_size = 16.f; } };
#endif
	};

	MetaStyles& meta_info_styles() { static MetaStyles styles; return styles; }

	void meta_description(Widget& parent, Meta& meta)
	{
		static float columns[2] = { 0.2f, 0.8f };
		Table& self = ui::columns(parent, { columns, 2 });
		ui::field_label(self, "name", meta.m_name);
		ui::field_label(self, "namespace", meta.m_namespace->m_name ? meta.m_namespace->m_name : "");
		ui::enum_field<TypeClass>(self, "type class", meta.m_type_class);
		ui::input_field<size_t>(self, "size", meta.m_size);
	}

	void meta_description(Widget& parent, Type& type)
	{
		return meta_description(parent, meta(type));
	}

	void meta_callable(Widget& parent, Callable& callable, bool skip_first = false, bool returns = true)
	{
		Widget& row = ui::widget(parent, meta_info_styles().element);
		//ui::item(row, meta_info_styles().syntax, "Function");
		if(returns)
			ui::item(row, meta_info_styles().type, type(callable.m_returnval).m_name);
		ui::item(row, meta_info_styles().identifier, callable.m_name);
		ui::item(row, meta_info_styles().syntax, "(");
		for(Param& param : callable.m_params)
		{
			if(skip_first && param.m_index == 0)
				continue;
			ui::item(row, meta_info_styles().type, param.m_value == Ref() ? "Ref" : type(param.m_value).m_name);
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

		for(Constructor& constructor : cls(type).m_constructors)
			meta_callable(self, constructor, true, false);
	}

	void meta_methods(Widget& parent, Type& type)
	{
		Widget& self = ui::sheet(parent);

		for(Method& method : cls(type).m_methods)
			meta_method(self, method);
	}

	void meta_fields(Widget& parent, Type& type)
	{
		Widget& self = ui::columns(parent, carray<float, 2>{ 0.3f, 0.7f });

		for(Member& member : cls(type).m_members)
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
		if(!cls(type).m_methods.empty())
			meta_methods(parent, type);
		if(!cls(type).m_members.empty())
			meta_fields(parent, type);
		//return meta_function(parent, function);
	}

	bool type_browser(Widget& parent, Type*& selected)
	{
		Widget& list = *ui::scroll_sheet(parent).m_body;

		for(Module* m : system().m_modules)
			for(Type* type : m->m_types)
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

	struct MetaEditState : public NodeState
	{
		MetaEditState() {}
		MetaEditState(Type& type) : m_type(&type) {}
		Type* m_type = nullptr;
	};

	void meta_edit(Widget& parent, Type& type)
	{
		enum Modes { BROWSE = 1 << 0 };

		Section& self = section(parent, ("Type Info : " + string(meta(type).m_name)).c_str());
		MetaEditState& state = self.state<MetaEditState>(type);

		if(ui::modal_button(self, *self.m_toolbar, "Browse", BROWSE))
		{
			Widget& modal = ui::modal(parent.parent_modal(), { 400, 800 });
			bool done = type_browser(*modal.m_body, state.m_type);
			if(done || !modal.m_open)
				self.m_switch &= ~BROWSE;
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

	void meta_browser(Widget& parent, Module& m)
	{
		UNUSED(parent); UNUSED(m);
	}

	void meta_browser(Widget& parent)
	{
		static Type* selected_type = nullptr;
		static Function* selected_function = nullptr;

		//Widget& self = ui::dockspace(parent);
		Widget& self = ui::board(parent);

		Widget& meta_list = *ui::scroll_sheet(self).m_body;

		for(Module* m : System::instance().m_modules)
		{
			for(Type* type : m->m_types)
			{
				if(ui::button(meta_list, type->m_name).activated())
					selected_type = type;
			}

			for(Function* function : m->m_functions)
			{
				if(ui::button(meta_list, function->m_name).activated())
					selected_function = function;
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

		for(Module* m : system().m_modules)
			for(Type* type : m->m_types)
			{
				if(ui::button(list, type->m_name).activated())
					selected = type;
			}

		if(selected)
			meta_edit(self, *selected);
	}
}

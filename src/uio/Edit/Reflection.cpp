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
#include <meta/refl/Convert.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Input.h>
#include <ui/Sequence.h>
#include <uio/Types.h>
#include <uio/Edit/Reflection.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Method.h>
#endif

namespace mud
{
	static void text_skin(InkStyle& style, const Colour& colour)
	{
		static float text_size = 15.f;
		style.m_empty = false;
		style.m_text_font = "veramono-bold";
		style.m_text_colour = colour;
		style.m_text_size = text_size;
	}

	struct MetaStyles
	{
		Style element = { "Element", styles().row, [](Layout& l) { l.m_spacing = vec2{ 5.f, 0.f }; } };

		Style sheet = { "Frame", styles().stack, [](Layout& l) { l.m_padding = vec4(20.f); l.m_spacing = vec2(10.f); } };
		Style frame = { "Frame", styles().stack, [](Layout& l) { l.m_padding = vec4(5.f); l.m_spacing = vec2(10.f); }, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = to_colour(25, 26, 31); } };
		
		Style label			= { "Syntax", styles().label,{}, [](InkStyle& l) { text_skin(l, Colour::White); } };
		Style type			= { "Type", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(255, 0, 78)); } }; // to_colour(125, 125, 125)
		Style function		= { "Function", styles().label,{}, [](InkStyle& l) { text_skin(l, to_colour(255, 0, 78)); } }; // to_colour(106, 176, 255)
		Style identifier	= { "Word", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(106, 176, 255)); } };
		Style syntax		= { "Syntax", styles().label, {}, [](InkStyle& l) { text_skin(l, Colour::White); } }; // Colour::White
		Style argument		= { "Argument", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(227, 131, 228)); } }; // Colour::White
		Style field			= { "Field", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(227, 131, 228)); } }; // Colour::White
		Style number		= { "Number", styles().label, {}, [](InkStyle& l) { text_skin(l, to_colour(227, 131, 228)); } }; // Colour::White
	};

	MetaStyles& meta_styles() { static MetaStyles styles; return styles; }

	void set_meta_palette(const std::vector<uint32_t>& palette)
	{
		meta_styles().label.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Word)]);
		meta_styles().type.skin().m_text_colour			= from_rgba(palette[size_t(CodePalette::Identifier)]);
		meta_styles().function.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Function)]);
		meta_styles().identifier.skin().m_text_colour	= from_rgba(palette[size_t(CodePalette::Identifier)]);
		meta_styles().syntax.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Punctuation)]);
		meta_styles().argument.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Parameter)]);
		meta_styles().field.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Field)]);
		meta_styles().number.skin().m_text_colour		= from_rgba(palette[size_t(CodePalette::Number)]);
	}

	void meta_type(Widget& parent, Meta& meta)
	{
		Widget& row = ui::widget(parent, meta_styles().element);
		ui::item(row, meta_styles().syntax, to_string(meta.m_type_class).c_str());
		if(!meta.m_namespace->is_root())
		{
			ui::item(row, meta_styles().type, meta.m_namespace->m_name);
			ui::item(row, meta_styles().syntax, "::");
		}
		ui::item(row, meta_styles().type, meta.m_name);

		Widget& size = ui::widget(parent, meta_styles().element);
		ui::item(size, meta_styles().type, "size");
		ui::item(size, meta_styles().number, to_string(meta.m_size).c_str());
	}

	void meta_description(Widget& parent, Meta& meta)
	{
		static float columns[2] = { 0.2f, 0.8f };
		Table& self = ui::columns(parent, { columns, 2 });
		ui::field_label(self, "name", meta.m_name);
		ui::field_label(self, "namespace", meta.m_namespace->m_name);
		ui::enum_field<TypeClass>(self, "type class", meta.m_type_class);
		ui::input_field<size_t>(self, "size", meta.m_size);
	}

	void meta_description(Widget& parent, Type& type)
	{
		return meta_description(parent, meta(type));
	}

	void meta_callable(Widget& parent, Callable& callable, bool skip_first = false, bool returns = true)
	{
		Widget& sheet = ui::widget(parent, styles().sheet, &callable);

		Widget& row = ui::widget(sheet, meta_styles().element);
		//ui::item(row, meta_styles().syntax, "Function");
		if(returns)
		{
			auto return_type = [](const Var& val) { if(val.none()) return "void"; else if(val == Ref()) return "Ref"; else return type(val).m_name; };
			ui::item(row, meta_styles().type, return_type(callable.m_returnval));
		}
		ui::item(row, meta_styles().function, callable.m_name);
		ui::item(row, meta_styles().syntax, "(");
		for(Param& param : callable.m_params)
		{
			if(skip_first && param.m_index == 0)
				continue;
			ui::item(row, meta_styles().type, param.m_value == Ref() ? "Ref" : type(param.m_value).m_name);
			ui::item(row, meta_styles().argument, param.m_name);
			if(&param != &callable.m_params.back())
				ui::item(row, meta_styles().syntax, ",");
		}
		ui::item(row, meta_styles().syntax, ")");
	}

	void meta_function(Widget& parent, Function& function)
	{
		return meta_callable(parent, function);
	}

	void meta_method(Widget& parent, Method& method)
	{
		return meta_callable(parent, method, true);
	}

	void meta_constructors(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);

		for(Constructor& constructor : cls.m_constructors)
			meta_callable(self, constructor, true, false);
	}

	void meta_methods(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);

		for(Method& method : cls.m_methods)
			meta_method(self, method);
	}

	void meta_fields(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);
		Widget& table = self;
		//Widget& table = ui::columns(self, carray<float, 2>{ 0.3f, 0.7f });

		for(Member& member : cls.m_members)
		{
			Widget& row = ui::widget(table, meta_styles().element);
			ui::item(row, meta_styles().type, member.m_type->m_name);
			ui::item(row, meta_styles().field, member.m_name);
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

	void meta_enum(Widget& parent, Enum& enu)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);
		
		for(size_t i = 0; i < enu.m_names.size(); ++i)
		{
			Widget& row = ui::widget(self, meta_styles().element);
			ui::item(row, meta_styles().identifier, enu.m_names[i]);
			ui::item(row, meta_styles().syntax, "=");
			ui::item(row, meta_styles().number, to_string(enu.m_indices[i]).c_str());
		}
	}

	void meta_class(Widget& parent, Class& cls)
	{
		//meta_description(parent, type);
		if (!cls.m_constructors.empty())
		{
			ui::item(parent, meta_styles().label, "constructors:");
			meta_constructors(parent, cls);
		}
		if (!cls.m_methods.empty())
		{
			ui::item(parent, meta_styles().label, "methods:");
			meta_methods(parent, cls);
		}
		if (!cls.m_members.empty())
		{
			ui::item(parent, meta_styles().label, "fields:");
			meta_fields(parent, cls);
		}
	}

	void meta_synopsis(Widget& parent, Type& type)
	{
		Widget& self = ui::widget(parent, meta_styles().frame, &type);

		Widget& row = ui::widget(self, meta_styles().element);
		ui::item(row, meta_styles().syntax, to_string(meta(type).m_type_class).c_str());
		ui::item(row, meta_styles().type, type.m_name);
		if(g_enu[type.m_id])
			meta_enum(self, enu(type));
		if (g_class[type.m_id])
			meta_class(self, cls(type));
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

	void class_edit(Widget& parent, Class& cls)
	{
		Widget& self = ui::widget(parent, meta_styles().frame);

		meta_type(self, meta(*cls.m_type));
		meta_class(self, cls);
	}

	void meta_edit(Widget& parent, Type& type)
	{
		enum Modes { Browse = 1 << 0 };

		Section& self = section(parent, ("Type Info : " + string(meta(type).m_name)).c_str());
		MetaEditState& state = self.state<MetaEditState>(type);

		if (ui::modal_button(self, *self.m_toolbar, "Browse", Browse))
		{
			Widget& modal = ui::modal(parent.parent_modal(), { 400, 800 });
			bool done = type_browser(*modal.m_body, state.m_type);
			if (done || !modal.m_open)
				self.m_switch &= ~Browse;
		}

		class_edit(*self.m_body, cls(*state.m_type));
	}

	void meta_browser(Widget& parent, Module& m)
	{
		UNUSED(parent); UNUSED(m);
	}

	void meta_browser(Widget& parent)
	{
		enum Mode : size_t { Basetypes = 0, Enums, Classes, Functions };

		static Ref selected = {};

		//Widget& self = ui::dockspace(parent);
		Widget& self = ui::board(parent);

		Widget& left = ui::layout_span(self, 0.3f);
		Widget& right = ui::layout_span(self, 0.7f);

		Widget& table = ui::columns(left, carray<float, 2>{ 0.3f, 0.7f });

		static Mode mode = Classes;
		ui::dropdown_field(table, "Browse:", carray<cstring, 4>{ "Basetypes", "Enums", "Classes", "Functions" }, (size_t&) mode);

		static std::map<Module*, bool> modules;

		Widget& row = ui::row(table);
		ui::label(row, "Modules");
		Widget& drop = ui::dropdown(row, ui::dropdown_styles().dropdown_input, "...", ui::PopupFlags::AutoModal);
		if(drop.m_body)
		{
			for(Module* m : System::instance().m_modules)
			{
				Widget& row = ui::row(*drop.m_body);
				ui::checkbox(row, modules[m]);
				ui::label(row, m->m_name);
			}
		}

		Widget& sheet = ui::widget(left, styles().sheet, (void*) mode);
		Widget& meta_list = *ui::scroll_sheet(sheet).m_body;

		auto choice = [](Widget& parent, Ref object, cstring name, Ref& selected) -> Widget& { Widget& element = ui::element(parent, object); ui::select_logic(element, object, selected); return ui::multi_item(element, carray<cstring, 1>{ name }); };

		for(Module* m : System::instance().m_modules)
			if(modules[m])
			{
				if(mode < Functions)
				{
					for(Type* type : m->m_types)
					{
						if((is_base_type(*type) && mode == Basetypes) || (is_enum(*type) && mode == Enums) || (is_class(*type) && mode == Classes))
							choice(meta_list, Ref(type), type->m_name, selected);
					}
				}
				else
				{
					for(Function* function : m->m_functions)
						choice(meta_list, Ref(function), function->m_name, selected);
				}
			}

		Widget& info = ui::widget(right, meta_styles().sheet, (void*)mode);
		if(Type* type = try_val<Type>(selected))
		{
			//if(is_basetype(*type))
			//	type_edit(right, *type);
			if(is_enum(*type))
				meta_enum(info, enu(*type));
			if(is_class(*type))
				class_edit(info, cls(*type));
		}
		if(Function* function = try_val<Function>(selected))
			meta_function(info, *function);
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

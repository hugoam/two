#pragma once

#include <two/infra.h>
#include <two/type.h>





#ifndef TWO_UIO_EXPORT
#define TWO_UIO_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class EditNestMode : unsigned int;
    export_ enum class EditorHint : unsigned int;

    export_ class DispatchItem;
    export_ class DispatchSelector;
    export_ struct EditSpec;
    export_ class ScriptEditor;
    export_ class DispatchInput;
}

#ifdef TWO_META_GENERATOR
namespace stl
{
	extern template class refl_ seque_ vector<two::Var>;
}
#endif

namespace two
{
	export_ TWO_UIO_EXPORT bool call_edit(Widget& parent, Call& call);

	export_ TWO_UIO_EXPORT void callable_edit(Widget& parent, Callable& callable);
	export_ TWO_UIO_EXPORT void function_edit(Widget& parent, Function& function);
	export_ TWO_UIO_EXPORT void method_edit(Widget& parent, Ref object, Method& method);
	export_ TWO_UIO_EXPORT void method_hook(Widget& parent, Ref object, Method& method);
}



namespace two
{
	export_ TWO_UIO_EXPORT void structure_node(Widget& parent, Ref object, vector<Ref>& selection);
	export_ TWO_UIO_EXPORT void structure_view(Widget& parent, Ref object, vector<Ref>& selection);
}



namespace two
{
	export_ TWO_UIO_EXPORT string object_name(Ref object);
	export_ TWO_UIO_EXPORT string object_icon(Ref object);

	export_ TWO_UIO_EXPORT Widget& object_button(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT Widget& object_item(Widget& parent, Ref object);
	export_ TWO_UIO_EXPORT bool object_item(Widget& parent, Ref object, Ref& selection);
	export_ TWO_UIO_EXPORT bool object_item(Widget& parent, Ref object, vector<Ref>& selection);

	export_ TWO_UIO_EXPORT Widget& entity_item(Widget& parent, Entity entity);
}


namespace two
{
	export_ class refl_ TWO_UIO_EXPORT ScriptEditor
	{
	public:
		ScriptEditor();
		~ScriptEditor();

		vector<Script*> m_scripts;

		LuaInterpreter* m_lua = nullptr;
		WrenInterpreter* m_wren = nullptr;

		void reset_interpreters(LuaInterpreter& lua, WrenInterpreter& wren);

		void open(Script& script);
		void close(Script& script);

		TextScript& create_script(const string& name, Language language, Signature signature = {});
		VisualScript& create_visual(const string& name, Signature signature = {});
	};

	export_ TWO_UIO_EXPORT void script_edit_output(Widget& parent, Interpreter& interpreter);
	export_ TWO_UIO_EXPORT Section& script_edit_code(Widget& parent, TextScript& script);
	export_ TWO_UIO_EXPORT Section& script_edit(Widget& parent, TextScript& script);
	export_ TWO_UIO_EXPORT void script_editor(Widget& parent, ScriptEditor& editor);
}



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



namespace two
{
	export_ TWO_UIO_EXPORT void ui_debug_modal(Widget& parent, Widget& target);
	export_ TWO_UIO_EXPORT void ui_debug_layout(Widget& parent, Widget& target);
	export_ TWO_UIO_EXPORT void ui_debug(Widget& parent, Widget& target);

	export_ TWO_UIO_EXPORT void ui_edit(Widget& parent, Sequence& selection);
	export_ TWO_UIO_EXPORT void ui_editor(Widget& parent);
}



namespace two
{
	export_ class TWO_UIO_EXPORT DispatchSelector : public Dispatch<bool, Widget&>, public LazyGlobal<DispatchSelector>
	{
	public:
		DispatchSelector();
	};

	export_ TWO_UIO_EXPORT void complex_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection = nullptr);
	export_ TWO_UIO_EXPORT void object_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection = nullptr);

	export_ TWO_UIO_EXPORT bool object_selector(Widget& parent, Indexer& indexer, Ref& result);
	export_ TWO_UIO_EXPORT bool object_selector(Widget& parent, Ref& result);

	export_ TWO_UIO_EXPORT void object_indexer_modal(Widget& parent, Indexer& indexer);
	export_ TWO_UIO_EXPORT bool object_selector_modal(Widget& screen, Widget& parent, Ref& result);
}



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



namespace two
{
	export_ class TWO_UIO_EXPORT DispatchItem : public Dispatch<Widget&, Widget&>, public LazyGlobal<DispatchItem>
	{
	public:
		DispatchItem();
	};
}



namespace two
{
#if 0
	export_ class TWO_UIO_EXPORT Dropper : public Widget
	{
	public:
		Dropper(Widget& parent, Type& deviceType);

		void drop(Widget& parent, , size_t position);

	protected:
		virtual Widget* swapdrop(Widget& parent, , Dropper& source) = 0;
		virtual bool candrop(Widget& parent, , Dropper& source) = 0;
		virtual void dropin(Widget& parent, , Dropper& source, size_t index) = 0;
		virtual void dropout(Widget& parent, , Dropper& source) = 0;
	};
#endif
}


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
    // Exported types
    export_ template <> TWO_UIO_EXPORT Type& type<two::EditNestMode>();
    export_ template <> TWO_UIO_EXPORT Type& type<two::EditorHint>();
    
    
    export_ template <> TWO_UIO_EXPORT Type& type<two::ScriptEditor>();
}



namespace two
{
	struct ProcessStructure;
	struct ProcessConstruct;

	export_ TWO_UIO_EXPORT void process_display(Widget& parent, ProcessDisplay& process);
	export_ TWO_UIO_EXPORT void process_display_structure(Widget& parent, ProcessStructure& process);
	export_ TWO_UIO_EXPORT void process_construct(Widget& parent, ProcessConstruct& process);
	export_ TWO_UIO_EXPORT Section& visual_script_edit(Widget& parent, VisualScript& script);
}



namespace two
{
	export_ TWO_UIO_EXPORT void meta_object_creator(Widget& parent);
	export_ TWO_UIO_EXPORT void object_injector(Widget& parent, Injector& injector);
	export_ TWO_UIO_EXPORT bool object_creator(Widget& parent, Creator& creator);

	export_ TWO_UIO_EXPORT bool object_switch_creator(Widget& parent, span<Type*> types);
	export_ TWO_UIO_EXPORT bool object_creator(Widget& parent, Type& type);
}


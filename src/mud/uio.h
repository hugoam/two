#pragma once

#include <mud/pool.h>
#include <mud/ui.h>
#include <mud/tree.h>
#include <mud/lang.h>
#include <mud/ecs.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/ctx.h>
#include <mud/infra.h>
#include <mud/type.h>





#ifndef MUD_UIO_EXPORT
#define MUD_UIO_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class EditNestMode : unsigned int;
    enum class EditorHint : unsigned int;
    
    
    class DispatchItem;
    struct SectionAction;
    struct Section;
    class DispatchSelector;
    struct EditSpec;
    class ScriptEditor;
    class DispatchInput;
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class MUD_UIO_EXPORT DispatchItem : public Dispatch<Widget&, Widget&>, public LazyGlobal<DispatchItem>
	{
	public:
		DispatchItem();
	};
}

namespace mud
{
#if 0
	export_ class MUD_UIO_EXPORT Dropper : public Widget
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


#ifndef MUD_MODULES
#include <stl/string.h>
#endif

namespace mud
{
	export_ MUD_UIO_EXPORT string object_name(Ref object);
	export_ MUD_UIO_EXPORT string object_icon(Ref object);

	export_ MUD_UIO_EXPORT Widget& object_button(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT Widget& object_item(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, Ref& selection);
	export_ MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, vector<Ref>& selection);
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditNestMode>();
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>();
    
    export_ template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>();
    
    export_ template struct MUD_UIO_EXPORT Typed<vector<mud::ScriptEditor*>>;
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	struct ProcessStructure;
	struct ProcessConstruct;

	export_ MUD_UIO_EXPORT void process_display(Widget& parent, ProcessDisplay& process);
	export_ MUD_UIO_EXPORT void process_display_structure(Widget& parent, ProcessStructure& process);
	export_ MUD_UIO_EXPORT void process_construct(Widget& parent, ProcessConstruct& process);
	export_ MUD_UIO_EXPORT Section& visual_script_edit(Widget& parent, VisualScript& script);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class MUD_UIO_EXPORT DispatchSelector : public Dispatch<bool, Widget&>, public LazyGlobal<DispatchSelector>
	{
	public:
		DispatchSelector();
	};

	export_ MUD_UIO_EXPORT void complex_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection = nullptr);
	export_ MUD_UIO_EXPORT void object_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection = nullptr);

	export_ MUD_UIO_EXPORT bool object_selector(Widget& parent, Indexer& indexer, Ref& result);
	export_ MUD_UIO_EXPORT bool object_selector(Widget& parent, Ref& result);

	export_ MUD_UIO_EXPORT void object_indexer_modal(Widget& parent, Indexer& indexer);
	export_ MUD_UIO_EXPORT bool object_selector_modal(Widget& screen, Widget& parent, Ref& result);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ MUD_UIO_EXPORT void meta_object_creator(Widget& parent);
	export_ MUD_UIO_EXPORT void object_injector(Widget& parent, Injector& injector);
	export_ MUD_UIO_EXPORT bool object_creator(Widget& parent, Creator& creator);

	export_ MUD_UIO_EXPORT bool object_switch_creator(Widget& parent, array<Type*> types);
	export_ MUD_UIO_EXPORT bool object_creator(Widget& parent, Type& type);
}


#include <stl/vector.h>

#ifndef MUD_CPP_20
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

	export_ extern MUD_UIO_EXPORT vector<EditSpec> g_edit_specs;
	
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
	export_ MUD_UIO_EXPORT func_ void multi_inspector(Widget& parent, Type& type, vector<Var>& objects, size_t& selected);

	export_ MUD_UIO_EXPORT func_ void multi_object_edit(Widget& parent, Type& type, vector<Ref> objects);

	template <class T_Object>
	T_Object* deref(unique<T_Object>& element) { return element.get(); }

#ifdef MUD_MEMORY_TRACKING
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



namespace mud
{
	export_ MUD_UIO_EXPORT bool call_edit(Widget& parent, Call& call);

	export_ MUD_UIO_EXPORT void callable_edit(Widget& parent, Callable& callable);
	export_ MUD_UIO_EXPORT void function_edit(Widget& parent, Function& function);
	export_ MUD_UIO_EXPORT void method_edit(Widget& parent, Ref object, Method& method);
	export_ MUD_UIO_EXPORT void method_hook(Widget& parent, Ref object, Method& method);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
namespace ui
{
	template <class T>
	inline bool enum_input(Widget& parent, T& value)
	{
		Enum& e = enu<T>();
		uint32_t index = e.index(Ref(&value));
		//ui::radio_switch(parent, to_array(e.m_names), index);
		if(ui::dropdown_input(parent, to_array(e.m_names), index))
		{
			e.varn(index, Ref(&value));
			return true;
		}
		return false;
	}

	template <class T>
	inline bool enum_field(Widget& parent, cstring name, T& value, bool reverse = false) { return field([&](Widget& self) { return enum_input<T>(self, value); }, parent, name, reverse); }
}

	export_ MUD_UIO_EXPORT void set_meta_palette(const vector<uint32_t>& palette);

	export_ MUD_UIO_EXPORT void meta_description(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_constructors(Widget& parent, Class& cls);
	export_ MUD_UIO_EXPORT void meta_methods(Widget& parent, Class& cls);
	export_ MUD_UIO_EXPORT void meta_fields(Widget& parent, Class& cls);

	export_ MUD_UIO_EXPORT void meta_enum(Widget& parent, Enum& enu);

	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Function& function);
	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Method& method);
	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void class_edit(Widget& parent, Class& cls);
	export_ MUD_UIO_EXPORT void meta_edit(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_browser(Widget& parent, Module& m);
	export_ MUD_UIO_EXPORT void meta_browser(Widget& parent);

	export_ MUD_UIO_EXPORT void type_browser(Widget& parent);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ MUD_UIO_EXPORT ScriptEditor
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

		TextScript& create_script(cstring name, Language language, Signature signature = {});
		VisualScript& create_visual(cstring name, Signature signature = {});
	};

	export_ MUD_UIO_EXPORT void script_edit_output(Widget& parent, Interpreter& interpreter);
	export_ MUD_UIO_EXPORT Section& script_edit_code(Widget& parent, TextScript& script);
	export_ MUD_UIO_EXPORT Section& script_edit(Widget& parent, TextScript& script);
	export_ MUD_UIO_EXPORT void script_editor(Widget& parent, ScriptEditor& editor);
}


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ MUD_UIO_EXPORT void structure_node(Widget& parent, Ref object, vector<Ref>& selection);
	export_ MUD_UIO_EXPORT void structure_view(Widget& parent, Ref object, vector<Ref>& selection);
}



namespace mud
{
	export_ MUD_UIO_EXPORT void ui_debug_modal(Widget& parent, Widget& target);
	export_ MUD_UIO_EXPORT void ui_debug_layout(Widget& parent, Widget& target);
	export_ MUD_UIO_EXPORT void ui_debug(Widget& parent, Widget& target);

	export_ MUD_UIO_EXPORT void ui_edit(Widget& parent, Sequence& selection);
	export_ MUD_UIO_EXPORT void ui_editor(Widget& parent);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class MUD_UIO_EXPORT DispatchInput : public Dispatch<bool, Widget&>, public Global<DispatchInput>
	{
	public:
		DispatchInput();
	};

	export_ MUD_UIO_EXPORT bool type_selector(Widget& parent, uint32_t& type, array<Type*> types);

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


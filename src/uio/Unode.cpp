//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <uio/Generated/Types.h>
#include <uio/Unode.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>

#include <obj/Reflect/Class.h>
#include <obj/Reflect/Convert.h>
#include <obj/Complex.h>

#include <uio/Edit/Section.h>
#include <uio/Edit/Method.h>

namespace mud
{
	bool modal_dialog(Widget& parent, cstring name, bool query)
	{
		Widget& self = ui::window(parent.root(), name);
		bool closed = !self.m_body || ui::button(parent, query ? "Done" : "Cancel").activated();
		//if(closed)
		//	self.close();
		return closed;
	}

	static string object_name(Ref object)
	{
		return object ? to_name(object.type(), object) : "null";
	}

	static string object_icon(Ref object)
	{
		return object ? "(" + string(meta(object).m_name) + ")" : "";
	}

	void object_context(Widget& parent, Ref object)
	{
		Widget& self = ui::popup(parent, ui::PopupFlags::Modal);
		//if(!self.m_open)
		//	self.close();

		if(meta(object).m_type_class == TypeClass::Complex)
			object = val<Complex>(object).m_construct;

		for(Method* method : cls(object).m_deep_methods)
		{
			Ref component = cls(object).get_related(object, *method->m_object_type);
			method_hook(self, component, *method);
		}
	}

	enum HookState
	{
		HOOK_CONTEXT = (1 << 0)
	};

	void object_hook(Widget& parent, Ref object)
	{
		carray<string, 2> elements = { object_name(object), object_icon(object) };
		if(ui::modal_multi_button(parent, parent, carray<cstring, 2>{ elements[0].c_str(), elements[1].c_str() }, HOOK_CONTEXT)) // (void*) id
			object_context(parent, object);

		//parent.m_onSelect = [&] { button.enableState(SELECTED); };
		//parent.m_onUnselect = [&] { button.disableState(SELECTED); };
	}

	bool object_trigger(Widget& parent, Ref object)
	{
		Widget& self = ui::multi_button(parent, carray<cstring, 2>{ object_name(object).c_str(), object_icon(object).c_str() }); // (void*)id;
		return self.activated();
	}
}

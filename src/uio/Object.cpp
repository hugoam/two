//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#ifdef MUD_ECS
#include <ecs/Entity.h>
#endif
#include <refl/Class.h>
#include <refl/Convert.h>
#include <ecs/Entity.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>
#include <ui/Sequence.h>
#include <uio/Types.h>
#include <uio/Unode.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Method.h>
#endif

namespace mud
{
	string object_name(Ref object)
	{
		if(!object) return "null";
		//else if(object.m_type->is<Entity>()) return to_name(val<Entity>(object).m_prototype.m_type, object);
		else return to_name(type(object), object);
	}

	string object_icon(Ref object)
	{
		if(!object) return "";
		//else if(type(object).is<Entity>()) return "(" + string(val<Entity>(object).m_prototype.m_type.m_name) + ")";
		else return "(" + string(type(object).m_name) + ")";
	}

	void object_context(Widget& parent, Ref object, uint32_t mode)
	{
		Widget& self = ui::popup(parent, ui::PopupFlags::AutoModal);
		if(!self.m_open)
			parent.m_switch &= ~mode;

		//if(meta(object).m_type_class == TypeClass::Object)
		//	object = val<Entity>(object);

		for(Method* method : cls(object).m_deep_methods)
		{
			Ref component = cls(object).as(object, *method->m_object_type);
			method_hook(self, component, *method);
		}
	}

	Widget& generic_object_item(Widget& parent, Ref object)
	{
		enum Modes { Context = (1 << 0) };

		Widget& self = ui::element(parent, object);
		ui::multi_item(self, carray<cstring, 2>{ object_icon(object).c_str(), object_name(object).c_str() });
		
		if(MouseEvent event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			self.m_switch |= Context;
		if((self.m_switch & Context) != 0)
			object_context(self, object, Context);

		return self;
	}

	Widget& object_button(Widget& parent, Ref object)
	{
		return generic_object_item(parent, object);
	}

	Widget& object_item(Widget& parent, Ref object)
	{
		if(DispatchItem::me().check(object))
			return DispatchItem::me().dispatch(object, parent);
		else
			return generic_object_item(parent, object);
	}

	bool object_item(Widget& parent, Ref object, Ref& selection)
	{
		Widget& self = object_item(parent, object);
		return ui::select_logic(self, object, selection);
	}

	bool object_item(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		Widget& self = object_item(parent, object);
		return ui::multiselect_logic(self, object, selection);
	}
}

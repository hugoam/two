//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.uio;

namespace two
{
	void object_injector(Widget& parent, Injector& injector)
	{
		Widget& self = ui::sheet(parent);
		call_edit(self, injector);
	}

	struct CreatorState : public NodeState
	{
		CreatorState(Type& type) : m_type(0), m_injector(make_unique<Injector>(type)) {}
		uint32_t m_type;
		unique<Injector> m_injector;
	};

	bool object_creator(Widget& parent, Injector& injector)
	{
		Widget& self = ui::widget(parent, styles().sheet, &injector);
		
		Table& fields = ui::columns(self, { 0.4f, 0.6f });
		call_edit(fields, injector);

		if(ui::button(self, "Create").activated())
		{
			if(false)//injector.m_constructor.validate(injector.m_args, 1))
			{
				injector.injectpool();
				return true;
			}
		}

		return false;
	}

	bool object_switch_creator(Widget& parent, span<Type*> types)
	{
		Widget& self = ui::sheet(parent);
		ui::title(self, "Create Object");

		CreatorState& state = self.state<CreatorState>(*types[0]);

		if(type_selector(self, state.m_type, types))
			state.m_injector = make_unique<Injector>(*types[state.m_type]);

		return object_creator(self, *state.m_injector);
	}

	bool object_creator(Widget& parent, Creator& creator)
	{
		Widget& self = ui::sheet(parent);

		ui::title(self, creator.m_prototype ? creator.m_prototype->m_name : creator.m_type.m_name);

		Table& fields = ui::table(self, { "field", "value" }, { 0.3f, 0.7f });
		call_edit(fields, creator.injector());

		if(ui::button(self, "Create").activated())
		{
			creator.m_injector->injectpool();
			return true;
		}

		return false;
	}

	struct ObjectCreatorState : public NodeState
	{
		ObjectCreatorState(Type& type) : m_creator(type) {}
		Creator m_creator;
	};

	bool object_creator(Widget& parent, Type& type)
	{
		Widget& self = ui::sheet(parent);
		ObjectCreatorState& state = self.state<ObjectCreatorState>(type);
		return object_creator(self, state.m_creator);
	}

	struct MetaObjectCreatorState : public NodeState
	{
		Type* m_type = nullptr;
	};

	void meta_object_creator(Widget& parent)
	{
		Widget& self = ui::sheet(parent);
		MetaObjectCreatorState& state = self.state<MetaObjectCreatorState>();

		for(Type* type : System::instance().m_types)
			if(is_root_type(*type) && !cls(*type).m_constructors.empty())
			{
				if(object_item(self, Ref(type)).activated())
					state.m_type = type;
			}

		if(state.m_type)
			object_creator(self, *state.m_type);
	}
}

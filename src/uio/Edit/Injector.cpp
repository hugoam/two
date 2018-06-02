//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#include <obj/Reflect/Class.h>
#include <obj/System/System.h>
#include <ui/Structs/Container.h>
#include <uio/Edit/Injector.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/Value.h>
#include <uio/Unode.h>
#endif

namespace mud
{
	struct MetaObjectCreatorState : public NodeState
	{
		Type* m_type = nullptr;
	};

	struct ObjectCreatorState : public NodeState
	{
		ObjectCreatorState(Type& type) : m_creator(type) {}
		Creator m_creator;
	};

	void object_injector_fields(Widget& parent, Injector& injector)
	{
		for(size_t i = 1; i < injector.m_args.size(); ++i)
		{
			const Param& param = injector.m_constructor.m_params[i];
			Ref value = injector.m_args[i];
			field_edit(parent, param.m_name, value, param.nullable());
			injector.m_args[i].set(value);
		}
	}

	void object_injector(Widget& parent, Injector& injector)
	{
		Widget& self = ui::sheet(parent);
		object_injector_fields(self, injector);
	}

	void object_creator_prototype(Widget& parent, Creator& creator)
	{
		Type* prototype = type_selector(parent, (Type*&) creator.m_prototype, (const std::vector<Type*>&) creator.m_type.m_class->m_prototypes);

		if(prototype && prototype != creator.m_prototype)
			creator.setPrototype(*prototype);
	}

	bool object_creator(Widget& parent, Creator& creator)
	{
		Widget& self = ui::stack(parent);

		if(creator.m_construct)
			object_creator_prototype(self, creator);

		ui::item(self, styles().title, creator.m_prototype ? creator.m_prototype->m_name : creator.m_type.m_name);
		static cstring columns[2] = { "field", "value" };
		Widget& fields = ui::table(self, { columns, 2 }, {}); //, { 0.4f, 0.6f });

		object_injector_fields(fields, creator.injector());

		if(ui::button(self, "Create").activated())
		{
			creator.create();
			return true;
		}

		return false;
	}

	bool object_creator(Widget& parent, Type& type)
	{
		Widget& self = ui::sheet(parent);
		ObjectCreatorState& state = self.state<ObjectCreatorState>(type);
		return object_creator(self, state.m_creator);
	}

	void meta_object_creator(Widget& parent)
	{
		Widget& self = ui::sheet(parent);
		MetaObjectCreatorState& state = self.state<MetaObjectCreatorState>();

		for(Type* type : System::instance().m_types)
			if(is_root_type(*type) && !type->m_class->m_constructors.empty())
			{
				if(object_item(self, type).activated())
					state.m_type = type;
			}

		if(state.m_type)
			object_creator(self, *state.m_type);
	}
}

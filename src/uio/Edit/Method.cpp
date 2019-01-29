//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <stl/string.h>
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#include <refl/Meta.h>
#include <refl/Method.h>
#include <refl/Call.h>
#include <ui/Ui.h>
#include <ui/Structs/Container.h>
#include <uio/Edit/Value.h>
#include <uio/Edit/Method.h>
#endif

#include <cstring>

namespace mud
{
	struct CallableEditState : public NodeState
	{
		CallableEditState(Callable& callable) : m_call(callable) {}
		CallableEditState(Callable& callable, Ref object) : m_call(callable, object) {}
		Call m_call;
	};

	bool call_edit(Widget& parent, Call& call)
	{
		bool method = strcmp(call.m_callable->m_params[0].m_name, "self") == 0;
		uint16_t offset = method ? 1 : 0;
		for(uint16_t i = offset; i < call.m_callable->m_params.size(); ++i)
		{
			const Param& param = call.m_callable->m_params[i];
			bool link = is_object(type(param.default_val())) || param.nullable();
			field_edit(parent, param.m_name, call.m_arguments[i].m_ref, link);
		}

		/*uint16_t offset = call.m_arguments.size() - call.m_callable->m_params.size();
		for(Param& param : call.m_callable->m_params)
			field_edit(parent, param.m_name, call.m_arguments[param.m_index + offset], param.nullable());*/
		return false;
	}

	void callable_edit(Widget& parent, Callable& callable)
	{
		Widget& self = ui::row(parent);
		CallableEditState& state = self.state<CallableEditState>(callable);
		call_edit(self, state.m_call);
	}

	void function_edit(Widget& parent, Function& function)
	{
		callable_edit(parent, function);
	}

	void method_edit(Widget& parent, Ref object, Method& method)
	{
		Widget& self = ui::row(parent);
		CallableEditState& state = self.state<CallableEditState>(method, object);
		if(ui::button(self, method.m_name).activated())
			state.m_call();
		call_edit(self, state.m_call);
	}

	void method_edit_modal(Widget& parent, Ref object, Method& method)
	{
		enum Modes { CALL = 1 << 0 };
		string name = "Call method " + string(method.m_object_type->m_name) + "::" + method.m_name;
		
		if(ui::modal_button(parent, parent, "Call", CALL))
		{
			Widget& modal = ui::auto_modal(parent, CALL, { 600, 400 });
			method_edit(modal, object, method);
		}
	}

	void method_trigger(Widget& parent, Ref object, Method& method)
	{
		if(ui::modal_button(parent, parent, method.m_name, uint32_t(1 << 0)))
			method_edit_modal(parent, object, method);
	}

	void method_hook(Widget& parent, Ref object, Method& method)
	{
		method_edit(parent, object, method);
	}
}

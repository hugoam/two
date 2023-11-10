//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.tool;
#else
#include <stl/algorithm.h>
#include <tool/Types.h>
#include <tool/ActionStack.h>
#endif

namespace two
{
	ActionStack::ActionStack()
		: m_done()
		, m_undone()
	{}

	ActionStack::~ActionStack()
	{}

	void ActionStack::push(object<EditorAction> action)
	{
		m_undone.clear();
		//action->apply();
		m_done.push_back(move(action));
	}

	void ActionStack::redo()
	{
		if(m_undone.empty())
			return;

		m_undone.back()->apply();
		m_done.push_back(pop(m_undone));
	}

	void ActionStack::undo()
	{
		if(m_done.empty())
			return;

		m_done.back()->undo();
		m_undone.push_back(pop(m_done));
	}

	UndoTool::UndoTool(ToolContext& context)
		: Tool(context, "Undo", type<UndoTool>())
	{}

	void UndoTool::activate()
	{
		m_context.m_action_stack->undo();
		m_state = ToolState::Done;
	}

	RedoTool::RedoTool(ToolContext& context)
		: Tool(context, "Redo", type<RedoTool>())
	{}

	void RedoTool::activate()
	{
		m_context.m_action_stack->redo();
		m_state = ToolState::Done;
	}
}

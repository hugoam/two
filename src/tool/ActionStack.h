//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tool/Tool.h>
#include <tool/Forward.h>

namespace two
{
	export_ class TWO_TOOL_EXPORT ActionStack
	{
	public:
		ActionStack();
		~ActionStack();

		ActionStack(const ActionStack& other) = delete;
		ActionStack& operator=(const ActionStack& other) = delete;

		void push(object<EditorAction> action);

		void redo();
		void undo();

	private:
		vector<object<EditorAction>> m_done;
		vector<object<EditorAction>> m_undone;
	};

	export_ class refl_ TWO_TOOL_EXPORT UndoTool : public Tool
	{
	public:
		UndoTool(ToolContext& context);

		virtual void activate() final;
	};

	export_ class refl_ TWO_TOOL_EXPORT RedoTool : public Tool
	{
	public:
		RedoTool(ToolContext& context);

		virtual void activate() final;
	};
}

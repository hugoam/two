//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/NonCopy.h>
#include <edit/Tool.h>
#include <edit/Generated/Forward.h>

namespace mud
{
	export_ class MUD_EDIT_EXPORT ActionStack : public NonCopy
	{
	public:
		ActionStack();

		void push(object_ptr<EditorAction> action);

		void redo();
		void undo();

	private:
		std::vector<object_ptr<EditorAction>> m_done;
		std::vector<object_ptr<EditorAction>> m_undone;
	};

	export_ class _refl_ MUD_EDIT_EXPORT UndoTool : public Tool
	{
	public:
		UndoTool(ToolContext& context);

		virtual void activate() final;
	};

	export_ class _refl_ MUD_EDIT_EXPORT RedoTool : public Tool
	{
	public:
		RedoTool(ToolContext& context);

		virtual void activate() final;
	};
}

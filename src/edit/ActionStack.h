//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/NonCopy.h>
#endif
#include <edit/Tool.h>
#include <edit/Forward.h>

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

	export_ class refl_ MUD_EDIT_EXPORT UndoTool : public Tool
	{
	public:
		UndoTool(ToolContext& context);

		virtual void activate() final;
	};

	export_ class refl_ MUD_EDIT_EXPORT RedoTool : public Tool
	{
	public:
		RedoTool(ToolContext& context);

		virtual void activate() final;
	};
}

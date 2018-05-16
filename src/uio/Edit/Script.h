//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Edit/Section.h>
#include <lang/Script.h>

namespace mud
{
	class _refl_ MUD_UIO_EXPORT ScriptEditor
	{
	public:
		ScriptEditor();
		~ScriptEditor();

		std::vector<VisualScript*> m_visual_scripts;
		std::vector<Script*> m_scripts;

		LuaInterpreter* m_interpreter = nullptr;

		void open(Script& script);
		Script& create_script(cstring name);
		void close(Script& script);

		void open(VisualScript& script);
		VisualScript& create_visual(cstring name);
		void close(VisualScript& script);

		virtual void handleAdd(VisualScript& script) { this->open(script); }
		virtual void handleRemove(VisualScript& script) { this->close(script); }
	};

	MUD_UIO_EXPORT void script_edit_output(Widget& parent, LuaInterpreter& lua);
	MUD_UIO_EXPORT void script_edit_code(Widget& parent, Script& script, ActionList actions = {});
	MUD_UIO_EXPORT void script_edit(Widget& parent, Script& script, ActionList actions = {});
	MUD_UIO_EXPORT void script_editor(Widget& parent, ScriptEditor& editor);
}

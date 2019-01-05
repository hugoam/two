//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <lang/Script.h>
#endif
#include <ui/Section.h>

namespace mud
{
	export_ class refl_ MUD_UIO_EXPORT ScriptEditor
	{
	public:
		ScriptEditor();
		~ScriptEditor();

		std::vector<Script*> m_scripts;

		LuaInterpreter* m_lua = nullptr;
		WrenInterpreter* m_wren = nullptr;

		void reset_interpreters(LuaInterpreter& lua, WrenInterpreter& wren);

		void open(Script& script);
		void close(Script& script);

		TextScript& create_script(cstring name, Language language, Signature signature = {});
		VisualScript& create_visual(cstring name, Signature signature = {});
	};

	export_ MUD_UIO_EXPORT void script_edit_output(Widget& parent, Interpreter& interpreter);
	export_ MUD_UIO_EXPORT void script_edit_code(Widget& parent, TextScript& script, ActionList actions = {});
	export_ MUD_UIO_EXPORT void script_edit(Widget& parent, TextScript& script, ActionList actions = {});
	export_ MUD_UIO_EXPORT void script_editor(Widget& parent, ScriptEditor& editor);
}

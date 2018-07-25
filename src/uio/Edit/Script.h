//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <lang/Script.h>
#endif
#include <uio/Edit/Section.h>

namespace mud
{
	export_ class refl_ MUD_UIO_EXPORT ScriptEditor
	{
	public:
		ScriptEditor();
		~ScriptEditor();

		std::vector<Script*> m_scripts;

		LuaInterpreter* m_interpreter = nullptr;

		void open(Script& script);
		void close(Script& script);

		LuaScript& create_script(cstring name);
		VisualScript& create_visual(cstring name);
	};

	export_ MUD_UIO_EXPORT void script_edit_output(Widget& parent, LuaInterpreter& lua);
	export_ MUD_UIO_EXPORT void script_edit_code(Widget& parent, LuaScript& script, ActionList actions = {});
	export_ MUD_UIO_EXPORT void script_edit(Widget& parent, LuaScript& script, ActionList actions = {});
	export_ MUD_UIO_EXPORT void script_editor(Widget& parent, ScriptEditor& editor);
}

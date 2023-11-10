//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/string.h>
#include <lang/Script.h>
#include <ui/Section.h>
#endif

namespace two
{
	export_ class refl_ TWO_UIO_EXPORT ScriptEditor
	{
	public:
		ScriptEditor();
		~ScriptEditor();

		vector<Script*> m_scripts;

		LuaInterpreter* m_lua = nullptr;
		WrenInterpreter* m_wren = nullptr;

		void reset_interpreters(LuaInterpreter& lua, WrenInterpreter& wren);

		void open(Script& script);
		void close(Script& script);

		TextScript& create_script(const string& name, Language language, Signature signature = {});
		VisualScript& create_visual(const string& name, Signature signature = {});
	};

	export_ TWO_UIO_EXPORT void script_edit_output(Widget& parent, Interpreter& interpreter);
	export_ TWO_UIO_EXPORT Section& script_edit_code(Widget& parent, TextScript& script);
	export_ TWO_UIO_EXPORT Section& script_edit(Widget& parent, TextScript& script);
	export_ TWO_UIO_EXPORT void script_editor(Widget& parent, ScriptEditor& editor);
}

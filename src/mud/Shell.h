#pragma once

#include <obj/Graph/Node.h>
#include <obj/System/System.h>
#include <mud/Forward.h>
#include <edit/EditContext.h>

#include <gfx/GfxSystem.h>
#include <lang/Lua.h>

#include <uio/Edit/Script.h>

namespace mud
{
	using Selection = std::vector<Ref>;

	class Shell : public NonCopy
	{
	public:
		Shell(array<cstring> resource_paths, int argc, char *argv[]);
		~Shell();

		void init();
		void run(const std::function<void(Shell&)>& func, size_t iterations = 0U);
		bool pump();

	public:
		string m_exec_path;
		string m_resource_path;

		User m_user;

		GfxSystem m_gfx_system;
		LuaInterpreter m_lua;
		EditContext m_editor;

		UiWindow* m_ui_window = nullptr;
		Widget* m_ui = nullptr;

		std::function<void(Shell&)> m_pump;
	};
}


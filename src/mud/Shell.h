#pragma once

#include <mud/Forward.h>

#include <ui/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>

namespace mud
{
	using Selection = std::vector<Ref>;

	struct ShellContext
	{
		Docksystem m_docksystem;
		Widget* m_screen;
		Dockbar* m_dockbar;
	};

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

		//User m_user;

		JobSystem m_job_system;
		GfxSystem m_gfx_system;
		//LuaInterpreter m_lua;
		//WrenInterpreter m_wren;
		//EditContext m_editor;
		ShellContext m_editor;

		unique_ptr<Context> m_context = nullptr;
		unique_ptr<Vg> m_vg = nullptr;
		unique_ptr<UiWindow> m_ui_window = nullptr;
		Ui* m_ui = nullptr;

		std::function<void(Shell&)> m_pump;
	};

	void shell_context(Widget& parent, ShellContext& context);
}


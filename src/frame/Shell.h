#pragma once

#include <frame/Forward.h>

#include <jobs/Api.h>
#include <ui/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>

namespace mud
{
	using Selection = vector<Ref>;

	struct refl_ ShellContext
	{
		Docksystem m_docksystem;
		attr_ Widget* m_screen = nullptr;
		attr_ Dockbar* m_dockbar = nullptr;
	};

	class refl_ Shell : public NonCopy
	{
	public:
		constr_ Shell(cstring resource_path, cstring exec_path = nullptr);
		~Shell();

		void init();
		void run(const std::function<void(Shell&)>& func, size_t iterations = 0U);
		meth_ bool pump();

	public:
		attr_ string m_exec_path;
		attr_ string m_resource_path;
		
		attr_ JobSystem m_job_system;
		attr_ GfxSystem m_gfx_system;
		attr_ ShellContext m_editor;

		unique_ptr<Context> m_context = nullptr;
		unique_ptr<Vg> m_vg = nullptr;
		unique_ptr<UiWindow> m_ui_window = nullptr;

		attr_ Ui* m_ui = nullptr;

		std::function<void(Shell&)> m_pump;
	};

	void shell_context(Widget& parent, ShellContext& context);
}


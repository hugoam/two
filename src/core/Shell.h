#pragma once

#include <core/Forward.h>

#include <ui/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>

#ifdef NEED_REFL
#include <mud/Modules.h>
namespace mud
{
	void load_modules()
	{
		System::instance().load_modules({ &mud_infra::m(), &mud_type::m(), &mud_pool::m(), &mud_refl::m(), &mud_ecs::m(), &mud_tree::m() });
		System::instance().load_modules({ &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_noise::m(), &mud_wfc::m(), &mud_fract::m(), &mud_lang::m() });
		System::instance().load_modules({ &mud_ctx::m(), &mud_ui::m(), &mud_gfx::m(), &mud_gfx_pbr::m(), &mud_gfx_obj::m(), &mud_gfx_gltf::m(), &mud_gfx_ui::m(), &mud_tool::m() });
	}
}
#endif

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


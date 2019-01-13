#include <mud/core.h>
//#include <core/Types.h>

#include <ui-vg/VgVg.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

//#define MUD_GFX_DEFERRED

namespace mud
{
#ifdef MUD_PLATFORM_EMSCRIPTEN
	static Shell* g_app = nullptr;
	static size_t g_frame = 0U;
	static size_t g_iterations = 0U;
	static void iterate()
	{
		g_app->pump();
		if(g_iterations > 0 && g_frame++ > g_iterations)
			emscripten_cancel_main_loop();
	}
#endif

    Shell::Shell(cstring resource_path, cstring exec_path)
        : m_exec_path(exec_path ? string(exec_path) : "")
		, m_resource_path(resource_path)
		, m_job_system()
		, m_gfx_system(resource_path)
	{
		// @todo this should be automatically done by math module
		register_math_conversions();

		//declare_gfx_edit();

		m_gfx_system.m_job_system = &m_job_system;
		m_job_system.adopt();

		this->init();
	}

	Shell::~Shell()
    {
		m_job_system.emancipate();
	}

	void Shell::run(const std::function<void(Shell&)>& func, size_t iterations)
	{
		m_pump = func;

#ifdef MUD_PLATFORM_EMSCRIPTEN
		g_app = this;
		g_iterations = iterations;
		emscripten_set_main_loop(iterate, 0, 1);
#else
		size_t frame = 0;
		while(pump() && (iterations == 0 || frame++ < iterations));
#endif
	}

	bool Shell::pump()
	{
		bool pursue = m_ui_window->input_frame();
		m_pump(*this);
		m_gfx_system.begin_frame();
		m_ui_window->render_frame();
		pursue &= m_gfx_system.next_frame();
		return pursue;
	}

	void Shell::init()
	{
		m_context = m_gfx_system.create_context("mud EditorCore", 1600, 900, false);
		GfxContext& context = as<GfxContext>(*m_context);
#if defined MUD_VG_VG
		m_vg = make_object<VgVg>(m_resource_path.c_str(), &m_gfx_system.m_allocator);
#elif defined MUD_VG_NANOVG
		m_vg = make_object<VgNanoBgfx>(m_resource_path.c_str());
#endif
		context.m_reset_vg = [&] { return m_vg->load_texture(context.m_target->m_diffuse.idx); };

		m_ui_window = make_unique<UiWindow>(*m_context, *m_vg);
		m_ui = m_ui_window->m_root_sheet.get();

		style_minimal(*m_ui_window);
	}

	void shell_context(Widget& parent, ShellContext& context)
	{
#if 0
		edit_context(parent, context, true);
#else
		Widget& board = ui::board(parent);
		context.m_screen = &ui::board(board);
		context.m_dockbar = &ui::dockbar(board, context.m_docksystem);
#endif
	}
}

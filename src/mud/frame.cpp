#include <mud/ui.vg.h>
#include <mud/frame.h>
#include <mud/infra.h>
#include <mud/type.h>
//#include <frame/Types.h>


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

    Shell::Shell(const string& resource_path, const string& exec_path)
        : m_exec_path(exec_path)
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

	void Shell::run(const ShellUpdate& func, size_t iterations)
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
		if(m_pump)
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
		m_vg = oconstruct<VgVg>(m_resource_path.c_str(), &m_gfx_system.allocator());
#elif defined MUD_VG_NANOVG
		m_vg = oconstruct<VgNanoBgfx>(m_resource_path.c_str());
#endif
		m_gfx_system.m_vg = &*m_vg;
		context.m_reset_vg = [](GfxContext& context, Vg& vg) { return vg.load_texture(context.m_target->m_diffuse.idx); };

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

#ifdef MUD_MODULES
module mud.frame;
#else
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_FRAME_EXPORT Type& type<mud::Shell>() { static Type ty("Shell", sizeof(mud::Shell)); return ty; }
    template <> MUD_FRAME_EXPORT Type& type<mud::ShellContext>() { static Type ty("ShellContext", sizeof(mud::ShellContext)); return ty; }
}

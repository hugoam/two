#include <frame/Shell.h>
//#include <frame/Types.h>

#include <ui-vg/VgVg.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

#include <stl/vector.hpp>

//#define TWO_GFX_DEFERRED

namespace two
{
#ifdef TWO_PLATFORM_EMSCRIPTEN
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

	unique<Vg> create_vg(GfxSystem& gfx, const string& resource_path)
	{
#if defined TWO_VG_VG
		return construct<VgVg>(resource_path, &gfx.allocator());
#elif defined TWO_VG_NANOVG
		return construct<VgNanoBgfx>(m_resource_path);
#endif
	}

	ShellWindow::ShellWindow(GfxSystem& gfx, uint32_t index, const string& name, const uvec2& size, bool fullscreen)
		: GfxWindow(gfx, name, size, fullscreen, index == 0)
#if !GLOBAL_VG
		, m_vg(create_vg(gfx, gfx.m_resource_path))
#endif
		, m_index(index)
		, m_ui_window(*this, *m_vg)
	{
#if GLOBAL_VG
		if(index == 0) m_vg->setup_context();
#else
		GfxWindow::m_vg = m_vg.get();
		m_vg->setup_context();
#endif
			

		m_reset_vg = [](GfxWindow& context, Vg& vg) { return vg.load_texture(context.m_target->m_diffuse.m_tex.idx); };

		m_ui_window.init();
		m_ui = m_ui_window.m_ui.get();

		style_minimal(m_ui_window);
	}

	bool ShellWindow::begin_frame()
	{
		GfxWindow::begin_frame();
		return m_ui_window.input_frame();
	}

	void ShellWindow::render_frame()
	{
		GfxWindow::render_frame();
		bgfx::setViewFrameBuffer(240 + m_index, m_target->m_backbuffer.m_fbo);
		m_ui_window.render_frame(240 + m_index);
	}

    Shell::Shell(const string& resource_path, const string& exec_path, bool window)
        : m_exec_path(exec_path)
		, m_resource_path(resource_path)
		, m_job_system()
		, m_gfx(resource_path)
	{
		// @todo this should be automatically done by math module
		register_math_conversions();

		//declare_gfx_edit();

		m_gfx.m_job_system = &m_job_system;
		m_job_system.adopt();

		this->init(window);
	}

	Shell::~Shell()
    {
		m_job_system.emancipate();
	}

	void Shell::run(const ShellUpdate& func, size_t iterations)
	{
		m_pump = func;

#ifdef TWO_PLATFORM_EMSCRIPTEN
		g_app = this;
		g_iterations = iterations;
		emscripten_set_main_loop(iterate, 0, 1);
#else
		size_t frame = 0;
		while(pump() && (iterations == 0 || frame++ < iterations));
#endif
	}

	bool Shell::begin_frame()
	{
		bool pursue = m_gfx.begin_frame();
		return pursue;
	}

	void Shell::end_frame()
	{
		m_gfx.render_contexts();
		m_gfx.end_frame();
	}

	bool Shell::pump()
	{
		bool pursue = this->begin_frame();
		if(m_pump)
		{
			for(auto& window : m_windows)
				m_pump(*this, *window);
		}
		this->end_frame();
		return pursue;
	}

	void Shell::init(bool window)
	{
#if GLOBAL_VG
		m_vg = create_vg(m_gfx, m_resource_path);
#endif

		if(window)
			this->window("two", uvec2(1600U, 900U), false);
	}

	ShellWindow& Shell::window(const string& name, const uvec2& size, bool fullscreen)
	{
		const uint32_t index = m_windows.size();
		m_windows.push_back(construct<ShellWindow>(m_gfx, index, name, size, fullscreen));
		return *m_windows.back();
	}

	void Shell::add_file(const string& path, span<uint8_t> data)
	{
		create_file_tree(path);
		write_binary_file(path, data);
	}

	ShellWindow& Shell::main_window()
	{
		return *m_windows[0];
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

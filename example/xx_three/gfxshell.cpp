#include <xx_three/xx_three.h>
#include <xx_three/gfxshell.h>

#if !UI

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

#include <stl/vector.hpp>

//#define TWO_GFX_DEFERRED

namespace two
{
#ifdef TWO_PLATFORM_EMSCRIPTEN
	static GfxShell* g_app = nullptr;
	static size_t g_frame = 0U;
	static size_t g_iterations = 0U;
	static void iterate()
	{
		g_app->pump();
		if(g_iterations > 0 && g_frame++ > g_iterations)
			emscripten_cancel_main_loop();
	}
#endif

	GfxContext::GfxContext(GfxSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main)
		: GfxWindow(gfx, name, size, fullscreen, main)
	{
		this->init(*this);
	}

	bool GfxContext::begin_frame()
	{
		InputContext::begin_frame();
		return GfxWindow::begin_frame();
	}

	void GfxContext::end_frame()
	{
		InputContext::end_frame();
		GfxWindow::end_frame();
	}

	GfxShell::GfxShell(const string& resource_path, const string& exec_path, bool window)
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

	GfxShell::~GfxShell()
    {
		m_job_system.emancipate();
	}

	void GfxShell::run(const ShellUpdate& func, size_t iterations)
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

	bool GfxShell::begin_frame()
	{
		bool pursue = m_gfx.begin_frame();

		//GfxWindow& w = this->main_window();
		//bgfx::setViewFrameBuffer(240, w.m_target->m_backbuffer.m_fbo);
		//bgfx::setViewClear(240, BGFX_CLEAR_COLOR);
		//bgfx::touch(240);

		return pursue;
	}

	void GfxShell::end_frame()
	{
		m_gfx.render_contexts();
		m_gfx.end_frame();
	}

	bool GfxShell::pump()
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

	void GfxShell::init(bool window)
	{
		if(window)
			this->window("two", uvec2(1600U, 900U), false);
	}

	GfxContext& GfxShell::window(const string& name, const uvec2& size, bool fullscreen)
	{
		m_windows.push_back(construct<GfxContext>(m_gfx, name, size, fullscreen));
		return *m_windows.back();
	}

	void GfxShell::add_file(const string& path, span<uint8_t> data)
	{
		create_file_tree(path);
		write_binary_file(path, data);
	}

	GfxContext& GfxShell::main_window()
	{
		return *m_windows[0];
	}

	GfxViewer::GfxViewer(GfxWindow& context, Scene& scene)
		: m_scene(&scene)
		, m_context(context)
		, m_camera()
		, m_viewport(m_camera, scene)
	{
		m_position = vec2(0.f);
		m_size = vec2(context.m_fb_size);

		m_viewport.m_rect = vec4(vec2(0.f), vec2(1.f));
		m_viewport.m_autoflip = true;

		m_viewport.m_tasks.push_back([&](Render& render) { this->render(render); });

		m_context.m_viewports.push_back(&m_viewport);

		//this->take_focus();
	}

	GfxViewer::~GfxViewer()
	{
		remove(m_context.m_viewports, &m_viewport);
	}

	void GfxViewer::update()
	{}

	void GfxViewer::render(Render& render)
	{
		for(auto& picker : m_pickers)
		{
			picker->process(render, picker->m_query);
		}

		//#define TWO_DEBUG_PICKER_TEXTURE
#ifdef TWO_DEBUG_PICKER_TEXTURE
		if(m_picker)
		{
			vec4 source_rect = { vec2(0.f), vec2(m_pick_query.m_rect.size) };
			vec4 target_rect = { vec2(0.f), vec2(render.m_target->m_size) * 0.33f };
			m_gfx.m_copy->quad(*render.m_target, 251, BGFX_INVALID_HANDLE, m_picker->m_fbo_texture, { source_rect, target_rect, true });
		}
#endif
	}

	vec4 GfxViewer::query_rect()
	{
		const vec4 absolute = vec4(m_position, m_size);
		return absolute / vec2(m_context.m_size);
	}

	void GfxViewer::resize()
	{
		m_viewport.m_rect = this->query_rect();
	}

	Ray GfxViewer::mouse_ray(const vec2& pos)
	{
		float xNDC = (pos.x / m_size.x) * 2.0f - 1.0f;
		float yNDC = ((m_size.y - pos.y) / m_size.y) * 2.0f - 1.0f;
		return m_camera.ray(vec2(xNDC, yNDC));
	}

	Picker& GfxViewer::picker(size_t index)
	{
		if(m_pickers.size() <= index)
			m_pickers.resize(index + 1);
		if(!m_pickers[index])
			m_pickers[index] = make_unique<Picker>(m_scene->m_gfx, *m_context.m_target);
		return *m_pickers[index];
	}

#if 0
	SceneViewer::SceneViewer(Widget* parent, void* identity)
		: GfxViewer(parent, identity, m_scene)
		, m_scene(as<GfxWindow>(parent->ui_window().m_context).m_gfx)
	{}
#endif
}

#endif

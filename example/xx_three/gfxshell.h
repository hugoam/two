#pragma once

#if !UI
#include <infra/Api.h>
#include <ecs/Api.h>
#include <jobs/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>

namespace two
{
	class GfxShell;

	using ShellUpdate = void(*)(GfxShell&, GfxWindow&);
	//using ShellUpdate = std::function<void(ShellX&)>;

	export_ class refl_ GfxShell
	{
	public:
		constr_ GfxShell(const string& resource_path, const string& exec_path = "", bool window = true);
		~GfxShell();

		meth_ void init(bool window = true);
		meth_ GfxWindow& window(const string& name, const uvec2& size, bool fullscreen = false);

		meth_ void add_file(const string& path, span<uint8_t> data);

		void run(const ShellUpdate& func, size_t iterations = 0U);

		meth_ bool begin_frame();
		meth_ void end_frame();

		meth_ bool pump();

		meth_ GfxWindow& main_window();

	public:
		attr_ string m_exec_path;
		attr_ string m_resource_path;
		
		attr_ JobSystem m_job_system;
		attr_ GfxSystem m_gfx;

		vector<unique<GfxWindow>> m_windows;

		ShellUpdate m_pump = nullptr;
	};

	export_ class refl_ GfxViewer
	{
	public:
		GfxViewer(GfxWindow& context, Scene& scene);
		~GfxViewer();

		attr_ Scene* m_scene;
		GfxWindow& m_context;

		attr_ Camera m_camera;
		attr_ Viewport m_viewport;
		attr_ vec2 m_position;
		attr_ vec2 m_size;

		vector<unique<Picker>> m_pickers;

		Item* m_hovered = nullptr;

		void update();

		void render(Render& render);

		void resize();
		vec4 query_rect();

		Ray mouse_ray(const vec2& pos);

		Picker& picker(size_t index);
	};

}
#endif

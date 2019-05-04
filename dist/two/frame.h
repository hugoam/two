#pragma once

#include <two/gfx.h>
#include <two/ui.h>
#include <two/geom.h>
#include <two/jobs.h>
#include <two/ecs.h>
#include <two/math.h>
#include <two/gfx.ui.h>
#include <two/infra.h>
#include <two/type.h>





#ifndef TWO_FRAME_EXPORT
#define TWO_FRAME_EXPORT TWO_IMPORT
#endif

namespace two
{
	struct ShellContext;
	class ShellWindow;
    class Shell;
}


#define GLOBAL_VG 0

namespace two
{
	struct refl_ ShellContext
	{
		Docksystem m_docksystem;
		attr_ Widget* m_screen = nullptr;
		attr_ Dockbar* m_dockbar = nullptr;
	};
	
	using ShellUpdate = void(*)(Shell&, ShellWindow&);
	//using ShellUpdate = std::function<void(Shell&)>;

	class refl_ ShellWindow : public GfxWindow
	{
	public:
		ShellWindow(GfxSystem& gfx, uint32_t index, const string& name, const uvec2& size, bool fullscreen = false);

#if !GLOBAL_VG
		unique<Vg> m_vg = nullptr;
#endif

		attr_ uint32_t m_index = 0;
		attr_ UiWindow m_ui_window;
		attr_ Ui* m_ui = nullptr;

		virtual bool begin_frame() override;
		virtual void render_frame() override;
		//virtual void end_frame() override;
	};

	class refl_ Shell
	{
	public:
		constr_ Shell(const string& resource_path, const string& exec_path = "", bool window = true);
		~Shell();

		meth_ void init(bool window = true);
		meth_ ShellWindow& window(const string& name, const uvec2& size, bool fullscreen = false);

		meth_ void add_file(const string& path, span<uint8_t> data);

		void run(const ShellUpdate& func, size_t iterations = 0U);

		meth_ bool begin_frame();
		meth_ void end_frame();

		meth_ bool pump();

		meth_ ShellWindow& main_window();

	public:
		attr_ string m_exec_path;
		attr_ string m_resource_path;
		
		attr_ JobSystem m_job_system;
		attr_ GfxSystem m_gfx;
		attr_ ShellContext m_editor;

#if GLOBAL_VG
		unique<Vg> m_vg = nullptr;
#endif

		vector<unique<ShellWindow>> m_windows;

		ShellUpdate m_pump = nullptr;
	};

	void shell_context(Widget& parent, ShellContext& context);
}


#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_MODULES
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_FRAME_EXPORT Type& type<two::ShellContext>();
    export_ template <> TWO_FRAME_EXPORT Type& type<two::ShellWindow>();
    export_ template <> TWO_FRAME_EXPORT Type& type<two::Shell>();
}

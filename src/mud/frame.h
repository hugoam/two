#pragma once

#include <mud/gfx.h>
#include <mud/ui.h>
#include <mud/jobs.h>
#include <mud/gfx.ui.h>
#include <mud/infra.h>
#include <mud/type.h>




#ifndef MUD_FRAME_EXPORT
#define MUD_FRAME_EXPORT MUD_IMPORT
#endif

namespace mud
{
	struct ShellContext;
    class Shell;
}


namespace mud
{
	using Selection = vector<Ref>;

	struct refl_ ShellContext
	{
		Docksystem m_docksystem;
		attr_ Widget* m_screen = nullptr;
		attr_ Dockbar* m_dockbar = nullptr;
	};
	
	using ShellUpdate = void(*)(Shell&);
	//using ShellUpdate = std::function<void(Shell&)>;

	class refl_ Shell : public NonCopy
	{
	public:
		constr_ Shell(const string& resource_path, const string& exec_path = "");
		~Shell();

		void init();
		void run(const ShellUpdate& func, size_t iterations = 0U);
		meth_ bool pump();

	public:
		attr_ string m_exec_path;
		attr_ string m_resource_path;
		
		attr_ JobSystem m_job_system;
		attr_ GfxSystem m_gfx_system;
		attr_ ShellContext m_editor;

		unique<Context> m_context = nullptr;
		unique<Vg> m_vg = nullptr;
		unique<UiWindow> m_ui_window = nullptr;

		attr_ Ui* m_ui = nullptr;

		ShellUpdate m_pump = nullptr;
	};

	void shell_context(Widget& parent, ShellContext& context);
}



#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <cstdint>
#include <stl/vector.h>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::Shell>();
    export_ template <> MUD_FRAME_EXPORT Type& type<mud::ShellContext>();
    
    export_ template struct MUD_FRAME_EXPORT Typed<vector<mud::Shell*>>;
    export_ template struct MUD_FRAME_EXPORT Typed<vector<mud::ShellContext*>>;
}

#include <mud/gfx.refl.h>
#include <mud/frame.h>
#include <mud/gfx.ui.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/frame.refl.h>


#ifdef MUD_MODULES
module mud.frame;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;

void mud_Shell__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Shell( *static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<bool*>(args[2]) ); }
void mud_Shell_init(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Shell*>(object)).init(*static_cast<bool*>(args[0])); }
void mud_Shell_window(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::Shell*>(object)).window(*static_cast<stl::string*>(args[0]), *static_cast<mud::uvec2*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_Shell_begin_frame(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Shell*>(object)).begin_frame(); }
void mud_Shell_end_frame(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Shell*>(object)).end_frame(); }
void mud_Shell_pump(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Shell*>(object)).pump(); }
void mud_Shell_main_window(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Shell*>(object)).main_window(); }
void mud_ShellContext__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ShellContext(  ); }
void mud_ShellContext__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ShellContext((*static_cast<mud::ShellContext*>(other))); }

namespace mud
{
	void mud_frame_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::Shell
	{
		Type& t = type<mud::Shell>();
		static Meta meta = { t, &namspc({ "mud" }), "Shell", sizeof(mud::Shell), TypeClass::Object };
		// bases
		// defaults
		static stl::string construct_0_exec_path_default = "";
		static bool construct_0_window_default = true;
		static bool init_0_window_default = true;
		static bool window_0_fullscreen_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Shell__construct_0, { { "resource_path", type<stl::string>(),  }, { "exec_path", type<stl::string>(), Param::Default, &construct_0_exec_path_default }, { "window", type<bool>(), Param::Default, &construct_0_window_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Shell, m_exec_path), type<stl::string>(), "exec_path", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shell, m_resource_path), type<stl::string>(), "resource_path", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shell, m_job_system), type<mud::JobSystem>(), "job_system", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Shell, m_gfx), type<mud::GfxSystem>(), "gfx", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Shell, m_editor), type<mud::ShellContext>(), "editor", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "init", Address(), mud_Shell_init, { { "window", type<bool>(), Param::Default, &init_0_window_default } }, g_qvoid },
			{ t, "window", Address(), mud_Shell_window, { { "name", type<stl::string>(),  }, { "size", type<mud::uvec2>(),  }, { "fullscreen", type<bool>(), Param::Default, &window_0_fullscreen_default } }, { &type<mud::ShellWindow>(), QualType::None } },
			{ t, "begin_frame", Address(), mud_Shell_begin_frame, {}, { &type<bool>(), QualType::None } },
			{ t, "end_frame", Address(), mud_Shell_end_frame, {}, g_qvoid },
			{ t, "pump", Address(), mud_Shell_pump, {}, { &type<bool>(), QualType::None } },
			{ t, "main_window", Address(), mud_Shell_main_window, {}, { &type<mud::ShellWindow>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::ShellContext
	{
		Type& t = type<mud::ShellContext>();
		static Meta meta = { t, &namspc({ "mud" }), "ShellContext", sizeof(mud::ShellContext), TypeClass::Struct };
		// bases
		// defaults
		static mud::Widget* screen_default = nullptr;
		static mud::Dockbar* dockbar_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ShellContext__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ShellContext__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ShellContext, m_screen), type<mud::Widget>(), "screen", screen_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::ShellContext, m_dockbar), type<mud::Dockbar>(), "dockbar", dockbar_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ShellWindow
	{
		Type& t = type<mud::ShellWindow>();
		static Meta meta = { t, &namspc({ "mud" }), "ShellWindow", sizeof(mud::ShellWindow), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::GfxWindow>() };
		static size_t bases_offsets[] = { base_offset<mud::ShellWindow, mud::GfxWindow>() };
		// defaults
		static uint32_t index_default = 0;
		static mud::Ui* ui_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::ShellWindow, m_index), type<uint32_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(mud::ShellWindow, m_ui_window), type<mud::UiWindow>(), "ui_window", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::ShellWindow, m_ui), type<mud::Ui>(), "ui", ui_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	
	{
		Type& t = type<stl::vector<mud::Ref>>();
		static Alias alias = { &t, &namspc({ "mud" }), "Selection" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<mud::Selection>());
		m.m_types.push_back(&type<mud::Shell>());
		m.m_types.push_back(&type<mud::ShellContext>());
		m.m_types.push_back(&type<mud::ShellWindow>());
	}
}

namespace mud
{
	mud_frame::mud_frame()
		: Module("mud::frame", { &mud_gfx::m(), &mud_gfx_ui::m() })
	{
		// setup reflection meta data
		mud_frame_meta(*this);
	}
}

#ifdef MUD_FRAME_MODULE
extern "C"
Module& getModule()
{
	return mud_frame::m();
}
#endif

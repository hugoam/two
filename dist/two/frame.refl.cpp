#include <two/gfx.refl.h>
#include <two/frame.h>
#include <two/gfx.ui.refl.h>
#include <two/refl.h>
#include <two/infra.h>
#include <two/type.h>
#include <two/frame.refl.h>


module two.frame;


using namespace two;

void two_ShellContext__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ShellContext(  ); }
void two_ShellContext__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ShellContext((*static_cast<two::ShellContext*>(other))); }
void two_Shell__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Shell( *static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<bool*>(args[2]) ); }
void two_Shell_init(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Shell*>(object)).init(*static_cast<bool*>(args[0])); }
void two_Shell_window(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Shell*>(object)).window(*static_cast<stl::string*>(args[0]), *static_cast<two::uvec2*>(args[1]), *static_cast<bool*>(args[2])); }
void two_Shell_add_file(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Shell*>(object)).add_file(*static_cast<stl::string*>(args[0]), *static_cast<stl::span<uint8_t>*>(args[1])); }
void two_Shell_begin_frame(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Shell*>(object)).begin_frame(); }
void two_Shell_end_frame(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Shell*>(object)).end_frame(); }
void two_Shell_pump(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Shell*>(object)).pump(); }
void two_Shell_main_window(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Shell*>(object)).main_window(); }

namespace two
{
	void two_frame_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::ShellContext
	{
		Type& t = type<two::ShellContext>();
		static Meta meta = { t, &namspc({ "two" }), "ShellContext", sizeof(two::ShellContext), TypeClass::Struct };
		// bases
		// defaults
		static two::Widget* screen_default = nullptr;
		static two::Dockbar* dockbar_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_ShellContext__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ShellContext__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ShellContext, m_screen), type<two::Widget>(), "screen", screen_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::ShellContext, m_dockbar), type<two::Dockbar>(), "dockbar", dockbar_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ShellWindow
	{
		Type& t = type<two::ShellWindow>();
		static Meta meta = { t, &namspc({ "two" }), "ShellWindow", sizeof(two::ShellWindow), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::GfxWindow>() };
		static size_t bases_offsets[] = { base_offset<two::ShellWindow, two::GfxWindow>() };
		// defaults
		static uint32_t index_default = 0;
		static two::Ui* ui_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::ShellWindow, m_index), type<uint32_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(two::ShellWindow, m_ui_window), type<two::UiWindow>(), "ui_window", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ShellWindow, m_ui), type<two::Ui>(), "ui", ui_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// two::Shell
	{
		Type& t = type<two::Shell>();
		static Meta meta = { t, &namspc({ "two" }), "Shell", sizeof(two::Shell), TypeClass::Object };
		// bases
		// defaults
		static stl::string construct_0_exec_path_default = "";
		static bool construct_0_window_default = true;
		static bool init_0_window_default = true;
		static bool window_0_fullscreen_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Shell__construct_0, { { "resource_path", type<stl::string>(),  }, { "exec_path", type<stl::string>(), Param::Default, &construct_0_exec_path_default }, { "window", type<bool>(), Param::Default, &construct_0_window_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Shell, m_exec_path), type<stl::string>(), "exec_path", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Shell, m_resource_path), type<stl::string>(), "resource_path", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Shell, m_job_system), type<two::JobSystem>(), "job_system", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Shell, m_gfx), type<two::GfxSystem>(), "gfx", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Shell, m_editor), type<two::ShellContext>(), "editor", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "init", Address(), two_Shell_init, { { "window", type<bool>(), Param::Default, &init_0_window_default } }, g_qvoid },
			{ t, "window", Address(), two_Shell_window, { { "name", type<stl::string>(),  }, { "size", type<two::uvec2>(),  }, { "fullscreen", type<bool>(), Param::Default, &window_0_fullscreen_default } }, { &type<two::ShellWindow>(), QualType::None } },
			{ t, "add_file", Address(), two_Shell_add_file, { { "path", type<stl::string>(),  }, { "data", type<stl::span<uint8_t>>(),  } }, g_qvoid },
			{ t, "begin_frame", Address(), two_Shell_begin_frame, {}, { &type<bool>(), QualType::None } },
			{ t, "end_frame", Address(), two_Shell_end_frame, {}, g_qvoid },
			{ t, "pump", Address(), two_Shell_pump, {}, { &type<bool>(), QualType::None } },
			{ t, "main_window", Address(), two_Shell_main_window, {}, { &type<two::ShellWindow>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<two::ShellContext>());
		m.m_types.push_back(&type<two::ShellWindow>());
		m.m_types.push_back(&type<two::Shell>());
	}
}

namespace two
{
	two_frame::two_frame()
		: Module("two::frame", { &two_gfx::m(), &two_gfx_ui::m() })
	{
		// setup reflection meta data
		two_frame_meta(*this);
	}
}

#ifdef TWO_FRAME_MODULE
extern "C"
Module& getModule()
{
	return two_frame::m();
}
#endif

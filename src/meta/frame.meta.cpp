#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.frame;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.ui.meta.h>
#include <meta/frame.meta.h>
#include <meta/frame.conv.h>
#endif

#include <frame/Api.h>

using namespace mud;

void mud_Shell__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Shell( *static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]) ); }
void mud_Shell_begin_frame(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Shell*>(object)).begin_frame(); }
void mud_Shell_end_frame(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Shell*>(object)).end_frame(); }
void mud_Shell_pump(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Shell*>(object)).pump(); }
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
		static mud::Ui* ui_default = nullptr;
		static stl::string construct_0_exec_path_default = "";
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Shell__construct_0, { { "resource_path", type<stl::string>(),  }, { "exec_path", type<stl::string>(), Param::Default, &construct_0_exec_path_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Shell, m_exec_path), type<stl::string>(), "exec_path", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shell, m_resource_path), type<stl::string>(), "resource_path", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shell, m_job_system), type<mud::JobSystem>(), "job_system", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Shell, m_gfx), type<mud::GfxSystem>(), "gfx", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Shell, m_editor), type<mud::ShellContext>(), "editor", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shell, m_ui), type<mud::Ui>(), "ui", ui_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "begin_frame", Address(), mud_Shell_begin_frame, {}, { &type<bool>(), QualType::None } },
			{ t, "end_frame", Address(), mud_Shell_end_frame, {}, { &type<bool>(), QualType::None } },
			{ t, "pump", Address(), mud_Shell_pump, {}, { &type<bool>(), QualType::None } }
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
	
	{
		Type& t = type<stl::vector<mud::Ref>>();
		static Alias alias = { &t, &namspc({ "mud" }), "Selection" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<mud::Selection>());
		m.m_types.push_back(&type<mud::Shell>());
		m.m_types.push_back(&type<mud::ShellContext>());
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

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
#endif


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
		// defaults
		static mud::Ui* ui_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Shell>(ref)) mud::Shell( val<string>(args[0]), val<string>(args[1]) ); }, { { "resource_path", var(string()) }, { "exec_path", var(string("")), Param::Default } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Shell::m_exec_path), type<string>(), "exec_path", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shell::m_resource_path), type<string>(), "resource_path", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shell::m_job_system), type<mud::JobSystem>(), "job_system", Ref(), Member::NonMutable, nullptr },
				{ t, member_address(&mud::Shell::m_gfx_system), type<mud::GfxSystem>(), "gfx_system", Ref(), Member::NonMutable, nullptr },
				{ t, member_address(&mud::Shell::m_editor), type<mud::ShellContext>(), "editor", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Shell::m_ui), type<mud::Ui>(), "ui", Ref(ui_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
				{ t, "pump", member_address<bool(mud::Shell::*)()>(&mud::Shell::pump), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Shell>(object).pump(); }, {}, var(bool()) }
			},
			// static members
			{
			}
		};
		init_pool<mud::Shell>();
		meta_class<mud::Shell>();
	}
	// mud::ShellContext
	{
		Type& t = type<mud::ShellContext>();
		static Meta meta = { t, &namspc({ "mud" }), "ShellContext", sizeof(mud::ShellContext), TypeClass::Struct };
		// defaults
		static mud::Widget* screen_default = nullptr;
		static mud::Dockbar* dockbar_default = nullptr;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ShellContext>(ref)) mud::ShellContext(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ShellContext>(ref)) mud::ShellContext(val<mud::ShellContext>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ShellContext::m_screen), type<mud::Widget>(), "screen", Ref(screen_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::ShellContext::m_dockbar), type<mud::Dockbar>(), "dockbar", Ref(dockbar_default), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ShellContext>();
	}
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

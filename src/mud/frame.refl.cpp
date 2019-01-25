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
		static Meta meta = { type<mud::Shell>(), &namspc({ "mud" }), "Shell", sizeof(mud::Shell), TypeClass::Object };
		static Class cls = { type<mud::Shell>(),
			// bases
			{  },
			{  },
			// constructors
			{
				{ type<mud::Shell>(), [](Ref ref, array<Var> args) { new(&val<mud::Shell>(ref)) mud::Shell( val<string>(args[0]), val<string>(args[1]) ); }, { { "resource_path", var(string()) }, { "exec_path", var(string("")), Param::Default } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ type<mud::Shell>(), member_address(&mud::Shell::m_exec_path), type<string>(), "exec_path", var(string()), Member::Value, nullptr },
				{ type<mud::Shell>(), member_address(&mud::Shell::m_resource_path), type<string>(), "resource_path", var(string()), Member::Value, nullptr },
				{ type<mud::Shell>(), member_address(&mud::Shell::m_job_system), type<mud::JobSystem>(), "job_system", Ref(type<mud::JobSystem>()), Member::NonMutable, nullptr },
				{ type<mud::Shell>(), member_address(&mud::Shell::m_gfx_system), type<mud::GfxSystem>(), "gfx_system", Ref(type<mud::GfxSystem>()), Member::NonMutable, nullptr },
				{ type<mud::Shell>(), member_address(&mud::Shell::m_editor), type<mud::ShellContext>(), "editor", var(mud::ShellContext()), Member::Value, nullptr },
				{ type<mud::Shell>(), member_address(&mud::Shell::m_ui), type<mud::Ui>(), "ui", Ref(type<mud::Ui>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
				{ type<mud::Shell>(), "pump", member_address<bool(mud::Shell::*)()>(&mud::Shell::pump), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Shell>(object).pump(); }, {}, var(bool()) }
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
		static Meta meta = { type<mud::ShellContext>(), &namspc({ "mud" }), "ShellContext", sizeof(mud::ShellContext), TypeClass::Struct };
		static Class cls = { type<mud::ShellContext>(),
			// bases
			{  },
			{  },
			// constructors
			{
				{ type<mud::ShellContext>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ShellContext>(ref)) mud::ShellContext(  ); }, {} }
			},
			// copy constructor
			{
				{ type<mud::ShellContext>(), [](Ref ref, Ref other) { new(&val<mud::ShellContext>(ref)) mud::ShellContext(val<mud::ShellContext>(other)); } }
			},
			// members
			{
				{ type<mud::ShellContext>(), member_address(&mud::ShellContext::m_screen), type<mud::Widget>(), "screen", Ref(type<mud::Widget>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ type<mud::ShellContext>(), member_address(&mud::ShellContext::m_dockbar), type<mud::Dockbar>(), "dockbar", Ref(type<mud::Dockbar>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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

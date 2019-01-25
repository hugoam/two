#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc-gfx;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/wfc/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-ui/Module.h>
#include <meta/wfc-gfx/Module.h>
#include <meta/wfc-gfx/Convert.h>
#endif

#include <wfc-gfx/Api.h>

namespace mud
{
	void mud_wfc_gfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::TileModel
	{
		Type& t = type<mud::TileModel>();
		static Meta meta = { t, &namspc({ "mud" }), "TileModel", sizeof(mud::TileModel), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::TileModel>(ref)) mud::TileModel(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TileModel>(ref)) mud::TileModel(val<mud::TileModel>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::TileModel>();
	}
	// mud::WfcBlock
	{
		Type& t = type<mud::WfcBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "WfcBlock", sizeof(mud::WfcBlock), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::WfcBlock>(ref)) mud::WfcBlock(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::WfcBlock>(ref)) mud::WfcBlock( val<mud::vec3>(args[0]), val<mud::uvec3>(args[1]), val<mud::vec3>(args[2]), val<mud::WaveTileset>(args[3]), val<bool>(args[4]) ); }, { { "position", var(mud::vec3()) }, { "size", var(mud::uvec3()) }, { "scale", var(mud::vec3()) }, { "tileset", var(mud::WaveTileset()) }, { "auto_solve", var(bool(false)), Param::Default } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::WfcBlock::m_position), type<mud::vec3>(), "position", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::WfcBlock::m_size), type<mud::uvec3>(), "size", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::WfcBlock::m_scale), type<mud::vec3>(), "scale", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::WfcBlock::m_aabb), type<mud::Aabb>(), "aabb", Ref(), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "reset", member_address<void(mud::WfcBlock::*)()>(&mud::WfcBlock::reset), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::WfcBlock>(object).reset(); }, {}, Var() },
				{ t, "observe", member_address<void(mud::WfcBlock::*)()>(&mud::WfcBlock::observe), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::WfcBlock>(object).observe(); }, {}, Var() },
				{ t, "propagate", member_address<void(mud::WfcBlock::*)()>(&mud::WfcBlock::propagate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args); val<mud::WfcBlock>(object).propagate(); }, {}, Var() },
				{ t, "solve", member_address<void(mud::WfcBlock::*)(size_t)>(&mud::WfcBlock::solve), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::WfcBlock>(object).solve(val<size_t>(args[0])); }, { { "limit", var(size_t(0)), Param::Default } }, Var() },
				{ t, "update", member_address<void(mud::WfcBlock::*)(mud::Wave&)>(&mud::WfcBlock::update), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::WfcBlock>(object).update(val<mud::Wave>(args[0])); }, { { "wave", var(mud::Wave()) } }, Var() }
			},
			// static members
			{
			}
		};
		init_pool<mud::WfcBlock>();
		meta_class<mud::WfcBlock>();
	}
		m.m_types.push_back(&type<mud::TileModel>());
		m.m_types.push_back(&type<mud::WfcBlock>());
	}
}

namespace mud
{
	mud_wfc_gfx::mud_wfc_gfx()
		: Module("mud::wfc-gfx", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_wfc::m(), &mud_ctx::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_ui::m() })
	{
		// setup reflection meta data
		mud_wfc_gfx_meta(*this);
	}
}

#ifdef MUD_WFC_GFX_MODULE
extern "C"
Module& getModule()
{
		return mud_wfc_gfx::m();
}
#endif

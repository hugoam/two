#include <mud/tree.refl.h>
#include <mud/wfc.refl.h>
#include <mud/srlz.refl.h>
#include <mud/uio.refl.h>
#include <mud/geom.refl.h>
#include <mud/ui.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/ctx.refl.h>
#include <mud/gfx.ui.refl.h>
#include <mud/wfc.gfx.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/wfc.gfx.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.wfc-gfx;
#else
#endif


using namespace mud;

void mud_TileModel__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::TileModel*>(ref))) mud::TileModel(  ); }
void mud_TileModel__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::TileModel*>(ref))) mud::TileModel((*static_cast<mud::TileModel*>(other))); }
void mud_WfcBlock__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::WfcBlock*>(ref))) mud::WfcBlock(  ); }
void mud_WfcBlock__construct_1(void* ref, array<void*> args) { new(&(*static_cast<mud::WfcBlock*>(ref))) mud::WfcBlock( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::uvec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::WaveTileset*>(args[3]), *static_cast<bool*>(args[4]) ); }
void mud_WfcBlock_reset(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::WfcBlock*>(object)).reset(); }
void mud_WfcBlock_observe(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::WfcBlock*>(object)).observe(); }
void mud_WfcBlock_propagate(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::WfcBlock*>(object)).propagate(); }
void mud_WfcBlock_solve(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::WfcBlock*>(object)).solve(*static_cast<size_t*>(args[0])); }
void mud_WfcBlock_update(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::WfcBlock*>(object)).update(*static_cast<mud::Wave*>(args[0])); }

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
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TileModel__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TileModel__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::WfcBlock
	{
		Type& t = type<mud::WfcBlock>();
		static Meta meta = { t, &namspc({ "mud" }), "WfcBlock", sizeof(mud::WfcBlock), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_WfcBlock__construct_0, {} },
			{ t, mud_WfcBlock__construct_1, { { "position", type<mud::vec3>(),  }, { "size", type<mud::uvec3>(),  }, { "scale", type<mud::vec3>(),  }, { "tileset", type<mud::WaveTileset>(),  }, { "auto_solve", type<bool>(), Param::Default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::WfcBlock, m_position), type<mud::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::WfcBlock, m_size), type<mud::uvec3>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::WfcBlock, m_scale), type<mud::vec3>(), "scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::WfcBlock, m_aabb), type<mud::Aabb>(), "aabb", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "reset", Address(), mud_WfcBlock_reset, {}, g_qvoid },
			{ t, "observe", Address(), mud_WfcBlock_observe, {}, g_qvoid },
			{ t, "propagate", Address(), mud_WfcBlock_propagate, {}, g_qvoid },
			{ t, "solve", Address(), mud_WfcBlock_solve, { { "limit", type<size_t>(), Param::Default } }, g_qvoid },
			{ t, "update", Address(), mud_WfcBlock_update, { { "wave", type<mud::Wave>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
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

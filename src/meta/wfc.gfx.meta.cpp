module;
#include <infra/Cpp20.h>
module two.wfc.gfx.meta;

using namespace two;

void two_TileModel__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::TileModel(  ); }
void two_TileModel__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TileModel((*static_cast<two::TileModel*>(other))); }
void two_WfcBlock__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::WfcBlock(  ); }
void two_WfcBlock__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::WfcBlock( *static_cast<two::vec3*>(args[0]), *static_cast<two::uvec3*>(args[1]), *static_cast<two::vec3*>(args[2]), *static_cast<two::WaveTileset*>(args[3]), *static_cast<bool*>(args[4]) ); }
void two_WfcBlock_reset(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::WfcBlock*>(object)).reset(); }
void two_WfcBlock_observe(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::WfcBlock*>(object)).observe(); }
void two_WfcBlock_propagate(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::WfcBlock*>(object)).propagate(); }
void two_WfcBlock_solve(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::WfcBlock*>(object)).solve(*static_cast<size_t*>(args[0])); }
void two_WfcBlock_update(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::WfcBlock*>(object)).update(*static_cast<two::Wave*>(args[0])); }

namespace two
{
	void two_wfc_gfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::TileModel
	{
		Type& t = type<two::TileModel>();
		static Meta meta = { t, &namspc({ "two" }), "TileModel", sizeof(two::TileModel), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TileModel__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TileModel__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::WfcBlock
	{
		Type& t = type<two::WfcBlock>();
		static Meta meta = { t, &namspc({ "two" }), "WfcBlock", sizeof(two::WfcBlock), TypeClass::Object };
		// bases
		// defaults
		static bool construct_1_auto_solve_default = false;
		static size_t solve_0_limit_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, two_WfcBlock__construct_0, {} },
			{ t, two_WfcBlock__construct_1, { { "position", type<two::vec3>(),  }, { "size", type<two::uvec3>(),  }, { "scale", type<two::vec3>(),  }, { "tileset", type<two::WaveTileset>(),  }, { "auto_solve", type<bool>(), Param::Default, &construct_1_auto_solve_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::WfcBlock, m_position), type<two::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::WfcBlock, m_size), type<two::uvec3>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::WfcBlock, m_scale), type<two::vec3>(), "scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::WfcBlock, m_aabb), type<two::Aabb>(), "aabb", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "reset", Address(), two_WfcBlock_reset, {}, g_qvoid },
			{ t, "observe", Address(), two_WfcBlock_observe, {}, g_qvoid },
			{ t, "propagate", Address(), two_WfcBlock_propagate, {}, g_qvoid },
			{ t, "solve", Address(), two_WfcBlock_solve, { { "limit", type<size_t>(), Param::Default, &solve_0_limit_default } }, g_qvoid },
			{ t, "update", Address(), two_WfcBlock_update, { { "wave", type<two::Wave>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<two::TileModel>());
		m.m_types.push_back(&type<two::WfcBlock>());
	}
}

namespace two
{
	two_wfc_gfx::two_wfc_gfx()
		: Module("two::wfc-gfx", { &two_infra::m(), &two_tree::m(), &two_type::m(), &two_srlz::m(), &two_math::m(), &two_geom::m(), &two_wfc::m(), &two_ctx::m(), &two_ui::m(), &two_uio::m(), &two_gfx::m(), &two_gfx_ui::m() })
	{
		// setup reflection meta data
		two_wfc_gfx_meta(*this);
	}
}

#ifdef TWO_WFC_GFX_MODULE
extern "C"
Module& getModule()
{
	return two_wfc_gfx::m();
}
#endif

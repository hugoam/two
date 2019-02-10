#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/srlz.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/wfc.meta.h>
#include <meta/wfc.conv.h>
#endif

#include <wfc/Api.h>

using namespace mud;

void mud_Result__to_string(void* val, string& str) { str = g_enu[type<mud::Result>().m_id]->name(uint32_t((*static_cast<mud::Result*>(val)))); }
void mud_Result__to_value(const string& str, void* val) { (*static_cast<mud::Result*>(val)) = mud::Result(g_enu[type<mud::Result>().m_id]->value(str.c_str())); }
void mud_Tile__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Tile(  ); }
void mud_Tile__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Tile((*static_cast<mud::Tile*>(other))); }
void mud_Tileset__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Tileset(  ); }
void mud_Tileset__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Tileset((*static_cast<mud::Tileset*>(other))); }
void mud_Wave__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Wave(  ); }
void mud_Wave__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Wave((*static_cast<mud::Wave*>(other))); }
void mud_Wave_solve(void* object, span<void*> args, void*& result) { (*static_cast<mud::Result*>(result)) = (*static_cast<mud::Wave*>(object)).solve(*static_cast<size_t*>(args[0])); }
void mud_TileWave__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::TileWave( *static_cast<mud::WaveTileset*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<uint16_t*>(args[2]), *static_cast<uint16_t*>(args[3]), *static_cast<bool*>(args[4]) ); }
void mud_TileWave__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TileWave((*static_cast<mud::TileWave*>(other))); }
void mud_WaveTileset__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::WaveTileset(  ); }
void mud_WaveTileset__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::WaveTileset((*static_cast<mud::WaveTileset*>(other))); }
void mud_parse_json_tileset_0(span<void*> args, void*& result) { UNUSED(result);  mud::parse_json_tileset(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::Tileset*>(args[2])); }
void mud_parse_json_wave_tileset_1(span<void*> args, void*& result) { UNUSED(result);  mud::parse_json_wave_tileset(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::WaveTileset*>(args[2])); }

namespace mud
{
	void mud_wfc_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Result>();
		static Meta meta = { t, &namspc({ "mud" }), "Result", sizeof(mud::Result), TypeClass::Enum };
		static cstring ids[] = { "kSuccess", "kFail", "kUnfinished" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Result vars[] = { mud::kSuccess, mud::kFail, mud::kUnfinished};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Result__to_string,
		                           mud_Result__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::Tile
	{
		Type& t = type<mud::Tile>();
		static Meta meta = { t, &namspc({ "mud" }), "Tile", sizeof(mud::Tile), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Tile__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Tile__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Tile, m_index), type<uint32_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tile, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tile, m_symmetry), type<char>(), "symmetry", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tile, m_cardinality), type<int>(), "cardinality", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tile, m_profile), type<int>(), "profile", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Tileset
	{
		Type& t = type<mud::Tileset>();
		static Meta meta = { t, &namspc({ "mud" }), "Tileset", sizeof(mud::Tileset), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Tileset__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Tileset__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Tileset, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tileset, m_tile_size), type<mud::vec3>(), "tile_size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tileset, m_tile_scale), type<mud::vec3>(), "tile_scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Tileset, m_num_tiles), type<uint16_t>(), "nutiles", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Wave
	{
		Type& t = type<mud::Wave>();
		static Meta meta = { t, &namspc({ "mud" }), "Wave", sizeof(mud::Wave), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Wave__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Wave__copy_construct }
		};
		// members
		// methods
		static Method methods[] = {
			{ t, "solve", Address(), mud_Wave_solve, { { "limit", type<size_t>(),  } }, { &type<mud::Result>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, methods, {}, };
	}
	// mud::TileWave
	{
		Type& t = type<mud::TileWave>();
		static Meta meta = { t, &namspc({ "mud" }), "TileWave", sizeof(mud::TileWave), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Wave>() };
		static size_t bases_offsets[] = { base_offset<mud::TileWave, mud::Wave>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TileWave__construct_0, { { "tileset", type<mud::WaveTileset>(),  }, { "width", type<uint16_t>(),  }, { "height", type<uint16_t>(),  }, { "depth", type<uint16_t>(),  }, { "periodic", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TileWave__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::WaveTileset
	{
		Type& t = type<mud::WaveTileset>();
		static Meta meta = { t, &namspc({ "mud" }), "WaveTileset", sizeof(mud::WaveTileset), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Tileset>() };
		static size_t bases_offsets[] = { base_offset<mud::WaveTileset, mud::Tileset>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_WaveTileset__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_WaveTileset__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	
	{
		Type& t = type<uchar>();
		static Alias alias = { &t, &namspc({ "mud" }), "ubool" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<uchar>();
		static Alias alias = { &t, &namspc({ "mud" }), "ColorIndex" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<ullong>();
		static Alias alias = { &t, &namspc({ "mud" }), "PatternHash" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<ushort>();
		static Alias alias = { &t, &namspc({ "mud" }), "PatternIndex" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<mud::ColorIndex>());
		m.m_types.push_back(&type<mud::PatternHash>());
		m.m_types.push_back(&type<mud::PatternIndex>());
		m.m_types.push_back(&type<mud::Result>());
		m.m_types.push_back(&type<mud::Tile>());
		m.m_types.push_back(&type<mud::Tileset>());
		m.m_types.push_back(&type<mud::Wave>());
		m.m_types.push_back(&type<mud::ubool>());
		m.m_types.push_back(&type<mud::TileWave>());
		m.m_types.push_back(&type<mud::WaveTileset>());
		{
			static Function f = { &namspc({ "mud" }), "parse_json_tileset", nullptr, mud_parse_json_tileset_0, { { "path", type<stl::string>(),  }, { "subset", type<stl::string>(),  }, { "outputTileset", type<mud::Tileset>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "parse_json_wave_tileset", nullptr, mud_parse_json_wave_tileset_1, { { "path", type<stl::string>(),  }, { "subset", type<stl::string>(),  }, { "outputTileset", type<mud::WaveTileset>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_wfc::mud_wfc()
		: Module("mud::wfc", { &mud_infra::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m() })
	{
		// setup reflection meta data
		mud_wfc_meta(*this);
	}
}

#ifdef MUD_WFC_MODULE
extern "C"
Module& getModule()
{
		return mud_wfc::m();
}
#endif

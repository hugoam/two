module;
#include <infra/Cpp20.h>
module two.wfc.meta;

using namespace two;

namespace two { using stl::string; }

void two_Result__to_string(void* val, string& str) { str = g_enu[type<two::Result>().m_id]->name(uint32_t((*static_cast<two::Result*>(val)))); }
void two_Result__to_value(const string& str, void* val) { (*static_cast<two::Result*>(val)) = two::Result(g_enu[type<two::Result>().m_id]->value(str.c_str())); }
void two_Tile__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Tile(  ); }
void two_Tile__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Tile((*static_cast<two::Tile*>(other))); }
void two_Tileset__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Tileset(  ); }
void two_Tileset__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Tileset((*static_cast<two::Tileset*>(other))); }
void two_Wave__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Wave(  ); }
void two_Wave__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Wave((*static_cast<two::Wave*>(other))); }
void two_Wave_solve(void* object, span<void*> args, void*& result) { (*static_cast<two::Result*>(result)) = (*static_cast<two::Wave*>(object)).solve(*static_cast<size_t*>(args[0])); }
void two_WaveTileset__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::WaveTileset(  ); }
void two_WaveTileset__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::WaveTileset((*static_cast<two::WaveTileset*>(other))); }
void two_TileWave__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::TileWave( *static_cast<two::WaveTileset*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<uint16_t*>(args[2]), *static_cast<uint16_t*>(args[3]), *static_cast<bool*>(args[4]) ); }
void two_TileWave__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TileWave((*static_cast<two::TileWave*>(other))); }
void two_parse_json_tileset_0(span<void*> args, void*& result) { UNUSED(result);  two::parse_json_tileset(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::Tileset*>(args[2])); }
void two_parse_json_wave_tileset_1(span<void*> args, void*& result) { UNUSED(result);  two::parse_json_wave_tileset(*static_cast<stl::string*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::WaveTileset*>(args[2])); }

namespace two
{
	void two_wfc_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::Result>();
		static Meta meta = { t, &namspc({ "two" }), "Result", sizeof(two::Result), TypeClass::Enum };
		static cstring ids[] = { "kSuccess", "kFail", "kUnfinished" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Result vars[] = { two::kSuccess, two::kFail, two::kUnfinished};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Result__to_string,
		                           two_Result__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::Tile
	{
		Type& t = type<two::Tile>();
		static Meta meta = { t, &namspc({ "two" }), "Tile", sizeof(two::Tile), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Tile__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Tile__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Tile, m_index), type<uint32_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tile, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tile, m_symmetry), type<char>(), "symmetry", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tile, m_cardinality), type<int>(), "cardinality", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tile, m_profile), type<int>(), "profile", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Tileset
	{
		Type& t = type<two::Tileset>();
		static Meta meta = { t, &namspc({ "two" }), "Tileset", sizeof(two::Tileset), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Tileset__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Tileset__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Tileset, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tileset, m_tile_size), type<two::vec3>(), "tile_size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tileset, m_tile_scale), type<two::vec3>(), "tile_scale", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Tileset, m_num_tiles), type<uint16_t>(), "nutiles", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Wave
	{
		Type& t = type<two::Wave>();
		static Meta meta = { t, &namspc({ "two" }), "Wave", sizeof(two::Wave), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Wave__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Wave__copy_construct }
		};
		// members
		// methods
		static Method methods[] = {
			{ t, "solve", Address(), two_Wave_solve, { { "limit", type<size_t>(),  } }, { &type<two::Result>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, methods, {}, };
	}
	// two::WaveTileset
	{
		Type& t = type<two::WaveTileset>();
		static Meta meta = { t, &namspc({ "two" }), "WaveTileset", sizeof(two::WaveTileset), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Tileset>() };
		static size_t bases_offsets[] = { base_offset<two::WaveTileset, two::Tileset>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_WaveTileset__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_WaveTileset__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::TileWave
	{
		Type& t = type<two::TileWave>();
		static Meta meta = { t, &namspc({ "two" }), "TileWave", sizeof(two::TileWave), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Wave>() };
		static size_t bases_offsets[] = { base_offset<two::TileWave, two::Wave>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TileWave__construct_0, { { "tileset", type<two::WaveTileset>(),  }, { "width", type<uint16_t>(),  }, { "height", type<uint16_t>(),  }, { "depth", type<uint16_t>(),  }, { "periodic", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TileWave__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	
	{
		Type& t = type<uchar>();
		static Alias alias = { &t, &namspc({ "two" }), "ubool" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<uchar>();
		static Alias alias = { &t, &namspc({ "two" }), "ColorIndex" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<ullong>();
		static Alias alias = { &t, &namspc({ "two" }), "PatternHash" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<ushort>();
		static Alias alias = { &t, &namspc({ "two" }), "PatternIndex" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<two::ubool>());
		m.m_types.push_back(&type<two::Result>());
		m.m_types.push_back(&type<two::Tile>());
		m.m_types.push_back(&type<two::Tileset>());
		m.m_types.push_back(&type<two::Wave>());
		m.m_types.push_back(&type<two::WaveTileset>());
		m.m_types.push_back(&type<two::TileWave>());
		m.m_types.push_back(&type<two::ColorIndex>());
		m.m_types.push_back(&type<two::PatternHash>());
		m.m_types.push_back(&type<two::PatternIndex>());
		{
			static Function f = { &namspc({ "two" }), "parse_json_tileset", funcptr<void(*)(const stl::string&, const stl::string&, two::Tileset&)>(two::parse_json_tileset), two_parse_json_tileset_0, { { "path", type<stl::string>(),  }, { "subset", type<stl::string>(),  }, { "outputTileset", type<two::Tileset>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "parse_json_wave_tileset", funcptr<void(*)(const stl::string&, const stl::string&, two::WaveTileset&)>(two::parse_json_wave_tileset), two_parse_json_wave_tileset_1, { { "path", type<stl::string>(),  }, { "subset", type<stl::string>(),  }, { "outputTileset", type<two::WaveTileset>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_wfc::two_wfc()
		: Module("two::wfc", { &two_infra::m(), &two_type::m(), &two_srlz::m(), &two_math::m(), &two_geom::m() })
	{
		// setup reflection meta data
		two_wfc_meta(*this);
	}
}

#ifdef TWO_WFC_MODULE
extern "C"
Module& getModule()
{
	return two_wfc::m();
}
#endif

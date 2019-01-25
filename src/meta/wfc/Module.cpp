#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/wfc/Module.h>
#include <meta/wfc/Convert.h>
#endif

#include <wfc/Api.h>

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
		meta_enum<mud::Result>();
	}
	
	// Sequences
	
	// mud::Tile
	{
		Type& t = type<mud::Tile>();
		static Meta meta = { t, &namspc({ "mud" }), "Tile", sizeof(mud::Tile), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Tile>(ref)) mud::Tile(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Tile>(ref)) mud::Tile(val<mud::Tile>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Tile::m_index), type<uint32_t>(), "index", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tile::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tile::m_symmetry), type<char>(), "symmetry", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tile::m_cardinality), type<int>(), "cardinality", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tile::m_profile), type<int>(), "profile", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Tile>();
	}
	// mud::Tileset
	{
		Type& t = type<mud::Tileset>();
		static Meta meta = { t, &namspc({ "mud" }), "Tileset", sizeof(mud::Tileset), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Tileset>(ref)) mud::Tileset(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Tileset>(ref)) mud::Tileset(val<mud::Tileset>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Tileset::m_name), type<string>(), "name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tileset::m_tile_size), type<mud::vec3>(), "tile_size", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tileset::m_tile_scale), type<mud::vec3>(), "tile_scale", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Tileset::m_num_tiles), type<uint16_t>(), "nutiles", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Tileset>();
	}
	// mud::Wave
	{
		Type& t = type<mud::Wave>();
		static Meta meta = { t, &namspc({ "mud" }), "Wave", sizeof(mud::Wave), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Wave>(ref)) mud::Wave(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Wave>(ref)) mud::Wave(val<mud::Wave>(other)); } }
			},
			// members
			{
			},
			// methods
			{
				{ t, "solve", member_address<mud::Result(mud::Wave::*)(size_t)>(&mud::Wave::solve), [](Ref object, array<Var> args, Var& result) { val<mud::Result>(result) = val<mud::Wave>(object).solve(val<size_t>(args[0])); }, { { "limit", var(size_t()) } }, var(mud::Result()) }
			},
			// static members
			{
			}
		};
		meta_class<mud::Wave>();
	}
	// mud::TileWave
	{
		Type& t = type<mud::TileWave>();
		static Meta meta = { t, &namspc({ "mud" }), "TileWave", sizeof(mud::TileWave), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Wave>() },
			{ base_offset<mud::TileWave, mud::Wave>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::TileWave>(ref)) mud::TileWave( val<mud::WaveTileset>(args[0]), val<uint16_t>(args[1]), val<uint16_t>(args[2]), val<uint16_t>(args[3]), val<bool>(args[4]) ); }, { { "tileset", var(mud::WaveTileset()) }, { "width", var(uint16_t()) }, { "height", var(uint16_t()) }, { "depth", var(uint16_t()) }, { "periodic", var(bool()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TileWave>(ref)) mud::TileWave(val<mud::TileWave>(other)); } }
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
		meta_class<mud::TileWave>();
	}
	// mud::WaveTileset
	{
		Type& t = type<mud::WaveTileset>();
		static Meta meta = { t, &namspc({ "mud" }), "WaveTileset", sizeof(mud::WaveTileset), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Tileset>() },
			{ base_offset<mud::WaveTileset, mud::Tileset>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::WaveTileset>(ref)) mud::WaveTileset(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::WaveTileset>(ref)) mud::WaveTileset(val<mud::WaveTileset>(other)); } }
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
		meta_class<mud::WaveTileset>();
	}
		m.m_types.push_back(&type<mud::Result>());
		m.m_types.push_back(&type<mud::Tile>());
		m.m_types.push_back(&type<mud::Tileset>());
		m.m_types.push_back(&type<mud::Wave>());
		m.m_types.push_back(&type<mud::TileWave>());
		m.m_types.push_back(&type<mud::WaveTileset>());
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::parse_json_tileset(val<string>(args[0]), val<string>(args[1]), val<mud::Tileset>(args[2])); };
			vector<Param> params = { { "path", var(string()) }, { "subset", var(string()) }, { "outputTileset", var(mud::Tileset()), Param::Output } };
			static Function f = { &namspc({ "mud" }), "parse_json_tileset", funcptr<void(*)(const string&, const string&, mud::Tileset&)>(&mud::parse_json_tileset), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::parse_json_wave_tileset(val<string>(args[0]), val<string>(args[1]), val<mud::WaveTileset>(args[2])); };
			vector<Param> params = { { "path", var(string()) }, { "subset", var(string()) }, { "outputTileset", var(mud::WaveTileset()), Param::Output } };
			static Function f = { &namspc({ "mud" }), "parse_json_wave_tileset", funcptr<void(*)(const string&, const string&, mud::WaveTileset&)>(&mud::parse_json_wave_tileset), func, params, Var() };
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

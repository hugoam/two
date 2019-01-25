#pragma once

#include <mud/geom.h>
#include <mud/srlz.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>



#ifndef MUD_WFC_EXPORT
#define MUD_WFC_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum Result : unsigned int;
    
    
    struct Tile;
    struct Tileset;
    struct DoubleGenerator;
    struct Wave;
    struct WaveTileset;
    struct TileWave;
    struct VoxelTile;
    struct RGBA;
    struct PalettedImage;
    class Patternset;
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Result>();
    
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Tile>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Tileset>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::Wave>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::TileWave>();
    export_ template <> MUD_WFC_EXPORT Type& type<mud::WaveTileset>();
    
    export_ template struct MUD_WFC_EXPORT Typed<vector<mud::Tile*>>;
    export_ template struct MUD_WFC_EXPORT Typed<vector<mud::Tileset*>>;
    export_ template struct MUD_WFC_EXPORT Typed<vector<mud::Wave*>>;
    export_ template struct MUD_WFC_EXPORT Typed<vector<mud::TileWave*>>;
    export_ template struct MUD_WFC_EXPORT Typed<vector<mud::WaveTileset*>>;
}

#ifndef MUD_MODULES
#include <stl/function.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/set.h>
#include <stl/map.h>
#endif

namespace mud
{
	using ubool = uint8_t;

#define MUD_WFC_PROPAGATION_VEC

	export_ enum refl_ Result : unsigned int
	{
		kSuccess,
		kFail,
		kUnfinished,
	};

	export_ struct refl_ MUD_WFC_EXPORT Tile
	{
		Tile() {}
		Tile(uint32_t index, string name, char symmetry, int cardinality, int profile) : m_index(index), m_name(name), m_symmetry(symmetry), m_cardinality(cardinality), m_profile(profile) {}
		attr_ uint32_t m_index;
		attr_ string m_name;
		attr_ char m_symmetry;
		attr_ int m_cardinality;
		attr_ int m_profile;
		int m_flips[8];
		uint32_t m_edges[6];
	};

	export_ struct refl_ MUD_WFC_EXPORT Tileset
	{
		attr_ string m_name;
		attr_ vec3 m_tile_size;
		attr_ vec3 m_tile_scale;
		vector<Tile> m_tiles;
		vector<Tile> m_tiles_flip;
		vector<double> m_weights;
		attr_ uint16_t m_num_tiles;

		constr_ Tileset() {}
		Tile* tile(const string& name) { for(Tile& tile : m_tiles) if(tile.m_name == name) return &tile; return nullptr; }
		int flip(int tile, uint8_t flip) const { return m_tiles_flip[tile].m_flips[flip]; }
	};

	using RandomDouble = function<double()>;
	using ValidCoord = function<bool(int, int, int)>;
	using Propagator = function<void(Wave&)>;

	export_ struct refl_ MUD_WFC_EXPORT Wave
	{
		Wave();
		Wave(uint16_t states, uint16_t width, uint16_t height, uint16_t depth, bool periodic);

		uint16_t m_width, m_height, m_depth;
		bool m_periodic;

		vector<double> m_states;
		vector<string> m_pattern_names; // debug
		array3d<vector<ubool>> m_wave;
		vector<uvec3> m_changes;

		bool m_stabilized = true;
		bool m_solved = false;
		Result m_state = Result::kUnfinished;

		RandomDouble m_random_double;
		ValidCoord m_valid_coord;
		Propagator m_propagate;

		uint16_t m_failure_point[6];

		/*double m_logT;
		vector<double> m_log_weights;

		void setup()
		{
		m_logT = log(m_num_states);

		m_log_weights.resize(m_num_states);
		for(int t = 0; t < m_num_states; t++)
		m_log_weights[t] = log(m_state_weights[t]);

		}*/

		void clear();
		void set_tile(const uvec3& coord, uint16_t tile);
		Result find_lowest_entropy(uvec3& coord);
		Result observe();
		void propagate(size_t limit = 0);

		meth_ Result solve(size_t limit);
	};

	export_ struct refl_ MUD_WFC_EXPORT WaveTileset : public Tileset
	{
		array3d<ubool> m_propagator[6];

		constr_ WaveTileset();
		void initialize();
		void connect(int left, int right, bool horizontal);
		void finalize();

		array3d<ubool>& side(SignedAxis axis) { return m_propagator[size_t(axis)]; }
	};

	export_ struct refl_ MUD_WFC_EXPORT TileWave : public Wave
	{
		TileWave();
		constr_ TileWave(WaveTileset& tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic);
	};

	export_ MUD_WFC_EXPORT bool neighbour(Wave& wave, const uvec3& coord, SignedAxis d, uvec3& neighbour);
	export_ MUD_WFC_EXPORT uint16_t tile_at(Wave& wave, uint16_t x, uint16_t y, uint16_t z);

	export_ MUD_WFC_EXPORT void add_tile(Tileset& tileset, const set<string>& subset_tiles, const string& tile_name, char symmetry, float weight);
	export_ MUD_WFC_EXPORT void add_tile(Tileset& tileset, const string& tile_name, char symmetry, float weight);

	export_ MUD_WFC_EXPORT func_ void parse_json_tileset(const string& path, const string& subset, Tileset& outputTileset);
	export_ MUD_WFC_EXPORT func_ void parse_json_wave_tileset(const string& path, const string& subset, WaveTileset& outputTileset);

	struct VoxelTile
	{
		size_t m_pattern;
		uint8_t m_profile;
	};

	struct RGBA
	{
		uint8_t r, g, b, a;
	};
	static_assert(sizeof(RGBA) == 4, "");
	inline bool operator==(RGBA x, RGBA y) { return x.r == y.r && x.g == y.g && x.b == y.b && x.a == y.a; }

	using ColorIndex = uint8_t; // tile index or color index. If you have more than 255, don't.
	using ColorPalette = vector<RGBA>;
	using ColorPattern = vector<ColorIndex>;
	using PatternHash = uint64_t; // Another representation of a Pattern.
	using PatternPrevalence = map<PatternHash, size_t>;
	using PatternIndex = uint16_t;

	const auto kInvalidIndex = static_cast<size_t>(-1);
	const auto kInvalidHash = static_cast<PatternHash>(-1);

	const size_t MAX_COLORS = 1 << (sizeof(ColorIndex) * 8);

	using OverlapGraphics = array3d<vector<ColorIndex>>;

	struct PalettedImage
	{
		size_t                  width, height;
		vector<ColorIndex> data; // width * height
		ColorPalette            palette;

		ColorIndex at_wrapped(size_t x, size_t y) const
		{
			return data[width * (y % height) + (x % width)];
		}
	};

	class Patternset
	{
	public:
		Patternset(int n, const PatternPrevalence& hashed_patterns, const ColorPalette& palette, PatternHash foundation_pattern);

		int m_n;
		array3d<vector<vector<PatternIndex>>> m_propagator;
		vector<ColorPattern> m_patterns;
		vector<double> m_weights;
	};
}


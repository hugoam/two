#include <mud/srlz.h>
#include <mud/wfc.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.wfc;
#else
#include <stl/map.h>
#include <stl/algorithm.h>
#endif

#include <json11.hpp>
using json = json11::Json;


namespace mud
{
	PatternHash hash_from_pattern(const ColorPattern& pattern, size_t palette_size)
	{
		/*CHECK_LT_F(pow((double)palette_size, (double)pattern.size()),
				   pow(2.0, sizeof(PatternHash) * 8),
				   "Too large palette (it is %lu) or too large pattern size (it's %.0f)",
				   palette_size, sqrt(pattern.size()));*/
		PatternHash result = 0;
		size_t power = 1;
		for(size_t i = 0; i < pattern.size(); ++i)
		{
			result += pattern[pattern.size() - 1 - i] * power;
			power *= palette_size;
		}
		return result;
	}

	ColorPattern pattern_from_hash(const PatternHash hash, int n, size_t palette_size)
	{
		uint64_t residue = hash;
		size_t power = size_t(pow(palette_size, n * n));
		ColorPattern result(n * n);

		for(size_t i = 0; i < result.size(); ++i)
		{
			power /= palette_size;
			size_t count = 0;

			while(residue >= power)
			{
				residue -= power;
				count++;
			}

			result[i] = static_cast<ColorIndex>(count);
		}

		return result;
	}

	template <class Fun>
	ColorPattern make_pattern(size_t n, const Fun& fun)
	{
		ColorPattern result(n * n);
		for(size_t dy = 0; dy < n; ++dy)
			for(size_t dx = 0; dx < n; ++dx)
				result[dy * n + dx] = fun(dx, dy);
		return result;
	};

	Patternset::Patternset(int n, const PatternPrevalence& hashed_patterns, const ColorPalette& palette, PatternHash foundation_pattern)
		: m_propagator(hashed_patterns.size(), 2 * n - 1, 2 * n - 1, {})
	{
		UNUSED(foundation_pattern);
		m_n = n;
		
		for(const auto& it : hashed_patterns)
		{
			//if(it.first == foundation_pattern)
			//	m_foundation = m_patterns.size();

			m_patterns.push_back(pattern_from_hash(it.first, n, palette.size()));
			m_weights.push_back(double(it.second));
		}

		const auto agrees = [&](const ColorPattern& p1, const ColorPattern& p2, int dx, int dy)
		{
			int xmin = dx < 0 ? 0 : dx, xmax = dx < 0 ? dx + n : n;
			int ymin = dy < 0 ? 0 : dy, ymax = dy < 0 ? dy + n : n;
			for(int y = ymin; y < ymax; ++y)
				for(int x = xmin; x < xmax; ++x)
					if(p1[x + n * y] != p2[x - dx + n * (y - dy)])
						return false;
			return true;
		};

		size_t longest_propagator = 0;
		size_t sum_propagator = 0;

		for(uint16_t t = 0; t < hashed_patterns.size(); ++t)
			for(int x = 0; x < 2 * n - 1; ++x)
				for(int y = 0; y < 2 * n - 1; ++y)
				{
					vector<PatternIndex>& patterns = m_propagator.at(x, y)[t];
					for(uint16_t t2 = 0; t2 < hashed_patterns.size(); ++t2)
						if(agrees(m_patterns[t], m_patterns[t2], x - n + 1, y - n + 1))
							patterns.push_back(t2);

					patterns.shrink_to_fit();
					longest_propagator = max(longest_propagator, patterns.size());
					sum_propagator += patterns.size();
				}

		//LOG_F(INFO, "propagator length: mean/max/sum: %.1f, %lu, %lu",
		//    (double)sum_propagator / _propagator.size(), longest_propagator, sum_propagator);
	}

	bool on_boundary(int n, Wave& wave, int x, int y, int z)
	{
		return !wave.m_periodic && (x + n > wave.m_width || y + n > wave.m_height || z + n > wave.m_depth);
	};

	void propagate_overlapping(Patternset& tileset, Wave& wave)
	{
		int n = tileset.m_n;

		uvec3 changed = pop(wave.m_changes);
				
		for(int dx = -n + 1; dx < n; ++dx) for(int dy = -n + 1; dy < n; ++dy) for(int dz = -n + 1; dz < n; ++dz)
		{
			ivec3 coord = ivec3(changed.x + dx, changed.y + dy, changed.z + dz);

			int sx = coord.x;
			if(sx < 0) sx += wave.m_width;
			else if(sx >= wave.m_width) sx -= wave.m_width;

			int sy = coord.y;
			if(sy < 0) sy += wave.m_height;
			else if(sy >= wave.m_height) sy -= wave.m_height;

			int sz = coord.z;
			if(sz < 0) sz += wave.m_depth;
			else if(sz >= wave.m_depth) sz -= wave.m_depth;

			if(!wave.m_periodic && (sx + n > wave.m_width || sy + n > wave.m_height || sz + n > wave.m_depth))
				continue;
		
			for(size_t t2 = 0; t2 < wave.m_states.size(); ++t2)
			{
				if(!wave.m_wave.at(sx, sy, sz)[t2])
					continue;

				bool can_pattern_fit = false;

				const vector<PatternIndex>& prop = tileset.m_propagator.at(n - 1 - dx, n - 1 - dy, n - 1 - dz)[t2];
				for(const auto& t3 : prop) {
					if(wave.m_wave.at(changed.x, changed.y, changed.z)[t3]) {
						can_pattern_fit = true;
						break;
					}
				}

				if(!can_pattern_fit) {
					wave.m_wave.at(sx, sy, sz)[t2] = false;
					wave.m_changes.push_back(uvec3(sx, sy, sz));
				}
			}
		}
	}

	PalettedImage load_paletted_image(RGBA* rgba, int width, int height, int comp)
	{
		const uint32_t num_pixels = width * height;

		// Fix issues with stbi_load:
		if(comp == 1)
		{
			// input was greyscale - set alpha:
			for(RGBA* pixel = rgba; pixel < rgba + num_pixels; ++rgba)
				pixel->a = pixel->r;
		}
		else
		{
			if(comp == 3)
			{
				for(RGBA* pixel = rgba; pixel < rgba + num_pixels; ++rgba)
					pixel->a = 255;
			}
			for(RGBA* pixel = rgba; pixel < rgba + num_pixels; ++rgba)
			{
				if(pixel->a == 0)
					*pixel = RGBA{ 0,0,0,0 };
			}
		}

		vector<RGBA> palette;
		vector<ColorIndex> data;

		for(size_t pixel_idx = 0; pixel_idx < num_pixels; ++pixel_idx)
		{
			const RGBA color = rgba[pixel_idx];
			const uint8_t color_idx = uint8_t(find(palette.begin(), palette.end(), color) - palette.begin());
			if(color_idx == palette.size())
			{
				palette.push_back(color);
			}
			data.push_back(color_idx);
		}

		return PalettedImage{
			static_cast<size_t>(width),
			static_cast<size_t>(height),
			data, palette
		};
	}

	PalettedImage load_paletted_image(const string& path)
	{
		UNUSED(path);
		int width = 0; int height = 0; int comp = 0;
		RGBA* rgba = nullptr; // reinterpret_cast<RGBA*>(stbi_load(path.c_str(), &width, &height, &comp, 4));
		PalettedImage image = load_paletted_image(rgba, width, height, comp);
		//stbi_image_free(rgba);
		return image;
	}

	// n = side of the pattern, e.g. 3.
	PatternPrevalence extract_patterns(const PalettedImage& sample, int n, bool periodic_in, size_t symmetry, PatternHash* out_lowest_pattern)
	{
		const auto pattern_from_sample = [&](size_t x, size_t y) {
			return make_pattern(n, [&](size_t dx, size_t dy) { return sample.at_wrapped(x + dx, y + dy); });
		};
		const auto rotate = [&](const ColorPattern& p) { return make_pattern(n, [&](size_t x, size_t y) { return p[n - 1 - y + x * n]; }); };
		const auto reflect = [&](const ColorPattern& p) { return make_pattern(n, [&](size_t x, size_t y) { return p[n - 1 - x + y * n]; }); };

		PatternPrevalence patterns;

		size_t h = sample.height - n + 1U;
		size_t w = sample.height - n + 1U;
		for(size_t y = 0; y < (periodic_in ? sample.height : h); ++y)
			for(size_t x = 0; y < (periodic_in ? sample.width : w); ++x)
			{
				ColorPattern ps[8];
				ps[0] = pattern_from_sample(x, y);
				ps[1] = reflect(ps[0]);
				ps[2] = rotate(ps[0]);
				ps[3] = reflect(ps[2]);
				ps[4] = rotate(ps[2]);
				ps[5] = reflect(ps[4]);
				ps[6] = rotate(ps[4]);
				ps[7] = reflect(ps[6]);

				for(size_t k = 0; k < symmetry; ++k)
				{
					auto hash = hash_from_pattern(ps[k], sample.palette.size());
					patterns[hash] += 1;
					if(out_lowest_pattern && y == sample.height - 1)
						*out_lowest_pattern = hash;
				}
			}

		return patterns;
	}

	void run_overlapping(const string& image, size_t symmetry, int n, uint16_t width, uint16_t height, uint16_t depth, bool periodic)
	{
		const PalettedImage sample_image = load_paletted_image(image);
		const PatternPrevalence hashed_patterns = extract_patterns(sample_image, n, false, symmetry, nullptr);
		Patternset tileset = { n, hashed_patterns, sample_image.palette, kInvalidHash };

		Wave wave(uint16_t(hashed_patterns.size()), width, height, depth, periodic); // resize each to model._num_patterns
		wave.m_propagate = [&](Wave& wave) { propagate_overlapping(tileset, wave); };
		wave.m_valid_coord = [&](int x, int y, int z) { return !on_boundary(n, wave, x, y, z); };
		//wave.m_states = tileset.m_weights;

		wave.solve(0);
	}

	using WfcImage = array3d<RGBA>;

	struct ProgressGif
	{
		const bool   kGifSeparatePalette = true;
		const size_t kGifInterval = 16; // Save an image every X iterations
		const int    kGifDelayCentiSec = 1;
		const int    kGifEndPauseCentiSec = 200;
		const size_t kUpscale = 4; // Upscale images before saving

		
		WfcImage upsample(const WfcImage& image)
		{
			WfcImage result(image.m_x * kUpscale, image.m_y * kUpscale, {});
			for(size_t y = 0; y < result.m_x; ++y)
				for(size_t x = 0; x < result.m_y; ++x)
					result.at(x, y) = image.at(x / kUpscale, y / kUpscale);
			return result;
		}
	};

	OverlapGraphics overlap_graphics(const Patternset& tileset, const Wave& wave)
	{
		OverlapGraphics result(wave.m_width, wave.m_height, {});
		for(uint16_t y = 0; y < wave.m_height; ++y)
			for(uint16_t x = 0; x < wave.m_width; ++x)
			{
				auto& tile_contributors = result.at(x, y);

				for(int dy = 0; dy < tileset.m_n; ++dy)
					for(int dx = 0; dx < tileset.m_n; ++dx)
					{
						int sx = x - dx;
						if(sx < 0) sx += wave.m_width;

						int sy = y - dy;
						if(sy < 0) sy += wave.m_height;

						if(!wave.m_valid_coord(sx, sy, 1))
							continue;

						for(size_t t = 0; t < wave.m_states.size(); ++t)
							if(wave.m_wave.at(sx, sy)[t])
								tile_contributors.push_back(tileset.m_patterns[t][dx + dy * tileset.m_n]);
					}
			}
		return result;
	}

	WfcImage overlap_image(const Patternset& tileset, const Wave& wave, const ColorPalette& palette)
	{
		OverlapGraphics graphics = overlap_graphics(tileset, wave);
		WfcImage result(graphics.m_y, graphics.m_x, 1); //{0, 0, 0, 0});

		for(size_t y = 0; y < graphics.m_x; ++y)
			for(size_t x = 0; x < graphics.m_y; ++x)
			{
				const auto& tile_contributors = graphics.at(x, y);
				if(tile_contributors.empty())
				{
					result.at(x, y) = { 0, 0, 0, 255 };
				}
				else if(tile_contributors.size() == 1)
				{
					result.at(x, y) = palette[tile_contributors[0]];
				}
				else
				{
					RGBA& colour = result.at(x, y);
					colour = { 0, 0, 0, 0 };
					for(const auto tile : tile_contributors)
					{
						colour.r += palette[tile].r;
						colour.g += palette[tile].g;
						colour.b += palette[tile].b;
						colour.a += palette[tile].a;
					}
					colour.r /= uint8_t(tile_contributors.size());
					colour.g /= uint8_t(tile_contributors.size());
					colour.b /= uint8_t(tile_contributors.size());
					colour.a /= uint8_t(tile_contributors.size());
				}
			}

		return result;
	}
}

#ifndef MUD_CPP_20
#include <string>
#endif

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <json11.hpp>
using json = json11::Json;

#endif


namespace mud
{
	void add_tile(Tileset& tileset, const vector<string>& subset_tiles, const string& tile_name, char symmetry, float weight)
	{
		if(!subset_tiles.empty() && !vector_has(subset_tiles, tile_name))
			return;

		using Transform = int(*)(int);
		Transform a; // rotates pattern counter-clockwise
		Transform b; // flips pattern vertically
		int cardinality = 1;

		if(symmetry == 'L') {
			cardinality = 4;
			a = [](int i) { return (i + 1) % 4; };
			b = [](int i) { return i % 2 == 0 ? i + 1 : i - 1; };
		}
		else if(symmetry == 'T') {
			cardinality = 4;
			a = [](int i) { return (i + 1) % 4; };
			b = [](int i) { return i % 2 == 0 ? i : 4 - i; };
		}
		else if(symmetry == 'I') {
			cardinality = 2;
			a = [](int i) { return 1 - i; };
			b = [](int i) { return i; };
		}
		else if(symmetry == '\\') {
			cardinality = 2;
			a = [](int i) { return 1 - i; };
			b = [](int i) { return 1 - i; };
		}
		else if(symmetry == 'X' || true) {
			cardinality = 1;
			a = [](int i) { return i; };
			b = [](int i) { return i; };
		}

		const uint32_t num_patterns = uint32_t(tileset.m_tiles_flip.size());

		tileset.m_tiles.push_back(Tile{ num_patterns, tile_name, symmetry, cardinality, 0 });

		for(int t = 0; t < cardinality; ++t)
		{
			Tile tile = { num_patterns + t, tile_name, symmetry, cardinality, t };

			tile.m_flips[0] = t;
			tile.m_flips[1] = a(t);
			tile.m_flips[2] = a(a(t));
			tile.m_flips[3] = a(a(a(t)));
			tile.m_flips[4] = b(t);
			tile.m_flips[5] = b(a(t));
			tile.m_flips[6] = b(a(a(t)));
			tile.m_flips[7] = b(a(a(a(t))));

			for(int s = 0; s < 8; ++s)
				tile.m_flips[s] += num_patterns;

			printf("DEBUG: tile %i = %s %i\n", int(tileset.m_tiles_flip.size()), tile_name.c_str(), t);
			tileset.m_tiles_flip.push_back(tile);
		}

		for(int t = 0; t < cardinality; ++t)
			tileset.m_weights.push_back(weight / float(cardinality));
	}

	void add_tile(Tileset& tileset, const string& tile_name, char symmetry, float weight)
	{
		add_tile(tileset, vector<string>(), tile_name, symmetry, weight);
	}

	void load_json_tileset(Tileset& tileset, const json& config, const string& subset)
	{
		tileset.m_name = config["name"].string_value().c_str();
		from_json(config["tile_size"], tileset.m_tile_size);
		from_json(config["tile_scale"], tileset.m_tile_scale);

		vector<string> subset_tiles;
		if(subset != "")
			for(const json& tile_name : config["subsets"][subset.c_str()].array_items())
				subset_tiles.push_back(tile_name.string_value().c_str());

		for(const json& json_tile : config["tiles"].array_items())
		{
			const string tile_name = json_tile["name"].string_value().c_str();
			char symmetry = json_tile["symmetry"].string_value()[0];
			float weight = float(json_tile["weight"].number_value());

			add_tile(tileset, subset_tiles, tile_name, symmetry, weight);
		}

		tileset.m_num_tiles = uint16_t(tileset.m_tiles_flip.size());
	}

	WaveTileset::WaveTileset()
		: Tileset()
	{}

	void WaveTileset::initialize()
	{
		for(size_t i = 0; i < 6; ++i)
			m_propagator[i].reset(m_num_tiles, m_num_tiles, m_num_tiles, false);
	}

	void WaveTileset::connect(int left, int right, bool horizontal)
	{
		if(horizontal)
		{
			side(SignedAxis::MinusX).at(right, left) = true;
			side(SignedAxis::MinusX).at(flip(right, 6), flip(left, 6)) = true;
			side(SignedAxis::MinusX).at(flip(left, 4), flip(right, 4)) = true;
			side(SignedAxis::MinusX).at(flip(left, 2), flip(right, 2)) = true;


			int down = flip(left, 1);
			int up = flip(right, 1);
			side(SignedAxis::PlusZ).at(up, down) = true;
			side(SignedAxis::PlusZ).at(flip(down, 6), flip(up, 6)) = true;
			side(SignedAxis::PlusZ).at(flip(up, 4), flip(down, 4)) = true;
			side(SignedAxis::PlusZ).at(flip(down, 2), flip(up, 2)) = true;
		}
		else
		{
			for(uint8_t g = 0; g < 8; g++)
				side(SignedAxis::PlusY).at(flip(left, g), flip(right, g)) = true;
		}
	}

	void WaveTileset::finalize()
	{
		for(int t1 = 0; t1 < m_num_tiles; ++t1)
			for(int t2 = 0; t2 < m_num_tiles; ++t2)
			{
				side(SignedAxis::PlusX).at(t1, t2)  = side(SignedAxis::MinusX).at(t2, t1);
				side(SignedAxis::MinusZ).at(t1, t2) = side(SignedAxis::PlusZ).at(t2, t1);
				side(SignedAxis::MinusY).at(t1, t2) = side(SignedAxis::PlusY).at(t2, t1);
			}
	}

	void load_rule_propagator(WaveTileset& tileset, const json& config)
	{
		for(const json& neighbor : config["neighbors"].array_items())
		{
			Tile* left = tileset.tile(neighbor["tiles"][0].string_value().c_str());
			Tile* right = tileset.tile(neighbor["tiles"][1].string_value().c_str());
			bool horizontal = neighbor["vertical"].is_null();

			if(left == nullptr || right == nullptr)
				continue;

			if(neighbor["flip"].is_null())
			{
				tileset.connect(left->m_index, right->m_index, horizontal);
			}
			else
			{
				int L = tileset.flip(left->m_index, uint8_t(neighbor["flip"][0].int_value()));
				int R = tileset.flip(right->m_index, uint8_t(neighbor["flip"][1].int_value()));
				tileset.connect(L, R, horizontal);
			}
		}
	}

	void load_edge_propagator(WaveTileset& tileset, const json& config)
	{
		map<char, uint32_t> edge_keys;
		uint32_t next_key = 0;

		for(const json& edge : config["edges"].array_items())
		{
			char code = edge["code"].string_value()[0];
			edge_keys[code] = next_key++;
		}

		for(const json& json_tile : config["tiles"].array_items())
		{
			Tile* tile = tileset.tile(json_tile["name"].string_value().c_str());
			string edges = json_tile["edges"].string_value().c_str();

			for(size_t side = 0; side < 6; ++side)
				tile->m_edges[side] = edge_keys[edges[side]];
		}

		for(const Tile& tile1 : tileset.m_tiles)
			for(const Tile& tile2 : tileset.m_tiles)
			{
				if(&tile1 == &tile2)
					continue;

				if(tile1.m_edges[size_t(SignedAxis::PlusX)] == tile2.m_edges[size_t(SignedAxis::MinusX)])
					tileset.connect(tile1.m_index, tile2.m_index, true);
				if(tile1.m_edges[size_t(SignedAxis::PlusY)] == tile2.m_edges[size_t(SignedAxis::MinusY)])
					tileset.connect(tile1.m_index, tile2.m_index, true);

				if(tile1.m_edges[size_t(SignedAxis::PlusZ)] == tile2.m_edges[size_t(SignedAxis::MinusZ)])
					tileset.connect(tile1.m_index, tile2.m_index, true);
			}
	}

	void parse_json_tileset(const string& path, const string& subset, Tileset& tileset)
	{
		json config;
		parse_json_file(path, config);
		load_json_tileset(tileset, config, subset);
	}

	void parse_json_wave_tileset(const string& path, const string& subset, WaveTileset& tileset)
	{
		json config;
		parse_json_file(path, config);
		load_json_tileset(tileset, config, subset);

		tileset.initialize();

		if(!config["neighbors"].is_null())
			load_rule_propagator(tileset, config);
		else if(!config["edges"].is_null())
			load_edge_propagator(tileset, config);

		tileset.finalize();
	}

	bool neighbour(Wave& wave, const uvec3& coord, SignedAxis d, uvec3& neighbour)
	{
		neighbour = coord;

		if(d == SignedAxis::MinusX)
		{
			if(coord.x == wave.m_width - 1U)
			{
				if(!wave.m_periodic) return false;
				else neighbour.x = 0;
			}
			else neighbour.x = coord.x + 1;
		}
		else if(d == SignedAxis::PlusX)
		{
			if(coord.x == 0)
			{
				if(!wave.m_periodic) return false;
				else neighbour.x = wave.m_width - 1;
			}
			else neighbour.x = coord.x - 1;
		}
		else if(d == SignedAxis::MinusZ)
		{
			if(coord.z == wave.m_depth - 1U)
			{
				if(!wave.m_periodic) return false;
				else neighbour.z = 0;
			}
			else neighbour.z = coord.z + 1;
		}
		else if(d == SignedAxis::PlusZ)
		{
			if(coord.z == 0)
			{
				if(!wave.m_periodic) return false;
				else neighbour.z = wave.m_depth - 1;
			}
			else neighbour.z = coord.z - 1;
		}
		else if(d == SignedAxis::MinusY)
		{
			if(coord.y == wave.m_height - 1U)
			{
				if(!wave.m_periodic) return false;
				else neighbour.y = 0;
			}
			else neighbour.y = coord.y + 1;
		}
		else if(d == SignedAxis::PlusY)
		{
			if(coord.y == 0)
			{
				if(!wave.m_periodic) return false;
				else neighbour.y = wave.m_height - 1;
			}
			else neighbour.y = coord.y - 1;
		}
		return true;
	}

	uint16_t tile_at(Wave& wave, uint16_t x, uint16_t y, uint16_t z)
	{
		uint16_t num_states = 0;;
		uint16_t tile = UINT16_MAX;

		for(uint16_t t = 0; t < wave.m_states.size(); ++t)
			if(wave.m_wave.at(x, y, z)[t])
				tile = (num_states++ == 0) ? t : UINT16_MAX;

		return tile;
	}

	void propagate_tiled(WaveTileset& tileset, Wave& wave)
	{
		uvec3 changed = pop(wave.m_changes);

		int directions = wave.m_depth == 1 ? 4 : 6;
		for(int d = 0; d < directions; d++)
		{
			uvec3 coord;
			if(!neighbour(wave, changed, SignedAxis(d), coord)) continue;

			for(size_t t2 = 0; t2 < wave.m_states.size(); t2++)
				if(wave.m_wave.at(coord.x, coord.y, coord.z)[t2])
				{
					bool b = false;

					for(size_t t1 = 0; t1 < wave.m_states.size() && !b; ++t1)
						if(wave.m_wave.at(changed.x, changed.y, changed.z)[t1])
							b = tileset.m_propagator[d].at(t2, t1) != 0;

					if(!b)
					{
						wave.m_wave.at(coord.x, coord.y, coord.z)[t2] = false;
						wave.m_changes.push_back(coord);
					}
				}
		}
	}

	TileWave::TileWave()
		: Wave()
	{}

	TileWave::TileWave(WaveTileset& tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic)
		: Wave(tileset.m_num_tiles, width, height, depth, periodic)
	{
		m_propagate = [&](Wave& wave) { propagate_tiled(tileset, wave); };
		m_valid_coord = [](int, int, int) { return true; };
		m_states = tileset.m_weights;
	}

	void run_tiled(WaveTileset& tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic)
	{
		TileWave wave(tileset, width, height, depth, periodic);
		wave.solve(0);
	}

	/*
	using Tile = vector<RGBA>;
	using TileLoader = function<Tile(const string& tile_name)>;

	Tile rotate_tile(const Tile& in_tile, const size_t tile_size)
	{
		//CHECK_EQ_F(in_tile.size(), tile_size * tile_size);
		Tile out_tile;
		for(size_t y = 0; y < tile_size; ++y) {
			for(size_t x = 0; x < tile_size; ++x) {
				out_tile.push_back(in_tile[tile_size - 1 - y + x * tile_size]);
			}
		}
		return out_tile;
	}

	void load_tiles(const TileLoader& tile_loader)
	{
		const TileLoader tile_loader = [&](const string& tile_name) -> Tile
		{
			const string path = image_dir + subdir + "/" + tile_name + ".bmp";
			int width, height, comp;
			RGBA* rgba = reinterpret_cast<RGBA*>(stbi_load(path.c_str(), &width, &height, &comp, 4));
			//CHECK_NOTNULL_F(rgba);
			const auto num_pixels = width * height;
			Tile tile(rgba, rgba + num_pixels);
			stbi_image_free(rgba);
			return tile;
		};


		vector<Tile> tiles;

		size_t tile_size = config["tile_size"];//, 16);
		const bool unique = config["unique"]; // , false);

		for(const json& tile : config["tiles"])
		{
			const string tile_name = tile["name"];

			if(unique)
			{
				for(int t = 0; t < cardinality; ++t) {
					string tile_id = tile_name + " " + to_string(t);
					const Tile bitmap = tile_loader(tile_id);
					//CHECK_EQ_F(bitmap.size(), _tile_size * _tile_size);
					tiles.push_back(bitmap);
				}
			}
			else
			{
				string tile_id = tile_name;
				const Tile bitmap = tile_loader(tile_id);
				//CHECK_EQ_F(bitmap.size(), _tile_size * _tile_size);
				tiles.push_back(bitmap);
				for(int t = 1; t < cardinality; ++t)
					tiles.push_back(rotate_tile(tiles[num_patterns + t - 1], tile_size));
			}
		}
	}

	Image TileModel::image(const Wave& wave) const
	{
		Image result(_width * _tile_size, _height * _tile_size, {});

		for(int x = 0; x < _width; ++x)
			for(int y = 0; y < _height; ++y)
			{
				double sum = 0;
				for(size_t t = 0; t < _num_patterns; ++t)
					if(wave.at(x, y)[t])
						sum += _pattern_weight[t];

				for(int yt = 0; yt < _tile_size; ++yt)
					for(int xt = 0; xt < _tile_size; ++xt)
					{
						if(sum == 0)
						{
							result.at(x * _tile_size + xt, y * _tile_size + yt) = { 0, 0, 0, 255 };
						}
						else
						{
							double r = 0, g = 0, b = 0, a = 0;
							for(int t = 0; t < _num_patterns; ++t)
								if(wave.at(x, y)[t])
								{
									RGBA c = _tiles[t][xt + yt * _tile_size];
									r += (double)c.r * _pattern_weight[t] / sum;
									g += (double)c.g * _pattern_weight[t] / sum;
									b += (double)c.b * _pattern_weight[t] / sum;
									a += (double)c.a * _pattern_weight[t] / sum;
								}

							result.at(x * _tile_size + xt, y * _tile_size + yt) = { (uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a };
						}
					}
			}

		return result;
	}
	*/
}




#ifdef MUD_MODULES
module mud.wfc;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_WFC_EXPORT Type& type<mud::Result>() { static Type ty("mud::Result", sizeof(mud::Result)); return ty; }
    
    template <> MUD_WFC_EXPORT Type& type<mud::Tile>() { static Type ty("Tile", sizeof(mud::Tile)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::Tileset>() { static Type ty("Tileset", sizeof(mud::Tileset)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::Wave>() { static Type ty("Wave", sizeof(mud::Wave)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::TileWave>() { static Type ty("TileWave", type<mud::Wave>(), sizeof(mud::TileWave)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::WaveTileset>() { static Type ty("WaveTileset", type<mud::Tileset>(), sizeof(mud::WaveTileset)); return ty; }
}

#ifndef MUD_CPP_20
#include <cmath>
#include <limits>
#include <numeric>
#endif

#ifdef MUD_MODULES
module mud.wfc;
#else
#endif

namespace mud
{
	double calc_sum(const vector<double>& a)
	{
		return std::accumulate(a.begin(), a.end(), 0.0);
	}

	// Pick a random index weighted by a
	size_t spin_the_bottle(const vector<double>& a, double between_zero_and_one)
	{
		double sum = calc_sum(a);

		if(sum == 0.0)
			return size_t(floor(between_zero_and_one * a.size()));

		double between_zero_and_sum = between_zero_and_one * sum;

		double accumulated = 0;
		for(size_t i = 0; i < a.size(); ++i)
		{
			accumulated += a[i];
			if(between_zero_and_sum <= accumulated)
				return i;
		}

		return 0;
	}

	Wave::Wave()
		: m_solved(true)
	{}

	Wave::Wave(uint16_t states, uint16_t width, uint16_t height, uint16_t depth, bool periodic)
		: m_width(width)
		, m_height(height)
		, m_depth(depth)
		, m_periodic(periodic)
		, m_states(states, 1.0)
		, m_wave(width, height, depth, vector<ubool>(states, true))
	{
		m_random_double = []() -> double { return random_scalar<double>(); };
	}

	void Wave::clear()
	{
		m_wave.reset(m_width, m_height, m_depth, vector<ubool>(m_states.size(), true));
		m_changes.clear();
	}

	Result Wave::find_lowest_entropy(uvec3& coord)
	{
		// We actually calculate exp(entropy), i.e. the sum of the weights of the possible patterns
		double min = std::numeric_limits<double>::infinity();

		for(uint16_t x = 0; x < m_width; ++x)
			for(uint16_t y = 0; y < m_height; ++y)
				for(uint16_t z = 0; z < m_depth; ++z)
				{
					if(!m_valid_coord(x, y, z)) continue;

					size_t states = 0;
					double entropy = 0;

					for(uint16_t t = 0; t < m_states.size(); ++t)
					{
						if(m_wave.at(x, y, z)[t])
						{
							states += 1;
							entropy += m_states[t];
						}
					}

					if(entropy == 0 || states == 0)
					{
						int directions = m_depth == 1 ? 4 : 6;

						for(int d = 0; d < directions; d++)
						{
							uvec3 adjacent;
							neighbour(*this, { x, y, z }, SignedAxis(d), adjacent);
							m_failure_point[d] = tile_at(*this, uint16_t(adjacent.x), uint16_t(adjacent.y), uint16_t(adjacent.z));
						}
						return Result::kFail;
					}

					if(states == 1)
						continue; // Already frozen

					// Add a tie-breaking bias:
					const double noise = 0.5 * m_random_double();
					entropy += noise;

					if(entropy < min)
					{
						min = entropy;
						coord = { x, y, z };
					}
				}

		if(min == std::numeric_limits<double>::infinity())
			return Result::kSuccess;
		else
			return Result::kUnfinished;
	}

	Result Wave::observe()
	{
		uvec3 coord;
		m_state = find_lowest_entropy(coord);
		if(m_state == Result::kSuccess)
			m_solved = true;
		if(m_state != Result::kUnfinished)
			return m_state;

		vector<double> distribution(m_states.size());
		for(uint16_t t = 0; t < m_states.size(); ++t)
			distribution[t] = m_wave.at(coord.x, coord.y, coord.z)[t] ? m_states[t] : 0;

		size_t r = spin_the_bottle(distribution, m_random_double());
		for(uint16_t t = 0; t < m_states.size(); ++t)
			m_wave.at(coord.x, coord.y, coord.z)[t] = (t == r);

		m_changes.push_back(coord);
		m_stabilized = false;

		return Result::kUnfinished;
	}

	void Wave::propagate(size_t limit)
	{
		for(size_t i = 0; (limit && i < limit) || (!limit && m_changes.size() > 0); ++i)
			m_propagate(*this);

		if(m_changes.size() == 0)
			m_stabilized = true;
	}

	void Wave::set_tile(const uvec3& coord, uint16_t tile)
	{
		for(uint16_t t = 0; t < m_states.size(); ++t)
			if(t != tile)
				m_wave.at(coord.x, coord.y, coord.z)[t] = false;

		m_changes.push_back({ coord.x, coord.y, coord.z });
	}

	Result Wave::solve(size_t limit)
	{
		for(size_t l = 0; l < limit || limit == 0; ++l)
		{
			Result result = this->observe();

			if(result != Result::kUnfinished)
				return result;

			this->propagate();
		}

		return Result::kUnfinished;
	}
}

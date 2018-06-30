//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.procgen;
#else
#include <json11.hpp>
using json = json11::Json;

#include <infra/Vector.h>
#include <infra/StringConvert.h>
#include <srlz/Serial.h>
#include <math/Axes.h>
#include <math/VecJson.h>
#include <procgen/Wfc/Wfc.h>
#endif


namespace mud
{
	void load_json_tileset(Tileset& tileset, const json& config, const string& subset)
	{
		tileset.m_name = config["name"].string_value();
		from_json(config["tile_size"], tileset.m_tile_size);
		from_json(config["tile_scale"], tileset.m_tile_scale);

		std::set<string> subset_tiles;
		if(subset != "")
			for(const json& tile_name : config["subsets"][subset].array_items())
				subset_tiles.insert(tile_name.string_value());

		for(const json& json_tile : config["tiles"].array_items())
		{
			const string tile_name = json_tile["name"].string_value();
			
			if(!subset_tiles.empty() && subset_tiles.count(tile_name) == 0)
				continue;

			std::function<int(int)> a; // rotates pattern counter-clockwise
			std::function<int(int)> b; // flips pattern vertically
			int cardinality = 1;

			char symmetry = json_tile["symmetry"].string_value()[0];

#ifndef MUD_MODULES // @todo clang bug
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
			else if(symmetry == 'X') {
				cardinality = 1;
				a = [](int i) { return i; };
				b = [](int i) { return i; };
			}
#endif

			const size_t num_patterns = tileset.m_tiles_flip.size();

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
				tileset.m_weights.push_back(json_tile["weight"].number_value() / float(cardinality));
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
			Tile* left = tileset.tile(neighbor["tiles"][0].string_value());
			Tile* right = tileset.tile(neighbor["tiles"][1].string_value());
			bool horizontal = neighbor["vertical"].is_null();

			if(left == nullptr || right == nullptr)
				continue;

			if(neighbor["flip"].is_null())
			{
				tileset.connect(left->m_index, right->m_index, horizontal);
			}
			else
			{
				int L = tileset.flip(left->m_index, neighbor["flip"][0].int_value());
				int R = tileset.flip(right->m_index, neighbor["flip"][1].int_value());
				tileset.connect(L, R, horizontal);
			}
		}
	}

	void load_edge_propagator(WaveTileset& tileset, const json& config)
	{
		std::map<char, uint32_t> edge_keys;
		uint32_t next_key = 0;

		for(const json& edge : config["edges"].array_items())
		{
			char code = edge["code"].string_value()[0];
			edge_keys[code] = next_key++;
		}

		for(const json& json_tile : config["tiles"].array_items())
		{
			Tile* tile = tileset.tile(json_tile["name"].string_value());
			string edges = json_tile["edges"].string_value();

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

	void propagate_tiled(WaveTileset& tileset, Wave& wave)
	{
		uvec3 changed = vector_pop(wave.m_changes);

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
#ifndef MUD_MODULES // @todo clang bug
		m_propagate = [&](Wave& wave) { propagate_tiled(tileset, wave); };
		m_valid_coord = [](int, int, int) { return true; };
		m_states = tileset.m_weights;
#endif
	}

	void run_tiled(WaveTileset& tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic)
	{
		TileWave wave(tileset, width, height, depth, periodic);
		wave.solve(0);
	}

	/*
	using Tile = std::vector<RGBA>;
	using TileLoader = std::function<Tile(const std::string& tile_name)>;

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
		const TileLoader tile_loader = [&](const std::string& tile_name) -> Tile
		{
			const std::string path = image_dir + subdir + "/" + tile_name + ".bmp";
			int width, height, comp;
			RGBA* rgba = reinterpret_cast<RGBA*>(stbi_load(path.c_str(), &width, &height, &comp, 4));
			//CHECK_NOTNULL_F(rgba);
			const auto num_pixels = width * height;
			Tile tile(rgba, rgba + num_pixels);
			stbi_image_free(rgba);
			return tile;
		};


		std::vector<Tile> tiles;

		size_t tile_size = config["tile_size"];//, 16);
		const bool unique = config["unique"]; // , false);

		for(const json& tile : config["tiles"])
		{
			const std::string tile_name = tile["name"];

			if(unique)
			{
				for(int t = 0; t < cardinality; ++t) {
					std::string tile_id = tile_name + " " + to_string(t);
					const Tile bitmap = tile_loader(tile_id);
					//CHECK_EQ_F(bitmap.size(), _tile_size * _tile_size);
					tiles.push_back(bitmap);
				}
			}
			else
			{
				std::string tile_id = tile_name;
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




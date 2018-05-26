
#include <gen/Wfc/Tileblock.h>

#include <geom/Intersect.h>
#include <geom/Shapes.h>
#include <geom/Symbol.h>
#include <geom/Primitive.h>

#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/Gfx.h>
#include <edit/Viewer/Viewer.h>

namespace mud
{
	Tileblock::Tileblock(const uvec3& size, const vec3& period, WaveTileset& tileset)
		: m_size(size)
		, m_period(period)
		, m_tileset(tileset)
		, m_wave(m_tileset, uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), false)
		, m_tiles(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), UINT16_MAX)
		, m_entropy(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), 0U)
	{}

	void Tileblock::next_frame(size_t tick, size_t delta)
	{
		UNUSED(delta);
		if(!m_wave.m_solved)
		{
			for(size_t i = 0; i < 10; ++i)
			{
				this->propagate();
				this->observe();
			}
			//this->solve();
		}

		m_last_tick = tick;
	}

	void Tileblock::reset()
	{
		m_wave = TileWave(m_tileset, uint16_t(m_size.x), uint16_t(m_size.y), uint16_t(m_size.z), false);
		this->update(m_wave);
	}

	void Tileblock::observe()
	{
		m_wave.observe();
		this->update(m_wave);
	}

	void Tileblock::propagate()
	{
		m_wave.propagate();
		this->update(m_wave);
	}

	void Tileblock::solve(size_t limit)
	{
		m_wave.solve(limit);
		this->update(m_wave);
	}

	void Tileblock::update(Wave& wave)
	{
		m_tiles.clear(UINT16_MAX);

		for(size_t x = 0; x < wave.m_width; x++) for(size_t y = 0; y < wave.m_height; y++) for(size_t z = 0; z < wave.m_depth; z++)
		{
			uint16_t num_states = 0;;

			for(uint16_t t = 0; t < wave.m_states.size(); ++t)
				if(wave.m_wave.at(x, y, z)[t])
					m_tiles.at(x, y, z) = (num_states++ == 0) ? t : UINT16_MAX;

			if(num_states > 1U)
				m_entropy.at(x, y, z) = num_states;
		}

		m_wave_updated = m_last_tick;
	}

	void paint_tile_grid(Gnode& parent, Tileblock& tileblock)
	{
		Colour colour = { 0.3f, 0.3f, 0.3f, 0.4f };
		Grid2 grid = { vec2{ float(tileblock.m_size.x), float(tileblock.m_size.z) } };

		vec3 center = -0.5f * vec3(tileblock.m_size) * tileblock.m_period;
		Gnode& self = gfx::node(parent, {}, center);
		gfx::shape(self, grid, Symbol(colour));
	}

	Model& entropy_cube(Gnode& parent, Tileblock& tileblock, uint16_t x, uint16_t y, uint16_t z)
	{
		static std::vector<Model*> cubes(tileblock.m_tileset.m_num_tiles + 1, nullptr);
		uint16_t states = tileblock.m_entropy.at(x, y, z);
		if(!cubes[states])
		{
			float entropy = float(states) / float(tileblock.m_tileset.m_num_tiles);
			Colour colour = Colour::AlphaGrey * entropy;
			cubes[states] = &parent.m_scene->m_gfx_system.fetch_symbol(Symbol(colour), Cube(0.5f), OUTLINE);
		}
		return *cubes[states];
	}

	struct TileOccurence { Model* tile; vec3 position; vec3 rotation; };

	struct VisuBlock : public NodeState
	{
		size_t m_updated = 0;
		std::map<Model*, std::vector<TileOccurence>> m_tiles;
	};

	void paint_tiles(Gnode& parent, Tileblock& tileblock)
	{
		VisuBlock& visu = parent.state<VisuBlock>();

		vec3 center = -0.5f * vec3(tileblock.m_size) * tileblock.m_period;
		Gnode& self = gfx::node(parent, {}, center);

		if(visu.m_updated < tileblock.m_wave_updated)
		{
			visu.m_updated = tileblock.m_wave_updated;

			self.clear();
			visu.m_tiles.clear();

			for(size_t x = 0; x < tileblock.m_tiles.m_x; ++x) for(size_t y = 0; y < tileblock.m_tiles.m_y; ++y) for(size_t z = 0; z < tileblock.m_tiles.m_z; ++z)
			{
				uint16_t index = tileblock.m_tiles.at(x, y, z);

				if(index == UINT16_MAX)
				{
					Model& cube = entropy_cube(parent, tileblock, uint16_t(x), uint16_t(y), uint16_t(z));
					visu.m_tiles[&cube].push_back({ &cube, vec3(uvec3(x, y, z)) + 0.5f, Zero3 });
					continue;
				}
				else
				{
					Tile& tile = tileblock.m_tileset.m_tiles_flip[index];

					if(tile.m_name == "empty")
						continue;

					Model* model = self.m_scene->m_gfx_system.models().file((tileblock.m_tileset.m_name + "/" + tile.m_name).c_str());
					visu.m_tiles[model].push_back({ model, vec3{ float(x) + 0.5f, float(y), float(z) + 0.5f }, vec3{ 0.f, -tile.m_profile * M_PI / 2.f, 0.f } });
				}
			}
		}

		for(auto& model_tiles : visu.m_tiles)
		{
			Item& item = gfx::item(self, *model_tiles.first, 0, nullptr, model_tiles.second.size());
			size_t index = 0;
			for(TileOccurence& tile : model_tiles.second)
				item.m_instances[index++] = bxSRT(tileblock.m_tileset.m_tile_scale, tile.rotation, tile.position + center);
		}
	}

	void highlighted_tile(Gnode& parent, const vec3& coord)
	{
		Gnode& self = gfx::node(parent, {}, coord + 0.5f);
		gfx::shape(self, Cube(0.5f + 0.01f), Symbol(Colour::Red));
	}

	void highlighted_tile(Gnode& parent, const uvec3& coord)
	{
		Gnode& node = gfx::node(parent, {}, vec3(coord));
		gfx::shape(node, Cube(), Symbol());
	}

	void paint_tileblock(Gnode& parent, Tileblock& tileblock)
	{
		paint_tile_grid(parent, tileblock);
		paint_tiles(parent, tileblock);

		if(tileblock.m_highlight != uvec3(UINT32_MAX))
			highlighted_tile(parent, vec3(tileblock.m_highlight));
	}


	void tile_view(Widget& parent, Tile& tile)
	{
		UNUSED(parent); UNUSED(tile);
	}

	struct ModelArrayView : public NodeState
	{
		GfxSystem& m_gfx_system;
		std::vector<Model*> models;
		std::vector<vec3> positions;
		std::vector<quat> rotations;
		std::vector<vec3> scales;

		ModelArrayView(GfxSystem& gfx_system) : m_gfx_system(gfx_system) {}
	};

	void model_array_view(Widget& parent, std::function<void(ModelArrayView&)> query_state)
	{
		SceneViewer& viewer = ui::scene_viewer(parent);
		ModelArrayView& state = viewer.state<ModelArrayView>(viewer.m_gfx_system);

		if(state.models.empty())
		{
			query_state(state);

			if(state.models.empty())
				return;

			uint16_t num_rows = 1;
			uint16_t num_columns = uint16_t(state.models.size()) / num_rows;

			vec3 array_size = { float(num_columns), 1.f, float(num_rows) };

			viewer.m_viewport.m_clear_colour = Colour::DarkGrey;
			viewer.m_camera.set_isometric(SOUTH, array_size * 0.5f);

			float margin = 0.8f;
			for(uint16_t i = 0; i < state.models.size(); ++i)
			{
				state.positions.push_back({ float(i % num_columns), 0.f, float(i / num_columns) });
				state.scales.push_back(vec3{ 1.f / (state.models[i]->m_radius * 2.f * margin) });
			}
		}

		Gnode& groot = viewer.m_scene->begin();
		for(size_t i = 0; i < state.models.size(); ++i)
			gfx::node_model(groot, *state.models[i], state.positions[i], state.rotations[i], state.scales[i]);
	}

	void tileset_view(Widget& parent, Tileset& tileset)
	{
		auto query_models = [&](ModelArrayView& state)
		{
			for(Tile& tile : tileset.m_tiles_flip)
			{
				state.models.push_back(state.m_gfx_system.models().file(tile.m_name.c_str()));
				state.rotations.push_back(angle_axis(float(M_PI) / 4.f - tile.m_profile * float(M_PI) / 2.f, Y3));
			}
		};

		model_array_view(parent, query_models);
	}

	void tileblock_view(Widget& parent, Tileblock& tileblock)
	{
		Widget& self = ui::layout(parent);

		if(tileblock.m_highlight == uvec3(UINT32_MAX))
			return;

		uvec3 coord = tileblock.m_highlight;

		auto query_models = [&](ModelArrayView& state)
		{
			for(size_t t = 0; t < tileblock.m_wave.m_states.size(); ++t)
				if(tileblock.m_wave.m_wave.at(coord.x, coord.y, coord.z)[t])
				{
					Tile tile = tileblock.m_tileset.m_tiles_flip[t];
					state.models.push_back(state.m_gfx_system.models().file(tile.m_name.c_str()));
					state.rotations.push_back(angle_axis(float(M_PI) / 4.f - tile.m_profile * float(M_PI) / 2.f, Y3));
				}
		};

		uint32_t id = (uint16_t(coord.x) << 16) | (uint16_t(coord.z) << 0);
		Widget& sheet = ui::widget(self, styles().sheet, (void*)id);
		model_array_view(sheet, query_models);
	}

	void tileblock_edit(Widget& parent, Tileblock& tileblock)
	{
		Widget& self = ui::layout_span(parent, 0.2f);
		tileblock_view(self, tileblock);
		//tileset_view(self, tileblock.m_tileset);
	}

	void tileblock_editor(Widget& parent, Viewer& viewport, Tileblock& tileblock)
	{
		Widget& self = ui::layout(parent);
		ui::layout_span(self, 0.8f);
		tileblock_edit(self, tileblock);

		vec3 closest;
		if(ray_aabb_intersection(Zero3, vec3(tileblock.m_size), viewport.mouse_ray(), closest))
			tileblock.m_highlight = clamp(uvec3(floor(closest)), uvec3(0U), tileblock.m_size - 1U);
		else
			tileblock.m_highlight = uvec3(UINT_MAX);

		if(ray_aabb_intersection(Zero3, vec3(tileblock.m_size), viewport.mouse_ray(), closest))
			highlighted_tile(viewport.m_scene->m_graph, floor(closest));
	}

}

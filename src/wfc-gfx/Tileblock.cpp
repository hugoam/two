//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc.gfx;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#include <math/Axes.h>
#include <math/Stat.hpp>
#include <math/Grid.hpp>
#include <geom/Intersect.h>
#include <geom/Shapes.h>
#include <geom/Symbol.h>
#include <geom/Primitive.h>
#include <tree/Graph.hpp>
#include <ui/Input.h>
#include <ui/Section.h>
#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/Gfx.h>
#include <gfx-ui/Viewer.h>
#include <wfc-gfx/Types.h>
#include <wfc-gfx/Tileblock.h>
#include <ecs/ECS.h>
#include <meta/math.conv.h>
#endif

namespace mud
{
	WfcBlock::WfcBlock() {}
	WfcBlock::WfcBlock(const vec3& position, const uvec3& size, const vec3& scale, WaveTileset& tileset, bool auto_solve)
		: m_position(position)
		, m_size(size)
		, m_scale(scale)
		, m_aabb(vec3(0.f), 0.5f * vec3(size) * scale)
		, m_tileset(&tileset)
		, m_wave(tileset, uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), false)
		, m_tiles(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), UINT16_MAX)
		, m_entropy(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), 0U)
		, m_auto_solve(auto_solve)
	{}

	uvec3 WfcBlock::to_coord(const vec3& position)
	{
		vec3 relative = position - m_position - m_aabb.bmin();
		return clamp(uvec3(floor(relative)), uvec3(0U), m_size - 1U);
	}

	vec3 WfcBlock::to_position(const uvec3& coord)
	{
		return m_position + m_aabb.bmin() + (vec3(coord) + vec3(0.5f, 0.f, 0.5f)) * m_scale;
	}

	void WfcBlock::load_models(GfxSystem& gfx, bool from_file)
	{
		for(Tile& tile : m_tileset->m_tiles_flip)
		{
			Model* model = from_file ? gfx.models().file(m_tileset->m_name + "/" + tile.m_name)
									 : gfx.models().get(tile.m_name.c_str());
			quat rotation = angle_axis(tile.m_profile * c_pi / 2.f, Y3);
			m_tile_models.push_back({ model, rotation });
		}
	}

	void WfcBlock::next_frame(size_t tick, size_t delta)
	{
		UNUSED(delta);
		if(m_auto_solve && !m_wave.m_solved)
		{
			if(m_wave.m_state == Result::kFail)
				this->reset();
			if(!m_wave.m_solved)
			{
				const size_t steps = 100;
				for(size_t i = 0; i < steps; ++i)
				{
					m_wave.propagate();
					m_wave.observe();
				}
				this->update(m_wave);
			}
		}

		m_last_tick = tick;
	}

	void WfcBlock::reset()
	{
		m_wave = TileWave(*m_tileset, uint16_t(m_size.x), uint16_t(m_size.y), uint16_t(m_size.z), false);
		this->update(m_wave);
	}

	void WfcBlock::observe()
	{
		m_wave.observe();
		this->update(m_wave);
	}

	void WfcBlock::propagate()
	{
		m_wave.propagate();
		this->update(m_wave);
	}

	void WfcBlock::solve(size_t limit)
	{
		m_wave.solve(limit);
		this->update(m_wave);
	}

	void WfcBlock::update(Wave& wave)
	{
		m_tiles.clear(UINT16_MAX);

		for(size_t x = 0; x < wave.m_width; x++) for(size_t y = 0; y < wave.m_height; y++) for(size_t z = 0; z < wave.m_depth; z++)
		{
			uint16_t num_states = 0;;
			uint16_t tile = UINT16_MAX;

			for(uint16_t t = 0; t < wave.m_states.size(); ++t)
				if(wave.m_wave.at(x, y, z)[t])
					tile = (num_states++ == 0) ? t : UINT16_MAX;

			m_entropy.at(x, y, z) = num_states;
			if(num_states == 1)
				m_tiles.at(x, y, z) = tile;
		}

		m_wave_updated = m_last_tick;

		if(wave.m_solved)
			m_wave_solved = m_last_tick;
	}

	void paint_tile_grid(Gnode& parent, WfcBlock& tileblock)
	{
		Colour colour = { 0.3f, 0.3f, 0.3f, 0.4f };
		Grid2 grid = { to_xz(vec3(tileblock.m_size)), to_xz(tileblock.m_scale) };

		Gnode& top = gfx::node(parent, {}, tileblock.m_aabb.m_center + Y3 * tileblock.m_aabb.m_extents.y);
		gfx::shape(top, grid, Symbol(colour));

		Gnode& bottom = gfx::node(parent, {}, tileblock.m_aabb.m_center - Y3 * tileblock.m_aabb.m_extents.y);
		gfx::shape(bottom, grid, Symbol(colour));
	}

	Model& entropy_cube(Gnode& parent, WfcBlock& tileblock, uint16_t x, uint16_t y, uint16_t z)
	{
		static vector<Model*> cubes(tileblock.m_tileset->m_num_tiles + 1, nullptr);
		uint16_t states = tileblock.m_entropy.at(x, y, z);
		if(!cubes[states])
		{
			float entropy = tileblock.m_tileset->m_num_tiles > 0 ? float(states) / float(tileblock.m_tileset->m_num_tiles) : 1.f;
			Colour colour = Colour::AlphaGrey * entropy;
			cubes[states] = &parent.m_scene->m_gfx.shape(Cube(0.5f), Symbol(colour), OUTLINE);
		}
		return *cubes[states];
	}

	struct VisuBlock : public NodeState
	{
		size_t m_updated = 0;
		map<Model*, vector<mat4>> m_tiles;
	};

	inline bool intersects(const uvec3& coord, const uvec3& lo, const uvec3& hi)
	{
		return coord.x >= lo.x && coord.x <= hi.x
			&& coord.y >= lo.y && coord.y <= hi.y
			&& coord.z >= lo.z && coord.z <= hi.z;
	}

	void paint_tiles(Gnode& parent, Ref object, WfcBlock& tileblock, const uvec3& focused, const uvec3* exclude, bool draw_entropy)
	{
		VisuBlock& visu = parent.state<VisuBlock>();

		Gnode& self = gfx::node(parent, object, tileblock.m_aabb.bmin());

		bool dirty = visu.m_updated < tileblock.m_wave_updated;
		if(dirty || exclude)
		{
			visu.m_updated = tileblock.m_wave_updated;

			self.clear();
			visu.m_tiles.clear();

			for(size_t x = 0; x < tileblock.m_tiles.m_x; ++x) for(size_t y = 0; y < tileblock.m_tiles.m_y; ++y) for(size_t z = 0; z < tileblock.m_tiles.m_z; ++z)
			{
				uint16_t index = tileblock.m_tiles.at(x, y, z);

				auto tile_transform = [&](quat rotation)
				{
					vec3 position = tileblock.to_position({ uint(x), uint(y), uint(z) });
					vec3 scale = tileblock.m_tileset->m_tile_scale * tileblock.m_scale;
					return bxTRS(scale, rotation, position);
				};

				if(index == UINT16_MAX)
				{
					if(draw_entropy)
					{
						Model& cube = entropy_cube(parent, tileblock, uint16_t(x), uint16_t(y), uint16_t(z));
						visu.m_tiles[&cube].push_back(tile_transform(ZeroQuat));
					}
				}
				else
				{
					if(exclude)
					{
						uvec3 lo = exclude[0];
						uvec3 hi = exclude[1];
						if(intersects(uvec3(uint(x), uint(y), uint(z)), lo, hi))
							continue;
					}

					TileModel& tile = tileblock.m_tile_models[index];
					if(tile.m_model)
						visu.m_tiles[tile.m_model].push_back(tile_transform(tile.m_rotation));
				}
			}
		}

		static Material& alpha_material = parent.m_scene->m_gfx.fetch_material("debug_alpha", "solid");

		for(auto& model_tiles : visu.m_tiles)
		{
			Material* material = focused == uvec3(UINT32_MAX) ? nullptr : &alpha_material;
			uint32_t flags = ItemFlag::Default | ItemFlag::Static | (dirty ? 0 : uint32_t(ItemFlag::NoUpdate));
			Item& item = gfx::item(self, *model_tiles.first, flags, material);
			gfx::instances(self, item, model_tiles.second);
		}

		if(focused != uvec3(UINT32_MAX))
		{
			uint16_t index = tileblock.m_tiles.at(focused.x, focused.y, focused.z);
			if(index != UINT16_MAX)
			{
				TileModel& tile = tileblock.m_tile_models[index];
				Gnode& node = gfx::node(self, {}, tileblock.to_position(focused), tile.m_rotation, tileblock.m_tileset->m_tile_scale * tileblock.m_scale);
				if(tile.m_model)
					gfx::item(node, *tile.m_model);
			}
		}
	}

	void paint_tile_cube(Gnode& parent, WfcBlock& tileblock, const uvec3& coord, const Colour& outline, const Colour& fill)
	{
		Gnode& node = gfx::node(parent, {}, tileblock.to_position(coord) + Y3 * 0.5f);
		gfx::shape(node, Cube(0.5f + 0.01f), Symbol(outline, fill));
	}

	void paint_tile_cube(Gnode& parent, WfcBlock& tileblock, const uvec3& coord)
	{
		return paint_tile_cube(parent, tileblock, coord, Colour::Red);
	}

	void paint_tileblock(Gnode& parent, Ref object, WfcBlock& tileblock, const uvec3& focused, const uvec3* exclude, bool draw_entropy)
	{
		paint_tile_grid(parent, tileblock);
		paint_tiles(parent, object, tileblock, focused, exclude, draw_entropy);
	}

	struct ModelArrayItem
	{
		Model* m_model;
		vec3 m_position;
		quat m_rotation;
		vec3 m_scale;
	};

	struct ModelArrayView : public NodeState
	{
		ModelArrayView() {}
		vector<ModelArrayItem> m_items = {};
		float m_item_radius = 0.f;
	};

	void model_array_view(Widget& parent, function<void(ModelArrayView&)> query_state, void* id = nullptr)
	{
		Widget& self = ui::widget(parent, styles().stack, id);
		ModelArrayView& state = self.state<ModelArrayView>();

		if(state.m_items.empty())
			query_state(state);

		if(state.m_items.empty())
			return;

		uint16_t num_rows = 2;
		uint16_t num_columns = uint16_t(state.m_items.size()) / num_rows;

		float size = 90.f;//parent.m_frame.m_size.x / float(num_columns);
		SceneViewer& viewer = ui::scene_viewer(self, { num_columns * size, num_rows * size });

		vec3 array_size = { float(num_columns - 1), 1.f, float(num_rows - 1) };
		vec3 center = array_size * 0.5f;

		viewer.m_viewport.m_clear_colour = Colour::DarkGrey;
		viewer.m_camera.set_isometric(IsometricAngle(SOUTH), center);
		viewer.m_camera.m_height = num_rows;

		float margin = 1.2f;
		for(uint16_t i = 0; i < state.m_items.size(); ++i)
		{
			state.m_items[i].m_position = { float(i % num_columns), 0.f, float(i / num_columns) };
			state.m_items[i].m_scale = vec3{ 1.f / (state.m_item_radius * 2.f * margin) };
		}

		Gnode& scene = viewer.m_scene.begin();
		gfx::direct_light_node(scene);

		auto draw = [](Gnode& parent, const Model& model, const vec3& position, const quat& rotation, const vec3& scale)
		{
			Gnode& self = gfx::node(parent, {}, position, rotation, scale);
			return gfx::item(self, model);
		};

		for(ModelArrayItem& item : state.m_items)
			if(item.m_model)
				draw(scene, *item.m_model, item.m_position, item.m_rotation, item.m_scale);

		//Gnode& origin = gfx::node(scene, {}, center);
		//gfx::draw(origin, Line(-100.f * X3, 100.f * X3), Symbol(Colour::Red));
		//gfx::draw(origin, Line(-100.f * Y3, 100.f * Y3), Symbol(Colour::Green));
		//gfx::draw(origin, Line(-100.f * Z3, 100.f * Z3), Symbol(Colour::Blue));
		//
		//Gnode& horigin = gfx::node(scene, {}, vec3(0.f, center.y, 0.f));
		//gfx::draw(horigin, Grid2(vec2(num_columns, num_rows)), Symbol());
	}

	void tileset_view(Widget& parent, WfcBlock& tileblock, Tileset& tileset)
	{
		auto query_models = [&](ModelArrayView& state)
		{
			for(Tile& tile : tileset.m_tiles_flip)
			{
				TileModel& tile_model = tileblock.m_tile_models[tile.m_index];
				state.m_items.push_back({ tile_model.m_model, vec3(0.f), rotate(tile_model.m_rotation, c_pi / 4.f, Y3), vec3(1.f) });
				if(tile_model.m_model && state.m_item_radius == 0.f)
					state.m_item_radius = tile_model.m_model->m_radius;
			}
		};

		model_array_view(parent, query_models);
	}

	void tile_states_view(Widget& parent, WfcBlock& tileblock, uvec3& coord)
	{
		auto query_models = [&](ModelArrayView& state)
		{
			for(size_t t = 0; t < tileblock.m_wave.m_states.size(); ++t)
				if(tileblock.m_wave.m_wave.at(coord.x, coord.y, coord.z)[t])
				{
					Tile& tile = tileblock.m_tileset->m_tiles_flip[t];
					TileModel& tile_model = tileblock.m_tile_models[tile.m_index];
					state.m_items.push_back({ tile_model.m_model, vec3(0.f), rotate(tile_model.m_rotation, c_pi / 4.f, Y3), vec3(1.f) });
					if(tile_model.m_model && state.m_item_radius == 0.f)
						state.m_item_radius = tile_model.m_model->m_radius;
				}
		};

		uint32_t id = (uint16_t(coord.x) << 16) | (uint16_t(coord.z) << 0);
		model_array_view(parent, query_models, (void*)uintptr_t(id));
	}

	uvec3 tileblock_ray(WfcBlock& tileblock, const Ray& ray)
	{
		vec3 closest;
		if(ray_aabb_intersection(tileblock.m_aabb.bmin(), tileblock.m_aabb.bmax(), ray, closest))
			return tileblock.to_coord(closest);
		else
			return uvec3(UINT_MAX);
	}
	
	void paint_states(Gnode& parent, WfcBlock& tileblock, const uvec3& coord)
	{
		paint_tile_cube(parent, tileblock, coord, Colour::Pink, Colour::None);

		Gnode& node = gfx::node(parent, {}, vec3(coord));

		size_t index = tileblock.m_wave.m_wave.indexAt(coord.x, coord.y, coord.z);
		size_t side = size_t(ceil(sqrt(float(tileblock.m_entropy[index]))));
		size_t columns = tileblock.m_entropy[index] / side;

		vec3 offset = tileblock.to_position(coord) - vec3(float(side - 1), 0.f, float(columns - 1)) * 0.5f + Y3 * 0.5f;

		size_t count = 0;
		for(uint16_t t = 0; t < tileblock.m_wave.m_states.size(); ++t)
			if(tileblock.m_wave.m_wave.at(coord.x, coord.y, coord.z)[t])
			{
				vec3 position = offset + vec3(float(count % side), 0.f, float(count / side));
				Gnode& con = gfx::node(node, {}, position, tileblock.m_tile_models[t].m_rotation, tileblock.m_tileset->m_tile_scale / 2.f);
				if(tileblock.m_tile_models[t].m_model)
					gfx::item(con, *tileblock.m_tile_models[t].m_model);
				++count;
			}
	}

	void paint_connections(Gnode& parent, WfcBlock& tileblock, const uvec3& coord)
	{
		Gnode& node = gfx::node(parent, {}, vec3(coord));

		int directions = tileblock.m_wave.m_depth == 1 ? 4 : 6;
		for(int d = 0; d < directions; d++)
		{
			size_t count = 0;

			size_t t2 = tileblock.m_tiles.at(coord.x, coord.y, coord.z);
			//uvec3 adjacent;
			//if(neighbour(tileblock.m_wave, coord, SignedAxis(d), adjacent))
				for(size_t t1 = 0; t1 < tileblock.m_wave.m_states.size(); ++t1)
					if(tileblock.m_tileset->m_propagator[d].at(t2, t1))
						if(tileblock.m_tile_models[t1].m_model)
						{
							vec3 position = tileblock.to_position(coord) + to_vec3(SignedAxis(d)) * float(++count) * 2.f;
							Gnode& con = gfx::node(node, {}, position, tileblock.m_tile_models[t1].m_rotation, tileblock.m_tileset->m_tile_scale);
							gfx::item(con, *tileblock.m_tile_models[t1].m_model);
						}
		}
	}

	void tileblock_edit(Widget& parent, Viewer& viewer, WfcBlock& tileblock, uvec3& highlighted, uvec3& selected, uvec3& focused)
	{
		Section& self = section(parent, "Edit WfcBlock");
		Widget& body = *self.m_body;

		auto button = [&](cstring label) { Widget& row = ui::row(body); return ui::button(row, label).activated(); };

		if(button("reset"))
			tileblock.reset();

		if(button("solve 10"))
			tileblock.solve(10);

		static uint16_t tile = 0;
		ui::number_field<uint16_t>(body, "tile", { tile, StatDef<uint16_t>{} });

		if(button("set tile"))
			tileblock.m_wave.set_tile(selected, tile);

		if(button("propagate once"))
			tileblock.m_wave.propagate(1);

		Widget& row = ui::row(body);
		ui::toggle(row, tileblock.m_auto_solve, "auto solve");

		//Widget& overlay = ui::screen(viewer);
		//tileset_view(overlay, tileblock, tileblock.m_tileset);

		//if(highlighted != uvec3(UINT32_MAX))
		//	tile_states_view(overlay, tileblock, highlighted);

		highlighted = tileblock_ray(tileblock, viewer.mouse_ray());

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			selected = tileblock_ray(tileblock, viewer.mouse_ray());

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			selected = tileblock_ray(tileblock, viewer.mouse_ray());

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseRight, EventType::Pressed))
			focused = tileblock_ray(tileblock, viewer.mouse_ray());
		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseRight, EventType::Released))
			focused = uvec3(UINT32_MAX);

		if(focused != uvec3(UINT32_MAX))
		{
			Widget& widget = ui::popup(viewer, styles().modal, ui::PopupFlags::None);

			size_t entropy = tileblock.m_entropy.at(focused.x, focused.y, focused.z);
			if(entropy == 1)
			{
				paint_connections(viewer.m_scene->m_graph, tileblock, focused);
				ui::label(widget, "Allowed Connections");
			}
			else
			{
				paint_states(viewer.m_scene->m_graph, tileblock, focused);
				ui::label(widget, "Possible States");
			}
		}
	}

	void tileblock_editor(Widget& parent, Viewer& viewer, WfcBlock& tileblock)
	{
		Widget& self = ui::layout(parent);

		static uvec3 highlighted = uvec3(UINT32_MAX);
		static uvec3 selected = uvec3(UINT32_MAX);
		static uvec3 focused = uvec3(UINT32_MAX);

		tileblock_edit(self, viewer, tileblock, highlighted, selected, focused);
	}

}

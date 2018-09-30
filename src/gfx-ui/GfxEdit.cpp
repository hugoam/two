//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.ui;
#else
#include <infra/Vector.h>
#include <type/Vector.h>
#include <type/DispatchDecl.h>
#include <pool/ObjectPool.h>
#include <refl/Class.h>
#include <math/Axes.h>
#include <geom/Symbol.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Aabb.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Input.h>
#include <ui/Sequence.h>
#include <uio/Unode.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Value.h>
#include <gfx/Gfx.h>
#include <gfx/Animated.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Asset.h>
#include <gfx/Pipeline.h>
#include <gfx/Froxel.h>
#include <gfx/Frustum.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-ui/Types.h>
#include <gfx-ui/GfxEdit.h>
#include <gfx-ui/Viewer.h>
#include <gfx-ui/ParticleEdit.h>
#endif

namespace mud
{
	void animation_edit(Widget& parent, Animated& animated)
	{
		Widget& self = ui::sheet(parent);

		Table& table = ui::table(self, carray<cstring, 2>{ "Field", "Value" }, carray<float, 2>{ 0.3f, 0.7f });

		static std::vector<cstring> animations;
		animations.clear();
		for(Animation* animation : animated.m_rig.m_skeleton.m_animations)
			animations.push_back(animation->m_name.c_str());

		static size_t animation = 0;
		if(ui::radio_field(table, "animation", animations, animation))
			animated.play(animations[animation], true, 0.f, 1.f);

		if(!animated.m_playing.empty())
		{
			AnimationPlay& play = animated.m_playing.back();
			ui::slider_field<float>(table, "speed", { play.m_speed, { -5.f, 5.f, 0.01f } });
			ui::slider_field<float>(table, "timeline", { play.m_cursor, { 0.f, play.m_animation->m_length, 0.01f } });
		}

		Table& playing = ui::table(self, carray<cstring, 2>{ "Animation", "Time" }, carray<float, 2>{ 0.6f, 0.4f });
		for(AnimationPlay& play : animated.m_playing)
		{
			Widget& row = ui::table_row(playing);
			ui::label(row, play.m_animation->m_name.c_str());
			ui::label(row, to_string(play.m_cursor).c_str());
		}

	}

	void space_axes(Gnode& parent)
	{
		static Colour colours[3] = { Colour::Red, Colour::Green, Colour::Blue };
		for(Axis axis : { Axis::X, Axis::Y, Axis::Z })
		{
			Gnode& node = gfx::node(parent, {}, to_vec3(axis) * 1.f);
			gfx::shape(node, Cylinder(0.1f, 1.f, axis), Symbol(colours[size_t(axis)]));
		}
	}

	mat4 fix_bone_pose(Bone& bone)
	{
		return bxrotation(angle_axis(-c_pi * 0.5f, X3)) * bxscale(vec3(0.009999999776482582f)) * bone.m_pose;
	}

	void debug_draw_skeleton(Gnode& parent, const vec3& position, const quat& rotation, Rig& rig)
	{
		for(Bone& bone : rig.m_skeleton.m_bones)
		{
			mat4 pose = bxrotation(rotation) * fix_bone_pose(bone);
			Gnode& node = gfx::node(parent, {}, position + vec3(pose * vec4(Zero3, 1.f)));
			gfx::shape(node, Sphere(0.02f), Symbol());
		}
	}

	void debug_draw_light_clusters(Gnode& parent, Camera& camera)
	{
		if(!camera.m_clustered) return;
		Froxelizer& clusters = *camera.m_clusters;

		if(clusters.m_debug_clusters.empty())
			clusters.compute_froxels();

		auto set_alpha = [](Colour c, float a) { c.m_a = a; return c; };
		static Colour pink = set_alpha(Colour::Pink, 0.1f);
		static Colour cyan = set_alpha(Colour::Cyan, 0.1f);

		enum Mode { ClusterIndex, RecordIndex, LightIndex, LightCount };
		Mode mode = ClusterIndex;

		mat4 transform = inverse(bxlookat(camera.m_eye, camera.m_target));
		size_t i = 0;
		for(Frustum& frustum : clusters.m_debug_clusters)
		{
			if(!clusters.m_froxels.m_data[i].count[0] && !clusters.m_froxels.m_data[i].count[1])
			{
				//gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour(1.f, 0.02f)));
				i++;
				continue;
			}

			Colour colour = Colour(1.f, 0.02f);
			size_t record = clusters.m_froxels.m_data[i].offset;
			size_t light = clusters.m_records.m_data[record];

			if(mode == ClusterIndex)
				colour = hsl_to_rgb(float(i) / (29.f * 16.f * 16.f), 1.f, 0.5f);
			else if(mode == RecordIndex)
				colour = hsl_to_rgb(float(record) / float(255.f), 1.f, 0.5f);
			else if(mode == LightIndex)
				colour = hsl_to_rgb(float(light) / 255.f, 1.f, 0.5f);
			else if(mode == LightCount)
				colour = hsl_to_rgb(float(clusters.m_froxels.m_data[i].count[0]) / 32.f, 1.f, 0.5f);
			
			gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(colour));
			i++;
		}
	}

	void debug_draw_light_slices(Gnode& parent, Light& light)
	{
		uint32_t index = 0; UNUSED(light);// light.m_index];

		GfxSystem& gfx_system = parent.m_scene->m_gfx_system;
		BlockShadow& block_shadow = *gfx_system.m_pipeline->block<BlockShadow>();
		
		if(index >= block_shadow.m_shadows.size())
			return;

		LightShadow& shadow = block_shadow.m_shadows[index];

		auto draw = [](Gnode& parent, const Shape& shape, const Symbol& symbol)
		{
			Gnode& self = gfx::node(parent, {});
			gfx::draw(self, shape, symbol);
		};

		for(size_t i = 0; i < shadow.m_slices.size(); ++i)
		{
			Frustum& frustum = shadow.m_frustum_slices[i].m_frustum;
			draw(parent, Box({ &frustum.m_corners[0], 8 }), Symbol());
			if(false)
				draw(parent, Sphere(frustum.m_center, frustum.m_radius), Symbol(Colour::DarkGrey));

			mat4 inverse_light = inverse(shadow.m_slices[i].m_transform);

			draw(parent, Sphere(vec3(inverse_light[3]), 1.f), Symbol());

			Box light_bounds = Box(min_max_to_aabb(shadow.m_slices[i].m_light_bounds.min, shadow.m_slices[i].m_light_bounds.max));

			for(vec3& vertex : light_bounds.m_vertices)
				vertex = vec3(inverse_light * vec4(vertex, 1.f));

			draw(parent, light_bounds, Symbol(Colour::Pink));
		}
	}

	void double_label(Widget& parent, cstring label, cstring value)
	{
		Widget& row = ui::row(parent);
		ui::label(row, label);
		ui::label(row, value);
	}

	void panel_gfx_stats(Widget& parent)
	{
		Widget& self = ui::sheet(parent);

		const bgfx::Stats* stats = bgfx::getStats();

		{
			Table& columns = ui::columns(self, carray<float, 2>{ 0.4f, 0.6f });

			double cpu_time = 1000.0f * stats->cpuTimeFrame / (double)stats->cpuTimerFreq;

			double_label(columns, "cpu frame", to_string(cpu_time).c_str());
			double_label(columns, "gpu latency", to_string(stats->maxGpuLatency).c_str());
			double_label(columns, "draw calls", to_string(stats->numDraw).c_str());

			double_label(columns, "backbuffer width", to_string(stats->width).c_str());
			double_label(columns, "backbuffer height", to_string(stats->height).c_str());
		}

		static cstring columns[3] = { "view", "gpu time", "cpu time" };
		Table& table = ui::table(self, { columns, 3 }, {});

		for(int i = 0; i < stats->numViews; ++i)
		{
			const bgfx::ViewStats& view_stats = stats->viewStats[i];
			double gpu_time = 1000.0f * view_stats.gpuTimeElapsed / (double)stats->gpuTimerFreq;
			double cpu_time = 1000.0f * view_stats.cpuTimeElapsed / (double)stats->cpuTimerFreq;

			Widget& row = ui::row(table);
			ui::label(row, view_stats.name);
			ui::label(row, truncate_number(to_string(gpu_time)).c_str());
			ui::label(row, truncate_number(to_string(cpu_time)).c_str());
		}
	}

	SceneViewer& asset_empty_viewer(Widget& parent, Ref object, vec3 offset, float radius)
	{
		static float time = 0.f;
		time += 0.01f;

		SceneViewer& viewer = ui::scene_viewer(parent, vec2(200.f));
		viewer.m_camera.m_eye = radius * 2.5f * Z3;

		quat rotation = axis_angle(Y3, fmod(time, 2.f * c_pi));

		Gnode& scene = viewer.m_scene->begin();
		gfx::node(scene, object, offset, rotation);
		gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
		return viewer;
	}

	SceneViewer& material_viewer(Widget& parent, Material& material)
	{
		SceneViewer& viewer = asset_empty_viewer(parent, Ref(&material), Zero3, 1.f);
		gfx::shape(*viewer.m_scene->m_graph.m_nodes[0], Sphere(), Symbol(Colour::White), 0U, &material);
		return viewer;
	}

	SceneViewer& model_viewer(Widget& parent, Model& model)
	{
		SceneViewer& viewer = asset_empty_viewer(parent, Ref(&model), -model.m_origin, model.m_radius);
		gfx::item(*viewer.m_scene->m_graph.m_nodes[0], model);
		return viewer;
	}

	SceneViewer& particles_viewer(Widget& parent, ParticleGenerator& particles)
	{
		SceneViewer& viewer = asset_empty_viewer(parent, Ref(&particles), Zero3, 1.f); // particles.m_radius
		gfx::particles(*viewer.m_scene->m_graph.m_nodes[0], particles);
		return viewer;
	}

	class DispatchAssetViewer : public Dispatch<SceneViewer&, Widget&>, public Global<DispatchAssetViewer>
	{
	public:
		DispatchAssetViewer()
		{
			dispatch_branch<Material>			(*this, [](Material& material, Widget& parent) -> SceneViewer&				{ return material_viewer(parent, material); });
			dispatch_branch<Model>				(*this, [](Model& model, Widget& parent) -> SceneViewer&					{ return model_viewer(parent, model); });
			dispatch_branch<ParticleGenerator>	(*this, [](ParticleGenerator& generator, Widget& parent) -> SceneViewer&	{ return particles_viewer(parent, generator); });
		}
	};

	SceneViewer& asset_viewer(Widget& parent, Ref asset)
	{
		return DispatchAssetViewer::me.dispatch(asset, parent);
	}

	Widget& asset_item(Widget& parent, cstring icon, cstring name, Ref asset)
	{
		Widget& self = ui::element(parent, asset);
		ui::multi_item(self, carray<cstring, 2>{ icon, name });
		//if(self.selected())
		//	asset_viewer(self, asset);
		if(Widget* tooltip = ui::hoverbox(self, 0.f))
			asset_viewer(*tooltip, asset);
		return self;
	}

	Widget& asset_element(ui::Sequence& sequence, cstring icon, cstring name, Ref asset)
	{
		Widget& self = asset_item(sequence.m_body ? *sequence.m_body : sequence, icon, name, asset);
		ui::multiselect_logic(self, asset, *sequence.m_selection);
		return self;
	}

	void asset_browser(Widget& parent, GfxSystem& gfx_system, std::vector<Ref>& selection)
	{
		Section& self = section(parent, "Assets");

		static bool textures = true;
		static bool programs = true;
		static bool materials = true;
		static bool models = true;
		static bool particles = true;
		static bool prefabs = true;

		ui::toggle(*self.m_toolbar, textures, "tex");
		ui::toggle(*self.m_toolbar, programs, "prg");
		ui::toggle(*self.m_toolbar, materials, "mat");
		ui::toggle(*self.m_toolbar, models, "mdl");
		ui::toggle(*self.m_toolbar, particles, "ptc");
		ui::toggle(*self.m_toolbar, prefabs, "pfb");

		ui::Sequence& sequence = ui::sequence(*self.m_body);
		sequence.m_selection = &selection;

		if(materials)
			for(auto& name_material : gfx_system.materials().m_assets)
				if(!name_material.second->m_builtin)
				{
					asset_element(sequence, "(material)", name_material.first.c_str(), Ref(name_material.second.get()));
				}

		if(programs)
			for(auto& name_program : gfx_system.programs().m_assets)
			{
				Widget& element = ui::element(sequence, Ref(name_program.second.get()));
				ui::multi_item(element, carray<cstring, 2>{ "(program)", name_program.first.c_str() });
			}

		if(models)
			for(auto& name_model : gfx_system.models().m_assets)
			{
				asset_element(sequence, "(model)", name_model.first.c_str(), Ref(name_model.second.get()));
			}

		if(particles)
			for(auto& name_particles : gfx_system.particles().m_assets)
			{
				asset_element(sequence, "(particles)", name_particles.first.c_str(), Ref(name_particles.second.get()));
			}
	}

	void asset_browser(Widget& parent, GfxSystem& gfx_system)
	{
		static std::vector<Ref> selection = {};
		asset_browser(parent, gfx_system, selection);
	}

	void asset_browser(Widget& parent, GfxSystem& gfx_system, Ref& selected)
	{
		static std::vector<Ref> selection = {};
		asset_browser(parent, gfx_system, selection);
		if(selection.size() > 0)
			selected = selection[0];
		else
			selected = {};
	}

	void edit_viewer_filters(Widget& parent, Viewer& viewer)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		Widget& self = ui::sheet(*scroll_sheet.m_body);

		RenderFilters& filters = viewer.m_filters;
		object_edit_expandbox(self, Ref(&filters.m_dof_blur));
		object_edit_expandbox(self, Ref(&filters.m_glow));
		object_edit_expandbox(self, Ref(&filters.m_bcs));
		object_edit_expandbox(self, Ref(&filters.m_tonemap));
	}

#if 0
	void painter_edit(Widget& parent, VisuPainter& painter)
	{
		Widget& self = ui::row(parent);
		ui::label(self, painter.m_name);
		Ref value = &painter.m_enabled;
		value_edit(self, value);
	}

	void painter_panel(Widget& parent, VisuScene& scene)
	{
		Widget& self = section(parent, "Painters");
		for(auto& painter : scene.m_painters)
			painter_edit(self, *painter);
	}

	void edit_gfx_items(Widget& parent, Scene& scene)
	{
		scene.m_pool->iterate_objects<Item>([&](Item& item) {
			object_edit_inline(parent, Ref(&item));
		});
	}
#endif

	void edit_gfx_scenes(Widget& parent, GfxSystem& gfx_system)
	{
		Widget& self = ui::layout(parent);
		UNUSED(gfx_system);
		UNUSED(self);
	}

	void gfx_editor(Widget& parent, GfxSystem& gfx_system)
	{
		enum Modes { SELECT = 1 << 0 };

		static Ref asset = {};

		Section& self = section(parent, "Gfx Editor");
		Widget& sheet = *self.m_body;
		ui::label(sheet, "Editing : ");
		if(ui::modal_button(sheet, sheet, "Select", SELECT))
		{
			Widget& modal = ui::auto_modal(sheet, SELECT, { 800.f, 600.f });
			asset_browser(*modal.m_body, gfx_system, asset);
		}

		if(asset)
		{
			if(type(asset).is<ParticleGenerator>())
				particle_edit(sheet, gfx_system, val<ParticleGenerator>(asset));
		}
	}

	void edit_gfx_system(Widget& parent, GfxSystem& gfx_system)
	{
		Tabber& tabber = ui::tabber(parent);

		if(Widget* stats = ui::tab(tabber, "Profiling"))
			panel_gfx_stats(*stats);

#if 0
		if(Widget* textures = ui::tab(tabber, "Textures"))
			multi_object_edit_container<Texture>(*textures, gfx_system.m_textures);

		if(Widget* programs = ui::tab(tabber, "Programs"))
			multi_object_edit_container<Program>(*programs, gfx_system.m_programs);

		if(Widget* materials = ui::tab(tabber, "Materials"))
			multi_object_edit_container<Material>(*materials, gfx_system.m_materials);

		if(Widget* blocks = ui::tab(tabber, "Blocks"))
			multi_object_edit_container<GfxBlock>(*blocks, gfx_system.m_pipeline->m_gfx_blocks);

#endif

#if 0
		if(Widget* items = ui::tab(tabber, "Items"))
			edit_gfx_items(*items, gfx_system);

		if(Widget* scenes = ui::tab(tabber, "Scenes"))
			edit_gfx_scenes(*scenes, gfx_system);
#endif

		if(Widget* editor = ui::tab(tabber, "Editor"))
			gfx_editor(*editor, gfx_system);

		if(Widget* particles = ui::tab(tabber, "Particle Editor"))
			particle_editor(*particles, gfx_system);
	}

	bool edit_shape(Widget& parent, ShapeVar& shape)
	{
		bool changed = false;

		// @todo: only these shape random distributions are implemented so far
		static std::vector<Type*> shape_types = type_vector<Sphere, SphereRing, Circle, Ring, Rect, Points>();
		//static std::vector<Type*> shape_types = type_vector<Line, Rect, Quad, Polygon, Grid2, Triangle, Circle,
		//													Ring, Ellipsis, Arc, Cylinder, Capsule, Cube, Aabb,
		//													Box, Sphere, SphereRing, Spheroid, Points, ConvexHull>();

		auto type_index = [&](Type* type) { for(size_t i = 0; i < shape_types.size(); ++i) { if(shape_types[i] == type) return i; } return SIZE_MAX; };

		Widget& self = ui::sheet(parent);
		size_t type = type_index(shape.m_shape ? &shape.m_shape->m_type : nullptr);
		if(type_selector(self, type, shape_types))
		{
			shape = ShapeVar(upcast<Shape>(construct(*shape_types[type])));
			changed = true;
		}

		if(shape.m_shape)
		{
			Widget& sheet = ui::widget(self, styles().sheet, &shape.shape());
			changed |= object_edit_columns(sheet, Ref(&shape.shape()));
		}
		return changed;
	}

	void declare_gfx_edit()
	{
		auto nest_mode = [](Type& type, EditNestMode mode)
		{
			g_edit_specs[type.m_id].m_nest_mode[0] = mode;
			g_edit_specs[type.m_id].m_nest_mode[1] = mode;
			g_edit_specs[type.m_id].m_setup = true;
		};

		nest_mode(type<BaseMaterialBlock>(), EditNestMode::Embed);
		nest_mode(type<UnshadedMaterialBlock>(), EditNestMode::Embed);
		nest_mode(type<PbrMaterialBlock>(), EditNestMode::Embed);

		nest_mode(type<MaterialParam<float>>(), EditNestMode::Embed);
		nest_mode(type<MaterialParam<Colour>>(), EditNestMode::Embed);

		nest_mode(type<ShapeVar>(), EditNestMode::Embed);

		{
			DispatchInput& dispatch = DispatchInput::me;
			dispatch_branch<ShapeVar>(dispatch, [](ShapeVar& object, Widget& parent) { return edit_shape(parent, object); });
		}

		{
			DispatchItem& dispatch = DispatchItem::me();
			dispatch_branch<Material>	(dispatch, [](Material& material, Widget& parent) -> Widget&	{ return asset_item(parent, "(material)", material.m_name.c_str(), Ref(&material)); });
			dispatch_branch<Model>		(dispatch, [](Model& model, Widget& parent) -> Widget&			{ return asset_item(parent, "(model)", model.m_name.c_str(), Ref(&model)); });
		}

	}

}

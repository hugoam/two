#include <two/gfx.h>
#include <two/pool.h>
#include <two/geom.h>
#include <two/ui.h>
#include <two/uio.h>
#include <two/gfx.pbr.h>
#include <two/srlz.h>
#include <two/tree.h>
#include <two/gfx.edit.h>
#include <two/math.h>
#include <two/refl.h>
#include <two/gfx.ui.h>
#include <two/infra.h>
#include <two/type.h>


#ifdef TWO_MODULES
module two.gfx-edit;
#else
#endif

namespace two
{
    // Exported types
    
    
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx-edit;
#else
#include <stl/algorithm.h>
#endif

namespace two
{
	void animation_edit(Widget& parent, Mime& animated)
	{
		Widget& self = ui::sheet(parent);

		Table& table = ui::table(self, { "Field", "Value" }, { 0.3f, 0.7f });

		static vector<cstring> animations;
		animations.clear();
		for(Animation* animation : animated.m_anims)
			animations.push_back(animation->m_name.c_str());

		static uint32_t animation = 0;
		if(ui::radio_field(table, "animation", animations, animation, Axis::Y))
			animated.start(animations[animation], true, 0.f, 1.f);

		if(!animated.m_playing.empty())
		{
			AnimPlay& play = animated.m_playing.back();
			ui::slider_field<float>(table, "speed", play.m_speed, { -5.f, 5.f, 0.01f });
			ui::slider_field<float>(table, "timeline", play.m_cursor, { 0.f, play.m_animation->m_length, 0.01f });
		}

		Table& playing = ui::table(self, { "Animation", "Time" }, { 0.6f, 0.4f });
		for(AnimPlay& play : animated.m_playing)
		{
			Widget& row = ui::table_row(playing);
			ui::label(row, play.m_animation->m_name.c_str());
			ui::label(row, to_string(play.m_cursor).c_str());
		}

	}

	void space_axes(Gnode& parent)
	{
		static table<Axis, Colour> colours = { Colour::Red, Colour::Green, Colour::Blue };
		for(Axis axis : { Axis::X, Axis::Y, Axis::Z })
		{
			Gnode& node = gfx::node(parent, to_vec3(axis) * 1.f);
			gfx::shape(node, Cylinder(0.1f, 1.f, axis), Symbol(colours[axis]));
		}
	}

	void double_label(Widget& parent, const string& label, const string& value)
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
			Table& columns = ui::columns(self, { 0.4f, 0.6f });

			double cpu_time = 1000.0f * stats->cpuTimeFrame / (double)stats->cpuTimerFreq;

			double_label(columns, "cpu frame", to_string(cpu_time));
			double_label(columns, "gpu latency", to_string(stats->maxGpuLatency));
			double_label(columns, "draw calls", to_string(stats->numDraw));

			double_label(columns, "backbuffer width", to_string(stats->width));
			double_label(columns, "backbuffer height", to_string(stats->height));
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

		quat rotation = axis_angle(Y3, fmod(time, c_2pi));

		Gnode& scene = viewer.m_scene.begin();
		gfx::node(scene, offset, rotation); // object
		gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);
		return viewer;
	}

	SceneViewer& material_viewer(Widget& parent, Material& material)
	{
		SceneViewer& viewer = asset_empty_viewer(parent, Ref(&material), vec3(0.f), 1.f);
		gfx::shape(*viewer.m_scene.m_graph.m_nodes[0], Sphere(), Symbol(Colour::White), 0U, &material);
		return viewer;
	}

	SceneViewer& model_viewer(Widget& parent, Model& model)
	{
		SceneViewer& viewer = asset_empty_viewer(parent, Ref(&model), -model.m_origin, model.m_radius);
		gfx::item(*viewer.m_scene.m_graph.m_nodes[0], model);
		return viewer;
	}

	SceneViewer& particles_viewer(Widget& parent, Flow& particles)
	{
		SceneViewer& viewer = asset_empty_viewer(parent, Ref(&particles), vec3(0.f), 1.f); // particles.m_radius
		gfx::flows(*viewer.m_scene.m_graph.m_nodes[0], particles);
		return viewer;
	}

	class DispatchAssetViewer : public Dispatch<SceneViewer&, Widget&>, public Global<DispatchAssetViewer>
	{
	public:
		DispatchAssetViewer()
		{
			dispatch_branch<Material>		(*this, +[](Material& material, Widget& parent) -> SceneViewer&			{ return material_viewer(parent, material); });
			dispatch_branch<Model>			(*this, +[](Model& model, Widget& parent) -> SceneViewer&				{ return model_viewer(parent, model); });
			dispatch_branch<Flow>	(*this, +[](Flow& generator, Widget& parent) -> SceneViewer&	{ return particles_viewer(parent, generator); });
		}
	};

	SceneViewer& asset_viewer(Widget& parent, Ref asset)
	{
		return DispatchAssetViewer::me.dispatch(asset, parent);
	}

	Widget& asset_item(Widget& parent, const string& icon, const string& name, Ref asset)
	{
		Widget& self = ui::element(parent, asset);
		ui::multi_item(self, { icon.c_str(), name.c_str() });
		//if(self.selected())
		//	asset_viewer(self, asset);
		if(Widget* tooltip = ui::hoverbox(self, 0.f))
			asset_viewer(*tooltip, asset);
		return self;
	}

	Widget& asset_element(ui::Sequence& sequence, const string& icon, const string& name, Ref asset)
	{
		Widget& self = asset_item(sequence.m_body ? *sequence.m_body : sequence, icon, name, asset);
		ui::multiselect_logic(self, asset, *sequence.m_selection);
		return self;
	}

	void asset_browser(Widget& parent, GfxSystem& gfx, vector<Ref>& selection)
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
			for(Material* material : gfx.materials().m_vector)
				if(!material->m_builtin)
				{
					asset_element(sequence, "(material)", material->m_name, Ref(material));
				}

		if(programs)
			for(Program* program : gfx.programs().m_vector)
			{
				Widget& element = ui::element(sequence, Ref(program));
				ui::multi_item(element, { "(program)", program->m_name.c_str() });
			}

		if(models)
			for(Model* model : gfx.models().m_vector)
			{
				asset_element(sequence, "(model)", model->m_name, Ref(model));
			}

		if(particles)
			for(Flow* particle : gfx.flows().m_vector)
			{
				asset_element(sequence, "(particles)", particle->m_name, Ref(particle));
			}
	}

	void asset_browser(Widget& parent, GfxSystem& gfx)
	{
		static vector<Ref> selection = {};
		asset_browser(parent, gfx, selection);
	}

	void asset_browser(Widget& parent, GfxSystem& gfx, Ref& selected)
	{
		static vector<Ref> selection = {};
		asset_browser(parent, gfx, selection);
		if(selection.size() > 0)
			selected = selection[0];
		else
			selected = {};
	}

	void edit_viewer_filters(Widget& parent, Viewer& viewer)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		Widget& self = ui::sheet(*scroll_sheet.m_body);
		UNUSED(self); UNUSED(viewer);

		Entt& filters = viewer.m_viewport;
		object_edit_expandbox(self, Ref(&filters.comp<DofBlur>()));
		object_edit_expandbox(self, Ref(&filters.comp<Glow>()));
		object_edit_expandbox(self, Ref(&filters.comp<BCS>()));
		object_edit_expandbox(self, Ref(&filters.comp<Tonemap>()));
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
		scene.m_pool->pool<Item>().iterate([&](Item& item) {
			object_edit_inline(parent, Ref(&item));
		});
	}
#endif

	void edit_gfx_scenes(Widget& parent, GfxSystem& gfx)
	{
		Widget& self = ui::layout(parent);
		UNUSED(gfx);
		UNUSED(self);
	}

	void gfx_editor(Widget& parent, GfxSystem& gfx)
	{
		enum Modes { SELECT = 1 << 0 };

		static Ref asset = {};

		Section& self = section(parent, "Gfx Editor");
		Widget& sheet = *self.m_body;
		ui::label(sheet, "Editing : ");
		if(ui::modal_button(sheet, sheet, "Select", SELECT))
		{
			Widget& modal = ui::auto_modal(sheet, SELECT, { 800.f, 600.f });
			asset_browser(*modal.m_body, gfx, asset);
		}

		if(asset)
		{
			if(type(asset).is<Flow>())
				particle_edit(sheet, gfx, val<Flow>(asset));
		}
	}

	void edit_gfx(Widget& parent, GfxSystem& gfx)
	{
		Tabber& tabber = ui::tabber(parent);

		if(Widget* stats = ui::tab(tabber, "Profiling"))
			panel_gfx_stats(*stats);

#if 0
		if(Widget* textures = ui::tab(tabber, "Textures"))
			multi_object_edit_container<Texture>(*textures, gfx.m_textures);

		if(Widget* programs = ui::tab(tabber, "Programs"))
			multi_object_edit_container<Program>(*programs, gfx.m_programs);

		if(Widget* materials = ui::tab(tabber, "Materials"))
			multi_object_edit_container<Material>(*materials, gfx.m_materials);

		if(Widget* blocks = ui::tab(tabber, "Blocks"))
			multi_object_edit_container<GfxBlock>(*blocks, gfx.m_renderer.m_gfx_blocks);

#endif

#if 0
		if(Widget* items = ui::tab(tabber, "Items"))
			edit_gfx_items(*items, gfx);

		if(Widget* scenes = ui::tab(tabber, "Scenes"))
			edit_gfx_scenes(*scenes, gfx);
#endif

		if(Widget* editor = ui::tab(tabber, "Editor"))
			gfx_editor(*editor, gfx);

		if(Widget* particles = ui::tab(tabber, "Particle Editor"))
			particle_editor(*particles, gfx);
	}

	export_ inline Var construct(Type& type)
	{
		return meta(type).m_empty_var;
	}

	export_ template <class T>
	T& upcast(Ref value) { Ref base = cls(value).upcast(value, type<T>()); return val<T>(base); }

	bool edit_shape(Widget& parent, ShapeVar& shape)
	{
		bool changed = false;

		// @todo: only these shape random distributions are implemented so far
		static vector<Type*> shape_types = type_vector<Sphere, SphereRing, Circle, Ring, Rect, Points>();
		//static vector<Type*> shape_types = type_vector<Line, Rect, Quad, Polygon, Grid2, Triangle, Circle,
		//													Ring, Ellipsis, Arc, Cylinder, Capsule, Cube, Aabb,
		//													Box, Sphere, SphereRing, Spheroid, Points, ConvexHull>();

		auto type_index = [&](Type* type) -> uint32_t { for(size_t i = 0; i < shape_types.size(); ++i) { if(shape_types[i] == type) return uint32_t(i); } return UINT32_MAX; };

		Widget& self = ui::sheet(parent);
		uint32_t type = type_index(shape.m_shape ? &shape.m_shape->m_type : nullptr);
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

		nest_mode(type<MaterialBase>(), EditNestMode::Embed);
		nest_mode(type<MaterialSolid>(), EditNestMode::Embed);
		nest_mode(type<MaterialPbr>(), EditNestMode::Embed);

		nest_mode(type<MaterialParam<float>>(), EditNestMode::Embed);
		nest_mode(type<MaterialParam<Colour>>(), EditNestMode::Embed);

		nest_mode(type<ShapeVar>(), EditNestMode::Embed);

		{
			DispatchInput& dispatch = DispatchInput::me;
			dispatch_branch<ShapeVar>(dispatch, +[](ShapeVar& object, Widget& parent) { return edit_shape(parent, object); });
		}

		{
			DispatchItem& dispatch = DispatchItem::me();
			dispatch_branch<Material>	(dispatch, +[](Material& material, Widget& parent) -> Widget&	{ return asset_item(parent, "(material)", material.m_name.c_str(), Ref(&material)); });
			dispatch_branch<Model>		(dispatch, +[](Model& model, Widget& parent) -> Widget&			{ return asset_item(parent, "(model)", model.m_name.c_str(), Ref(&model)); });
		}

	}

}


#ifdef TWO_MODULES
module two.gfx-edit;
#else
#endif

namespace two
{
	struct ParticleEditorState : public NodeState
	{
		ParticleEditorState() {}
		Flow m_particles;
	};

	void cube_test(Gnode& parent)
	{
		Gnode& self = gfx::node(parent);
		gfx::shape(self, Cube(1.f), Symbol());
	}

	void particle_editor_viewer(Widget& parent, Flow& particles)
	{
		SceneViewer& viewer = ui::scene_viewer(parent, vec2(500.f));
		ui::orbit_controller(viewer);

		//viewer.m_clear_colour = Colour::DarkGrey;
		//viewer.m_camera.set_isometric(SOUTH, vec3(0.f));

		Gnode& scene = viewer.m_scene.begin();
		gfx::flows(scene, particles);

		Shape* shape = particles.m_shape.m_shape.get();
		if(shape)
			gfx::shape(scene, *shape, Symbol());

		cube_test(scene);
	}

	enum ParticleEditSwitch
	{
		OPEN_PARTICLES = 1 << 0,
		SAVE_PARTICLES = 1 << 1
	};

	void open_particles(Widget& parent, GfxSystem& system, Flow& generator)
	{
		static string location = "";
		if(select_value(parent, OPEN_PARTICLES, location, true))
		{
			if(file_exists(system.m_resource_path + "/" + location))
			{
				unpack_json_file(Ref(&generator), system.m_resource_path + "/" + location);
			}
		}
	}

	void save_particles(Widget& parent, GfxSystem& system, Flow& generator)
	{
		static string destination = "";
		if(select_value(parent, SAVE_PARTICLES, destination, true))
		{
			pack_json_file(Ref(&generator), system.m_resource_path + "/" + destination);
		}
	}

	void particle_edit(Widget& parent, GfxSystem& system, Flow& generator)
	{
		Section& self = section(parent, "Particle Editor");

		object_edit(*self.m_body, Ref(&generator));
		particle_editor_viewer(self, generator);

		if(ui::modal_button(self, *self.m_toolbar, "Open", OPEN_PARTICLES))
			open_particles(self, system, generator);
		if(ui::modal_button(self, *self.m_toolbar, "Save", SAVE_PARTICLES))
			save_particles(self, system, generator);
	}

	void particle_editor(Widget& parent, GfxSystem& system)
	{
		Widget& self = ui::sheet(parent);
		ParticleEditorState& state = self.state<ParticleEditorState>();
		particle_edit(self, system, state.m_particles);
	}
}


#ifdef TWO_MODULES
module two.gfx-edit;
#else
#include <stl/algorithm.h>
//#include <infra/ToString.h>
#endif

namespace two
{
#if 0
	TreeNode& prefab_node(Widget& parent, PrefabNode* parent_node, PrefabNode& node, PrefabNode*& selected)
	{
		TreeNode& self = ui::tree_node(parent, to_string(var(node.m_prefab_type)).c_str());

		if(self.m_header->activated())
			selected = &node;

		self.m_header->set_state(ACTIVE, selected == &node);

		if(ui::button(*self.m_header, "+").activated())
		{
			node.m_nodes.push_back({});
			selected = &node.m_nodes.back();
		}
		if(ui::button(*self.m_header, "X").activated())
		{
			if(selected == &node)
				selected = parent_node;
			vector_remove_object(parent_node->m_nodes, node);
			return self;
		}

		for(PrefabNode& child : node.m_nodes)
			prefab_node(*self.m_body, &node, child, selected);

		return self;
	}

	void prefab_structure(Widget& parent, PrefabNode& node, PrefabNode*& selected)
	{
		Section& self = section(parent, "Prefab Graph");
		prefab_node(*self.m_body, nullptr, node, selected);
	}

	Widget& prefab_inspector(Widget& parent, PrefabNode& node)
	{
		Section& self = section(parent, "Prefab Inspector");

		static cstring types[6] = { "None", "Item", "Model", "Shape", "Flare", "Light" };
		static vector<Function*> functions = { nullptr, &function(gfx::item), &function(gfx::model), &function(gfx::shape), &function(&gfx::particles), &function(gfx::light) };

		static cstring columns[2] = { "field", "value" };
		Widget& table = ui::table(*self.m_body, { columns, 2 }, {});

		Widget& row = ui::row(table);
		ui::label(row, "type");
		if(ui::dropdown_input(row, { types, 6 }, (uint32_t&)node.m_prefab_type))
			node.m_call = { *functions[size_t(node.m_prefab_type)] };

		object_edit(table, Ref(&node.m_transform), EditorHint::Rows);
		if(node.m_call.m_callable)
			call_edit(table, node.m_call);

		return self;
	}

	void prefab_edit(Widget& parent, GfxSystem& gfx, PrefabNode& node, PrefabNode*& selected)
	{
		UNUSED(gfx);
		Widget& self = ui::sheet(parent);

		prefab_structure(self, node, selected);

		if(selected)
			prefab_inspector(self, *selected);
	}
#endif
}

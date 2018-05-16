//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Ui/GfxEdit.h>

#include <uio/Unode.h>
#include <ui/Structs/Container.h>
#include <ui/Input.h>

#include <obj/Vector.h>

#include <uio/Edit/Inspector.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Value.h>

#include <gfx/Blocks/Shadow.h>
#include <gfx/Widget/Viewer.h>
#include <gfx/Ui/ParticleEdit.h>
#include <gfx/Gfx.h>
#include <gfx/Animated.h>

#include <geom/Symbol.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Aabb.h>

namespace mud
{
	void animation_edit(Widget& parent, Animated& animated)
	{
		Widget& self = ui::sheet(parent);

		Table& table = ui::table(self, carray<cstring, 2>{ "Field", "Value" }, carray<float, 2>{ 0.3f, 0.7f });

		static std::vector<cstring> animations;
		animations.clear();
		for(Animation& animation : animated.m_rig.m_animations)
			animations.push_back(animation.m_name);

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
			ui::label(row, play.m_animation->m_name);
			ui::label(row, to_string(play.m_cursor).c_str());
		}

	}

	// @kludge FUCK THIS
	template <> MUD_GFX_EXPORT Type& type<ValueTrack<vec3>>();
	template <> MUD_GFX_EXPORT Type& type<ValueTrack<quat>>();
	template <> MUD_GFX_EXPORT Type& type<ValueTrack<float>>();
	template <> MUD_GFX_EXPORT Type& type<ValueTrack<uint32_t>>();
	template <> MUD_GFX_EXPORT Type& type<ValueTrack<Colour>>();

	void space_axes(Gnode& parent)
	{
		static Colour colours[3] = { Colour::Red, Colour::Green, Colour::Blue };
		for(Axis axis : { Axis::X, Axis::Y, Axis::Z })
		{
			Gnode& node = gfx::node(parent, {}, to_vec3(axis) * 1.f);
			gfx::shape(node, Cylinder(0.1f, 1.f, axis), Symbol(Colour::None, colours[size_t(axis)]));
		}
	}

	void debug_draw_light_slices(Gnode& parent, Light& light, LightShadow& shadow)
	{
		UNUSED(light);
		for(size_t i = 0; i < shadow.m_slices.size(); ++i)
		{
			Frustum& frustum = shadow.m_frustum_slices[i].m_frustum;
			gfx::node_shape(parent, Box({ &frustum.m_corners[0], 8 }), Symbol(), Zero3);
			if(false)
				gfx::node_shape(parent, Spheroid(frustum.m_radius), Symbol(Colour::DarkGrey), frustum.m_center);

			mat4 inverse_light = inverse(shadow.m_slices[i].m_transform);

			gfx::node_shape(parent, Spheroid(1.f), Symbol(), vec3(inverse_light[3]));

			Box light_bounds = Box(min_max_to_aabb(shadow.m_slices[i].m_light_bounds.min, shadow.m_slices[i].m_light_bounds.max));

			for(vec3& vertex : light_bounds.m_vertices)
				vertex = vec3(inverse_light * vec4(vertex, 1.f));

			gfx::node_shape(parent, light_bounds, Symbol(Colour::Pink), Zero3);
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

#if 0
		uint16_t numDynamicIndexBuffers;  //!< Number of used dynamic index buffers.
		uint16_t numDynamicVertexBuffers; //!< Number of used dynamic vertex buffers.
		uint16_t numFrameBuffers;         //!< Number of used frame buffers.
		uint16_t numIndexBuffers;         //!< Number of used index buffers.
		uint16_t numOcclusionQueries;     //!< Number of used occlusion queries.
		uint16_t numPrograms;             //!< Number of used programs.
		uint16_t numShaders;              //!< Number of used shaders.
		uint16_t numTextures;             //!< Number of used textures.
		uint16_t numUniforms;             //!< Number of used uniforms.
		uint16_t numVertexBuffers;        //!< Number of used vertex buffers.
		uint16_t numVertexDecls;          //!< Number of used vertex declarations.
#endif

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

	void edit_viewer_filters(Widget& parent, Viewer& viewer)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		Widget& self = ui::sheet(*scroll_sheet.m_body);

		RenderFilters& filters = viewer.m_filters;
		object_edit_expandbox(self, &filters.m_dof_blur);
		object_edit_expandbox(self, &filters.m_glow);
		object_edit_expandbox(self, &filters.m_bcs);
		object_edit_expandbox(self, &filters.m_tonemap);
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
#endif

#if 0
	void edit_gfx_items(Widget& parent, GfxSystem& system)
	{
		VecPool<Item>* pool = system.m_object_pool.pool<Item>().m_vec_pool.get();
		for(; pool; pool = pool->m_next.get())
			for(Item* item : pool->m_objects)
				object_edit_inline(parent, item);
	}
#endif 

	void edit_gfx_scenes(Widget& parent, GfxSystem& system)
	{
		Widget& self = ui::layout(parent);
		UNUSED(system);
		UNUSED(self);
	}

	void edit_gfx_system(Widget& parent, GfxSystem& system)
	{
		Tabber& tabber = ui::tabber(parent);

		if(Widget* stats = ui::tab(tabber, "Profiling"))
			panel_gfx_stats(*stats);

#if 0
		if(Widget* textures = ui::tab(tabber, "Textures"))
			multi_object_edit_container<Texture>(*textures, system.m_textures);

		if(Widget* programs = ui::tab(tabber, "Programs"))
			multi_object_edit_container<Program>(*programs, system.m_programs);

		if(Widget* materials = ui::tab(tabber, "Materials"))
			multi_object_edit_container<Material>(*materials, system.m_materials);

		if(Widget* blocks = ui::tab(tabber, "Blocks"))
			multi_object_edit_container<GfxBlock>(*blocks, system.m_pipeline->m_gfx_blocks);

#endif

#if 0
		if(Widget* items = ui::tab(tabber, "Items"))
			edit_gfx_items(*items, system);

		if(Widget* scenes = ui::tab(tabber, "Scenes"))
			edit_gfx_scenes(*scenes, system);
#endif

		if(Widget* particles = ui::tab(tabber, "Particle Editor"))
			particle_editor(*particles, system);
	}

	bool edit_shape(Widget& parent, ShapeVar& shape)
	{
		bool changed = false;
		static std::vector<Type*> shape_types = type_vector<Line, Rect, Quad, Polygon, Grid2, Triangle, Circle,
															Ring, Ellipsis, Arc, Cylinder, Capsule, Cube, Aabb, 
															Box, Sphere, SphereRing, Spheroid, Points, ConvexHull>();

		Widget& self = ui::sheet(parent);
		Type* type = shape.m_shape ? &shape.m_shape->m_type : nullptr;
		Type* new_type = type_selector(self, type, shape_types);

		if(new_type != type)
		{
			shape = ShapeVar(upcast<Shape>(construct(*new_type)));
			changed = true;
		}

		if(shape.m_shape)
		{
			Shape& shape_ref = shape;
			changed |= object_edit(self, &shape_ref);
		}
		return changed;
	}

	void declare_gfx_edit()
	{
		DispatchInput& dispatch = DispatchInput::me();
		dispatch_branch<ValueTrack<float>>(dispatch, [](ValueTrack<float>& value, Widget& parent) { return value_track_edit<float>(parent, value); });
		dispatch_branch<ValueTrack<uint32_t>>(dispatch, [](ValueTrack<uint32_t>& value, Widget& parent) { return value_track_edit<uint32_t>(parent, value); });
		dispatch_branch<ValueTrack<vec3>>(dispatch, [](ValueTrack<vec3>& value, Widget& parent) { return value_track_edit<vec3>(parent, value); });
		dispatch_branch<ValueTrack<quat>>(dispatch, [](ValueTrack<quat>& value, Widget& parent) { return value_track_edit<quat>(parent, value); });
		dispatch_branch<ValueTrack<Colour>>(dispatch, [](ValueTrack<Colour>& value, Widget& parent) { return value_track_edit<Colour>(parent, value); });

		dispatch_branch<ShapeVar>(dispatch, [](ShapeVar& object, Widget& parent) { return edit_shape(parent, object); });
	}

}

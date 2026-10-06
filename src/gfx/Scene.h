//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Graph.h>
#include <gfx/Handles.h>
#include <gfx/Texture.h>

#include <bgfx/bgfx.h>

namespace two
{
	export_ struct refl_ Sun
	{
		attr_ float azimuth;
		attr_ float elevation;
		attr_ Colour m_colour = { 0.8f, 0.8f, 0.0f };
		attr_ float m_intensity = 0.f;
	};

	export_ struct refl_ Radiance
	{
		attr_ gpu_ Colour m_colour = Colour::White;
		attr_ gpu_ float m_energy = 1.0f;
		attr_ gpu_ Colour m_ambient = Colour::Black;
		attr_ Texture* m_texture = nullptr;
		attr_ Texture* m_filtered = nullptr;
		attr_ bool m_filter = true;
		bool m_preprocessed = false;
	};

	export_ enum class refl_ BackgroundMode : unsigned int
	{
		None,
		Panorama,
		Radiance,
		Custom
	};

	export_ struct refl_ Background
	{
		attr_ BackgroundMode m_mode = BackgroundMode::None;
		attr_ Colour m_colour = Colour::Black;
		attr_ Program* m_custom_program = nullptr;
		attr_ Texture* m_texture = nullptr;
		using CustomRender = void(*)(GfxSystem&, Render&); CustomRender m_custom_function;
	};

	export_ struct refl_ Skylight
	{
		attr_ bool m_enabled = false;
		attr_ float m_intensity = 1.f;
		attr_ vec3 m_position = vec3(0.f, 1.f, 0.f);
		attr_ gpu_ vec3 m_direction;
		attr_ gpu_ Colour m_color;
		attr_ gpu_ Colour m_ground;
	};

	export_ struct refl_ Fog
	{
		attr_ bool m_enabled = false;
		attr_ gpu_ float m_density = 0.01f;
		attr_ gpu_ Colour m_colour = Colour::White;

		attr_ gpu_ bool m_depth = false;
		attr_ gpu_ float m_depth_begin = 0.f;
		attr_ gpu_ float m_depth_end = 0.f;
		attr_ gpu_ float m_depth_curve = 1.f;

		attr_ gpu_ bool m_height = false;
		attr_ gpu_ float m_height_min = 0.f;
		attr_ gpu_ float m_height_max = 1.f;
		attr_ gpu_ float m_height_curve = 0.1f;

		attr_ gpu_ bool m_transmit = false;
		attr_ gpu_ float m_transmit_curve = 1.f;
	};

	export_ struct refl_ Zone
	{
		attr_ Background m_background;
		attr_ Radiance m_radiance;
		attr_ Sun m_sun;
		attr_ Skylight m_skylight;
		attr_ Fog m_fog;
	};

	class Shot;

	// the scene is the graph of its nodes, the root of which is m_graph
	export_ class refl_ TWO_GFX_EXPORT Scene : public PooledGraph<Gnode>
	{
	public:
		constr_ Scene(GfxSystem& gfx);
		~Scene();

		GfxSystem& m_gfx;

		object<ImmediateDraw> m_immediate;
		object<ParticleSystem> m_particle_system;
		object<PassJobs> m_pass_jobs;

		attr_ uint32_t m_index;
		attr_ Gnode m_graph;

		SoundManager* m_sound_manager = nullptr;
		// the node of the transform each node's objects are attached to, by node index: null until a node without one of its own is asked for it
		TNodeArray<Node3Handle>& m_attach;
		attr_ Zone m_env;
		attr_ Ref m_user;

		// the top-level node of the graph whose objects the scene renders: the root of the graph
		uint32_t m_render_tree = 0;

		meth_ Gnode begin();
		meth_ void update();

		// visits the objects of a type of the scene's tree, with their index in their store
		template <class T, class T_Func>
		inline void iterate(T_Func func) { PooledGraph<Gnode>::template iterate<T>(m_render_tree, func); }

		void debug_items(Render& render);

		vector<Sound*> m_orphan_sounds;
	};

	export_ TWO_GFX_EXPORT void cull_items(Scene& scene, const Plane6& planes, vector<ItemIndex>& items);

	export_ TWO_GFX_EXPORT void gather_items(Scene& scene, const Camera& camera, vector<ItemIndex>& items);
	export_ TWO_GFX_EXPORT void gather_occluders(Scene& scene, const Camera& camera, vector<ItemIndex>& occluders);
	export_ TWO_GFX_EXPORT void gather_lights(Scene& scene, vector<LightIndex>& lights);

	export_ TWO_GFX_EXPORT void gather_render(Scene& scene, Render& render);
}

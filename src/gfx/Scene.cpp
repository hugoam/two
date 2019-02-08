//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
#include <tree/Graph.hpp>
#include <math/Timer.h>
#include <pool/ObjectPool.hpp>
#include <geom/Geom.hpp>
#include <geom/Intersect.h>
#include <geom/Shapes.h>
#include <gfx/Types.h>
#include <gfx/Scene.h>
#include <gfx/Renderer.h>
#include <gfx/Item.h>
#include <gfx/Frustum.h>
#include <gfx/Camera.h>
#include <gfx/Shot.h>
#include <gfx/Particles.h>
#include <gfx/Animated.h>
#include <gfx/Draw.h>
#include <gfx/Model.h>
#include <gfx/Pipeline.h>
#include <gfx/GfxSystem.h>
#endif

#define DEBUG_ITEMS 0

namespace mud
{
	Scene::Scene(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_immediate(oconstruct<ImmediateDraw>(gfx_system.fetch_material("immediate", "unshaded")))
		, m_pass_jobs(oconstruct<PassJobs>())
		, m_graph(*this)
		, m_root_node(this)
	{
		m_environment.m_radiance.m_colour = Colour::White;//{ 0.35f, 0.33f, 0.3f, 1.f };
		m_environment.m_radiance.m_energy = 0.3f;
		m_environment.m_radiance.m_ambient = 0.7f;

		m_pool = oconstruct<ObjectPool>();
		m_pool->create_pool<Particles>(1024);

		m_particle_system = oconstruct<ParticleSystem>(gfx_system, m_pool->pool<Particles>());
	}

	Scene::~Scene()
	{}

	void Scene::update()
	{
		static Clock clock;
		float timestep = float(clock.step());

		m_pool->pool<Animated>().iterate([=](Animated& animated)
		{
			animated.advance(timestep);
		});

		m_pool->pool<Item>().iterate([=](Item& item)
		{
			item.update();
		});

		for(size_t i = 0; i < size_t(PassType::Count); ++i)
			m_pass_jobs->m_jobs[i].clear();
	}

	Gnode& Scene::begin()
	{
		this->update();
		m_immediate->begin();
		return m_graph.begin(true);
	}

	void Scene::debug_items(Render& render)
	{
		mat4 identity = bxidentity();
		bool debug = render.m_target != nullptr;
		if(debug)
			for(Item* item : render.m_shot->m_items)
			{
				Colour colour = { 1.f, 0.f, 1.f, 0.15f };
				Cube cube = Cube(item->m_aabb);
				m_immediate->shape(identity, { Symbol::wire(colour, true), &cube, OUTLINE });
				//m_immediate->draw(item->m_node->m_transform, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
			}
	}

	void cull_items(Scene& scene, const Plane6& planes, vector<Item*>& items)
	{
		//items.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0
			&& frustum_aabb_intersection(planes, item.m_aabb))
			{
				items.push_back(&item);
			}
		});
	}

	void gather_items(Scene& scene, const Camera& camera, vector<Item*>& items)
	{
		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);

		Plane near_plane = camera.near_plane();

		vec4 lod_levels = camera.m_far * vec4{ 0.02f, 0.3f, 0.6f, 0.8f };

		//items.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0)
			{
				if(!frustum_aabb_intersection(planes, item.m_aabb))
					return;

				float depth = distance(near_plane, item.m_aabb.m_center);

				vec4 comparison = vec4(greater(vec4(depth), lod_levels));
				float index = dot(vec4(1.f), comparison);
				uint8_t lod = uint8_t(min(index, 3.f));

				bool has_lod = (item.m_flags & (ItemFlag::Lod0 << lod)) != 0;
				if(has_lod)
				{
					item.m_depth = depth;
					items.push_back(&item);
				}
			}
		});
	}

	void gather_occluders(Scene& scene, const Camera& camera, vector<Item*>& occluders)
	{
		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);

		//occluders.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Occluder) != 0
			&& frustum_aabb_intersection(planes, item.m_aabb))
			{
				occluders.push_back(&item);
			}
		});
	}

	void gather_lights(Scene& scene, vector<Light*>& lights)
	{
		//lights.reserve(m_pool->pool<Light>().size());
		scene.m_pool->pool<Light>().iterate([&](Light& light)
		{
			if(light.m_visible)
			{
				light.m_shot_index = lights.size();
				lights.push_back(&light);
			}
		});
	}

	void gather_render(Scene& scene, Render& render)
	{
		gather_items(scene, render.m_camera, render.m_shot->m_items);
		gather_occluders(scene, render.m_camera, render.m_shot->m_occluders);
		gather_lights(scene, render.m_shot->m_lights);

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, render.m_shot->m_items));

		render.m_environment = &scene.m_environment;
		render.m_shot->m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}
}

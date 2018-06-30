//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <math/Timer.h>
#include <pool/ObjectPool.h>
#include <geom/Intersect.h>
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
#include <gfx/Pipeline.h>
#include <gfx/GfxSystem.h>
#endif

namespace mud
{
	Scene::Scene(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_immediate(make_object<ImmediateDraw>(gfx_system.fetch_material("immediate", "unshaded")))
		, m_pass_jobs(make_object<PassJobs>())
		, m_graph(*this)
		, m_root_node(this)
	{
		m_environment.m_radiance.m_colour = Colour::White;//{ 0.35f, 0.33f, 0.3f, 1.f };
		m_environment.m_radiance.m_energy = 0.3f;
		m_environment.m_radiance.m_ambient = 0.7f;

		m_pool = make_object<ObjectPool>();
		m_pool->create_pool<Node3>();
		m_pool->create_pool<Item>();
		m_pool->create_pool<Animated>();
		m_pool->create_pool<Light>();
		m_pool->create_pool<Camera>();
		m_pool->create_pool<Particles>(1024);

		m_particle_system = make_object<ParticleSystem>(gfx_system, m_pool->pool<Particles>());
	}

	Scene::~Scene()
	{}

	void Scene::update()
	{
		static Clock clock;
		float timestep = float(clock.step());

		VecPool<Animated>* animateds = m_pool->pool<Animated>().m_vec_pool.get();
		for(; animateds; animateds = animateds->m_next.get())
			for(Animated* animated : animateds->m_objects)
				animated->advance(timestep);

		for(size_t i = 0; i < size_t(PassType::Count); ++i)
			m_pass_jobs->m_jobs[i].clear();
	}

	Gnode& Scene::begin()
	{
		this->update();
		return m_graph.begin();
	}

	void Scene::gather_render(Render& render)
	{
		Plane6 planes = frustum_planes(render.m_camera.m_projection, render.m_camera.m_transform);

		Plane near_plane = render.m_camera.near_plane();

		vec4 lod_levels = render.m_camera.m_far * vec4{ 0.02f, 0.3f, 0.6f, 0.8f };

		//render.m_shot->m_items.reserve(m_pool->pool<Item>().m_vec_pool.size());

		VecPool<Item>* items = m_pool->pool<Item>().m_vec_pool.get();
		for(; items; items = items->m_next.get())
			for(Item* item : items->m_objects)
				if(item->m_visible && item->m_cast_shadows != ItemShadow::OnlyShadow)
				{
					float depth = plane_distance_to(near_plane, item->m_node.m_position);

					vec4 comparison = vec4(greater(vec4(depth), lod_levels));
					float index = dot(vec4(1.f), comparison);
					uint8_t lod = uint8_t(min(index, 3.f));

					bool has_lod = (item->m_flags & (ITEM_LOD_0 << lod)) != 0;
					if(frustum_aabb_intersection(planes, item->m_aabb) && has_lod)
					{
						item->m_depth = depth;
						render.m_shot->m_items.push_back(item);
					}
				}

		//render.m_shot->m_lights.reserve(m_shot->m_lights.size());
		VecPool<Light>* lights = m_pool->pool<Light>().m_vec_pool.get();
		for(; lights; lights = lights->m_next.get())
			for(Light* light : lights->m_objects)
				if(light->m_visible)
				{
					render.m_shot->m_lights.push_back(light);
				}

#if  0
		render.m_shot->m_gi_probes.reserve(m_shot->m_gi_probes.size());
		VecPool<GIProbe>* probes = m_pool->pool<GIProbe>().m_vec_pool.get();
		for(; probes; probes = probes->m_next.get())
			for(GIProbe* probe : probes->m_objects)
			{
				render.m_shot->m_gi_probes.push_back(gi_probe);
				gi_probe->m_dirty = true;
			}

		VecPool<ReflectionProbe>* probes = m_pool->pool<ReflectionProbe>().m_vec_pool.get();
		for(; probes; probes = probes->m_next.get())
			for(ReflectionProbe* probe : probes->m_objects)
				if(probe->m_visible)
				{
					render.m_shot->m_reflection_probes.push_back(probe);
					probe->m_dirty = true; // force dirty for now
				}
#endif

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, to_array(render.m_shot->m_items)));

		render.m_environment = &m_environment;
		render.m_shot->m_immediate = { m_immediate.get() };
	}
}

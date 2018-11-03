//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <tree/Node.inl.h>
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
#include <gfx/Model.h>
#include <gfx/Pipeline.h>
#include <gfx/GfxSystem.h>
// @kludge fix this dependency inversion
#include <gfx-pbr/Types.h>
#include <gfx-pbr/VoxelGI.h>
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

		m_pool->iterate_objects<Animated>([=](Animated& animated)
		{
			animated.advance(timestep);
		});

		m_pool->iterate_objects<Item>([=](Item& item)
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
		return begin_node<Gnode>(m_graph, true);
	}

	void Scene::cull_items(const Plane6& planes, std::vector<Item*>& items)
	{
		//render.m_shot->m_items.reserve(m_pool->pool<Item>().m_vec_pool.size());

		m_pool->iterate_objects<Item>([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0
			&& frustum_aabb_intersection(planes, item.m_aabb))
			{
				items.push_back(&item);
			}
		});
	}

	void Scene::gather_items(const Camera& camera, std::vector<Item*>& items)
	{
		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);

		Plane near_plane = camera.near_plane();

		vec4 lod_levels = camera.m_far * vec4{ 0.02f, 0.3f, 0.6f, 0.8f };

		//items.reserve(m_pool->pool<Item>().size());
		m_pool->iterate_objects<Item>([&](Item& item)
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

	void Scene::gather_lights(std::vector<Light*>& lights)
	{
		//lights.reserve(m_pool->pool<Light>().size());
		m_pool->iterate_objects<Light>([&](Light& light)
		{
			if(light.m_visible)
			{
				light.m_shot_index = lights.size();
				lights.push_back(&light);
			}
		});
	}

	void Scene::gather_gi_probes(std::vector<GIProbe*>& gi_probes)
	{
		//gi_probes.reserve(m_pool->pool<GIProbe>().size());
		m_pool->iterate_objects<GIProbe>([&](GIProbe& gi_probe)
		{
			gi_probes.push_back(&gi_probe);
		});
	}

#if  0
	void Scene::gather_reflection_probes(std::vector<ReflectionProbe*>& reflection_probes)
	{
		m_pool->iterate_objects<ReflectionProbe>([&](ReflectionProbe& probe)
		{
			if(probe.m_visible)
			{
				reflection_probes.push_back(probe);
				probe.m_dirty = true; // force dirty for now
			}
		});
	}
#endif

	void Scene::gather_render(Render& render)
	{
		this->gather_items(render.m_camera, render.m_shot->m_items);
		this->gather_lights(render.m_shot->m_lights);
		this->gather_gi_probes(render.m_shot->m_gi_probes);
		//this->gather_reflection_probes(render.m_shot->m_reflection_probes);

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, to_array(render.m_shot->m_items)));

		render.m_environment = &m_environment;
		render.m_shot->m_immediate = { m_immediate.get() };
	}
}

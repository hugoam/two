//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <infra/ToString.h>
#include <math/Vec.hpp>
#include <geom/Shapes.h>
#include <gfx/Shot.h>
#include <gfx/Item.h>
#include <gfx/Viewport.h>
#include <gfx/Scene.h>
#include <gfx/Camera.h>
#include <gfx/Froxel.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Lighting.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/Gpu/Light.hpp>
#include <gfx-pbr/Gpu/Zone.hpp>
#endif

#include <cstring>

#include <cstdio>

namespace mud
{
	GpuState<Radiance> GpuState<Radiance>::me;
	GpuState<Skylight> GpuState<Skylight>::me;
	GpuState<Fog> GpuState<Fog>::me;
	GpuState<Zone> GpuState<Zone>::me;
	GpuState<ZoneLights> GpuState<ZoneLights>::me;

	GpuState<GpuLight> GpuState<GpuLight>::me;

	BlockLight::BlockLight(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockLight>())
	{
		m_options = { "SKY_LIGHT", "FOG" };

		m_defines = {
			{ "MAX_LIGHTS", to_string(c_max_forward_lights)  },
			{ "MAX_SHADOWS", to_string(c_max_shadows) },
		};
	}

	void BlockLight::init_block()
	{
		u_shot.createUniforms();

#if !ZONES_BUFFER
		GpuState<Radiance>::me.init();
		GpuState<Skylight>::me.init();
		GpuState<Fog>::me.init();
#endif

#if !LIGHTS_BUFFER
		GpuState<GpuLight>::me.init();
#endif

#if !ZONES_LIGHTS_BUFFER
		GpuState<ZoneLights>::me.init();
#endif
	}

	void BlockLight::begin_render(Render& render)
	{
		UNUSED(render);

		m_direct_lights.clear();
		for(Light* light : render.m_shot.m_lights)
			if(light->m_type == LightType::Direct)
			{
				m_direct_lights.push_back(light);
			}

		m_direct_light = m_direct_lights.empty() ? nullptr : m_direct_lights[m_direct_light_index];

		this->setup_lights(render, render.m_camera->m_view);
		this->upload_lights(render);
		this->upload_zones(render);

		m_direct_light_index = 0;

		m_direct_light = m_direct_lights.empty() ? nullptr : m_direct_lights[m_direct_light_index];

#ifdef MULTIPLE_DIRECT_LIGHTS
		if(!m_direct_lights.empty())
			m_direct_light = m_direct_lights[m_direct_light_index++];

		if(m_direct_light_index > 0)
			pass.m_bgfx_state |= BGFX_STATE_BLEND_ADD;

		request.num_passes = m_direct_lights.empty() ? 1 : m_direct_lights.size();
#endif
	}

	void BlockLight::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		if(render.m_viewport->m_clustered)
			program.set_option(0, CLUSTERED, true);

		if(render.m_env && render.m_env->m_skylight.m_enabled)
			program.set_option(m_index, SKY_LIGHT, true);

		if(render.m_env && render.m_env->m_fog.m_enabled)
			program.set_option(m_index, FOG, true);
	}

	void BlockLight::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);
#if !ZONES_LIGHTS_BUFFER
		GpuState<ZoneLights>::me.upload(pass.m_index, m_zones[0]);
#endif

#if !ZONES_BUFFER
		GpuState<Zone>::me.upload(pass, render.m_scene->m_env);
#endif

#if !LIGHTS_BUFFER
		GpuState<GpuLight>::me.upload(pass, const_cast<vector<GpuLight>&>(m_gpu_lights));
#endif

#if ZONES_BUFFER
		uint32_t zones = uint32_t(TextureSampler::Zones);
		bgfx::setViewUniform(pass.m_index, u_shot.s_zones, &zones);
#endif

#if LIGHTS_BUFFER
		uint32_t lights = uint32_t(TextureSampler::Lights);
		bgfx::setViewUniform(pass.m_index, u_shot.s_lights, &lights);
#endif

		if(render.m_viewport->m_clustered)
			render.m_viewport->m_clusters->submit(pass);
	}

	void BlockLight::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(element);
		bgfx::Encoder& encoder = *pass.m_encoder;

		if(render.m_viewport->m_clustered)
			render.m_viewport->m_clusters->submit(encoder);

		this->commit_zones(render, pass); //render, pass, render.m_env);
		this->commit_lights(render, pass);

		// set to not render if not first direct pass, depending on cull
	}

	void BlockLight::setup_lights(Render& render, const mat4& view)
	{
		const vec3 skylight = muln(view, normalize(render.m_env->m_skylight.m_position));
		render.m_env->m_skylight.m_direction = skylight;

		span<Light*> lights = render.m_shot.m_lights;
		lights.m_count = min(lights.m_count, size_t(c_max_forward_lights));

		ZoneLights& zone = m_zones[0];
		zone.m_light_counts = vec4(0.f);
		zone.m_shadow_counts = vec4(0.f);

		m_gpu_lights.clear();

		for(size_t index = 0; index < lights.size(); ++index)
		{
			const Light& light = *lights[index];

			const vec3 position = mulp(view, light.m_node->position());
			const float range = light.m_range;
			const vec3 energy = to_vec3(light.m_colour * light.m_energy);
			const vec3 energy2 = to_vec3(to_linear(light.m_colour) * light.m_energy);
			const float specular = light.m_specular;
			const vec3 direction = muln(view, light.m_node->direction());
			const float attenuation = light.m_attenuation;
			const float spot_attenuation = light.m_spot_attenuation;
			const float spot_cutoff = cos(to_radians(light.m_spot_angle));

			m_gpu_lights.push_back({ position, range, energy, specular, direction, attenuation, spot_attenuation, spot_cutoff });

			float& light_type_count = zone.m_light_counts[size_t(light.m_type)];
			zone.m_light_indices[size_t(light_type_count)][size_t(light.m_type)] = float(index);
			light_type_count++;

			if(light.m_shadows)
			{
				float& shadow_type_count = zone.m_shadow_counts[size_t(light.m_type)];
				shadow_type_count++;
			}
		}

		m_light_count = uint16_t(lights.m_count);
		zone.m_light_count = uint16_t(lights.m_count);
	}

	void BlockLight::upload_lights(Render& render)
	{
		UNUSED(render);
#if LIGHTS_BUFFER
		GpuState<GpuLight>::me.pack(m_lights_texture, m_gpu_lights);
#endif
	}

	void BlockLight::upload_zones(Render& render)
	{
#if ZONES_BUFFER
		span<Zone> zones = { &render.m_scene->m_env, 1 };
		GpuState<Zone>::me.pack(m_zones_texture, zones);
#else
		UNUSED(render);
#endif
	}

	void BlockLight::commit_lights(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
#if LIGHTS_BUFFER
		bgfx::Encoder& encoder = *pass.m_encoder;
		encoder.setTexture(uint8_t(TextureSampler::Lights), m_lights_texture);
#endif
	}

	void BlockLight::commit_zones(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
#if ZONES_BUFFER
		bgfx::Encoder& encoder = *pass.m_encoder;
		encoder.setTexture(uint8_t(TextureSampler::Zones), m_zones_texture);
#endif
		//GpuState<ZoneLights>::me.upload(encoder, m_zones[0]);
	}
}

#ifdef _DEBUG
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#include <gfx/Gfx.h>
#include <geom/ShapesComplex.h>
#include <geom/Symbol.h>
namespace mud
{
	void debug_draw_light_clusters(Gnode& parent, Viewport& viewport, Camera& camera)
	{
		if(!viewport.m_clustered) return;
		Froxelizer& clusters = *viewport.m_clusters;

		if(clusters.m_debug_clusters.empty())
			clusters.compute_clusters();

		enum Mode { ClusterIndex, RecordIndex, LightIndex, LightCount };
		Mode mode = ClusterIndex;

		mat4 transform = inverse(bxlookat(camera.m_eye, camera.m_target));
		uint32_t i = 0;
		for(Frustum& frustum : clusters.m_debug_clusters)
		{
			if(!clusters.count(i, 0) && !clusters.count(i, 1))
			{
				//gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour(1.f, 0.02f)));
				i++;
				continue;
			}

			Colour colour = Colour(1.f, 0.02f);
			uint32_t record = clusters.record(i);
			uint32_t light = clusters.light(record);

			if(mode == ClusterIndex)
				colour = hsl(float(i) / (29.f * 16.f * 16.f), 1.f, 0.5f);
			else if(mode == RecordIndex)
				colour = hsl(float(record) / float(255.f), 1.f, 0.5f);
			else if(mode == LightIndex)
				colour = hsl(float(light) / 255.f, 1.f, 0.5f);
			else if(mode == LightCount)
				colour = hsl(float(clusters.count(i)) / 32.f, 1.f, 0.5f);

			gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(colour));
			i++;
		}
	}

	void debug_draw_light_slices(Gnode& parent, Light& light, bool frustums, bool bounds)
	{
		uint32_t index = 0; UNUSED(light);// light.m_index];

		GfxSystem& gfx = parent.m_scene->m_gfx;
		BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();

		if(index >= block_shadow.m_shadows.size())
			return;

		CSMShadow& shadow = block_shadow.m_csm_shadows[index];

		auto draw = [](Gnode& parent, const Shape& shape, const Symbol& symbol)
		{
			Gnode& self = gfx::node(parent, {});
			gfx::draw(self, shape, symbol);
		};

		for(size_t i = 0; i < shadow.m_slices.size(); ++i)
		{
			mat4 inverse_light = inverse(shadow.m_slices[i].m_transform);
			draw(parent, Sphere(vec3(inverse_light[3]), 1.f), Symbol::wire(Colour::White));

			if(frustums)
			{
				Frustum& frustum = shadow.m_slices[i].m_frustum;
				draw(parent, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour::White));
				if(false)
					draw(parent, Sphere(frustum.m_center, frustum.m_radius), Symbol::wire(Colour::DarkGrey));

			}

			if(bounds)
			{
				Box light_bounds = Box(Cube(aabb(shadow.m_slices[i].m_light_bounds.min, shadow.m_slices[i].m_light_bounds.max)));

				for(vec3& vertex : light_bounds.m_vertices)
					vertex = vec3(inverse_light * vec4(vertex, 1.f));

				draw(parent, light_bounds, Symbol::wire(Colour::Pink));
			}
		}
	}
}
#endif

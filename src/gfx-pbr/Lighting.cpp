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

namespace mud
{
	GpuState<Radiance> GpuState<Radiance>::me;
	GpuState<Fog> GpuState<Fog>::me;
	GpuState<Zone> GpuState<Zone>::me;
	GpuState<ZoneLights> GpuState<ZoneLights>::me;

	GpuState<GpuLight> GpuState<GpuLight>::me;

	BlockLight::BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow)
		: DrawBlock(gfx_system, type<BlockLight>())
		, m_block_shadow(block_shadow)
	{
		static cstring options[2] = { "FOG", "DIRECT_LIGHT" };
		m_shader_block->m_options = { options, 2 };

		static string max_lights = to_string(c_max_forward_lights);
		static string max_shadows = to_string(c_max_shadows);

		static ShaderDefine defines[2] = {
			{ "MAX_LIGHTS", max_lights.c_str()  },
			{ "MAX_SHADOWS", max_shadows.c_str() },
		};
		m_shader_block->m_defines = { defines, 2 };
	}

	void BlockLight::init_block()
	{
		u_shot.createUniforms();

#if ZONES_BUFFER
#else
		GpuState<Radiance>::me.init();
		GpuState<Fog>::me.init();
#endif
		GpuState<ZoneLights>::me.init();
	}

	void BlockLight::begin_render(Render& render)
	{
		UNUSED(render);

		m_direct_lights.clear();
		for(Light* light : render.m_shot->m_lights)
			if(light->m_type == LightType::Direct)
			{
				m_direct_lights.push_back(light);
			}

		m_direct_light = m_direct_lights.empty() ? nullptr : m_direct_lights[m_direct_light_index];
		m_block_shadow.m_direct_light = m_direct_light;
	}

	void BlockLight::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockLight::begin_draw_pass(Render& render)
	{
		this->update_lights(render, render.m_camera.m_transform, render.m_shot->m_lights, m_block_shadow.m_shadows);
		this->update_zones({ &render.m_scene.m_env, 1 });

		m_direct_light_index = 0;

		m_direct_light = m_direct_lights.empty() ? nullptr : m_direct_lights[m_direct_light_index];
		m_block_shadow.m_direct_light = m_direct_light;

#ifdef MULTIPLE_DIRECT_LIGHTS
		if(!m_direct_lights.empty())
			m_direct_light = m_direct_lights[m_direct_light_index++];

		if(m_direct_light_index > 0)
			render_pass.m_bgfx_state |= BGFX_STATE_BLEND_ADD;

		request.num_passes = m_direct_lights.empty() ? 1 : m_direct_lights.size();
#endif
	}

	void BlockLight::options(Render& render, ShaderVersion& shader_version) const
	{
		if(render.m_camera.m_clustered)
			shader_version.set_option(0, CLUSTERED, true);

		if(render.m_env && render.m_env->m_fog.m_enabled)
			shader_version.set_option(m_index, FOG, true);

		bool cull = !m_direct_light || false; // !(element.m_item->m_layer_mask & m_direct_light->m_layers);

		if(!cull)
			shader_version.set_option(m_index, DIRECT_LIGHT, true);
	}

	void BlockLight::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		GpuState<ZoneLights>::me.upload(render_pass.m_index, m_zones[0]);
	}

	void BlockLight::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(render.m_camera.m_clustered)
			render.m_camera.m_clusters->submit(encoder);

		this->upload_zones(render, render_pass); //render, render_pass, render.m_env);
		this->upload_lights(render, render_pass);

		// set to not render if not first direct pass, depending on cull
	}

	void BlockLight::update_lights(Render& render, const mat4& view, span<Light*> all_lights, span<LightShadow> shadows)
	{
		UNUSED(render);
		mat4 inverse_view = inverse(view);

		span<Light*> lights = { all_lights.m_pointer, min(all_lights.m_count, size_t(c_max_forward_lights)) };
		uint16_t light_count = 0;

		vector<GpuLight> gpu_lights;

		ZoneLights& zone = m_zones[0];
		zone.m_light_counts = vec4(0.f);

		for(size_t index = 0; index < lights.size(); ++index)
		{
			Light& light = *lights[index];

			vec3 position = mulp(view, light.m_node.position());
			float range = light.m_range;
			vec3 energy = to_vec3(to_linear(light.m_colour) * light.m_energy);
			float specular = light.m_specular;
			vec3 direction = muln(view, light.m_node.direction());
			float attenuation = light.m_attenuation;
			float shadow_enabled = light.m_shadows ? 1.f : 0.f;
			vec3 shadow_color = to_vec3(to_linear(light.m_shadow_colour));
			float spot_attenuation = light.m_spot_attenuation;
			float spot_cutoff = cos(to_radians(light.m_spot_angle));

			gpu_lights.push_back({ position, range, energy, specular, direction, attenuation, shadow_enabled, shadow_color, spot_attenuation, spot_cutoff });

			float& light_type_count = zone.m_light_counts[size_t(light.m_type)];
			zone.m_light_indices[size_t(light_type_count)][size_t(light.m_type)] = light_count;
			light_type_count++;

			if(light.m_shadows) //&& shadows[light_count])
			{
				if(light.m_type == LightType::Direct)
				{
					for(uint32_t i = 0; i < shadows[light_count].m_frustum_slices.size(); ++i)
					{
						m_csm_splits[i] = shadows[light_count].m_frustum_slices[i].m_frustum.m_far;
						m_csm_matrix[i] = shadows[light_count].m_slices[i].m_shadow_matrix * inverse_view;
					}
				}
				else if(light.m_type == LightType::Point)
				{
					//m_shadow_matrix[light_count] = inverse(view * light.m_node.m_transform);
				}
				else if(light.m_type == LightType::Spot)
				{
					//m_shadow_matrix[light_count] = shadows[light_count].m_slices[0].m_shadow_matrix * inverse_view;
				}
			}

			light_count++;
		}

		m_light_count = light_count;
		zone.m_light_count = light_count;

		GpuState<GpuLight>::me.pack(m_lights_texture, gpu_lights);
	}

	void BlockLight::update_zones(span<Zone> zones)
	{
#if ZONES_BUFFER
		GpuState<Zone>::me.pack(m_zones_texture, zones);
#else
#endif
	}

	void BlockLight::upload_lights(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		encoder.setTexture(uint8_t(TextureSampler::Lights), u_shot.s_lights, m_lights_texture);
	}

	void BlockLight::upload_zones(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
#if ZONES_BUFFER
		encoder.setTexture(uint8_t(TextureSampler::Zones), u_shot.s_zones, m_zones_texture);
#else
		GpuState<Zone>::me.upload(encoder, render.m_scene.m_env);
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
	void debug_draw_light_clusters(Gnode& parent, Camera& camera)
	{
		if(!camera.m_clustered) return;
		Froxelizer& clusters = *camera.m_clusters;

		if(clusters.m_debug_clusters.empty())
			clusters.compute_froxels();

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
				colour = hsl_to_rgb(float(i) / (29.f * 16.f * 16.f), 1.f, 0.5f);
			else if(mode == RecordIndex)
				colour = hsl_to_rgb(float(record) / float(255.f), 1.f, 0.5f);
			else if(mode == LightIndex)
				colour = hsl_to_rgb(float(light) / 255.f, 1.f, 0.5f);
			else if(mode == LightCount)
				colour = hsl_to_rgb(float(clusters.count(i)) / 32.f, 1.f, 0.5f);

			gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(colour));
			i++;
		}
	}

	void debug_draw_light_slices(Gnode& parent, Light& light, bool frustums, bool bounds)
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
			mat4 inverse_light = inverse(shadow.m_slices[i].m_transform);
			draw(parent, Sphere(vec3(inverse_light[3]), 1.f), Symbol::wire(Colour::White));

			if(frustums)
			{
				Frustum& frustum = shadow.m_frustum_slices[i].m_frustum;
				draw(parent, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour::White));
				if(false)
					draw(parent, Sphere(frustum.m_center, frustum.m_radius), Symbol::wire(Colour::DarkGrey));

			}

			if(bounds)
			{
				Box light_bounds = Box(aabb(shadow.m_slices[i].m_light_bounds.min, shadow.m_slices[i].m_light_bounds.max));

				for(vec3& vertex : light_bounds.m_vertices)
					vertex = vec3(inverse_light * vec4(vertex, 1.f));

				draw(parent, light_bounds, Symbol::wire(Colour::Pink));
			}
		}
	}
}
#endif

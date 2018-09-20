//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <infra/Vector.h>
#include <infra/StringConvert.h>
#include <math/VecOps.h>
#include <gfx/Shot.h>
#include <gfx/Item.h>
#include <gfx/Viewport.h>
#include <gfx/Scene.h>
#include <gfx/Camera.h>
#include <gfx/Froxel.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Light.h>
#include <gfx-pbr/Shadow.h>
#endif

namespace mud
{
	constexpr size_t BlockLight::ShotUniform::max_lights;
	constexpr size_t BlockLight::ShotUniform::max_shadows;
	constexpr size_t BlockLight::ShotUniform::max_forward_lights;
	constexpr size_t BlockLight::ShotUniform::max_directional_lights;

	BlockLight::BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow)
		: DrawBlock(gfx_system, type<BlockLight>())
		, m_block_shadow(block_shadow)
	{
		static cstring options[2] = { "FOG", "DIRECTIONAL_LIGHT" };
		m_shader_block->m_options = { options, 2 };

		static string max_lights = to_string(ShotUniform::max_lights);
		static string max_shadows = to_string(ShotUniform::max_shadows);
		static string max_dir_lights = to_string(ShotUniform::max_directional_lights);

		static ShaderDefine defines[3] = {
			{ "MAX_LIGHTS", max_lights.c_str()  },
			{ "MAX_SHADOWS", max_shadows.c_str() },
			{ "MAX_DIRECTIONAL_LIGHTS", max_dir_lights.c_str() }
		};
		m_shader_block->m_defines = { defines, 3 };
	}

	void BlockLight::init_gfx_block()
	{
		u_shot.createUniforms();
		u_scene.createUniforms();
		u_fog.createUniforms();
	}

	void BlockLight::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockLight::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockLight::begin_gfx_pass(Render& render)
	{
		m_directional_light_index = 0;

		m_directional_light = m_directional_lights.empty() ? nullptr : m_directional_lights[m_directional_light_index];
		m_block_shadow.m_directional_light = m_directional_light;

		this->update_lights(render, to_array(render.m_shot->m_lights), to_array(m_block_shadow.m_shadows));

		//if(!m_directional_lights.empty())
		//	m_directional_light = m_directional_lights[m_directional_light_index++];

		//if(m_directional_light_index > 0)
		//	render_pass.m_bgfx_state |= BGFX_STATE_BLEND_ADD;

		//request.num_passes = m_directional_lights.empty() ? 1 : m_directional_lights.size();
	}

	void BlockLight::submit_gfx_element(Render& render, const Pass& render_pass, DrawElement& element) const
	{
		if(render.m_camera.m_clustered)
			this->submit_pass(render, render_pass, element.m_shader_version, to_array(render.m_shot->m_lights));
		else
			this->submit_pass(render, render_pass, element.m_shader_version, to_array(element.m_item->m_lights));
	}

	void BlockLight::submit_gfx_cluster(Render& render, const Pass& render_pass, DrawCluster& cluster) const
	{
		this->submit_pass(render, render_pass, cluster.m_shader_version, cluster.m_lights);
	}

	void BlockLight::submit_pass(Render& render, const Pass& render_pass, ShaderVersion& shader_version, array<Light*> lights) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(render.m_camera.m_clustered)
		{
			shader_version.set_option(0, CLUSTERED, true);
			render.m_camera.m_clusters->submit(encoder);
		}

		if(render.m_environment && render.m_environment->m_fog.m_enabled)
			shader_version.set_option(m_index, FOG, true);

		bool cull = !m_directional_light || false; // !(element.m_item->m_layer_mask & m_directional_light->m_layers);

		if(!cull)
			shader_version.set_option(m_index, DIRECTIONAL_LIGHT, true);

		this->upload_environment(render, render_pass, render.m_environment);
		this->upload_fog(render, render_pass, render.m_scene.m_environment.m_fog);
		this->upload_lights(render, render_pass);

		// set to not render if not first directional pass, depending on cull
	}

	void BlockLight::upload_environment(Render& render, const Pass& render_pass, Environment* environment) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		Colour clear_color = render.m_viewport.m_clear_colour;

		vec4 radiance_color_energy = { to_vec3(clear_color), 1.f };
		vec4 ambient_params = { 0.f, 0.f, 0.f, 0.f };

		if(environment)
		{
			radiance_color_energy = { to_vec3(environment->m_radiance.m_colour), environment->m_radiance.m_energy };
			ambient_params = { environment->m_radiance.m_ambient, 0.f, 0.f, 0.f };
		}

		encoder.setUniform(u_scene.u_radiance_color_energy, &radiance_color_energy);
		encoder.setUniform(u_scene.u_ambient_params, &ambient_params);
	}

	void BlockLight::upload_fog(Render& render, const Pass& render_pass, Fog& fog) const
	{
		if(!fog.m_enabled)
			return;

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		vec4 fog_params_0 = { fog.m_density, to_vec3(fog.m_colour) };
		vec4 fog_params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_curve, 0.f };
		vec4 fog_params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
		vec4 fog_params_3 = { float(fog.m_transmit), fog.m_transmit_curve, 0.f, 0.f };
		
		encoder.setUniform(u_fog.u_fog_params_0, &fog_params_0);
		encoder.setUniform(u_fog.u_fog_params_1, &fog_params_1);
		encoder.setUniform(u_fog.u_fog_params_2, &fog_params_2);
		encoder.setUniform(u_fog.u_fog_params_3, &fog_params_3);
	}

	void BlockLight::update_lights(Render& render, array<Light*> all_lights, array<LightShadow> shadows)
	{
		mat4 view_matrix = inverse(render.m_camera.m_transform);

		array<Light*> lights = { all_lights.m_pointer, min(all_lights.m_count, size_t(ShotUniform::max_lights)) };
		m_directional_lights.clear();
		uint16_t light_count = 0;

		m_lights_data.light_counts = Zero4;

		for(Light* light : lights)
		{
			if(light->m_type == LightType::Directional && m_directional_lights.size() < ShotUniform::max_directional_lights)
				m_directional_lights.push_back(light);
		}

		for(Light* light : lights)
		{
			Colour energy = to_linear(light->m_colour) * light->m_energy;
			vec3 position = vec3(render.m_camera.m_transform * vec4(light->m_node.m_position, 1.f));
			vec3 direction = vec3(render.m_camera.m_transform * vec4(light->m_node.direction(), 0.f));
			Colour shadow_color = to_linear(light->m_shadow_colour);
			m_lights_data.shadow_color_enabled[light_count] = { to_vec3(shadow_color), light->m_shadows ? 1.f : 0.f };

			m_lights_data.position_range[light_count] = { position, light->m_range };
			m_lights_data.energy_specular[light_count] = { to_vec3(energy), light->m_specular };
			m_lights_data.direction_attenuation[light_count] = { direction, light->m_attenuation };
			m_lights_data.spot_params[light_count] = { light->m_spot_attenuation, cos(to_radians(light->m_spot_angle)), 0.f, 0.f };

			float& light_type_count = m_lights_data.light_counts[size_t(light->m_type)];
			m_lights_data.light_indices[size_t(light_type_count)][size_t(light->m_type)] = light_count;
			light_type_count++;

			if(light->m_shadows) //&& shadows[light_count])
			{
				if(light->m_type == LightType::Directional)
				{
					for(size_t i = 0; i < shadows[light_count].m_frustum_slices.size(); ++i)
					{
						m_lights_data.csm_splits[light_count][i] = shadows[light_count].m_frustum_slices[i].m_frustum.m_far;
						m_lights_data.csm_matrix[light_count][i] = shadows[light_count].m_slices[i].m_shadow_matrix * view_matrix;
					}
				}
				else if(light->m_type == LightType::Point)
				{
					m_lights_data.shadow_matrix[light_count] = inverse(render.m_camera.m_transform * light->m_node.transform());
				}
				else if(light->m_type == LightType::Spot)
				{
					m_lights_data.shadow_matrix[light_count] = shadows[light_count].m_slices[0].m_shadow_matrix * view_matrix;
				}
			}

			light_count++;
		}

		m_light_count = light_count;
	}

	void BlockLight::upload_lights(Render& render, const Pass& render_pass) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		
		if(m_light_count > 0)
			u_shot.u_light_array.setUniforms(encoder, m_lights_data, uint16_t(m_directional_lights.size()), m_light_count);

		encoder.setUniform(u_shot.u_light_counts, &m_lights_data.light_counts);
		encoder.setUniform(u_shot.u_light_indices, m_lights_data.light_indices, m_light_count);
	}
}

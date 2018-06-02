//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h>
#include <stdint.h>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <obj/Vector.h>
#include <obj/String/StringConvert.h>
#include <math/VecOps.h>
#include <gfx/Shot.h>
#include <gfx/Item.h>
#include <gfx/Viewport.h>
#include <gfx/Scene.h>
#include <gfx/Camera.h>
#include <gfx-pbr/Generated/Types.h>
#include <gfx-pbr/Light.h>
#include <gfx-pbr/Shadow.h>
#endif

namespace mud
{
	constexpr size_t BlockLight::ShotUniform::max_lights;
	constexpr size_t BlockLight::ShotUniform::max_directional_lights;

	BlockLight::BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow)
		: DrawBlock(gfx_system, type<BlockLight>())
		, m_block_shadow(block_shadow)
	{
		static cstring options[1] = { "DIRECTIONAL_LIGHT" };
		m_shader_block->m_options = { options, 1 };

		static string max_lights = to_string(ShotUniform::max_lights);
		static string max_dir_lights = to_string(ShotUniform::max_directional_lights);

		static ShaderDefine defines[2] = {
			{ "MAX_LIGHTS", max_lights.c_str()  },
			{ "MAX_DIRECTIONAL_LIGHTS", max_dir_lights.c_str() }
		};
		m_shader_block->m_defines = { defines, 2 };
	}

	void BlockLight::init_gfx_block()
	{
		u_shot.createUniforms();
		u_scene.createUniforms();
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

		//if(!m_directional_lights.empty())
		//	m_directional_light = m_directional_lights[m_directional_light_index++];

		this->upload_environment(render, render.m_environment);
		this->upload_lights(render, to_array(render.m_shot->m_lights), to_array(m_block_shadow.m_shadows));

		//if(m_directional_light_index > 0)
		//	render_pass.m_bgfx_state |= BGFX_STATE_BLEND_ADD;

		//request.num_passes = m_directional_lights.empty() ? 1 : m_directional_lights.size();
	}

	void BlockLight::submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass);

		// @kludge
		m_directional_light = m_directional_lights.empty() ? nullptr : m_directional_lights[m_directional_light_index];
		m_block_shadow.m_directional_light = m_directional_light;

		bool cull = !m_directional_light || !(element.m_item->m_layer_mask & m_directional_light->m_layers);

		if(!cull)
			element.m_shader_version.set_option(m_index, DIRECTIONAL_LIGHT, true);

		this->upload_lights(render, to_array(element.m_item->m_lights), to_array(m_block_shadow.m_shadows));

		// set to not render if not first directional pass, depending on cull
	}

	void BlockLight::upload_environment(Render& render, Environment* environment)
	{
		Colour clear_color = render.m_viewport.m_clear_colour;

		vec4 radiance_color_energy = { to_vec3(clear_color), 1.f };
		vec4 ambient_params = { 0.f, 0.f, 0.f, 0.f };

		if(environment)
		{
			radiance_color_energy = { to_vec3(environment->m_radiance.m_colour), environment->m_radiance.m_energy };
			ambient_params = { environment->m_radiance.m_ambient, 0.f, 0.f, 0.f };
		}

		bgfx::setUniform(u_scene.u_radiance_color_energy, &radiance_color_energy);
		bgfx::setUniform(u_scene.u_ambient_params, &ambient_params);
	}

	void BlockLight::upload_lights(Render& render, array<Light*> all_lights, array<LightShadow> shadows)
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
			m_lights_data.spot_params[light_count] = { light->m_spot_attenuation, cos(light->m_spot_angle), 0.f, 0.f };
			
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
		
		if(light_count > 0)
			u_shot.u_light_array.setUniforms(m_lights_data, uint16_t(m_directional_lights.size()), light_count);


		bgfx::setUniform(u_shot.u_light_counts, &m_lights_data.light_counts);
		bgfx::setUniform(u_shot.u_light_indices, m_lights_data.light_indices, light_count);
	}
}

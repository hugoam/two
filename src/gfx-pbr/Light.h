

#pragma once

#include <gfx/Renderer.h>
#include <gfx/Light.h>
#include <gfx-pbr/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	enum ShaderOptionLight : unsigned int
	{
		DIRECTIONAL_LIGHT
	};

	template <uint16_t num_lights, uint16_t num_directional = 1>
	struct LightArray
	{
		vec4 position_range[num_lights];
		vec4 energy_specular[num_lights];
		vec4 direction_attenuation[num_lights];
		vec4 shadow_color_enabled[num_lights];
		mat4 shadow_matrix[num_lights];
		vec4 spot_params[num_lights];

		vec4 light_indices[num_lights];
		vec4 light_counts;

		mat4 csm_matrix[num_directional][4];
		vec4 csm_splits[num_directional];
	};

	export_ class _refl_ MUD_GFX_EXPORT BlockLight : public DrawBlock
	{
	public:
		BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		virtual void begin_gfx_pass(Render& render) final;
		virtual void submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element) final;

		void upload_environment(Render& render, Environment* environment);

		void upload_lights(Render& render, array<Light*> lights, array<LightShadow> shadows);
		
		BlockShadow& m_block_shadow;

		uint16_t m_directional_light_index = 0;
		Light* m_directional_light = nullptr;
		std::vector<Light*> m_directional_lights;

		struct LightUniform
		{
			void createUniforms(uint16_t max_directional, uint16_t max_lights)
			{
				u_light_position_range			= bgfx::createUniform("u_light_position_range",			bgfx::UniformType::Vec4, max_lights);
				u_light_energy_specular			= bgfx::createUniform("u_light_energy_specular",		bgfx::UniformType::Vec4, max_lights);
				u_light_direction_attenuation	= bgfx::createUniform("u_light_direction_attenuation",	bgfx::UniformType::Vec4, max_lights);
				u_light_shadow					= bgfx::createUniform("u_light_shadow",					bgfx::UniformType::Vec4, max_lights);
				u_light_shadow_matrix			= bgfx::createUniform("u_light_shadow_matrix",			bgfx::UniformType::Mat4, max_lights);
				u_light_spot_params				= bgfx::createUniform("u_light_spot_params",			bgfx::UniformType::Vec4, max_lights);
				u_csm_matrix					= bgfx::createUniform("u_csm_matrix",					bgfx::UniformType::Mat4, max_directional * 4);
				u_csm_splits					= bgfx::createUniform("u_csm_splits",					bgfx::UniformType::Vec4, max_directional);
			}

			template <uint16_t size>
			void setUniforms(LightArray<size>& data, uint16_t directional_light_count, uint16_t light_count)
			{
				bgfx::setUniform(u_light_position_range,        &data.position_range,			light_count);
				bgfx::setUniform(u_light_energy_specular,		&data.energy_specular,			light_count);
				bgfx::setUniform(u_light_direction_attenuation, &data.direction_attenuation,	light_count);
				bgfx::setUniform(u_light_shadow,				&data.shadow_color_enabled,		light_count);
				bgfx::setUniform(u_light_shadow_matrix,			&data.shadow_matrix,			light_count);
				bgfx::setUniform(u_light_spot_params,           &data.spot_params,				light_count);

				bgfx::setUniform(u_csm_matrix, &data.csm_matrix[0], directional_light_count * 4);
				bgfx::setUniform(u_csm_splits, &data.csm_splits,	directional_light_count);
			}

			bgfx::UniformHandle u_light_position_range;
			bgfx::UniformHandle u_light_energy_specular;
			bgfx::UniformHandle u_light_direction_attenuation;
			bgfx::UniformHandle u_light_shadow;
			bgfx::UniformHandle u_light_shadow_matrix;
			bgfx::UniformHandle u_light_spot_params;
			bgfx::UniformHandle u_csm_matrix;
			bgfx::UniformHandle u_csm_splits;
		};

		struct ShotUniform
		{
			static constexpr size_t max_lights = 16;
			static constexpr size_t max_directional_lights = 1;

			void createUniforms()
			{
				u_light_indices = bgfx::createUniform("u_light_indices", bgfx::UniformType::Vec4, max_lights);
				u_light_counts  = bgfx::createUniform("u_light_counts",  bgfx::UniformType::Vec4);

				u_light_array.createUniforms(uint16_t(max_directional_lights), uint16_t(max_lights));
			}

			bgfx::UniformHandle u_light_indices;
			bgfx::UniformHandle u_light_counts;

			LightUniform u_light_array;

		} u_shot;

		struct SceneUniform
		{
			void createUniforms()
			{
				u_radiance_color_energy =  bgfx::createUniform("u_radiance_color_energy",	bgfx::UniformType::Vec4);
				u_ambient_params =		   bgfx::createUniform("u_ambient_params",			bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_radiance_color_energy;
			bgfx::UniformHandle u_ambient_params;

		} u_scene;

		LightArray<ShotUniform::max_lights> m_lights_data;
	};
}



#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Light.h>
#endif
#include <gfx-pbr/Forward.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	enum ShaderOptionLight : unsigned int
	{
		FOG,
		DIRECT_LIGHT
	};

	template <uint16_t num_lights, uint16_t num_direct = 1>
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

		mat4 csm_matrix[num_direct][4];
		vec4 csm_splits[num_direct];
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockLight : public DrawBlock
	{
	public:
		BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const final;
		virtual void submit(Render& render, const Pass& render_pass) const final;

		void update_lights(Render& render, const mat4& view, array<Light*> lights, array<LightShadow> shadows);

		void upload_environment(Render& render, const Pass& render_pass, Environment* environment) const;
		void upload_fog(Render& render, const Pass& render_pass, Fog& fog) const;
		void upload_lights(const Pass& render_pass) const;
		
		BlockShadow& m_block_shadow;

		uint16_t m_direct_light_index = 0;
		Light* m_direct_light = nullptr;
		vector<Light*> m_direct_lights;

		struct LightUniform
		{
			void createUniforms(uint16_t max_direct, uint16_t max_lights)
			{
				u_light_position_range			= bgfx::createUniform("u_light_position_range",			bgfx::UniformType::Vec4, max_lights);
				u_light_energy_specular			= bgfx::createUniform("u_light_energy_specular",		bgfx::UniformType::Vec4, max_lights);
				u_light_direction_attenuation	= bgfx::createUniform("u_light_direction_attenuation",	bgfx::UniformType::Vec4, max_lights);
				u_light_shadow					= bgfx::createUniform("u_light_shadow",					bgfx::UniformType::Vec4, max_lights);
				u_light_shadow_matrix			= bgfx::createUniform("u_light_shadow_matrix",			bgfx::UniformType::Mat4, max_lights);
				u_light_spot_params				= bgfx::createUniform("u_light_spot_params",			bgfx::UniformType::Vec4, max_lights);
				u_csm_matrix					= bgfx::createUniform("u_csm_matrix",					bgfx::UniformType::Mat4, max_direct * 4);
				u_csm_splits					= bgfx::createUniform("u_csm_splits",					bgfx::UniformType::Vec4, max_direct);
			}

			template <uint16_t size>
			void setUniforms(bgfx::Encoder& encoder, const LightArray<size>& data, uint16_t direct_light_count, uint16_t light_count) const
			{
				encoder.setUniform(u_light_position_range,			&data.position_range,			light_count);
				encoder.setUniform(u_light_energy_specular,			&data.energy_specular,			light_count);
				encoder.setUniform(u_light_direction_attenuation,	&data.direction_attenuation,	light_count);
				encoder.setUniform(u_light_shadow,					&data.shadow_color_enabled,		light_count);
				encoder.setUniform(u_light_shadow_matrix,			&data.shadow_matrix,			light_count);
				encoder.setUniform(u_light_spot_params,				&data.spot_params,				light_count);

				encoder.setUniform(u_csm_matrix, &data.csm_matrix[0], direct_light_count * 4);
				encoder.setUniform(u_csm_splits, &data.csm_splits,	direct_light_count);
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
			static constexpr size_t max_lights = 64;
			static constexpr size_t max_shadows = 32;
			static constexpr size_t max_forward_lights = 16;
			static constexpr size_t max_direct_lights = 1;

			void createUniforms()
			{
				u_light_indices = bgfx::createUniform("u_light_indices", bgfx::UniformType::Vec4, max_lights);
				u_light_counts  = bgfx::createUniform("u_light_counts",  bgfx::UniformType::Vec4);

				u_light_array.createUniforms(uint16_t(max_direct_lights), uint16_t(max_lights));
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

		struct FogUniform
		{
			void createUniforms()
			{
				u_fog_params_0 = bgfx::createUniform("u_fog_params_0", bgfx::UniformType::Vec4);
				u_fog_params_1 = bgfx::createUniform("u_fog_params_1", bgfx::UniformType::Vec4);
				u_fog_params_2 = bgfx::createUniform("u_fog_params_2", bgfx::UniformType::Vec4);
				u_fog_params_3 = bgfx::createUniform("u_fog_params_3", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_fog_params_0;
			bgfx::UniformHandle u_fog_params_1;
			bgfx::UniformHandle u_fog_params_2;
			bgfx::UniformHandle u_fog_params_3;

		} u_fog;

		LightArray<ShotUniform::max_lights> m_lights_data;
		uint16_t m_light_count;
	};
}

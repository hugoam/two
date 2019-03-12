

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/ReflectionAtlas.h>

namespace mud
{
	struct gpu_ GpuReflectionProbe
	{
		attr_ gpu_ vec3 extents;
		attr_ gpu_ float intensity;
		attr_ gpu_ vec4 atlas_rect;
		attr_ gpu_ mat4 transform;
	};

	template <uint16_t num_probes>
	struct ReflectionProbeArray
	{
		vec4 extents_intensity[num_probes];
		vec4 ambient[num_probes];
		vec4 atlas_rect[num_probes];
		mat4 matrix[num_probes];

		vec4 indices[num_probes];
		vec4 counts;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT ReflectionProbe
	{
	public:
		ReflectionProbe(Node3& node);

		attr_ Node3& m_node;

		attr_ bool m_visible = true;
		attr_ float m_intensity = 1.f;
		attr_ vec3 m_extents = vec3(0.f);
		attr_ bool m_shadows = false;

		ReflectionAtlas* m_atlas;
		int m_atlas_index = -1;

		attr_ bool m_dirty = true;
	};

	export_ MUD_GFX_PBR_EXPORT void pass_probes(GfxSystem& gfx, Render& render);

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockReflection : public DrawBlock
	{
	public:
		BlockReflection(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, ProgramVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const override;

		void upload_reflection_probes(Render& render, Pass& render_pass, span<ReflectionProbe*> probes);
		void render_reflection_probe(Render& render, ReflectionProbe& reflection_probe);

		ReflectionCubemap& find_cubemap(uint16_t size);

		struct ReflectionUniform
		{
			static constexpr size_t max_reflection_probes = 16;

			void createUniforms(uint16_t max_probes)
			{
				u_extents_intensity		= bgfx::createUniform("u_reflection_extents_intensity",	bgfx::UniformType::Vec4, max_probes);
				u_ambient				= bgfx::createUniform("u_reflection_ambient",			bgfx::UniformType::Vec4, max_probes);
				u_atlas_rect			= bgfx::createUniform("u_reflection_atlas_rect",		bgfx::UniformType::Mat4, max_probes);
				u_matrix				= bgfx::createUniform("u_reflection_matrix",			bgfx::UniformType::Vec4, max_probes);

				//u_indices		= bgfx::createUniform("u_reflection_indices",		bgfx::UniformType::Sampler, max_probes);
				//u_count		= bgfx::createUniform("u_reflection_count",			bgfx::UniformType::Sampler);
			}

			template <uint16_t size>
			void setUniforms(bgfx::Encoder& encoder, ReflectionProbeArray<size>& data, uint16_t probe_count)
			{
				encoder.setUniform(u_extents_intensity,		&data.extents_intensity,	probe_count);
				encoder.setUniform(u_ambient,				&data.ambient,				probe_count);
				encoder.setUniform(u_atlas_rect,			&data.atlas_rect,			probe_count);
				encoder.setUniform(u_matrix,				&data.matrix,				probe_count);
			}

			bgfx::UniformHandle u_extents_intensity;
			bgfx::UniformHandle u_ambient;
			bgfx::UniformHandle u_atlas_rect;
			bgfx::UniformHandle u_matrix;

			bgfx::UniformHandle u_indices;
			bgfx::UniformHandle u_count;

			bgfx::UniformHandle s_atlas;
		};

		ReflectionUniform u_uniform;

		vector<ReflectionCubemap> m_cubemaps;

		ReflectionAtlas m_atlas;

		float m_reflection_multiplier;
	};
}

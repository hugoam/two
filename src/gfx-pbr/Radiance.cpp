//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <gfx/Scene.h>
#include <gfx/Texture.h>
#include <gfx/RenderTarget.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Radiance.h>
#endif

#include <cstdio>

namespace mud
{
	BlockRadiance::BlockRadiance(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: DrawBlock(gfx, type<BlockRadiance>())
		, m_filter(filter)
		, m_copy(copy)
		, m_prefilter_program(gfx.programs().create("filter/prefilter_envmap"))
	{
		static cstring options[] = { "RADIANCE_ENVMAP", "RADIANCE_CUBE" };
		m_shader_block->m_options = options;

		m_prefilter_program.register_block(filter);
		m_prefilter_program.register_block(*this);
	}

	void BlockRadiance::init_block()
	{
		u_prefilter.createUniforms();
		u_radiance.createUniforms();
	}
	
	void BlockRadiance::begin_frame(const RenderFrame& frame)
	{
		UNUSED(frame);
		for(Radiance* radiance : m_prefilter_queue)
			this->prefilter_radiance(*radiance);
		m_prefilter_queue.clear();
	}

	void BlockRadiance::begin_render(Render& render)
	{
		if(!render.m_env || !render.m_env->m_radiance.m_texture)
			return;

		if(!render.m_env->m_radiance.m_preprocessed && render.m_env->m_radiance.m_filter)
			m_prefilter_queue.push_back(&render.m_env->m_radiance);

#ifdef DEBUG_RADIANCE
		if(bgfx::isValid(render.m_env->m_radiance.m_filtered))
		{
			m_gfx.m_copy->debug_show_texture(render, render.m_env->m_radiance.m_filtered, vec4(0.f), false, false, false, 2);
		}
#endif
	}

	Texture* radiancemap(Radiance& radiance)
	{
		Texture* const filtered = radiance.m_filtered;
		Texture* const reflection = radiance.m_texture;
		if(filtered && filtered->valid())
			return filtered;
		else if(reflection && reflection->valid() && !radiance.m_filter)
			return reflection;
		else
			return nullptr;
	}

	void BlockRadiance::options(Render& render, ProgramVersion& shader_version) const
	{
		Texture* radiance = radiancemap(render.m_env->m_radiance);

		if(radiance)
			shader_version.set_option(m_index, RADIANCE_ENVMAP);
		if(radiance && radiance->m_is_cube)
			shader_version.set_option(m_index, RADIANCE_CUBE);
	}

	void BlockRadiance::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);
		uint32_t stage = uint32_t(TextureSampler::Radiance);
		bgfx::setViewUniform(pass.m_index, u_radiance.s_radiance, &stage);
	}

	void BlockRadiance::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(element);
		bgfx::Encoder& encoder = *pass.m_encoder;

		if(Texture* radiance = radiancemap(render.m_env->m_radiance))
			encoder.setTexture(uint8_t(TextureSampler::Radiance), *radiance);
	}

	void BlockRadiance::prefilter_radiance(Radiance& radiance)
	{
		if(m_prefiltered.find(radiance.m_texture) != m_prefiltered.end())
		{
			radiance.m_filtered = m_prefiltered[radiance.m_texture];
			radiance.m_preprocessed = true;
			return;
		}

		//if(!radiance.m_texture->valid() || radiance.m_texture->m_is_cube)
		if(!radiance.m_texture->valid())// || radiance.m_texture->m_is_cube)
			return;

		constexpr int roughness_levels = 8;

		const bool cube = radiance.m_texture->m_is_cube;
		const uvec2 size = cube
			? radiance.m_texture->m_size
			: m_gfx.main_target().m_size;

		const uint64_t flags = BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP;

		//bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA16F;
		bgfx::TextureFormat::Enum format = radiance.m_texture->m_format;
		if(!bgfx::isTextureValid(1, cube, 1, format, flags))
			format = bgfx::TextureFormat::RGB10A2;

		if(!bgfx::isTextureValid(1, cube, 1, format, flags))
		{
			printf("WARNING: could not prefilter env map roughness levels\n");
			return;
		}

		Texture& filtered = m_gfx.textures().create(radiance.m_texture->m_name + "_filtered");
		filtered = { size, true, format, flags, cube };

		//const uint8_t view_id = Render::s_preprocess_pass_id; //render.preprocess_pass();

		auto blit_level = [&](Texture& source, const uvec2& size, int level, int face = 0)
		{
			const uvec2 level_size = uvec2(size.x >> level, size.y >> level);
			bgfx::Attachment attach = { bgfx::Access::Write, filtered, uint16_t(level), uint16_t(face), BGFX_RESOLVE_NONE };
			FrameBuffer render_target = { level_size, filtered, { attach } }; // @todo fix ownership
			m_copy.quad(Pass(), render_target, source);
			bgfx::frame();
		};

		const uint16_t num_faces = cube ? 6 : 1;

		for(uint16_t i = 0; i < roughness_levels; i++)
		{
			const uvec2 level_size = uvec2(size.x >> i, size.y >> i);
			FrameBuffer target = { level_size, format, GFX_TEXTURE_POINT };

			for(uint16_t face = 0; face < num_faces; ++face)
			{
				ProgramVersion program = { &m_prefilter_program };

				const int source_level = i == 0 ? 0 : i - 1;
				Texture& source = i == 0 ? *radiance.m_texture : filtered;
				m_filter.source0(source, program, source_level, GFX_TEXTURE_POINT);

				float roughness = i / float(roughness_levels - 1);
#ifdef MUD_PLATFORM_EMSCRIPTEN
				constexpr uint num_samples = 64;
#else
				constexpr uint num_samples = 512;
#endif
				const vec4 prefilter_p0 = { roughness, float(num_samples), 0.f, 0.f };
				bgfx::setUniform(u_prefilter.u_prefilter_envmap_p0, &prefilter_p0);

				if(cube)
				{
					constexpr vec3 up[6] = { Y3, Y3, -Z3, Z3, Y3, Y3 };
					constexpr vec3 dir[6] = { X3, -X3, Y3, -Y3, Z3, -Z3 };

					const mat4 cubemat = bxlookat(vec3(0.f), vec3(0.f) + dir[face], up[face]);
					bgfx::setUniform(u_prefilter.u_prefilter_cube, &cubemat);
				}

				m_filter.quad(Pass(), target, program, 0U, true);

				blit_level(target.m_tex, size, i, face);
			}
		}

		m_prefiltered[radiance.m_texture] = &filtered;
		radiance.m_filtered = &filtered;
		radiance.m_preprocessed = true;
	}
}

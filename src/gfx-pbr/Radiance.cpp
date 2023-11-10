//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <gfx/Cpp20.h>
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <infra/Log.h>
#include <gfx/Scene.h>
#include <gfx/Texture.h>
#include <gfx/Material.h>
#include <gfx/RenderTarget.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Radiance.h>
#endif

#include <cstdio>

#define DEBUG_ENVMAP 0
#define DEBUG_RADIANCE 0

#ifndef TWO_MODULES
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif

namespace two
{
	BlockRadiance::BlockRadiance(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: DrawBlock(gfx, type<BlockRadiance>())
		, m_filter(filter)
		, m_copy(copy)
		, m_prefilter_program(gfx.programs().create("filter/prefilter_envmap"))
	{
		m_options = { "RADIANCE_ENVMAP", "RADIANCE_CUBE" };

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

		Radiance& radiance = render.m_env->m_radiance;
		if(!radiance.m_preprocessed && radiance.m_filter)
			m_prefilter_queue.push_back(&radiance);

#if DEBUG_ENVMAP
		m_gfx.m_copy->debug_show_texturep(render, radiance.m_texture, vec4(0.f), 0);
#endif

#if DEBUG_RADIANCE
		m_gfx.m_copy->debug_show_texturep(render, radiance.m_filtered, vec4(0.f), 2);
#endif
	}

	static Texture* radiancemap(Radiance& radiance)
	{
		Texture* filtered = radiance.m_filtered;
		Texture* reflection = radiance.m_texture;
		if(filtered && filtered->valid())
			return filtered;
		else if(reflection && reflection->valid() && !radiance.m_filter)
			return reflection;
		else
			return nullptr;
	}

	void BlockRadiance::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		const bool enable = !element.m_material->m_lit.m_no_envmap;
		Texture* radiance = radiancemap(render.m_env->m_radiance);

		if(enable && radiance)
			program.set_option(m_index, RADIANCE_ENVMAP);
		if(enable && radiance && radiance->m_is_cube)
			program.set_option(m_index, RADIANCE_CUBE);
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

		const uint64_t flags = BGFX_TEXTURE_RT | TEXTURE_CLAMP;

		//bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA16F;
		TextureFormat format = radiance.m_texture->m_format;
		if(!bgfx::isTextureValid(1, cube, 1, bgfx::TextureFormat::Enum(format), flags))
			format = TextureFormat::RGB10A2;

		if(!bgfx::isTextureValid(1, cube, 1, bgfx::TextureFormat::Enum(format), flags))
		{
			warn("could not prefilter env map roughness levels");
			return;
		}

		Texture& filtered = m_gfx.textures().create(radiance.m_texture->m_name + "_filtered");
		filtered = { size, true, format, flags, cube };

		//const uint8_t view_id = Render::s_preprocess_pass_id; //render.preprocess_pass();

		auto blit_level = [&](Texture& source, const uvec2& size, uint16_t level, uint16_t face)
		{
			const uvec2 level_size = uvec2(size.x >> level, size.y >> level);
			bgfx::Attachment attach = { bgfx::Access::Write, filtered, level, face, 1, BGFX_RESOLVE_NONE };
			FrameBuffer render_target = { level_size, filtered, { attach } }; // @todo fix ownership
			m_copy.submit(Pass(), render_target, source, RenderQuad(), 0U, true);
		};

		const uint16_t num_faces = cube ? 6 : 1;

		for(uint16_t i = 0; i < roughness_levels; i++)
		{
			const uvec2 level_size = uvec2(size.x >> i, size.y >> i);
			FrameBuffer target = { level_size, format, TEXTURE_POINT };

			for(uint16_t face = 0; face < num_faces; ++face)
			{
				ProgramVersion program = { m_prefilter_program };

				const int source_level = i == 0 ? 0 : i - 1;
				Texture& source = i == 0 ? *radiance.m_texture : filtered;
				m_filter.source0p(source, program, source_level, TEXTURE_POINT);

				float roughness = i / float(roughness_levels - 1);
#ifdef TWO_PLATFORM_EMSCRIPTEN
				constexpr uint num_samples = 64;
#else
				constexpr uint num_samples = 512;
#endif
				const vec4 prefilter_p0 = { roughness, float(num_samples), 0.f, 0.f };
				bgfx::setUniform(u_prefilter.u_prefilter_envmap_p0, &prefilter_p0);

				if(cube)
				{
					CONSTEXPR vec3 up[6] = { y3, y3, -z3, z3, y3, y3 };
					CONSTEXPR vec3 dir[6] = { x3, -x3, y3, -y3, z3, -z3 };

					const mat4 cubemat = bxlookat(vec3(0.f), vec3(0.f) + dir[face], up[face]);
					bgfx::setUniform(u_prefilter.u_prefilter_cube, &cubemat);
				}

				m_filter.submit(Pass(), target, program, RenderQuad(), 0U, true);

				blit_level(target.m_tex, size, i, face);
			}
		}

		m_prefiltered[radiance.m_texture] = &filtered;
		radiance.m_filtered = &filtered;
		radiance.m_preprocessed = true;
	}
}

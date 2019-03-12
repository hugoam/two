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
		static cstring options[] = { "RADIANCE_ENVMAP", "RADIANCE_ARRAY" };
		m_shader_block->m_options = options;
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

		if(!render.m_env->m_radiance.m_preprocessed)
			m_prefilter_queue.push_back(&render.m_env->m_radiance);

#ifdef DEBUG_RADIANCE
		if(bgfx::isValid(render.m_env->m_radiance.m_filtered))
		{
			BlockCopy& copy = *m_gfx.m_renderer.block<BlockCopy>();
			copy.debug_show_texture(render, render.m_env->m_radiance.m_filtered, vec4(0.f), false, false, false, 2);
		}
#endif
	}

	void BlockRadiance::options(Render& render, ShaderVersion& shader_version) const
	{
		Texture* radiance = render.m_env->m_radiance.m_filtered;

		if(radiance && radiance->valid())
			shader_version.set_option(m_index, RADIANCE_ENVMAP);
	}

	void BlockRadiance::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		uint32_t stage = uint32_t(TextureSampler::Radiance);
		bgfx::setViewUniform(render_pass.m_index, u_radiance.s_radiance, &stage);
	}

	void BlockRadiance::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(element);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		Texture* radiance = render.m_env->m_radiance.m_filtered;

		if(radiance && radiance->valid())
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

		if(!radiance.m_texture->valid())
			return;

		constexpr int roughness_levels = 8;

#define MUD_RADIANCE_MIPMAPS

		//if(radiance.m_filtered->valid())
		//	bgfx::destroy(radiance.m_filtered);

		RenderTarget& target = *m_gfx.context().m_target;
		uint16_t width = uint16_t(target.m_size.x); //radiance.m_texture->m_width;
		uint16_t height = uint16_t(target.m_size.y); //radiance.m_texture->m_height;

#ifdef MUD_RADIANCE_MIPMAPS
		uint16_t texture_layers = 1;
		bool mips = true;
#else
		uint16_t texture_layers = roughness_levels;
		bool mips = false;
#endif

		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA16F;
		if(!bgfx::isTextureValid(1, mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP))
			format = bgfx::TextureFormat::RGB10A2;

		if(!bgfx::isTextureValid(1, mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP))
		{
			printf("WARNING: could not prefilter env map roughness levels\n");
			return;
		}

		bool blit_support = false; // (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0;

		Texture& filtered = m_gfx.textures().create(radiance.m_texture->m_name + "_filtered");
		if(blit_support)
			filtered = { uvec2(width, height), mips, texture_layers, format, BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP };
		else
			filtered = { uvec2(width, height), mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP };

		uint8_t view_id = Render::s_preprocess_pass_id; //render.preprocess_pass();

		auto blit_to_array = [&](Texture& texture, uvec2 size, int level)
		{
			if(blit_support)
			{
				bgfx::blit(view_id + 1, filtered, 0, 0, 0, uint16_t(level), texture, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), 1);
				bgfx::frame();
			}
			else
			{
				bgfx::Attachment attachment = { bgfx::Access::Write, filtered, uint16_t(mips ? level : 0), uint16_t(mips ? 0 : level), BGFX_RESOLVE_NONE };
				FrameBuffer render_target = { size, bgfx::createFrameBuffer(1, &attachment, false) };
				m_copy.submit_quad(view_id + 1, render_target, texture);
				bgfx::frame();
			}
		};

		blit_to_array(*radiance.m_texture, { width, height }, 0);

		for(uint16_t i = 1; i < roughness_levels; i++)
		{
			uvec2 size = mips ? uvec2(width >> i, height >> i) : uvec2(width, height);
			FrameBuffer copy_target = { size, format, GFX_TEXTURE_POINT };

			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, filtered, GFX_TEXTURE_POINT);

			int source_level = i - 1;
			bgfx::setUniform(m_filter.u_uniform.u_source_0_level, &source_level);

			float roughness = i / float(roughness_levels - 1);
#ifdef MUD_PLATFORM_EMSCRIPTEN
			float num_samples = 64;
#else
			float num_samples = 512;
#endif
			vec4 prefilter_p0 = { roughness, float(num_samples), 0.f, 0.f };
			bgfx::setUniform(u_prefilter.u_prefilter_envmap_p0, &prefilter_p0);

			bgfx::ProgramHandle program = m_prefilter_program.default_version();
			m_filter.submit_quad(view_id, copy_target, program, 0U, true);

			blit_to_array(copy_target, size, i);
		}

		m_prefiltered[radiance.m_texture] = &filtered;
		radiance.m_filtered = &filtered;
		radiance.m_preprocessed = true;
	}
}

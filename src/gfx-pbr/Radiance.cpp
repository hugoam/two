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
	BlockRadiance::BlockRadiance(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy)
		: DrawBlock(gfx_system, type<BlockRadiance>())
		, m_filter(filter)
		, m_copy(copy)
		, m_prefilter_program(gfx_system.programs().create("filter/prefilter_envmap"))
	{
		static cstring options[2] = { "RADIANCE_ENVMAP", "RADIANCE_ARRAY" };
		m_shader_block->m_options = { options, 2 };
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
		if(bgfx::isValid(render.m_env->m_radiance.m_roughness_array))
		{
			BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
			copy.debug_show_texture(render, render.m_env->m_radiance.m_roughness_array, vec4(0.f), false, false, false, 2);
		}
#endif
	}

	void BlockRadiance::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockRadiance::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockRadiance::options(Render& render, ShaderVersion& shader_version) const
	{
		bgfx::TextureHandle radiance = render.m_env->m_radiance.m_roughness_array;

		if(bgfx::isValid(radiance))
			shader_version.set_option(m_index, RADIANCE_ENVMAP);
	}

	void BlockRadiance::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		uint32_t stage = uint32_t(TextureSampler::Radiance);
		bgfx::setViewUniform(render_pass.m_index, u_radiance.s_radiance_map, &stage);
	}

	void BlockRadiance::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		bgfx::TextureHandle radiance = render.m_env->m_radiance.m_roughness_array;

		// @todo implement bgfx::setViewTexture
		if(bgfx::isValid(radiance))
			encoder.setTexture(uint8_t(TextureSampler::Radiance), radiance);
	}

	void BlockRadiance::prefilter_radiance(Radiance& radiance)
	{
		if(m_prefiltered.find(radiance.m_texture->m_texture.idx) != m_prefiltered.end())
		{
			radiance.m_roughness_array = { m_prefiltered[radiance.m_texture->m_texture.idx] };
			radiance.m_preprocessed = true;
			return;
		}

		if(!bgfx::isValid(radiance.m_texture->m_texture))
			return;

		constexpr int roughness_levels = 8;

#define MUD_RADIANCE_MIPMAPS

		if(bgfx::isValid(radiance.m_roughness_array))
			bgfx::destroy(radiance.m_roughness_array);

		RenderTarget& target = *m_gfx_system.context().m_target;
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

		if(blit_support)
			radiance.m_roughness_array = bgfx::createTexture2D(width, height, mips, texture_layers, format, BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP);
		else
			radiance.m_roughness_array = bgfx::createTexture2D(width, height, mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP);

		bgfx::TextureHandle radiance_array = radiance.m_roughness_array;

		uint8_t view_id = Render::s_preprocess_pass_id; //render.preprocess_pass();

		auto blit_to_array = [&](bgfx::TextureHandle texture, uvec2 size, int level)
		{
			if(blit_support)
			{
				bgfx::blit(view_id + 1, radiance_array, 0, 0, 0, uint16_t(level), texture, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), 1);
				bgfx::frame();
			}
			else
			{
				bgfx::Attachment attachment = { bgfx::Access::Write, radiance_array, uint16_t(mips ? level : 0), uint16_t(mips ? 0 : level), BGFX_RESOLVE_NONE };
				FrameBuffer render_target = { size, bgfx::createFrameBuffer(1, &attachment, false) };
				m_copy.submit_quad(render_target, view_id + 1, texture);
				bgfx::frame();
			}
		};

		blit_to_array(radiance.m_texture->m_texture, { width, height }, 0);

		for(uint16_t i = 1; i < roughness_levels; i++)
		{
			uvec2 size = mips ? uvec2(width >> i, height >> i) : uvec2(width, height);
			FrameBuffer copy_target = { size, format, GFX_TEXTURE_POINT };

			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, radiance_array, GFX_TEXTURE_POINT);

			int source_level = i - 1;
			bgfx::setUniform(m_filter.u_uniform.u_source_0_level, &source_level);

			float roughness = i / float(roughness_levels - 1);
#ifdef MUD_PLATFORM_EMSCRIPTEN
			float num_samples = 64;
#else
			float num_samples = 512;
#endif
			vec4 prefilter_params = { roughness, float(num_samples), 0.f, 0.f };
			bgfx::setUniform(u_prefilter.u_prefilter_envmap_params, &prefilter_params);

			bgfx::ProgramHandle program = m_prefilter_program.default_version();
			m_filter.submit_quad(copy_target, view_id, program, 0U, true);

			blit_to_array(bgfx::getTexture(copy_target.m_fbo), size, i);
		}

		m_prefiltered[radiance.m_texture->m_texture.idx] = radiance.m_roughness_array.idx;
		radiance.m_preprocessed = true;
	}
}

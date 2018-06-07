//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx/Scene.h>
#include <gfx/Texture.h>
#include <gfx/RenderTarget.h>
#include <gfx-pbr/Generated/Types.h>
#include <gfx-pbr/Radiance.h>
#endif

namespace mud
{
	BlockRadiance::BlockRadiance(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy)
		: DrawBlock(gfx_system, type<BlockRadiance>())
		, m_filter(filter)
		, m_copy(copy)
		, m_prefilter_program("filter/prefilter_envmap")
	{
		static cstring options[2] = { "RADIANCE_ENVMAP", "RADIANCE_ARRAY" };
		m_shader_block->m_options = { options, 2 };
	}

	void BlockRadiance::init_gfx_block()
	{
		u_prefilter.createUniforms();
		u_radiance.createUniforms();
	}

	void BlockRadiance::begin_gfx_block(Render& render)
	{
		if(!render.m_environment || !render.m_environment->m_radiance.m_texture)
			return;
			
		this->prefilter_radiance(render, render.m_environment->m_radiance);
	}

	void BlockRadiance::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockRadiance::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockRadiance::submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass);
		bgfx::TextureHandle radiance = render.m_environment->m_radiance.m_roughness_array;

		if(bgfx::isValid(radiance))
		{
			bgfx::setTexture(uint8_t(TextureSampler::Radiance), u_radiance.s_radiance_map, radiance);
			element.m_shader_version.set_option(m_index, RADIANCE_ENVMAP);
		}
	}

	void BlockRadiance::prefilter_radiance(Render& render, Radiance& radiance)
	{
		if(render.m_environment->m_radiance.m_preprocessed == true)
			return;

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

		uint16_t width = uint16_t(render.m_target->m_size.x); //radiance.m_texture->m_width;
		uint16_t height = uint16_t(render.m_target->m_size.y); //radiance.m_texture->m_height;

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

		uint8_t view_id = render.preprocess_pass();

		if(blit_support)
		{
			bgfx::blit(view_id, radiance_array, 0, 0, 0, 0, radiance.m_texture->m_texture, 0, 0, 0, 0, width, height, 1);
		}
		else
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, radiance.m_texture->m_texture, GFX_TEXTURE_CLAMP);

			FrameBuffer render_target = { uvec2(width, height), bgfx::createFrameBuffer(1, &radiance_array, false) };
			m_filter.render_quad(render_target, view_id, m_copy.m_program.default_version(), { Rect4, Zero4, true });
		}

		for(uint16_t i = 1; i < roughness_levels; i++)
		{
#ifdef MUD_RADIANCE_MIPMAPS
			width >>= 1;
			height >>= 1;
#endif

			FrameBuffer copy_target = { uvec2(width, height), format, GFX_TEXTURE_POINT };

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

			m_filter.render_quad(copy_target, view_id, m_prefilter_program.default_version(), { Rect4, Zero4, true });

			if(blit_support)
			{
				bgfx::blit(view_id, radiance_array, 0, 0, 0, i, bgfx::getTexture(copy_target.m_fbo), 0, 0, 0, 0, width, height, 1);
			}
			else
			{
#ifdef MUD_RADIANCE_MIPMAPS
				bgfx::Attachment attachment = { radiance_array, i, 0 };
#else
				bgfx::Attachment attachment = { radiance_array, 0, i };
#endif
				FrameBuffer render_target = { uvec2(width, height), bgfx::createFrameBuffer(1, &attachment, false) };
				m_copy.submit_quad(render_target, view_id, bgfx::getTexture(copy_target.m_fbo), { Rect4, Zero4, true });
			}

			bgfx::frame();
		}

		m_prefiltered[radiance.m_texture->m_texture.idx] = radiance.m_roughness_array.idx;
		radiance.m_preprocessed = true;
	}
}

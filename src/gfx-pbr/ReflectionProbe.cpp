//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <math/Vec.hpp>
#include <gfx/Shot.h>
#include <gfx/RenderTarget.h>
#include <gfx/ManualRender.h>
#include <gfx/Scene.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/ReflectionProbe.h>
#endif

namespace mud
{
	constexpr size_t BlockReflection::ReflectionUniform::max_reflection_probes;

	ReflectionProbe::ReflectionProbe(Node3& node)
		: m_node(node)
	{}

	ReflectionCubemap::ReflectionCubemap(uint32_t size)
		: m_size(size)
	{
		const uint64_t flags = BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT;
		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;
		if(!bgfx::isTextureValid(0, true, 1, color_format, flags))
			color_format = bgfx::TextureFormat::RGB10A2;

		m_cubemap = Texture{ bgfx::createTextureCube(size, false, 1, color_format, flags) };
		m_depth = { uvec2(size), false, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT };

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachments[2] =
			{
				{ bgfx::Access::Write, m_depth , 0, 1, BGFX_RESOLVE_AUTO_GEN_MIPS },
				{ bgfx::Access::Write, m_cubemap, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS }
			};
			m_fbo[i] = { uvec2(size), bgfx::createFrameBuffer(2, attachments, true) };
		}
	}

	BlockReflection::BlockReflection(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockReflection>())
		, m_atlas(1024, 16)
	{}

	void BlockReflection::init_block()
	{
		int max_cubemap_size = 512;
		int cube_size = max_cubemap_size;

		while(cube_size >= 32)
		{
			//m_cubemaps.push_back(cube_size);
			cube_size >>= 1;
		}
	}

	void BlockReflection::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockReflection::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockReflection::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		//uint32_t stage = uint32_t(TextureSampler::ReflectionProbe);
		//bgfx::setViewUniform(render_pass.m_index, u_uniform.s_atlas, &stage);
	}

	void BlockReflection::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(element);
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(m_atlas.m_color.valid() && m_atlas.m_size > 0)
			encoder.setTexture(uint8_t(TextureSampler::ReflectionProbe), m_atlas.m_color);

		//upload_reflection_probes(render, to_array(render.m_shot->m_reflection_probes));
	}

	void BlockReflection::upload_reflection_probes(Render& render, Pass& render_pass, span<ReflectionProbe*> probes)
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		mat4 view_matrix = inverse(render.m_camera.m_transform);

		ReflectionProbeArray<16> probe_array;

		uint16_t probe_count = 0;

		for(ReflectionProbe* probe : probes)
		{
			//probe->m_last_pass = render.m_pass_index;

			probe_array.extents_intensity[probe_count] = { probe->m_extents, probe->m_intensity };

			Colour ambient_linear = to_linear(render.m_env->m_radiance.m_ambient) * render.m_env->m_radiance.m_energy;
			probe_array.ambient[probe_count] = { to_vec3(ambient_linear), 0.f };

			probe_array.atlas_rect[probe_count] = { m_atlas.probe_rect(*probe) };
			probe_array.matrix[probe_count] = view_matrix * probe->m_node.m_transform;

			probe_count++;
		}

		if(probe_count > 0)
			u_uniform.setUniforms(encoder, probe_array, probe_count);

		encoder.setUniform(u_uniform.u_count, &probe_array.counts);
		encoder.setUniform(u_uniform.u_indices, probe_array.indices, probe_count);
	}

	ReflectionCubemap& BlockReflection::find_cubemap(uint16_t size)
	{
		for(ReflectionCubemap& cubemap : m_cubemaps)
			if(cubemap.m_size > size * 2)
				return cubemap;
		return m_cubemaps[0];
	}

	void BlockReflection::render_reflection_probe(Render& render, ReflectionProbe& probe)
	{
		static const vec3 view_normal[6] = { -X3,  X3, -Y3,  Y3, -Z3,  Z3 };
		static const vec3 view_up[6] = { -Y3, -Y3, -Z3,  Z3, -Y3, -Y3 };

		uvec4 atlas_rect = m_atlas.render_update(render, probe);

		ReflectionCubemap& cubemap = find_cubemap(uint16_t(atlas_rect.width));

		for(int i = 0; i < 6; ++i)
		{
			vec3 edge = view_normal[i] * probe.m_extents;
			float range = abs(dot(view_normal[i], edge));

			mat4 transform = probe.m_node.m_transform * bxlookat(vec3(0.f), view_normal[i], view_up[i]);
			mat4 projection = bxproj(90.f, 1.f, 0.01f, range, bgfx::getCaps()->homogeneousDepth);

			RenderFunc renderer = m_gfx.renderer(Shading::Volume);

			ManualRender probe_render = { render, Shading::Volume,  cubemap.m_fbo[i], uvec4(Rect4), transform, projection };
			//probe_render.cull();
			probe_render.render(m_gfx.m_renderer, renderer);
		}
	}

	void pass_probes(GfxSystem& gfx, Render& render)
	{
		static BlockReflection& block_reflection = *gfx.m_renderer.block<BlockReflection>();

		Pass render_pass = render.next_pass("probes", PassType::Probes);

		block_reflection.m_reflection_multiplier = 1.f;

#if 0
		for(ReflectionProbe* probe : render.m_shot->m_reflection_probes)
		{
			if(!probe->m_dirty)
				continue;

			m_block_reflection.render_reflection_probe(render, *probe);
			//prefilter_reflection_probe(*probe);
		}
#endif

		block_reflection.m_reflection_multiplier = 0.f;
	}
}

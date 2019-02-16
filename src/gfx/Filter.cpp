//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <math/Vec.hpp>
#include <geom/Primitive.h>
#include <gfx/Types.h>
#include <gfx/Filter.h>
#include <gfx/RenderTarget.h>
#include <gfx/Camera.h>
#include <gfx/Program.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#endif

#include <cstdio>
#include <cassert>

namespace mud
{
	BlockFilter::BlockFilter(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, *this)
		, m_quad_program(gfx_system.programs().create("filter/quad"))
	{
		static cstring options[5] = {
			"UNPACK_DEPTH",
			"SOURCE_DEPTH",
			"SOURCE_0_CUBE",
			"SOURCE_0_ARRAY",
			"FILTER_DEBUG_UV"
		};
		m_shader_block->m_options = { options, 5 };
	}

	void BlockFilter::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockFilter::begin_render(Render& render)
	{
		UNUSED(render);
		//this->set_uniforms(render);
	}

	void BlockFilter::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	struct GpuTargetRect
	{
		attr_ gpu_ vec2 rect_size;
		attr_ gpu_ vec2 pixel_size;
	};

	void BlockFilter::set_uniforms(Render& render, bgfx::Encoder& encoder)
	{
		render.set_uniforms(encoder);

		vec4 camera_params{ render.m_camera.m_near, render.m_camera.m_far,
							render.m_camera.m_fov, render.m_camera.m_aspect };
		encoder.setUniform(u_uniform.u_camera_params, &camera_params);

		vec4 screen_params{ vec2(render.m_target->m_size),
							1.0f / vec2(render.m_target->m_size) };
		encoder.setUniform(u_uniform.u_screen_size_pixel_size, &screen_params);
	}

	struct ScreenQuadVertex
	{
		vec3 m_pos;
		uint32_t m_rgba;
		vec2 m_texcoord;

		static bgfx::VertexDecl& decl()
		{
			static bgfx::VertexDecl decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour | VertexAttribute::TexCoord0);
			return decl;
		}
	};

	static void draw_quad(const vec2& size, bool fbo_flip)
	{
		if(3 == bgfx::getAvailTransientVertexBuffer(3, ScreenQuadVertex::decl()))
		{
			bgfx::TransientVertexBuffer vertexbuffer;
			bgfx::allocTransientVertexBuffer(&vertexbuffer, 3, ScreenQuadVertex::decl());

			const float zz = -1.0f;

			const vec2 min = { -size.x, 0.f };
			const vec2 max = { size.x, size.y * 2.0f };

			vec2 min_uv = { -1.0f, 0.0f };
			vec2 max_uv = {  1.0f, 2.0f };

			if(fbo_flip && bgfx::getCaps()->originBottomLeft)
			{
				min_uv = { -1.0f,  1.0f };
				max_uv = {  1.0f, -1.0f };
			}

			ScreenQuadVertex* vertex = (ScreenQuadVertex*)vertexbuffer.data;
			vertex[0] = { { min.x, min.y, zz }, 0xffffffff, { min_uv.x, min_uv.y } };
			vertex[1] = { { max.x, max.y, zz }, 0xffffffff, { max_uv.x, max_uv.y } };
			vertex[2] = { { max.x, min.y, zz }, 0xffffffff, { max_uv.x, min_uv.y } };

			bgfx::setVertexBuffer(0, &vertexbuffer);
		}
	}

	static void draw_unit_quad(bool fbo_flip)
	{
		draw_quad({ 1.f, 1.f }, fbo_flip);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		if(quad.m_source.z > 1.f || quad.m_source.w > 1.f)
			printf("WARNING: Source rect expected in relative coordinates\n");

#ifdef _DEBUG
		bgfx::setViewName(view, "quad");
#endif
		bgfx::setViewFrameBuffer(view, fbo);
		bgfx::setViewTransform(view, value_ptr(target.m_screen_view), value_ptr(target.m_screen_proj));
		bgfx::setViewRect(view, uint16_t(quad.m_dest.x), uint16_t(quad.m_dest.y), uint16_t(rect_w(quad.m_dest)), uint16_t(rect_h(quad.m_dest)));

		draw_unit_quad(quad.m_fbo_flip);
		//draw_quad(rect_w(quad.m_dest), rect_h(quad.m_dest));

		bgfx::setUniform(u_uniform.u_source_0_crop, &quad.m_source);

		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW | flags);
		bgfx::submit(view, program);

		if(render)
			bgfx::frame();
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags, bool render)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, fbo, program, quad, flags, render);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		this->submit_quad(target, view, target.m_fbo, program, quad, flags, render); // BGFX_INVALID_HANDLE
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags, bool render)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, program, quad, flags, render);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, uint64_t flags, bool render)
	{
		vec4 rect = vec4(vec2(0.f), vec2(target.m_size));
		RenderQuad quad = { target.source_quad(rect), target.dest_quad(rect), true };
		this->submit_quad(target, view, program, quad, flags, render);
	}

	BlockCopy::BlockCopy(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program(gfx_system.programs().create("filter/copy"))
	{
		m_program.register_block(filter);
	}

	void BlockCopy::init_block()
	{}

	void BlockCopy::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, texture, GFX_TEXTURE_CLAMP);
		m_filter.submit_quad(target, view, fbo, m_program.default_version(), quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, fbo, texture, quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags)
	{
		this->submit_quad(target, view, target.m_fbo, texture, quad, flags); // BGFX_INVALID_HANDLE
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, texture, quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, uint64_t flags)
	{
		vec4 rect = vec4(vec2(0.f), vec2(target.m_size));
		RenderQuad quad = { target.source_quad(rect), target.dest_quad(rect), true };
		this->submit_quad(target, view, texture, quad, flags);
	}

	void BlockCopy::debug_show_texture(Render& render, bgfx::TextureHandle texture, const vec4& rect, bool is_depth, bool is_depth_packed, bool is_array, int level)
	{
		assert(render.m_target);
		vec4 dest = rect == vec4(0.f) ? vec4(vec2(0.f), vec2(render.m_target->m_size) * 0.25f) : rect;;
		RenderQuad target_quad = { Rect4, render.m_target->dest_quad(dest, true) };

		ShaderVersion shader_version = { &m_program };
		if(is_depth)
			shader_version.set_option(m_filter.m_index, FILTER_SOURCE_DEPTH);
		if(is_depth_packed)
			shader_version.set_option(m_filter.m_index, FILTER_UNPACK_DEPTH);
		if(is_array)
			shader_version.set_option(m_filter.m_index, FILTER_SOURCE_0_ARRAY);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, texture, GFX_TEXTURE_CLAMP);
		bgfx::setUniform(m_filter.u_uniform.u_source_0_level, &level);

		uint8_t view = render.debug_pass();
		m_filter.submit_quad(*render.m_target, view, BGFX_INVALID_HANDLE, m_program.version(shader_version), target_quad, 0);
	}
}
//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <geom/Primitive.h>
#include <gfx/Generated/Types.h>
#include <gfx/Filter.h>
#include <gfx/RenderTarget.h>
#include <gfx/Camera.h>
#include <gfx/Program.h>
#endif

namespace mud
{
	BlockFilter::BlockFilter(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, *this)
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

	void BlockFilter::init_gfx_block()
	{
		u_uniform.createUniforms();
	}

	void BlockFilter::begin_gfx_block(Render& render)
	{
		this->set_uniforms(render);
	}

	void BlockFilter::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockFilter::set_uniforms(Render& render)
	{
		render.set_uniforms();

		vec4 camera_params{ render.m_camera.m_near, render.m_camera.m_far,
							render.m_camera.m_fov, render.m_camera.m_aspect };
		bgfx::setUniform(u_uniform.u_camera_params, &camera_params);

		vec4 screen_params{ vec2(render.m_target->m_size),
							1.0f / vec2(render.m_target->m_size) };
		bgfx::setUniform(u_uniform.u_screen_size_pixel_size, &screen_params);
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

	static void draw_quad(const vec2& size, bool source_fbo)
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

			if(source_fbo && bgfx::getCaps()->originBottomLeft)
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

	static void draw_unit_quad(bool source_fbo)
	{
		draw_quad({ 1.f, 1.f }, source_fbo);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags)
	{
		float y = quad.m_dest.y;
		if(quad.m_relative && bgfx::getCaps()->originBottomLeft)
			y = target.m_size.y - quad.m_dest.y - rect_h(quad.m_dest);

#if _DEBUG
		bgfx::setViewName(view, "quad");
#endif
		bgfx::setViewFrameBuffer(view, fbo);
		bgfx::setViewTransform(view, value_ptr(target.m_screen_view), value_ptr(target.m_screen_proj));
		if(quad.m_dest == Zero4)
			bgfx::setViewRect(view, 0, 0, uint16_t(target.m_size.x), uint16_t(target.m_size.y));
		else
			bgfx::setViewRect(view, uint16_t(quad.m_dest.x), uint16_t(y), uint16_t(rect_w(quad.m_dest)), uint16_t(rect_h(quad.m_dest)));

		draw_unit_quad(quad.m_source_fbo);
		//draw_quad(rect_w(quad.m_dest), rect_h(quad.m_dest));

		// @todo fix this mess, either receive relative crop and dest rects, or pixel size crop and dest rects
		if(quad.m_source != Rect4)
		{
			vec4 crop = vec4(rect_offset(quad.m_source) / vec2(target.m_size), rect_size(quad.m_source) / vec2(target.m_size));
			if(!quad.m_relative && bgfx::getCaps()->originBottomLeft)
				crop.y = 1.f - crop.y - rect_h(crop);
			bgfx::setUniform(u_uniform.u_source_0_crop, &crop);
		}
		else
		{
			bgfx::setUniform(u_uniform.u_source_0_crop, &quad.m_source);
		}

		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW | flags);
		bgfx::submit(view, program);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags)
	{
		this->submit_quad(target, view, target.m_fbo, program, quad, flags); // BGFX_INVALID_HANDLE
	}

	void BlockFilter::render_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad)
	{
		this->submit_quad(target, view, program, quad);
		bgfx::frame();
	}

	BlockCopy::BlockCopy(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program("filter/copy")
	{
		m_program.register_block(filter);
	}

	void BlockCopy::init_gfx_block()
	{}

	void BlockCopy::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, texture, GFX_TEXTURE_CLAMP);
		m_filter.submit_quad(target, view, fbo, m_program.default_version(), quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags)
	{
		this->submit_quad(target, view, target.m_fbo, texture, quad, flags); // BGFX_INVALID_HANDLE
	}

	void BlockCopy::debug_show_texture(FrameBuffer& target, bgfx::TextureHandle texture, bool is_depth, bool is_depth_packed, bool is_array, int level)
	{
		uint8_t view_id = 251;

		RenderQuad target_quad = RenderQuad{ Rect4,{ vec2(0.f), vec2(target.m_size) * 0.33f }, true };

		ShaderVersion shader_version = { &m_program };
		if(is_depth)
			shader_version.set_option(m_filter.m_index, FILTER_SOURCE_DEPTH);
		if(is_depth_packed)
			shader_version.set_option(m_filter.m_index, FILTER_UNPACK_DEPTH);
		if(is_array)
			shader_version.set_option(m_filter.m_index, FILTER_SOURCE_0_ARRAY);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, texture, GFX_TEXTURE_CLAMP);
		bgfx::setUniform(m_filter.u_uniform.u_source_0_level, &level);

		m_filter.submit_quad(target, view_id, BGFX_INVALID_HANDLE, m_program.version(shader_version), target_quad, 0);
	}
}
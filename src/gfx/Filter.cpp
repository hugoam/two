//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
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
	BlockFilter::BlockFilter(GfxSystem& gfx)
		: GfxBlock(gfx, *this)
		, m_quad_program(gfx.programs().create("filter/quad"))
	{
		gfx.m_filter = this;

		static cstring options[] = {
			"UNPACK_DEPTH",
			"SOURCE_DEPTH",
			"SOURCE_0_CUBE",
			"SOURCE_0_ARRAY",
			"FILTER_DEBUG_UV"
		};
		m_shader_block->m_options = options;
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

	RenderQuad BlockFilter::render_quad(FrameBuffer& source, const vec4& source_rect, FrameBuffer& dest, const vec4& dest_rect, bool fbo_flip)
	{
		return { source.source_quad(source_rect, true), dest.dest_quad(dest_rect, true), fbo_flip };
	}

	void BlockFilter::source0(Texture& texture, ProgramVersion& program, int level, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), u_uniform.s_source_0, texture, flags);

		const vec4 levels = { float(level), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_source_levels, &levels);

		program.set_option(m_index, SOURCE_DEPTH, texture.m_is_depth);
		program.set_option(m_index, UNPACK_DEPTH, texture.m_is_depth_packed);
		program.set_option(m_index, SOURCE_0_ARRAY, texture.m_is_array);
		program.set_option(m_index, SOURCE_0_CUBE, texture.m_is_cube);
	}

	void BlockFilter::source0(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), u_uniform.s_source_0, texture, flags);
	}

	void BlockFilter::source1(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source1), u_uniform.s_source_1, texture, flags);
	}

	void BlockFilter::source2(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source2), u_uniform.s_source_2, texture, flags);
	}

	void BlockFilter::source3(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source3), u_uniform.s_source_3, texture, flags);
	}

	void BlockFilter::sourcedepth(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::SourceDepth), u_uniform.s_source_depth, texture, flags);
	}

	void BlockFilter::uniform(const Pass& pass, const string& name, const vec4& value)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], &value);
	}

	void BlockFilter::uniforms(const Pass& pass, const string& name, const vec4* value, uint16_t num)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, num, bgfx::UniformFreq::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], value, num);
	}

	struct GpuTargetRect
	{
		attr_ gpu_ vec2 rect_size;
		attr_ gpu_ vec2 pixel_size;
	};

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

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		if(quad.m_source.width > 1.f || quad.m_source.height > 1.f)
			printf("WARNING: Source rect expected in relative coordinates\n");

		static mat4 mview = bxidentity();
		static mat4 proj = bxortho({ 0.f, 1.f, 1.f, 0.f }, 0.f, 1.f, 0.f, bgfx::getCaps()->homogeneousDepth);// false))

#ifdef _DEBUG
		bgfx::setViewName(pass.m_index, pass.m_name.c_str());
#endif
		bgfx::setViewFrameBuffer(pass.m_index, fbo);
		bgfx::setViewTransform(pass.m_index, value_ptr(mview), value_ptr(proj));
		bgfx::setViewRect(pass.m_index, uint16_t(quad.m_dest.x), uint16_t(quad.m_dest.y), uint16_t(quad.m_dest.width), uint16_t(quad.m_dest.height));

		draw_unit_quad(quad.m_fbo_flip);
		//draw_quad(quad.m_dest.width, quad.m_dest.height);

		bgfx::setUniform(u_uniform.u_source_crop, &quad.m_source);

		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW | flags);
		bgfx::submit(pass.m_index, program);

		if(render)
			bgfx::frame();
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		this->quad(pass, fbo, program.fetch(), quad, flags, render);
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const uvec4& rect, uint64_t flags, bool render)
	{
		this->quad(pass, fbo, program.fetch(), fbo.render_quad(vec4(rect), true), flags, render);
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, uint64_t flags, bool render)
	{
		const vec4 rect = vec4(vec2(0.f), vec2(fbo.m_size));
		this->quad(pass, fbo, program.fetch(), fbo.render_quad(rect, true), flags, render);
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, Program& program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		this->quad(pass, fbo, program.default_version(), quad, flags, render);
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, Program& program, const uvec4& rect, uint64_t flags, bool render)
	{
		this->quad(pass, fbo, program.default_version(), fbo.render_quad(vec4(rect), true), flags, render);
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, Program& program, uint64_t flags, bool render)
	{
		const vec4 rect = vec4(vec2(0.f), vec2(fbo.m_size));
		this->quad(pass, fbo, program.default_version(), fbo.render_quad(rect, true), flags, render);
	}

	BlockCopy::BlockCopy(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/copy"))
	{
		gfx.m_copy = this;

		m_program.register_block(filter);
	}

	void BlockCopy::init_block()
	{}

	void BlockCopy::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, const RenderQuad& quad, uint64_t flags)
	{
		ProgramVersion program = { &m_program };
		m_filter.source0(texture, program, GFX_TEXTURE_CLAMP);
		m_filter.quad(pass, fbo, program, quad, flags);
	}

	void BlockCopy::quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, const uvec4& rect, uint64_t flags)
	{
		this->quad(pass, fbo, texture, fbo.render_quad(vec4(rect), true), flags);
	}

	void BlockCopy::quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, uint64_t flags)
	{
		vec4 rect = vec4(vec2(0.f), vec2(fbo.m_size));
		this->quad(pass, fbo, texture, fbo.render_quad(rect, true), flags);
	}

	void BlockCopy::debug_show_texture(Render& render, Texture& texture, const vec4& rect, int level)
	{
		assert(render.m_target);
		const vec4 dest = rect == vec4(0.f) ? vec4(vec2(0.f), vec2(render.m_target->m_size) * 0.25f) : rect;
		const RenderQuad target_quad = { Rect4, render.m_target->dest_quad(dest, true) };

		ProgramVersion program = { &m_program };
		m_filter.source0(texture, program, level, GFX_TEXTURE_CLAMP);

		Pass pass; pass.m_index = render.debug_pass();
		m_filter.quad(pass, render.m_target->m_backbuffer, program, target_quad, 0);
	}
}

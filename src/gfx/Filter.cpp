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

		m_options = {
			"UNPACK_DEPTH",
			"SOURCE_DEPTH",
			"SOURCE_0_CUBE",
			"SOURCE_0_ARRAY",
			"FILTER_DEBUG_UV"
		};
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

	void BlockFilter::multiply(float mul)
	{
		m_multiply = mul;
	}

	void BlockFilter::source0p(Texture& texture, ProgramVersion& program, int level, uint32_t flags)
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

	void BlockFilter::uniform(const Pass& pass, const string& name, const mat4& value)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Mat4, 1U, bgfx::UniformFreq::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], &value);
	}

	void BlockFilter::uniform(const Pass& pass, const string& name, const vec4& value)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], &value);
	}

	void BlockFilter::uniforms(const Pass& pass, const string& name, span<float> values)
	{
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, values.size() / 4, bgfx::UniformFreq::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], values.data(), values.size() / 4);
	}

	void BlockFilter::uniforms4(const Pass& pass, const string& name, span<vec4> values)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, values.size(), bgfx::UniformFreq::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], values.data(), values.size());
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

	void BlockFilter::submit(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		const ushort2 pos = ushort2(floor(quad.m_dest.pos * vec2(fbo.m_size)));
		const ushort2 size = ushort2(ceil((quad.m_dest.pos + quad.m_dest.size) * vec2(fbo.m_size))) - pos;

		ushort4 rect = ushort4(pos, size);
		if(quad.m_relative && bgfx::getCaps()->originBottomLeft)
			rect.y = ushort(fbo.m_size.y) - rect.y - rect.height;

		vec4 crop = quad.m_source;
		if(quad.m_blit)
			crop = vec4(rect) / vec2(fbo.m_size);
		if(!quad.m_relative && bgfx::getCaps()->originBottomLeft)
			crop.y = 1.f - crop.y - crop.height;
		
		//printf("%s crop (%f, %f) (%f, %f)\n", pass.m_name.c_str(), crop.x, crop.y, crop.width, crop.height);

		static mat4 mview = bxidentity();
		static mat4 proj = bxortho(vec4(0.f, 1.f, 1.f, 0.f), 0.f, 1.f, 0.f, bgfx::getCaps()->homogeneousDepth);// false))

#ifdef _DEBUG
		bgfx::setViewName(pass.m_index, pass.m_name.c_str());
#endif
		bgfx::setViewFrameBuffer(pass.m_index, fbo);
		bgfx::setViewTransform(pass.m_index, value_ptr(mview), value_ptr(proj));
		bgfx::setViewRect(pass.m_index, rect.x, rect.y, rect.width, rect.height);

		draw_unit_quad(quad.m_fbo_flip);
		//draw_quad(quad.m_dest.width, quad.m_dest.height);

		bgfx::setUniform(u_uniform.u_source_crop, &crop);

		const vec4 p0 = { m_multiply, 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_filter_p0, &p0);

		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW | flags);
		bgfx::submit(pass.m_index, program.fetch());

		if(render)
			bgfx::frame();

		m_multiply = 1.f;
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, uint64_t flags, bool render)
	{
		this->submit(pass, fbo, program, RenderQuad(pass.m_rect, true), flags, render);
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

	void BlockCopy::submit(const Pass& pass, FrameBuffer& fbo, Texture& texture, const RenderQuad& quad, uint64_t flags)
	{
		ProgramVersion program = { m_program };
		m_filter.source0p(texture, program, TEXTURE_CLAMP);
		m_filter.submit(pass, fbo, program, quad, flags);
	}

	void BlockCopy::quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, uint64_t flags)
	{
		this->submit(pass, fbo, texture, RenderQuad(pass.m_rect, true), flags);
	}

	void BlockCopy::debug_show_texture(Render& render, Texture& texture, const vec4& rect, int level)
	{
		assert(render.m_target);
		const vec4 dest = rect == vec4(0.f) ? vec4(vec2(0.f), vec2(0.25f)) : rect;
		const RenderQuad target_quad = { Rect4, dest };

		ProgramVersion program = { m_program };
		m_filter.source0p(texture, program, level, TEXTURE_CLAMP);

		Pass pass; pass.m_index = render.debug_pass();
		m_filter.submit(pass, render.m_target->m_backbuffer, program, target_quad, 0);
	}
}

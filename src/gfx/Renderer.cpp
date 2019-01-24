//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP20
#include <algorithm>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <jobs/JobLoop.h>
#include <gfx/Types.h>
#include <gfx/Renderer.h>
#include <gfx/Pipeline.h>
#include <gfx/Shot.h>
#include <gfx/Program.h>
#include <gfx/Viewport.h>
#include <gfx/Scene.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Skeleton.h>
#include <gfx/RenderTarget.h>
#include <gfx/Material.h>
#include <gfx/Frustum.h>
#include <gfx/GfxSystem.h>
#include <gfx/Filter.h>
#endif

#include <Tracy.hpp>

//#define MUD_GFX_JOBS

namespace mud
{
	uint8_t GfxBlock::s_block_index = 0;

	struct RenderUniform
	{
		RenderUniform() {}
		RenderUniform(int)
			: u_render_params(bgfx::createUniform("u_render_params", bgfx::UniformType::Vec4))
		{}

		bgfx::UniformHandle u_render_params;
	};

	static RenderUniform s_render_uniform;

	Render::Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame)
		: m_shading(shading), m_scene(*viewport.m_scene), m_target(&target), m_target_fbo(target.m_fbo), m_viewport(viewport)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{
		m_debug_pass_index = 245;
		static bool init_uniform = true;
		if(init_uniform)
		{
			s_render_uniform = { 0 };
			init_uniform = false;
		}
	}

	Render::Render(Shading shading, Viewport& viewport, bgfx::FrameBufferHandle& target_fbo, RenderFrame& frame)
		: m_shading(shading), m_scene(*viewport.m_scene), m_target(nullptr), m_target_fbo(target_fbo), m_viewport(viewport)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{
		m_debug_pass_index = 245;
	}

	Render::~Render()
	{}

	Pass Render::next_pass(const char* name, bool subpass)
	{
		if(!subpass)
			m_sub_pass_index = 0;

		Pass render_pass;
		render_pass.m_target = m_target;
		render_pass.m_bgfx_state = 0;
		render_pass.m_fbo = m_target_fbo;
		render_pass.m_viewport = &m_viewport;
		render_pass.m_use_mrt = m_needs_mrt;
		render_pass.m_index = m_pass_index++;
		render_pass.m_sub_pass = m_sub_pass_index++;

		render_pass.m_encoder = bgfx::begin();

		//printf("INFO: render pass %s\n", name.c_str());
		m_viewport.render_pass(name, render_pass);

		bgfx::setViewName(render_pass.m_index, name);

		return render_pass;
	}

	void Render::set_uniforms(bgfx::Encoder& encoder) const
	{
		vec4 render_params = { m_frame.m_time, float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
		encoder.setUniform(s_render_uniform.u_render_params, &render_params);
	}

	struct Renderer::Impl
	{
		vector<GfxBlock*> m_gfx_blocks;
		vector<unique<RenderPass>> m_render_passes;
	};

	Renderer::Renderer(GfxSystem& gfx_system, Pipeline& pipeline, Shading shading)
		: m_gfx_system(gfx_system)
		, m_pipeline(pipeline)
		, m_shading(shading)
		, m_impl(make_unique<Impl>())
	{}

	Renderer::~Renderer()
	{}

	void Renderer::init()
	{
		for(auto& render_pass : m_impl->m_render_passes)
			for(GfxBlock* gfx_block : render_pass->m_gfx_blocks)
			{
				if(!has_block(*gfx_block))
					add_block(*gfx_block);
			}
	}

	bool Renderer::has_block(GfxBlock& block)
	{
		return std::find(m_impl->m_gfx_blocks.begin(), m_impl->m_gfx_blocks.end(), &block) != m_impl->m_gfx_blocks.end();
	}

	void Renderer::add_block(GfxBlock& block)
	{
		m_impl->m_gfx_blocks.push_back(&block);
	}

	RenderPass& Renderer::add_pass(unique<RenderPass> render_pass)
	{ 
		m_impl->m_render_passes.emplace_back(move(render_pass));
		return *m_impl->m_render_passes.back();
	}

	void Renderer::gather(Render& render)
	{
		m_pipeline.m_gather_func(render.m_scene, render);
	}

	void Renderer::render(Render& render)
	{
		//render.m_needs_depth_prepass = true;

		for(GfxBlock* block : m_impl->m_gfx_blocks)
			block->begin_render(render);

		// @todo this temporarily fixes the MRT GL bug by forcing MRT in the shader even if not needed by any effects
		render.m_is_mrt = render.m_target && render.m_target->m_mrt;
		//render.m_is_mrt = render.m_needs_mrt && render.m_target && render.m_target->m_mrt;

		for(auto& pass : m_impl->m_render_passes)
		{
			ZoneScopedNC(pass->m_name, tracy::Color::Cyan);

			pass->blocks_begin_pass(render);
			pass->submit_render_pass(render);
		}

		render.m_frame.m_render_pass = render.m_pass_index;

		render.m_frame.m_num_draw_calls += render.m_num_draw_calls;
		render.m_frame.m_num_vertices += render.m_num_vertices;
		render.m_frame.m_num_triangles += render.m_num_triangles;
	}
	
	void Renderer::subrender(Render& render, Render& sub)
	{
		this->render(sub);
		render.m_pass_index = sub.m_pass_index;
	}

	GfxBlock::GfxBlock(GfxSystem& gfx_system, Type& type)
		: m_gfx_system(gfx_system), m_type(type), m_index(s_block_index++)
		, m_shader_block(make_unique<ShaderBlock>())
	{}

	GfxBlock::~GfxBlock()
	{}

	RenderPass::RenderPass(GfxSystem& gfx_system, const char* name, PassType pass_type)
		: m_gfx_system(gfx_system)
		, m_name(name)
		, m_pass_type(pass_type)
		, m_gfx_blocks(gfx_system.m_pipeline->pass_blocks(pass_type))
	{}

	DrawElement::DrawElement(Item& item, const Program& program, const ModelItem& model, const Material& material, const Skin* skin)
		: m_item(&item), m_program(&program), m_model(&model), m_material(&material), m_skin(skin)
		, m_shader_version(material.shader_version(program, item, model))
	{}

	struct DrawList : public vector<DrawElement>
	{
		struct SortByKey
		{
			inline bool operator()(const DrawElement& a, const DrawElement& b) { return a.m_sort_key < b.m_sort_key; }
		};

		DrawList(size_t size)
			: vector<DrawElement>(size)
		{}

		array<DrawElement> elements() { return{ this->first(), this->size() }; }

		DrawElement* first() { return &(*this)[0]; }

		DrawElement& add_element() { this->resize(this->size() + 1); return this->back(); }

		void sort() { std::sort(this->begin(), this->end(), SortByKey()); }
	};

	struct DrawPass::Impl
	{
		Impl() : m_draw_elements(0) {}
		DrawList m_draw_elements;
		vector<DrawBlock*> m_draw_blocks;
	};

	DrawPass::DrawPass(GfxSystem& gfx_system, const char* name, PassType type)
		: RenderPass(gfx_system, name, type)
		, m_impl(make_unique<Impl>())
	{
		this->init_blocks();
	}

	DrawPass::~DrawPass()
	{}

	void DrawPass::init_blocks()
	{
		for(GfxBlock* block : m_gfx_blocks)
			if(block->m_draw_block)
				m_impl->m_draw_blocks.push_back(&as<DrawBlock>(*block));

		m_draw_blocks = m_impl->m_draw_blocks;
	}

	void DrawPass::add_element(Render& render, DrawElement element)
	{
		for(DrawBlock* block : m_impl->m_draw_blocks)
			block->options(render, element.m_shader_version);

		element.m_shader_version.set_option(0, INSTANCING, !element.m_item->m_instances.empty());
		element.m_shader_version.set_option(0, BILLBOARD, element.m_item->m_flags & ItemFlag::Billboard);
		element.m_shader_version.set_option(0, SKELETON, element.m_skin != nullptr);
		element.m_shader_version.set_option(0, QNORMALS, element.m_model->m_mesh->m_qnormals);

		element.m_bgfx_program = const_cast<Program*>(element.m_program)->version(element.m_shader_version);

		m_impl->m_draw_elements.add_element() = element;
	}

	bool mask_draw_mode(uint32_t mask, DrawMode check)
	{
		return (mask & 1 << check) == 0;
	}

	inline Material& item_material(const Item& item, const ModelItem& model_item, Material& fallback)
	{
		if(item.m_material)
			return *item.m_material;
		else if(model_item.m_material)
			return *model_item.m_material;
		else if(model_item.m_mesh->m_material)
			return *model_item.m_mesh->m_material;
		else
			return fallback;
	}

	void DrawPass::gather_draw_elements(Render& render)
	{
		Material& fallback_material = m_gfx_system.debug_material();

		for(Item* item : render.m_shot->m_items)
			for(const ModelItem& model_item : item->m_model->m_items)
			{
				Material& material = item_material(*item, model_item, fallback_material);
				Program& program = *material.m_program;

				if(mask_draw_mode(material.m_base_block.m_geometry_filter, model_item.m_mesh->m_draw_mode))
					continue;

				Skin* skin = (model_item.m_skin > -1 && item->m_rig) ? &item->m_rig->m_skins[model_item.m_skin] : nullptr;

				DrawElement element = { *item, program, model_item, material, skin };
				element.m_sort_key |= uint64_t(element.m_material->m_index) << 0;
				element.m_sort_key |= uint64_t(element.m_model->m_mesh->m_index) << 16;

				this->queue_draw_element(render, element);
			}
	}

	uint32_t float_flip(uint32_t f)
	{
		uint32_t mask = -int(f >> 31) | 0x80000000;
		return f ^ mask;
	}

	// Taking highest 10 bits for rough sort of floats.
	// 0.01 maps to 752; 0.1 to 759; 1.0 to 766; 10.0 to 772;
	// 100.0 to 779 etc. Negative numbers go similarly in 0..511 range.
	uint32_t depth_to_bits(float depth)
	{
		union { float f; uint32_t i; } f2i;
		f2i.f = depth;
		f2i.i = float_flip(f2i.i); // flip bits to be sortable
		uint32_t b = f2i.i >> 22; // take highest 10 bits
		return b;
	}

	void DrawPass::submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, size_t first, size_t count) const
	{
		//printf("submit_draw_elements %i to %i\n", int(first), int(first + count));

		Pass render_pass = pass;
		render_pass.m_encoder = &encoder;

		for(size_t i = first; i < first + count; ++i)
		{
			const DrawElement& element = m_impl->m_draw_elements[i];

			for(DrawBlock* block : m_impl->m_draw_blocks)
				block->submit(render, element, render_pass);
			
			uint64_t render_state = 0 | render_pass.m_bgfx_state | element.m_bgfx_state;
			element.m_material->submit(encoder, render_state, element.m_skin);
			element.m_item->submit(encoder, render_state, *element.m_model);

			render.set_uniforms(encoder);

			encoder.setState(render_state);

			encoder.submit(render_pass.m_index, element.m_bgfx_program, depth_to_bits(element.m_item->m_depth));

			render.m_num_draw_calls += 1;
			render.m_num_vertices += element.m_model->m_mesh->m_vertex_count;
			render.m_num_triangles += element.m_model->m_mesh->m_index_count / 3;
		}
	}

	void DrawPass::submit_render_pass(Render& render)
	{
		this->blocks_begin_draw_pass(render);

		m_impl->m_draw_elements.clear();
		this->gather_draw_elements(render);

		uint8_t num_sub_passes = this->num_draw_passes(render);

		for(PassJob& job : render.m_scene.m_pass_jobs->m_jobs[size_t(m_pass_type)])
		{
			Pass render_pass = render.next_pass(m_name);
			render.set_uniforms(*render_pass.m_encoder);
			job(render, render_pass);
		}

		for(uint8_t sub_pass = 0; sub_pass < num_sub_passes; ++sub_pass)
		{
			Pass render_pass = render.next_pass(m_name, sub_pass > 0);
			this->next_draw_pass(render, render_pass);
			render.m_viewport.render_pass(m_name, render_pass);

#ifdef MUD_GFX_JOBS
			auto submit = [&](JobSystem& js, Job* job, size_t start, size_t count)
			{
				UNUSED(job);
				bgfx::Encoder& encoder = *m_gfx_system.m_encoders[js.thread()];
				this->submit_draw_elements(encoder, render, render_pass, start, count);
			};

			JobSystem& js = *m_gfx_system.m_job_system;
			Job* job = split_jobs<16>(js, nullptr, 0, uint32_t(m_impl->m_draw_elements.size()), submit);
			js.complete(job);
#else
			bgfx::Encoder& encoder = *render_pass.m_encoder;
			this->submit_draw_elements(encoder, render, render_pass, 0, m_impl->m_draw_elements.size());
#endif
		}
	}
}

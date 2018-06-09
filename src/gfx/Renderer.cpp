//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <algorithm>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
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

namespace mud
{
	uint8_t GfxBlock::s_block_index = 0;

	Render::Render(Viewport& viewport, RenderTarget& target, RenderFrame& frame)
		: m_scene(*viewport.m_scene), m_target(&target), m_target_fbo(target.m_fbo), m_viewport(viewport)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport.m_filters), m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{}

	Render::Render(Viewport& viewport, bgfx::FrameBufferHandle& target_fbo, RenderFrame& frame)
		: m_scene(*viewport.m_scene), m_target(nullptr), m_target_fbo(target_fbo), m_viewport(viewport)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport.m_filters), m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{}

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

		//printf("INFO: render pass %s\n", name.c_str());
		m_viewport.render_pass(name, render_pass);

		return render_pass;
	}

	struct RenderUniform
	{
		RenderUniform()
			: u_render_params(bgfx::createUniform("u_render_params", bgfx::UniformType::Vec4))
		{}

		bgfx::UniformHandle u_render_params;
	};

	void Render::set_uniforms()
	{
		static RenderUniform render_uniform;

		vec4 render_params = { m_frame.m_time, float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
		bgfx::setUniform(render_uniform.u_render_params, &render_params);
	}

	struct Renderer::Impl
	{
		std::vector<GfxBlock*> m_gfx_blocks;
		std::vector<unique_ptr<RenderPass>> m_render_passes;
	};

	Renderer::Renderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: m_gfx_system(gfx_system)
		, m_pipeline(pipeline)
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

	RenderPass& Renderer::add_pass(unique_ptr<RenderPass> render_pass)
	{ 
		m_impl->m_render_passes.emplace_back(std::move(render_pass));
		return *m_impl->m_render_passes.back();
	}

	void Renderer::render(Render& render)
	{
		//render.m_needs_depth_prepass = true;

		for(GfxBlock* block : m_impl->m_gfx_blocks)
			block->begin_gfx_block(render);

		// @todo this temporarily fixes the MRT GL bug by forcing MRT in the shader even if not needed by any effects
		render.m_is_mrt = render.m_target && render.m_target->m_mrt;
		//render.m_is_mrt = render.m_needs_mrt && render.m_target && render.m_target->m_mrt;

		for(auto& pass : m_impl->m_render_passes)
		{
			pass->begin_render_pass(render);
			pass->submit_render_blocks(render);
			pass->submit_render_pass(render);
		}

		render.m_frame.m_render_pass = render.m_pass_index;
	}
	
	GfxBlock::GfxBlock(GfxSystem& gfx_system, Type& type)
		: m_gfx_system(gfx_system), m_type(type), m_index(s_block_index++)
		, m_shader_block(make_unique<ShaderBlock>())
	{}

	GfxBlock::~GfxBlock()
	{}

	RenderPass::RenderPass(GfxSystem& gfx_system, const char* name, PassType pass_type)
		: m_name(name)
		, m_pass_type(pass_type)
		, m_gfx_blocks(gfx_system.m_pipeline->pass_blocks(pass_type))
	{}

	DrawElement::DrawElement(Item& item, const ModelItem& model, const Material& material, const Skin* skin)
		: m_item(&item), m_model(&model), m_material(&material), m_skin(skin)
		, m_shader_version(material.shader_version())
	{}

	struct DrawList : public std::vector<DrawElement>
	{
		struct SortByKey
		{
			inline bool operator()(const DrawElement& a, const DrawElement& b) { return a.m_sort_key < b.m_sort_key; }
		};

		DrawList(size_t size)
			: std::vector<DrawElement>(size)
		{}

		array<DrawElement> elements() { return{ this->first(), this->size() }; }

		DrawElement* first() { return &(*this)[0]; }

		DrawElement& add_element() { this->resize(this->size() + 1); return this->back(); }

		void sort() { std::sort(this->begin(), this->end(), SortByKey()); }
	};

	struct DrawPass::Impl
	{
		Impl() : m_draw_elements(1024) {}
		DrawList m_draw_elements;
		std::vector<DrawBlock*> m_draw_blocks;
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
	}

	void DrawPass::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}
	
	void DrawPass::add_element(DrawElement element)
	{
		m_impl->m_draw_elements.add_element() = element;
	}

	void DrawPass::gather_draw_elements(Render& render)
	{
		for(Item* item : render.m_shot->m_items)
			for(const ModelItem& model_item : item->m_model->m_items)
			{
				Material& material = model_item.m_mesh->m_material ? *model_item.m_mesh->m_material : *item->m_material;
				Skin* skin = (model_item.m_skin > -1 && item->m_rig) ? &item->m_rig->m_skins[model_item.m_skin] : nullptr;

				DrawElement element = { *item, model_item, material, skin };

				this->queue_draw_element(render, element);

				element.m_sort_key |= uint64_t(element.m_material->m_index) << 0;
				element.m_sort_key |= uint64_t(element.m_model->m_mesh->m_index) << 16;
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

	void DrawPass::submit_render_pass(Render& render)
	{
		for(DrawBlock* block : m_impl->m_draw_blocks)
			block->begin_gfx_pass(render);

		m_impl->m_draw_elements.clear();
		gather_draw_elements(render);

		uint8_t num_sub_passes = this->num_draw_passes(render);

		for(PassJob& job : render.m_scene.m_pass_jobs->m_jobs[size_t(m_pass_type)])
		{
			Pass render_pass = render.next_pass(m_name);
			render.set_uniforms();
			job(render_pass);
		}

		for(uint8_t sub_pass = 0; sub_pass < num_sub_passes; ++sub_pass)
		{
			Pass render_pass = render.next_pass(m_name, sub_pass > 0);
			this->next_draw_pass(render, render_pass);

			for(size_t i = 0; i < m_impl->m_draw_elements.size(); ++i)
			{
				DrawElement element = m_impl->m_draw_elements[i];

				for(DrawBlock* block : m_impl->m_draw_blocks)
					block->submit_gfx_element(render, render_pass, element);

				this->submit_draw_element(render_pass, element);

				element.m_shader_version.set_option(0, INSTANCING, !element.m_item->m_instances.empty());
				element.m_shader_version.set_option(0, BILLBOARD, element.m_item->m_flags & ITEM_BILLBOARD);
				element.m_shader_version.set_option(0, SKELETON, element.m_skin != nullptr);
				
				uint64_t render_state = 0 | render_pass.m_bgfx_state | element.m_bgfx_state;
				element.m_material->submit(render_state, element.m_skin);
				element.m_item->submit(render_state, *element.m_model);

				render.set_uniforms();

				bgfx::setState(render_state);

				bgfx::ProgramHandle program = element.m_material->m_program->version(element.m_shader_version);
				bgfx::submit(render_pass.m_index, program, depth_to_bits(element.m_item->m_depth));
			}
		}
	}
}

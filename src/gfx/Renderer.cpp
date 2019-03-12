//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
#include <infra/Sort.h>
#include <math/Vec.hpp>
#include <jobs/JobLoop.hpp>
#include <gfx/Types.h>
#include <gfx/Renderer.h>
#include <gfx/ManualRender.h>
#include <gfx/Pipeline.h>
#include <gfx/Draw.h>
#include <gfx/Shot.h>
#include <gfx/Program.h>
#include <gfx/Viewport.h>
#include <gfx/Camera.h>
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
			: u_render_p0(bgfx::createUniform("u_render_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View))
			, u_viewport_p0(bgfx::createUniform("u_viewport_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View))
			, u_camera_p0(bgfx::createUniform("u_camera_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformFreq::View))
		{}

		bgfx::UniformHandle u_render_p0;
		bgfx::UniformHandle u_viewport_p0;
		bgfx::UniformHandle u_camera_p0;
	};

	static RenderUniform s_render_uniform;

	Render::Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame)
		: m_shading(shading), m_scene(*viewport.m_scene), m_target(&target), m_target_fbo(&target), m_viewport(viewport), m_rect(viewport.m_rect)
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

	Render::Render(Shading shading, Viewport& viewport, FrameBuffer& target_fbo, RenderFrame& frame)
		: m_shading(shading), m_scene(*viewport.m_scene), m_target(nullptr), m_target_fbo(&target_fbo), m_viewport(viewport), m_rect(viewport.m_rect)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{
		m_debug_pass_index = 245;
	}

	Render::~Render()
	{}

	Pass Render::next_pass(cstring name, PassType type, bool subpass)
	{
		if(!subpass)
			m_sub_pass_index = 0;

		Pass render_pass;
		render_pass.m_target = m_target;
		render_pass.m_bgfx_state = 0;
		render_pass.m_fbo = *m_target_fbo;
		render_pass.m_viewport = &m_viewport;
		render_pass.m_rect = m_rect;
		render_pass.m_use_mrt = m_needs_mrt;
		render_pass.m_index = m_pass_index++;
		render_pass.m_sub_pass = m_sub_pass_index++;
		render_pass.m_pass_type = type;

		render_pass.m_encoder = bgfx::begin();

		bgfx::setViewName(render_pass.m_index, name);

		//printf("INFO: render pass %s\n", name.c_str());
		m_viewport.render_pass(render_pass);

		this->set_uniforms(render_pass);

		return render_pass;
	}

	Pass Render::composite_pass(cstring name, bgfx::FrameBufferHandle fbo, const uvec4& rect)
	{
		Pass render_pass = this->next_pass(name, PassType::PostProcess);
		render_pass.m_fbo = fbo;
		render_pass.m_rect = rect;
		return render_pass;
	}

	void Render::set_uniforms(const Pass& render_pass) const
	{
		vec4 render_p0 = { m_frame.m_time, float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
		bgfx::setViewUniform(render_pass.m_index, s_render_uniform.u_render_p0, &render_p0);

		if(m_target)
		{
			vec4 screen_p0{ vec2(m_target->m_size), 1.0f / vec2(m_target->m_size) };
			bgfx::setViewUniform(render_pass.m_index, s_render_uniform.u_viewport_p0, &screen_p0);
		}

		vec4 camera_p0{ m_camera.m_near, m_camera.m_far, m_camera.m_fov, m_camera.m_aspect };
		bgfx::setViewUniform(render_pass.m_index, s_render_uniform.u_camera_p0, &camera_p0);
	}

	struct DrawList : public vector<DrawElement>
	{
		struct SortByKey
		{
			inline bool operator()(const DrawElement& a, const DrawElement& b) { return a.m_sort_key < b.m_sort_key; }
		};

		DrawList(size_t size)
			: vector<DrawElement>(size)
		{}

		span<DrawElement> elements() { return{ this->first(), this->size() }; }

		DrawElement* first() { return &(*this)[0]; }

		DrawElement& add_element() { this->resize(this->size() + 1); return this->back(); }

		void sort() { quicksort<DrawElement>(*this, SortByKey()); }
	};

	struct Renderer::Impl
	{
		Impl() : m_draw_list(UINT16_MAX) {}
		DrawList m_draw_list;
	};

	Renderer::Renderer(GfxSystem& gfx)
		: m_gfx(gfx)
		, m_impl(make_unique<Impl>())
	{}

	Renderer::~Renderer()
	{}

	void Renderer::gather(Render& render)
	{
		m_gather_func(render.m_scene, render);
	}

	void Renderer::render(Render& render, RenderFunc renderer)
	{
		this->begin(render);
		renderer(m_gfx, render);
		this->end(render);
	}

	void Renderer::begin(Render& render)
	{
		//render.m_needs_depth_prepass = true;

		this->block<BlockMaterial>()->begin_render(render);

		//for(const auto& block : m_gfx_blocks)
		//	block->begin_render(render);

		// @todo this temporarily fixes the MRT GL bug by forcing MRT in the shader even if not needed by any effects
		render.m_is_mrt = render.m_target && render.m_target->m_mrt;
		//render.m_is_mrt = render.m_needs_mrt && render.m_target && render.m_target->m_mrt;
	}

	void Renderer::end(Render& render)
	{
		render.m_frame.m_render_pass = render.m_pass_index;

		render.m_frame.m_num_draw_calls += render.m_num_draw_calls;
		render.m_frame.m_num_vertices += render.m_num_vertices;
		render.m_frame.m_num_triangles += render.m_num_triangles;
	}
	
	void Renderer::subrender(Render& render, Render& sub, RenderFunc renderer)
	{
		this->render(sub, renderer);
		render.m_pass_index = sub.m_pass_index;
	}

	GfxBlock::GfxBlock(GfxSystem& gfx, Type& type)
		: m_gfx(gfx), m_type(type), m_index(++s_block_index)
		, m_shader_block(make_unique<ShaderBlock>())
	{}

	GfxBlock::~GfxBlock()
	{}

	DrawElement::DrawElement(Item& item, const Program& program, const ModelItem& model, const Material& material, const Skin* skin, uint64_t sort_key)
		: m_item(&item), m_program(&program), m_model(&model), m_material(&material), m_skin(skin)
		, m_sort_key(sort_key)
		//, m_shader_version(material.shader_version(program, item, model))
		, m_shader_version(material.shader_version(program))
	{}

	struct DrawPass
	{
		DrawList m_draw_elements;
	};

	void Renderer::shader_options(Render& render, Pass& pass, ShaderVersion& version) const
	{
		//for(GfxBlock* block : m_gfx.m_renderer.m_pass_blocks[pass.m_pass_type])
		//	if(block->m_draw_block)
		//		((DrawBlock*)block)->options(render, version);

		version.set_option(0, BUFFER_ZONES, ZONES_BUFFER);
		version.set_option(0, BUFFER_LIGHTS, LIGHTS_BUFFER);
		version.set_option(0, BUFFER_MATERIALS, MATERIALS_BUFFER);
	}

	void Renderer::add_element(Render& render, Pass& pass, DrawElement element)
	{
		this->shader_options(render, pass, element.m_shader_version);

		element.m_shader_version.set_option(0, INSTANCING, element.m_item->m_batch != nullptr);
		element.m_shader_version.set_option(0, BILLBOARD, element.m_item->m_flags & ItemFlag::Billboard);
		element.m_shader_version.set_option(0, SKELETON, element.m_skin != nullptr);
		element.m_shader_version.set_option(0, QNORMALS, element.m_model->m_mesh->m_qnormals);

		element.m_bgfx_program = const_cast<Program*>(element.m_program)->version(element.m_shader_version);

		m_impl->m_draw_list.add_element() = element;
	}

	bool mask_primitive(uint32_t mask, PrimitiveType check)
	{
		uint32_t filter = 1 << uint(check);
		return (mask & filter) == 0;
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

	DrawElement Renderer::draw_element(Item& item, const ModelItem& model_item) const
	{
		static Material& fallback_material = m_gfx.debug_material();

		const Material& material = item_material(item, model_item, fallback_material);
		const Program& program = *material.m_program;

		//if(mask_primitive(material.m_base.m_geometry_filter, model_item.m_mesh->m_primitive))
		//	continue;

		const Skin* skin = (model_item.m_skin > -1 && item.m_rig) ? &item.m_rig->m_skins[model_item.m_skin] : nullptr;

		const uint64_t sort_key = uint64_t(material.m_index) << 0
								| uint64_t(model_item.m_mesh->m_index) << 16;

		return { item, program, model_item, material, skin, sort_key };
	}

	void Renderer::clear_draw_elements(Render& render, Pass& pass)
	{
		UNUSED(render); UNUSED(pass);
		m_impl->m_draw_list.clear();
	}

	void Renderer::gather_draw_elements(Render& render, Pass& pass)
	{
		for(Item* item : render.m_shot->m_items)
			for(const ModelItem& model_item : item->m_model->m_items)
			{
				DrawElement element = this->draw_element(*item, model_item);
				this->add_element(render, pass, element);
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

	void Renderer::submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, size_t first, size_t count) const
	{
		//printf("submit_draw_elements %i to %i\n", int(first), int(first + count));

		Pass render_pass = pass;
		render_pass.m_encoder = &encoder;

		for(size_t i = first; i < first + count; ++i)
		{
			const DrawElement& element = m_impl->m_draw_list[i];
			this->submit(encoder, render, render_pass, submit, element);
		}
	}

	void Renderer::submit(bgfx::Encoder& encoder, Render& render, Pass& render_pass, Submit submit, const DrawElement& element) const
	{
		//for(GfxBlock* block : m_gfx.m_renderer.m_pass_blocks[render_pass.m_pass_type])
		//	if(block->m_draw_block)
		//		((DrawBlock*)block)->submit(render, element, render_pass);

		if(submit)
			submit(m_gfx, render, render_pass, element);

		uint64_t render_state = 0 | render_pass.m_bgfx_state | element.m_bgfx_state;
		element.m_material->submit(*element.m_program, encoder, render_state, element.m_skin);
		element.m_item->submit(encoder, render_state, *element.m_model);

		encoder.setState(render_state);

		encoder.submit(render_pass.m_index, element.m_bgfx_program, depth_to_bits(element.m_item->m_depth));

		render.m_num_draw_calls += 1;
		render.m_num_vertices += element.m_model->m_mesh->m_vertex_count;
		render.m_num_triangles += element.m_model->m_mesh->m_index_count / 3;
	}

	void Renderer::begin_render_pass(Render& render, PassType pass_type)
	{
		//this->clear_draw_elements(render);
		//this->gather_draw_elements(render);

		for(PassJob& job : render.m_scene.m_pass_jobs->m_jobs[pass_type])
		{
			Pass render_pass = render.next_pass("job", pass_type); // render_pass.m_name);
			job(render, render_pass);
		}
	}

	void Renderer::submit_render_pass(Render& render, Pass& render_pass, Submit submit)
	{
		render.m_viewport.render_pass(render_pass);

		m_gfx.m_renderer.block<BlockMaterial>()->submit(render, render_pass);

		//for(GfxBlock* block : m_gfx.m_renderer.m_pass_blocks[render_pass.m_pass_type])
		//	if(block->m_draw_block)
		//		((DrawBlock*)block)->submit(render, render_pass);

#ifdef MUD_GFX_JOBS
		auto submit = [&](JobSystem& js, Job* job, size_t start, size_t count)
		{
			UNUSED(job);
			bgfx::Encoder& encoder = *m_gfx.m_encoders[js.thread()];
			this->submit_draw_elements(encoder, render, render_pass, start, count);
		};

		JobSystem& js = *m_gfx.m_job_system;
		Job* job = split_jobs<16>(js, nullptr, 0, uint32_t(m_impl->m_draw_elements.size()), submit);
		js.complete(job);
#else
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		this->submit_draw_elements(encoder, render, render_pass, submit, 0, m_impl->m_draw_list.size());
#endif
	}

	void Renderer::pass(Render& render, Pass& render_pass, Enqueue enqueue, Submit submit)
	{
		this->begin_render_pass(render, render_pass.m_pass_type);

		this->clear_draw_elements(render, render_pass);

		for(Item* item : render.m_shot->m_items)
			for(const ModelItem& model_item : item->m_model->m_items)
			{
				enqueue(m_gfx, render, render_pass, this->draw_element(*item, model_item));
			}

		this->submit_render_pass(render, render_pass, submit);
	}

	ManualRender::ManualRender(Render& render, Shading shading, FrameBuffer& fbo, const uvec4& viewport_rect)
		: m_render(render)
		, m_camera()
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_sub_render(shading, m_viewport, fbo, render.m_frame)
	{
		m_sub_render.m_shot->m_lights = m_render.m_shot->m_lights;
	}

	ManualRender::ManualRender(Render& render, Shading shading, FrameBuffer& fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection, bool ortho)
		: m_render(render)
		, m_camera(transform, projection, ortho)
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_sub_render(shading, m_viewport, fbo, render.m_frame)
	{
		m_sub_render.m_shot->m_lights = m_render.m_shot->m_lights;
	}

	void ManualRender::render(Renderer& renderer, RenderFunc func)
	{
		renderer.render(m_sub_render, func);
		m_render.m_pass_index = m_sub_render.m_pass_index;
	}
}

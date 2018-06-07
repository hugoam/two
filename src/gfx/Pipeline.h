//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/EnumArray.h>
#endif
#include <gfx/Generated/Forward.h>
#include <gfx/Renderer.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	using PassJob = std::function<void(const Pass&)>;

	export_ struct MUD_GFX_EXPORT PassJobs
	{
#ifdef MUD_MODULES
		enum_array<PassType, std::vector<PassJob>, size_t(PassType::Count)> m_jobs;
#else
		enum_array<PassType, std::vector<PassJob>> m_jobs;
#endif
	};

	export_ class MUD_GFX_EXPORT Pipeline : public NonCopy
	{
	public:
		Pipeline(GfxSystem& gfx_system);
		~Pipeline();

		template <class T_Block>
		T_Block* block() { for(auto& block : m_gfx_blocks) if(&(block->m_type) == &type<T_Block>()) return &as<T_Block>(*block); return nullptr; }

		template <class T_Block, class... T_Args>
		T_Block& add_block(T_Args&&... args) { m_gfx_blocks.emplace_back(make_unique<T_Block>(std::forward<T_Args>(args)...)); return as<T_Block>(*m_gfx_blocks.back()); }

		array<GfxBlock*> pass_blocks(PassType pass);

		std::vector<unique_ptr<GfxBlock>> m_gfx_blocks;

#ifdef MUD_MODULES
		enum_array<PassType, std::vector<GfxBlock*>, size_t(PassType::Count)> m_pass_blocks;
#else
		enum_array<PassType, std::vector<GfxBlock*>> m_pass_blocks;
#endif
	};

	export_ class MUD_GFX_EXPORT PassClear : public RenderPass
	{
	public:
		PassClear(GfxSystem& gfx_system);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassUnshaded : public DrawPass
	{
	public:
		PassUnshaded(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
		virtual void submit_draw_element(Pass& render_pass, DrawElement& element) final;
	};

	export_ class MUD_GFX_EXPORT PassOpaque : public DrawPass
	{
	public:
		PassOpaque(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
		virtual void submit_draw_element(Pass& render_pass, DrawElement& element) final;

		size_t m_directional_light_index;
	};

	export_ class MUD_GFX_EXPORT PassBackground : public RenderPass
	{
	public:
		PassBackground(GfxSystem& gfx_system);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassAlpha : public DrawPass
	{
	public:
		PassAlpha(GfxSystem& gfx_system);
		
		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
		virtual void submit_draw_element(Pass& render_pass, DrawElement& element) final;
	};

	export_ class MUD_GFX_EXPORT PassFlip : public RenderPass
	{
	public:
		PassFlip(GfxSystem& gfx_system, BlockCopy& copy);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;

		BlockCopy& m_copy;
	};

	struct MinimalRenderer : public Renderer
	{
		MinimalRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct UnshadedRenderer : public Renderer
	{
		UnshadedRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct ClearRenderer : public Renderer
	{
		ClearRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};
}

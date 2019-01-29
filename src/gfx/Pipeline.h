//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <infra/EnumArray.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Renderer.h>

namespace mud
{
	using PassJob = void(*)(Render&, const Pass&);

	export_ MUD_GFX_EXPORT void pipeline_minimal(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred);

	export_ struct MUD_GFX_EXPORT PassJobs
	{
		enum_array<PassType, vector<PassJob>> m_jobs;
	};

	export_ class MUD_GFX_EXPORT Pipeline : public NonCopy
	{
	public:
		Pipeline(GfxSystem& gfx_system);
		~Pipeline();

		using GatherFunc = void(*)(Scene&, Render&);
		GatherFunc m_gather_func;

		template <class T_Block>
		T_Block* block() { for(auto& block : m_gfx_blocks) if(&(block->m_type) == &type<T_Block>()) return &as<T_Block>(*block); return nullptr; }

		template <class T_Block, class... T_Args>
		T_Block& add_block(T_Args&&... args) { m_gfx_blocks.push_back(make_unique<T_Block>(static_cast<T_Args&&>(args)...)); return as<T_Block>(*m_gfx_blocks.back()); }

		array<GfxBlock*> pass_blocks(PassType pass);

		vector<unique<GfxBlock>> m_gfx_blocks;

		enum_array<PassType, vector<GfxBlock*>> m_pass_blocks;
	};

	export_ class MUD_GFX_EXPORT PassClear : public RenderPass
	{
	public:
		PassClear(GfxSystem& gfx_system);

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassUnshaded : public DrawPass
	{
	public:
		PassUnshaded(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_EXPORT PassBackground : public RenderPass
	{
	public:
		PassBackground(GfxSystem& gfx_system);

		virtual void submit_render_pass(Render& render) final;
	};

	export_ class MUD_GFX_EXPORT PassFlip : public RenderPass
	{
	public:
		PassFlip(GfxSystem& gfx_system, BlockCopy& copy);

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

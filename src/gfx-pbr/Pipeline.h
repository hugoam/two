//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/EnumArray.h>
#include <gfx/Pipeline.h>
#endif
#include <gfx-pbr/Forward.h>

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT BlockGeometry : public DrawBlock
	{
	public:
		BlockGeometry(GfxSystem& gfx_system);
		~BlockGeometry();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const final;
		virtual void submit(Render& render, const Pass& render_pass) const final;

		Material* m_material = nullptr;
		Material* m_material_twosided = nullptr;
	};

	export_ class MUD_GFX_PBR_EXPORT PassOpaque : public DrawPass
	{
	public:
		PassOpaque(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;

		size_t m_direct_light_index;
	};

	export_ class MUD_GFX_PBR_EXPORT PassAlpha : public DrawPass
	{
	public:
		PassAlpha(GfxSystem& gfx_system);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;
	};

	export_ class MUD_GFX_PBR_EXPORT PassGeometry : public DrawPass
	{
	public:
		PassGeometry(GfxSystem& gfx_system, BlockGeometry& block_geometry);

		virtual void next_draw_pass(Render& render, Pass& render_pass) final;
		virtual void queue_draw_element(Render& render, DrawElement& element) final;

		BlockGeometry& m_block_geometry;
	};

	export_ class MUD_GFX_PBR_EXPORT PassLights : public RenderPass
	{
	public:
		PassLights(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void submit_render_pass(Render& render) final;
		
		BlockFilter& m_filter;
		Program* m_program;
	};

	struct ReflectionRenderer : public Renderer
	{
		ReflectionRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct ForwardRenderer : public Renderer
	{
		ForwardRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct DeferredRenderer : public Renderer
	{
		DeferredRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ MUD_GFX_PBR_EXPORT void pipeline_pbr(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred = false);
}

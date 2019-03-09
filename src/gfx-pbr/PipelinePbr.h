//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/table.h>
#include <gfx/Pipeline.h>
#endif
#include <gfx-pbr/Forward.h>

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT BlockGeometry : public DrawBlock
	{
	public:
		BlockGeometry(GfxSystem& gfx);
		~BlockGeometry();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const final;
		virtual void submit(Render& render, const Pass& render_pass) const final;
		virtual void submit(Render& render, const DrawElement& element, const Pass& render_pass) const final;

		Material* m_material = nullptr;
		Material* m_material_twosided = nullptr;
	};

	export_ MUD_GFX_PBR_EXPORT void pass_gi_probes(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void pass_shadowmaps(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void pass_shadow(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void pass_opaque(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void pass_alpha(GfxSystem& gfx, Render& render);

	export_ MUD_GFX_PBR_EXPORT void pass_geometry(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void pass_lights(GfxSystem& gfx, Render& render);

	export_ MUD_GFX_PBR_EXPORT void pass_voxel_gi(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void pass_lightmap(GfxSystem& gfx, Render& render);

	export_ MUD_GFX_PBR_EXPORT void render_pbr_forward(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void render_pbr_deferred(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void render_shadow(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void render_voxel(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void render_lightmap(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_PBR_EXPORT void render_reflection(GfxSystem& gfx, Render& render);

	export_ MUD_GFX_PBR_EXPORT void gather_gi_probes(Scene& scene, vector<GIProbe*>& gi_probes);
	export_ MUD_GFX_PBR_EXPORT void gather_lightmaps(Scene& scene, vector<LightmapAtlas*>& atlases);
	export_ MUD_GFX_PBR_EXPORT void gather_reflection_probes(Scene& scene, vector<ReflectionProbe*>& reflection_probes);

	export_ MUD_GFX_PBR_EXPORT void pipeline_pbr(GfxSystem& gfx, Renderer& pipeline, bool deferred = false);
	
namespace gfx
{
	export_ MUD_GFX_PBR_EXPORT func_ void setup_pipeline_pbr(GfxSystem& gfx);
}
}

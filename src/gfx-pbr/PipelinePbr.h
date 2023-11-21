//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-pbr/Forward.h>

namespace two
{
	export_ class refl_ TWO_GFX_PBR_EXPORT PBRShot : public Shot
	{
	public:
		vector<ReflectionProbe*> m_reflection_probes;
		vector<GIProbe*> m_gi_probes;
		vector<LightmapAtlas*> m_lightmaps;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockGeometry : public DrawBlock
	{
	public:
		BlockGeometry(GfxSystem& gfx);
		~BlockGeometry();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const final;
		virtual void submit(Render& render, const Pass& pass) const final;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const final;

		Material* m_material = nullptr;
		Material* m_material_twosided = nullptr;
	};

	export_ TWO_GFX_PBR_EXPORT func_ void begin_pbr_render(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_gi_probes(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_shadowmaps(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_shadow(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_opaque(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_alpha(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_geometry(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_lights(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_voxel_gi(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_lightmap(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pass_begin_post(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_post_auto(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void pass_post_effects(GfxSystem& gfx, Render& render, DofBlur& dof, Glow& glow, Tonemap& tonemap, BCS& bcs);

	export_ TWO_GFX_PBR_EXPORT func_ void render_pbr_forward(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_pbr_deferred(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_shadow(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_voxel(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_lightmap(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_PBR_EXPORT func_ void render_reflection(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_PBR_EXPORT void gather_gi_probes(Scene& scene, vector<GIProbe*>& gi_probes);
	export_ TWO_GFX_PBR_EXPORT void gather_lightmaps(Scene& scene, vector<LightmapAtlas*>& atlases);
	export_ TWO_GFX_PBR_EXPORT void gather_reflection_probes(Scene& scene, vector<ReflectionProbe*>& reflection_probes);

	export_ TWO_GFX_PBR_EXPORT void gather_render_pbr(Scene& scene, Render& render);

	export_ TWO_GFX_PBR_EXPORT func_ void pipeline_pbr(GfxSystem& gfx, Renderer& pipeline, bool deferred = false);
	
namespace gfx
{
	export_ TWO_GFX_PBR_EXPORT func_ void setup_pipeline_pbr(GfxSystem& gfx);
}
}

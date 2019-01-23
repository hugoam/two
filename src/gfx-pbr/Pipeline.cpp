//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <pool/ObjectPool.h>
#include <gfx/Types.h>
#include <gfx/Api.h>
#include <gfx-pbr/Pipeline.h>
#include <gfx-pbr/Api.h>
#endif

#define DEBUG_ITEMS 0
#define DEPTH_PASS 1
#define DEBUG_GBUFFERS 0

namespace mud
{
#define MUD_GFX_STATE_DEFAULT 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL \
								| BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA

#define MUD_GFX_STATE_DEFAULT_ALPHA 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS \
									  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA

	void gather_gi_probes(Scene& scene, vector<GIProbe*>& gi_probes)
	{
		//gi_probes.reserve(m_pool->pool<GIProbe>().size());
		scene.m_pool->pool<GIProbe>().iterate([&](GIProbe& gi_probe)
		{
			gi_probes.push_back(&gi_probe);
		});
	}

	void gather_lightmaps(Scene& scene, vector<LightmapAtlas*>& atlases)
	{
		//atlases.reserve(m_pool->pool<LightmapAtlas>().size());
		scene.m_pool->pool<LightmapAtlas>().iterate([&](LightmapAtlas& atlas)
		{
			atlases.push_back(&atlas);
		});
	}

	void gather_reflection_probes(Scene& scene, vector<ReflectionProbe*>& reflection_probes)
	{
		scene.m_pool->pool<ReflectionProbe>().iterate([&](ReflectionProbe& probe)
		{
			if(probe.m_visible)
			{
				reflection_probes.push_back(&probe);
				probe.m_dirty = true; // force dirty for now
			}
		});
	}

	void gather_render_pbr(Scene& scene, Render& render)
	{
		gather_items(scene, render.m_camera, render.m_shot->m_items);
		gather_occluders(scene, render.m_camera, render.m_shot->m_occluders);
		gather_lights(scene, render.m_shot->m_lights);
		gather_gi_probes(scene, render.m_shot->m_gi_probes);
		gather_lightmaps(scene, render.m_shot->m_lightmaps);
		gather_reflection_probes(scene, render.m_shot->m_reflection_probes);

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, to_array(render.m_shot->m_items)));

		render.m_environment = &scene.m_environment;
		render.m_shot->m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}

	void pipeline_pbr(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred)
	{
		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx_system);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx_system, filter);
		BlockBlur& blur = pipeline.add_block<BlockBlur>(gfx_system, filter);

		// pipeline 
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx_system);
		BlockGeometry& geometry = pipeline.add_block<BlockGeometry>(gfx_system);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx_system, filter);
		BlockRadiance& radiance = pipeline.add_block<BlockRadiance>(gfx_system, filter, copy);
		BlockShadow& shadow = pipeline.add_block<BlockShadow>(gfx_system, depth);
		BlockLight& light = pipeline.add_block<BlockLight>(gfx_system, shadow);
		BlockReflection& reflection = pipeline.add_block<BlockReflection>(gfx_system);
		BlockGITrace& gi_trace = pipeline.add_block<BlockGITrace>(gfx_system);
		BlockGIBake& gi_bake = pipeline.add_block<BlockGIBake>(gfx_system, light, gi_trace);
		BlockLightmap& lightmap = pipeline.add_block<BlockLightmap>(gfx_system, light, gi_bake);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx_system);
		UNUSED(geometry);
		UNUSED(particles);

		// mrt
		//BlockSSAO& ssao = pipeline.add_block<BlockSSAO>(gfx_system, filter, blur);
		//BlockSSR& ssr = pipeline.add_block<BlockSSR>(gfx_system);
		//BlockSSS& sss = pipeline.add_block<BlockSSS>(gfx_system);
		BlockResolve& resolve = pipeline.add_block<BlockResolve>(gfx_system, copy);

		// effects
		BlockDofBlur& dof_blur = pipeline.add_block<BlockDofBlur>(gfx_system, filter);
		//BlockExposure& exposure = pipeline.add_block<BlockExposure>(gfx_system);
		BlockGlow& glow = pipeline.add_block<BlockGlow>(gfx_system, filter, copy, blur);
		BlockTonemap& tonemap = pipeline.add_block<BlockTonemap>(gfx_system, filter, copy);

		vector<GfxBlock*> depth_blocks = { &depth };
		vector<GfxBlock*> geometry_blocks = {};
		vector<GfxBlock*> shading_blocks = { &radiance, &light, &shadow, &gi_trace, &reflection, &lightmap };
		vector<GfxBlock*> gi_blocks = { &light, &shadow, &gi_bake };
		vector<GfxBlock*> lightmap_blocks = { &light, &shadow, &gi_trace, &lightmap };

		pipeline.m_pass_blocks[size_t(PassType::Unshaded)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Background)] = { &sky };
		pipeline.m_pass_blocks[size_t(PassType::Effects)] = { /*&ssao, &ssr, &sss,*/ &resolve };
		pipeline.m_pass_blocks[size_t(PassType::PostProcess)] = { &dof_blur/*, &exposure*/, &glow, &tonemap };

		pipeline.m_pass_blocks[size_t(PassType::VoxelGI)] = gi_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Lightmap)] = lightmap_blocks;

		// forward
		pipeline.m_pass_blocks[size_t(PassType::Depth)] = depth_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Opaque)] = shading_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Alpha)] = shading_blocks;

		// deferred
		pipeline.m_pass_blocks[size_t(PassType::Geometry)] = geometry_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Lights)] = shading_blocks;

		{
			Program& program_unshaded = gfx_system.programs().create("unshaded");
			program_unshaded.register_blocks(depth_blocks);

			Program& program_depth = gfx_system.programs().create("depth");
			program_depth.register_blocks(depth_blocks);
			
			Program& program_pbr = gfx_system.programs().create("pbr/pbr");
			program_pbr.register_blocks(shading_blocks);

			Program& program_geometry = gfx_system.programs().create("pbr/geometry");
			program_geometry.register_blocks(geometry_blocks);

			Program& program_lights = gfx_system.programs().create("pbr/lights");
			program_lights.register_blocks(shading_blocks);

			Program& program_fresnel = gfx_system.programs().create("fresnel");
			UNUSED(program_fresnel);

			Program& program_gi_voxelize = gfx_system.programs().create("gi/voxelize");
			program_gi_voxelize.register_blocks(gi_blocks);

			Program& program_gi_voxel_light = gfx_system.programs().create("gi/direct_light");
			program_gi_voxel_light.m_compute = true;
			program_gi_voxel_light.register_blocks(gi_blocks);

			Program& program_gi_voxel_bounce = gfx_system.programs().create("gi/bounce_light");
			program_gi_voxel_bounce.m_compute = true;
			program_gi_voxel_bounce.register_blocks(gi_blocks);

			Program& program_gi_voxel_output = gfx_system.programs().create("gi/output_light");
			program_gi_voxel_output.m_compute = true;
			program_gi_voxel_output.register_blocks(gi_blocks);

			Program& program_lightmap = gfx_system.programs().create("pbr/lightmap");
			program_lightmap.register_blocks(lightmap_blocks);
		}

		static ForwardRenderer forward_renderer = { gfx_system, pipeline };
		static DeferredRenderer deferred_renderer = { gfx_system, pipeline };
		static ShadowRenderer shadow_renderer = { gfx_system, pipeline };
		static VoxelRenderer voxel_renderer = { gfx_system, pipeline };
		static LightmapRenderer lightmap_renderer = { gfx_system, pipeline };

		if(deferred)
			gfx_system.set_renderer(Shading::Shaded, deferred_renderer);
		else
			gfx_system.set_renderer(Shading::Shaded, forward_renderer);

		gfx_system.set_renderer(Shading::Volume, shadow_renderer);

		gfx_system.set_renderer(Shading::Voxels, voxel_renderer);

		gfx_system.set_renderer(Shading::Lightmap, lightmap_renderer);

		pipeline.m_gather_func = gather_render_pbr;
	}

	ForwardRenderer::ForwardRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Shaded)
	{
		this->add_pass<PassGIProbes>(gfx_system, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
#if DEPTH_PASS
		this->add_pass<PassDepth>(gfx_system, *pipeline.block<BlockDepth>());
#endif
		this->add_pass<PassOpaque>(gfx_system);
		this->add_pass<PassBackground>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		this->add_pass<PassAlpha>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassEffects>(gfx_system);
		this->add_pass<PassPostProcess>(gfx_system, *pipeline.block<BlockCopy>());
		//this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	DeferredRenderer::DeferredRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Shaded)
	{
		this->add_pass<PassGIProbes>(gfx_system, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassGeometry>(gfx_system, *pipeline.block<BlockGeometry>());
		this->add_pass<PassLights>(gfx_system, *pipeline.block<BlockFilter>());
		this->add_pass<PassBackground>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		//this->add_pass<PassAlpha>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassEffects>(gfx_system);
		this->add_pass<PassPostProcess>(gfx_system, *pipeline.block<BlockCopy>());
		//this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	ShadowRenderer::ShadowRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Volume)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassShadow>(gfx_system, *pipeline.block<BlockDepth>(), *pipeline.block<BlockShadow>());
		this->init();
	}

	VoxelRenderer::VoxelRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Voxels)
	{
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassGIBake>(gfx_system, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->init();
	}

	LightmapRenderer::LightmapRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Lightmap)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassLightmap>(gfx_system, *pipeline.block<BlockLightmap>());
		this->init();
	}

	ReflectionRenderer::ReflectionRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Volume)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassOpaque>(gfx_system);
		this->add_pass<PassBackground>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		this->add_pass<PassAlpha>(gfx_system);
		this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	PassOpaque::PassOpaque(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "opaque", PassType::Opaque)
	{}

	void PassOpaque::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

#ifdef DEPTH_PASS
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_EQUAL
								     | BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;
#else
		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
#endif
	}

	void PassOpaque::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, MRT, render.m_is_mrt);

			this->add_element(render, element);
		}
	}

	PassAlpha::PassAlpha(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "alpha", PassType::Alpha)
	{}

	void PassAlpha::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);

		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT_ALPHA;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthDescending);
	}

	void PassAlpha::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled && element.m_material->m_base_block.m_is_alpha)
		{
			blend_state(element.m_material->m_base_block.m_blend_mode, element.m_bgfx_state);

			this->add_element(render, element);
		}
	}

	PassGeometry::PassGeometry(GfxSystem& gfx_system, BlockGeometry& block_geometry)
		: DrawPass(gfx_system, "geometry", PassType::Geometry)
		, m_block_geometry(block_geometry)
	{}

	void PassGeometry::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
		render_pass.m_fbo = render.m_target->m_gbuffer.m_fbo;
	}

	void PassGeometry::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, DEFERRED, true);

			this->add_element(render, element);
		}
	}

	PassLights::PassLights(GfxSystem& gfx_system, BlockFilter& filter)
		: RenderPass(gfx_system, "lights", PassType::Lights)
		, m_filter(filter)
		, m_program(&gfx_system.programs().fetch("pbr/lights"))
	{
		//m_program.register_block(*this);
	}

	void PassLights::submit_render_pass(Render& render)
	{
		Pass render_pass = render.next_pass(m_name);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		render_pass.m_encoder = &encoder;

		DrawCluster cluster;
		cluster.m_lights = render.m_shot->m_lights;
		cluster.m_shader_version = { m_program };

		for(GfxBlock* block : m_gfx_blocks)
			if(block->m_draw_block)
			{
				as<DrawBlock>(*block).begin_draw_pass(render);
				as<DrawBlock>(*block).options(render, cluster.m_shader_version);
				as<DrawBlock>(*block).submit(render, render_pass);
			}

		cluster.m_shader_version.set_option(0, MRT, render.m_is_mrt);

		encoder.setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_gbuffer.m_position);
		encoder.setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_gbuffer.m_normal);
		encoder.setTexture(uint8_t(TextureSampler::Source2), m_filter.u_uniform.s_source_2, render.m_target->m_gbuffer.m_albedo);
		encoder.setTexture(uint8_t(TextureSampler::Source3), m_filter.u_uniform.s_source_3, render.m_target->m_gbuffer.m_surface);

		m_filter.submit_quad(*render.m_target, render_pass.m_index, render.m_target_fbo,
							 m_program->version(cluster.m_shader_version), render.m_viewport.m_rect, BGFX_STATE_BLEND_ALPHA);

#if DEBUG_GBUFFERS
		if(render.m_target)
		{
			BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
			vec2 size = vec2(render.m_target->m_size) * 0.25f;
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_depth,    vec4(vec2(0.f, size.y * 0.f), size), true);
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_normal,   vec4(vec2(0.f, size.y * 1.f), size));
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_albedo,   vec4(vec2(0.f, size.y * 2.f), size));
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_surface,  vec4(vec2(0.f, size.y * 3.f), size));
		}
#endif
	}

	BlockGeometry::BlockGeometry(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGeometry>())
	{}

	BlockGeometry::~BlockGeometry()
	{}

	void BlockGeometry::init_block()
	{
		m_material = &m_gfx_system.fetch_material("geometry", "pbr/geometry");
		m_material_twosided = &m_gfx_system.fetch_material("geometry_twosided", "pbr/geometry");
		m_material_twosided->m_base_block.m_cull_mode = CullMode::None;
	}

	void BlockGeometry::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockGeometry::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);
	}
}
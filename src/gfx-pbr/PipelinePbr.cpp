//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <ecs/ECS.hpp>
#include <pool/ObjectPool.hpp>
#include <gfx/Types.h>
#include <gfx/Api.h>
#include <gfx-pbr/PipelinePbr.h>
#include <gfx-pbr/Api.h>
#endif

#define DEBUG_ITEMS 0
#define DEPTH_PASS 0
#define DEBUG_GBUFFERS 0

namespace mud
{
#define MUD_GFX_STATE_DEFAULT 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL \
								| BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA

#define MUD_GFX_STATE_DEFAULT_ALPHA 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS \
									  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA

namespace gfx
{
	void setup_pipeline_pbr(GfxSystem& gfx)
	{
		gfx.init_pipeline(pipeline_pbr);
	}
}

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

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, render.m_shot->m_items));

		render.m_env = &scene.m_env;
		render.m_shot->m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}

	void pipeline_pbr(GfxSystem& gfx, Pipeline& pipeline, bool deferred)
	{
		BlockMaterial& material = pipeline.add_block<BlockMaterial>(gfx);
		UNUSED(material);

		GfxBlock& pbr = pbr_block(gfx);

		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx, filter);
		BlockBlur& blur = pipeline.add_block<BlockBlur>(gfx, filter);

		// pipeline 
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx);
		BlockGeometry& geometry = pipeline.add_block<BlockGeometry>(gfx);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx, filter);
		BlockRadiance& radiance = pipeline.add_block<BlockRadiance>(gfx, filter, copy);
		BlockLight& light = pipeline.add_block<BlockLight>(gfx);
		BlockShadow& shadow = pipeline.add_block<BlockShadow>(gfx, depth, light);
		BlockReflection& reflection = pipeline.add_block<BlockReflection>(gfx);
		BlockGITrace& gi_trace = pipeline.add_block<BlockGITrace>(gfx);
		BlockGIBake& gi_bake = pipeline.add_block<BlockGIBake>(gfx, light, shadow, gi_trace);
		BlockLightmap& lightmap = pipeline.add_block<BlockLightmap>(gfx, light, gi_bake);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx);
		UNUSED(geometry);
		UNUSED(particles);

		// mrt
		//BlockSSAO& ssao = pipeline.add_block<BlockSSAO>(gfx, filter, blur);
		//BlockSSR& ssr = pipeline.add_block<BlockSSR>(gfx);
		//BlockSSS& sss = pipeline.add_block<BlockSSS>(gfx);
		BlockResolve& resolve = pipeline.add_block<BlockResolve>(gfx, copy);

		// effects
		BlockDofBlur& dof_blur = pipeline.add_block<BlockDofBlur>(gfx, filter);
		//BlockExposure& exposure = pipeline.add_block<BlockExposure>(gfx);
		BlockGlow& glow = pipeline.add_block<BlockGlow>(gfx, filter, copy, blur);
		BlockTonemap& tonemap = pipeline.add_block<BlockTonemap>(gfx, filter, copy);

		vector<GfxBlock*> depth_blocks = { &depth };
		vector<GfxBlock*> geometry_blocks = {};
		vector<GfxBlock*> shading_blocks = { &radiance, &light, &shadow, &gi_trace, &reflection, &lightmap, &pbr };
		vector<GfxBlock*> gi_blocks = { &light, &shadow, &gi_bake };
		vector<GfxBlock*> lightmap_blocks = { &light, &shadow, &gi_trace, &lightmap };

		pipeline.m_pass_blocks[PassType::Solid] = {};
		pipeline.m_pass_blocks[PassType::Background] = { &sky };
		pipeline.m_pass_blocks[PassType::Effects] = { /*&ssao, &ssr, &sss,*/ &resolve };
		pipeline.m_pass_blocks[PassType::PostProcess] = { &dof_blur/*, &exposure*/, &glow, &tonemap };

		pipeline.m_pass_blocks[PassType::VoxelGI] = gi_blocks;
		pipeline.m_pass_blocks[PassType::Lightmap] = lightmap_blocks;

		// forward
		pipeline.m_pass_blocks[PassType::Depth] = depth_blocks;
		pipeline.m_pass_blocks[PassType::Opaque] = shading_blocks;
		pipeline.m_pass_blocks[PassType::Alpha] = shading_blocks;

		// deferred
		pipeline.m_pass_blocks[PassType::Geometry] = geometry_blocks;
		pipeline.m_pass_blocks[PassType::Lights] = shading_blocks;

		auto create_programs = [&]()
		{
			Program& solid = gfx.programs().create("solid");
			solid.m_blocks[MaterialBlock::Alpha] = true;
			solid.m_blocks[MaterialBlock::Solid] = true;
			solid.register_blocks(depth_blocks);

			Program& normal = gfx.programs().create("normal");
			normal.m_blocks[MaterialBlock::Solid] = true;
			//normal.m_blocks[MaterialBlock::Pbr] = true;

			Program& point = gfx.programs().create("point");
			point.m_blocks[MaterialBlock::Solid] = true;
			point.m_blocks[MaterialBlock::Point] = true;
			point.m_primitives = uint32_t(1 << uint(PrimitiveType::Points));

			Program& line = gfx.programs().create("line");
			line.m_blocks[MaterialBlock::Solid] = true;
			line.m_blocks[MaterialBlock::Line] = true;
			point.m_primitives = uint32_t(1 << uint(PrimitiveType::Lines) | 1 << uint(PrimitiveType::LineStrip));

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(depth_blocks);
			depth.m_blocks[MaterialBlock::Alpha] = true;

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(depth_blocks);
			distance.m_blocks[MaterialBlock::Alpha] = true;

			Program& pbr = gfx.programs().create("pbr/pbr");
			pbr.register_blocks(shading_blocks);
			pbr.m_blocks[MaterialBlock::Alpha] = true;
			pbr.m_blocks[MaterialBlock::Pbr] = true;

			Program& geometry = gfx.programs().create("pbr/geometry");
			geometry.register_blocks(geometry_blocks);
			geometry.m_blocks[MaterialBlock::Alpha] = true;
			geometry.m_blocks[MaterialBlock::Pbr] = true;

			Program& lights = gfx.programs().create("pbr/lights");
			lights.register_blocks(shading_blocks);

			Program& fresnel = gfx.programs().create("fresnel");
			fresnel.m_blocks[MaterialBlock::Alpha] = true;
			fresnel.m_blocks[MaterialBlock::Fresnel] = true;

			Program& gi_voxelize = gfx.programs().create("gi/voxelize");
			gi_voxelize.register_blocks(gi_blocks);

			Program& gi_voxel_light = gfx.programs().create("gi/direct_light");
			gi_voxel_light.m_compute = true;
			gi_voxel_light.register_blocks(gi_blocks);

			Program& gi_voxel_bounce = gfx.programs().create("gi/bounce_light");
			gi_voxel_bounce.m_compute = true;
			gi_voxel_bounce.register_blocks(gi_blocks);

			Program& gi_voxel_output = gfx.programs().create("gi/output_light");
			gi_voxel_output.m_compute = true;
			gi_voxel_output.register_blocks(gi_blocks);

			Program& lightmap = gfx.programs().create("pbr/lightmap");
			lightmap.register_blocks(lightmap_blocks);
		};

		create_programs();

		static ForwardRenderer forward_renderer = { gfx, pipeline };
		static DeferredRenderer deferred_renderer = { gfx, pipeline };
		static ShadowRenderer shadow_renderer = { gfx, pipeline };
		static VoxelRenderer voxel_renderer = { gfx, pipeline };
		static LightmapRenderer lightmap_renderer = { gfx, pipeline };

		if(deferred)
			gfx.set_renderer(Shading::Shaded, deferred_renderer);
		else
			gfx.set_renderer(Shading::Shaded, forward_renderer);

		gfx.set_renderer(Shading::Volume, shadow_renderer);

		gfx.set_renderer(Shading::Voxels, voxel_renderer);

		gfx.set_renderer(Shading::Lightmap, lightmap_renderer);

		pipeline.m_gather_func = gather_render_pbr;

		g_viewer_ecs->init<Tonemap, BCS, Glow, DofBlur>();
	}

	ForwardRenderer::ForwardRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Shaded)
	{
		this->add_pass<PassGIProbes>(gfx, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->add_pass<PassShadowmap>(gfx, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx);
#if DEPTH_PASS
		this->add_pass<PassDepth>(gfx, *pipeline.block<BlockDepth>());
#endif
		this->add_pass<PassOpaque>(gfx);
		this->add_pass<PassBackground>(gfx);
		this->add_pass<PassParticles>(gfx);
		this->add_pass<PassAlpha>(gfx);
		this->add_pass<PassSolid>(gfx);
		this->add_pass<PassEffects>(gfx);
		this->add_pass<PassPostProcess>(gfx, *pipeline.block<BlockCopy>());
		//this->add_pass<PassFlip>(gfx, *pipeline.block<BlockCopy>());
		this->init();
	}

	DeferredRenderer::DeferredRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Shaded)
	{
		this->add_pass<PassGIProbes>(gfx, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->add_pass<PassShadowmap>(gfx, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassGeometry>(gfx, *pipeline.block<BlockGeometry>());
		this->add_pass<PassLights>(gfx, *pipeline.block<BlockFilter>());
		this->add_pass<PassBackground>(gfx);
		this->add_pass<PassParticles>(gfx);
		//this->add_pass<PassAlpha>(gfx);
		this->add_pass<PassSolid>(gfx);
		this->add_pass<PassEffects>(gfx);
		this->add_pass<PassPostProcess>(gfx, *pipeline.block<BlockCopy>());
		//this->add_pass<PassFlip>(gfx, *pipeline.block<BlockCopy>());
		this->init();
	}

	ShadowRenderer::ShadowRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Volume)
	{
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassShadow>(gfx, *pipeline.block<BlockDepth>(), *pipeline.block<BlockShadow>());
		this->init();
	}

	VoxelRenderer::VoxelRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Voxels)
	{
		this->add_pass<PassShadowmap>(gfx, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassGIBake>(gfx, *pipeline.block<BlockLight>(), *pipeline.block<BlockShadow>(), *pipeline.block<BlockGIBake>());
		this->init();
	}

	LightmapRenderer::LightmapRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Lightmap)
	{
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassLightmap>(gfx, *pipeline.block<BlockLightmap>());
		this->init();
	}

	ReflectionRenderer::ReflectionRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Volume)
	{
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassOpaque>(gfx);
		this->add_pass<PassBackground>(gfx);
		this->add_pass<PassParticles>(gfx);
		this->add_pass<PassAlpha>(gfx);
		this->add_pass<PassFlip>(gfx, *pipeline.block<BlockCopy>());
		this->init();
	}

	PassOpaque::PassOpaque(GfxSystem& gfx)
		: DrawPass(gfx, "opaque", PassType::Opaque)
	{}

	void PassOpaque::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

#if DEPTH_PASS
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_EQUAL
								     | BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;
#else
		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
#endif
	}

	void PassOpaque::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_program->m_blocks[MaterialBlock::Pbr] && !element.m_material->m_alpha.m_is_alpha)
		{
			if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, MRT, render.m_is_mrt);

			this->add_element(render, element);
		}
	}

	PassAlpha::PassAlpha(GfxSystem& gfx)
		: DrawPass(gfx, "alpha", PassType::Alpha)
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
		if(element.m_program->m_blocks[MaterialBlock::Pbr] && element.m_material->m_alpha.m_is_alpha)
		{
			blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);

			this->add_element(render, element);
		}
	}

	PassGeometry::PassGeometry(GfxSystem& gfx, BlockGeometry& block_geometry)
		: DrawPass(gfx, "geometry", PassType::Geometry)
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
		if(element.m_program->m_blocks[MaterialBlock::Pbr] && !element.m_material->m_alpha.m_is_alpha)
		{
			if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, DEFERRED, true);

			this->add_element(render, element);
		}
	}

	PassLights::PassLights(GfxSystem& gfx, BlockFilter& filter)
		: RenderPass(gfx, "lights", PassType::Lights)
		, m_filter(filter)
		, m_program(&gfx.programs().fetch("pbr/lights"))
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
				as<DrawBlock>(*block).begin_pass(render);
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
			BlockCopy& copy = *m_gfx.m_pipeline->block<BlockCopy>();
			vec2 size = vec2(render.m_target->m_size) * 0.25f;
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_depth,    vec4(vec2(0.f, size.y * 0.f), size), true);
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_normal,   vec4(vec2(0.f, size.y * 1.f), size));
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_albedo,   vec4(vec2(0.f, size.y * 2.f), size));
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_surface,  vec4(vec2(0.f, size.y * 3.f), size));
		}
#endif
	}

	BlockGeometry::BlockGeometry(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockGeometry>())
	{}

	BlockGeometry::~BlockGeometry()
	{}

	void BlockGeometry::init_block()
	{
		m_material = &m_gfx.fetch_material("geometry", "pbr/geometry");
		m_material_twosided = &m_gfx.fetch_material("geometry_twosided", "pbr/geometry");
		m_material_twosided->m_base.m_cull_mode = CullMode::None;
	}

	void BlockGeometry::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::begin_pass(Render& render)
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

	void BlockGeometry::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(render_pass);
	}
}
//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx/Types.h>
#include <gfx/Api.h>
#include <gfx-pbr/Pipeline.h>
#include <gfx-pbr/Api.h>
#endif

namespace mud
{
#define MUD_GFX_STATE_DEFAULT 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL \
								| BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA

#define MUD_GFX_STATE_DEFAULT_ALPHA 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS \
									  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA

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
		BlockGI& gi = pipeline.add_block<BlockGI>(gfx_system);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx_system);
		UNUSED(geometry);
		UNUSED(particles);
		UNUSED(gi);

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

		std::vector<GfxBlock*> depth_blocks = { &depth };
		std::vector<GfxBlock*> geometry_blocks = { &depth };
		std::vector<GfxBlock*> shading_blocks = { &radiance, &light, &shadow, &reflection };
		std::vector<GfxBlock*> gi_blocks = { &gi };

		pipeline.m_pass_blocks[size_t(PassType::Unshaded)] = { &depth };
		pipeline.m_pass_blocks[size_t(PassType::Background)] = { &sky };
		pipeline.m_pass_blocks[size_t(PassType::Effects)] = { /*&ssao, &ssr, &sss,*/ &resolve };
		pipeline.m_pass_blocks[size_t(PassType::PostProcess)] = { &dof_blur/*, &exposure*/, &glow, &tonemap };

		pipeline.m_pass_blocks[size_t(PassType::VoxelGI)] = gi_blocks;

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
			program_gi_voxelize.default_version();
		}

		static ForwardRenderer forward_renderer = { gfx_system, pipeline };
		static DeferredRenderer deferred_renderer = { gfx_system, pipeline };
		static ShadowRenderer shadow_renderer = { gfx_system, pipeline };
		static VoxelRenderer voxel_renderer = { gfx_system, pipeline };

		if(deferred)
			gfx_system.set_renderer(Shading::Shaded, deferred_renderer);
		else
			gfx_system.set_renderer(Shading::Shaded, forward_renderer);

		gfx_system.set_renderer(Shading::Volume, shadow_renderer);

		gfx_system.set_renderer(Shading::Voxels, voxel_renderer);
	}

	ForwardRenderer::ForwardRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassVoxelGI>(gfx_system, *pipeline.block<BlockGI>());
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
		//this->add_pass<PassDepth>(gfx_system, *pipeline.block<BlockDepth>());
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
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassVoxelGI>(gfx_system, *pipeline.block<BlockGI>());
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
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassShadow>(gfx_system, *pipeline.block<BlockDepth>(), *pipeline.block<BlockShadow>());
		this->init();
	}

	VoxelRenderer::VoxelRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassGI>(gfx_system, *pipeline.block<BlockGI>());
		this->init();
	}

	ReflectionRenderer::ReflectionRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
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
		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
	}

	void PassOpaque::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			element.m_shader_version.set_option(0, MRT, render.m_is_mrt);
			add_element(element);
		}
	}

	void PassOpaque::submit_draw_element(Pass& render_pass, DrawElement& element) const
	{
		UNUSED(render_pass);
		if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
			element.m_bgfx_state |= BGFX_STATE_WRITE_Z;
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
			add_element(element);
	}

	void PassAlpha::submit_draw_element(Pass& render_pass, DrawElement& element) const
	{
		UNUSED(render_pass);
		blend_state(element.m_material->m_base_block.m_blend_mode, element.m_bgfx_state);
	}

	PassGeometry::PassGeometry(GfxSystem& gfx_system, BlockGeometry& block_geometry)
		: DrawPass(gfx_system, "geometry", PassType::Geometry)
		, m_block_geometry(block_geometry)
	{}

	void PassGeometry::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
		render_pass.m_fbo = render.m_target->m_gbuffer.m_fbo;
	}

	void PassGeometry::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			element.m_shader_version.set_option(0, DEFERRED, true);
			add_element(element);
		}
	}

	void PassGeometry::submit_draw_element(Pass& render_pass, DrawElement& element) const
	{
		UNUSED(render_pass);
		if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
			element.m_bgfx_state |= BGFX_STATE_WRITE_Z;
	}

	PassLights::PassLights(GfxSystem& gfx_system, BlockFilter& filter)
		: RenderPass(gfx_system, "lights", PassType::Lights)
		, m_filter(filter)
		, m_program(&gfx_system.programs().fetch("pbr/lights"))
	{
		//m_program.register_block(*this);
	}

	void PassLights::begin_render_pass(Render& render)
	{
		UNUSED(render);
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
				as<DrawBlock>(*block).begin_gfx_pass(render);
				as<DrawBlock>(*block).submit_gfx_cluster(render, render_pass, cluster);
			}

		cluster.m_shader_version.set_option(0, MRT, render.m_is_mrt);

		encoder.setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_gbuffer.m_position);
		encoder.setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_gbuffer.m_normal);
		encoder.setTexture(uint8_t(TextureSampler::Source2), m_filter.u_uniform.s_source_2, render.m_target->m_gbuffer.m_albedo);
		encoder.setTexture(uint8_t(TextureSampler::Source3), m_filter.u_uniform.s_source_3, render.m_target->m_gbuffer.m_surface);

		m_filter.submit_quad(*render.m_target, render_pass.m_index, render.m_target_fbo,
							 m_program->version(cluster.m_shader_version), render.m_viewport.m_rect, BGFX_STATE_BLEND_ALPHA);
	}

	BlockGeometry::BlockGeometry(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGeometry>())
	{}

	BlockGeometry::~BlockGeometry()
	{}

	void BlockGeometry::init_gfx_block()
	{
		m_material = &m_gfx_system.fetch_material("geometry", "pbr/geometry");
		m_material_twosided = &m_gfx_system.fetch_material("geometry_twosided", "pbr/geometry");
		m_material_twosided->m_base_block.m_cull_mode = CullMode::None;
	}

	void BlockGeometry::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::submit_gfx_element(Render& render, const Pass& render_pass, DrawElement& element) const
	{
		UNUSED(render); UNUSED(render_pass); UNUSED(element);
	}

	void BlockGeometry::submit_gfx_cluster(Render& render, const Pass& render_pass, DrawCluster& cluster) const
	{
		UNUSED(render); UNUSED(render_pass); UNUSED(cluster);
	}
}
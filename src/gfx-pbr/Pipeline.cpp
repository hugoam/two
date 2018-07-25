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
	void pipeline_pbr(GfxSystem& gfx_system, Pipeline& pipeline)
	{
		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx_system);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx_system, filter);
		BlockBlur& blur = pipeline.add_block<BlockBlur>(gfx_system, filter);

		// pipeline 
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx_system);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx_system, filter);
		BlockRadiance& radiance = pipeline.add_block<BlockRadiance>(gfx_system, filter, copy);
		BlockShadow& shadow = pipeline.add_block<BlockShadow>(gfx_system, depth);
		BlockLight& light = pipeline.add_block<BlockLight>(gfx_system, shadow);
		BlockReflection& reflection = pipeline.add_block<BlockReflection>(gfx_system);
		//BlockGI& gi = pipeline.add_block<BlockGI>(gfx_system);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx_system);
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

		pipeline.m_pass_blocks[size_t(PassType::Depth)] = { &depth };
		pipeline.m_pass_blocks[size_t(PassType::Unshaded)] = { &depth };
		pipeline.m_pass_blocks[size_t(PassType::Background)] = { &sky };
		pipeline.m_pass_blocks[size_t(PassType::Opaque)] = { &radiance, &light, &shadow, &reflection };
		pipeline.m_pass_blocks[size_t(PassType::Alpha)] = { &radiance, &light, &shadow, &reflection };
		pipeline.m_pass_blocks[size_t(PassType::Effects)] = { /*&ssao, &ssr, &sss,*/ &resolve };
		pipeline.m_pass_blocks[size_t(PassType::PostProcess)] = { &dof_blur/*, &exposure*/, &glow, &tonemap };

		gfx_system.programs().create("unshaded", [&](Program& program) { program.register_blocks(pipeline.pass_blocks(PassType::Unshaded)); });
		gfx_system.programs().create("depth", [&](Program& program) { program.register_blocks(pipeline.pass_blocks(PassType::Depth)); });
		gfx_system.programs().create("pbr/pbr", [&](Program& program) { program.register_blocks(pipeline.pass_blocks(PassType::Opaque)); });
		gfx_system.programs().create("fresnel", [&](Program& program) { /*program.register_blocks(pipeline.pass_blocks(PassType::Unshaded));*/ });

		static MainRenderer main_renderer = { gfx_system, pipeline };
		static ShadowRenderer shadow_renderer = { gfx_system, pipeline };

		gfx_system.set_renderer(Shading::Shaded, main_renderer);
		gfx_system.set_renderer(Shading::Volume, shadow_renderer);
	}

	MainRenderer::MainRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
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

	ShadowRenderer::ShadowRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassShadow>(gfx_system, *pipeline.block<BlockDepth>(), *pipeline.block<BlockShadow>());
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
}
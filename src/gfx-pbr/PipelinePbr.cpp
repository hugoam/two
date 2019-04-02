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
		gather_items(scene, *render.m_camera, render.m_shot.m_items);
		gather_occluders(scene, *render.m_camera, render.m_shot.m_occluders);
		gather_lights(scene, render.m_shot.m_lights);
		gather_gi_probes(scene, render.m_shot.m_gi_probes);
		gather_lightmaps(scene, render.m_shot.m_lightmaps);
		gather_reflection_probes(scene, render.m_shot.m_reflection_probes);

		render.m_frustum = optimized_frustum(*render.m_camera, render.m_shot.m_items);

		render.m_shot.m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}

	void pipeline_pbr(GfxSystem& gfx, Renderer& pipeline, bool deferred)
	{
		BlockMaterial& material = pipeline.add_block<BlockMaterial>(gfx);
		BlockPbr& pbr = pipeline.add_block<BlockPbr>(gfx);
		UNUSED(material);

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
		UNUSED(sky);

		// mrt
		//BlockSSAO& ssao = pipeline.add_block<BlockSSAO>(gfx, filter, blur);
		//BlockSSR& ssr = pipeline.add_block<BlockSSR>(gfx);
		//BlockSSS& sss = pipeline.add_block<BlockSSS>(gfx);

		// effects
		BlockDofBlur& dof_blur = pipeline.add_block<BlockDofBlur>(gfx, filter);
		//BlockExposure& exposure = pipeline.add_block<BlockExposure>(gfx);
		BlockGlow& glow = pipeline.add_block<BlockGlow>(gfx, filter, copy, blur);
		BlockTonemap& tonemap = pipeline.add_block<BlockTonemap>(gfx, filter, copy);
		UNUSED(dof_blur);
		UNUSED(glow);
		UNUSED(tonemap);

		vector<GfxBlock*> depth_blocks = { &depth };
		vector<GfxBlock*> geometry_blocks = {};
		vector<GfxBlock*> shading_blocks = { &radiance, &light, &shadow, &gi_trace, &reflection, &lightmap, &pbr };
		vector<GfxBlock*> gi_blocks = { &light, &shadow, &gi_bake };
		vector<GfxBlock*> lightmap_blocks = { &light, &shadow, &gi_trace, &lightmap };

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
			line.m_primitives = uint32_t(1 << uint(PrimitiveType::Lines) | 1 << uint(PrimitiveType::LineStrip));

			Program& line_fat = gfx.programs().create("line_fat");
			line_fat.m_blocks[MaterialBlock::Solid] = true;
			line_fat.m_blocks[MaterialBlock::Line] = true;
			//line_fat.m_primitives = uint32_t(1 << uint(PrimitiveType::Lines) | 1 << uint(PrimitiveType::LineStrip));

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(depth_blocks);
			depth.m_blocks[MaterialBlock::Alpha] = true;

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(depth_blocks);
			distance.m_blocks[MaterialBlock::Alpha] = true;

			Program& pbr = gfx.programs().create("pbr/pbr");
			pbr.register_blocks(shading_blocks);
			pbr.m_blocks[MaterialBlock::Alpha] = true;
			pbr.m_blocks[MaterialBlock::Lit] = true;
			pbr.m_blocks[MaterialBlock::Pbr] = true;

			Program& phong = gfx.programs().create("pbr/phong");
			phong.register_blocks(shading_blocks);
			phong.m_blocks[MaterialBlock::Alpha] = true;
			phong.m_blocks[MaterialBlock::Lit] = true;
			phong.m_blocks[MaterialBlock::Phong] = true;

			Program& three = gfx.programs().create("pbr/three");
			three.register_blocks(shading_blocks);
			three.m_blocks[MaterialBlock::Alpha] = true;
			three.m_blocks[MaterialBlock::Lit] = true;
			three.m_blocks[MaterialBlock::Pbr] = true;

			Program& basic = gfx.programs().create("pbr/basic");
			basic.register_blocks(shading_blocks);
			basic.m_blocks[MaterialBlock::Alpha] = true;
			basic.m_blocks[MaterialBlock::Lit] = true;
			basic.m_blocks[MaterialBlock::Pbr] = true;

			Program& geometry = gfx.programs().create("pbr/geometry");
			geometry.register_blocks(geometry_blocks);
			geometry.m_blocks[MaterialBlock::Alpha] = true;
			geometry.m_blocks[MaterialBlock::Lit] = true;
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

		if(deferred)
			gfx.set_renderer(Shading::Shaded, render_pbr_deferred);
		else
			gfx.set_renderer(Shading::Shaded, render_pbr_forward);

		gfx.set_renderer(Shading::Volume, render_shadow);

		gfx.set_renderer(Shading::Voxels, render_voxel);

		gfx.set_renderer(Shading::Lightmap, render_lightmap);

		pipeline.m_gather_func = gather_render_pbr;

		g_viewer_ecs->init<Tonemap, BCS, Glow, DofBlur>();
	}

	struct PbrBlocks
	{
		BlockRadiance& radiance;
		BlockLight& light;
		BlockShadow& shadow;
		BlockGITrace& gi_trace;
		BlockReflection& reflection;
		BlockLightmap& lightmap;
	};

	span<DrawBlock*> pbr_blocks(GfxSystem& gfx)
	{
		static DrawBlock* blocks[] = {
			gfx.m_renderer.block<BlockRadiance>(),
			gfx.m_renderer.block<BlockLight>(),
			gfx.m_renderer.block<BlockShadow>(),
			gfx.m_renderer.block<BlockGITrace>(),
			gfx.m_renderer.block<BlockReflection>(),
			gfx.m_renderer.block<BlockLightmap>(),
			//*gfx.m_renderer.block<BlockPbr>()
		};
		return blocks;
	}

	void begin_pbr_render(GfxSystem& gfx, Render& render)
	{
		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->begin_render(render);
	}

	void pbr_options(GfxSystem& gfx, Render& render, ProgramVersion& version)
	{
		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->options(render, version);
	}

	void submit_pbr_pass(GfxSystem& gfx, Render& render, const Pass& pass)
	{
		static BlockLight& block_light = *gfx.m_renderer.block<BlockLight>();
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();

		block_shadow.m_direct_light = block_light.m_direct_light;
		block_shadow.commit_shadows(render, render.m_camera->m_transform);

		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->submit(render, pass);

		//block_pbr.submit(render, pass);
	}

	void submit_pbr_element(GfxSystem& gfx, Render& render, const DrawElement& element, Pass& pass)
	{
		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->submit(render, element, pass);
	}

	void render_pbr_forward(GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_gi_probes(gfx, render);
		pass_shadowmaps(gfx, render);
		pass_clear(gfx, render);
#if DEPTH_PASS
		pass_depth(gfx, render);
#endif
		pass_opaque(gfx, render);
		pass_background(gfx, render);
		pass_particles(gfx, render);
		pass_alpha(gfx, render);
		pass_solid(gfx, render);
		//pass_effects(gfx, render);
		pass_resolve(gfx, render);
		pass_post_process(gfx, render);
	}

	void render_pbr_deferred(GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_gi_probes(gfx, render);
		pass_shadowmaps(gfx, render);
		pass_clear(gfx, render);
		pass_geometry(gfx, render);
		pass_lights(gfx, render);
		pass_background(gfx, render);
		pass_particles(gfx, render);
		//pass_alpha(gfx, render);
		pass_solid(gfx, render);
	}

	void render_shadow(GfxSystem& gfx, Render& render)
	{
		//begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
		pass_shadow(gfx, render);
	}

	void render_voxel(GfxSystem& gfx, Render& render)
	{
		//begin_pbr_render(gfx, render);

		pass_shadowmaps(gfx, render);
		pass_clear(gfx, render);
		pass_voxel_gi(gfx, render);
	}

	void render_lightmap(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_lightmap(gfx, render);
	}

	void render_reflection(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
#if DEPTH_PASS
		pass_depth(gfx, render);
#endif
		pass_opaque(gfx, render);
		pass_background(gfx, render);
		pass_particles(gfx, render);
		pass_alpha(gfx, render);
	}

	void pass_opaque(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("opaque", PassType::Opaque);

		submit_pbr_pass(gfx, render, pass);

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthAscending);

		uint64_t cull = render.m_vflip ? BGFX_STATE_CULL_CCW : BGFX_STATE_CULL_CW;

#if DEPTH_PASS
		pass.m_bgfx_state = cull | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z 
								 | BGFX_STATE_DEPTH_TEST_EQUAL | BGFX_STATE_MSAA;
#else
		pass.m_bgfx_state = cull | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z 
								 | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_MSAA;
#endif

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(pass);
			bool lit = element.m_program->m_blocks[MaterialBlock::Lit] && !element.m_material->m_alpha.m_is_alpha;
			bool opaque = element.m_program->m_passes[PassType::Opaque];
			if(!lit && !opaque) return false;

			if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			if(lit)
				pbr_options(gfx, render, element.m_shader_version);
			return true;
		};

		auto submit_element = [](GfxSystem& gfx, Render& render, Pass& pass, const DrawElement& element)
		{
			submit_pbr_element(gfx, render, element, pass);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element, submit_element);
	}

	void pass_alpha(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("alpha", PassType::Alpha);

		submit_pbr_pass(gfx, render, pass);

		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS
							  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA;

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthDescending);

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(pass);
			if(!element.m_program->m_blocks[MaterialBlock::Pbr] || !element.m_material->m_alpha.m_is_alpha)
				return false;

			blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);

			pbr_options(gfx, render, element.m_shader_version);

			return true;
		};

		auto submit_element = [](GfxSystem& gfx, Render& render, Pass& pass, const DrawElement& element)
		{
			submit_pbr_element(gfx, render, element, pass);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element, submit_element);
	}

	void pass_geometry(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		Pass pass = render.next_pass("geometry", PassType::Geometry);

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthAscending);
		
		uint64_t cull = render.m_vflip ? BGFX_STATE_CULL_CCW : BGFX_STATE_CULL_CW;

		pass.m_bgfx_state = cull | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z 
								 | BGFX_STATE_DEPTH_TEST_EQUAL | BGFX_STATE_MSAA;

		pass.m_fbo = &render.m_target->m_gbuffer;

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(render); UNUSED(pass);
			bool lit = element.m_program->m_blocks[MaterialBlock::Lit] && !element.m_material->m_alpha.m_is_alpha;
			bool opaque = element.m_program->m_passes[PassType::Opaque];
			if(!lit && !opaque) return false;

			if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, DEFERRED, true);
			return true;
		};

		auto submit_element = [](GfxSystem& gfx, Render& render, Pass& pass, const DrawElement& element)
		{
			submit_pbr_element(gfx, render, element, pass);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element, submit_element);
	}

	void pass_lights(GfxSystem& gfx, Render& render)
	{
		static Program& program = gfx.programs().fetch("pbr/lights");

		Pass pass = render.next_pass("lights", PassType::Lights);
		bgfx::Encoder& encoder = *pass.m_encoder;
		pass.m_encoder = &encoder;

		submit_pbr_pass(gfx, render, pass);

		DrawCluster cluster;
		cluster.m_lights = render.m_shot.m_lights;
		cluster.m_shader_version = { program };

		for(auto& block : gfx.m_renderer.m_gfx_blocks)
			if(block->m_draw_block)
			{
				as<DrawBlock>(*block).options(render, cluster.m_shader_version);
				as<DrawBlock>(*block).submit(render, pass);
			}

		RenderTarget& target = *render.m_target;
		GBuffer& gbuffer = target.m_gbuffer;

		gfx.m_filter->source0(gbuffer.m_position);
		gfx.m_filter->source1(gbuffer.m_normal);
		gfx.m_filter->source2(gbuffer.m_albedo);
		gfx.m_filter->source3(gbuffer.m_surface);

		gfx.m_filter->quad(pass, *render.m_fbo, cluster.m_shader_version, BGFX_STATE_BLEND_ALPHA);

#if DEBUG_GBUFFERS
		vec2 size = vec2(target.m_size) * 0.25f;
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_depth, vec4(vec2(0.f, size.y * 0.f), size), true);
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_normal, vec4(vec2(0.f, size.y * 1.f), size));
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_albedo, vec4(vec2(0.f, size.y * 2.f), size));
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_surface, vec4(vec2(0.f, size.y * 3.f), size));
#endif
	}
	
	void pass_pre_post_process(GfxSystem& gfx, Render& render)
	{
		RenderTarget& target = *render.m_target;
		gfx.m_copy->quad(render.composite_pass("post process begin"), target.m_post.swap(), target.m_diffuse);
	}

	void pass_post_process(GfxSystem& gfx, Render& render)
	{
		RenderTarget& target = *render.m_target;
		gfx.m_copy->quad(render.composite_pass("post process begin"), target.m_post.swap(), target.m_diffuse);

		// submit each post process effect

		static BlockDofBlur& dof_blur = *gfx.m_renderer.block<BlockDofBlur>();
		static BlockGlow& glow = *gfx.m_renderer.block<BlockGlow>();
		static BlockTonemap& tonemap = *gfx.m_renderer.block<BlockTonemap>();

		dof_blur.submit_pass(render);
		glow.submit_pass(render);
		tonemap.submit_pass(render);
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

	void BlockGeometry::options(Render& render, ProgramVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockGeometry::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
	}

	void BlockGeometry::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);
	}
}
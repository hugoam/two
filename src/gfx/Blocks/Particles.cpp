
#include <gfx/Generated/Types.h>
#include <gfx/Blocks/Particles.h>

#include <gfx/Particles.h>
#include <gfx/Camera.h>

namespace mud
{
	BlockParticles::BlockParticles(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockParticles>())
		, m_particle_system(gfx_system, 64)
	{}

	void BlockParticles::init_gfx_block()
	{
		m_particle_system.createSprite("particle.ktx", "particle.ktx");
		m_particle_system.createSprite("flames.png", "flames_b.png", { 2, 2 });
		m_particle_system.createSprite("billows.png", "billows_b.png", { 2, 2 });
		m_particle_system.createSprite("wave.png", "wave_b.png");
	}

	void BlockParticles::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockParticles::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockParticles::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockParticles::submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element)
	{
		UNUSED(render); UNUSED(render_pass); UNUSED(element);
	}

	PassParticles::PassParticles(GfxSystem& gfx_system, BlockParticles& block_particles)
		: RenderPass(gfx_system, "particles", {})
		, m_block_particles(block_particles)
	{
		UNUSED(gfx_system);
	}

	void PassParticles::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassParticles::submit_render_pass(Render& render)
	{
		Pass particle_pass = render.next_pass("particles");

		m_block_particles.m_particle_system.update(render.m_frame.m_delta_time); // * timeScale
		m_block_particles.m_particle_system.render(particle_pass.m_index, render.m_camera.m_transform, render.m_camera.m_node.m_position);
	}
}
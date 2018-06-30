//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <math/Curve.h>
#include <math/ImageAtlas.h>
#include <geom/Shape.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	struct Particle
	{
		vec3 start;
		vec3 dir;
		quat rot;

		float speed_seed;
		float angle_seed;
		float blend_seed;
		float colour_seed;
		float scale_seed;
		float sprite_seed;

		float life;
		float lifetime;
	};

	struct ParticleSort
	{
		float    dist;
		uint32_t idx;
	};

	export_ enum class refl_ EmitterFlow : unsigned int
	{
		Outward,
		Absolute
	};

	export_ struct refl_ MUD_GFX_EXPORT ParticleGenerator
	{
		ParticleGenerator();
		ParticleGenerator(cstring name);

		attr_ string m_name;

		// emitter
		attr_ mut_ float m_duration = 1.f;
		attr_ mut_ float m_start_time = 0.f;
		attr_ mut_ bool m_loop = false;
		attr_ mut_ ShapeVar m_shape = {};
		attr_ mut_ EmitterFlow m_flow = EmitterFlow::Outward;
		attr_ mut_ bool m_billboard = true;
		attr_ mut_ vec3 m_direction = { 0.f, 0.f, -1.f };
		attr_ mut_ quat m_rotation = ZeroQuat;
		attr_ mut_ BlendMode m_blend_mode = BlendMode::Normal;

		//attr_ mut_ ValueTrack<vec3> m_position = { Zero3 };
		//attr_ mut_ ValueTrack<quat> m_rotation = { ZeroQuat };
		attr_ mut_ ValueTrack<float> m_volume = { 1.f };

		attr_ mut_ ValueTrack<uint32_t> m_rate = { 0 };

		attr_ mut_ ValueTrack<float> m_lifetime = { 1.f };
		attr_ mut_ ValueTrack<float> m_gravity = { 0.f };

		// particles
		attr_ mut_ ValueTrack<float> m_speed = { 1.f };
		attr_ mut_ ValueTrack<float> m_angle = { 0.f };
		attr_ mut_ ValueTrack<float> m_blend = { std::vector<float>({ 0.8f, 0.0f }) };
		attr_ mut_ ValueTrack<Colour> m_colour = { Colour::White };
		attr_ mut_ ValueTrack<float> m_scale = { 0.1f };

		attr_ mut_ ValueTrack<float> m_sprite_frame = { 0.f };

		attr_ mut_ string m_sprite_name;

		const Sprite* m_sprite = nullptr;
	};

	struct ParticleVertex
	{
		vec3 m_pos;
		uint32_t m_abgr;
		vec2 m_uv;
		float m_blend;
		float m_radius;
		//float m_angle;

		static void init();

		static bgfx::VertexDecl ms_decl;
	};

	export_ struct refl_ MUD_GFX_EXPORT Particles : public ParticleGenerator
	{
	public:
		Particles(Node3* node = nullptr, ShapeVar shape = {}, uint32_t max_particles = 1024);

		attr_ Node3* m_node = nullptr;

		bool ended() { return m_time > m_duration; }

		void upload();
		void update(float dt);
		void spawn(float dt);
		uint32_t render(const SpriteAtlas& atlas, const mat4& view, const vec3& eye, uint32_t first, uint32_t max, ParticleSort* outSort, ParticleVertex* outVertices);

		inline void write_vertex(ParticleVertex*& dest, ParticleVertex vertex);

		float m_time = 0.0f;
		float m_dt = 0.0f;
		bool m_ended = false;

		Aabb m_aabb;

		std::vector<Particle> m_particles;
		uint32_t m_max;
	};

#ifndef MUD_MODULES
	template <class T>
	class TPool;
#endif

	export_ class MUD_GFX_EXPORT ParticleSystem
	{
	public:
		ParticleSystem(GfxSystem& gfx_system, TPool<Particles>& emitters);
		~ParticleSystem();

		GfxSystem& m_gfx_system;
		BlockParticles& m_block;

		void shutdown();

		void update(float timestep);
		void render(uint8_t pass, const mat4& view, const vec3& eye);
		
		TPool<Particles>& m_emitters;

		bgfx::ProgramHandle m_program;

		uint32_t m_num = 0;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockParticles : public GfxBlock
	{
	public:
		BlockParticles(GfxSystem& gfx_system);
		~BlockParticles();

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		SpriteAtlas m_sprites;
		bgfx::TextureHandle m_texture;

		bgfx::UniformHandle s_color;

		Sprite* create_sprite(cstring name, cstring path, uvec2 frames = uvec2(0U));
		Sprite* create_sprite(cstring name, uvec2 size, uvec2 frames, const void* data);
		void remove_sprite(Sprite& image);
	};

	export_ class MUD_GFX_EXPORT PassParticles : public RenderPass
	{
	public:
		PassParticles(GfxSystem& gfx_system);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;
	};
}

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Curve.h>
#include <geom/Shape.h>
#include <ui/ImageAtlas.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bx/easing.h>
#include <bgfx/bgfx.h>
#endif

#include <vector>

namespace mud
{
	struct Particle
	{
		vec3 start;
		vec3 dir;

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

	enum class _refl_ EmitterDirection : unsigned int
	{
		Outward,
		Absolute
	};

	struct _refl_ MUD_GFX_EXPORT ParticleGenerator
	{
		ParticleGenerator();
		ParticleGenerator(cstring name);

		_attr_ strung m_name;

		// emitter
		_attr_ _mut_ float m_duration = 1.f;
		_attr_ _mut_ float m_start_time = 0.f;
		_attr_ _mut_ bool m_loop = false;
		_attr_ _mut_ ShapeVar m_shape = {};
		_attr_ _mut_ EmitterDirection m_direction = EmitterDirection::Outward;
		_attr_ _mut_ vec3 m_absolute_direction = { 0.f, 0.f, -1.f };//-Z3;
		_attr_ _mut_ BlendMode m_blend_mode = BlendMode::Normal;

		_attr_ _mut_ ValueTrack<vec3> m_position = { Zero3 };
		_attr_ _mut_ ValueTrack<quat> m_rotation = { ZeroQuat };
		_attr_ _mut_ ValueTrack<float> m_volume = { 1.f };

		_attr_ _mut_ ValueTrack<uint32_t> m_rate = { 0 };

		_attr_ _mut_ ValueTrack<float> m_lifetime = { 1.f };
		_attr_ _mut_ ValueTrack<float> m_gravity = { 0.f };

		// particles
		_attr_ _mut_ ValueTrack<float> m_speed = { 1.f };
		_attr_ _mut_ ValueTrack<float> m_angle = { 0.f };
		_attr_ _mut_ ValueTrack<float> m_blend = { std::vector<float>({ 0.8f, 0.0f }) };
		_attr_ _mut_ ValueTrack<Colour> m_colour = { Colour::White };
		_attr_ _mut_ ValueTrack<float> m_scale = { 0.1f };

		_attr_ _mut_ ValueTrack<float> m_sprite_frame = { 0.f };

		_attr_ _mut_ strung m_sprite_name;

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

	struct _refl_ MUD_GFX_EXPORT ParticleEmitter : public ParticleGenerator
	{
		ParticleEmitter(ShapeVar shape = {}, uint32_t max_particles = 1024)
			: m_max(max_particles)
		{
			m_shape = shape;
			m_particles.reserve(m_max);
		}

		void update(float _dt);
		void spawn(float _dt);
		uint32_t render(const SpriteAtlas& atlas, const mat4& view, const vec3& eye, uint32_t first, uint32_t max, ParticleSort* outSort, ParticleVertex* outVertices);

		inline void writeVertex(ParticleVertex*& dest, ParticleVertex vertex);

		float m_time = 0.0f;
		float m_dt = 0.0f;
		Node3* m_node = nullptr;

		Aabb m_aabb;

		std::vector<Particle> m_particles;
		uint32_t m_max;
	};

	template <class T>
	class TPool;

	struct MUD_GFX_EXPORT ParticleSystem
	{
		ParticleSystem(GfxSystem& gfx_system, uint16_t maxEmitters = 64);
		~ParticleSystem();

		GfxSystem& m_gfx_system;

		void shutdown();

		Sprite* createSprite(cstring name, cstring path, uvec2 frames = uvec2(0U));
		Sprite* createSprite(cstring name, uvec2 size, uvec2 frames, const void* data);
		void removeSprite(Sprite& image);

		void update(float timestep);
		void render(uint8_t pass, const mat4& view, const vec3& eye);

		unique_ptr<TPool<ParticleEmitter>> m_emitters;

		SpriteAtlas m_sprites;

		bgfx::UniformHandle s_texColor;
		bgfx::TextureHandle m_texture;
		bgfx::ProgramHandle m_program;

		uint32_t m_num = 0;
	};

	class _refl_ MUD_GFX_EXPORT Particles
	{
	public:
		Particles(ParticleSystem& particle_system, Node3& node);
		~Particles();

		_attr_ Node3& m_node;

		ParticleSystem& m_particle_system;
		ParticleEmitter& m_emitter;

		void upload();
	};

	class _refl_ MUD_GFX_EXPORT BlockParticles : public DrawBlock
	{
	public:
		BlockParticles(GfxSystem& gfx_system);

		ParticleSystem m_particle_system;

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		virtual void begin_gfx_pass(Render& render) final;
		virtual void submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element) final;
	};

	class MUD_GFX_EXPORT PassParticles : public RenderPass
	{
	public:
		PassParticles(GfxSystem& gfx_system, BlockParticles& pass_particles);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;

		BlockParticles& m_block_particles;
	};
}

//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <math/Vec.h>
#include <math/Curve.h>
#include <geom/Shape.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Material.h>
#include <gfx/Renderer.h>

#include <bgfx/bgfx.h>

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

	// alternate names: spout, flux, jet
	export_ struct refl_ MUD_GFX_EXPORT Flow
	{
		Flow();
		Flow(const string& name);

		attr_ string m_name;

		// emitter
		attr_ float m_duration = 1.f;
		attr_ float m_start_time = 0.f;
		attr_ bool m_loop = false;
		attr_ ShapeVar m_shape = {};
		attr_ EmitterFlow m_flow = EmitterFlow::Outward;
		attr_ bool m_billboard = true;
		attr_ vec3 m_direction = { 0.f, 0.f, -1.f };
		attr_ quat m_rotation = ZeroQuat;
		attr_ BlendMode m_blend_mode = BlendMode::Normal;

		//attr_ ValueTrack<vec3> m_position = { vec3(0.f) };
		//attr_ ValueTrack<quat> m_rotation = { ZeroQuat };
		attr_ ValueTrack<float> m_volume = { 1.f };

		attr_ ValueTrack<uint32_t> m_rate = { 0 };

		attr_ ValueTrack<float> m_lifetime = { 1.f };
		attr_ ValueTrack<float> m_gravity = { 0.f };

		// particles
		attr_ ValueTrack<float> m_speed = { 1.f };
		attr_ ValueTrack<float> m_angle = { 0.f };
		attr_ ValueTrack<float> m_blend = { vector<float>({ 0.8f, 0.0f }) };
		attr_ ValueTrack<Colour> m_colour = { Colour::White };
		attr_ ValueTrack<float> m_scale = { 0.1f };

		attr_ ValueTrack<float> m_sprite_frame = { 0.f };

		attr_ string m_sprite_name;

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
	};

	// alternate names: jet, flow, surge, spray
	export_ struct refl_ MUD_GFX_EXPORT Flare : public Flow
	{
	public:
		Flare(Node3* node = nullptr, ShapeVar shape = {}, uint32_t max_particles = 1024);

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

		vector<Particle> m_particles;
		uint32_t m_max;
	};

#ifndef MUD_MODULES
	template <class T>
	class TPool;
#endif

	export_ class MUD_GFX_EXPORT ParticleSystem
	{
	public:
		ParticleSystem(GfxSystem& gfx, TPool<Flare>& emitters);
		~ParticleSystem();

		GfxSystem& m_gfx;
		BlockParticles& m_block;

		void shutdown();

		void update(float timestep);
		void render(bgfx::Encoder& encoder, uint8_t pass, const mat4& view, const vec3& eye);
		
		TPool<Flare>& m_emitters;

		bgfx::ProgramHandle m_program;

		uint32_t m_num = 0;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockParticles : public GfxBlock
	{
	public:
		BlockParticles(GfxSystem& gfx);
		~BlockParticles();

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		unique<SpriteAtlas> m_sprites;
		bgfx::TextureHandle m_texture;

		bgfx::UniformHandle s_color;

		Sprite* create_sprite(cstring name, cstring path, uvec2 frames = uvec2(0U));
		Sprite* create_sprite(cstring name, uvec2 size, uvec2 frames, const void* data);
		void remove_sprite(Sprite& image);
	};

	export_ MUD_GFX_EXPORT void pass_particles(GfxSystem& gfx, Render& render);
}

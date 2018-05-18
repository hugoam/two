//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Interp.h>
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

	enum class _refl_ TrackMode : unsigned int
	{
		Constant,
		ConstantRandom,
		Curve,
		CurveRandom
	};

	template <class T>
	struct _refl_ _struct_ ValueCurve
	{
		_constr_ ValueCurve() {}
		_constr_ ValueCurve(std::vector<T> keys) : m_keys(keys) {}
		ValueCurve(T value) : m_keys(1, value) {}

		T sample_constant()
		{
			return m_keys[0];
		}

		T sample_curve(float t)
		{
			//bx::EaseFn ease = bx::getEaseFunc(m_ease);
			//const float tt = bx::clamp(ease(t), 0.f, 1.f);

			uint32_t key = uint32_t(t * (m_keys.size() - 1));
			float interval = 1.f / float(m_keys.size() - 1);
			float ttmod = bx::mod(t, interval) / interval;

			return mud::lerp(m_keys[key], m_keys[key + 1], ttmod);
		}

		_attr_ _mut_ std::vector<T> m_keys;
	};

	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueCurve<vec3>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueCurve<quat>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueCurve<float>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueCurve<uint32_t>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueCurve<Colour>;

	template <class T>
	struct _refl_ _struct_ ValueTrack
	{
		_constr_ ValueTrack() {}
		_constr_ ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve) : m_mode(mode), m_curve(curve), m_min_curve(min_curve), m_max_curve(max_curve) {}
		ValueTrack(T value) : m_mode(TrackMode::Constant), m_curve(value) {}
		ValueTrack(T min, T max) : m_mode(TrackMode::ConstantRandom), m_min_curve(min), m_max_curve(max) {}
		ValueTrack(std::vector<T> values) : m_mode(TrackMode::Curve), m_curve(values) {}
		ValueTrack(std::vector<T> min_values, std::vector<T> max_values) : m_mode(TrackMode::CurveRandom), m_min_curve(min_values), m_max_curve(max_values) {}

		void set_mode(TrackMode mode)
		{
			if(mode == TrackMode::Constant)
				*this = ValueTrack<T>(T());
			else if(mode == TrackMode::ConstantRandom)
				*this = ValueTrack<T>(T(), T());
			else if(mode == TrackMode::Curve)
				*this = ValueTrack<T>(std::vector<T>(2, T()));
			else if(mode == TrackMode::CurveRandom)
				*this = ValueTrack<T>(std::vector<T>(2, T()), std::vector<T>(2, T()));
		}

		T sample(float t, float seed = 0.f)
		{
			if(m_mode == TrackMode::Constant)
				return m_curve.sample_constant();
			else if(m_mode == TrackMode::ConstantRandom)
				return mud::lerp(m_min_curve.sample_constant(), m_max_curve.sample_constant(), seed);
			else if(m_mode == TrackMode::Curve)
				return m_curve.sample_curve(t);
			else //if(m_mode == TrackMode::CurveRandom)
				return mud::lerp(m_min_curve.sample_curve(t), m_max_curve.sample_curve(t), seed);
		}

		_attr_ _mut_ TrackMode m_mode;
		_attr_ _mut_ ValueCurve<T> m_curve;
		_attr_ _mut_ ValueCurve<T> m_min_curve;
		_attr_ _mut_ ValueCurve<T> m_max_curve;

#ifndef MUD_GENERATOR_SKIP_INCLUDES
		bx::Easing::Enum m_ease = bx::Easing::Linear;
#endif
	};

	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueTrack<vec3>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueTrack<quat>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueTrack<float>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueTrack<uint32_t>;
	template struct _refl_ _struct_ MUD_GFX_EXPORT ValueTrack<Colour>;

	enum class _refl_ EmitterDirection : unsigned int
	{
		Outward,
		Absolute
	};

	struct _refl_ MUD_GFX_EXPORT ParticleGenerator
	{
		ParticleGenerator();

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
}

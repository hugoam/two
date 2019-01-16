//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/math.h>
#include <bx/allocator.h>
#include <bimg/bimg.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/string.h>
#include <pool/Pool.h>
#include <math/Math.h>
#include <math/Random.h>
#include <geom/ShapeDistrib.h>
#include <gfx/Types.h>
#include <gfx/Particles.h>
#include <gfx/GfxSystem.h>
#include <gfx/Renderer.h>
#include <gfx/Texture.h>
#include <gfx/Material.h>
#include <gfx/Program.h>
#include <gfx/Asset.h>
#include <gfx/Camera.h>
#include <gfx/Scene.h>
#include <gfx/Pipeline.h>
#include <gfx/Node3.h>
#endif

#define SPRITE_TEXTURE_SIZE 2048U

namespace mud
{
	void ParticleVertex::init()
	{
		bgfx::VertexDecl decl;

		decl.begin();
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
			decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
			decl.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float);
		decl.end();

		ms_decl = decl;

		//ms_decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour | VertexAttribute::TexCoord0);
	}

	bgfx::VertexDecl ParticleVertex::ms_decl;

	ParticleFlow::ParticleFlow()
	{}

	ParticleFlow::ParticleFlow(cstring name)
		: m_name(name)
	{}

	Particles::Particles(Node3* node, ShapeVar shape, uint32_t max_particles)
		: m_node(node)
		, m_max(max_particles)
	{
		m_shape = shape;
		m_particles.reserve(m_max);
	}

	void Particles::upload()
	{}

	void Particles::update(float delta)
	{
		m_time += delta;

		for(Particle& particle : m_particles)
			particle.life += delta / particle.lifetime;

		vector_remove_if(m_particles, [&](Particle& particle) { return particle.life > m_duration; });

		m_ended = m_time > m_duration && !m_loop;
		if(!m_ended && m_rate.sample(m_time) > 0)
			spawn(delta);
	}


	void Particles::spawn(float dt)
	{
		mat4 transform = m_node ? m_node->m_transform : bxidentity();

		//quat rotation = m_rotation.sample(m_time, random_scalar(0.f, 1.f));
		//vec3 position = m_position.sample(m_time, random_scalar(0.f, 1.f));
		//transform = bxSRT(Unit3, rotation, position) * transform;

		m_dt += dt;

		const float particle_period = 1.0f / m_rate.sample(m_time);
		const uint32_t num_particles = uint32_t(m_dt / particle_period);
		m_dt -= num_particles * particle_period;

		size_t count = min(num_particles, m_max - uint32_t(m_particles.size()));
		vector<vec3> points = distribute_shape(*m_shape, count);

		float time = 0.0f;
		for(size_t ii = 0; ii < count; ++ii)
		{
			Particle particle;

			float volume = m_volume.sample(m_time, random_scalar(0.f, 1.f));

			vec3 pos = points[ii] * volume;
			vec3 dir = m_flow == EmitterFlow::Outward ? normalize(points[ii]) : m_direction;

			particle.life = time;
			particle.lifetime = m_lifetime.sample(m_time, random_scalar(0.f, 1.f));

			particle.start = vec3(transform * vec4{ pos, 1.f });
			particle.dir = vec3(transform * vec4{ dir, 0.f });
			particle.rot = ZeroQuat; // m_node->m_rotation; // @todo

			particle.speed_seed = random_scalar(0.f, 1.f);
			particle.angle_seed = random_scalar(0.f, 1.f);
			particle.blend_seed = random_scalar(0.f, 1.f);
			particle.colour_seed = random_scalar(0.f, 1.f);
			particle.scale_seed = random_scalar(0.f, 1.f);
			particle.sprite_seed = random_scalar(0.f, 1.f);

			time += particle_period;

			m_particles.push_back(particle);
		}
	}

	uint32_t Particles::render(const SpriteAtlas& atlas, const mat4& view, const vec3& eye, uint32_t first, uint32_t max, ParticleSort* outSort, ParticleVertex* outVertices)
	{
		m_aabb =
		{
			{ bx::kInfinity,  bx::kInfinity,  bx::kInfinity },
			{ -bx::kInfinity, -bx::kInfinity, -bx::kInfinity },
		};

		if(m_sprite == nullptr)
			return 0;
		
		uint32_t index = first;
		for(Particle& particle : m_particles)
		{
			if(index + 1 >= max)
				break;

			vec3 gravity = { 0.0f, -9.81f * m_gravity.sample(particle.life) * bx::square(particle.life), 0.0f };
			UNUSED(gravity);

			float advance = particle.life * particle.lifetime * m_speed.sample(particle.life, particle.speed_seed);
			vec3 pos = particle.start + particle.dir * advance; //+ gravity;

			ParticleSort& sort = outSort[index];
			vec3 tmp = eye - pos;
			sort.dist = bx::sqrt(dot(tmp, tmp));
			sort.idx = index;

			float blend = m_blend.sample(particle.life, particle.blend_seed);
			float scale = m_scale.sample(particle.life, particle.scale_seed);

			Colour colour = m_colour.sample(particle.life, particle.colour_seed);
			uint32_t abgr = to_abgr(colour);

			vec3 udir;
			vec3 vdir;

			if(m_billboard)
			{
				udir = scale * vec3{ view[0][0], view[1][0], view[2][0] };
				vdir = scale * vec3{ view[0][1], view[1][1], view[2][1] };
			}
			else
			{
				udir = scale * rotate(particle.rot, X3);
				vdir = scale * rotate(particle.rot, Y3);
			}

			float frame = m_sprite_frame.sample(particle.life, particle.sprite_seed);
			const vec4 uv = atlas.sprite_uv(*m_sprite, frame);

			ParticleVertex* vertex = &outVertices[index * 4];

			write_vertex(vertex, { pos - udir - vdir, abgr, { uv[0], uv[1] }, blend, scale });
			write_vertex(vertex, { pos + udir - vdir, abgr, { uv[2], uv[1] }, blend, scale });
			write_vertex(vertex, { pos + udir + vdir, abgr, { uv[2], uv[3] }, blend, scale });
			write_vertex(vertex, { pos - udir + vdir, abgr, { uv[0], uv[3] }, blend, scale });

			++index;
		}

		return uint32_t(m_particles.size());
	}

	inline void Particles::write_vertex(ParticleVertex*& dest, ParticleVertex vertex)
	{
		m_aabb.merge(vertex.m_pos);
		*dest = vertex;
		++dest;
	}

	static int32_t particleSortFn(const void* _lhs, const void* _rhs)
	{
		const ParticleSort& lhs = *(const ParticleSort*)_lhs;
		const ParticleSort& rhs = *(const ParticleSort*)_rhs;
		return lhs.dist > rhs.dist ? -1 : 1;
	}

	ParticleSystem::ParticleSystem(GfxSystem& gfx_system, TPool<Particles>& emitters)
		: m_gfx_system(gfx_system)
		, m_block(*gfx_system.m_pipeline->block<BlockParticles>())
		, m_emitters(emitters)
		, m_program(gfx_system.programs().fetch("particle").default_version())
	{}

	ParticleSystem::~ParticleSystem()
	{}

	void ParticleSystem::shutdown()
	{
		bgfx::destroy(m_program);
	}

	void ParticleSystem::update(float _dt)
	{
		uint32_t num_particles = 0;
		for(Particles* emitter : m_emitters.m_vec_pool->m_objects)
		{
			emitter->update(_dt);
			num_particles += uint32_t(emitter->m_particles.size());
		}
		m_num = num_particles;
	}

	void ParticleSystem::render(bgfx::Encoder& encoder, uint8_t pass, const mat4& view, const vec3& eye)
	{
		if(0 == m_num)
			return;

		const uint32_t numVertices = min(bgfx::getAvailTransientVertexBuffer(m_num * 4, ParticleVertex::ms_decl), uint32_t(UINT16_MAX));
		const uint32_t numIndices = bgfx::getAvailTransientIndexBuffer(m_num * 6);
		const uint32_t max = bx::uint32_min(numVertices / 4, numIndices / 6);
		BX_WARN(m_num == max, "Truncating transient buffer for particles to maximum available (requested %d, available %d).", m_num, max);

		if(0 < max)
		{
			bgfx::TransientVertexBuffer vertex_buffer;
			bgfx::TransientIndexBuffer index_buffer;

			bgfx::allocTransientBuffers(&vertex_buffer, ParticleVertex::ms_decl, max * 4, &index_buffer, max * 6);

			vector<ParticleSort> particleSort{ max };

			uint32_t pos = 0;
			ParticleVertex* vertices = (ParticleVertex*)vertex_buffer.data;

			for(Particles* emitter : m_emitters.m_vec_pool->m_objects)
				pos += emitter->render(m_block.m_sprites, view, eye, pos, max, particleSort.data(), vertices);

			qsort(particleSort.data(), max, sizeof(ParticleSort), particleSortFn);

			uint16_t* indices = (uint16_t*)index_buffer.data;
			for(uint32_t ii = 0; ii < max; ++ii)
			{
				auto tri = [](uint16_t*& dest, uint16_t a, uint16_t b, uint16_t c) { *dest++ = a; *dest++ = b; *dest++ = c; };
				const uint16_t index = uint16_t(particleSort[ii].idx) * 4;
				uint16_t* dest = &indices[ii * 6];
				tri(dest, index + 0, index + 1, index + 2);
				tri(dest, index + 2, index + 3, index + 0);
			}

			uint64_t bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS; // | BGFX_STATE_CULL_CW;
			blend_state(m_emitters.m_vec_pool->m_objects[0]->m_blend_mode, bgfx_state);

			encoder.setState(bgfx_state);
			encoder.setVertexBuffer(0, &vertex_buffer);
			encoder.setIndexBuffer(&index_buffer);
			encoder.setTexture(uint8_t(TextureSampler::Color), m_block.s_color, m_block.m_texture);
			encoder.submit(pass, m_program);
		}
	}

	BlockParticles::BlockParticles(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, type<BlockParticles>())
		, m_sprites(uvec2(SPRITE_TEXTURE_SIZE))
	{}

	BlockParticles::~BlockParticles()
	{
		bgfx::destroy(m_texture);
		bgfx::destroy(s_color);
	}

	void BlockParticles::init_block()
	{
		ParticleVertex::init();

		s_color = bgfx::createUniform("s_texColor", bgfx::UniformType::Int1);
		m_texture = bgfx::createTexture2D(SPRITE_TEXTURE_SIZE, SPRITE_TEXTURE_SIZE, false, 1, bgfx::TextureFormat::BGRA8);

		this->create_sprite("particle.ktx", "particle.ktx");
		//this->create_sprite("flames.png", "flames_b.png", { 2, 2 });
		//this->create_sprite("billows.png", "billows_b.png", { 2, 2 });
		//this->create_sprite("wave.png", "wave_b.png");
		//this->create_sprite("geometric.png", "geometric_b.png", { 2, 2 });
	}

	void BlockParticles::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockParticles::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	Sprite* BlockParticles::create_sprite(cstring name, cstring pathname, uvec2 frames)
	{
		string filename = "textures/particles/" + string(pathname);
		LocatedFile location = m_gfx_system.locate_file(filename.c_str());
		string path = string(location.m_location) + filename;

		bimg::ImageContainer* image = load_bgfx_image(m_gfx_system.m_allocator, m_gfx_system.file_reader(), path.c_str(), bgfx::TextureFormat::BGRA8);
		Sprite* sprite = this->create_sprite(name, uvec2(image->m_width, image->m_height), frames, image->m_data);
		bimg::imageFree(image);
		return sprite;
	}

	Sprite* BlockParticles::create_sprite(cstring name, uvec2 size, uvec2 frames, const void* data)
	{
		Sprite* sprite = m_sprites.add_sprite(name, size, frames);
		if(sprite)
		{
			bgfx::updateTexture2D(m_texture, 0, 0, uint16_t(sprite->d_coord.x), uint16_t(sprite->d_coord.y),
								  uint16_t(sprite->d_size.x), uint16_t(sprite->d_size.y), bgfx::copy(data, size.x*size.y * 4));
		}

		return sprite;
	}

	void BlockParticles::remove_sprite(Sprite& sprite)
	{
		UNUSED(sprite);
	}

	PassParticles::PassParticles(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "particles", {})
	{
		UNUSED(gfx_system);
	}

	void PassParticles::submit_render_pass(Render& render)
	{
		Pass particle_pass = render.next_pass("particles");
		bgfx::Encoder& encoder = *particle_pass.m_encoder;

		render.m_scene.m_particle_system->update(render.m_frame.m_delta_time); // * timeScale
		render.m_scene.m_particle_system->render(encoder, particle_pass.m_index, render.m_camera.m_transform, render.m_camera.m_eye);
	}
}

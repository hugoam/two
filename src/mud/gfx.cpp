#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/pool.h>
#include <mud/ui.h>
#include <mud/jobs.h>
#include <mud/tree.h>
#include <mud/ecs.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.gfx;
#else
#include <bx/math.h>

#endif

#include <cstdio>

namespace mud
{
	Animated::Animated(Node3& node)
		: m_node(node)
	{}

	Animated::~Animated()
	{}

	void Animated::add_item(Item& item)
	{
		m_rig = *item.m_model->m_rig;
		item.m_rig = &m_rig;
	}

	void Animated::start(cstring name, bool loop, float blend, float speed, bool transient)
	{
		for(Animation* animation : m_rig.m_skeleton.m_animations)
			if(animation->m_name == name)
			{
				this->play(*animation, loop, blend, speed, transient);
				return;
			}
	}

	void Animated::play(const Animation& animation, bool loop, float blend, float speed, bool transient)
	{
		for(AnimationPlay& playing : m_playing)
		{
			playing.m_transient = true;
			if(blend == 0.f)
				blend = m_default_blend_time;
			if(blend > 0.f)
				playing.m_fadeout = blend;
		}

		m_playing.push_back({ animation, loop, speed, transient, &m_rig.m_skeleton });
		m_active = true;
	}

	void Animated::stop()
	{
		m_playing.clear();
	}

	void Animated::pause()
	{
		m_active = false;
	}

	void Animated::next_animation()
	{
		//this->play(*pop(m_queue));
	}

	void Animated::advance(float delta)
	{
		if(m_playing.size() > 2)
			printf("WARNING: Animated playing more than 2 animations at the same time\n");

		for(AnimationPlay& play : m_playing)
			play.step(delta, m_speed_scale);

		vector_remove_if(m_playing, [](AnimationPlay& play) { return play.m_transient && play.m_ended; });

		for(Bone& bone : m_rig.m_skeleton.m_bones)
			bone.m_pose_local = bxTRS(bone.m_scale, bone.m_rotation, bone.m_position);

		m_rig.update_rig();
	}

	void Animated::seek(float time)
	{
		for(AnimationPlay& play : m_playing)
		{
			play.m_cursor = time;
			play.update(time, 0.f, 1.f);
		}
	}

	AnimationPlay::AnimationPlay(const Animation& animation, bool loop, float speed, bool transient, Skeleton* skeleton)
		: m_animation(&animation)
		, m_loop(loop)
		, m_speed(speed)
		, m_transient(transient)
	{
		m_tracks.reserve(animation.tracks.size());

		for(const AnimationTrack& track : animation.tracks)
		{
			Bone* target = nullptr;
			if(skeleton && skeleton->m_bones.size() > track.m_node)
				target = &skeleton->m_bones[track.m_node];
			if(!target)
			{
				//printf("WARNING: No bone found for animation %s track %s with target %s\n", animation.m_name.c_str(), "", track.m_node_name.c_str());
				continue;
			}

			AnimatedTrack playtrack = { &track, target, {}, track.m_keys[0].m_value };

			m_tracks.push_back(playtrack);
		}
	}

	void AnimationPlay::step(float timestep, float speed)
	{
		float delta = timestep * m_speed * speed;
		float next_pos = m_cursor + delta;
		float blend = 1.f;

		bool looped = false;
		if(m_loop && next_pos >= m_animation->m_length)
		{
			next_pos = fmod(next_pos, m_animation->m_length);
			looped = true;
		}
		else if(m_loop && next_pos < 0.f)
		{
			next_pos = m_animation->m_length - fmod(-next_pos, m_animation->m_length);
			looped = true;
		}
		else if(!m_loop && next_pos >= m_animation->m_length)
		{
			next_pos = m_animation->m_length;
			m_ended = true;
		}

		delta = next_pos - m_cursor;
		m_cursor = next_pos;

		if(m_fadeout)
		{
			blend = m_fadeout_left / m_fadeout;
			m_fadeout_left -= delta;

			if(m_fadeout_left <= 0.f)
				m_ended = true;
		}

		for(AnimatedTrack& track : m_tracks)
		{
			AnimationCursor& c = track.m_cursor;
			c.m_time = m_cursor;

			if(m_ended)
				continue;

			if(looped)
			{
				c.m_prev = m_speed > 0.f ? 0 : track.m_track->m_keys.size() - 2;
				c.m_next = m_speed > 0.f ? 1 : track.m_track->m_keys.size() - 1;
			}

			while(m_speed > 0.f && c.m_time >= track.m_track->m_keys[c.m_next].m_time)
			{
				c.m_next++;
				c.m_prev++;
			}
			while(m_speed < 0.f && c.m_time <= track.m_track->m_keys[c.m_prev].m_time)
			{
				c.m_next--;
				c.m_prev--;
			}
		}

		this->update(m_cursor, delta, blend);
	}

	void AnimationPlay::update(float time, float delta, float interp)
	{
		UNUSED(time); UNUSED(interp);
		for(AnimatedTrack& track : m_tracks)
		{
			auto apply = [](Bone& bone, AnimationTarget target, const Value& value)
			{
				if(target == AnimationTarget::Position)
					bone.m_position = *(vec3*)value.m_value;
				else if(target == AnimationTarget::Rotation)
					bone.m_rotation = *(quat*)value.m_value;
				if(target == AnimationTarget::Scale)
					bone.m_scale = *(vec3*)value.m_value;
			};

			if(track.m_track->m_interpolation > Interpolation::Nearest)
			{
				track.m_value = track.m_track->sample(track.m_cursor);

				// @todo : add blending of multiple animations
				/*
				if(track.m_value.none())
					track.m_value = value;
				else
					track.m_value = interpolate(track.m_value, value, interp);
				*/

				//printf("Animation value for track %s = %s\n", track.m_track->m_node_name.c_str(), to_string(track.m_value).c_str());
				apply(*track.m_target, track.m_track->m_target, track.m_value);
			}
			else
			{
				track.m_value = track.m_track->value(track.m_cursor, delta > 0.f);
				apply(*track.m_target, track.m_track->m_target, track.m_value);
			}
		}
	}
}



#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <algorithm>

namespace mud
{
	static Type* s_target_types[3] = { &type<vec3>(), &type<quat>(), &type<vec3>() };

	Animation::Animation(cstring name)
		: m_name(name)
	{}
	
	AnimationTrack::AnimationTrack(Animation& animation, size_t node, cstring node_name, AnimationTarget target)
		: m_animation(&animation), m_node(node), m_node_name(node_name), m_target(target), m_value_type(s_target_types[size_t(target)])
	{}

	void AnimationTrack::insert_key(float time, const Value& value, float transition)
	{
		size_t position = key_before(time);
		m_keys.insert(m_keys.begin() + position + 1, Key{ time, value, transition });
	}

	size_t AnimationTrack::key_after(float time) const
	{
		assert(m_keys.size() > 0);
		auto predicate = [](float lhs, const Key& rhs) { return lhs < rhs.m_time; };
		auto result = std::upper_bound(m_keys.begin(), m_keys.end(), time, predicate);
		return result - m_keys.begin();
	}

	size_t AnimationTrack::key_before(float time) const
	{
		return key_after(time) - 1;
	}

	Value AnimationTrack::sample(AnimationCursor& cursor) const
	{
		assert(m_keys.size() > 0);

		if(cursor.m_time == m_keys.back().m_time)
		{
			return m_keys.back().m_value;
		}
		if(m_keys.size() == 1)
		{
			return m_keys[0].m_value;
		}

		float c = abs(cursor.m_time - m_keys[cursor.m_prev].m_time) / abs(m_keys[cursor.m_next].m_time - m_keys[cursor.m_prev].m_time);
		//printf("sample %i < %i, %f\n", int(cursor.m_prev), int(cursor.m_next), c);

		auto at = [&](size_t i) { return Ref((void*)m_keys[i].m_value.m_value, *m_value_type); };

		if(m_interpolation == Interpolation::Nearest)
		{
			return m_keys[cursor.m_prev].m_value;
		}
		else if(m_interpolation == Interpolation::Linear)
		{
			Value result;
			interpolate(Ref((void*)result.m_value, *m_value_type), at(cursor.m_prev), at(cursor.m_next), c);
			return result;
		}
		else if(m_interpolation == Interpolation::Cubic || true)
		{
			Value result;
			size_t pre = max<size_t>(0, cursor.m_prev - 1);
			size_t post = max<size_t>(cursor.m_next + 1, m_keys.size());
			interpolate_cubic(Ref((void*)result.m_value, *m_value_type), at(pre), at(cursor.m_prev), at(cursor.m_next), at(post), c);
			return result;
		}
	}

	Value AnimationTrack::value(AnimationCursor& cursor, bool forward) const
	{
		size_t key = forward ? cursor.m_next : cursor.m_prev;
		return m_keys[key].m_value;
	}
}



#include <bx/math.h>
#include <cassert>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	static size_t data_type_to_size(GpuBuffer::Element element) noexcept
	{
		using ET = GpuBuffer::ElementType;
		switch (element.type)
		{
			case ET::UINT8:  return element.size * sizeof(uint8_t);
			case ET::INT8:   return element.size * sizeof(int8_t);
			case ET::UINT16: return element.size * sizeof(uint16_t);
			case ET::INT16:  return element.size * sizeof(int16_t);
			case ET::UINT32: return element.size * sizeof(uint32_t);
			case ET::INT32:  return element.size * sizeof(int32_t);
			//case ET::HALF:   return element.size * sizeof(math::half);
			case ET::FLOAT:  return element.size * sizeof(float);
			default: return 0;
		}
	}

	static bgfx::TextureFormat::Enum data_type_to_texture_format(GpuBuffer::Element element) noexcept
	{
		using TF = bgfx::TextureFormat;
		static const TF::Enum formats[8][4] =
		{
			{ TF::R8,   TF::RG8U,   TF::RGB8U,   TF::RGBA8U },
			{ TF::R8I,   TF::RG8I,   TF::RGB8I,   TF::RGBA8I },
			{ TF::R16,  TF::RG16,  TF::Unknown, TF::RGBA16U },
			{ TF::R16I,  TF::RG16I,  TF::Unknown, TF::RGBA16I },
			{ TF::R32U,  TF::RG32U,  TF::Unknown, TF::RGBA32U },
			{ TF::R32I,  TF::RG32I,  TF::Unknown, TF::RGBA32I },
			{ TF::R16F,  TF::RG16F,  TF::Unknown, TF::RGBA16F },
			{ TF::R32F,  TF::RG32F,  TF::Unknown, TF::RGBA32F },
		};

		size_t index = size_t(element.type);
		assert(index < 8 && element.size > 0 && element.size <= 4);
		return formats[index][element.size - 1];
	}

	GpuBuffer::GpuBuffer(Element element, size_t row_size, size_t row_count)
		: m_element(element)
		, m_size(uint32_t(data_type_to_size(element) * row_size * row_count))
		, m_width(uint16_t(row_size))
		, m_height(uint16_t(row_count))
		, m_row_size(uint16_t(data_type_to_size(element) * row_size))
	{
		m_format = data_type_to_texture_format(element);
		m_texture = bgfx::createTexture2D(m_width, m_height, false, 1, m_format);
		//m_buffer = bgfx::createDynamicVertexBuffer(m_froxels.m_memory, decl);
	}

	GpuBuffer::~GpuBuffer()
	{
		bgfx::destroy(m_texture);
	}

	void GpuBuffer::commit(const bgfx::Memory* memory) noexcept
	{
		bgfx::updateTexture2D(m_texture, 0, 0, 0, 0, m_width, m_height, memory);

		/*const uintptr_t size = uintptr_t(end) - uintptr_t(begin);
		assert(size <= m_row_size * m_height);

		for(auto const& range : mDirtyRanges)
		{
			bgfx::updateTexture2D(m_texture, 1, 0, 0, range.start, m_width, range.size, memory);
		}*/
	}

	void GpuBuffer::invalidate() noexcept
	{
		//invalidate(0, m_height);
	}

	void GpuBuffer::invalidate(size_t row, size_t count) noexcept
	{
		UNUSED(row); UNUSED(count);
		//mDirtyRanges.set(uint32_t(row), uint32_t(count));
	}

}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	Camera::Camera()
		: m_eye(Z3)
		, m_target(Zero3)
	{
		m_eye = vec3(10.f);
		m_far = 300.f;
	}

	Camera::Camera(mat4 transform, mat4 projection, bool ortho)
		: m_transform(transform)
		, m_projection(projection)
		, m_orthographic(ortho)
	{}

	Camera::Camera(mat4 transform, float fov, float aspect, float near, float far)
		: m_transform(transform)
		, m_projection(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(mat4 transform, vec2 rect, float near, float far)
		: m_transform(transform)
		, m_projection(bxortho(-rect.x / 2.f, rect.x / 2.f, -rect.y / 2.f, rect.y / 2.f, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth))
		, m_aspect(rect.x / rect.y)
		, m_near(near)
		, m_far(far)
		, m_orthographic(true)
		, m_height(rect.y)
	{}

	Camera::~Camera()
	{}

	Plane Camera::near_plane() const
	{
		vec3 direction = normalize(m_target - m_eye);
		return { m_eye + direction * m_near, direction };
	}

	Plane Camera::far_plane() const
	{
		vec3 direction = normalize(m_target - m_eye);
		return { m_eye + direction * m_far, direction };
	}

	inline vec4 ortho_rect(float height, float aspect) { return { -height / 2.f * aspect, height / 2.f * aspect, -height / 2.f, height / 2.f }; };

	mat4 Camera::projection(float near, float far, bool ndc)
	{
		UNUSED(ndc);
		if(!m_orthographic)
			return bxproj(m_fov, m_aspect, near, far, bgfx::getCaps()->homogeneousDepth);
		else
			return bxortho(ortho_rect(m_height, m_aspect), near, far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::update()
	{
		m_transform = bxlookat(m_eye, m_target);

		if(!m_orthographic)
			m_projection = bxproj(m_fov, m_aspect, m_near, m_far, bgfx::getCaps()->homogeneousDepth);
		else
			m_projection = bxortho(ortho_rect(m_height, m_aspect), m_near, m_far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::set_look_at(const vec3& eye, const vec3& target)
	{
		m_eye = eye;
		m_target = target;
	}

	void Camera::set_isometric(IsometricAngle from_angle, const vec3& position)
	{
		static const vec3 z_angles[3] = { Zero3, -Z3,  Z3 };
		static const vec3 x_angles[3] = { Zero3,  X3, -X3 };

		vec3 angle = Y3 + z_angles[uint8_t(from_angle >> 0)] + x_angles[uint8_t(from_angle >> 8)];

		m_orthographic = true;
		m_height = 1.0f;

		m_target = position;
		m_eye = position + angle;
	}

	Ray Camera::ray(const vec2& offset) const
	{
		mat4 invViewProj = inverse(bxmul(m_transform, m_projection));

		vec3 start = bxmulh(invViewProj, { offset.x, offset.y, 0.0f });
		vec3 end = bxmulh(invViewProj, { offset.x, offset.y, 1.0f });

		return { start, end, normalize(end - start), 1.f / normalize(end - start) };
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <bx/math.h>

#ifndef NO_OCCLUSION_CULLING
#include <MaskedOcclusionCulling.h>
#endif

//#define DEBUG_VISIBLE
//#define DEBUG_CULLED
//#define DEBUG_RECTS
//#define DEBUG_CULLED_RECTS
#define ITEM_TO_CLIP

namespace mud
{
	void screen_space_rect(Render& render, const Camera& camera, const mat4& mat, const vec2& lo, const vec2& hi, const Colour& colour)
	{
		static const mat4 identity = bxidentity();

		const float proj_height = bx::tan(bx::toRad(camera.m_fov) * 0.5f);
		const float proj_width = proj_height * camera.m_aspect;

		float near = camera.m_near * 2.f;
		const float nw = near * proj_width;
		const float nh = near * proj_height;

		Quad rect = {};
		rect.m_vertices[0] = mulp(mat, vec3(hi.x * nw, hi.y * nh, -near));
		rect.m_vertices[1] = mulp(mat, vec3(hi.x * nw, lo.y * nh, -near));
		rect.m_vertices[2] = mulp(mat, vec3(lo.x * nw, lo.y * nh, -near));
		rect.m_vertices[3] = mulp(mat, vec3(lo.x * nw, hi.y * nh, -near));
		render.m_shot->m_immediate[0]->draw(identity, { Symbol::wire(colour, true), &rect, OUTLINE });
	}

	// ref: https://github.com/erich666/jgt-code
	// Fast Projected Area Computation for Three-Dimensional Bounding Boxes
	const int indexlist[64][7] =
	{
		{-1,-1,-1,-1,-1,-1,   0}, //  0 inside
		{ 0, 4, 7, 3,-1,-1,   4}, //  1 left
		{ 1, 2, 6, 5,-1,-1,   4}, //  2 right
		{-1,-1,-1,-1,-1,-1,   0}, //  3 -
		{ 0, 1, 5, 4,-1,-1,   4}, //  4 bottom
		{ 0, 1, 5, 4, 7, 3,   6}, //  5 bottom, left
		{ 0, 1, 2, 6, 5, 4,   6}, //  6 bottom, right
		{-1,-1,-1,-1,-1,-1,   0}, //  7 -
		{ 2, 3, 7, 6,-1,-1,   4}, //  8 top
		{ 0, 4, 7, 6, 2, 3,   6}, //  9 top, left
		{ 1, 2, 3, 7, 6, 5,   6}, // 10 top, right
		{-1,-1,-1,-1,-1,-1,   0}, // 11 -
		{-1,-1,-1,-1,-1,-1,   0}, // 12 -
		{-1,-1,-1,-1,-1,-1,   0}, // 13 -
		{-1,-1,-1,-1,-1,-1,   0}, // 14 -
		{-1,-1,-1,-1,-1,-1,   0}, // 15 -
		{ 0, 3, 2, 1,-1,-1,   4}, // 16 front
		{ 0, 4, 7, 3, 2, 1,   6}, // 17 front, left
		{ 0, 3, 2, 6, 5, 1,   6}, // 18 front, right
		{-1,-1,-1,-1,-1,-1,   0}, // 19 -
		{ 0, 3, 2, 1, 5, 4,   6}, // 20 front, bottom
		{ 1, 5, 4, 7, 3, 2,   6}, // 21 front, bottom, left
		{ 0, 3, 2, 6, 5, 4,   6}, // 22 front, bottom, right
		{-1,-1,-1,-1,-1,-1,   0}, // 23 -
		{ 0, 3, 7, 6, 2, 1,   6}, // 24 front, top
		{ 0, 4, 7, 6, 2, 1,   6}, // 25 front, top, left
		{ 0, 3, 7, 6, 5, 1,   6}, // 26 front, top, right
		{-1,-1,-1,-1,-1,-1,   0}, // 27 -
		{-1,-1,-1,-1,-1,-1,   0}, // 28 -
		{-1,-1,-1,-1,-1,-1,   0}, // 29 -
		{-1,-1,-1,-1,-1,-1,   0}, // 30 -
		{-1,-1,-1,-1,-1,-1,   0}, // 31 -
		{ 4, 5, 6, 7,-1,-1,   4}, // 32 back
		{ 0, 4, 5, 6, 7, 3,   6}, // 33 back, left
		{ 1, 2, 6, 7, 4, 5,   6}, // 34 back, right
		{-1,-1,-1,-1,-1,-1,   0}, // 35 -
		{ 0, 1, 5, 6, 7, 4,   6}, // 36 back, bottom
		{ 0, 1, 5, 6, 7, 3,   6}, // 37 back, bottom, left
		{ 0, 1, 2, 6, 7, 4,   6}, // 38 back, bottom, right
		{-1,-1,-1,-1,-1,-1,   0}, // 39 -
		{ 2, 3, 7, 4, 5, 6,   6}, // 40 back, top
		{ 0, 4, 5, 6, 2, 3,   6}, // 41 back, top, left
		{ 1, 2, 3, 7, 4, 5,   6}, // 42 back, top, right
		{-1,-1,-1,-1,-1,-1,   0}, // 43 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 44 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 45 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 46 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 47 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 48 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 49 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 50 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 51 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 52 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 53 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 54 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 55 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 56 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 57 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 58 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 59 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 60 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 61 invalid
		{-1,-1,-1,-1,-1,-1,   0}, // 62 invalid
		{-1,-1,-1,-1,-1,-1,   0}  // 63 invalid
	};

	Point8 aabb_corners(const vec3& lo, const vec3& hi)
	{
		Point8 corners;
		corners[0] = vec3(lo[0], lo[1], lo[2]); //     7+------+6
		corners[1] = vec3(hi[0], lo[1], lo[2]); //     /|     /|
		corners[2] = vec3(hi[0], hi[1], lo[2]); //    / |    / |
		corners[3] = vec3(lo[0], hi[1], lo[2]); //   / 4+---/--+5
		corners[4] = vec3(lo[0], lo[1], hi[2]); // 3+------+2 /    y   z
		corners[5] = vec3(hi[0], lo[1], hi[2]); //  | /    | /     |  /
		corners[6] = vec3(hi[0], hi[1], hi[2]); //  |/     |/      |/
		corners[7] = vec3(lo[0], hi[1], hi[2]); // 0+------+1      *---x
		return corners;
	}

	struct DepthRect { vec2 lo; vec2 hi; float depth; };

	// eye point (in bbox object coordinates)
	DepthRect project_aabb(const vec3& eye, float far, const vec3& lo, const vec3& hi, const mat4& transform, const mat4& view)
	{
		DepthRect rect = { vec2(FLT_MAX), vec2(-FLT_MAX), far };

		//compute 6-bit code to classify eye with respect to the 6 defining planes of the bbox
		int pos = ((eye[0] < lo[0]) ?  1 : 0)   // 1 = left
			    + ((eye[0] > hi[0]) ?  2 : 0)   // 2 = right
			    + ((eye[1] < lo[1]) ?  4 : 0)   // 4 = bottom
			    + ((eye[1] > hi[1]) ?  8 : 0)   // 8 = top
			    + ((eye[2] < lo[2]) ? 16 : 0)   // 16 = front
			    + ((eye[2] > hi[2]) ? 32 : 0);  // 32 = back

		int num = indexlist[pos][6]; // look up number of vertices in outline
		if(num == 0) return rect;  // invalid case

		Point8 corners = aabb_corners(lo, hi);

		struct vec3w { float x; float y; float w; };
		auto mulxyproj = [](const mat4& mat, const vec3& vec) -> vec3w
		{
			const float* pmat = value_ptr(mat);
			float x = vec[0] * pmat[0] + vec[1] * pmat[4] + vec[2] * pmat[8] + pmat[12];
			float y = vec[0] * pmat[1] + vec[1] * pmat[5] + vec[2] * pmat[9] + pmat[13];
			float w = vec[0] * pmat[3] + vec[1] * pmat[7] + vec[2] * pmat[11] + pmat[15];
			float invw = sign(w) / w;
			vec2 point = vec2(x, y) * invw;
			return { point.x, point.y, w };
		};

		mat4 local_to_clip = view * transform;

		for(int i = 0; i < num; i++) // transform all outline corners into 2D screen space
		{
			vec3w p = mulxyproj(local_to_clip, corners[indexlist[pos][i]]);
			rect.depth = max(0.f, min(p.w, rect.depth));
			rect.lo = min(vec2(p.x, p.y), rect.lo);
			rect.hi = max(vec2(p.x, p.y), rect.hi);
		}

		return rect;
	}

	DepthRect project_aabb(const Camera& camera, const mat4& transform, const Aabb& aabb)
	{
		return project_aabb(camera.m_eye, camera.m_far, aabb.bmin(), aabb.bmax(), transform, camera.m_transform);
	}

	DepthRect project_aabb_strict(const Camera& camera, const mat4& transform, const Aabb& aabb)
	{
		DepthRect rect = { vec2(FLT_MAX), vec2(-FLT_MAX), camera.m_far };
		Point8 corners = aabb_corners(aabb.bmin(), aabb.bmax());
		for(size_t i = 0; i < 8; ++i)
		{
			vec4 p = transform * vec4(corners[i], 1.f);
			rect.depth = max(0.f, min(p.w, rect.depth));
			p /= p.w;
			rect.lo = min(vec2(p), rect.lo);
			rect.hi = max(vec2(p), rect.hi);
		}
		return rect;
	}

#ifdef NO_OCCLUSION_CULLING
	Culler::Culler(Viewport& viewport) : m_viewport(&viewport) {}
	Culler::~Culler() {}
	void Culler::begin(Viewport& viewport) { UNUSED(viewport); }
	void Culler::render(Render& render) { UNUSED(render); }
	void Culler::rasterize(Render& render) { UNUSED(render); }
	void Culler::cull(Render& render) { UNUSED(render); }
	void Culler::debug(Render& render) { UNUSED(render); }
#else
	Culler::Culler(Viewport& viewport)
		: m_viewport(&viewport)
	{
		m_moc = MaskedOcclusionCulling::Create();
	}

	Culler::~Culler()
	{
		MaskedOcclusionCulling::Destroy(m_moc);
	}

	void Culler::begin(Viewport& viewport)
	{
		//auto round = [](uint number, uint multiple) { return ((number + multiple / 2) / multiple) * multiple; };
		auto round = [](uint number, uint multiple) { return (number / multiple) * multiple; };

		// these are defines in culling library but not exposed
		uvec2 size = { round(rect_w(viewport.m_rect), 8), round(rect_h(viewport.m_rect), 4) };

		unsigned int width, height;
		m_moc->GetResolution(width, height);

		if(width != size.x || height != size.y)
			m_moc->SetResolution(size.x, size.y);

		m_moc->ClearBuffer();
	}

	void Culler::render(Render& render)
	{
		if(rect_w(render.m_viewport.m_rect) == 0 || rect_h(render.m_viewport.m_rect) == 0)
			return;

		this->begin(render.m_viewport);
		this->rasterize(render);
		this->cull(render);
		//this->debug(render);

#ifdef DEBUG_VISIBLE
		mat4 identity = bxidentity();
		bool debug = render.m_target != nullptr;
		if(debug)
			for(Item* item : render.m_shot->m_items)
				if((item->m_flags & ItemFlag::Occluder) == 0)
				{
					Colour colour = { 1.f, 1.f, 0.f, 0.15f };
					render.m_shot->m_immediate[0]->draw(identity, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
				}
#endif
	}

	void Culler::rasterize(Render& render)
	{
		const mat4 world_to_clip = render.m_camera.m_projection * render.m_camera.m_transform;

		for(Item* item : render.m_shot->m_occluders)
		{
			const mat4 model_to_clip = world_to_clip * item->m_node->m_transform;

			for(ModelItem& model_item : item->m_model->m_items)
			{
				Mesh& mesh = *model_item.m_mesh;

				if(mesh.m_draw_mode == DrawMode::OUTLINE)
					continue;

				float* vertices = (float*)mesh.m_cached_vertices.data();
				size_t stride = vertex_size(mesh.m_vertex_format); // sizeof(vec3)

				MaskedOcclusionCulling::VertexLayout layout = { int(stride), 4, 8 };

				if(mesh.m_index32)
				{
					uint32_t* indices = (uint32_t*)mesh.m_cached_indices.data();
					m_moc->RenderTriangles(vertices, indices, mesh.m_index_count / 3, value_ptr(model_to_clip),
										   MaskedOcclusionCulling::BACKFACE_CW, MaskedOcclusionCulling::CLIP_PLANE_ALL, layout);
				}
				else
				{
					uint16_t* indices = (uint16_t*)mesh.m_cached_indices.data();
					m_moc->RenderTriangles(vertices, indices, mesh.m_index_count / 3, value_ptr(model_to_clip),
										   MaskedOcclusionCulling::BACKFACE_CW, MaskedOcclusionCulling::CLIP_PLANE_ALL, layout);
				}
			}
		}
	}

	void Culler::cull(Render& render)
	{
		static const mat4 identity = bxidentity();
		const mat4 world_to_clip = render.m_camera.m_projection * render.m_camera.m_transform;
		const mat4 camera_to_world = inverse(render.m_camera.m_transform);

		vector<Item*> items = render.m_shot->m_items;
		render.m_shot->m_items.clear();

		Plane near = render.m_camera.near_plane();

		vector<Item*> culled;
		for(Item* item : items)
		{
			if((item->m_flags & ItemFlag::Occluder) != 0)
			{
				render.m_shot->m_items.push_back(item);
				continue;
			}

#ifdef ITEM_TO_CLIP
			mat4 item_to_clip = world_to_clip * item->m_node->m_transform;
			DepthRect bounds = project_aabb_strict(render.m_camera, item_to_clip, item->m_model->m_aabb);
#else
			DepthRect bounds = project_aabb_strict(render.m_camera, world_to_clip, item->m_aabb);
#endif

			MaskedOcclusionCulling::CullingResult result = m_moc->TestRect(bounds.lo.x, bounds.lo.y, bounds.hi.x, bounds.hi.y, bounds.depth);
			if(result == MaskedOcclusionCulling::VISIBLE)
				render.m_shot->m_items.push_back(item);
			else
				culled.push_back(item);

#ifdef DEBUG_CULLED_RECTS
			if(result != MaskedOcclusionCulling::VISIBLE)
				screen_space_rect(render, render.m_camera, camera_to_world, bounds.lo, bounds.hi, Colour::Pink);
#endif
#ifdef DEBUG_RECTS
			screen_space_rect(render, render.m_camera, camera_to_world, bounds.lo, bounds.hi, Colour::Cyan);
#endif
		}

#ifdef DEBUG_CULLED
		bool debug = render.m_target != nullptr;
		if(debug)
			for(Item* item : culled)
			{
				Colour colour = { 1.f, 0.f, 1.f, 0.15f };
				render.m_shot->m_immediate[0]->draw(identity, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
			}
#endif
	}

	void Culler::debug(Render& render)
	{
		if(render.m_frame.m_frame % 30 == 0)
		{
			uint16_t width = uint16_t(rect_w(render.m_viewport.m_rect));
			uint16_t height = uint16_t(rect_h(render.m_viewport.m_rect));
			m_depth_data.resize(width * height);

			m_moc->ComputePixelDepthBuffer(m_depth_data.data(), false);

			if(!bgfx::isValid(m_depth_texture))
				m_depth_texture = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::R32F);

			const bgfx::Memory* memory = bgfx::makeRef(m_depth_data.data(), width * height * sizeof(float));
			bgfx::updateTexture2D(m_depth_texture, 0, 0, 0, 0, width, height, memory);
		}

		BlockCopy& copy = *render.m_scene.m_gfx_system.m_pipeline->block<BlockCopy>();
		copy.debug_show_texture(render, m_depth_texture, vec4(0.f));
	}
#endif
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	PassDepth::PassDepth(GfxSystem& gfx_system, cstring name, BlockDepth& block_depth)
		: DrawPass(gfx_system, name, PassType::Depth)
		, m_block_depth(block_depth)
	{}

	PassDepth::PassDepth(GfxSystem& gfx_system, BlockDepth& block_depth)
		: PassDepth(gfx_system, "depth", block_depth)
	{}

	void PassDepth::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW ;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

		m_block_depth.m_current_params = &m_block_depth.m_depth_params;
	}

	void PassDepth::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		
		if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
		{
			if(element.m_item->m_shadow == ItemShadow::DoubleSided)
				element.m_material = m_block_depth.m_depth_material_twosided;
			else
				element.m_material = m_block_depth.m_depth_material;

			element.m_program = element.m_material->m_program;
			element.m_shader_version = { element.m_material->m_program };

			this->add_element(render, element);
		}
	}

	BlockDepth::BlockDepth(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockDepth>())
	{}

	BlockDepth::~BlockDepth()
	{}

	void BlockDepth::init_block()
	{
		m_depth_material = &m_gfx_system.fetch_material("depth", "depth");
		m_depth_material_twosided = &m_gfx_system.fetch_material("depth_twosided", "depth");
		m_depth_material_twosided->m_base_block.m_cull_mode = CullMode::None;
		u_depth.createUniforms();
	}

	void BlockDepth::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockDepth::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		encoder.setUniform(u_depth.u_depth_params, &(*m_current_params));
	}
}

#ifndef MUD_CPP_20
#include <array>
#include <map>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	void shapes_size(array<const ProcShape> shapes, DrawMode draw_mode, ShapeSize& size, size_t& count)
	{
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				size.vec += draw_mode == PLAIN ? symbol_triangle_size(shape).vec
											   : symbol_line_size(shape).vec;
				count++;
			}
	}

	void shapes_size(array<const ProcShape> shapes, array<ShapeSize> size, size_t& count)
	{
		shapes_size(shapes, PLAIN, size[PLAIN], count);
		shapes_size(shapes, OUTLINE, size[OUTLINE], count);
	}

	ImmediateDraw::ImmediateDraw(Material& material)
		: m_material(material)
		, m_cursor{ 0, 0 }
	{
		m_material.m_unshaded_block.m_enabled = true;

		m_batches[PLAIN].resize(64);
		m_batches[OUTLINE].resize(64);

		ms_vertex_decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour);
	}

	void ImmediateDraw::begin()
	{
		DrawMode draw_modes[2] = { PLAIN, OUTLINE };
		for(DrawMode draw_mode : draw_modes)
			for(Batch& batch : m_batches[draw_mode])
			{
				batch.m_vertices.clear();
				batch.m_indices.clear();
			}
	}

	ImmediateDraw::Batch* ImmediateDraw::batch(DrawMode draw_mode, size_t vertex_count)
	{
		size_t& cursor = m_cursor[draw_mode];
		if(m_batches[draw_mode][cursor].m_vertices.size() + vertex_count > UINT16_MAX)
			cursor++;
		if(cursor > m_batches[draw_mode].size())
			return nullptr;
		return &m_batches[draw_mode][cursor];
	}

	void ImmediateDraw::draw(const mat4& transform, const ProcShape& shape)
	{
		this->draw(transform, carray<ProcShape, 1>{ shape });
	}

	void ImmediateDraw::draw(const mat4& transform, array<ProcShape> shapes)
	{
		ShapeSize size[2] = { { 0, 0 }, { 0, 0 } };
		size_t shape_count = 0;

		shapes_size(shapes, { size, 2 }, shape_count);

		if(size[PLAIN].vertex_count)
			this->draw(transform, shapes, size[PLAIN], PLAIN);
		if(size[OUTLINE].vertex_count)
			this->draw(transform, shapes, size[OUTLINE], OUTLINE);
	}

	void ImmediateDraw::draw(const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		Batch* batch = this->batch(draw_mode, size.vertex_count);
		if(batch)
			this->draw(*batch, transform, shapes, size, draw_mode);
	}

	void ImmediateDraw::draw(Batch& batch, const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		size_t vertex_offset = batch.m_vertices.size();
		size_t index_offset = batch.m_indices.size();

		batch.m_vertices.resize(batch.m_vertices.size() + size.vertex_count);
		batch.m_indices.resize(batch.m_indices.size() + size.index_count);

		MeshAdapter data(Vertex::vertex_format, &batch.m_vertices[vertex_offset], size.vertex_count, &batch.m_indices[index_offset], size.index_count, false);
		data.m_offset = uint32_t(vertex_offset);

		for(const ProcShape& shape : shapes)
		{
			draw_mode == OUTLINE ? symbol_draw_lines(shape, data)
								 : symbol_draw_triangles(shape, data);
			data.next();
		}

		for(size_t i = vertex_offset; i < batch.m_vertices.size(); ++i)
		{
			batch.m_vertices[i].m_position = vec3(transform * vec4(batch.m_vertices[i].m_position, 1.f));
			//batch.m_vertices[i].m_position = batch.m_vertices[i].m_position;
		}
	}

	void ImmediateDraw::submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state)
	{
		this->submit(encoder, view, bgfx_state, PLAIN);
		this->submit(encoder, view, bgfx_state, OUTLINE);
	}

	void ImmediateDraw::submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode)
	{
		for(Batch& batch : m_batches[draw_mode])
			this->submit(encoder, view, bgfx_state, draw_mode, batch);
		m_cursor[draw_mode] = 0;
	}

	void ImmediateDraw::submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode, Batch& batch)
	{
		if(batch.m_vertices.empty())
			return;

		uint32_t num_vertices = uint32_t(batch.m_vertices.size());
		uint32_t num_indices = uint32_t(batch.m_indices.size());

		if(num_vertices != bgfx::getAvailTransientVertexBuffer(num_vertices, ms_vertex_decl)
		|| num_indices != bgfx::getAvailTransientIndexBuffer(num_indices))
			return;

		bgfx::TransientVertexBuffer vertex_buffer;
		bgfx::allocTransientVertexBuffer(&vertex_buffer, num_vertices, ms_vertex_decl);
		bx::memCopy(vertex_buffer.data, batch.m_vertices.data(), num_vertices * sizeof(Vertex));//ms_vertex_decl.m_stride);

		bgfx::TransientIndexBuffer index_buffer;
		bgfx::allocTransientIndexBuffer(&index_buffer, num_indices);
		bx::memCopy(index_buffer.data, batch.m_indices.data(), num_indices * sizeof(uint16_t));

		m_material.submit(encoder, bgfx_state);

		encoder.setVertexBuffer(0, &vertex_buffer);
		encoder.setIndexBuffer(&index_buffer);
		encoder.setState(draw_mode == OUTLINE ? bgfx_state | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA : bgfx_state);

		mat4 identity = bxidentity();
		encoder.setTransform(value_ptr(identity));

		encoder.submit(view, m_material.m_program->default_version());
	}

	bgfx::VertexDecl ImmediateDraw::ms_vertex_decl;

	struct SymbolIndex::Impl
	{
		std::map<uint64_t, Material*> m_materials;
		std::map<uint64_t, std::map<std::array<char, c_max_shape_size>, object<Model>>> m_symbols;
	};

	SymbolIndex::SymbolIndex()
		: m_impl(make_unique<Impl>())
	{}

	SymbolIndex::~SymbolIndex()
	{}

	uint64_t hash_symbol(const Symbol& symbol, DrawMode draw_mode)
	{
		return uint64_t(symbol.m_detail) | uint64_t(draw_mode << 16);
	}

	uint64_t hash_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		return draw_mode == PLAIN ? uint64_t(to_abgr(symbol.m_fill)) | uint64_t(symbol.m_overlay) << 32 | uint64_t(symbol.m_double_sided) << 33
								  : uint64_t(to_abgr(symbol.m_outline)) | uint64_t(symbol.m_overlay) << 32 | uint64_t(symbol.m_double_sided) << 33;
	}

	Material& SymbolIndex::symbol_material(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode)
	{
		Colour colour = draw_mode == PLAIN ? symbol.m_fill : symbol.m_outline;

		uint64_t hash = hash_symbol_material(symbol, draw_mode);
		if(m_impl->m_materials.find(hash) == m_impl->m_materials.end())
		{
			Material& m = gfx_system.fetch_material("Symbol" + to_string(hash), "unshaded");
			m.m_base_block.m_depth_draw_mode = DepthDraw::Disabled;
			m.m_base_block.m_depth_test = symbol.m_overlay ? DepthTest::Disabled : DepthTest::Enabled;
			m.m_base_block.m_cull_mode = symbol.m_double_sided ? CullMode::None : CullMode::Back;
			m.m_unshaded_block.m_enabled = true;
			m.m_unshaded_block.m_colour.m_value = colour;
			m_impl->m_materials[hash] = &m;
		}
		return *m_impl->m_materials[hash];
	}

	Model& SymbolIndex::symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		uint64_t hash = hash_symbol(symbol, draw_mode);
		std::array<char, c_max_shape_size> shape_mem = {};
		std::memcpy(&shape_mem[0], (void*) &shape, shape.m_type.m_size);

		auto& shapes = m_impl->m_symbols[hash];
		if(shapes.find(shape_mem) == shapes.end())
		{
			//printf("INFO: created indexed Shape %s %s\n", shape.m_type.m_name, pack_json(Ref(&shape)).c_str());
			string name = "Shape:" + string(shape.m_type.m_name);
			shapes[shape_mem] = draw_model(name.c_str(), ProcShape{ symbol, &shape, draw_mode }, true);
		}

		return *shapes[shape_mem];
	}

	object<Model> draw_model(cstring id, const ProcShape& shape, bool readback)
	{
		return draw_model(id, vector<ProcShape>{ { shape } }, readback);
	}

	object<Model> draw_model(cstring id, const vector<ProcShape>& shapes, bool readback)
	{
		object<Model> model = make_object<Model>(id);
		draw_model(shapes, *model, readback);
		return model;
	}

	void draw_model(const ProcShape& shape, Model& model, bool readback, Material* material)
	{
		draw_model(vector<ProcShape>{ { shape } }, model, readback, material);
	}

	void draw_model(const vector<ProcShape>& shapes, Model& model, bool readback, Material* material)
	{
		ShapeSize size[2] = { { 0, 0 }, { 0, 0 } };
		size_t shape_count = 0;

		shapes_size(shapes, { size, 2 }, shape_count);

		if(size[PLAIN].vertex_count)
			draw_mesh(shapes, model, size[PLAIN], PLAIN, readback, material);
		if(size[OUTLINE].vertex_count)
			draw_mesh(shapes, model, size[OUTLINE], OUTLINE, readback, material);

		model.prepare();
	}

	void draw_mesh(const ProcShape& shape, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		draw_mesh(vector<ProcShape>{ { shape } }, model, draw_mode, readback, material);
	}

	void draw_mesh(const vector<ProcShape>& shapes, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		ShapeSize size = { 0, 0 };
		size_t shape_count = 0;

		shapes_size(shapes, draw_mode, size, shape_count);
		draw_mesh(shapes, model, size, draw_mode, readback, material);
	}

	void draw_mesh(const vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback, Material* material)
	{
		Mesh& mesh = model.add_mesh(model.m_name + to_string(uint(draw_mode)), readback);
		mesh.m_material = material;

		GpuMesh gpu_mesh = alloc_mesh(ShapeVertex::vertex_format, size.vertex_count, size.index_count);
		
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				draw_mode == OUTLINE ? symbol_draw_lines(shape, gpu_mesh.m_writer)
									 : symbol_draw_triangles(shape, gpu_mesh.m_writer);
				gpu_mesh.m_writer.next();
			}

		if(draw_mode == PLAIN)
			generate_mikkt_tangents({ (ShapeIndex*)gpu_mesh.m_indices, gpu_mesh.m_index_count }, { (ShapeVertex*)gpu_mesh.m_vertices, gpu_mesh.m_vertex_count });

		mesh.upload(draw_mode, gpu_mesh);

		model.add_item(mesh, bxidentity());
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	PassEffects::PassEffects(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "effects", PassType::Effects)
	{}

	void PassEffects::submit_render_pass(Render& render)
	{
		UNUSED(render);
	}

	BlockResolve::BlockResolve(GfxSystem& gfx_system, BlockCopy& copy)
		: GfxBlock(gfx_system, *this)
		, m_copy(copy)
	{}

	void BlockResolve::init_block()
	{}

	void BlockResolve::begin_render(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockResolve::begin_pass(Render& render)
	{
		if(!render.m_is_mrt) return;
		
		// @todo three passes to resolve ? this is terrible :( but we can't read and write from the same buffer at the same time can we
		bgfx::FrameBufferHandle target = render.m_target->m_ping_pong.swap();
		m_copy.submit_quad(*render.m_target, render.composite_pass(), target,
						   render.m_target->m_diffuse, render.m_viewport.m_rect);

		m_copy.submit_quad(*render.m_target, render.composite_pass(), target,
						   render.m_target->m_specular, render.m_viewport.m_rect, BGFX_STATE_BLEND_ADD);

		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target_fbo,
						   render.m_target->m_ping_pong.last(), render.m_viewport.m_rect);
	}

	PassPostProcess::PassPostProcess(GfxSystem& gfx_system, BlockCopy& copy)
		: RenderPass(gfx_system, "post process", PassType::PostProcess)
		, m_copy(copy)
	{}

	void PassPostProcess::submit_render_pass(Render& render)
	{
		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.swap(),
							render.m_target->m_diffuse, render.m_viewport.m_rect);

		for(GfxBlock* block : m_gfx_blocks)
			block->submit_pass(render);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <cstdio>

namespace mud
{
	BlockFilter::BlockFilter(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, *this)
		, m_quad_program(gfx_system.programs().create("filter/quad"))
	{
		static cstring options[5] = {
			"UNPACK_DEPTH",
			"SOURCE_DEPTH",
			"SOURCE_0_CUBE",
			"SOURCE_0_ARRAY",
			"FILTER_DEBUG_UV"
		};
		m_shader_block->m_options = { options, 5 };
	}

	void BlockFilter::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockFilter::begin_render(Render& render)
	{
		UNUSED(render);
		//this->set_uniforms(render);
	}

	void BlockFilter::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockFilter::set_uniforms(Render& render, bgfx::Encoder& encoder)
	{
		render.set_uniforms(encoder);

		vec4 camera_params{ render.m_camera.m_near, render.m_camera.m_far,
							render.m_camera.m_fov, render.m_camera.m_aspect };
		encoder.setUniform(u_uniform.u_camera_params, &camera_params);

		vec4 screen_params{ vec2(render.m_target->m_size),
							1.0f / vec2(render.m_target->m_size) };
		encoder.setUniform(u_uniform.u_screen_size_pixel_size, &screen_params);
	}

	struct ScreenQuadVertex
	{
		vec3 m_pos;
		uint32_t m_rgba;
		vec2 m_texcoord;

		static bgfx::VertexDecl& decl()
		{
			static bgfx::VertexDecl decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour | VertexAttribute::TexCoord0);
			return decl;
		}
	};

	static void draw_quad(const vec2& size, bool fbo_flip)
	{
		if(3 == bgfx::getAvailTransientVertexBuffer(3, ScreenQuadVertex::decl()))
		{
			bgfx::TransientVertexBuffer vertexbuffer;
			bgfx::allocTransientVertexBuffer(&vertexbuffer, 3, ScreenQuadVertex::decl());

			const float zz = -1.0f;

			const vec2 min = { -size.x, 0.f };
			const vec2 max = { size.x, size.y * 2.0f };

			vec2 min_uv = { -1.0f, 0.0f };
			vec2 max_uv = {  1.0f, 2.0f };

			if(fbo_flip && bgfx::getCaps()->originBottomLeft)
			{
				min_uv = { -1.0f,  1.0f };
				max_uv = {  1.0f, -1.0f };
			}

			ScreenQuadVertex* vertex = (ScreenQuadVertex*)vertexbuffer.data;
			vertex[0] = { { min.x, min.y, zz }, 0xffffffff, { min_uv.x, min_uv.y } };
			vertex[1] = { { max.x, max.y, zz }, 0xffffffff, { max_uv.x, max_uv.y } };
			vertex[2] = { { max.x, min.y, zz }, 0xffffffff, { max_uv.x, min_uv.y } };

			bgfx::setVertexBuffer(0, &vertexbuffer);
		}
	}

	static void draw_unit_quad(bool fbo_flip)
	{
		draw_quad({ 1.f, 1.f }, fbo_flip);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		if(quad.m_source.z > 1.f || quad.m_source.w > 1.f)
			printf("WARNING: Source rect expected in relative coordinates\n");

#if _DEBUG
		bgfx::setViewName(view, "quad");
#endif
		bgfx::setViewFrameBuffer(view, fbo);
		bgfx::setViewTransform(view, value_ptr(target.m_screen_view), value_ptr(target.m_screen_proj));
		bgfx::setViewRect(view, uint16_t(quad.m_dest.x), uint16_t(quad.m_dest.y), uint16_t(rect_w(quad.m_dest)), uint16_t(rect_h(quad.m_dest)));

		draw_unit_quad(quad.m_fbo_flip);
		//draw_quad(rect_w(quad.m_dest), rect_h(quad.m_dest));

		bgfx::setUniform(u_uniform.u_source_0_crop, &quad.m_source);

		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW | flags);
		bgfx::submit(view, program);

		if(render)
			bgfx::frame();
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags, bool render)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, fbo, program, quad, flags, render);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		this->submit_quad(target, view, target.m_fbo, program, quad, flags, render); // BGFX_INVALID_HANDLE
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags, bool render)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, program, quad, flags, render);
	}

	void BlockFilter::submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, uint64_t flags, bool render)
	{
		vec4 rect = vec4(vec2(0.f), vec2(target.m_size));
		RenderQuad quad = { target.source_quad(rect), target.dest_quad(rect), true };
		this->submit_quad(target, view, program, quad, flags, render);
	}

	BlockCopy::BlockCopy(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program(gfx_system.programs().create("filter/copy"))
	{
		m_program.register_block(filter);
	}

	void BlockCopy::init_block()
	{}

	void BlockCopy::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, texture, GFX_TEXTURE_CLAMP);
		m_filter.submit_quad(target, view, fbo, m_program.default_version(), quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, fbo, texture, quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags)
	{
		this->submit_quad(target, view, target.m_fbo, texture, quad, flags); // BGFX_INVALID_HANDLE
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags)
	{
		RenderQuad quad = { target.source_quad(vec4(rect)), target.dest_quad(vec4(rect)), true };
		this->submit_quad(target, view, texture, quad, flags);
	}

	void BlockCopy::submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, uint64_t flags)
	{
		vec4 rect = vec4(vec2(0.f), vec2(target.m_size));
		RenderQuad quad = { target.source_quad(rect), target.dest_quad(rect), true };
		this->submit_quad(target, view, texture, quad, flags);
	}

	void BlockCopy::debug_show_texture(Render& render, bgfx::TextureHandle texture, const vec4& rect, bool is_depth, bool is_depth_packed, bool is_array, int level)
	{
		assert(render.m_target);
		vec4 dest = rect == vec4(0.f) ? vec4(vec2(0.f), vec2(render.m_target->m_size) * 0.25f) : rect;;
		RenderQuad target_quad = { Rect4, render.m_target->dest_quad(dest, true) };

		ShaderVersion shader_version = { &m_program };
		if(is_depth)
			shader_version.set_option(m_filter.m_index, FILTER_SOURCE_DEPTH);
		if(is_depth_packed)
			shader_version.set_option(m_filter.m_index, FILTER_UNPACK_DEPTH);
		if(is_array)
			shader_version.set_option(m_filter.m_index, FILTER_SOURCE_0_ARRAY);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, texture, GFX_TEXTURE_CLAMP);
		bgfx::setUniform(m_filter.u_uniform.u_source_0_level, &level);

		uint8_t view = render.debug_pass();
		m_filter.submit_quad(*render.m_target, view, BGFX_INVALID_HANDLE, m_program.version(shader_version), target_quad, 0);
	}
}


#include <bx/allocator.h>
#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/swap.h>
#endif

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <limits>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

//#define USE_STD_BITSET

namespace mud
{
	// This depends on the maximum number of lights (currently 255),and can't be more than 16 bits.
	static_assert(CONFIG_MAX_LIGHT_INDEX <= UINT16_MAX, "can't have more than 65536 lights");
	using RecordBufferType = std::conditional_t<CONFIG_MAX_LIGHT_INDEX <= UINT8_MAX, uint8_t, uint16_t>;

	// this is chosen so froxelizePointAndSpotLight() vectorizes 4 froxel tests / spotlight
	// with 256 lights this implies 8 jobs (256 / 32) for froxelization.

	using LightGroupType = uint32_t;

	// The first entry always encodes the type of light, i.e. point/spot
	using FroxelThreadData = carray<LightGroupType, FROXEL_BUFFER_ENTRY_COUNT_MAX + 1>;

	static constexpr bool SUPPORTS_REMAPPED_FROXELS = false;

	// The Froxel buffer is set to FROXEL_BUFFER_WIDTH x n
	// With n limited by the supported texture dimension, which is guaranteed to be at least 2048
	// in all version of GLES.

	// Make sure this matches the same constants in shading_lit.fs
	constexpr uint32_t FROXEL_BUFFER_WIDTH_SHIFT = 6u;
	constexpr uint32_t FROXEL_BUFFER_WIDTH = 1u << FROXEL_BUFFER_WIDTH_SHIFT;
	constexpr uint32_t FROXEL_BUFFER_WIDTH_MASK = FROXEL_BUFFER_WIDTH - 1u;
	constexpr uint32_t FROXEL_BUFFER_HEIGHT = (FROXEL_BUFFER_ENTRY_COUNT_MAX + FROXEL_BUFFER_WIDTH_MASK) / FROXEL_BUFFER_WIDTH;

	constexpr uint32_t RECORD_BUFFER_WIDTH_SHIFT = 5u;
	constexpr uint32_t RECORD_BUFFER_WIDTH = 1u << RECORD_BUFFER_WIDTH_SHIFT;
	constexpr uint32_t RECORD_BUFFER_WIDTH_MASK = RECORD_BUFFER_WIDTH - 1u;

	constexpr uint32_t RECORD_BUFFER_HEIGHT = 2048;
	constexpr uint32_t RECORD_BUFFER_ENTRY_COUNT = RECORD_BUFFER_WIDTH * RECORD_BUFFER_HEIGHT; // 64K

	// number of lights processed by one group (e.g. 32)
	static constexpr uint32_t LIGHT_PER_GROUP = sizeof(LightGroupType) * 8;

	// number of groups (i.e. jobs) to use for froxelization (e.g. 8)
	static constexpr uint32_t GROUP_COUNT = (CONFIG_MAX_LIGHT_COUNT + LIGHT_PER_GROUP - 1) / LIGHT_PER_GROUP;


	// record buffer cannot be larger than 65K entries because we're using uint16_t to store indices
	// so its maximum size is 128 KiB
	static_assert(RECORD_BUFFER_ENTRY_COUNT <= 65536, "RecordBuffer cannot be larger than 65536 entries");

	inline GpuBuffer::ElementType record_type() { return std::is_same<RecordBufferType, uint8_t>::value ? GpuBuffer::ElementType::UINT8 : GpuBuffer::ElementType::UINT16; }

	// clustered shading refs
	// http://www.humus.name/Articles/PracticalClusteredShading.pdf
	// http://www.cse.chalmers.se/~uffe/clustered_shading_preprint.pdf

	struct LightRecord
	{
#ifndef USE_STD_BITSET
		using Lights = bitset<uint64_t, (CONFIG_MAX_LIGHT_COUNT + 63) / 64>;
#else
		using Lights = std::bitset<CONFIG_MAX_LIGHT_COUNT>;
#endif
		Lights lights;
	};

	struct LightParams
	{
		LightParams(vec3 position, float cosSqr, vec3 axis, float invSin, float radius) : position(position), cosSqr(cosSqr), axis(axis), invSin(invSin), radius(radius) {}
		vec3 position;
		float cosSqr;
		vec3 axis;
		float invSin = std::numeric_limits<float>::infinity(); // this must be initialized to indicate this is a point light
		float radius; // radius is not used in the hot loop, so leave it at the end
	};

	struct Froxelizer::Impl
	{
		Impl()
			: m_froxels({ GpuBuffer::ElementType::UINT16, 2 }, FROXEL_BUFFER_WIDTH, FROXEL_BUFFER_HEIGHT)
			, m_records({ record_type(), 1 }, RECORD_BUFFER_WIDTH, RECORD_BUFFER_HEIGHT)
		{}

		template <class T>
		struct Buffer
		{
			Buffer(GpuBuffer::Element element, uint32_t row_size, uint32_t row_count) : m_buffer(element, row_size, row_count) {}
			GpuBuffer m_buffer;
			vector<T> m_data;
			const bgfx::Memory* m_memory;
		};

		vector<FroxelThreadData> m_froxel_sharded_data;  // 256 KiB w/ 256 lights
		vector<LightRecord> m_light_records;             // 256 KiB w/ 256 lights

		Buffer<FroxelEntry> m_froxels;			//  32 KiB w/ 8192 froxels
		Buffer<RecordBufferType> m_records;		//  64 KiB // max 32 KiB  (actual: resolution dependant)
	};

	void froxelize_light(ClusteredFrustum& frustum, FroxelThreadData& froxelThread, uint32_t bit, const mat4& projection, float near, const LightParams& light, float light_far);

	Froxelizer::Froxelizer(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_impl(construct<Impl>())
	{
		UNUSED(RECORD_BUFFER_WIDTH_MASK);
		m_uniform.createUniforms();
	}

	Froxelizer::~Froxelizer()
	{}

	uint32_t Froxelizer::record(uint32_t cluster) { return m_impl->m_froxels.m_data[cluster].offset; }
	uint32_t Froxelizer::count(uint32_t record, int type) { return m_impl->m_froxels.m_data[record].count[type]; }
	uint32_t Froxelizer::light(uint32_t record) { return m_impl->m_records.m_data[record]; }

	bool Froxelizer::update(const Viewport& viewport, const mat4& projection, float near, float far)
	{
		if(m_viewport != &viewport || m_viewport->m_rect != viewport.m_rect) //[[unlikely]]
			m_dirty |= VIEWPORT_CHANGED;
		if(m_projection != projection) //[[unlikely]]
			m_dirty |= PROJECTION_CHANGED;

		//if(all(less(abs(m_projection), vec3(EPSILON))))

		m_viewport = &viewport;
		m_projection = projection;
		m_near = near;
		UNUSED(far);

		bool uniformsNeedUpdating = false;

		if(m_dirty) // [[unlikely]] 
			uniformsNeedUpdating = update();

		return uniformsNeedUpdating;
	}

	bool Froxelizer::prepare(const Viewport& viewport, const mat4& projection, float near, float far)
	{
		bool uniformsNeedUpdating = this->update(viewport, projection, near, far);

		// froxel buffer (~32 KiB) & record buffer (~64 KiB)
		m_impl->m_froxels.m_data.resize(FROXEL_BUFFER_ENTRY_COUNT_MAX);
		m_impl->m_records.m_data.resize(RECORD_BUFFER_ENTRY_COUNT);

		m_impl->m_light_records.resize(FROXEL_BUFFER_ENTRY_COUNT_MAX);  // light records per froxel (~256 KiB)
		m_impl->m_froxel_sharded_data.resize(GROUP_COUNT);				// froxel thread data (~256 KiB)

		return uniformsNeedUpdating;
	}

	void Froxelizer::update_viewport()
	{
		m_frustum.m_near = m_light_near;
		m_frustum.m_far = m_light_far;

		m_frustum.resize(rect_size(vec4(m_viewport->m_rect)));

		m_params_z = { 0.f, 0.f, -m_frustum.m_linearizer, float(m_frustum.m_subdiv_z) };
		if(SUPPORTS_REMAPPED_FROXELS)
		{
			m_params_f.x = uint32_t(m_frustum.m_subdiv_z);
			m_params_f.y = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_z);
			m_params_f.z = 1;
		}
		else
		{
			m_params_f.x = 1;
			m_params_f.y = uint32_t(m_frustum.m_subdiv_x);
			m_params_f.z = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y);
		}
	}

	void Froxelizer::update_projection()
	{
		m_frustum.recompute(m_projection, rect_size(vec4(m_viewport->m_rect)));

		//    linearizer = log2(zLightFar / zLightNear) / (zcount - 1)
		//    vz = -exp2((i - zcount) * linearizer) * zLightFar
		// => i = log2(zLightFar / -vz) / -linearizer + zcount
		
		float Pz = m_projection[2][2];
		float Pw = m_projection[3][2];
		if(m_projection[2][3] != 0)
		{
			// perspective projection
			// (clip) cz = Pz*vz+Pw, cw=-vz
			// (ndc)  nz = -Pz-Pw/vz
			// (win)  fz = -Pz*0.5+0.5 - Pw*0.5/vz
			// ->  = vz = -Pw / (2*fz + Pz-1)
			// i = log2(zLightFar*(2*fz + Pz-1) / Pw) / -linearizer + zcount
			m_params_z[0] = 2.0f * m_light_far / Pw;
			m_params_z[1] = m_light_far * (Pz - 1.0f) / Pw;
		}
		else
		{
			// orthographic projection
			// (clip) cz = Pz*vz+Pw, cw=1
			// (ndc)  nz = Pz*vz+Pw
			// (win)  fz = Pz*vz*0.5 + Pw*0.5+0.5
			// ->  = vz = (2*fz - Pw-1)/Pz
			// i = log2(-vz / zLightFar) / linearizer + zcount
			// i = log2((-2*fz + Pw + 1)/(Pz*zLightFar)) / linearizer + zcount

			m_params_z[0] = -2.0f / (Pz * m_light_far);
			m_params_z[1] = (1.0f + Pw) / (Pz * m_light_far);
			m_params_z[2] = m_frustum.m_linearizer;
		}

		if(m_debug_clusters.size() > 0)
			this->compute_froxels();
	}

	bool Froxelizer::update()
	{
		bool uniformsNeedUpdating = false;
		if(m_dirty & VIEWPORT_CHANGED) // [[unlikely]] 
		{
			update_viewport();
			uniformsNeedUpdating = true;
		}

		if(m_dirty & (PROJECTION_CHANGED | VIEWPORT_CHANGED)) // [[unlikely]] 
		{
			update_projection();
			uniformsNeedUpdating = true;
		}
		assert(m_light_near >= m_near);
		m_dirty = 0;
		return uniformsNeedUpdating;
	}

	void Froxelizer::compute_froxels()
	{	
		m_debug_clusters.resize(m_frustum.m_cluster_count);

		uint32_t i = 0;

		for(uint16_t z = 0; z < m_frustum.m_subdiv_z; ++z)
		for(uint16_t y = 0; y < m_frustum.m_subdiv_y; ++y)
		for(uint16_t x = 0; x < m_frustum.m_subdiv_x; ++x)
		{
			m_debug_clusters[i++] = m_frustum.cluster_frustum(x, y, z);
		}
	}

	void Froxelizer::upload()
	{
		m_impl->m_froxels.m_memory = bgfx::copy(m_impl->m_froxels.m_data.data(), uint32_t(sizeof(FroxelEntry) * m_impl->m_froxels.m_data.size()));
		m_impl->m_records.m_memory = bgfx::copy(m_impl->m_records.m_data.data(), uint32_t(sizeof(RecordBufferType) * m_impl->m_records.m_data.size()));

		// send data to GPU
		m_impl->m_froxels.m_buffer.commit(m_impl->m_froxels.m_memory);
		m_impl->m_records.m_buffer.commit(m_impl->m_records.m_memory);
	}

	void Froxelizer::submit(bgfx::Encoder& encoder) const
	{
		encoder.setTexture(uint8_t(TextureSampler::LightRecords), m_uniform.s_light_records, m_impl->m_records.m_buffer.m_texture);
		encoder.setTexture(uint8_t(TextureSampler::Clusters), m_uniform.s_light_clusters, m_impl->m_froxels.m_buffer.m_texture);

		auto submit = [=](bgfx::Encoder& encoder, vec4 params, vec4 f, vec4 z)
		{
			encoder.setUniform(m_uniform.u_froxel_params, &params);
			encoder.setUniform(m_uniform.u_froxel_f, &f);
			encoder.setUniform(m_uniform.u_froxel_z, &z);
		};

		submit(encoder, vec4(m_frustum.m_inv_tile_size, rect_offset(vec4(m_viewport->m_rect))), vec4(vec3(m_params_f), 0.f), m_params_z);
	}

	void Froxelizer::froxelize_lights(const Camera& camera, array<Light*> lights)
	{
		// note: this is called asynchronously
		froxelize_loop(camera, lights);
		froxelize_assign_records_compress(uint32_t(lights.size()));
	}

	void Froxelizer::froxelize_light_group(const Camera& camera, array<Light*> lights, uint32_t offset, uint32_t stride)
	{
		const mat4& projection = m_projection;

		for(uint32_t i = offset; i < lights.size(); i += stride)
		{
			vec3 position = mulp(camera.m_transform, lights[i]->m_node.position());
			vec3 direction = muln(camera.m_transform, lights[i]->m_node.direction());

			float cos2 = bx::square(cos(to_radians(lights[i]->m_spot_angle)));
			float invsin = 1.f / std::sqrt(1.f - cos2);

			LightParams light = { position, cos2, direction, invsin, lights[i]->m_range };

			const uint32_t group = i % GROUP_COUNT;
			const uint32_t bit = i / GROUP_COUNT;
			assert(bit < LIGHT_PER_GROUP);

			FroxelThreadData& threadData = m_impl->m_froxel_sharded_data[group];
			const bool isSpot = light.invSin != std::numeric_limits<float>::infinity();
			threadData[0] |= isSpot << bit;
			froxelize_light(m_frustum, threadData, bit, projection, m_near, light, m_light_far);
		}
	}

#define MUD_THREADED

	void Froxelizer::froxelize_loop(const Camera& camera, array<Light*> lights)
	{
		memset(m_impl->m_froxel_sharded_data.data(), 0, m_impl->m_froxel_sharded_data.size() * sizeof(FroxelThreadData));

#ifdef MUD_THREADED
		JobSystem& js = *m_gfx_system.m_job_system;
		Job* parent = js.job();
		for(uint32_t i = 0; i < GROUP_COUNT; i++)
		{
			auto task = [=, &camera](JobSystem&, Job*) { this->froxelize_light_group(camera, lights, i, GROUP_COUNT); };
			js.run(js.job(parent, task));
		}
		js.complete(parent);
#else
		for(uint32_t i = 0; i < GROUP_COUNT; i++)
			this->froxelize_light_group(camera, lights, i, GROUP_COUNT);
#endif
	}

	void Froxelizer::froxelize_assign_records_compress(uint32_t num_lights)
	{
		UNUSED(num_lights);

		auto inspect = [&]()
		{
			uint32_t i = 0;
			for(FroxelEntry& entry : m_impl->m_froxels.m_data)
			{
				if((entry.count[0] > 0 || entry.count[1] > 0) && entry.offset == 0)
					printf("froxel %i has lights but offset 0\n", int(i));
				i++;
			}
		};
		UNUSED(inspect);

		// convert froxel data from N groups of M bits to LightRecord::Lights, so we can
		// easily compare adjacent froxels, for compaction. The conversion loops below get
		// inlined and vectorized in release builds.

		// keep these two loops separate, it helps the compiler a lot
		LightRecord::Lights spot_lights;

		using container_type = LightRecord::Lights::container_type;
		constexpr uint32_t r = sizeof(container_type) / sizeof(LightGroupType);

		for(uint32_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
		{
			container_type b = m_impl->m_froxel_sharded_data[i * r][0];
			for(uint32_t k = 0; k < r; k++)
				b |= (container_type(m_impl->m_froxel_sharded_data[i * r + k][0]) << (LIGHT_PER_GROUP * k));
			spot_lights.at(i) = b;
		}

		// this gets very well vectorized...
		for(uint32_t j = 1, jc = FROXEL_BUFFER_ENTRY_COUNT_MAX; j < jc; j++)
		{
			for(uint32_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
			{
				container_type b = m_impl->m_froxel_sharded_data[i * r][j];
				for(uint32_t k = 0; k < r; k++)
					b |= (container_type(m_impl->m_froxel_sharded_data[i * r + k][j]) << (LIGHT_PER_GROUP * k));
				m_impl->m_light_records[j - 1].lights.at(i) = b;
			}
		}

		uint16_t offset = 0;

		auto remap = [stride = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y)](uint32_t i) -> uint32_t
		{
			if(SUPPORTS_REMAPPED_FROXELS) {
				// TODO: with the non-square froxel change these would be mask ops instead of divide.
				i = (i % stride) * CONFIG_FROXEL_SLICE_COUNT + (i / stride);
			}
			return i;
		};

		uint32_t num_clusters = m_frustum.m_cluster_count;
		for(uint32_t cluster = 0; cluster < num_clusters;)
		{
			LightRecord b = m_impl->m_light_records[cluster];
			if(b.lights.none())
			{
				m_impl->m_froxels.m_data[remap(cluster++)].u32 = 0;
				continue;
			}

			// We have a limitation of 255 spot + 255 point lights per froxel.
			uint8_t point_count = uint8_t(min(255U, uint32_t((b.lights & ~spot_lights).count())));
			uint8_t spot_count = uint8_t(min(255U, uint32_t((b.lights &  spot_lights).count())));

			FroxelEntry entry = { offset, point_count, spot_count };

			const uint8_t light_count = entry.count[0] + entry.count[1];

			if(offset + light_count >= RECORD_BUFFER_ENTRY_COUNT) //[[unlikely]]
			{
				// note: instead of dropping froxels we could look for similar records we've already
				// filed up.
				do { // this compiles to memset() when remap() is identity
					m_impl->m_froxels.m_data[remap(cluster++)].u32 = 0;
				} while(cluster < num_clusters);
				goto out_of_memory;
			}

			// iterate the bitfield
			uint32_t first_point = offset;
			uint32_t first_spot = offset + entry.count[0];
			uint32_t point = first_point;
			uint32_t spot = first_spot;

//#ifndef USE_STD_BITSET
#if 0
			b.lights.for_each([&](uint32_t l) mutable
#else
			for(uint32_t l = 0; l < CONFIG_MAX_LIGHT_COUNT; ++l)
				if(b.lights[l])
#endif
			{
				// make sure to keep this code branch-less
				const bool isSpot = spot_lights[l];
				auto& i = isSpot ? spot : point;
				auto  s = isSpot ? first_spot : first_point;

				const uint32_t word = l / LIGHT_PER_GROUP;
				const uint32_t bit = l % LIGHT_PER_GROUP;
				uint32_t ll = (bit * GROUP_COUNT) | (word % GROUP_COUNT);
				assert(ll < num_lights);

				m_impl->m_records.m_data[i] = (RecordBufferType)ll;
				// we need to "cancel" the write if we have more than 255 spot or point lights
				// (this is a limitation of the data type used to store the light counts per froxel)
				i += (i - s < 255) ? 1 : 0;

//#ifndef USE_STD_BITSET
#if 0
			});
#else
			}
#endif

			offset += light_count;

			do {
				m_impl->m_froxels.m_data[remap(cluster++)].u32 = entry.u32;
				if(cluster >= num_clusters) break;

				if(m_impl->m_light_records[cluster].lights != b.lights && cluster >= m_frustum.m_subdiv_x)
				{
					// if this froxel record doesn't match the previous one on its left,
					// we re-try with the record above it, which saves many froxel records
					// (north of 10% in practice).
					b = m_impl->m_light_records[cluster - m_frustum.m_subdiv_x];
					entry.u32 = m_impl->m_froxels.m_data[remap(cluster - m_frustum.m_subdiv_x)].u32;
				}
			} while(m_impl->m_light_records[cluster].lights == b.lights);

			//printf("\niteration %i\n\n", i);
			//inspect();
		}

	out_of_memory:
		;
	}

	static inline vec2 project(mat4 const& p, vec3 const& v)
	{
		const float vx = v[0];
		const float vy = v[1];
		const float vz = v[2];

		// We know we're using a projection matrix (which has a bunch of zeros)
		// But we need to handle asymetric frustums and orthographic projections.
		//       orthographic ------------------------+
		//  asymmetric frustum ---------+             |
		//                              v             v
		const float x = p[0].x * vx + p[2].x * vz + p[3].x;
		const float y = p[1].y * vy + p[2].y * vz + p[3].y;
		const float w = p[2].w * vz + p[3].w;

		return vec2(x, y) * (1 / w);
	}

	inline float sphere_plane_distance2(const vec4& s, float px, float pz)
	{
		return sphere_plane_intersection(vec3(s), s.w, { px, 0.f, pz }, 0.f).w;
	}
	
	inline vec4 sphere_plane_intersection(const vec4& s, float py, float pz)
	{
		return sphere_plane_intersection(vec3(s), s.w, { 0.f, py, pz }, 0.f);
	}
	
	inline vec4 sphere_plane_intersection(const vec4& s, float pw)
	{
		return sphere_plane_intersection(vec3(s), s.w, { 0.f, 0.f, 1.f }, pw);
	}

	inline bool sphere_cone_intersection(const vec4& s, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		return sphere_cone_intersection_fast(vec3(s), s.w, cone_position, cone_axis, cone_sin_inverse, cone_cos_squared);
	}
	
	void light_bounds(ClusteredFrustum& frustum, const mat4& projection, float near, const LightParams& light, uvec3& lo, uvec3& hi)
	{
		// find a reasonable bounding-box in froxel space for the sphere by projecting
		// it's (clipped) bounding-box to clip-space and converting to froxel indices.
		Aabb aabb = { light.position, vec3(light.radius) };
		const float znear = bx::min(-near, aabb.m_center.z + aabb.m_extents.z); // z values are negative
		const float zfar = aabb.m_center.z - aabb.m_extents.z;

		vec2 xyLeftNear		= project(projection, { vec2(aabb.m_center) - vec2(aabb.m_extents), znear });
		vec2 xyLeftFar		= project(projection, { vec2(aabb.m_center) - vec2(aabb.m_extents), zfar });
		vec2 xyRightNear	= project(projection, { vec2(aabb.m_center) + vec2(aabb.m_extents), znear });
		vec2 xyRightFar		= project(projection, { vec2(aabb.m_center) + vec2(aabb.m_extents), zfar });

		// handle inverted frustums (e.g. x or y symetries)
		if(xyLeftNear.x > xyRightNear.x)   swap(xyLeftNear.x, xyRightNear.x);
		if(xyLeftNear.y > xyRightNear.y)   swap(xyLeftNear.y, xyRightNear.y);
		if(xyLeftFar.x  > xyRightFar.x)    swap(xyLeftFar.x, xyRightFar.x);
		if(xyLeftFar.y  > xyRightFar.y)    swap(xyLeftFar.y, xyRightFar.y);

		const auto imin = frustum.tile_index(min(xyLeftNear, xyLeftFar));
		lo = { imin.x, imin.y, frustum.slice(znear) };

		const auto imax = frustum.tile_index(max(xyRightNear, xyRightFar));
		hi = {
			imax.x + 1,   // x1 points to 1 past the last value (like end() does
			imax.y,      // y1 points to the last value
			frustum.slice(zfar)  // z1 points to the last value
		};
	}

	void froxelize_light(ClusteredFrustum& frustum, FroxelThreadData& froxelThread, uint32_t bit, const mat4& projection, float near, const LightParams& light, float light_far)
	{
		if(light.position.z + light.radius < -light_far) // [[unlikely]] // z values are negative
		{
			// This light is fully behind LightFar, it doesn't light anything
			// (we could avoid this check if we culled lights using LightFar instead of the
			// culling camera's far plane)
			return;
		}

		// the code below works with radius^2
		const vec4 s = { light.position, light.radius * light.radius };

		uvec3 lo, hi;
		light_bounds(frustum, projection, near, light, lo, hi);

		assert(lo.x < hi.x);
		assert(lo.y <= hi.y);
		assert(lo.z <= hi.z);

		const uint32_t zcenter = frustum.slice(s.z);

		for(uint32_t iz = lo.z; iz <= hi.z; ++iz)
		{
			vec4 cz(s);
			if(iz != zcenter) // [[unlikely]]
				cz = sphere_plane_intersection(s, (iz < zcenter) ? frustum.m_distances_z[iz + 1] : frustum.m_distances_z[iz]);

			// find x & y slices that contain the sphere's center
			// (note: this changes with the Z slices
			const vec2 clip = project(projection, vec3(cz));
			const auto center = frustum.tile_index(clip);

			if(cz.w > 0)
			{ // intersection of light with this plane (slice)
				for(uint32_t iy = lo.y; iy <= hi.y; ++iy)
				{
					vec4 cy(cz);
					if(iy != center.y) // [[unlikely]] 
					{
						vec4 const& plane = iy < center.y ? frustum.m_planes_y[iy + 1] : frustum.m_planes_y[iy];
						cy = sphere_plane_intersection(cz, plane.y, plane.z);
					}
					if(cy.w > 0)
					{ // intersection of light with this horizontal plane
						uint32_t bx, ex; // horizontal begin/end indices
										// find the begin index (left side)
						for(bx = lo.x; ++bx <= center.x;)
							if(sphere_plane_distance2(cy, frustum.m_planes_x[bx].x, frustum.m_planes_x[bx].z) > 0)
								break; // intersection

						// find the end index (right side), x1 is past the end
						for(ex = hi.x; --ex > center.x;)
							if(sphere_plane_distance2(cy, frustum.m_planes_x[ex].x, frustum.m_planes_x[ex].z) > 0)
								break; // intersection

						--bx;
						++ex;

						if(bx >= ex) // [[unlikely]]
							continue;

						assert(bx < frustum.m_subdiv_x && ex <= frustum.m_subdiv_x);

						// The first entry reserved for type of light, i.e. point/spot
						uint16_t fi = frustum.index(bx, iy, iz) + 1;
						if(light.invSin != std::numeric_limits<float>::infinity())
						{
							// This is a spotlight (common case)
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
							{
								// see if this froxel intersects the cone
								bool intersect = sphere_cone_intersection(frustum.m_bounding_spheres[fi - 1], light.position, light.axis, light.invSin, light.cosSqr);
								froxelThread[fi++] |= LightGroupType(intersect) << bit;
							}
						}
						else
						{
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
								froxelThread[fi++] |= LightGroupType(1) << bit;
						}
					}
				}
			}
		}
	}
}


#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <cstddef>
#include <cstdint>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

namespace mud
{
	inline Plane bounding_plane(const mat4& mat, Axis component, float dir)
	{
		return {
			mat[0][3] + dir * mat[0][size_t(component)],
			mat[1][3] + dir * mat[1][size_t(component)],
			mat[2][3] + dir * mat[2][size_t(component)],
			mat[3][3] + dir * mat[3][size_t(component)]
		};
	}

	Plane6 bounding_planes(const mat4& mat)
	{
		Plane6 planes;

		planes.m_right = bounding_plane(mat, Axis::X, -1.f);
		planes.m_left  = bounding_plane(mat, Axis::X,  1.f);

		planes.m_up    = bounding_plane(mat, Axis::Y, -1.f);
		planes.m_down  = bounding_plane(mat, Axis::Y,  1.f);

		planes.m_near  = bounding_plane(mat, Axis::Z, -1.f);
		planes.m_far   = bounding_plane(mat, Axis::Z,  1.f);

		for(size_t i = 0; i < 6; ++i)//Plane& plane : planes)
			planes[i] = normalize(Plane{ -planes[i].m_normal, planes[i].m_distance });

		return planes;
	}

	Plane6 frustum_planes(const mat4& projection, const mat4& transform)
	{
		return bounding_planes(projection * transform);
	}

	Plane6 frustum_planes(const mat4& view, float fov, float aspect, float near, float far)
	{
		mat4 projection = bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth);
		return frustum_planes(projection, view);
	}

	Plane6 frustum_planes(const mat4& view, const vec2& rect, float near, float far)
	{
		mat4 projection = bxortho(-rect.x / 2.f, rect.x / 2.f, -rect.y / 2.f, rect.y / 2.f, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth);
		return frustum_planes(projection, view);
	}

	Point8 frustum_corners(const Plane6& planes)
	{
		Point8 points;

		const Plane* corners[8][3] =
		{
			{ &planes.m_near,  &planes.m_left,  &planes.m_up   },
			{ &planes.m_near,  &planes.m_left,  &planes.m_down },
			{ &planes.m_near,  &planes.m_right, &planes.m_down },
			{ &planes.m_near,  &planes.m_right, &planes.m_up   },
			{ &planes.m_far,   &planes.m_left,  &planes.m_down },
			{ &planes.m_far,   &planes.m_left,  &planes.m_up   },
			{ &planes.m_far,   &planes.m_right, &planes.m_up   },
			{ &planes.m_far,   &planes.m_right, &planes.m_down },
		};

		for(uint i = 0; i < 8; i++)
			points[i] = plane_3_intersection(*corners[i][0], *corners[i][1], *corners[i][2]);

		return points;
	}

	Point8 frustum_corners(const mat4& projection, const mat4& transform)
	{
		Plane6 planes = frustum_planes(projection, transform);
		return frustum_corners(planes);
	}

	Point8 frustum_corners(float nw, float nh, float fw, float fh, float near, float far, const mat4& view)
	{
		Point8 corners =
		{
			{ -nw,  nh, -near },
			{ -nw, -nh, -near },
			{  nw, -nh, -near },
			{  nw,  nh, -near },
			{ -fw, -fh, -far },
			{ -fw,  fh, -far },
			{  fw,  fh, -far },
			{  fw, -fh, -far },
		};

		// Convert corners to world space.
		mat4 inverse_view = inverse(view);
		for(uint i = 0; i < 8; i++)
			corners[i] = bxmul(inverse_view, corners[i]);

		return corners;
	}

	Point8 frustum_corners(const vec2& size, float near, float far, const mat4& view)
	{
		return frustum_corners(size.x / 2.f, size.y / 2.f, size.x / 2.f, size.y / 2.f, near, far, view);
	}

	Point8 frustum_corners(float fov, float aspect, float near, float far, const mat4& view)
	{
		const float proj_height = bx::tan(bx::toRad(fov) * 0.5f);
		const float proj_width = proj_height * aspect;

		// Frustum corners in view space.
		const float nw = near * proj_width;
		const float nh = near * proj_height;
		const float fw = far  * proj_width;
		const float fh = far  * proj_height;

		return frustum_corners(nw, nh, fw, fh, near, far, view);
	}

	vec2 frustum_viewport_size(const mat4& projection)
	{
		Plane6 planes = bounding_planes(projection);
		vec3 intersection = plane_3_intersection(planes.m_near, planes.m_right, planes.m_up);
		return{ intersection.x, intersection.y };
	}

	Frustum::Frustum()
	{}

	Frustum::Frustum(const mat4& transform, float fov, float aspect, float near, float far)
		: m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
		, m_planes(frustum_planes(transform, fov, aspect, near, far))
		, m_corners(frustum_corners(fov, aspect, near, far, transform))
	{
		this->compute();
	}

	Frustum::Frustum(const mat4& transform, const vec2& rect, float near, float far)
		: m_near(near)
		, m_far(far)
		, m_planes(frustum_planes(transform, rect, near, far))
		, m_corners(frustum_corners(rect, near, far, transform))
	{
		this->compute();
	}

	void Frustum::compute()
	{
		m_center = Zero3;
		for(uint i = 0; i < 8; i++)
			m_center += m_corners[i];
		//m_center /= 8.f;
		m_center = m_center / 8.f;

		m_radius = 0.f;
		for(uint i = 0; i < 8; i++)
			m_radius = max(distance(m_center, m_corners[i]), m_radius);
	}

	Frustum optimized_frustum(Camera& camera, array<Item*> items)
	{
		if(!camera.m_optimize_ends)
			return Frustum{ camera.m_transform, camera.m_fov, camera.m_aspect, camera.m_near, camera.m_far };

		Plane near_plane = camera.near_plane();

		float z_max = -1e20f;
		float z_min = 1e20f;

		for(Item* item : items)
		{
			vec2 min_max = project_aabb_in_plane(near_plane, item->m_aabb);

			z_min = min(min_max.x, z_min);
			z_max = max(min_max.y, z_max);
		}

		float near = max(camera.m_near, z_min);
		float far = min(camera.m_far, z_max);

		return Frustum{ camera.m_transform, camera.m_fov, camera.m_aspect, near, far };
	}

	void split_frustum_slices(Camera& camera, array<FrustumSlice> slices, uint8_t num_splits, float near, float far, float split_distribution)
	{
		const float ratio = far / near;

		for(uint8_t i = 0; i < num_splits; ++i)
		{
			float si = float(int8_t(i * 2 + 1)) / float(num_splits * 2);

			const float split = split_distribution * (near * powf(ratio, si)) + (1 - split_distribution) * (near + (far - near) * si);
			const float slice_near = i == 0 ? near : slices[i - 1].m_frustum.m_far * 1.005f;
			const float slice_far = i == num_splits - 1 ? far : split;

			Frustum frustum;
			if(camera.m_orthographic)
			{
				vec2 rect = { camera.m_height * camera.m_aspect, camera.m_height };
				frustum = { camera.m_transform, rect, slice_near, slice_far };
			}
			else
			{
				frustum = { camera.m_transform, camera.m_fov, camera.m_aspect, slice_near, slice_far };
			}

			slices[i] = { i, frustum };
		}
	}

	void split_frustum_slices(Camera& camera, array<FrustumSlice> slices, uint8_t num_splits, float split_distribution)
	{
		split_frustum_slices(camera, slices, num_splits, camera.m_near, camera.m_far, split_distribution);
	}
}


#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/limits.h>
#include <stl/algorithm.h>
//#include <stl/type_traits.h>
#endif

//#include <type_traits>
//#include <limits>
#include <cstddef>
#include <cstdint>

namespace mud
{
	void compute_frustum_subdiv(ClusteredFrustum& frustum, vec2 clip_size, size_t slices)
	{
		// TODO: don't hardcode this
		frustum.m_subdiv_x = uint16_t(32);
		frustum.m_subdiv_y = uint16_t(16);
		if(clip_size.y > clip_size.x)
			swap(frustum.m_subdiv_x, frustum.m_subdiv_y);
		frustum.m_subdiv_z = uint16_t(slices);
		frustum.m_tile_size.x = (uint(clip_size.x) + frustum.m_subdiv_x - 1) / frustum.m_subdiv_x;
		frustum.m_tile_size.y = (uint(clip_size.y) + frustum.m_subdiv_y - 1) / frustum.m_subdiv_y;
	}

	void compute_frustum_subdiv_square(ClusteredFrustum& frustum, vec2 clip_size, size_t slices, size_t max_clusters)
	{
		// calculate froxel dimension from FROXEL_BUFFER_ENTRY_COUNT_MAX and viewport
		// - Start from the maximum number of froxels we can use in the x-y plane
		size_t per_slice = max_clusters / slices;
		// - compute the number of square froxels we need in width and height, rounded down
		//   solving: |  froxel_count_x * froxel_count_y == per_slice
		//            |  froxel_count_x / froxel_count_y == width / height
		size_t count_x = size_t(sqrt(per_slice * clip_size.x / clip_size.y));
		size_t count_y = size_t(sqrt(per_slice * clip_size.y / clip_size.x));
		// - copmute the froxels dimensions, rounded up
		size_t size_x = (size_t(clip_size.x) + count_x - 1) / count_x;
		size_t size_y = (size_t(clip_size.y) + count_y - 1) / count_y;
		// - and since our froxels must be square, only keep the largest dimension
		size_t size = max(size_x, size_y);

		// Here we recompute the froxel counts which may have changed a little due to the rounding
		// and the squareness requirement of froxels
		count_x = (size_t(clip_size.x) + size - 1) / size;
		count_y = (size_t(clip_size.y) + size - 1) / size;

		frustum.m_tile_size = uvec2(uint(size));
		frustum.m_subdiv_x = uint16_t(count_x);
		frustum.m_subdiv_y = uint16_t(count_y);
		frustum.m_subdiv_z = uint16_t(slices);
	}

	uvec2 ClusteredFrustum::tile_index(const vec2& clip) const
	{
		// clip coordinates between [-1, 1], conversion to index between [0, count[
		//  = floor((clip + 1) * ((0.5 * dimension) / froxelsize))
		//  = floor((clip + 1) * constant
		//  = floor(clip * constant + constant)
		const uint xi = uint(clamp(int(clip.x * m_clip_to_cluster.x + m_clip_to_cluster.x), 0, m_subdiv_x - 1));
		const uint yi = uint(clamp(int(clip.y * m_clip_to_cluster.y + m_clip_to_cluster.y), 0, m_subdiv_y - 1));
		return{ xi, yi };
	}

	uint ClusteredFrustum::slice(float z) const
	{
		// The vastly common case is that z<0, so we always do the math for this case
		// and we "undo" it below otherwise. This works because we're using fast::log2 which
		// doesn't care if given a negative number (we'd have to use abs() otherwise).

		// This whole function is now branch-less.

		int s = int((log2(-z) - m_far_log2) * m_linearizer + m_subdiv_z);

		// there are cases where z can be negative here, e.g.:
		// - the light is visible, but its center is behind the camera
		// - the camera's near is behind the camera (e.g. with shadowmap cameras)
		// in that case just return the first slice
		s = z < 0 ? s : 0;

		// clamp between [0, m_subdiv_z)
		return size_t(clamp(s, 0, m_subdiv_z - 1));
	}

	Plane to_plane(const vec4& p) { return{ vec3(p), p.w }; }

	Frustum ClusteredFrustum::cluster_frustum(uint x, uint y, uint z) const
	{
		assert(x < m_subdiv_x);
		assert(y < m_subdiv_y);
		assert(z < m_subdiv_z);
		Frustum froxel;
		froxel.m_planes.m_left = to_plane(m_planes_x[x]);
		froxel.m_planes.m_down = to_plane(m_planes_y[y]);
		froxel.m_planes.m_near = to_plane(vec4{ 0, 0, 1, -m_distances_z[z] });
		froxel.m_planes.m_right = to_plane(-m_planes_x[x + 1]);
		froxel.m_planes.m_up = to_plane(-m_planes_y[y + 1]);
		froxel.m_planes.m_far = to_plane(vec4{ 0, 0, 1, -m_distances_z[z + 1] });
		froxel.m_corners = frustum_corners(froxel.m_planes);
		froxel.compute();
		return froxel;
	}

	void ClusteredFrustum::resize(const vec2& clip_size)
	{
		//compute_frustum_subdiv(*this, clip_size);
		compute_frustum_subdiv_square(*this, clip_size);

		m_distances_z.resize(m_subdiv_z + 1);
		m_planes_x.resize(m_subdiv_x + 1);
		m_planes_y.resize(m_subdiv_y + 1);

		m_cluster_count = uint16_t(m_subdiv_x * m_subdiv_y * m_subdiv_z);
		m_bounding_spheres.resize(m_cluster_count);

		m_clip_to_cluster = (0.5f * vec2(clip_size)) / vec2(m_tile_size);
		m_inv_tile_size = 1.0f / vec2(m_tile_size);

		const float linearizer = log2(m_far / m_near) / float(m_subdiv_z - 1);

		m_distances_z[0] = 0.0f;

		for(int i = 1, n = m_subdiv_z; i <= n; i++)
			m_distances_z[i] = m_far * exp2f(float(i - n) * linearizer);

		// for the inverse-transformation (view-space z to z-slice)
		m_linearizer = 1 / linearizer;
		m_far_log2 = log2(m_far);
	}

	void ClusteredFrustum::recompute(const mat4& projection, const vec2& clip_size)
	{
		// clip-space dimensions
		const vec2 froxel_clip_size = (2.0f * vec2(m_tile_size)) / clip_size;
		const mat4 inv_projection = inverse(projection);
		
		auto to_view_space = [](const mat4& inv_projection, vec4 p0, vec4 p1)
		{
			p0 = inv_projection * p0;
			p1 = inv_projection * p1;
			return vec4(normalize(cross(vec3(p1), vec3(p0))), 0.f);
		};

		for(uint16_t i = 0, n = m_subdiv_x; i <= n; ++i)
		{
			float x = (i * froxel_clip_size.x) - 1.0f;
			vec4 p0 = { x, -1, -1, 1 };
			vec4 p1 = { x,  1, -1, 1 };
			m_planes_x[i] = to_view_space(inv_projection, p0, p1);
		}

		for(uint16_t i = 0, n = m_subdiv_y; i <= n; ++i)
		{
			float y = (i * froxel_clip_size.y) - 1.0f;
			vec4 p0 = { -1, y, -1, 1 };
			vec4 p1 = {  1, y, -1, 1 };
			m_planes_y[i] = to_view_space(inv_projection, p0, p1);
		}

		// 3-planes intersection:
		//      -d0.(n1 x n2) - d1.(n2 x n0) - d2.(n0 x n1)
		// P = ---------------------------------------------
		//                      n0.(n1 x n2)

		// use stack memory here, it's only 16 KiB max
		assert(m_subdiv_x <= 2048);
		typename std::aligned_storage<sizeof(vec2), alignof(vec2)>::type stack[2048];
		vec2* const minMaxX = reinterpret_cast<vec2*>(stack);

		for(uint iz = 0, fi = 0, nz = m_subdiv_z; iz < nz; ++iz)
		{
			vec4 planes[6];
			vec3 minp;
			vec3 maxp;

			// near/far planes for all froxels at iz
			planes[4] = vec4{ 0, 0, 1, m_distances_z[iz + 0] };
			planes[5] = -vec4{ 0, 0, 1, m_distances_z[iz + 1] };

			// min/max for z is calculated trivially because near/far planes are parallel to
			// the camera.
			minp.z = -m_distances_z[iz + 1];
			maxp.z = -m_distances_z[iz];
			assert(minp.z < maxp.z);

			for(uint16_t ix = 0; ix < m_subdiv_x; ++ix)
			{
				// left, right planes for all froxels at ix
				planes[0] = m_planes_x[ix];
				planes[1] = -m_planes_x[ix + 1];
				minp.x = limits<float>::max();
				maxp.x = limits<float>::min();
				// min/max for x is calculated by intersecting the near/far and left/right planes
				for(uint16_t c = 0; c < 4; ++c)
				{
					vec4 const& p0 = planes[0 + (c & 1)];     // {x,0,z,0}
					vec4 const& p2 = planes[4 + (c >> 1)];    // {0,0,+/-1,d}
					float px = (p2.z * p2.w * p0.z) / p0.x;
					minp.x = min(minp.x, px);
					maxp.x = max(maxp.x, px);
				}
				assert(minp.x < maxp.x);
				minMaxX[ix] = vec2{ minp.x, maxp.x };
			}

			for(uint16_t iy = 0; iy < m_subdiv_y; ++iy)
			{
				// bottom, top planes for all froxels at iy
				planes[2] = m_planes_y[iy];
				planes[3] = -m_planes_y[iy + 1];
				minp.y = limits<float>::max();
				maxp.y = limits<float>::min();
				// min/max for y is calculated by intersecting the near/far and bottom/top planes
				for(uint16_t c = 0; c < 4; ++c)
				{
					vec4 const& p1 = planes[2 + (c & 1)];     // {0,y,z,0}
					vec4 const& p2 = planes[4 + (c >> 1)];    // {0,0,+/-1,d}
					float py = (p2.z * p2.w * p1.z) / p1.y;
					minp.y = min(minp.y, py);
					maxp.y = max(maxp.y, py);
				}
				assert(minp.y < maxp.y);

				for(uint16_t ix = 0, nx = m_subdiv_x; ix < nx; ++ix)
				{
					// note: clang vectorizes this loop!
					assert(this->index(ix, iy, iz) == fi);
					minp.x = minMaxX[ix][0];
					maxp.x = minMaxX[ix][1];
					m_bounding_spheres[fi++] = { (maxp + minp) * 0.5f, length((maxp - minp) * 0.5f) };
				}
			}
		}
	}
}


#include <bx/timer.h>
#include <bx/file.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/string.h>
#include <stl/map.h>
#endif

#include <Tracy.hpp>

//#define MUD_GFX_THREADED

namespace mud
{
	GfxContext::GfxContext(GfxSystem& gfx_system, const string& name, int width, int height, bool fullScreen, bool init)
		: BgfxContext(gfx_system, name, width, height, fullScreen, false)
		, m_gfx_system(gfx_system)
		, m_target()
	{
		if(init)
			gfx_system.init(*this);
		m_target = make_object<RenderTarget>(uvec2(width, height));
	}

	GfxContext::~GfxContext()
	{}

	void GfxContext::reset(uint16_t width, uint16_t height)
	{
		bgfx::reset(width, height, BGFX_RESET_NONE);
		if(width == 0 || height == 0)
			m_target = nullptr;
		else
		{
			if(!m_target || width != m_target->m_size.x || height != m_target->m_size.y)
				m_target = make_object<RenderTarget>(uvec2(width, height));
		}
		m_vg_handle = m_reset_vg(*this, *m_gfx_system.m_vg);
	}

	struct GfxSystem::Impl
	{
		vector<string> m_resource_paths;

		vector<GfxContext*> m_contexts;
		vector<Scene*> m_scenes;

		bx::FileReader m_file_reader;
		bx::FileWriter m_file_writer;

		unique<TPool<Mesh>> m_meshes;
		unique<TPool<Rig>> m_rigs;
		unique<TPool<Animation>> m_animations;

		unique<AssetStore<Texture>> m_textures;
		unique<AssetStore<Program>> m_programs;
		unique<AssetStore<Material>> m_materials;
		unique<AssetStore<Model>> m_models;
		unique<AssetStore<ParticleFlow>> m_particles;
		unique<AssetStore<Prefab>> m_prefabs;

		vector<Importer*> m_importers;

		vector<Renderer*> m_renderers;

		Texture* m_white_texture = nullptr;
		Texture* m_black_texture = nullptr;
		Texture* m_normal_texture = nullptr;

		SymbolIndex m_symbols;

#ifdef MUD_GFX_THREADED
		vector<bgfx::Encoder*> m_encoders;
#endif
	};

	GfxSystem::GfxSystem(const string& resource_path)
		: BgfxSystem(resource_path)
		, m_impl(make_unique<Impl>())
		, m_pipeline(make_unique<Pipeline>(*this))
	{
		Program::ms_gfx_system = this;
		Material::ms_gfx_system = this;
		Model::ms_gfx_system = this;

		this->add_resource_path(resource_path, false);
	}

	GfxSystem::~GfxSystem()
	{}

	bx::FileReaderI& GfxSystem::file_reader() { return m_impl->m_file_reader; }
	bx::FileWriterI& GfxSystem::file_writer() { return m_impl->m_file_writer; }

	TPool<Mesh>& GfxSystem::meshes() { return *m_impl->m_meshes; }
	TPool<Rig>& GfxSystem::rigs() { return *m_impl->m_rigs; }
	TPool<Animation>& GfxSystem::animations() { return *m_impl->m_animations; }

	AssetStore<Texture>& GfxSystem::textures() { return *m_impl->m_textures; }
	AssetStore<Program>& GfxSystem::programs() { return *m_impl->m_programs; }
	AssetStore<Material>& GfxSystem::materials() { return *m_impl->m_materials; }
	AssetStore<Model>& GfxSystem::models() { return *m_impl->m_models; }
	AssetStore<ParticleFlow>& GfxSystem::particles() { return *m_impl->m_particles; }
	AssetStore<Prefab>& GfxSystem::prefabs() { return *m_impl->m_prefabs; }

	void GfxSystem::add_importer(ModelFormat format, Importer& importer)
	{
		m_impl->m_importers[size_t(format)] = &importer;
	}

	Importer* GfxSystem::importer(ModelFormat format)
	{
		return m_impl->m_importers[size_t(format)];
	}

	object<Context> GfxSystem::create_context(const string& name, int width, int height, bool fullScreen)
	{
		object<GfxContext> context = make_object<GfxContext>(*this, name, width, height, fullScreen, !m_initialized);
		m_impl->m_contexts.push_back(context.get());
		return move(context);
	}

	void GfxSystem::init(GfxContext& context)
	{
		BgfxSystem::init(context);

		m_impl->m_meshes = make_unique<TPool<Mesh>>();
		m_impl->m_rigs = make_unique<TPool<Rig>>();
		m_impl->m_animations = make_unique<TPool<Animation>>();
		//std::function<T>();
		m_impl->m_textures = make_unique<AssetStore<Texture>>(*this, "textures/", [&](Texture& texture, const string& path) { load_texture(*this, texture, path); });
		m_impl->m_programs = make_unique<AssetStore<Program>>(*this, "programs/", ".prg");
		m_impl->m_materials = make_unique<AssetStore<Material>>(*this, "materials/", ".mtl");
		m_impl->m_models = make_unique<AssetStore<Model>>(*this, "models/");
		m_impl->m_particles = make_unique<AssetStore<ParticleFlow>>(*this, "particles/", ".ptc");
		//m_impl->m_prefabs = make_unique<AssetStore<Prefab>>(*this, "prefabs/", ".pfb");
		m_impl->m_prefabs = make_unique<AssetStore<Prefab>>(*this, "models/");

		m_impl->m_renderers.resize(size_t(Shading::Count));
		m_impl->m_importers.resize(size_t(ModelFormat::Count));

		m_impl->m_white_texture = this->textures().file("white.png");
		m_impl->m_black_texture = this->textures().file("black.png");
		m_impl->m_normal_texture = this->textures().file("normal.png");

		m_pipeline = make_unique<Pipeline>(*this);
	}

	void GfxSystem::default_pipeline()
	{
		this->init_pipeline(pipeline_minimal);
	}

	void GfxSystem::init_pipeline(PipelineDecl decl)
	{
#ifdef MUD_GFX_DEFERRED
		decl(*this, *m_pipeline, true);
#else
		decl(*this, *m_pipeline, false);
#endif

		for(auto& block : m_pipeline->m_gfx_blocks)
			block->init_block();

		static ClearRenderer clear_renderer = { *this, *m_pipeline };
		static UnshadedRenderer unshaded_renderer = { *this, *m_pipeline };
		static MinimalRenderer minimal_renderer = { *this, *m_pipeline };
		UNUSED(minimal_renderer);

		this->set_renderer(Shading::Unshaded, unshaded_renderer);
		this->set_renderer(Shading::Clear, clear_renderer);

		this->create_debug_materials();
	}

	void GfxSystem::add_resource_path(const string& path, bool relative)
	{
		printf("INFO: resource path: %s\n", path.c_str());
		m_impl->m_resource_paths.push_back(relative ? m_resource_path + "/" + path : path);
	}

	void GfxSystem::set_renderer(Shading shading, Renderer& renderer)
	{
		m_impl->m_renderers[size_t(shading)] = &renderer;
	}

	Renderer& GfxSystem::renderer(Shading shading)
	{
		return *m_impl->m_renderers[size_t(shading)];
	}

	GfxContext& GfxSystem::context(size_t index)
	{
		return *m_impl->m_contexts[index];
	}

	void GfxSystem::begin_frame()
	{
		RenderFrame frame = { m_frame, m_time, m_delta_time, Render::s_render_pass_id };

		{
			ZoneScopedNC("programs", tracy::Color::Cyan);

			for(auto& name_program : m_impl->m_programs->m_assets)
				name_program.second->update(*this);
		}

		{
			ZoneScopedNC("renderers", tracy::Color::Cyan);

			for(auto& block : m_pipeline->m_gfx_blocks)
				block->begin_frame(frame);
		}
	}

	bool GfxSystem::next_frame()
	{
		RenderFrame frame = { m_frame, m_time, m_delta_time, Render::s_render_pass_id };

#ifdef MUD_GFX_THREADED
		{
			ZoneScopedNC("gfx begin", tracy::Color::Cyan);

			m_num_encoders = min(uint32_t(4U), bgfx::getCaps()->limits.maxEncoders);

			m_encoders[0] = bgfx::begin();
			for(size_t i = 1; i < m_num_encoders; ++i)
				m_encoders[i] = bgfx::begin(true);
		}
#endif

		for(GfxContext* context : m_impl->m_contexts)
			for(Viewport* viewport : context->m_viewports)
				if(viewport->m_active)
				{
					ZoneScopedNC("gfx viewport", tracy::Color::Cyan);

					Renderer& renderer = this->renderer(viewport->m_shading);
					this->render(renderer, *context, *viewport, frame);
				}

#ifdef MUD_GFX_THREADED
		{
			ZoneScopedNC("gfx end", tracy::Color::Cyan);

			for(size_t i = 1; i < m_num_encoders; ++i)
				bgfx::end(m_encoders[i]);
		}
#endif

		bool pursue = true;
		{
			ZoneScopedNC("gfx contexts", tracy::Color::Cyan);

			for(GfxContext* context : m_impl->m_contexts)
				pursue &= context->next_frame();
		}

		{
			ZoneScopedNC("gfx frame", tracy::Color::Cyan);
			BgfxSystem::next_frame();
		}

		return pursue;
	}

	void GfxSystem::render(Renderer& renderer, GfxContext& context, Viewport& viewport, RenderFrame& frame)
	{
		Render render = { renderer.m_shading, viewport, *context.m_target, frame };
		renderer.gather(render);
		render.m_viewport.render(render);
		render.m_viewport.cull(render);

#ifdef DEBUG_ITEMS
		scene.debug_items(render);
#endif

		if(rect_w(viewport.m_rect) != 0 && rect_h(viewport.m_rect) != 0)
			renderer.render(render);

		//copy.debug_show_texture(render, render.m_environment->m_radiance.m_texture->m_texture, vec4(0.f), false, false, false, 0);
		//copy.debug_show_texture(render, render.m_environment->m_radiance.m_roughness_array, vec4(0.f), false, false, false, 1);
		//copy.debug_show_texture(render, bgfx::getTexture(render.m_target->m_effects.last()), vec4(0.f));
	}

	RenderFrame GfxSystem::render_frame()
	{
		return { m_frame, m_time, m_delta_time, Render::s_render_pass_id };
	}

	LocatedFile GfxSystem::locate_file(const string& file, array<string> extensions)
	{
		for(const string& path : m_impl->m_resource_paths)
			for(size_t i = 0; i < extensions.size(); ++i)
			{
				string filepath = path + "/" + file + extensions[i];
				if(file_exists(filepath))
				{
					return { path, file, extensions[i], i };
				}
			}
		return {};
	}

	LocatedFile GfxSystem::locate_file(const string& file)
	{
		carray<string, 1> exts = { "" };
		return this->locate_file(file, exts);
	}

	Texture& GfxSystem::default_texture(TextureHint hint)
	{
		if(hint == TextureHint::Black)
			return *m_impl->m_black_texture;
		else if(hint == TextureHint::White)
			return *m_impl->m_white_texture;
		else //if(hint == TextureHint::Normal)
			return *m_impl->m_normal_texture;
	}

	void GfxSystem::create_debug_materials()
	{
		Material& debug = this->fetch_material("debug", "unshaded");
		debug.m_unshaded_block.m_enabled = true;

		Material& alpha = this->fetch_material("debug_alpha", "unshaded");
		alpha.m_unshaded_block.m_enabled = true;
		alpha.m_unshaded_block.m_colour = Colour{ 0.2f, 0.2f, 0.2f, 0.1f };

		Material& pbr = this->fetch_material("debug_pbr", "pbr/pbr");
		pbr.m_pbr_block.m_enabled = true;
	}

	Material& GfxSystem::debug_material()
	{
		return *this->materials().get("debug_pbr");
	}

	Material& GfxSystem::fetch_material(const string& name, const string& shader, bool builtin)
	{
		Program* program = this->programs().file(shader);
		Material& material = this->materials().fetch(name);
		material.m_builtin = builtin;
		material.m_program = program;
		return material;
	}

	Material& GfxSystem::fetch_image256_material(const Image256& image)
	{
		string name = "Image256_" + to_string((uintptr_t)&image);
		Material* material = this->materials().get(name);

		if(!material)
		{
			string image_name = "Image256_" + to_string((uintptr_t)&image);
			auto initializer = [&](Texture& texture) { auto data = image.read(); load_texture_rgba(texture, image.m_width, image.m_height, data); };

			Texture& texture = this->textures().fetch(image_name);
			initializer(texture);
			material = &this->fetch_material(name, "unshaded");
			material->m_unshaded_block.m_enabled = true;
			material->m_unshaded_block.m_colour.m_texture = &texture;
		}

		return *material;
	}

	Model& GfxSystem::fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		return m_impl->m_symbols.symbol_model(symbol, shape, draw_mode);
	}

	Material& GfxSystem::fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		if(symbol.m_image256)
			return this->fetch_image256_material(*symbol.m_image256);
		else
			return m_impl->m_symbols.symbol_material(*this, symbol, draw_mode);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <cstdio>

namespace mud
{
	Gnode::Gnode() : Graph() {}
	Gnode::Gnode(Scene& scene, SoundManager* sound_manager) : Graph(), m_scene(&scene), m_attach(&scene.m_root_node), m_sound_manager(sound_manager) {}
	Gnode::Gnode(Gnode* parent, void* identity) : Graph(parent, identity), m_scene(parent->m_scene), m_attach(parent->m_attach), m_sound_manager(parent->m_sound_manager) {}

	Gnode::~Gnode()
	{
		this->clear();
	}

	void Gnode::clear()
	{
		m_nodes.clear();
		if(m_node)
		{
			m_scene->m_pool->pool<Node3>().tdestroy(*m_node);
			m_node = nullptr;
		}
		if(m_item)
		{
			m_scene->m_pool->pool<Item>().tdestroy(*m_item);
			m_item = nullptr;
		}
		if(m_animated)
		{
			m_scene->m_pool->pool<Animated>().tdestroy(*m_animated);
			m_animated = nullptr;
		}
		if(m_particles)
		{
			m_scene->m_pool->pool<Particles>().tdestroy(*m_particles);
			m_particles = nullptr;
		}
		if(m_light)
		{
			m_scene->m_pool->pool<Light>().tdestroy(*m_light);
			m_light = nullptr;
		}

		if(m_sound)
		{
			m_scene->m_orphan_sounds.push_back(m_sound);
			m_sound = nullptr;
			printf("ERROR: sound goes out of graph but wasn't destroyed\n");
		}
	}

	void debug_tree(Gnode& node, size_t index, size_t depth)
	{
		auto print_depth = [](size_t depth) { for(size_t i = 0; i < depth; ++i) printf("    "); };
		print_depth(depth);
		printf("node %i\n", int(index));
		if(node.m_item)
		{
			print_depth(depth + 1);
			printf("item %s\n", node.m_item->m_model->m_name.c_str());
		}
		for(size_t i = 0; i < node.m_nodes.size(); ++i)
			debug_tree(*node.m_nodes[i], i, depth + 1);
	}

	template <class T_Element, class... T_Args>
	inline T_Element& create(Scene& scene, T_Args&&... args)
	{
		return scene.m_pool->pool<T_Element>().construct(static_cast<T_Args&&>(args)...);
	}

namespace gfx
{
	Gnode& node(Gnode& parent, Ref object, const mat4& transform)
	{
		Gnode& self = parent.subi(object.m_value);
		if(!self.m_node)
		{
			self.m_node = &create<Node3>(*parent.m_scene, parent.m_scene, object);
			self.m_attach = self.m_node;
		}
		self.m_node->m_transform = transform;
		return self;
	}

	Gnode& node(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, object, bxTRS(scale, rotation, position));
	}

	Gnode& node(Gnode& parent, Ref object, const Transform& transform)
	{
		return node(parent, object, transform.m_position, transform.m_rotation, transform.m_scale);
	}

	Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, object, parent.m_attach->m_transform * bxTRS(scale, rotation, position));
	}

	Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation)
	{
		return node(parent, object, parent.m_attach->m_transform * bxTRS(Unit3, rotation, position));
	}

	void update_item_aabb(Item& item)
	{
		if(item.m_instances.size() == 0)
		{
			item.m_aabb = transform_aabb(item.m_model->m_aabb, item.m_node->m_transform);
		}
		else
		{
			item.m_aabb = {};
			for(const mat4& transform : item.m_instances)
				item.m_aabb.mergeSafe(transform_aabb(item.m_model->m_aabb, transform));
		}
	}

	void update_item_lights(Item& item)
	{
		item.m_lights.clear();

		item.m_node->m_scene->m_pool->pool<Light>().iterate([&](Light& light)
		{
			if(light.m_type == LightType::Direct || sphere_aabb_intersection(light.m_node.position(), light.m_range, item.m_aabb))
				item.m_lights.push_back(&light);
		});
	}

	Item& item(Gnode& parent, const Model& model, uint32_t flags, Material* material, size_t instances, array<mat4> transforms)
	{
		Gnode& self = parent.suba<Gnode>();
		bool update = (flags & ItemFlag::NoUpdate) == 0;
		if(!self.m_item)
		{
			self.m_item = &create<Item>(*self.m_scene, *self.m_attach, model, flags, material, instances);
			update = true;
		}
		self.m_item->m_model = const_cast<Model*>(&model);
		self.m_item->m_material = material;
		if(transforms.size() > 0)
		{
			self.m_item->m_instances.resize(instances);
			copy<mat4>(self.m_item->m_instances, transforms);
		}
		if(instances > 0)
		{
			self.m_item->m_instances.resize(instances);
			self.m_item->update_instances();
		}
		if(update)
		{
			update_item_aabb(*self.m_item);
			update_item_lights(*self.m_item);
		}
		return *self.m_item;
	}

	void prefab(Gnode& parent, const Prefab& prefab, bool transform, uint32_t flags, Material* material, size_t instances, array<mat4> transforms)
	{
		Gnode& self = parent.suba<Gnode>();
		
		for(size_t i = 0; i < prefab.m_items.size(); ++i)
		{
			mat4 tr = transform ? parent.m_attach->m_transform * prefab.m_nodes[i].m_transform
								: prefab.m_nodes[i].m_transform;
			Gnode& no = node(self, {}, tr);
			Item& it = item(no, *prefab.m_items[i].m_model, prefab.m_items[i].m_flags | flags, material, instances, transforms);
			//it = prefab.m_items[i];
			//shape(self, Cube(i.m_aabb.m_center, vec3(0.1f)), Symbol::wire(Colour::Red, true));
			//shape(self, submodel->m_aabb, Symbol::wire(Colour::White));
			UNUSED(it);
		}
	}

	Item& shape_item(Gnode& parent, Model& model, const Symbol& symbol, uint32_t flags, Material* material, size_t instances, DrawMode draw_mode)
	{
		Item& self = item(parent, model, flags, material, instances);
		self.m_material = material ? material : &parent.m_scene->m_gfx_system.fetch_symbol_material(symbol, draw_mode);
		return self;
	}

	Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags, Material* material, size_t instances)
	{
		Item* item = nullptr;
		Symbol white = { Colour::White, Colour::White };
		if(symbol.fill())
			item = &shape_item(parent, parent.m_scene->m_gfx_system.fetch_symbol(white, shape, PLAIN), symbol, flags, material, instances, PLAIN);
		if(symbol.outline())
			item = &shape_item(parent, parent.m_scene->m_gfx_system.fetch_symbol(white, shape, OUTLINE), symbol, flags, material, instances, OUTLINE);
		return *item;
	}

	void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		UNUSED(flags);
		if(symbol.fill())
			scene.m_immediate->draw(transform, { symbol, &shape, PLAIN });
		if(symbol.outline())
			scene.m_immediate->draw(transform, { symbol, &shape, OUTLINE });
	}

	void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		draw(*parent.m_scene, parent.m_attach->m_transform, shape, symbol, flags);
	}

	Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags, Material* material, size_t instances)
	{
		return shape(parent, Quad(size), { image }, flags, material, instances);
	}

	Item* model(Gnode& parent, const string& name, uint32_t flags, Material* material, size_t instances)
	{
		Model* model = parent.m_scene->m_gfx_system.models().file(name.c_str());
		if(model)
			return &item(parent, *model, flags, material, instances);
		return nullptr;
	}

	Animated& animated(Gnode& parent, Item& item)
	{
		Gnode& self = parent.suba();
		if(!self.m_animated)
		{
			self.m_animated = &create<Animated>(*self.m_scene, *self.m_attach);
			self.m_animated->add_item(item);
		}
		return *self.m_animated;
	}

	Particles& particles(Gnode& parent, const ParticleFlow& emitter, uint32_t flags, size_t instances)
	{
		UNUSED(flags); UNUSED(instances);
		Gnode& self = parent.suba();
		if(!self.m_particles)
			self.m_particles = &create<Particles>(*self.m_scene, self.m_attach, Sphere(1.f), 1024);
		as<ParticleFlow>(*self.m_particles) = emitter;
		self.m_particles->m_node = self.m_attach;
		self.m_particles->m_sprite = &parent.m_scene->m_particle_system->m_block.m_sprites.find_sprite(emitter.m_sprite_name.c_str());
		return *self.m_particles;
	}

	Light& light(Gnode& parent, LightType light_type, bool shadows, Colour colour, float range, float attenuation)
	{
		Gnode& self = parent.suba();
		if(!self.m_light)
		{
			self.m_light = &create<Light>(*self.m_scene, *self.m_attach, light_type, shadows);
		}
		self.m_light->m_type = light_type;
		self.m_light->m_colour = colour;
		self.m_light->m_range = range;
		self.m_light->m_attenuation = attenuation;
		return *self.m_light;
	}

	Light& direct_light_node(Gnode& parent, const quat& rotation)
	{
		Gnode& self = node(parent, {}, Zero3, rotation);
		Light& l = light(self, LightType::Direct, true, Colour{ 0.8f, 0.8f, 0.7f }, 1.f);
		l.m_energy = 0.6f;
		l.m_shadow_flags = CSM_Stabilize;
#ifdef MUD_PLATFORM_EMSCRIPTEN
		l.m_shadow_num_splits = 2;
#else
		l.m_shadow_num_splits = 4;
#endif
		return l;
	}

	Light& sun_light(Gnode& parent, float azimuth, float elevation)
	{
		return direct_light_node(parent, sun_rotation(azimuth, elevation));
	}

	quat facing(const vec3& direction)
	{
		float angle = atan2(direction.x, direction.z);
		return { cosf(angle / 2.f), 0.f, 1.f * sinf(angle / 2.f), 0.f };
	}

	Light& direct_light_node(Gnode& parent, const vec3& direction)
	{
		return direct_light_node(parent, facing(direction));
	}

	Light& direct_light_node(Gnode& parent)
	{
		return direct_light_node(parent, quat(vec3(-c_pi / 4.f, -c_pi / 4.f, 0.f)));
	}

	void radiance(Gnode& parent, const string& texture, BackgroundMode background)
	{
		parent.m_scene->m_environment.m_radiance.m_texture = parent.m_scene->m_gfx_system.textures().file(texture.c_str());
		parent.m_scene->m_environment.m_background.m_mode = background;
	}

	void custom_sky(Gnode& parent, CustomSky renderer)
	{
		parent.m_scene->m_environment.m_background.m_custom_function = renderer;
		parent.m_scene->m_environment.m_background.m_mode = BackgroundMode::Custom;
	}

	void manual_job(Gnode& parent, PassType pass, ManualJob job)
	{
		parent.m_scene->m_pass_jobs->m_jobs[size_t(pass)].push_back(job);
	}

	Material& pbr_material(GfxSystem& gfx_system, cstring name, const PbrMaterialBlock& pbr_block)
	{
		Program& program = *gfx_system.programs().file("pbr/pbr");
		Material& material = gfx_system.materials().fetch(name);
		material.m_program = &program;
		material.m_pbr_block = pbr_block;
		return material;
	}

	Material& pbr_material(GfxSystem& gfx_system, cstring name, const Colour& albedo, float metallic, float roughness)
	{
		return pbr_material(gfx_system, name, { albedo, metallic, roughness });
	}
}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
//#include <srlz/Serial.h>
#endif

namespace mud
{
	Import::Import(GfxSystem& gfx_system, const string& filepath, const ImportConfig& config)
		: m_gfx_system(gfx_system),m_config(config)
	{
		m_path = file_directory(filepath);
		m_file = file_name(filepath);
	}

	bool ImportConfig::filter_element(const string& name) const
	{
		for(const string& filter : m_exclude_elements)
			if(name.find(filter) != string::npos)
			{
				return true;
			}

		for(const string& filter : m_include_elements)
			if(name.find(filter) == string::npos)
			{
				return true;
			}

		return false;
	}

	bool ImportConfig::filter_material(const string& name) const
	{
		for(const string& filter : m_exclude_materials)
			if(name.find(filter) != string::npos)
			{
				return true;
			}

		for(const string& filter : m_include_materials)
			if(name.find(filter) == string::npos)
			{
				return true;
			}

		return false;
	}

	void import_to_prefab(GfxSystem& gfx_system, Prefab& prefab, Import& state, uint32_t flags)
	{
		UNUSED(gfx_system);
		prefab.m_nodes.reserve(state.m_items.size());
		prefab.m_items.reserve(state.m_items.size());

		prefab.m_aabb = {};

		for(Import::Item& item : state.m_items)
		{
			Model& model = *item.model;
			prefab.m_nodes.push_back({ item.transform });
			prefab.m_items.push_back({ prefab.m_nodes.back(), model, ItemFlag::Default | flags });

			// special hack for occluders
			if(model.m_items[0].m_mesh->m_material && model.m_items[0].m_mesh->m_material->m_name == "occluder")
				prefab.m_items.back().m_flags = ItemFlag::Occluder;

			prefab.m_aabb.mergeSafe(transform_aabb(model.m_aabb, item.transform));
		}
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#include <bgfx/bgfx.h>
#include <bx/math.h>

#endif

#include <algorithm>

namespace mud
{
	Item::Item(Node3& node, const Model& model, uint32_t flags, Material* material, size_t instances)
		: m_node(&node)
		, m_model(const_cast<Model*>(&model))
		, m_flags(flags)
		, m_material(material)
		, m_instances(instances)
	{
		if(flags == 0)
			m_flags = ItemFlag::Default;
		if((flags & ItemFlag::LodAll) == 0)
			m_flags |= ItemFlag::LodAll;
	}

	Item::~Item()
	{}

	void Item::update()
	{
		//if(!m_instances.empty())
		//	this->update_instances();
	}

	void Item::update_instances()
	{
		m_instance_buffers.resize(m_model->m_items.size());

		for(const ModelItem& item : m_model->m_items)
		{
			bgfx::InstanceDataBuffer& buffer = m_instance_buffers[item.m_index];
			uint32_t num = bgfx::getAvailInstanceDataBuffer(uint32_t(m_instances.size()), sizeof(mat4));
			if(num == 0)
				return;
			bgfx::allocInstanceDataBuffer(&buffer, num, sizeof(mat4));

			mat4* mat = (mat4*)buffer.data;

			if(item.m_has_transform)
			{
				for(uint32_t i = 0; i < buffer.num; ++i)
					*mat++ = m_instances[i] * item.m_transform;
			}
			else
			{
				std::copy(m_instances.begin(), m_instances.end(), mat);
			}
		}
	}

	void Item::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelItem& item) const
	{
		bgfx_state |= item.m_mesh->submit(encoder);

		mat4 transform = m_node->m_transform * item.m_transform;
		encoder.setTransform(value_ptr(transform));

		if(!m_instances.empty())
			encoder.setInstanceDataBuffer(&m_instance_buffers[item.m_index]);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	Light::Light(Node3& node, LightType type, bool shadows)
		: m_node(node)
		, m_type(type)
		, m_shadows(shadows)
	{
		m_shadow_bias = 0.1f;
		m_shadow_normal_bias = 0.f; // @todo investigate why making this higher fucks up the first shadow slice

		if(type != LightType::Spot)
			m_spot_angle = 0.f;
	}

	Light::~Light()
	{}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	ManualRender::ManualRender(Render& render, Shading shading, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect)
		: m_render(render)
		, m_camera()
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_sub_render(shading, m_viewport, fbo, render.m_frame)
	{
		m_sub_render.m_shot->m_lights = m_render.m_shot->m_lights;
	}

	ManualRender::ManualRender(Render& render, Shading shading, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection, bool ortho)
		: m_render(render)
		, m_camera(transform, projection, ortho)
		, m_viewport(m_camera, render.m_scene, viewport_rect)
		, m_sub_render(shading, m_viewport, fbo, render.m_frame)
	{
		m_sub_render.m_shot->m_lights = m_render.m_shot->m_lights;
	}

	void ManualRender::render(Renderer& renderer)
	{
		renderer.render(m_sub_render);
		m_render.m_pass_index = m_sub_render.m_pass_index;
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
//#include <gfx-pbr/VoxelGI.h>
//#include <gfx-pbr/Lightmap.h>
#endif

namespace mud
{
	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state)
	{
		if(blend_mode == BlendMode::Mix)
			bgfx_state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
		else if(blend_mode == BlendMode::Add)
			//bgfx_state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_ONE);
			bgfx_state |= BGFX_STATE_BLEND_ADD;
		else if(blend_mode == BlendMode::Sub)
			bgfx_state |= (BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_ONE))
						 | BGFX_STATE_BLEND_EQUATION(BGFX_STATE_BLEND_EQUATION_REVSUB);
		else if(blend_mode == BlendMode::Mul)
			bgfx_state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
		else if(blend_mode == BlendMode::Normal)
			bgfx_state |= BGFX_STATE_BLEND_NORMAL;
		else if(blend_mode == BlendMode::Alpha)
			bgfx_state |= BGFX_STATE_BLEND_ALPHA;
	}

	struct UnshadedMaterialUniform
	{
		UnshadedMaterialUniform() {}
		UnshadedMaterialUniform(GfxSystem& gfx_system)
			: m_white_tex (&gfx_system.default_texture(TextureHint::White))
			, u_color(bgfx::createUniform("u_color", bgfx::UniformType::Vec4))
			, s_color (bgfx::createUniform("s_color", bgfx::UniformType::Int1))
		{}

		void upload(bgfx::Encoder& encoder, const UnshadedMaterialBlock& block) const
		{
			vec4 colour = to_vec4(block.m_colour.m_value);
			encoder.setUniform(u_color, &colour);

			encoder.setTexture(uint8_t(TextureSampler::Color), s_color, block.m_colour.m_texture ? block.m_colour.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle u_color;
		bgfx::UniformHandle s_color;
	};

	struct FresnelMaterialUniform
	{
		FresnelMaterialUniform() {}
		FresnelMaterialUniform(GfxSystem& gfx_system)
			: m_white_tex(&gfx_system.default_texture(TextureHint::White))
			, u_fresnel_params(bgfx::createUniform("u_fresnel_params", bgfx::UniformType::Vec4))
			, u_fresnel_value(bgfx::createUniform("u_fresnel_value", bgfx::UniformType::Vec4))
			, s_fresnel(bgfx::createUniform("s_fresnel", bgfx::UniformType::Int1))
		{}

		void upload(bgfx::Encoder& encoder, const FresnelMaterialBlock& block) const
		{
			vec4 value = to_vec4(block.m_value.m_value);
			vec4 params = { block.m_fresnel_bias, block.m_fresnel_scale, block.m_fresnel_power, 1.f };
			encoder.setUniform(u_fresnel_value, &value);
			encoder.setUniform(u_fresnel_params, &params);

			encoder.setTexture(uint8_t(TextureSampler::Color), s_fresnel, block.m_value.m_texture ? block.m_value.m_texture->m_texture : m_white_tex->m_texture);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle u_fresnel_params;
		bgfx::UniformHandle u_fresnel_value;
		bgfx::UniformHandle s_fresnel;
	};

	struct PbrMaterialUniform
	{
		PbrMaterialUniform() {}
		PbrMaterialUniform(GfxSystem& gfx_system)
			: m_white_tex(&gfx_system.default_texture(TextureHint::White))
			, m_black_tex (&gfx_system.default_texture(TextureHint::Black))
			, m_normal_tex(&gfx_system.default_texture(TextureHint::Normal))
			, u_albedo(bgfx::createUniform("u_albedo", bgfx::UniformType::Vec4))
			, u_pbr_params_0(bgfx::createUniform("u_pbr_params_0", bgfx::UniformType::Vec4))
			, u_pbr_params_1(bgfx::createUniform("u_pbr_params_1", bgfx::UniformType::Vec4))
			, u_pbr_channels_0(bgfx::createUniform("u_pbr_channels_0", bgfx::UniformType::Vec4))
			, u_emissive(bgfx::createUniform("u_emissive", bgfx::UniformType::Vec4))
			//, u_lightmap_params(bgfx::createUniform("u_lightmap_params", bgfx::UniformType::Vec4))
			, s_albedo(bgfx::createUniform("s_albedo", bgfx::UniformType::Int1))
			, s_metallic (bgfx::createUniform("s_metallic", bgfx::UniformType::Int1))
			, s_roughness(bgfx::createUniform("s_roughness", bgfx::UniformType::Int1))
			, s_emissive(bgfx::createUniform("s_emissive", bgfx::UniformType::Int1))
			, s_normal(bgfx::createUniform("s_normal", bgfx::UniformType::Int1))
			, s_depth(bgfx::createUniform("s_depth", bgfx::UniformType::Int1))
			, s_ambient_occlusion(bgfx::createUniform("s_ambient_occlusion", bgfx::UniformType::Int1))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Int1))
		{}

		void upload(bgfx::Encoder& encoder, const PbrMaterialBlock& block) const
		{
			vec4 albedo = to_vec4(block.m_albedo.m_value);
			encoder.setUniform(u_albedo, &albedo);

			vec4 spec_met_rough = { block.m_specular, block.m_metallic.m_value, block.m_roughness.m_value, block.m_normal.m_value };
			encoder.setUniform(u_pbr_params_0, &spec_met_rough);

			vec4 emissive = to_vec4(block.m_emissive.m_value);
			encoder.setUniform(u_emissive, &emissive);

			vec4 pbr_params_1 = { block.m_anisotropy.m_value, block.m_refraction.m_value, block.m_subsurface.m_value, block.m_depth.m_value };
			encoder.setUniform(u_pbr_params_1, &pbr_params_1);

			vec4 pbr_channels = { float(block.m_roughness.m_channel), float(block.m_metallic.m_channel), 0.f, 0.f };
			encoder.setUniform(u_pbr_channels_0, &pbr_channels);

			auto is_valid = [](Texture* texture) { return texture != nullptr && bgfx::isValid(texture->m_texture); };

			encoder.setTexture(uint8_t(TextureSampler::Color), s_albedo, is_valid(block.m_albedo.m_texture) ? block.m_albedo.m_texture->m_texture : m_white_tex->m_texture);
			encoder.setTexture(uint8_t(TextureSampler::Metallic), s_metallic, is_valid(block.m_metallic.m_texture) ? block.m_metallic.m_texture->m_texture : m_white_tex->m_texture);
			encoder.setTexture(uint8_t(TextureSampler::Roughness), s_roughness, is_valid(block.m_roughness.m_texture) ? block.m_roughness.m_texture->m_texture : m_white_tex->m_texture);

			if(is_valid(block.m_normal.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Normal), s_normal, block.m_normal.m_texture->m_texture);

			if(is_valid(block.m_emissive.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Emissive), s_emissive, block.m_emissive.m_texture->m_texture);
			else if(block.m_emissive.m_value.m_a > 0.f)
				encoder.setTexture(uint8_t(TextureSampler::Emissive), s_emissive, m_black_tex->m_texture);

			if(is_valid(block.m_depth.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Depth), s_depth, block.m_depth.m_texture->m_texture);
			
			if(is_valid(block.m_ambient_occlusion.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::AO), s_ambient_occlusion, block.m_ambient_occlusion.m_texture->m_texture);
		}

		Texture* m_white_tex;
		Texture* m_black_tex;
		Texture* m_normal_tex;

		bgfx::UniformHandle u_albedo;
		bgfx::UniformHandle u_pbr_params_0;
		bgfx::UniformHandle u_pbr_params_1;
		bgfx::UniformHandle u_pbr_channels_0;
		bgfx::UniformHandle u_emissive;
		//bgfx::UniformHandle u_lightmap_params;

		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_metallic;
		bgfx::UniformHandle s_roughness;
		bgfx::UniformHandle s_emissive;
		bgfx::UniformHandle s_normal;
		bgfx::UniformHandle s_depth;
		bgfx::UniformHandle s_ambient_occlusion;
		//bgfx::UniformHandle s_lightmap;
	};

	PbrBlock::PbrBlock(GfxSystem& gfx_system)
		: GfxBlock(gfx_system, *this)
	{
		static cstring options[7] = {
			"NORMAL_MAP",
			"EMISSIVE",
			"ANISOTROPY",
			"AMBIENT_OCCLUSION",
			"DEPTH_MAPPING",
			"DEEP_PARALLAX",
			"LIGHTMAP"
		};
		m_shader_block->m_options = { options, 7 };
	}

	template <> Type& type<mud::PbrBlock>() { static Type ty("PbrBlock"); return ty; }

	PbrBlock& pbr_block(GfxSystem& gfx_system)
	{
		static PbrBlock pbr = { gfx_system };
		return pbr;
	}

	//static TypedUniformBlock<BaseMaterialBlock> s_base_material_block = { "material" };
	//static TypedUniformBlock<UnshadedMaterialBlock> s_unshaded_material_block = { "unshaded" };
	//static TypedUniformBlock<PbrMaterialBlock> s_pbr_material_block = { "pbr" };

	GfxSystem* Material::ms_gfx_system = nullptr;

	void load_material(Material& material, Program& program)
	{
		material.m_program = &program;
	}

	//static uint16_t s_material_index = 0;

	Material::BaseMaterialUniform Material::s_base_uniform = {};
	static UnshadedMaterialUniform s_unshaded_material_block = {};
	static FresnelMaterialUniform s_fresnel_material_block = {};
	static PbrMaterialUniform s_pbr_material_block = {};

	Material::Material(const string& name)
		: m_index(uint16_t(index(type<Material>(), Ref(this))))//++s_material_index)
		, m_name(name)
	{
		static bool init_blocks = true;
		if(init_blocks)
		{
			s_base_uniform = { *ms_gfx_system };
			s_unshaded_material_block = { *ms_gfx_system };
			s_fresnel_material_block = { *ms_gfx_system };
			s_pbr_material_block = { *ms_gfx_system };

			init_blocks = false;
		}
	}

	ShaderVersion Material::shader_version(const Program& program) const
	{
		PbrBlock& pbr = pbr_block(*ms_gfx_system);

		ShaderVersion version = { &program };

		auto is_valid = [](Texture* texture) { return texture != nullptr && bgfx::isValid(texture->m_texture); };

		if(m_pbr_block.m_enabled)
		{
			if(is_valid(m_pbr_block.m_normal.m_texture))
				version.set_option(pbr.m_index, NORMAL_MAP);
			if(is_valid(m_pbr_block.m_emissive.m_texture) || m_pbr_block.m_emissive.m_value.m_a > 0.f)
				version.set_option(pbr.m_index, EMISSIVE);
			if(is_valid(m_pbr_block.m_ambient_occlusion.m_texture))
				version.set_option(pbr.m_index, AMBIENT_OCCLUSION);
			if(is_valid(m_pbr_block.m_depth.m_texture))
				version.set_option(pbr.m_index, DEPTH_MAPPING);
			if(m_pbr_block.m_deep_parallax)
				version.set_option(pbr.m_index, DEEP_PARALLAX);
		}

		return version;
	}

	ShaderVersion Material::shader_version(const Program& program, const Item& item, const ModelItem& model_item) const
	{
		ShaderVersion version = this->shader_version(program);
		UNUSED(item); UNUSED(model_item);
#if 0
		PbrBlock& pbr = pbr_block(*ms_gfx_system);

		if(item.m_lightmaps.size() > 0)
		{
			LightmapItem& binding = *item.m_lightmaps[model_item.m_index];
			if(bgfx::isValid(binding.m_lightmap))
			{
				version.set_option(pbr.m_index, LIGHTMAP);
			}
		}
#endif

		return version;
	}

	void Material::state(uint64_t& bgfx_state) const
	{
		if(m_base_block.m_cull_mode == CullMode::None)
			bgfx_state &= ~BGFX_STATE_CULL_MASK;

		if(m_base_block.m_depth_test == DepthTest::Disabled)
			bgfx_state &= ~BGFX_STATE_DEPTH_TEST_MASK;

		if(m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
			bgfx_state |= BGFX_STATE_WRITE_Z;
		if(m_base_block.m_depth_draw_mode == DepthDraw::Disabled)
			bgfx_state &= ~BGFX_STATE_WRITE_Z;
	}

	void Material::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin) const
	{
		this->state(bgfx_state);

		s_base_uniform.upload(encoder, m_base_block);
		if(m_unshaded_block.m_enabled)
			s_unshaded_material_block.upload(encoder, m_unshaded_block);
		if(m_fresnel_block.m_enabled)
			s_fresnel_material_block.upload(encoder, m_fresnel_block);
		if(m_pbr_block.m_enabled)
			s_pbr_material_block.upload(encoder, m_pbr_block);

		if(skin)
			encoder.setTexture(uint8_t(TextureSampler::Skeleton), s_base_uniform.s_skeleton, skin->m_texture);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/map.h>
#endif

#include <meshoptimizer.h>

#include <cstdio>

namespace mud
{
	bgfx::VertexDecl create_vertex_decl(uint32_t vertex_format)
	{
		bgfx::VertexDecl decl;

		bool half_support = (bgfx::getCaps()->supported & BGFX_CAPS_VERTEX_ATTRIB_HALF) != 0;
		bool needs_half = (vertex_format & VertexAttribute::QTexCoord0) != 0
					   || (vertex_format & VertexAttribute::QTexCoord1) != 0;
		if(needs_half && !half_support)
			printf("WARNING: half vertex attribute not supported but used by texcoords\n");

		bool normalize_indices = false;
#ifdef MUD_PLATFORM_EMSCRIPTEN
		normalize_indices = true;
#endif

		decl.begin();

		if((vertex_format & VertexAttribute::Position) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QPosition) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Half);
		if((vertex_format & VertexAttribute::Normal) != 0)
			decl.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QNormal) != 0)
			decl.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8);
		if((vertex_format & VertexAttribute::Colour) != 0)
			decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
		if((vertex_format & VertexAttribute::Tangent) != 0)
			decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QTangent) != 0)
			decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8);
		if((vertex_format & VertexAttribute::Bitangent) != 0)
			decl.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::TexCoord0) != 0)
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QTexCoord0) != 0)
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Half);
		if((vertex_format & VertexAttribute::TexCoord1) != 0)
			decl.add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QTexCoord1) != 0)
			decl.add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Half);
		if((vertex_format & VertexAttribute::Joints) != 0)
			decl.add(bgfx::Attrib::Indices, 4, bgfx::AttribType::Uint8, normalize_indices);
		if((vertex_format & VertexAttribute::Weights) != 0)
			decl.add(bgfx::Attrib::Weight, 4, bgfx::AttribType::Float);

		decl.end();

		return decl;
	}

	const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format)
	{
		static map<uint32_t, bgfx::VertexDecl> decls;
		if(decls.find(vertex_format) == decls.end())
			decls[vertex_format] = create_vertex_decl(vertex_format);
		return decls[vertex_format];
	}

	static uint16_t s_mesh_index = 0;

	Mesh::Mesh(const string& name, bool readback)
		: m_name(name)
		, m_index(++s_mesh_index)
		, m_readback(readback)
		//, m_material(&gfx_system.debug_material())
		, m_material(nullptr)
	{}

	Mesh::~Mesh()
	{
		this->clear();
	}

	void Mesh::clear()
	{
		if(bgfx::isValid(m_vertex_buffer))
			bgfx::destroy(m_vertex_buffer);
		if(bgfx::isValid(m_index_buffer))
			bgfx::destroy(m_index_buffer);
	}

	void Mesh::read(MeshAdapter& writer, const mat4& transform) const
	{
		MeshAdapter reader = m_cache.read();

		for(size_t i = 0; i < reader.m_vertices.size(); ++i)
		{
			writer.position(mulp(transform, reader.position()));
			if(writer.m_cursor.m_normal)
				writer.normal(muln(transform, reader.normal()));
			if(writer.m_cursor.m_uv0)
				writer.uv0(reader.uv0());
		}

		for(size_t i = 0; i < reader.m_indices.size(); ++i)
		{
			uint32_t index = m_index32 ? reader.index32() : reader.index();
			assert(index <= writer.m_vertices.size());
			writer.index(index);
		}

		writer.next();
	}

	void Mesh::read(MeshPacker& packer, const mat4& transform) const
	{
		MeshAdapter reader = m_cache.read();

		for(size_t i = 0; i < reader.m_vertices.size(); ++i)
		{
			packer.m_positions.push_back(mulp(transform, reader.position()));
			if((m_vertex_format & VertexAttribute::Normal) != 0)
				packer.m_normals.push_back(muln(transform, reader.normal()));
			if((m_vertex_format & VertexAttribute::Colour) != 0)
				packer.m_colours.push_back(reader.colour());
			if((m_vertex_format & VertexAttribute::Tangent) != 0)
				packer.m_tangents.push_back(mult(transform, reader.tangent()));
			if((m_vertex_format & VertexAttribute::TexCoord0) != 0)
				packer.m_uv0s.push_back(reader.uv0());
			if((m_vertex_format & VertexAttribute::TexCoord1) != 0)
				packer.m_uv1s.push_back(reader.uv1());
			//packer.m_bones.push_back(source.bones());
			//packer.m_weights.push_back(source.weights());
		}

		for(size_t i = 0; i < reader.m_indices.size(); ++i)
		{
			packer.m_indices.push_back(m_index32 ? reader.index32() : reader.index());
		}
	}

	void Mesh::upload(DrawMode draw_mode, const GpuMesh& gpu_mesh)
	{
		this->clear();

		m_draw_mode = draw_mode;
		m_vertex_format = gpu_mesh.m_vertex_format;
		m_vertex_count = gpu_mesh.m_vertex_count;
		m_index_count = gpu_mesh.m_index_count;
		m_index32 = gpu_mesh.m_index32;

		m_vertex_buffer = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
		m_index_buffer = bgfx::createIndexBuffer(gpu_mesh.m_index_memory, m_index32 ? BGFX_BUFFER_INDEX32 : 0);

		m_aabb = aabb(gpu_mesh.m_writer.m_aabb.lo, gpu_mesh.m_writer.m_aabb.hi);
		m_uv0_rect = { gpu_mesh.m_writer.m_uv0_rect.lo, gpu_mesh.m_writer.m_uv0_rect.hi };
		m_uv1_rect = { gpu_mesh.m_writer.m_uv1_rect.lo, gpu_mesh.m_writer.m_uv1_rect.hi };

		MeshAdapter reader = gpu_mesh.m_writer.read();
		m_radius = 0.f;
		for(size_t i = 0; i < reader.m_vertices.size(); ++i)
			m_radius = max(length(reader.position() - m_aabb.m_center), m_radius);

		m_origin = m_aabb.m_center;

		if(m_readback)
			this->cache(gpu_mesh);
	}

	template <class T>
	void optimize(const GpuMesh& mesh, GpuMesh& optmesh)
	{
		size_t vertex_stride = vertex_size(mesh.m_vertex_format);

		vector<unsigned int> remap(mesh.m_vertex_count);
		uint32_t index_count = mesh.m_index_count;
		size_t vertex_count = meshopt_generateVertexRemap(remap.data(), (T*)mesh.m_indices, index_count, mesh.m_vertices, mesh.m_vertex_count, vertex_stride);

		// we can't allocate a new mesh with different index size because meshoptimizer remap functions don't allow for different types of indices
		optmesh = alloc_mesh(mesh.m_vertex_format, uint32_t(vertex_count), index_count, mesh.m_index32);

		optmesh.m_writer.m_aabb = mesh.m_writer.m_aabb;
		optmesh.m_writer.m_uv0_rect = mesh.m_writer.m_uv0_rect;
		optmesh.m_writer.m_uv1_rect = mesh.m_writer.m_uv1_rect;

		meshopt_remapIndexBuffer((T*)optmesh.m_indices, (T*)mesh.m_indices, index_count, remap.data());

		meshopt_remapVertexBuffer(optmesh.m_vertices, mesh.m_vertices, mesh.m_vertex_count, vertex_stride, remap.data());

		meshopt_optimizeVertexCache((T*)optmesh.m_indices, (T*)optmesh.m_indices, index_count, vertex_count);

		meshopt_optimizeOverdraw((T*)optmesh.m_indices, (T*)optmesh.m_indices, index_count, (float*)optmesh.m_vertices, vertex_count, vertex_stride, 1.05f);

		meshopt_optimizeVertexFetch(optmesh.m_vertices, (T*)optmesh.m_indices, index_count, optmesh.m_vertices, vertex_count, vertex_stride);

		//meshopt_simplify(optmesh.m_indices, optmesh.m_indices, index_count, optmesh.m_vertices, vertex_count, vertex_stride);
	}

	void Mesh::upload_opt(DrawMode draw_mode, const GpuMesh& mesh)
	{
		GpuMesh optmesh;

		if(mesh.m_index32)
			optimize<uint32_t>(mesh, optmesh);
		else
			optimize<uint16_t>(mesh, optmesh);

		//printf("optimized mesh %s from %i to %i vertices\n", m_name.c_str(), mesh.m_vertex_count, optmesh.m_vertex_count);

		this->upload(draw_mode, optmesh);
	}

	void Mesh::write(DrawMode draw_mode, MeshPacker& packer, bool optimize)
	{
		m_qnormals = packer.m_quantize;

		GpuMesh gpu_mesh = alloc_mesh(packer.vertex_format(), packer.vertex_count(), packer.index_count());
		packer.pack_vertices(gpu_mesh.m_writer, bxidentity());
		gpu_mesh.m_writer.rewind();

		if(optimize)
			this->upload_opt(draw_mode, gpu_mesh);
		else
			this->upload(draw_mode, gpu_mesh);
	}

	void Mesh::cache(const GpuMesh& gpu_mesh)
	{
		m_cached_vertices.resize(gpu_mesh.m_vertex_memory->size);
		m_cached_indices.resize(gpu_mesh.m_index_memory->size);

		memcpy(m_cached_vertices.data(), gpu_mesh.m_vertex_memory->data, gpu_mesh.m_vertex_memory->size);
		memcpy(m_cached_indices.data(), gpu_mesh.m_index_memory->data, gpu_mesh.m_index_memory->size);

		m_cache = MeshAdapter(gpu_mesh.m_vertex_format, m_cached_vertices.data(), m_vertex_count, m_cached_indices.data(), m_index_count, m_index32);
		m_cache.rewind();
	}

	uint64_t Mesh::submit(bgfx::Encoder& encoder) const
	{
		encoder.setVertexBuffer(0, m_vertex_buffer);
		encoder.setIndexBuffer(m_index_buffer);
		return m_draw_mode == PLAIN ? 0 : (BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	//static uint16_t s_model_index = 0;

	GfxSystem* Model::ms_gfx_system = nullptr;

	Model::Model(const string& name)
		: m_name(name)
		, m_index(uint16_t(index(type<Model>(), Ref(this))))//++s_model_index)
	{}

	Model::~Model()
	{}

	Mesh& Model::add_mesh(const string& name, bool readback)
	{
		Mesh& mesh = ms_gfx_system->meshes().construct(name, readback);
		return mesh;
	}

	Rig& Model::add_rig(const string& name)
	{
		UNUSED(name);
		m_rig = &ms_gfx_system->rigs().construct();
		return *m_rig;
	}

	ModelItem& Model::add_item(Mesh& mesh, mat4 transform, int skin, Colour colour, Material* material)
	{
		m_items.push_back({ m_items.size(), &mesh, transform != bxidentity(), transform, skin, colour, material });
		return m_items.back();
	}

	void Model::prepare()
	{
		m_aabb = {};
		m_radius = 0.f;

		for(const ModelItem& item: m_items)
		{
			m_geometry[item.m_mesh->m_draw_mode] = true;
			m_aabb.mergeSafe(transform_aabb(item.m_mesh->m_aabb, item.m_transform));
		}

		m_radius = sqrt(2.f) * max(m_aabb.m_extents.x, max(m_aabb.m_extents.y, m_aabb.m_extents.z));

		m_origin = m_aabb.m_center;
	}

	Model& model_variant(GfxSystem& gfx_system, Model& original, const string& name, array<string> materials, array<Material*> substitutes)
	{
		Model& variant = gfx_system.models().create(name);
		variant = original;

		for(ModelItem& item : variant.m_items)
			for(size_t i = 0; i < materials.size(); ++i)
			{
				if(item.m_mesh->m_material->m_name == materials[i])
					item.m_material = substitutes[i];
			}

		return variant;
	}
}

#ifndef MUD_CPP_20
#include <cstdio>
#endif

#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace bx
{
	inline void mtxQuatLh(float* _result, const float* _quat)
	{
		const float x = _quat[0];
		const float y = _quat[1];
		const float z = _quat[2];
		const float w = _quat[3];

		const float x2  =  x + x;
		const float y2  =  y + y;
		const float z2  =  z + z;
		const float x2x = x2 * x;
		const float x2y = x2 * y;
		const float x2z = x2 * z;
		const float x2w = x2 * w;
		const float y2y = y2 * y;
		const float y2z = y2 * z;
		const float y2w = y2 * w;
		const float z2z = z2 * z;
		const float z2w = z2 * w;

		_result[ 0] = 1.0f - (y2y + z2z);
		_result[ 1] =         x2y + z2w;
		_result[ 2] =         x2z - y2w;
		_result[ 3] = 0.0f;

		_result[ 4] =         x2y - z2w;
		_result[ 5] = 1.0f - (x2x + z2z);
		_result[ 6] =         y2z + x2w;
		_result[ 7] = 0.0f;

		_result[ 8] =         x2z + y2w;
		_result[ 9] =         y2z - x2w;
		_result[10] = 1.0f - (x2x + y2y);
		_result[11] = 0.0f;

		_result[12] = 0.0f;
		_result[13] = 0.0f;
		_result[14] = 0.0f;
		_result[15] = 1.0f;
	}
}

namespace mud
{
	mat4 bxidentity() { mat4 result; bx::mtxIdentity(value_ptr(result)); return result; }
	mat4 bxinverse(const mat4& mat) { mat4 result; bx::mtxInverse(value_ptr(result), value_ptr(mat)); return result; }
	mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans) { mat4 result; bx::mtxSRT(value_ptr(result), scale.x, scale.y, scale.z, rot.x, rot.y, rot.z, trans.x, trans.y, trans.z); return result; }
	mat4 bxscale(const vec3& scale) { mat4 result; bx::mtxScale(value_ptr(result), scale.x, scale.y, scale.z); return result; }
	mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuatLh(value_ptr(result), value_ptr(rot)); return result; }
	//mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), value_ptr(rot)); return transpose(result); }
	mat4 bxtranslation(const vec3& vec) { mat4 result; bx::mtxTranslate(value_ptr(result), vec.x, vec.y, vec.z); return result; }
	mat4 bxmul(const mat4& lhs, const mat4& rhs) { mat4 result; bx::mtxMul(value_ptr(result), value_ptr(lhs), value_ptr(rhs)); return result; }
	vec4 bxmul(const mat4& mat, const vec4& vec) { vec4 result; bx::vec4MulMtx(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	vec3 bxmul(const mat4& mat, const vec3& vec) { vec3 result; bx::vec3MulMtx(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	vec3 bxmulh(const mat4& mat, const vec3& vec) { vec3 result; bx::vec3MulMtxH(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	mat4 bxlookat(const vec3& eye, const vec3& at) { mat4 result; bx::mtxLookAtRh(value_ptr(result), value_ptr(eye), value_ptr(at)); return result; }
	void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up) { bx::mtxLookAtRh(value_ptr(result), value_ptr(eye), value_ptr(at), value_ptr(up)); }
	mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up) { mat4 result; bx::mtxLookAtRh(value_ptr(result), value_ptr(eye), value_ptr(at), value_ptr(up)); return result; }
	mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc) { mat4 result; bx::mtxProjRh(value_ptr(result), fov, aspect, near, far, oglNdc); return result; }
	mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrthoRh(value_ptr(result), rect.x, rect.y, rect.z, rect.w, near, far, offset, oglNdc); return result; }
	mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrthoRh(value_ptr(result), left, right, bottom, top, near, far, offset, oglNdc); return result; }
	mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxtranslation(trans), bxmul(bxrotation(rot), bxscale(scale))); }
	mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxscale(scale), bxmul(bxrotation(rot), bxtranslation(trans))); }

	void debug_print_mat(const mat4& mat)
	{
		//vec3 scale = { length(vec3{ mat[0] }), length(vec3{ mat[1] }), length(vec3{ mat[2] }) };
		printf("pos %.1f, %.1f, %.1f ", mat[3].x, mat[3].y, mat[3].z);
		//printf("orientation %f, %f, %f, %f\n", m_rotation.x, bone.m_rotation.y, bone.m_rotation.z, bone.m_rotation.w);)
	}

	static uint16_t s_node_index = 0;

	Node3::Node3(Scene* scene, Ref object)
		: m_scene(scene)
		, m_index(s_node_index++)
		, m_object(object)
	{}

	Node3::Node3(const mat4& transform)
		: m_index(s_node_index++)
		, m_transform(transform)
	{}
}


#include <bx/math.h>
#include <bx/allocator.h>
#include <bimg/bimg.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/string.h>
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

	ParticleFlow::ParticleFlow(const string& name)
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
		LocatedFile location = m_gfx_system.locate_file("textures/particles/" + string(pathname));
		bimg::ImageContainer* image = load_bgfx_image(m_gfx_system.m_allocator, m_gfx_system.file_reader(), location.path(true).c_str(), bgfx::TextureFormat::BGRA8);
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


#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/map.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
#define PICKING_FOV 3.0f

	Picker::Picker(GfxSystem& gfx_system, FrameBuffer& target)
		: m_target(target)
		, m_size(target.m_size) //PICKING_BUFFER_SIZE)
		, m_program(gfx_system.programs().fetch("picking_id"))
		, m_data(target.m_size.x * target.m_size.y)
	{
		u_picking_id = bgfx::createUniform("u_picking_id", bgfx::UniformType::Vec4);
		
		uint64_t flags = GFX_TEXTURE_POINT | BGFX_SAMPLER_MIP_POINT | GFX_TEXTURE_CLAMP;

		if((bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0 && (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_READ_BACK) != 0)
			m_readback_texture = bgfx::createTexture2D(uint16_t(m_size.y), uint16_t(m_size.y), false, 1, bgfx::TextureFormat::RGBA8, 0 | BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK | flags);

		bgfx::TextureHandle rt[2] =
		{
			bgfx::createTexture2D(uint16_t(m_size.x), uint16_t(m_size.y), false, 1, bgfx::TextureFormat::RGBA8, 0 | BGFX_TEXTURE_RT | flags),
			bgfx::createTexture2D(uint16_t(m_size.x), uint16_t(m_size.y), false, 1, bgfx::TextureFormat::D24S8, 0 | BGFX_TEXTURE_RT | flags)
		};

		m_fbo = bgfx::createFrameBuffer(BX_COUNTOF(rt), rt, true);
		m_fbo_texture = bgfx::getTexture(m_fbo);
	}

	Picker::~Picker()
	{
		bgfx::destroy(m_fbo);
		if(bgfx::isValid(m_readback_texture))
			bgfx::destroy(m_readback_texture);
	}

	void Picker::pick_point(Viewport& viewport, vec2 position, PickCallback callback, uint32_t mask)
	{
		if(m_query) return;
		Ray ray = viewport.ray(position);
		float fov = viewport.m_camera->m_fov / m_size.y;// / float(m_context.m_target->m_size.y);
		m_query = { uvec4{ uvec2(position), uvec2(1U) }, ray, fov, viewport.m_camera->m_aspect, mask };
		m_query.m_callback = callback;
	}

	void Picker::pick_rectangle(Viewport& viewport, vec4 rect, MultipickCallback callback, uint32_t mask)
	{
		if(m_query) return;
		Ray ray = viewport.ray(rect_center(rect));
		float fov = viewport.m_camera->m_fov * rect_h(rect) / m_size.y;
		float aspect = rect_w(rect) / rect_h(rect);
		m_query = { uvec4(rect), ray, fov, aspect, mask };
		m_query.m_multi_callback = callback;
	}

	void Picker::process(Render& render, PickQuery& query)
	{
		if(!query || render.m_shot->m_items.empty()) return;

		uint8_t view = render.picking_pass();

		bgfx::setViewFrameBuffer(view, m_fbo);
		bgfx::setViewClear(view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		mat4 pickView = bxlookat(query.m_center_ray.m_start, query.m_center_ray.m_end);
		mat4 pickProj = bxproj(query.m_fov, query.m_aspect, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewName(view, "picking");
		uint16_t rect_y = bgfx::getCaps()->originBottomLeft ? uint16_t(m_size.y - rect_h(query.m_rect)) : 0;
		bgfx::setViewRect(view, 0, rect_y, uint16_t(rect_w(query.m_rect)), uint16_t(rect_h(query.m_rect)));
		bgfx::setViewTransform(view, value_ptr(pickView), value_ptr(pickProj));
		
		//Frustum frustum = { pickProj, pickView, 0.1f, 1000.f, query.m_fov, query.m_aspect };

		for(uint32_t index = 0; index < render.m_shot->m_items.size(); ++index)
		{
			Item& item = *render.m_shot->m_items[index];

			//if(!frustum_aabb_intersection(frustum.m_planes, item.m_aabb))
			//	continue;

			if(item.m_flags == 0 || !(item.m_flags & query.m_mask))
				continue;
			
			vec4 unpacked = unpack4(index);
			vec4 colour_id = { unpacked.w, unpacked.z, unpacked.y, unpacked.x }; // unpack4 gives reversed order from what we wnat

			bgfx::Encoder& encoder = *bgfx::begin();

			encoder.setUniform(u_picking_id, value_ptr(colour_id));

			if(item.m_model->m_items.empty())
				encoder.touch(view);

			for(const ModelItem& model_item : item.m_model->m_items)
			{
				Material& material = model_item.m_mesh->m_material ? *model_item.m_mesh->m_material : *item.m_material;

				ShaderVersion shader_version = { &m_program };
				shader_version.set_option(0, BILLBOARD, item.m_flags & ItemFlag::Billboard);

				uint64_t render_state = BGFX_STATE_DEFAULT;
				material.state(render_state);
				item.submit(encoder, render_state, model_item);

				encoder.setState(render_state);
				encoder.submit(view, m_program.version(shader_version));
			}

			bgfx::end(&encoder);
		}

		// every time the blit to CPU texture is finished, we read the focused item
		if(query.m_readback_ready <= render.m_frame.m_frame)
		{
			Item* item = nullptr;
			vector<Item*> items = {};

			// not sure which is more efficient
			//vector<uint32_t> counts(render.m_items.size());
			map<uint32_t, uint32_t> counts; 
			uint32_t maxAmount = 0;

			//array<uint32_t> data = { m_data.data(), rect_w(query.m_rect) * rect_h(query.m_rect) };
			//for(const uint32_t& id : data)
			for(size_t x = 0; x < rect_w(query.m_rect); ++x)
				for(size_t y = 0; y < rect_h(query.m_rect); ++y)
				{
					size_t offset = x + y * m_size.x;
					const uint32_t& id = m_data[offset];

					if(id == uint32_t(255 << 24) || id >= render.m_shot->m_items.size())
						continue;

					vector_add(items, render.m_shot->m_items[id]);

					uint32_t count = ++counts[id];
					if(count > maxAmount && id < render.m_shot->m_items.size())
					{
						maxAmount = count;
						item = render.m_shot->m_items[id];
					}
				}

			if(query.m_callback)
				query.m_callback(item);
			if(query.m_multi_callback)
				query.m_multi_callback(items);

			query = {};
		}

		if(query && query.m_readback_ready == UINT32_MAX)
		{
			if(bgfx::isValid(m_readback_texture))
			{
				bgfx::blit(render.picking_pass(), m_readback_texture, 0, 0, m_fbo_texture, 0, 0, uint16_t(rect_w(query.m_rect)), uint16_t(rect_h(query.m_rect)));
				query.m_readback_ready = bgfx::readTexture(m_readback_texture, m_data.data());
			}
			else
			{
				query.m_readback_ready = bgfx::readTexture(m_fbo_texture, m_data.data());
			}
		}
	}
	

}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
#define MUD_GFX_STATE_DEFAULT 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL \
								| BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA

#define MUD_GFX_STATE_DEFAULT_ALPHA 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS \
									  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA

	void pipeline_minimal(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred)
	{
		UNUSED(deferred);

		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx_system);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx_system, filter);
		
		// pipeline
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx_system);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx_system, filter);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx_system);
		UNUSED(particles);

		// mrt
		BlockResolve& resolve = pipeline.add_block<BlockResolve>(gfx_system, copy);

		// effects

		pipeline.m_pass_blocks[size_t(PassType::Depth)] = { &depth };
		pipeline.m_pass_blocks[size_t(PassType::Unshaded)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Background)] = { &sky };
		pipeline.m_pass_blocks[size_t(PassType::Opaque)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Alpha)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Effects)] = { &resolve };
		pipeline.m_pass_blocks[size_t(PassType::PostProcess)] = {};

		{
			Program& program_unshaded = gfx_system.programs().create("unshaded");
			program_unshaded.register_blocks(pipeline.pass_blocks(PassType::Unshaded));

			Program& program_depth = gfx_system.programs().create("depth");
			program_depth.register_blocks(pipeline.pass_blocks(PassType::Depth));

			Program& program_pbr = gfx_system.programs().create("pbr/pbr");
			program_pbr.register_blocks(pipeline.pass_blocks(PassType::Opaque));

			Program& program_fresnel = gfx_system.programs().create("fresnel");
			UNUSED(program_fresnel);
		}

		static MinimalRenderer main_renderer = { gfx_system, pipeline };
		static MinimalRenderer shadow_renderer = { gfx_system, pipeline };

		gfx_system.set_renderer(Shading::Shaded, main_renderer);
		gfx_system.set_renderer(Shading::Volume, shadow_renderer);

		pipeline.m_gather_func = gather_render;
	}

	Pipeline::Pipeline(GfxSystem& gfx_system)
	{
		UNUSED(gfx_system);
	}

	Pipeline::~Pipeline()
	{}

	array<GfxBlock*> Pipeline::pass_blocks(PassType pass)
	{
		return to_array(m_pass_blocks[size_t(pass)]);
	}

	MinimalRenderer::MinimalRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Shaded)
	{
		this->add_pass<PassClear>(gfx_system);
		//this->add_pass<PassOpaque>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	UnshadedRenderer::UnshadedRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Unshaded)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	ClearRenderer::ClearRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Clear)
	{
		this->add_pass<PassClear>(gfx_system);
		this->init();
	}

	static uint8_t s_blank = 0;
	static uint8_t s_zero = 1;

	PassClear::PassClear(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "clear", PassType::Clear)
	{
		bgfx::setPaletteColor(s_blank, 0.f, 0.f, 0.f, 1.f);
		bgfx::setPaletteColor(s_zero, 0.f, 0.f, 0.f, 0.f);
	}

	void PassClear::submit_render_pass(Render& render)
	{
		Pass render_pass = render.next_pass("clear");

		if(render.m_target && render.m_target->m_mrt) //render_pass.m_use_mrt)
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_blank, s_blank, s_blank, s_blank);
		else
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, to_rgba(render.m_viewport.m_clear_colour), 1.f, 0);

		if(render.m_target && render.m_target->m_deferred)
		{
			Pass gbuffer_pass = render.next_pass("clear gbuffer");
			bgfx::setViewClear(gbuffer_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_zero, s_zero, s_zero, s_zero);
			bgfx::setViewFrameBuffer(gbuffer_pass.m_index, render.m_target->m_gbuffer.m_fbo);
		}

		bgfx::touch(render_pass.m_index);
	}

	PassUnshaded::PassUnshaded(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "unshaded", PassType::Unshaded)
	{}

	void PassUnshaded::next_draw_pass(Render& render, Pass& render_pass)
	{
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A //| BGFX_STATE_DEPTH_TEST_LEQUAL
									 | BGFX_STATE_MSAA | BGFX_STATE_CULL_CW | BGFX_STATE_BLEND_ALPHA;

		bgfx::Encoder& encoder = *render_pass.m_encoder;
		for(ImmediateDraw* immediate : render.m_shot->m_immediate)
			immediate->submit(encoder, render_pass.m_index, render_pass.m_bgfx_state);
	}

	void PassUnshaded::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);

		if(element.m_material->m_unshaded_block.m_enabled || element.m_material->m_fresnel_block.m_enabled)
			this->add_element(render, element);
	}

	PassBackground::PassBackground(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "background", PassType::Background)
	{}

	void PassBackground::submit_render_pass(Render& render)
	{
		UNUSED(render);
	}

	PassFlip::PassFlip(GfxSystem& gfx_system, BlockCopy& copy)
		: RenderPass(gfx_system, "post process", PassType::Flip)
		, m_copy(copy)
	{}

	void PassFlip::submit_render_pass(Render& render)
	{
		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_diffuse, render.m_viewport.m_rect);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/set.h>
#endif

namespace mud
{
#ifdef MUD_PREFABNODE
	PrefabNode::PrefabNode()
	{}

	void PrefabNode::draw(Gnode& parent)
	{
		Gnode& self = gfx::node(parent, m_object);
		Gnode& item = gfx::node(self, Ref(this), m_transform.m_position, m_transform.m_rotation, m_transform.m_scale);

		if(m_call.m_callable)
			m_call.m_arguments[0] = Ref(&item);
		if(m_call.validate())
			m_call();
		//else
		//	printf("WARNING: invalid prefab node element arguments\n");

		for(PrefabNode& node : m_nodes)
			node.draw(self);
	}
#endif

	Prefab::Prefab(const string& name)
		: m_name(name)
	{}

	Prefab& import_prefab(GfxSystem& gfx_system, ModelFormat format, const string& name, const ImportConfig& config)
	{
		LocatedFile location = gfx_system.locate_file("models/" + name, carray<string, 1>{ format == ModelFormat::obj ? ".obj" : ".gltf" });
		Prefab& prefab = gfx_system.prefabs().create(name);
		gfx_system.importer(format)->import_prefab(prefab, location.path(false), config);
		return prefab;
	}

	void destroy_prefab(GfxSystem& gfx_system, Prefab& prefab)
	{
		set<Model*> models;
		for(Item& item : prefab.m_items)
			models.insert(item.m_model);

		for(Model* model : models)
		{
			for(ModelItem& model_item : model->m_items)
			{
				gfx_system.meshes().destroy(Ref(model_item.m_mesh));
			}

			gfx_system.models().destroy(model->m_name);
		}
	}
}

#ifndef MUD_CPP_20
#include <mutex>
#endif

#include <bx/platform.h>
#include <bx/readerwriter.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#endif

namespace bgfx
{
	int compileShader(int _argc, const char* _argv[]);
	void getShaderError(char* _outputText, uint16_t& _outputSize);
}

namespace mud
{
	static const bgfx::Memory* load_mem(bx::FileReaderI& reader, const char* file_path)
	{
		if(!bx::open(&reader, file_path))
		{
			printf("ERROR: failed to open file %s\n", file_path);
			return nullptr;
		}

		uint32_t size = uint32_t(bx::getSize(&reader));
		const bgfx::Memory* mem = bgfx::alloc(size + 1);
		bx::read(&reader, mem->data, size);
		bx::close(&reader);
		mem->data[mem->size - 1] = '\0';
		return mem;
	}

	bgfx::ShaderHandle load_shader(bx::FileReaderI& reader, cstring path)
	{
		if(file_exists(path))
			return bgfx::createShader(load_mem(reader, path));
		else
			return BGFX_INVALID_HANDLE;
	}

	bgfx::ProgramHandle load_compute_program(bx::FileReaderI& reader, const string& shader_path)
	{
		const string  cs_path = shader_path + "_cs";

		bgfx::ShaderHandle compute_shader = load_shader(reader, cs_path.c_str());

		return bgfx::createProgram(compute_shader, true);
	}

	bgfx::ProgramHandle load_program(bx::FileReaderI& reader, const string& shader_path)
	{
		const string vs_path = shader_path + "_vs";
		const string gs_path = shader_path + "_gs";
		const string fs_path = shader_path + "_fs";

		bgfx::ShaderHandle vertex_shader = load_shader(reader, vs_path.c_str());
		bgfx::ShaderHandle geometry_shader = load_shader(reader, gs_path.c_str());
		bgfx::ShaderHandle fragment_shader = load_shader(reader, fs_path.c_str());

		bgfx::ProgramHandle program = bgfx::isValid(geometry_shader) ? bgfx::createProgram(vertex_shader, geometry_shader, fragment_shader, true)
																	 : bgfx::createProgram(vertex_shader, fragment_shader, true);

		if(!bgfx::isValid(program))
			printf("ERROR: failed to load program %s\n", shader_path.c_str());
		else
			printf("INFO: loaded program %s id %i\n", shader_path.c_str(), int(program.idx));

		return program;
	}

	static cstring shader_suffixes[] = 
	{
		"_cs.sc",
		"_fs.sc",
		"_gs.sc",
		"_vs.sc",
	};

	cstring shader_suffix(ShaderType shader_type)
	{
		return shader_suffixes[size_t(shader_type)];
	}

	string shader_path(GfxSystem& gfx_system, const string& name, ShaderType shader_type)
	{
		string suffix = shader_suffix(shader_type);
		return gfx_system.m_resource_path + "/shaders/" + name + suffix;
	}

#ifdef MUD_LIVE_SHADER_COMPILER
	bool compile_shader(GfxSystem& gfx_system, const string& name, const string& suffix, ShaderType shader_type, const string& defines_in, cstring source)
	{
		string defines = defines_in;
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;

		string source_path = shader_path(gfx_system, name, shader_type);

		if(source != nullptr)
		{
			write_file(source_path.c_str(), source);
		}

#ifdef _DEBUG
		//bool debug = true;
#else
		//bool debug = false;
#endif

		static cstring output_suffixes[] = { "_cs", "_fs", "_gs", "_vs" };

		string output_suffix = output_suffixes[size_t(shader_type)];
		string output_path = gfx_system.m_resource_path + "/shaders/compiled/" + name + suffix + output_suffix;

		create_file_tree(output_path.c_str());

		printf("INFO: Compiling Shader : %s\n", source_path.c_str());
		printf("INFO: Defines : %s\n", defines.c_str());

		string include = gfx_system.m_resource_path + "/shaders/";
		string varying_path = gfx_system.m_resource_path + "/shaders/varying.def.sc";

		enum Target { GLSL, ESSL, HLSL, Metal };
#if BX_PLATFORM_WINDOWS
		Target target = is_opengl ? GLSL : HLSL;
#elif BX_PLATFORM_LINUX
		Target target = GLSL; UNUSED(is_opengl);
#elif BX_PLATFORM_EMSCRIPTEN
		Target target = ESSL; UNUSED(is_opengl);
#elif BX_PLATFORM_OSX
		Target target = is_opengl ? GLSL : Metal;
#endif

		if(target == ESSL || target == Metal)
			defines += "NO_TEXEL_FETCH;";

		vector<cstring> args;
		auto push_arg = [&args](cstring name, cstring arg) { args.push_back(name); args.push_back(arg); };

		static cstring types[] = { "compute", "fragment", "geometry", "vertex" };

		push_arg("-f", source_path.c_str());
		push_arg("-o", output_path.c_str());
		push_arg("-i", include.c_str());
		args.push_back("--depends");
		push_arg("--varyingdef", varying_path.c_str());
		push_arg("--define", defines.c_str());
		push_arg("--type", types[size_t(shader_type)]);

		//if(debug)
			//args.push_back("--debug");

#ifndef MUD_PLATFORM_EMSCRIPTEN
		args.push_back("-O3");
#endif

		if (target == GLSL)
		{
			push_arg("--platform", "linux");
			push_arg("--profile", "120");
			//push_arg("--profile", "130");
			//push_arg("--profile", "430");
		}
		else if(target == ESSL)
		{
			push_arg("--platform", "android");
		}
		else if(target == HLSL)
		{
			static cstring profiles[] = { "cs_5_0", "ps_5_0", "gs_5_0", "vs_5_0" };
			push_arg("--platform", "windows");
			push_arg("--profile", profiles[size_t(shader_type)]);
		}
		else if (target == Metal)
		{
			push_arg("--platform", "osx");
			push_arg("--profile", "metal");
		}

		int result = bgfx::compileShader(uint32_t(args.size()), args.data());

		if(result == EXIT_FAILURE)
		{
			char output_text[90000];
			uint16_t output_size;
			bgfx::getShaderError(output_text, output_size);

			printf("ERROR: failed to compile %s (%s), defines = %s\n", source_path.c_str(), output_path.c_str(), defines.c_str());
			printf("%s\n", output_text);
			return false;
		}

		return true;
	}
#endif

	struct Program::Impl
	{
		string m_name;

		map<uint64_t, Version> m_versions;
		vector<string> m_option_names;
		vector<string> m_mode_names;

		vector<ShaderDefine> m_defines;
	};

	string program_defines(Program::Impl& program, const ShaderVersion& version)
	{
		string defines = "";

		for(size_t option = 0; option < 32; ++option)
			if(version.m_options & uint32_t(1 << option))
				defines += program.m_option_names[option] + ";";

		for(size_t mode = 0; mode < program.m_mode_names.size(); ++mode)
			defines += program.m_mode_names[mode] + "=" + to_string(version.m_modes[mode]) + ";";

		for(const ShaderDefine& define : program.m_defines)
			defines += string(define.m_name) + "=" + define.m_value + ";";

		return defines;
	}

	GfxSystem* Program::ms_gfx_system = nullptr;

	Program::Program(const string& name, bool compute)
		: m_compute(compute)
		, m_impl(make_unique<Impl>())
	{
		m_impl->m_name = name;
		PbrBlock& pbr = pbr_block(*ms_gfx_system);

		static cstring options[7] = { "SKELETON", "INSTANCING", "BILLBOARD", "QNORMALS", "MRT", "DEFERRED", "CLUSTERED" };
		this->register_options(0, { options, 7 });
		this->register_options(pbr.m_index, pbr.m_shader_block->m_options);
	}

	Program::Program(const string& name, array<GfxBlock*> blocks, array<cstring> sources)
		: Program(name)
	{
		this->register_blocks(blocks);

		for(ShaderType shader_type = ShaderType(0); shader_type != ShaderType::Count; shader_type = ShaderType(uint32_t(shader_type) + 1))
			m_sources[size_t(shader_type)] = sources[size_t(shader_type)];
	}

	Program::~Program()
	{}

	ShaderVersion Program::shader_version(Version& version)
	{
		ShaderVersion config = { this };
		memcpy(&config.m_options, &version.m_version, sizeof(uint64_t));
		return config;
	}

	void Program::compile(GfxSystem& gfx_system, Version& version, bool compute)
	{
		const ShaderVersion config = shader_version(version);

		string suffix = "_v" + to_string(version.m_version);
		string defines = program_defines(*m_impl, config);

		bool compiled = true;
#ifdef MUD_LIVE_SHADER_COMPILER
		if(compute)
		{
			compiled &= compile_shader(gfx_system, m_impl->m_name, suffix, ShaderType::Compute, defines, m_sources[size_t(ShaderType::Compute)]);
		}
		else
		{
			compiled &= compile_shader(gfx_system, m_impl->m_name, suffix, ShaderType::Vertex, defines, m_sources[size_t(ShaderType::Vertex)]);
			compiled &= compile_shader(gfx_system, m_impl->m_name, suffix, ShaderType::Fragment, defines, m_sources[size_t(ShaderType::Fragment)]);

			if(file_exists(shader_path(gfx_system, m_impl->m_name, ShaderType::Geometry).c_str()))
				compiled &= compile_shader(gfx_system, m_impl->m_name, suffix, ShaderType::Geometry, defines, m_sources[size_t(ShaderType::Geometry)]);
		}
#endif

		string full_name = m_impl->m_name + suffix;

		if(!compiled)
		{
			printf("WARNING: failed to compile program %s : using last valid version instead\n", full_name.c_str());
			version.m_update = m_update;
			return;
		}

		printf("INFO: loading program %s with options %s\n", full_name.c_str(), defines.c_str());
		string compiled_path = gfx_system.m_resource_path + "/shaders/compiled/" + full_name;
		version.m_program = compute ? load_compute_program(gfx_system.file_reader(), compiled_path)
									: load_program(gfx_system.file_reader(), compiled_path);
		version.m_update = m_update;
	}

	void Program::update(GfxSystem& gfx_system)
	{
		for(auto& hash_version : m_impl->m_versions)
		{
			Version& version = hash_version.second;
			if(version.m_update < m_update)
			{
				this->compile(gfx_system, version, m_compute);
			}
		}
	}

	cstring Program::name()
	{
		return m_impl->m_name.c_str();
	}

	bgfx::ProgramHandle Program::default_version()
	{
		ShaderVersion config(this);
		return this->version(config);
	}

	bgfx::ProgramHandle Program::version(const ShaderVersion& config)
	{
		uint64_t version_hash = config.hash();

		Version& version = m_impl->m_versions[version_hash];
		if(version.m_update < m_update)
		{
			version.m_version = version_hash;
			this->compile(*ms_gfx_system, version, m_compute);
		}

		return version.m_program;
	}

	template <class T, class U>
	inline void vector_prepend(vector<T>& vector, const U& other)
	{
		vector.insert(vector.begin(), other.begin(), other.end());
	}

	void Program::register_blocks(array<GfxBlock*> blocks)
	{
		for(GfxBlock* block : blocks)
			this->register_block(*block);
	}

	void Program::register_block(const GfxBlock& block)
	{
		this->register_options(block.m_index, block.m_shader_block->m_options);
		this->register_modes(block.m_index, block.m_shader_block->m_modes);
		vector_prepend(m_impl->m_defines, block.m_shader_block->m_defines);
	}

	void Program::register_options(uint8_t block, array<cstring> options)
	{
		m_blocks.m_shader_blocks[block].m_option_shift = uint8_t(m_impl->m_option_names.size());

		for(size_t i = 0; i < options.size(); ++i)
			m_impl->m_option_names.emplace_back(options[i]);
	}

	void Program::register_modes(uint8_t block, array<cstring> modes)
	{
		m_blocks.m_shader_blocks[block].m_mode_shift = uint8_t(m_impl->m_mode_names.size());

		for(size_t i = 0; i < modes.size(); ++i)
			m_impl->m_mode_names.emplace_back(modes[i]);
	}
}

#ifndef MUD_CPP20
#include <algorithm>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <Tracy.hpp>

//#define MUD_GFX_JOBS

namespace mud
{
	uint8_t GfxBlock::s_block_index = 0;

	struct RenderUniform
	{
		RenderUniform() {}
		RenderUniform(int)
			: u_render_params(bgfx::createUniform("u_render_params", bgfx::UniformType::Vec4))
		{}

		bgfx::UniformHandle u_render_params;
	};

	static RenderUniform s_render_uniform;

	Render::Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame)
		: m_shading(shading), m_scene(*viewport.m_scene), m_target(&target), m_target_fbo(target.m_fbo), m_viewport(viewport)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{
		m_debug_pass_index = 245;
		static bool init_uniform = true;
		if(init_uniform)
		{
			s_render_uniform = { 0 };
			init_uniform = false;
		}
	}

	Render::Render(Shading shading, Viewport& viewport, bgfx::FrameBufferHandle& target_fbo, RenderFrame& frame)
		: m_shading(shading), m_scene(*viewport.m_scene), m_target(nullptr), m_target_fbo(target_fbo), m_viewport(viewport)
		, m_camera(*viewport.m_camera), m_frame(frame), m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
		, m_shot(make_unique<Shot>())
	{
		m_debug_pass_index = 245;
	}

	Render::~Render()
	{}

	Pass Render::next_pass(const char* name, bool subpass)
	{
		if(!subpass)
			m_sub_pass_index = 0;

		Pass render_pass;
		render_pass.m_target = m_target;
		render_pass.m_bgfx_state = 0;
		render_pass.m_fbo = m_target_fbo;
		render_pass.m_viewport = &m_viewport;
		render_pass.m_use_mrt = m_needs_mrt;
		render_pass.m_index = m_pass_index++;
		render_pass.m_sub_pass = m_sub_pass_index++;

		render_pass.m_encoder = bgfx::begin();

		//printf("INFO: render pass %s\n", name.c_str());
		m_viewport.render_pass(name, render_pass);

		bgfx::setViewName(render_pass.m_index, name);

		return render_pass;
	}

	void Render::set_uniforms(bgfx::Encoder& encoder) const
	{
		vec4 render_params = { m_frame.m_time, float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
		encoder.setUniform(s_render_uniform.u_render_params, &render_params);
	}

	struct Renderer::Impl
	{
		vector<GfxBlock*> m_gfx_blocks;
		vector<unique<RenderPass>> m_render_passes;
	};

	Renderer::Renderer(GfxSystem& gfx_system, Pipeline& pipeline, Shading shading)
		: m_gfx_system(gfx_system)
		, m_pipeline(pipeline)
		, m_shading(shading)
		, m_impl(make_unique<Impl>())
	{}

	Renderer::~Renderer()
	{}

	void Renderer::init()
	{
		for(auto& render_pass : m_impl->m_render_passes)
			for(GfxBlock* gfx_block : render_pass->m_gfx_blocks)
			{
				if(!has_block(*gfx_block))
					add_block(*gfx_block);
			}
	}

	bool Renderer::has_block(GfxBlock& block)
	{
		return std::find(m_impl->m_gfx_blocks.begin(), m_impl->m_gfx_blocks.end(), &block) != m_impl->m_gfx_blocks.end();
	}

	void Renderer::add_block(GfxBlock& block)
	{
		m_impl->m_gfx_blocks.push_back(&block);
	}

	RenderPass& Renderer::add_pass(unique<RenderPass> render_pass)
	{ 
		m_impl->m_render_passes.emplace_back(move(render_pass));
		return *m_impl->m_render_passes.back();
	}

	void Renderer::gather(Render& render)
	{
		m_pipeline.m_gather_func(render.m_scene, render);
	}

	void Renderer::render(Render& render)
	{
		//render.m_needs_depth_prepass = true;

		for(GfxBlock* block : m_impl->m_gfx_blocks)
			block->begin_render(render);

		// @todo this temporarily fixes the MRT GL bug by forcing MRT in the shader even if not needed by any effects
		render.m_is_mrt = render.m_target && render.m_target->m_mrt;
		//render.m_is_mrt = render.m_needs_mrt && render.m_target && render.m_target->m_mrt;

		for(auto& pass : m_impl->m_render_passes)
		{
			ZoneScopedNC(pass->m_name, tracy::Color::Cyan);

			pass->blocks_begin_pass(render);
			pass->submit_render_pass(render);
		}

		render.m_frame.m_render_pass = render.m_pass_index;

		render.m_frame.m_num_draw_calls += render.m_num_draw_calls;
		render.m_frame.m_num_vertices += render.m_num_vertices;
		render.m_frame.m_num_triangles += render.m_num_triangles;
	}
	
	void Renderer::subrender(Render& render, Render& sub)
	{
		this->render(sub);
		render.m_pass_index = sub.m_pass_index;
	}

	GfxBlock::GfxBlock(GfxSystem& gfx_system, Type& type)
		: m_gfx_system(gfx_system), m_type(type), m_index(s_block_index++)
		, m_shader_block(make_unique<ShaderBlock>())
	{}

	GfxBlock::~GfxBlock()
	{}

	RenderPass::RenderPass(GfxSystem& gfx_system, const char* name, PassType pass_type)
		: m_gfx_system(gfx_system)
		, m_name(name)
		, m_pass_type(pass_type)
		, m_gfx_blocks(gfx_system.m_pipeline->pass_blocks(pass_type))
	{}

	DrawElement::DrawElement(Item& item, const Program& program, const ModelItem& model, const Material& material, const Skin* skin)
		: m_item(&item), m_program(&program), m_model(&model), m_material(&material), m_skin(skin)
		, m_shader_version(material.shader_version(program, item, model))
	{}

	struct DrawList : public vector<DrawElement>
	{
		struct SortByKey
		{
			inline bool operator()(const DrawElement& a, const DrawElement& b) { return a.m_sort_key < b.m_sort_key; }
		};

		DrawList(size_t size)
			: vector<DrawElement>(size)
		{}

		array<DrawElement> elements() { return{ this->first(), this->size() }; }

		DrawElement* first() { return &(*this)[0]; }

		DrawElement& add_element() { this->resize(this->size() + 1); return this->back(); }

		void sort() { std::sort(this->begin(), this->end(), SortByKey()); }
	};

	struct DrawPass::Impl
	{
		Impl() : m_draw_elements(0) {}
		DrawList m_draw_elements;
		vector<DrawBlock*> m_draw_blocks;
	};

	DrawPass::DrawPass(GfxSystem& gfx_system, const char* name, PassType type)
		: RenderPass(gfx_system, name, type)
		, m_impl(make_unique<Impl>())
	{
		this->init_blocks();
	}

	DrawPass::~DrawPass()
	{}

	void DrawPass::init_blocks()
	{
		for(GfxBlock* block : m_gfx_blocks)
			if(block->m_draw_block)
				m_impl->m_draw_blocks.push_back(&as<DrawBlock>(*block));

		m_draw_blocks = m_impl->m_draw_blocks;
	}

	void DrawPass::add_element(Render& render, DrawElement element)
	{
		for(DrawBlock* block : m_impl->m_draw_blocks)
			block->options(render, element.m_shader_version);

		element.m_shader_version.set_option(0, INSTANCING, !element.m_item->m_instances.empty());
		element.m_shader_version.set_option(0, BILLBOARD, element.m_item->m_flags & ItemFlag::Billboard);
		element.m_shader_version.set_option(0, SKELETON, element.m_skin != nullptr);
		element.m_shader_version.set_option(0, QNORMALS, element.m_model->m_mesh->m_qnormals);

		element.m_bgfx_program = const_cast<Program*>(element.m_program)->version(element.m_shader_version);

		m_impl->m_draw_elements.add_element() = element;
	}

	bool mask_draw_mode(uint32_t mask, DrawMode check)
	{
		return (mask & 1 << check) == 0;
	}

	inline Material& item_material(const Item& item, const ModelItem& model_item, Material& fallback)
	{
		if(item.m_material)
			return *item.m_material;
		else if(model_item.m_material)
			return *model_item.m_material;
		else if(model_item.m_mesh->m_material)
			return *model_item.m_mesh->m_material;
		else
			return fallback;
	}

	void DrawPass::gather_draw_elements(Render& render)
	{
		Material& fallback_material = m_gfx_system.debug_material();

		for(Item* item : render.m_shot->m_items)
			for(const ModelItem& model_item : item->m_model->m_items)
			{
				Material& material = item_material(*item, model_item, fallback_material);
				Program& program = *material.m_program;

				if(mask_draw_mode(material.m_base_block.m_geometry_filter, model_item.m_mesh->m_draw_mode))
					continue;

				Skin* skin = (model_item.m_skin > -1 && item->m_rig) ? &item->m_rig->m_skins[model_item.m_skin] : nullptr;

				DrawElement element = { *item, program, model_item, material, skin };
				element.m_sort_key |= uint64_t(element.m_material->m_index) << 0;
				element.m_sort_key |= uint64_t(element.m_model->m_mesh->m_index) << 16;

				this->queue_draw_element(render, element);
			}
	}

	uint32_t float_flip(uint32_t f)
	{
		uint32_t mask = -int(f >> 31) | 0x80000000;
		return f ^ mask;
	}

	// Taking highest 10 bits for rough sort of floats.
	// 0.01 maps to 752; 0.1 to 759; 1.0 to 766; 10.0 to 772;
	// 100.0 to 779 etc. Negative numbers go similarly in 0..511 range.
	uint32_t depth_to_bits(float depth)
	{
		union { float f; uint32_t i; } f2i;
		f2i.f = depth;
		f2i.i = float_flip(f2i.i); // flip bits to be sortable
		uint32_t b = f2i.i >> 22; // take highest 10 bits
		return b;
	}

	void DrawPass::submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, size_t first, size_t count) const
	{
		//printf("submit_draw_elements %i to %i\n", int(first), int(first + count));

		Pass render_pass = pass;
		render_pass.m_encoder = &encoder;

		for(size_t i = first; i < first + count; ++i)
		{
			const DrawElement& element = m_impl->m_draw_elements[i];

			for(DrawBlock* block : m_impl->m_draw_blocks)
				block->submit(render, element, render_pass);
			
			uint64_t render_state = 0 | render_pass.m_bgfx_state | element.m_bgfx_state;
			element.m_material->submit(encoder, render_state, element.m_skin);
			element.m_item->submit(encoder, render_state, *element.m_model);

			render.set_uniforms(encoder);

			encoder.setState(render_state);

			encoder.submit(render_pass.m_index, element.m_bgfx_program, depth_to_bits(element.m_item->m_depth));

			render.m_num_draw_calls += 1;
			render.m_num_vertices += element.m_model->m_mesh->m_vertex_count;
			render.m_num_triangles += element.m_model->m_mesh->m_index_count / 3;
		}
	}

	void DrawPass::submit_render_pass(Render& render)
	{
		this->blocks_begin_draw_pass(render);

		m_impl->m_draw_elements.clear();
		this->gather_draw_elements(render);

		uint8_t num_sub_passes = this->num_draw_passes(render);

		for(PassJob& job : render.m_scene.m_pass_jobs->m_jobs[size_t(m_pass_type)])
		{
			Pass render_pass = render.next_pass(m_name);
			render.set_uniforms(*render_pass.m_encoder);
			job(render, render_pass);
		}

		for(uint8_t sub_pass = 0; sub_pass < num_sub_passes; ++sub_pass)
		{
			Pass render_pass = render.next_pass(m_name, sub_pass > 0);
			this->next_draw_pass(render, render_pass);
			render.m_viewport.render_pass(m_name, render_pass);

#ifdef MUD_GFX_JOBS
			auto submit = [&](JobSystem& js, Job* job, size_t start, size_t count)
			{
				UNUSED(job);
				bgfx::Encoder& encoder = *m_gfx_system.m_encoders[js.thread()];
				this->submit_draw_elements(encoder, render, render_pass, start, count);
			};

			JobSystem& js = *m_gfx_system.m_job_system;
			Job* job = split_jobs<16>(js, nullptr, 0, uint32_t(m_impl->m_draw_elements.size()), submit);
			js.complete(job);
#else
			bgfx::Encoder& encoder = *render_pass.m_encoder;
			this->submit_draw_elements(encoder, render, render_pass, 0, m_impl->m_draw_elements.size());
#endif
		}
	}
}


#include <bx/math.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#define MUD_GL_NO_MRT
//#define MUD_GFX_DEFERRED

namespace mud
{
	vec4 fbo_dest_quad(const uvec2& size, const vec4& rect, bool relative)
	{
		vec4 result = rect;
		if(relative && bgfx::getCaps()->originBottomLeft)
			result.y = size.y - rect.y - rect_h(rect);
		return result;
	}

	vec4 fbo_source_quad(const uvec2& size, const vec4& rect, bool relative)
	{
		vec4 crop = vec4(rect_offset(rect) / vec2(size), rect_size(rect) / vec2(size));
		if(!relative && bgfx::getCaps()->originBottomLeft)
			crop.y = 1.f - crop.y - rect_h(crop);
		return crop;
	}

#if defined MUD_UNIFORM_BLOCKS
	TypedUniformBlock<RenderBlock> RenderBlock::s_block = { "render" };
#endif

	FrameBuffer::FrameBuffer(uvec2 size)
		: m_size(size)
		, m_screen_view(bxidentity())
		, m_screen_proj(bxortho({ 0.f, 1.f, 1.f, 0.f }, 0.f, 1.f, 0.f, bgfx::getCaps()->homogeneousDepth))// false))
	{
		m_fbo = BGFX_INVALID_HANDLE;

#if defined MUD_UNIFORM_BLOCKS
		m_render_block.m_render_size = vec2(m_size);
		m_render_block.m_pixel_size = 1.0f / vec2(m_size);
#endif
	}

	FrameBuffer::FrameBuffer(uvec2 size, bgfx::TextureFormat::Enum format, uint32_t textureFlags)
		: FrameBuffer(size)
	{
		m_fbo = bgfx::createFrameBuffer(uint16_t(size.x), uint16_t(size.y), format, textureFlags);
	}

	FrameBuffer::FrameBuffer(uvec2 size, bgfx::FrameBufferHandle fbo)
		: FrameBuffer(size)
	{
		m_fbo = fbo;
	}

	FrameBuffer::~FrameBuffer()
	{
		if(bgfx::isValid(m_fbo))
			bgfx::destroy(m_fbo);
	}

	void SwapBuffer::create(uvec2 size, bgfx::TextureFormat::Enum color_format)
	{
		m_one = bgfx::createFrameBuffer(uint16_t(size.x), uint16_t(size.y), color_format, GFX_TEXTURE_CLAMP);// | GFX_TEXTURE_POINT);
		m_two = bgfx::createFrameBuffer(uint16_t(size.x), uint16_t(size.y), color_format, GFX_TEXTURE_CLAMP);// | GFX_TEXTURE_POINT);
	}

	SwapBuffer::~SwapBuffer()
	{
		if(bgfx::isValid(m_one))
			bgfx::destroy(m_one);
		if(bgfx::isValid(m_two))
			bgfx::destroy(m_two);
	}

	void Cascade::create(uvec2 size, bgfx::TextureFormat::Enum color_format)
	{
		//uint64_t flags = BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP;
		uint64_t flags = BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP;

		if(bgfx::isTextureValid(1, true, 1, color_format, flags))
		{
			m_texture = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), true, 1, color_format, flags);

			for(uint16_t i = 1; size.x > 1 && i < 9; ++i)
			{
				bgfx::Attachment attachment = { m_texture, i, 0, BGFX_RESOLVE_NONE };
				m_mips[i] = make_unique<FrameBuffer>(uvec2(size.x >> i, size.y >> i), bgfx::createFrameBuffer(1, &attachment, false));
			}
		}
	}

	Cascade::~Cascade()
	{
		if(bgfx::isValid(m_texture))
			bgfx::destroy(m_texture);
	}

	RenderTarget::RenderTarget(uvec2 size)
		: FrameBuffer(size)
		//, m_msaa(MSAA::X16)
	{
		static const uint64_t msaa_value[] = { BGFX_TEXTURE_RT, BGFX_TEXTURE_RT_MSAA_X2, BGFX_TEXTURE_RT_MSAA_X4, BGFX_TEXTURE_RT_MSAA_X8, BGFX_TEXTURE_RT_MSAA_X16 };
		
		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, false, 1, color_format, 0))
			color_format = bgfx::TextureFormat::RGB10A2;
		if(!bgfx::isTextureValid(0, false, 1, color_format, 0))
			color_format = bgfx::TextureFormat::RGBA8;
		if(!bgfx::isTextureValid(0, false, 1, color_format, msaa_value[size_t(m_msaa)]))
			m_msaa = MSAA::Disabled;

		uint64_t render_target_flags = msaa_value[size_t(m_msaa)];
#if defined MUD_PLATFORM_EMSCRIPTEN && !defined MUD_WEBGL2
		render_target_flags |= GFX_TEXTURE_CLAMP;
#endif

		m_depth = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::D24S8, render_target_flags);

		m_diffuse = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format, render_target_flags);

#if defined MUD_PLATFORM_EMSCRIPTEN && !defined MUD_WEBGL2
		m_mrt = false;
#else
		m_mrt = bgfx::getCaps()->limits.maxFBAttachments >= 4;
#endif
		
#ifdef MUD_GL_NO_MRT
		// disabling MRT on OpenGL until we figure out a fix for the visual bug
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;
		if(is_opengl)
			m_mrt = false;
#endif

		m_mrt = false;
		if(m_mrt)
		{
			m_specular = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format, render_target_flags);

			m_normal_rough = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8, render_target_flags);

			//m_sss = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::R8, render_target_flags);

			bgfx::TextureHandle textures[4] = { m_depth, m_diffuse, m_specular, m_normal_rough };
			m_fbo = bgfx::createFrameBuffer(4, textures, true);
		}
		else
		{
			bgfx::TextureHandle textures[2] = { m_depth, m_diffuse };
			m_fbo = bgfx::createFrameBuffer(2, textures, true);
		}

		m_ping_pong.create(size, color_format);
		m_post_process.create(size, color_format);

#if !defined MUD_PLATFORM_EMSCRIPTEN || defined MUD_WEBGL2
		m_cascade.create(size, color_format);
#endif

#ifdef MUD_GFX_DEFERRED
		m_deferred = true;
#else
		m_deferred = false;
#endif
		if(m_deferred)
		{
			m_gbuffer.m_depth		= bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::D24S8,	render_target_flags);
			m_gbuffer.m_position	= bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format,					render_target_flags);
			m_gbuffer.m_normal		= bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format,					render_target_flags);
			m_gbuffer.m_albedo		= bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format,					render_target_flags);
			m_gbuffer.m_surface		= bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8,	render_target_flags);

			bgfx::TextureHandle textures[5] = { m_gbuffer.m_depth, m_gbuffer.m_position, m_gbuffer.m_normal, m_gbuffer.m_albedo, m_gbuffer.m_surface };
			m_gbuffer.m_fbo = bgfx::createFrameBuffer(5, textures, true);
		}
	}

	RenderTarget::~RenderTarget()
	{
		if(bgfx::isValid(m_fbo))
			bgfx::destroy(m_fbo);
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#define DEBUG_ITEMS 1

namespace mud
{
	Scene::Scene(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
		, m_immediate(make_object<ImmediateDraw>(gfx_system.fetch_material("immediate", "unshaded")))
		, m_pass_jobs(make_object<PassJobs>())
		, m_graph(*this)
		, m_root_node(this)
	{
		m_environment.m_radiance.m_colour = Colour::White;//{ 0.35f, 0.33f, 0.3f, 1.f };
		m_environment.m_radiance.m_energy = 0.3f;
		m_environment.m_radiance.m_ambient = 0.7f;

		m_pool = make_object<ObjectPool>();
		m_pool->create_pool<Particles>(1024);

		m_particle_system = make_object<ParticleSystem>(gfx_system, m_pool->pool<Particles>());
	}

	Scene::~Scene()
	{}

	void Scene::update()
	{
		static Clock clock;
		float timestep = float(clock.step());

		m_pool->pool<Animated>().iterate([=](Animated& animated)
		{
			animated.advance(timestep);
		});

		m_pool->pool<Item>().iterate([=](Item& item)
		{
			item.update();
		});

		for(size_t i = 0; i < size_t(PassType::Count); ++i)
			m_pass_jobs->m_jobs[i].clear();
	}

	Gnode& Scene::begin()
	{
		this->update();
		m_immediate->begin();
		return begin_node<Gnode>(m_graph, true);
	}

	void Scene::debug_items(Render& render)
	{
		mat4 identity = bxidentity();
		bool debug = render.m_target != nullptr;
		if(debug)
			for(Item* item : render.m_shot->m_items)
			{
				Colour colour = { 1.f, 0.f, 1.f, 0.15f };
				m_immediate->draw(identity, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
				//m_immediate->draw(item->m_node->m_transform, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
			}
	}

	void cull_items(Scene& scene, const Plane6& planes, vector<Item*>& items)
	{
		//items.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0
			&& frustum_aabb_intersection(planes, item.m_aabb))
			{
				items.push_back(&item);
			}
		});
	}

	void gather_items(Scene& scene, const Camera& camera, vector<Item*>& items)
	{
		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);

		Plane near_plane = camera.near_plane();

		vec4 lod_levels = camera.m_far * vec4{ 0.02f, 0.3f, 0.6f, 0.8f };

		//items.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0)
			{
				if(!frustum_aabb_intersection(planes, item.m_aabb))
					return;

				float depth = distance(near_plane, item.m_aabb.m_center);

				vec4 comparison = vec4(greater(vec4(depth), lod_levels));
				float index = dot(vec4(1.f), comparison);
				uint8_t lod = uint8_t(min(index, 3.f));

				bool has_lod = (item.m_flags & (ItemFlag::Lod0 << lod)) != 0;
				if(has_lod)
				{
					item.m_depth = depth;
					items.push_back(&item);
				}
			}
		});
	}

	void gather_occluders(Scene& scene, const Camera& camera, vector<Item*>& occluders)
	{
		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);

		//occluders.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Occluder) != 0
			&& frustum_aabb_intersection(planes, item.m_aabb))
			{
				occluders.push_back(&item);
			}
		});
	}

	void gather_lights(Scene& scene, vector<Light*>& lights)
	{
		//lights.reserve(m_pool->pool<Light>().size());
		scene.m_pool->pool<Light>().iterate([&](Light& light)
		{
			if(light.m_visible)
			{
				light.m_shot_index = lights.size();
				lights.push_back(&light);
			}
		});
	}

	void gather_render(Scene& scene, Render& render)
	{
		gather_items(scene, render.m_camera, render.m_shot->m_items);
		gather_occluders(scene, render.m_camera, render.m_shot->m_occluders);
		gather_lights(scene, render.m_shot->m_lights);

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, to_array(render.m_shot->m_items)));

		render.m_environment = &scene.m_environment;
		render.m_shot->m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}
}


#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

#include <bx/math.h>

#define SKELETON_TEXTURE_SIZE 256

namespace mud
{
	Skeleton::Skeleton()
	{}

	Skeleton::Skeleton(cstring name, int num_bones)
		: m_name(name)
	{
		m_bones.reserve(num_bones);
	}

	void Skeleton::update_bones()
	{
		for(Bone& bone : m_bones)
		{
			if(bone.m_parent > -1)
				bone.m_pose = m_bones[bone.m_parent].m_pose * bone.m_pose_local;
			else
				bone.m_pose = bone.m_pose_local;
		}
	}

	Bone& Skeleton::add_bone(cstring name, int parent)
	{		
		m_bones.emplace_back(name, int(m_bones.size()), parent);
		return m_bones.back();
	}

	Bone* Skeleton::find_bone(cstring name)
	{
		for(size_t i = 0; i < m_bones.size(); i++)
			if(m_bones[i].m_name == name)
				return &m_bones[i];
		return nullptr;
	}

	Skin::Skin(Skeleton& skeleton, int num_joints)
		: m_skeleton(&skeleton)
	{
		int height = num_joints / SKELETON_TEXTURE_SIZE;
		if(num_joints % SKELETON_TEXTURE_SIZE)
			height++;

		m_texture = bgfx::createTexture2D(SKELETON_TEXTURE_SIZE, uint16_t(height * 4), false, 1, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);
		//m_texture_data.resize(SKELETON_TEXTURE_SIZE * height * 4 * 4);
	}

	Skin::Skin(const Skin& copy, Skeleton& skeleton)
		: Skin(skeleton, int(copy.m_joints.size()))
	{
		m_joints = copy.m_joints;
		m_skeleton = &skeleton;
	}

	Skin::~Skin()
	{
		if(bgfx::isValid(m_texture))
			bgfx::destroy(m_texture);
	}

	void Skin::add_joint(cstring bone, const mat4& inverse_bind)
	{
		Joint joint = { size_t(m_skeleton->find_bone(bone)->m_index), inverse_bind, mat4{} };
		m_joints.push_back(joint);
	}

	Joint* Skin::find_bone_joint(cstring name)
	{
		for(Joint& joint : m_joints)
			if(m_skeleton->m_bones[joint.m_bone].m_name == name)
				return &joint;
		return nullptr;
	}

	void Skin::update_joints()
	{
		int height = int(m_joints.size()) / SKELETON_TEXTURE_SIZE;
		if(m_joints.size() % SKELETON_TEXTURE_SIZE)
			height++;

		m_memory = bgfx::alloc(SKELETON_TEXTURE_SIZE * height * 4 * 4 * sizeof(float));

		int index = 0;
		for(Joint& joint : m_joints)
		{
			joint.m_joint = m_skeleton->m_bones[joint.m_bone].m_pose * joint.m_inverse_bind;

			float* texture = (float*)m_memory->data;
			//float* texture = m_texture_data.data();
			int offset = ((index / SKELETON_TEXTURE_SIZE) * SKELETON_TEXTURE_SIZE) * 4 * 4 + (index % SKELETON_TEXTURE_SIZE) * 4;
			index++;

			//debug_print_mat(joint.m_joint);

			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
					texture[offset + j] = joint.m_joint[j][i];
				offset += SKELETON_TEXTURE_SIZE * 4;
			}
		}

		//const bgfx::Memory* mem = bgfx::makeRef(m_texture_data.data(), sizeof(float) * m_texture_data.size());
		bgfx::updateTexture2D(m_texture, 0, 0, 0, 0, SKELETON_TEXTURE_SIZE, uint16_t(height * 4), m_memory);
	}

	Rig::Rig()
	{}

	Rig::Rig(const Rig& rig)
		: m_skeleton(rig.m_skeleton)
	{
		for(const Skin& skin : rig.m_skins)
			m_skins.emplace_back(skin, m_skeleton);
	}

	Rig& Rig::operator=(const Rig& rig)
	{
		m_skeleton = rig.m_skeleton;
		m_skins.reserve(rig.m_skins.size());
		for(const Skin& skin : rig.m_skins)
			m_skins.emplace_back(skin, m_skeleton);
		return *this;
	}

	void Rig::update_rig()
	{
		m_skeleton.update_bones();

		for(Skin& skin : m_skins)
			skin.update_joints();
	}
}

#ifdef _DEBUG
namespace mud
{
	mat4 fix_bone_pose(Bone& bone)
	{
		return bxrotation(angle_axis(-c_pi * 0.5f, X3)) * bxscale(vec3(0.009999999776482582f)) * bone.m_pose;
	}

	void debug_draw_skeleton(Gnode& parent, const vec3& position, const quat& rotation, Rig& rig)
	{
		for (Bone& bone : rig.m_skeleton.m_bones)
		{
			mat4 pose = bxrotation(rotation) * fix_bone_pose(bone);
			Gnode& node = gfx::node(parent, {}, position + vec3(pose * vec4(Zero3, 1.f)));
			gfx::shape(node, Sphere(0.02f), Symbol());
		}
	}
}
#endif

#ifndef MUD_CPP20
#include <algorithm>
#include <cstdio>
#endif

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>
#include <bimg/encode.h>
#include <bx/readerwriter.h>
#include <bx/file.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/string.h>
#endif

namespace mud
{
	string readable_file_size(double size)
	{
		int i = 0;
		const char* units[] = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
		for(; size > 1024; ++i)
			size /= 1024;
		char buffer[10];
		sprintf(buffer, "%.*f %s", i, size, units[i]);
		return string(buffer);
	}

	static void* load_mem(bx::FileReaderI* reader, bx::AllocatorI* allocator, const char* file_path, uint32_t* size)
	{
		if(!bx::open(reader, file_path))
		{
			printf("ERROR: Failed to open: %s.\n", file_path);
			return nullptr;
		}

		uint32_t data_size = (uint32_t)bx::getSize(reader);
		void* data = BX_ALLOC(allocator, data_size);
		bx::read(reader, data, data_size);
		bx::close(reader);

		if(size)
			*size = data_size;
		return data;
	}

	static void release_bgfx_image(void* _ptr, void* _userData)
	{
		BX_UNUSED(_ptr);
		bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
		bimg::imageFree(imageContainer);
	}

	void save_bgfx_texture(bx::AllocatorI& allocator, bx::FileWriterI& writer, cstring file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth)
	{
		bimg::ImageContainer* source = bimg::imageAlloc(&allocator, bimg::TextureFormat::Enum(texture_format), width, height, depth, 1, false, false);
		if(source == nullptr) return;

		for(uint8_t mip = 0; mip < source->m_numMips; ++mip)
		{
			uint32_t ready = bgfx::readTexture(texture, source->m_data, mip);
			while(bgfx::frame() != ready);
		}

		if(!bx::open(&writer, file_path))
		{
			printf("ERROR: Unable to open output file '%s'", file_path);
			return;
		}

		bimg::ImageContainer* encoded = source;
		if(target_format != texture_format)
			encoded = bimg::imageEncode(&allocator, bimg::TextureFormat::Enum(target_format), bimg::Quality::Default, *source);
		if(encoded == nullptr)
		{
			bimg::imageFree(source);
			return;
		}

		uint8_t stride = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(target_format)) / 8;

		if(target_format == bgfx::TextureFormat::RGBA16F)
			//bimg::imageWriteKtx(&writer, bimg::TextureFormat::RGBA16F, false, width, height, depth, source->m_numMips, 1, encoded->m_data, nullptr);
			bimg::imageWriteHdr(&writer, width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA16F, false, nullptr);
		if(target_format == bgfx::TextureFormat::RGBA8)
			bimg::imageWritePng(&writer, width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA8, false);
		if(target_format == bgfx::TextureFormat::BC3 || target_format == bgfx::TextureFormat::BC6H)
			bimg::imageWriteDds(&writer, *encoded, encoded->m_data, encoded->m_size, nullptr);

		bx::close(&writer);

		bimg::imageFree(source);
		if(target_format != texture_format)
			bimg::imageFree(encoded);
	}

	bgfx::TextureHandle load_bgfx_image(bimg::ImageContainer& image, const char* name, uint64_t flags, bgfx::TextureInfo* info)
	{
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

		const bgfx::Memory* mem = bgfx::makeRef(image.m_data, image.m_size, release_bgfx_image, &image);

		printf("INFO: Loaded image %s of size %s in memory\n", name, readable_file_size(image.m_size).c_str());

		if(image.m_cubeMap)
		{
			handle = bgfx::createTextureCube(uint16_t(image.m_width), 1 < image.m_numMips,
											 image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format), flags, mem);
		}
		else if(1 < image.m_depth)
		{
			handle = bgfx::createTexture3D(uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
										   1 < image.m_numMips, bgfx::TextureFormat::Enum(image.m_format), flags, mem);
		}
		else
		{
			handle = bgfx::createTexture2D(uint16_t(image.m_width), uint16_t(image.m_height), 1 < image.m_numMips,
										   image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format), flags, mem);
		}
		
		if(info)
		{
			bgfx::calcTextureSize(*info, uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
								  image.m_cubeMap, 1 < image.m_numMips, image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format));
		}

		return handle;
	}

	bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, const char* name, void* data, size_t size, uint64_t flags, bgfx::TextureInfo* info, bool generate_mips)
	{
		bimg::ImageContainer* image = bimg::imageParse(&allocator, data, uint32_t(size));
		BX_FREE(&allocator, data);

		if(!image)
			return BGFX_INVALID_HANDLE;

		// @todo implement per-type asset load options and remove this
		bool need_mips = image->m_format == bimg::TextureFormat::R8
					  || image->m_format == bimg::TextureFormat::RGB8
					  || image->m_format == bimg::TextureFormat::RGBA8;

		need_mips = false;

		if(need_mips && generate_mips && image->m_numMips <= 1)
		{
			bimg::ImageContainer* rgba8 = bimg::imageConvert(&allocator, bimg::TextureFormat::RGBA8, *image);
			bimg::ImageContainer* mips = bimg::imageGenerateMips(&allocator, *rgba8);
			if(mips != nullptr)
			{
				bimg::imageFree(rgba8);
				bimg::imageFree(image);
				image = mips;
			}
			else
			{
				printf("WARNING: could not generate mips for texture %s\n", name);
			}
		}

		return load_bgfx_image(*image, name, flags, info);
	}

	bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, bx::FileReaderI& reader, const char* file_path, uint64_t flags, bgfx::TextureInfo* info, bool generate_mips)
	{
		uint32_t size;
		void* data = load_mem(&reader, &allocator, file_path, &size);
		if(!data)
			return BGFX_INVALID_HANDLE;
		else
			return load_bgfx_texture(allocator, file_path, data, size, flags, info, generate_mips);
	}

	bimg::ImageContainer* load_bgfx_image(bx::AllocatorI& allocator, bx::FileReaderI& _reader, const char* _filePath, bgfx::TextureFormat::Enum _dstFormat)
	{
		uint32_t size = 0;
		void* data = load_mem(&_reader, &allocator, _filePath, &size);
		return bimg::imageParse(&allocator, data, size, bimg::TextureFormat::Enum(_dstFormat));
	}

	void save_texture(GfxSystem& gfx_system, Texture& texture, const string& path)
	{
		save_bgfx_texture(gfx_system.m_allocator, gfx_system.file_writer(), path.c_str(), texture.m_format, texture.m_texture, texture.m_format, texture.m_width, texture.m_height);
	}

	void set_texture_info(Texture& texture, bgfx::TextureInfo& texture_info)
	{
		texture.m_width = texture_info.width;
		texture.m_height = texture_info.height;
		texture.m_format = texture_info.format;
		texture.m_bits_per_pixel = texture_info.bitsPerPixel;
	}

	void load_texture(GfxSystem& gfx_system, Texture& texture, const string& path)
	{
		bgfx::TextureInfo texture_info;
		texture.m_texture = load_bgfx_texture(gfx_system.m_allocator, gfx_system.file_reader(), path.c_str(), 0U, &texture_info, true);
		// if(!bgfx::isValid(texture.m_texture)) set placeholder "missing texture" texture instead
		set_texture_info(texture, texture_info);
	}

	void load_texture_mem(GfxSystem& gfx_system, Texture& texture, array<uint8_t> data)
	{
		bgfx::TextureInfo texture_info;
		texture.m_texture = load_bgfx_texture(gfx_system.m_allocator, texture.m_name.c_str(), (void*)data.m_pointer, data.m_count, 0U, &texture_info, true);
		// if(!bgfx::isValid(texture.m_texture)) set placeholder "missing texture" texture instead
		set_texture_info(texture, texture_info);
	}

	void load_texture_rgba(Texture& texture, uint16_t width, uint16_t height, array<uint8_t> data)
	{
		const bgfx::Memory* memory = bgfx::alloc(uint32_t(sizeof(uint8_t) * data.m_count));
		std::copy(data.m_pointer, data.m_pointer + data.m_count, memory->data);
		texture.m_texture = bgfx::createTexture2D(width, height, false, 1, bgfx::TextureFormat::RGBA8, GFX_TEXTURE_POINT, memory);
	}

	Texture::Texture(const string& name)
		: m_name(name)
	{}

	Texture::~Texture()
	{}
}

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTarget>() { static Type ty("mud::AnimationTarget", sizeof(mud::AnimationTarget)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BackgroundMode>() { static Type ty("mud::BackgroundMode", sizeof(mud::BackgroundMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlendMode>() { static Type ty("mud::BlendMode", sizeof(mud::BlendMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::CullMode>() { static Type ty("mud::CullMode", sizeof(mud::CullMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthDraw>() { static Type ty("mud::DepthDraw", sizeof(mud::DepthDraw)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthTest>() { static Type ty("mud::DepthTest", sizeof(mud::DepthTest)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::EmitterFlow>() { static Type ty("mud::EmitterFlow", sizeof(mud::EmitterFlow)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Interpolation>() { static Type ty("mud::Interpolation", sizeof(mud::Interpolation)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::IsometricAngle>() { static Type ty("mud::IsometricAngle", sizeof(mud::IsometricAngle)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ItemShadow>() { static Type ty("mud::ItemShadow", sizeof(mud::ItemShadow)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::LightType>() { static Type ty("mud::LightType", sizeof(mud::LightType)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Lighting>() { static Type ty("mud::Lighting", sizeof(mud::Lighting)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MSAA>() { static Type ty("mud::MSAA", sizeof(mud::MSAA)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialFlag>() { static Type ty("mud::MaterialFlag", sizeof(mud::MaterialFlag)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelFormat>() { static Type ty("mud::ModelFormat", sizeof(mud::ModelFormat)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Month>() { static Type ty("mud::Month", sizeof(mud::Month)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrDiffuseMode>() { static Type ty("mud::PbrDiffuseMode", sizeof(mud::PbrDiffuseMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrSpecularMode>() { static Type ty("mud::PbrSpecularMode", sizeof(mud::PbrSpecularMode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShaderType>() { static Type ty("mud::ShaderType", sizeof(mud::ShaderType)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shading>() { static Type ty("mud::Shading", sizeof(mud::Shading)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ShadowFlags>() { static Type ty("mud::ShadowFlags", sizeof(mud::ShadowFlags)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureChannel>() { static Type ty("mud::TextureChannel", sizeof(mud::TextureChannel)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureHint>() { static Type ty("mud::TextureHint", sizeof(mud::TextureHint)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::TextureSampler>() { static Type ty("mud::TextureSampler", sizeof(mud::TextureSampler)); return ty; }
    
    template <> MUD_GFX_EXPORT Type& type<mud::Animated>() { static Type ty("Animated", sizeof(mud::Animated)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimatedTrack>() { static Type ty("AnimatedTrack", sizeof(mud::AnimatedTrack)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Animation>() { static Type ty("Animation", sizeof(mud::Animation)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationPlay>() { static Type ty("AnimationPlay", sizeof(mud::AnimationPlay)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AnimationTrack>() { static Type ty("AnimationTrack", sizeof(mud::AnimationTrack)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Material>>() { static Type ty("AssetStore<mud::Material>", sizeof(mud::AssetStore<mud::Material>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Model>>() { static Type ty("AssetStore<mud::Model>", sizeof(mud::AssetStore<mud::Model>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::ParticleFlow>>() { static Type ty("AssetStore<mud::ParticleFlow>", sizeof(mud::AssetStore<mud::ParticleFlow>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Prefab>>() { static Type ty("AssetStore<mud::Prefab>", sizeof(mud::AssetStore<mud::Prefab>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Program>>() { static Type ty("AssetStore<mud::Program>", sizeof(mud::AssetStore<mud::Program>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::AssetStore<mud::Texture>>() { static Type ty("AssetStore<mud::Texture>", sizeof(mud::AssetStore<mud::Texture>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Background>() { static Type ty("Background", sizeof(mud::Background)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BaseMaterialBlock>() { static Type ty("BaseMaterialBlock", sizeof(mud::BaseMaterialBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Bone>() { static Type ty("Bone", sizeof(mud::Bone)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Camera>() { static Type ty("Camera", sizeof(mud::Camera)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Culler>() { static Type ty("Culler", sizeof(mud::Culler)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DepthParams>() { static Type ty("DepthParams", sizeof(mud::DepthParams)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Environment>() { static Type ty("Environment", sizeof(mud::Environment)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Filter>() { static Type ty("Filter", sizeof(mud::Filter)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Fog>() { static Type ty("Fog", sizeof(mud::Fog)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrameBuffer>() { static Type ty("FrameBuffer", sizeof(mud::FrameBuffer)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FresnelMaterialBlock>() { static Type ty("FresnelMaterialBlock", sizeof(mud::FresnelMaterialBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Frustum>() { static Type ty("Frustum", sizeof(mud::Frustum)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::FrustumSlice>() { static Type ty("FrustumSlice", sizeof(mud::FrustumSlice)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxBlock>() { static Type ty("GfxBlock", sizeof(mud::GfxBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxContext>() { static Type ty("GfxContext", sizeof(mud::GfxContext)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::GfxSystem>() { static Type ty("GfxSystem", sizeof(mud::GfxSystem)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Gnode>() { static Type ty("Gnode", sizeof(mud::Gnode)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ImmediateDraw>() { static Type ty("ImmediateDraw", sizeof(mud::ImmediateDraw)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ImportConfig>() { static Type ty("ImportConfig", sizeof(mud::ImportConfig)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Item>() { static Type ty("Item", sizeof(mud::Item)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Joint>() { static Type ty("Joint", sizeof(mud::Joint)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Light>() { static Type ty("Light", sizeof(mud::Light)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Material>() { static Type ty("Material", sizeof(mud::Material)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<float>>() { static Type ty("MaterialParam<float>", sizeof(mud::MaterialParam<float>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::MaterialParam<mud::Colour>>() { static Type ty("MaterialParam<mud::Colour>", sizeof(mud::MaterialParam<mud::Colour>)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Mesh>() { static Type ty("Mesh", sizeof(mud::Mesh)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Model>() { static Type ty("Model", sizeof(mud::Model)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ModelItem>() { static Type ty("ModelItem", sizeof(mud::ModelItem)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Node3>() { static Type ty("Node3", sizeof(mud::Node3)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ParticleFlow>() { static Type ty("ParticleFlow", sizeof(mud::ParticleFlow)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::PbrMaterialBlock>() { static Type ty("PbrMaterialBlock", sizeof(mud::PbrMaterialBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Prefab>() { static Type ty("Prefab", sizeof(mud::Prefab)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Program>() { static Type ty("Program", sizeof(mud::Program)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Radiance>() { static Type ty("Radiance", sizeof(mud::Radiance)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderFrame>() { static Type ty("RenderFrame", sizeof(mud::RenderFrame)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderQuad>() { static Type ty("RenderQuad", sizeof(mud::RenderQuad)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Rig>() { static Type ty("Rig", sizeof(mud::Rig)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Scene>() { static Type ty("Scene", sizeof(mud::Scene)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Shot>() { static Type ty("Shot", sizeof(mud::Shot)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skeleton>() { static Type ty("Skeleton", sizeof(mud::Skeleton)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Skin>() { static Type ty("Skin", sizeof(mud::Skin)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Sun>() { static Type ty("Sun", sizeof(mud::Sun)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::SymbolIndex>() { static Type ty("SymbolIndex", sizeof(mud::SymbolIndex)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Texture>() { static Type ty("Texture", sizeof(mud::Texture)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::UnshadedMaterialBlock>() { static Type ty("UnshadedMaterialBlock", sizeof(mud::UnshadedMaterialBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Viewport>() { static Type ty("Viewport", sizeof(mud::Viewport)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockCopy>() { static Type ty("BlockCopy", type<mud::GfxBlock>(), sizeof(mud::BlockCopy)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::DrawBlock>() { static Type ty("DrawBlock", type<mud::GfxBlock>(), sizeof(mud::DrawBlock)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockDepth>() { static Type ty("BlockDepth", type<mud::DrawBlock>(), sizeof(mud::BlockDepth)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockFilter>() { static Type ty("BlockFilter", type<mud::GfxBlock>(), sizeof(mud::BlockFilter)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockParticles>() { static Type ty("BlockParticles", type<mud::GfxBlock>(), sizeof(mud::BlockParticles)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockResolve>() { static Type ty("BlockResolve", type<mud::GfxBlock>(), sizeof(mud::BlockResolve)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::BlockSky>() { static Type ty("BlockSky", type<mud::GfxBlock>(), sizeof(mud::BlockSky)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::ClusteredFrustum>() { static Type ty("ClusteredFrustum", type<mud::Frustum>(), sizeof(mud::ClusteredFrustum)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::Particles>() { static Type ty("Particles", type<mud::ParticleFlow>(), sizeof(mud::Particles)); return ty; }
    template <> MUD_GFX_EXPORT Type& type<mud::RenderTarget>() { static Type ty("RenderTarget", type<mud::FrameBuffer>(), sizeof(mud::RenderTarget)); return ty; }
}

#if 0

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	UniformBlock::UniformBlock(Type& type, const string& name)
		: m_type(type)
		, m_name(name)
	{}

	void UniformBlock::pack_member(size_t size, Member& member)
	{
		if(m_uniforms.empty() || m_uniforms.back().m_space < size)
			m_uniforms.push_back({ "u_" + m_name + "_params_" + to_string(m_num_packed++), member.m_address, bgfx::UniformType::Vec4 });

		m_uniforms.back().m_fields.push_back({ member.m_name, member.m_address, size });
		m_uniforms.back().m_space -= size;
	}

	void UniformBlock::create_member(GfxSystem& gfx_system, const string& name, Member& member)
	{
		if(member.m_type->is<float>())
			pack_member(1, member);
		else if(member.m_type->is<vec2>())
			pack_member(2, member);
		else if(member.m_type->is<vec3>())
			pack_member(3, member);
		else if(member.m_type->is<vec4>() || member.m_type->is<Colour>())
			m_uniforms.push_back(Uniform{ "u_" + name, member.m_address, bgfx::UniformType::Vec4 });
		else if(member.m_type->is<Texture>())
			m_samplers.push_back(Sampler{ "s_" + name, member.m_address, uint8_t(m_samplers.size()), &gfx_system.default_texture(TextureHint::White), {} });
		else if(member.m_type->is<mat4>())
			m_uniforms.push_back(Uniform{ "u_" + name, member.m_address, bgfx::UniformType::Mat4 });

		else if(member.cls().m_members.size() > 0)
			for(Member& sub_member : member.cls().m_members)
				create_member(gfx_system, name, sub_member);
	}

	string UniformBlock::shader_decl()
	{
		for(Uniform& uniform : m_uniforms)
			if(!uniform.m_fields.empty())
			{
				string uniform_decl = "uniform vec4 " + uniform.m_name + "\n";
				for(Uniform::Field& field : uniform.m_fields)
					uniform_decl += "#define u_" + field.m_name + uniform.m_name + "";
			}

		return "";
	}

	void UniformBlock::create(GfxSystem& gfx_system)
	{
		for(Member& member : cls(m_type).m_members)
			create_member(gfx_system, member.m_name, member);

		for(Uniform& uniform : m_uniforms)
			uniform.create();

		for(Sampler& sampler : m_samplers)
			sampler.create();
	}
}

#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <bgfx/bgfx.h>
#include <bx/math.h>

#endif

//#define NO_OCCLUSION_CULLING

namespace mud
{
	GridECS s_viewer_ecs;
	GridECS* g_viewer_ecs = &s_viewer_ecs;

	static uint16_t viewportIndex = 1;

	Viewport::Viewport(Camera& camera, Scene& scene, uvec4 rect, bool scissor)
		: m_camera(&camera)
		, m_scene(&scene)
		, m_index(viewportIndex++)
		, m_rect(rect)
		, m_scissor(scissor)
		, m_culler(*this)
	{
		(Entt&)(*this) = { &s_viewer_ecs, s_viewer_ecs.create() };
	}

	Viewport::~Viewport()
	{}

	void Viewport::render_pass(cstring name, const Pass& render_pass)
	{
		bgfx::setViewName(render_pass.m_index, name);
		bgfx::setViewRect(render_pass.m_index, uint16_t(m_rect.x), uint16_t(m_rect.y), uint16_t(rect_w(m_rect)), uint16_t(rect_h(m_rect)));
		bgfx::setViewTransform(render_pass.m_index, value_ptr(m_camera->m_transform), value_ptr(m_camera->m_projection));
		bgfx::setViewFrameBuffer(render_pass.m_index, render_pass.m_fbo);
		bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_NONE);

		if(m_scissor)
			bgfx::setViewScissor(render_pass.m_index, uint16_t(m_rect.x), uint16_t(m_rect.y), uint16_t(rect_w(m_rect)), uint16_t(rect_h(m_rect)));

		bgfx::touch(render_pass.m_index);
	}

	void Viewport::cull(Render& render)
	{
#ifndef NO_OCCLUSION_CULLING
		m_culler.render(render);
#else
		UNUSED(render);
#endif
	}

	void Viewport::render(Render& render)
	{
		if(rect_h(m_rect) != 0)
			m_camera->m_aspect = float(rect_w(m_rect)) / float(rect_h(m_rect));
		m_camera->update();

		if(m_camera->m_clusters)
		{
			m_camera->m_clusters->m_dirty |= Froxelizer::VIEWPORT_CHANGED | Froxelizer::PROJECTION_CHANGED;
			m_camera->m_clusters->update(*this, m_camera->m_projection, m_camera->m_near, m_camera->m_far);
			m_camera->m_clusters->froxelize_lights(*m_camera, render.m_shot->m_lights);
			m_camera->m_clusters->upload();
		}

		for(RenderTask& task : m_tasks)
			task(render);
	}

	/*void hmdUpdate()
	{
		// Set view and projection matrix for view 0.
		const bgfx::HMD* hmd = bgfx::getHMD();
		if(NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING))
		{
			float view[16];
			bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
			bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

			// Set view 0 default viewport.
			//
			// Use HMD's width/height since HMD's internal frame buffer size
			// might be much larger than window size.
			bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
		}
		else
		
	}*/

	Ray Viewport::ray(const vec2& pos)
	{
		// coord in NDC
		float xNDC = (pos.x / float(rect_w(m_rect))) * 2.0f - 1.0f;
		float yNDC = ((float(rect_h(m_rect)) - pos.y) / float(rect_h(m_rect))) * 2.0f - 1.0f;

		return m_camera->ray({ xNDC, yNDC });
	}

	vec3 Viewport::raycast(const Plane& plane, const vec2& pos)
	{
		Ray ray = this->ray(pos);
		return plane_segment_intersection(plane, { ray.m_start, ray.m_end });
	}
}


#include <bx/allocator.h>
#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#endif

namespace mud
{
	quat sun_rotation(float azimuth, float altitude, const vec3& up, const vec3& north)
	{
		UNUSED(north);
		return angle_axis(-azimuth, up) * angle_axis(-altitude, X3); // cross(north, up));
	}

	quat sun_rotation(Month month, float latitude_degrees, float hour, float ecliptic_obliquity, const vec3& up, const vec3& north)
	{
		float day = 30.0f * float(month) + 15.0f;
		float lambda = 280.46f + 0.9856474f * day;
		lambda = bx::toRad(lambda);
		float delta = bx::asin(bx::sin(ecliptic_obliquity) * bx::sin(lambda));

		float latitude = bx::toRad(latitude_degrees);
		float h = hour * bx::kPi / 12.0f;
		float azimuth = bx::atan2(bx::sin(h), bx::cos(h) * bx::sin(latitude) - bx::tan(delta) * bx::cos(latitude));
		float altitude = bx::asin(bx::sin(latitude) * bx::sin(delta) + bx::cos(latitude) * bx::cos(delta) * bx::cos(h));

		return sun_rotation(azimuth, altitude, up, north);
	}

	BlockSky::BlockSky(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_skybox_program(gfx_system.programs().create("skybox"))
	{}

	void BlockSky::init_block()
	{
		u_skybox.createUniforms();
	}

	void BlockSky::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockSky::begin_pass(Render& render)
	{
		if(!render.m_environment)
			return;

		BackgroundMode mode = render.m_environment->m_background.m_mode;
		if(mode == BackgroundMode::Custom)
			return render.m_environment->m_background.m_custom_function(render);
		else if(mode == BackgroundMode::Radiance || mode == BackgroundMode::Panorama)
		{
			if(!bgfx::isValid(render.m_environment->m_radiance.m_roughness_array))
				return;

			Pass sky_pass = render.next_pass("sky");
			bgfx::Encoder& encoder = *sky_pass.m_encoder;

			encoder.setTexture(uint8_t(TextureSampler::Source0), u_skybox.s_skybox_map, render.m_environment->m_radiance.m_roughness_array);

			unsigned int level = mode == BackgroundMode::Radiance ? 3 : 0;
			vec4 skybox_params = { float(level), float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
			encoder.setUniform(u_skybox.u_skybox_params, &skybox_params);

			mat4 skybox_matrix = bxinverse(render.m_camera.m_transform);
			encoder.setUniform(u_skybox.u_skybox_matrix, &skybox_matrix);

			m_filter.set_uniforms(render, encoder);

			m_filter.submit_quad(*render.m_target, sky_pass.m_index, render.m_target_fbo, m_skybox_program.default_version(), render.m_viewport.m_rect, BGFX_STATE_DEPTH_TEST_LEQUAL);
		}
	}
}

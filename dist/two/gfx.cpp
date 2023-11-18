#include <two/gfx.h>
#include <two/geom.h>
#include <two/pool.h>
#include <two/jobs.h>
#include <two/tree.h>
#include <two/ecs.h>
#include <two/math.h>
#include <two/refl.h>
#include <two/infra.h>
#include <two/type.h>



module two.gfx;

#include <cstdio>

namespace two
{
	Mime::Mime()
	{}

	Mime::~Mime()
	{}

	void Mime::add_item(Item& item)
	{
		m_rig = *item.m_model->m_rig;
		item.m_rig = &m_rig;

		m_targets = m_rig.m_skeleton.m_bones;
		m_nodes.resize(m_rig.m_skeleton.m_bones.size());

		m_anims = item.m_model->m_anims;
	}

	void Mime::add_nodes(span<Node3> nodes)
	{
		m_targets = nodes;
		m_nodes.resize(nodes.size());
	}

	void Mime::start(const string& name, bool loop, float blend, float speed, bool transient)
	{
		for(Animation* animation : m_anims)
			if(animation->m_name == name)
			{
				this->play(*animation, loop, blend, speed, transient);
				return;
			}
	}

	void Mime::play(const Animation& animation, bool loop, float blend, float speed, bool transient)
	{
		for(AnimPlay& playing : m_playing)
		{
			playing.m_transient = true;
			if(blend == 0.f)
				blend = m_default_blend_time;
			if(blend > 0.f)
				playing.m_fadeout = blend;
		}

		m_playing.push_back({ animation, loop, speed, transient, m_nodes, &m_rig });
		m_active = true;
	}

	void Mime::stop()
	{
		m_playing.clear();
	}

	void Mime::pause()
	{
		m_active = false;
	}

	void Mime::next_animation()
	{
		//this->play(*pop(m_queue));
	}

	void Mime::advance(float delta)
	{
		if(m_playing.size() > 2)
			printf("[warning] Mime playing more than 2 animations at the same time\n");

		for(AnimPlay& play : m_playing)
			play.step(delta, m_speed_scale);

		remove_if(m_playing, [](AnimPlay& play) { return play.m_transient && play.m_ended; });

		for(AnimNode& node : m_nodes)
		{
			node.m_transform = bxTRS(node.m_scale, node.m_rotation, node.m_position);
		}

		for(size_t i = 0; i < m_nodes.size(); ++i)
		{
			Node3& node = m_targets[i];
			node.m_transform = node.m_parent != UINT32_MAX
				? m_targets[node.m_parent].m_transform * m_nodes[i].m_transform
				: m_nodes[i].m_transform;
		}

		m_rig.update_rig();
	}

	void Mime::seek(float time)
	{
		for(AnimPlay& play : m_playing)
		{
			play.m_cursor = time;
			play.update(time, 0.f, 1.f);
		}
	}

	AnimPlay::AnimPlay(const Animation& animation, bool loop, float speed, bool transient, span<AnimNode> nodes, Rig* rig)
		: m_animation(&animation)
		, m_loop(loop)
		, m_speed(speed)
		, m_transient(transient)
		, m_nodes(nodes)
		, m_rig(rig)
	{
		m_tracks.reserve(animation.tracks.size());

		for(const AnimTrack& track : animation.tracks)
		{
			AnimNode* target = nullptr;
			if(nodes.size() > track.m_node)
				target = &nodes[track.m_node];
			if(!target && track.m_target != AnimTarget::Weights)
			{
				printf("[warning] No bone found for animation %s track %s with target %i %s\n", animation.m_name.c_str(), "", int(track.m_node), track.m_node_name.c_str());
				continue;
			}

			Track playtrack = { &track, target, {}, track.m_keys[0].m_value };

			m_tracks.push_back(playtrack);
		}
	}

	void AnimPlay::step(float timestep, float speed)
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

		for(AnimPlay::Track& track : m_tracks)
		{
			AnimCursor& c = track.m_cursor;
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

	void AnimPlay::update(float time, float delta, float interp)
	{
		UNUSED(time); UNUSED(interp);
		for(AnimPlay::Track& track : m_tracks)
		{
			auto apply = [](Rig& rig, AnimNode& bone, AnimTarget target, const Value& value)
			{
				if(target == AnimTarget::Position)
					bone.m_position = *(vec3*)value.mem;
				else if(target == AnimTarget::Rotation)
					bone.m_rotation = *(quat*)value.mem;
				else if(target == AnimTarget::Scale)
					bone.m_scale = *(vec3*)value.mem;
				else if(target == AnimTarget::Weights)
				{
					vector<float>& weights = *(vector<float>*)value.mem;
					rig.m_morphs.resize(weights.size());
					for(size_t i = 0; i < weights.size(); ++i)
					{
						rig.m_morphs[i] = weights[i];
					}
				}
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
				apply(*m_rig, *track.m_node, track.m_track->m_target, track.m_value);
			}
			else
			{
				track.m_value = track.m_track->value(track.m_cursor, delta > 0.f);
				apply(*m_rig, *track.m_node, track.m_track->m_target, track.m_value);
			}
		}
	}
}



module two.gfx;

#include <cassert>
#include <algorithm>

namespace two
{
	static table<AnimTarget, Type*> s_target_types = { &type<vec3>(), &type<quat>(), &type<vec3>(), &type<vector<float>>() };

	static table<AnimTarget, Value(*)()> s_empty_value =
	{
		[]() { Value val; new (val.mem) vec3(); return val; },
		[]() { Value val; new (val.mem) quat(); return val; },
		[]() { Value val; new (val.mem) vec3(); return val; },
		[]() { Value val; new (val.mem) vector<float>(); return val; }
	};
	
	Animation::Animation(cstring name)
		: m_name(name)
	{}
	
	AnimTrack::AnimTrack() {}
	AnimTrack::AnimTrack(Animation& animation, size_t node, cstring node_name, AnimTarget target)
		: m_animation(&animation), m_node(node), m_node_name(node_name), m_target(target), m_value_type(s_target_types[target])
	{}

	void AnimTrack::insert_key(float time, const Value& value, float transition)
	{
		size_t position = key_before(time);
		m_keys.insert(m_keys.begin() + position + 1, Key{ time, value, transition });
	}

	size_t AnimTrack::key_after(float time) const
	{
		assert(m_keys.size() > 0);
		auto predicate = [](float lhs, const Key& rhs) { return lhs < rhs.m_time; };
		auto result = std::upper_bound(m_keys.begin(), m_keys.end(), time, predicate);
		return result - m_keys.begin();
	}

	size_t AnimTrack::key_before(float time) const
	{
		return key_after(time) - 1;
	}

	Value AnimTrack::sample(AnimCursor& cursor) const
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

		auto at = [&](size_t i) { return Ref((void*)m_keys[i].m_value.mem, *m_value_type); };

		if(m_interpolation == Interpolation::Nearest)
		{
			return m_keys[cursor.m_prev].m_value;
		}
		else if(m_interpolation == Interpolation::Linear)
		{
			Value result = s_empty_value[m_target]();
			interpolate(Ref((void*)result.mem, *m_value_type), at(cursor.m_prev), at(cursor.m_next), c);
			return result;
		}
		else if(m_interpolation == Interpolation::Cubic || true)
		{
			Value result = s_empty_value[m_target]();
			size_t pre = max<size_t>(0, cursor.m_prev - 1);
			size_t post = max<size_t>(cursor.m_next + 1, m_keys.size());
			interpolate_cubic(Ref((void*)result.mem, *m_value_type), at(pre), at(cursor.m_prev), at(cursor.m_next), at(post), c);
			return result;
		}
	}

	Value AnimTrack::value(AnimCursor& cursor, bool forward) const
	{
		size_t key = forward ? cursor.m_next : cursor.m_prev;
		return m_keys[key].m_value;
	}
}




namespace two
{
	template class TWO_GFX_EXPORT AssetStore<Texture>;
	template class TWO_GFX_EXPORT AssetStore<Program>;
	template class TWO_GFX_EXPORT AssetStore<Material>;
	template class TWO_GFX_EXPORT AssetStore<Model>;
	template class TWO_GFX_EXPORT AssetStore<Flow>;
	template class TWO_GFX_EXPORT AssetStore<Prefab>;
}


#include <cassert>

module two.gfx;

namespace two
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
			{ TF::R8,    TF::RG8U,   TF::RGB8U,   TF::RGBA8U },
			{ TF::R8I,   TF::RG8I,   TF::RGB8I,   TF::RGBA8I },
			{ TF::R16,   TF::RG16,   TF::Unknown, TF::RGBA16U },
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
		m_texture = { uvec2(m_width, m_height), false, TextureFormat(m_format) };
		//m_buffer = bgfx::createDynamicVertexBuffer(m_clusters.m_memory, decl);
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


module two.gfx;

#include <bgfx/bgfx.h>

namespace two
{
	Camera::Camera()
	{
		//m_eye = vec3(10.f);
		m_far = 300.f;
	}

	Camera::Camera(mat4 transform, mat4 projection, bool ortho)
		: m_view(transform)
		, m_proj(projection)
		, m_orthographic(ortho)
	{}

	Camera::Camera(mat4 transform, float fov, float aspect, float near, float far)
		: m_view(transform)
		, m_proj(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(vec3 eye, vec3 at, vec3 up, float fov, float aspect, float near, float far)
		: m_eye(eye)
		, m_target(at)
		, m_up(up)
		, m_view(bxlookat(m_eye, m_target, m_up))
		, m_proj(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(mat4 transform, vec2 rect, float near, float far)
		: m_view(transform)
		, m_proj(bxortho(-rect.x / 2.f, rect.x / 2.f, -rect.y / 2.f, rect.y / 2.f, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth))
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
		if(m_no_update) return;

		m_view = bxlookat(m_eye, m_target, m_up);

		if(!m_orthographic)
			m_proj = bxproj(m_fov, m_aspect, m_near, m_far, bgfx::getCaps()->homogeneousDepth);
		else
			m_proj = bxortho(ortho_rect(m_height, m_aspect), m_near, m_far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::set_look_at(const vec3& eye, const vec3& target)
	{
		m_eye = eye;
		m_target = target;
	}

	void Camera::set_isometric(IsometricAngle from_angle, const vec3& position)
	{
		static const vec3 z_angles[3] = { vec3(0.f), -Z3,  Z3 };
		static const vec3 x_angles[3] = { vec3(0.f),  X3, -X3 };

		vec3 angle = Y3 + z_angles[uint8_t(from_angle >> 0)] + x_angles[uint8_t(from_angle >> 8)];

		m_orthographic = true;
		m_height = 1.0f;

		m_target = position;
		m_eye = position + angle;
	}

	Ray Camera::ray(const vec2& offset) const
	{
		const mat4 inv_viewproj = inverse(m_proj * m_view);

		const vec3 start = bxmulh(inv_viewproj, vec3(offset.x, offset.y, 0.0f));
		const vec3 end = bxmulh(inv_viewproj, vec3(offset.x, offset.y, 1.0f));

		return { start, end, normalize(end - start), 1.f / normalize(end - start) };
	}

	vec3 Camera::transform(const vec3& point) const
	{
		return mulp(m_view, point);
	}

	vec3 Camera::project(const vec3& point) const
	{
		const mat4 viewproj = m_proj * m_view;
		const vec4 clip = viewproj * vec4(point, 1.f);
		const vec3 ndc = vec3(clip) / clip.w;
		return ndc;
	}

	MirrorCamera mirror_camera(const Camera& sourcecam, Node3& node, float clipBias)
	{
		mat4 rotatemat = rotation(node.m_transform);
		vec3 position = vec3(node.m_transform[3]);
		//vec3 normal = muln(m_node->m_transform, Z3);
		vec3 normal = muln(rotatemat, Y3);
		vec3 dir = position - sourcecam.m_eye;

		// Avoid rendering when mirror is facing away
		if(dot(dir, normal) > 0)
			return {};

		rotatemat = rotation(inverse(sourcecam.m_view));
		vec3 eye = -reflect(dir, normal) + position;
		vec3 lookat = muln(rotatemat, -Z3) + sourcecam.m_eye;
		vec3 target = -reflect(position - lookat, normal) + position;
		vec3 up = reflect(muln(rotatemat, Y3), normal);

		Camera camera = Camera(eye, target, up, sourcecam.m_fov, sourcecam.m_aspect, sourcecam.m_near, sourcecam.m_far);
		camera.m_no_update = true;

		static mat4 bias = bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, false);
		mat4 mirror = bias * camera.m_proj * camera.m_view;

		// Now update projection matrix with new clip plane, implementing code from: http://www.terathon.com/code/oblique.html
		// Paper explaining this technique: http://www.terathon.com/lengyel/Lengyel-Oblique.pdf
		Plane plane = Plane(position, normal);
		plane = camera.m_view * plane;

		vec4 clipPlane = vec4(plane.m_normal.x, plane.m_normal.y, plane.m_normal.z, plane.m_distance);

		mat4& proj = camera.m_proj;

		vec4 q;
		q.x = (sign(clipPlane.x) + proj.f[8]) / proj.f[0];
		q.y = (sign(clipPlane.y) + proj.f[9]) / proj.f[5];
		q.z = -1.0f;
		q.w = (1.0f + proj.f[10]) / proj.f[14];

		// Calculate the scaled plane vector
		clipPlane *= 2.f / dot(clipPlane, q);

		// Replacing the third row of the projection matrix
		proj.f[2] = clipPlane.x;
		proj.f[6] = clipPlane.y;
		proj.f[10] = clipPlane.z + 1.0f - clipBias;
		proj.f[14] = clipPlane.w;

		return { true, camera, mirror };
	}
}


module two.gfx;

#ifndef NO_OCCLUSION_CULLING
#include <MaskedOcclusionCulling.h>
#endif

//#define DEBUG_VISIBLE
//#define DEBUG_CULLED
//#define DEBUG_RECTS
//#define DEBUG_CULLED_RECTS
#define ITEM_TO_CLIP

namespace two
{
	void screen_space_rect(Render& render, const Camera& camera, const mat4& mat, const vec2& lo, const vec2& hi, const Colour& colour)
	{
		static const mat4 identity = bxidentity();

		auto torad = [](float d) { return d * c_pi / 180.0f; };
		const float proj_height = tan(torad(camera.m_fov) * 0.5f);
		const float proj_width = proj_height * camera.m_aspect;

		float near = camera.m_near * 2.f;
		const float nw = near * proj_width;
		const float nh = near * proj_height;

		Quad rect = {};
		rect.m_vertices[0] = mulp(mat, vec3(hi.x * nw, hi.y * nh, -near));
		rect.m_vertices[1] = mulp(mat, vec3(hi.x * nw, lo.y * nh, -near));
		rect.m_vertices[2] = mulp(mat, vec3(lo.x * nw, lo.y * nh, -near));
		rect.m_vertices[3] = mulp(mat, vec3(lo.x * nw, hi.y * nh, -near));
		render.m_shot.m_immediate[0]->shape(identity, { Symbol::wire(colour, true), &rect, OUTLINE });
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
		return project_aabb(camera.m_eye, camera.m_far, aabb.bmin(), aabb.bmax(), transform, camera.m_view);
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
	void Culler::begin(Render& render) { UNUSED(render); }
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

	void Culler::begin(Render& render)
	{
		//auto round = [](uint number, uint multiple) { return ((number + multiple / 2) / multiple) * multiple; };
		auto round = [](uint number, uint multiple) { return (number / multiple) * multiple; };

		// these are defines in culling library but not exposed
		const uvec4 rect = uvec4(render.m_viewport->m_rect * vec2(render.m_fbo->m_size));
		const uvec2 size = { round(rect.width, 8U), round(rect.height, 4U) };

		unsigned int width, height;
		m_moc->GetResolution(width, height);

		if(width != size.x || height != size.y)
			m_moc->SetResolution(size.x, size.y);

		m_moc->ClearBuffer();
	}

	void Culler::render(Render& render)
	{
		if(render.m_shot.m_occluders.empty())
			return;
		if(render.m_rect.width == 0 || render.m_rect.height == 0)
			return;

		this->begin(render);
		this->rasterize(render);
		this->cull(render);
		//this->debug(render);

#ifdef DEBUG_VISIBLE
		mat4 identity = bxidentity();
		bool debug = render.m_target != nullptr;
		if(debug)
			for(Item* item : render.m_shot.m_items)
				if((item->m_flags & ItemFlag::Occluder) == 0)
				{
					Colour colour = { 1.f, 1.f, 0.f, 0.15f };
					render.m_shot.m_immediate[0]->draw(identity, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
				}
#endif
	}

	void Culler::rasterize(Render& render)
	{
		const mat4 world_to_clip = render.m_camera->m_proj * render.m_camera->m_view;

		for(Item* item : render.m_shot.m_occluders)
		{
			const mat4 model_to_clip = world_to_clip * item->m_node->m_transform;

			for(ModelElem& elem : item->m_model->m_items)
			{
				Mesh& mesh = *elem.m_mesh;

				if(mesh.m_primitive < PrimitiveType::Triangles)
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
		const mat4 world_to_clip = render.m_camera->m_proj * render.m_camera->m_view;
		const mat4 camera_to_world = inverse(render.m_camera->m_view);

		vector<Item*> items = render.m_shot.m_items;
		render.m_shot.m_items.clear();

		Plane near = render.m_camera->near_plane();

		vector<Item*> culled;
		for(Item* item : items)
		{
			if((item->m_flags & ItemFlag::Occluder) != 0)
			{
				render.m_shot.m_items.push_back(item);
				continue;
			}

#ifdef ITEM_TO_CLIP
			mat4 item_to_clip = world_to_clip * item->m_node->m_transform;
			DepthRect bounds = project_aabb_strict(*render.m_camera, item_to_clip, item->m_model->m_aabb);
#else
			DepthRect bounds = project_aabb_strict(*render.m_camera, world_to_clip, item->m_aabb);
#endif

			MaskedOcclusionCulling::CullingResult result = m_moc->TestRect(bounds.lo.x, bounds.lo.y, bounds.hi.x, bounds.hi.y, bounds.depth);
			if(result == MaskedOcclusionCulling::VISIBLE)
				render.m_shot.m_items.push_back(item);
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
				render.m_shot.m_immediate[0]->draw(identity, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
			}
#endif
	}

	void Culler::debug(Render& render)
	{
		if(render.m_frame->m_frame % 30 == 0)
		{
			const uint width = uint(render.m_rect.width * render.m_target->m_size.x);
			const uint height = uint(render.m_rect.height * render.m_target->m_size.y);
			m_depth_data.resize(width * height);

			m_moc->ComputePixelDepthBuffer(m_depth_data.data(), false);

			if(!bgfx::isValid(m_depth_texture))
				m_depth_texture = { uvec2(width, height), false, TextureFormat::R32F };

			const bgfx::Memory* memory = bgfx::makeRef(m_depth_data.data(), width * height * sizeof(float));
			bgfx::updateTexture2D(m_depth_texture, 0, 0, 0, 0, uint16_t(width), uint16_t(height), memory);
		}

		render.m_scene->m_gfx.m_copy->debug_show_texture(render, m_depth_texture, vec4(0.f));
	}
#endif
}


#include <bgfx/bgfx.h>

module two.gfx;

namespace two
{
	bool queue_depth(GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
	{
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();

		if(element.m_material->m_base.m_depth_draw != DepthDraw::Enabled
		|| element.m_material->m_alpha.m_is_alpha)
			return false;

		const DepthMethod depth_method = block_depth.m_depth_method;
		const Program& program = depth_method == DepthMethod::Distance ? *block_depth.m_distance_program
																	   : *block_depth.m_depth_program;

		element.set_program(program);
		return true;
	}

	void pass_depth(GfxSystem& gfx, Render& render, Pass& pass, bool submit)
	{
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();
		block_depth.submit(render, pass);

		UNUSED(render);
		if(block_depth.m_depth_method == DepthMethod::Distance)
			pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW;
		else
			pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthAscending);

		if(submit)
			gfx.m_renderer.pass(render, pass, queue_depth);
	}

#if 0
	void pass_override(GfxSystem& gfx, Render& render, Pass& pass, Program& program)
	{
		UNUSED(render);
		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;

		auto queue_draw_element = [&](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			element.set_program(program);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}
#endif

	void pass_depth(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("depth", PassType::Depth);
		pass_depth(gfx, render, pass);
	}

	BlockDepth::BlockDepth(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockDepth>())
	{}

	BlockDepth::~BlockDepth()
	{}

	void BlockDepth::init_block()
	{
		m_depth_program = m_gfx.programs().file("depth");
		m_distance_program = m_gfx.programs().file("distance");

		u_depth.createUniforms();
	}

	void BlockDepth::begin_render(Render& render)
	{
		UNUSED(render);

		m_depth_params = {};
		m_distance_params = {};
	}

	void BlockDepth::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(program);
	}

	void BlockDepth::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
		bgfx::setViewUniform(pass.m_index, u_depth.u_depth_p0, &m_depth_params);

		vec4 distance_p0 = { m_distance_params.m_eye, 0.f };
		vec4 distance_p1 = { m_distance_params.m_near, m_distance_params.m_far, 0.f, 0.f };
		bgfx::setViewUniform(pass.m_index, u_depth.u_distance_p0, &distance_p0);
		bgfx::setViewUniform(pass.m_index, u_depth.u_distance_p1, &distance_p1);
	}

	void BlockDepth::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);
	}
}

#ifndef TWO_CPP_20
#include <array>
#include <map>
#include <cstring>
#endif

module two.gfx;

namespace two
{
	ShapeSize shapes_size(span<ProcShape> shapes, DrawMode draw_mode)
	{
		ShapeSize size = { 0U, 0U };

		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				size.vec += draw_mode == PLAIN
					? symbol_triangle_size(shape).vec
					: symbol_line_size(shape).vec;
			}

		return size;
	}

	ImmediateDraw::ImmediateDraw(Material& material)
		: m_material(material)
		, m_cursor{ 0, 0 }
	{
		m_batches[PLAIN].resize(64);
		m_batches[OUTLINE].resize(64);

		m_material.m_base.m_shader_color = ShaderColor::Vertex;

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

	void ImmediateDraw::shape(const mat4& transform, const ProcShape& shape)
	{
		this->draw(transform, { shape });
	}

	void ImmediateDraw::draw(const mat4& transform, span<ProcShape> shapes)
	{
		this->draw(transform, shapes, PLAIN);
		this->draw(transform, shapes, OUTLINE);
	}

	void ImmediateDraw::draw(const mat4& transform, span<ProcShape> shapes, DrawMode draw_mode)
	{
		ShapeSize size = shapes_size(shapes, draw_mode);
		if(size.vertex_count == 0) return;

		Batch* batch = this->batch(draw_mode, size.vertex_count);
		if(batch)
			this->draw(*batch, transform, shapes, size, draw_mode);
	}

	void ImmediateDraw::draw(Batch& batch, const mat4& transform, span<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		size_t vertex_offset = batch.m_vertices.size();
		size_t index_offset = batch.m_indices.size();

		batch.m_vertices.resize(batch.m_vertices.size() + size.vertex_count);
		batch.m_indices.resize(batch.m_indices.size() + size.index_count);

		MeshAdapter data(Vertex::vertex_format, { &batch.m_vertices[vertex_offset], size.vertex_count }, { &batch.m_indices[index_offset], size.index_count }, false);
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
		memcpy(vertex_buffer.data, batch.m_vertices.data(), num_vertices * sizeof(Vertex));//ms_vertex_decl.m_stride);

		bgfx::TransientIndexBuffer index_buffer;
		bgfx::allocTransientIndexBuffer(&index_buffer, num_indices);
		memcpy(index_buffer.data, batch.m_indices.data(), num_indices * sizeof(uint16_t));

		ProgramVersion program = m_material.program(*m_material.m_program);
		m_material.submit(*program.m_program, encoder, bgfx_state);

		encoder.setVertexBuffer(0, &vertex_buffer);
		encoder.setIndexBuffer(&index_buffer);

		encoder.setGroup(bgfx::UniformSet::Group, m_material.m_index);
		encoder.setState(draw_mode == OUTLINE ? bgfx_state | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA : bgfx_state);

		static const mat4 identity = bxidentity();
		encoder.setTransform(value_ptr(identity));

		encoder.submit(view, program.fetch());
	}

	bgfx::VertexDecl ImmediateDraw::ms_vertex_decl;

	static size_t s_direct_index = 0;

	Direct::Direct()
	{}

	Direct::Direct(Item& item)
		: m_item(&item)
		//, m_mesh("direct" + to_string(s_direct_index++))
		//, m_model("direct" + to_string(s_direct_index++))
	{}

	struct SymbolIndex::Impl
	{
		std::map<uint64_t, object<Material>> m_materials;
		std::map<uint64_t, std::map<std::array<char, c_max_shape_size>, object<Model>>> m_symbols;
	};

	SymbolIndex::SymbolIndex()
		: m_impl(make_unique<Impl>())
	{}

	SymbolIndex::~SymbolIndex()
	{}

	uint64_t hash_symbol(const Symbol& symbol, DrawMode draw_mode)
	{
		uint32_t subdiv = uint16_t(symbol.m_subdiv.x) | uint16_t(symbol.m_subdiv.y) << 16;
		return uint64_t(symbol.m_detail) | uint64_t(draw_mode << 16) | uint64_t(subdiv) << 32ULL;
	}

	uint64_t hash_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		return draw_mode == PLAIN ? uint64_t(to_abgr(symbol.m_fill)) | uint64_t(symbol.m_overlay) << 32 | uint64_t(symbol.m_double_sided) << 33
								  : uint64_t(to_abgr(symbol.m_outline)) | uint64_t(symbol.m_overlay) << 32 | uint64_t(symbol.m_double_sided) << 33;
	}

	Material& SymbolIndex::symbol_material(GfxSystem& gfx, const Symbol& symbol, DrawMode draw_mode)
	{
		Colour colour = draw_mode == PLAIN ? symbol.m_fill : symbol.m_outline;

		uint64_t hash = hash_symbol_material(symbol, draw_mode);
		if(m_impl->m_materials.find(hash) == m_impl->m_materials.end())
		{
			m_impl->m_materials[hash] = construct<Material>("Symbol" + to_string(hash));
			Material& m = *m_impl->m_materials[hash];

			m.m_program = &gfx.programs().fetch("solid");
			m.m_base.m_depth_draw = DepthDraw::Disabled;
			m.m_base.m_depth_test = symbol.m_overlay ? DepthTest::Disabled : DepthTest::Enabled;
			m.m_base.m_cull_mode = symbol.m_double_sided ? CullMode::None : CullMode::Back;
			m.m_solid.m_colour.m_value = colour;
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
			//printf("[info] created indexed Shape %s %s\n", shape.m_type.m_name, pack_json(Ref(&shape)).c_str());
			string name = "Shape:" + string(shape.m_type.m_name);
			shapes[shape_mem] = gen_model(name.c_str(), ProcShape{ symbol, &shape, draw_mode }, true);
		}

		return *shapes[shape_mem];
	}

	object<Model> gen_model(cstring id, const ProcShape& shape, bool readback)
	{
		return gen_model(id, vector<ProcShape>{ shape }, readback);
	}

	object<Model> gen_model(cstring id, span<ProcShape> shapes, bool readback)
	{
		object<Model> model = oconstruct<Model>(id);
		gen_model(shapes, *model, readback);
		return model;
	}

	void gen_model(const ProcShape& shape, Model& model, bool readback, Material* material)
	{
		gen_model(span<ProcShape>{ shape }, model, readback, material);
	}

	void gen_model(span<ProcShape> shapes, Model& model, bool readback, Material* material)
	{
		gen_mesh(shapes, model, PLAIN, readback, material);
		gen_mesh(shapes, model, OUTLINE, readback, material);
		model.prepare();
	}

	void gen_mesh(const ProcShape& shape, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		gen_mesh(span<ProcShape>{ shape }, model, draw_mode, readback, material);
	}

	void gen_mesh(span<ProcShape> shapes, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		ShapeSize size = shapes_size(shapes, draw_mode);
		if(size.vertex_count == 0) return;

		Mesh& mesh = model.add_mesh(model.m_name + to_string(uint(draw_mode)), readback);
		mesh.m_material = material;

		const PrimitiveType primitive = draw_mode == PLAIN ? PrimitiveType::Triangles : PrimitiveType::Lines;
		GpuMesh gpu_mesh = alloc_mesh(primitive, ShapeVertex::vertex_format, size.vertex_count, size.index_count);

		MeshAdapter& writer = gpu_mesh.m_writer;
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				draw_mode == OUTLINE ? symbol_draw_lines(shape, writer)
									 : symbol_draw_triangles(shape, writer);
				writer.next();
			}

		if(draw_mode == PLAIN)
			generate_mikkt_tangents({ (ShapeIndex*)gpu_mesh.m_indices.data(), gpu_mesh.m_index_count }, { (ShapeVertex*)gpu_mesh.m_vertices.data(), gpu_mesh.m_vertex_count });

		mesh.upload(gpu_mesh);

		model.add_item(mesh, bxidentity());
	}

	void gen_geom(const ProcShape& shape, MeshPacker& geom, DrawMode draw_mode)
	{
		gen_geom(span<ProcShape>{ shape }, geom, draw_mode);
	}

	void gen_geom(span<ProcShape> shapes, MeshPacker& geom, DrawMode draw_mode)
	{
		ShapeSize size = shapes_size(shapes, draw_mode);
		if(size.vertex_count == 0) return;

		geom.resize(size.vertex_count, size.index_count, ShapeVertex::vertex_format);

		MeshAdapter writer = MeshAdapter(size.vertex_count, geom);
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				draw_mode == OUTLINE
					? symbol_draw_lines(shape, writer)
					: symbol_draw_triangles(shape, writer);
				writer.next();
			}
	}

	Lines::Lines()
	{}

	Lines::Lines(const vector<vec3>& points)
	{
		this->start(points[0]);
		for(const vec3& p : points)
		{
			this->next(p);
		}
	}

	Lines::Lines(const Curve3& curve, size_t subdiv)
		: Lines(curve.points(subdiv))
	{}

	void Lines::add(const vec3& start, const vec3& end, const Colour& start_colour, const Colour& end_colour)
	{
		const float start_distance = m_segments.size() > 0 ? m_segments.back().dist1 : 0.f;
		const float end_distance = start_distance + distance(start, end);
		m_segments.push_back({ start, start_distance, end, end_distance, start_colour, end_colour });
	}

	void Lines::start(const vec3& position, const Colour& colour)
	{
		m_segments.push_back({ position, 0.f, position, 0.f, colour, colour });
	}

	void Lines::next(const vec3& end, const Colour& colour)
	{
		const Segment& last = m_segments.back();
		const float dist = last.dist1 + distance(last.pos1, end);
		m_segments.push_back({ last.pos1, last.dist1, end, dist, last.col1, colour });
	}

	void Lines::setup()
	{
		for(size_t i = 0; i < m_segments.size(); ++i)
		{
			Segment& seg = m_segments[i];
			seg.dist0 = i > 0 ? m_segments[i - 1].dist1 : 0.f;
			seg.dist1 = seg.dist0 + distance(seg.pos0, seg.pos1);
		}
	}

	void Lines::write(Mesh& mesh)
	{
		const uint32_t vertex_format = VertexAttribute::Position4 | VertexAttribute::Colour;
		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Lines, vertex_format, uint32_t(m_segments.size() * 2), 0U);
		MeshAdapter& writer = gpu_mesh.m_writer;

		for(const Segment& seg : m_segments)
		{
			writer.position4(vec4(seg.pos0, seg.dist0));
			writer.colour(seg.col0);

			writer.position4(vec4(seg.pos1, seg.dist1));
			writer.colour(seg.col1);
		}

		mesh.upload(gpu_mesh);
	}

	void Lines::commit(Batch& batch)
	{
		span<float> memory = batch.begin(uint32_t(m_segments.size())); // , sizeof(Segment)
		memcpy(memory.data(), m_segments.data(), memory.size() * sizeof(float));
	}

	void Lines::update_aabb()
	{
		m_aabb = {};

		for(Segment& seg : m_segments)
		{
			m_aabb.merge(seg.pos0);
			m_aabb.merge(seg.pos1);
		}
	}

	void Lines::update_sphere()
	{
		const vec3 center = m_aabb.m_center;
		float radius2 = 0.f;

		for(Segment& seg : m_segments)
		{
			radius2 = max(radius2, distance2(center, seg.pos0));
			radius2 = max(radius2, distance2(center, seg.pos1));
		}

		m_radius = sqrt(radius2);
	}
}


module two.gfx;

namespace two
{
	void pass_resolve(GfxSystem& gfx, Render& render)
	{
		// process effects

		if(!render.m_is_mrt) return;
		
		// @todo three passes to resolve ? this is terrible :( but we can't read and write from the same buffer at the same time can we
		FrameBuffer& fbo = render.m_target->m_ping_pong.swap();
		gfx.m_copy->quad(render.composite_pass("resolve diffuse"), fbo, render.m_target->m_diffuse);
		gfx.m_copy->quad(render.composite_pass("resolve specular"), fbo, render.m_target->m_specular, BGFX_STATE_BLEND_ADD);

		gfx.m_copy->quad(render.composite_pass("resolve"), *render.m_fbo, render.m_target->m_ping_pong.last());
	}

	void pass_effects(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx); UNUSED(render);
		// submit ssao
		// submit ssr
		// submit sss
	}
}


module two.gfx;

#include <cstdio>
#include <cassert>

namespace two
{
	BlockFilter::BlockFilter(GfxSystem& gfx)
		: GfxBlock(gfx, *this)
		, m_quad_program(gfx.programs().create("filter/quad"))
	{
		gfx.m_filter = this;

		m_options = {
			"UNPACK_DEPTH",
			"SOURCE_DEPTH",
			"SOURCE_0_CUBE",
			"SOURCE_0_ARRAY",
			"FILTER_DEBUG_UV"
		};
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

	void BlockFilter::multiply(float mul)
	{
		m_multiply = mul;
	}

	void BlockFilter::source0p(Texture& texture, ProgramVersion& program, int level, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), u_uniform.s_source_0, texture, flags);

		const vec4 levels = { float(level), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_source_levels, &levels);

		program.set_option(m_index, SOURCE_DEPTH, texture.m_is_depth);
		program.set_option(m_index, UNPACK_DEPTH, texture.m_is_depth_packed);
		program.set_option(m_index, SOURCE_0_ARRAY, texture.m_is_array);
		program.set_option(m_index, SOURCE_0_CUBE, texture.m_is_cube);
	}

	void BlockFilter::source0(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), u_uniform.s_source_0, texture, flags);
	}

	void BlockFilter::source1(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source1), u_uniform.s_source_1, texture, flags);
	}

	void BlockFilter::source2(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source2), u_uniform.s_source_2, texture, flags);
	}

	void BlockFilter::source3(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source3), u_uniform.s_source_3, texture, flags);
	}

	void BlockFilter::sourcedepth(Texture& texture, uint32_t flags)
	{
		bgfx::setTexture(uint8_t(TextureSampler::SourceDepth), u_uniform.s_source_depth, texture, flags);
	}

	void BlockFilter::uniform(const Pass& pass, const string& name, const mat4& value)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Mat4, 1U, bgfx::UniformSet::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], &value);
	}

	void BlockFilter::uniform(const Pass& pass, const string& name, const vec4& value)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], &value);
	}

	void BlockFilter::uniforms(const Pass& pass, const string& name, span<float> values)
	{
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, values.size() / 4, bgfx::UniformSet::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], values.data(), values.size() / 4);
	}

	void BlockFilter::uniforms4(const Pass& pass, const string& name, span<vec4> values)
	{
		//if(!has(m_uniforms, name))			
		if(m_uniforms.find(name) == m_uniforms.end())
			m_uniforms[name] = bgfx::createUniform(name.c_str(), bgfx::UniformType::Vec4, values.size(), bgfx::UniformSet::View);

		bgfx::setViewUniform(pass.m_index, m_uniforms[name], values.data(), values.size());
	}

	struct GpuTargetRect
	{
		attr_ gpu_ vec2 rect_size;
		attr_ gpu_ vec2 pixel_size;
	};

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

	void BlockFilter::submit(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const RenderQuad& quad, uint64_t flags, bool render)
	{
		const ushort2 pos = ushort2(floor(quad.m_dest.pos * vec2(fbo.m_size)));
		const ushort2 size = ushort2(ceil((quad.m_dest.pos + quad.m_dest.size) * vec2(fbo.m_size))) - pos;

		ushort4 rect = ushort4(pos, size);
		if(quad.m_relative && bgfx::getCaps()->originBottomLeft)
			rect.y = ushort(fbo.m_size.y) - rect.y - rect.height;

		vec4 crop = quad.m_source;
		if(quad.m_blit)
			crop = vec4(rect) / vec2(fbo.m_size);
		if(!quad.m_relative && bgfx::getCaps()->originBottomLeft)
			crop.y = 1.f - crop.y - crop.height;
		
		//printf("%s crop (%f, %f) (%f, %f)\n", pass.m_name.c_str(), crop.x, crop.y, crop.width, crop.height);

		static mat4 mview = bxidentity();
		static mat4 proj = bxortho(vec4(0.f, 1.f, 1.f, 0.f), 0.f, 1.f, 0.f, bgfx::getCaps()->homogeneousDepth);// false))

#ifdef _DEBUG
		bgfx::setViewName(pass.m_index, pass.m_name.c_str());
#endif
		bgfx::setViewFrameBuffer(pass.m_index, fbo);
		bgfx::setViewTransform(pass.m_index, value_ptr(mview), value_ptr(proj));
		bgfx::setViewRect(pass.m_index, rect.x, rect.y, rect.width, rect.height);

		draw_unit_quad(quad.m_fbo_flip);
		//draw_quad(quad.m_dest.width, quad.m_dest.height);

		bgfx::setUniform(u_uniform.u_source_crop, &crop);

		const vec4 p0 = { m_multiply, 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_filter_p0, &p0);

		bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW | flags);
		bgfx::submit(pass.m_index, program.fetch());

		if(render)
			bgfx::frame();

		m_multiply = 1.f;
	}

	void BlockFilter::quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, uint64_t flags, bool render)
	{
		this->submit(pass, fbo, program, RenderQuad(pass.m_rect, true), flags, render);
	}

	BlockCopy::BlockCopy(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/copy"))
	{
		gfx.m_copy = this;

		m_program.register_block(filter);
	}

	void BlockCopy::init_block()
	{}

	void BlockCopy::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockCopy::submit(const Pass& pass, FrameBuffer& fbo, Texture& texture, const RenderQuad& quad, uint64_t flags)
	{
		ProgramVersion program = { m_program };
		m_filter.source0p(texture, program, TEXTURE_CLAMP);
		m_filter.submit(pass, fbo, program, quad, flags);
	}

	void BlockCopy::quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, uint64_t flags)
	{
		this->submit(pass, fbo, texture, RenderQuad(pass.m_rect, true), flags);
	}

	void BlockCopy::debug_show_texture(Render& render, Texture& texture, const vec4& rect, int level)
	{
		assert(render.m_target);
		const vec4 dest = rect == vec4(0.f) ? vec4(vec2(0.f), vec2(0.25f)) : rect;
		const RenderQuad target_quad = { Rect4, dest };

		ProgramVersion program = { m_program };
		m_filter.source0p(texture, program, level, TEXTURE_CLAMP);

		Pass pass; pass.m_index = render.debug_pass();
		m_filter.submit(pass, render.m_target->m_backbuffer, program, target_quad, 0);
	}
}


#include <bx/allocator.h>

module two.gfx;

#include <stl/stddef.h>
#include <stdint.h>
#include <cstring>
#include <cstdio>
#include <limits>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

//#define USE_STD_BITSET

#include <stl/vector.hpp>

namespace two
{
	// This depends on the maximum number of lights (currently 255),and can't be more than 16 bits.
	static_assert(CONFIG_MAX_LIGHT_INDEX <= UINT16_MAX, "can't have more than 65536 lights");
	using RecordBufferType = std::conditional_t<CONFIG_MAX_LIGHT_INDEX <= UINT8_MAX, uint8_t, uint16_t>;

	// this is chosen so clusterizePointAndSpotLight() vectorizes 4 cluster tests / spotlight
	// with 256 lights this implies 8 jobs (256 / 32) for clusterization.

	using LightGroupType = uint32_t;

	// The first entry always encodes the type of light, i.e. point/spot
	using FroxelThreadData = array<LightGroupType, CLUSTER_BUFFER_ENTRY_COUNT_MAX + 1>;

	static constexpr bool SUPPORTS_REMAPPED_CLUSTERS = false;

	// The Froxel buffer is set to CLUSTER_BUFFER_WIDTH x n
	// With n limited by the supported texture dimension, which is guaranteed to be at least 2048
	// in all version of GLES.

	// Make sure this matches the same constants in shading_lit.fs
	constexpr uint32_t CLUSTER_BUFFER_WIDTH_SHIFT = 6u;
	constexpr uint32_t CLUSTER_BUFFER_WIDTH = 1u << CLUSTER_BUFFER_WIDTH_SHIFT;
	constexpr uint32_t CLUSTER_BUFFER_WIDTH_MASK = CLUSTER_BUFFER_WIDTH - 1u;
	constexpr uint32_t CLUSTER_BUFFER_HEIGHT = (CLUSTER_BUFFER_ENTRY_COUNT_MAX + CLUSTER_BUFFER_WIDTH_MASK) / CLUSTER_BUFFER_WIDTH;

	constexpr uint32_t RECORD_BUFFER_WIDTH_SHIFT = 5u;
	constexpr uint32_t RECORD_BUFFER_WIDTH = 1u << RECORD_BUFFER_WIDTH_SHIFT;
	constexpr uint32_t RECORD_BUFFER_WIDTH_MASK = RECORD_BUFFER_WIDTH - 1u;

	constexpr uint32_t RECORD_BUFFER_HEIGHT = 2048;
	constexpr uint32_t RECORD_BUFFER_ENTRY_COUNT = RECORD_BUFFER_WIDTH * RECORD_BUFFER_HEIGHT; // 64K

	// number of lights processed by one group (e.g. 32)
	static constexpr uint32_t LIGHT_PER_GROUP = sizeof(LightGroupType) * 8;

	// number of groups (i.e. jobs) to use for clusterization (e.g. 8)
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

	struct FroxelUniform
	{
		void createUniforms()
		{
			s_light_records  = bgfx::createUniform("s_light_records",  bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
			s_light_clusters = bgfx::createUniform("s_light_clusters", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);

			u_cluster_p0 = bgfx::createUniform("u_cluster_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_cluster_f = bgfx::createUniform("u_cluster_f", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
			u_cluster_z = bgfx::createUniform("u_cluster_z", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View);
		}

		bgfx::UniformHandle s_light_records;
		bgfx::UniformHandle s_light_clusters;

		bgfx::UniformHandle u_cluster_p0;
		bgfx::UniformHandle u_cluster_f;
		bgfx::UniformHandle u_cluster_z;
	};

	struct Froxelizer::Impl
	{
		Impl()
			: m_clusters({ GpuBuffer::ElementType::UINT16, 2 }, CLUSTER_BUFFER_WIDTH, CLUSTER_BUFFER_HEIGHT)
			, m_records({ record_type(), 1 }, RECORD_BUFFER_WIDTH, RECORD_BUFFER_HEIGHT)
		{
			m_uniform.createUniforms();
		}

		template <class T>
		struct Buffer
		{
			Buffer(GpuBuffer::Element element, uint32_t row_size, uint32_t row_count) : m_buffer(element, row_size, row_count) {}
			GpuBuffer m_buffer;
			vector<T> m_data;
			const bgfx::Memory* m_memory;
		};

		vector<FroxelThreadData> m_cluster_sharded_data;  // 256 KiB w/ 256 lights
		vector<LightRecord> m_light_records;             // 256 KiB w/ 256 lights

		Buffer<FroxelEntry> m_clusters;			//  32 KiB w/ 8192 clusters
		Buffer<RecordBufferType> m_records;		//  64 KiB // max 32 KiB  (actual: resolution dependant)

		FroxelUniform m_uniform;
	};

	void clusterize_light(ClusteredFrustum& frustum, FroxelThreadData& clusterThread, uint32_t bit, const mat4& projection, float near, const LightParams& light, float light_far);

	Froxelizer::Froxelizer(GfxSystem& gfx)
		: m_gfx(gfx)
		, m_impl(construct<Impl>())
	{
		UNUSED(RECORD_BUFFER_WIDTH_MASK);
	}

	Froxelizer::~Froxelizer()
	{}

	uint32_t Froxelizer::record(uint32_t cluster) { return m_impl->m_clusters.m_data[cluster].offset; }
	uint32_t Froxelizer::count(uint32_t record, int type) { return m_impl->m_clusters.m_data[record].count[type]; }
	uint32_t Froxelizer::light(uint32_t record) { return m_impl->m_records.m_data[record]; }

	bool Froxelizer::update(const uvec4& rect, const mat4& projection, float near, float far)
	{
		if(m_viewport != rect) //[[unlikely]]
			m_dirty |= uint8_t(Dirty::Viewport);
		if(m_proj != projection) //[[unlikely]]
			m_dirty |= uint8_t(Dirty::Projection);

		//if(all(less(abs(m_proj), vec3(EPSILON))))

		m_viewport = rect;
		m_proj = projection;
		m_near = near;
		m_light_far = far;

		bool uniformsNeedUpdating = false;

		if(m_dirty) // [[unlikely]] 
			uniformsNeedUpdating = update();

		return uniformsNeedUpdating;
	}

	void Froxelizer::setup()
	{
		// cluster buffer (~32 KiB) & record buffer (~64 KiB)
		m_impl->m_clusters.m_data.resize(CLUSTER_BUFFER_ENTRY_COUNT_MAX);
		m_impl->m_records.m_data.resize(RECORD_BUFFER_ENTRY_COUNT);

		m_impl->m_light_records.resize(CLUSTER_BUFFER_ENTRY_COUNT_MAX);  // light records per cluster (~256 KiB)
		m_impl->m_cluster_sharded_data.resize(GROUP_COUNT);				// cluster thread data (~256 KiB)
	}

	void Froxelizer::update_viewport()
	{
		m_frustum.m_near = m_light_near;
		m_frustum.m_far = m_light_far;

		m_frustum.resize(vec2(m_viewport.size));

		m_pz = { 0.f, 0.f, -m_frustum.m_linearizer, float(m_frustum.m_subdiv_z) };
		if(SUPPORTS_REMAPPED_CLUSTERS)
		{
			m_pf.x = uint32_t(m_frustum.m_subdiv_z);
			m_pf.y = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_z);
			m_pf.z = 1;
		}
		else
		{
			m_pf.x = 1;
			m_pf.y = uint32_t(m_frustum.m_subdiv_x);
			m_pf.z = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y);
		}
	}

	void Froxelizer::update_projection()
	{
		m_frustum.recompute(m_proj, vec2(m_viewport.size));

		//    linearizer = log2(zLightFar / zLightNear) / (zcount - 1)
		//    vz = -exp2((i - zcount) * linearizer) * zLightFar
		// => i = log2(zLightFar / -vz) / -linearizer + zcount
		
		float Pz = m_proj[2][2];
		float Pw = m_proj[3][2];
		if(m_proj[2][3] != 0)
		{
			// perspective projection
			// (clip) cz = Pz*vz+Pw, cw=-vz
			// (ndc)  nz = -Pz-Pw/vz
			// (win)  fz = -Pz*0.5+0.5 - Pw*0.5/vz
			// ->  = vz = -Pw / (2*fz + Pz-1)
			// i = log2(zLightFar*(2*fz + Pz-1) / Pw) / -linearizer + zcount
			m_pz[0] = 2.0f * m_light_far / Pw;
			m_pz[1] = m_light_far * (Pz - 1.0f) / Pw;
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

			m_pz[0] = -2.0f / (Pz * m_light_far);
			m_pz[1] = (1.0f + Pw) / (Pz * m_light_far);
			m_pz[2] = m_frustum.m_linearizer;
		}

		if(m_debug_clusters.size() > 0)
			this->compute_clusters();
	}

	bool Froxelizer::update()
	{
		bool uniformsNeedUpdating = false;
		if(m_dirty & uint8_t(Dirty::Viewport)) // [[unlikely]] 
		{
			update_viewport();
			uniformsNeedUpdating = true;
		}

		if(m_dirty & uint8_t(Dirty::Projection) | uint8_t(Dirty::Viewport)) // [[unlikely]] 
		{
			update_projection();
			uniformsNeedUpdating = true;
		}
		assert(m_light_near >= m_near);
		m_dirty = 0;
		return uniformsNeedUpdating;
	}

	void Froxelizer::compute_clusters()
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
		m_impl->m_clusters.m_memory = bgfx::copy(m_impl->m_clusters.m_data.data(), uint32_t(sizeof(FroxelEntry) * m_impl->m_clusters.m_data.size()));
		m_impl->m_records.m_memory = bgfx::copy(m_impl->m_records.m_data.data(), uint32_t(sizeof(RecordBufferType) * m_impl->m_records.m_data.size()));

		// send data to GPU
		m_impl->m_clusters.m_buffer.commit(m_impl->m_clusters.m_memory);
		m_impl->m_records.m_buffer.commit(m_impl->m_records.m_memory);
	}

	struct refl_ GpuClusters
	{
		attr_ gpu_ vec2 inv_tile_size;
		attr_ gpu_ vec2 viewport_pos;
		attr_ gpu_ vec3 params_f;
		attr_ gpu_ vec4 params_z;
	};

	void Froxelizer::submit(const Pass& pass) const
	{
		uint32_t records = uint32_t(TextureSampler::LightRecords);
		uint32_t clusters = uint32_t(TextureSampler::Clusters);

		bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.s_light_records, &records);
		bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.s_light_clusters, &clusters);

		auto submit = [=](vec4 params, vec4 f, vec4 z)
		{
			bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.u_cluster_p0, &params);
			bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.u_cluster_f, &f);
			bgfx::setViewUniform(pass.m_index, m_impl->m_uniform.u_cluster_z, &z);
		};

		submit(vec4(m_frustum.m_inv_tile_size, vec2(m_viewport.pos)), vec4(vec3(m_pf), 0.f), m_pz);
	}

	void Froxelizer::submit(bgfx::Encoder& encoder) const
	{
		encoder.setTexture(uint8_t(TextureSampler::LightRecords), m_impl->m_records.m_buffer.m_texture);
		encoder.setTexture(uint8_t(TextureSampler::Clusters), m_impl->m_clusters.m_buffer.m_texture);
	}

	void Froxelizer::clusterize_lights(const Camera& camera, span<Light*> lights)
	{
		// note: this is called asynchronously
		clusterize_loop(camera, lights);
		clusterize_assign_records_compress(uint32_t(lights.size()));
	}

	void Froxelizer::clusterize_light_group(const Camera& camera, span<Light*> lights, uint32_t offset, uint32_t stride)
	{
		const mat4& projection = m_proj;

		for(uint32_t i = offset; i < lights.size(); i += stride)
		{
			vec3 position = mulp(camera.m_view, lights[i]->m_node->position());
			vec3 direction = muln(camera.m_view, lights[i]->m_node->direction());

			float cos2 = sq(cos(to_radians(lights[i]->m_spot_angle)));
			float invsin = 1.f / std::sqrt(1.f - cos2);

			LightParams light = { position, cos2, direction, invsin, lights[i]->m_range };

			const uint32_t group = i % GROUP_COUNT;
			const uint32_t bit = i / GROUP_COUNT;
			assert(bit < LIGHT_PER_GROUP);

			FroxelThreadData& threadData = m_impl->m_cluster_sharded_data[group];
			const bool isSpot = light.invSin != std::numeric_limits<float>::infinity();
			threadData[0] |= isSpot << bit;
			clusterize_light(m_frustum, threadData, bit, projection, m_near, light, m_light_far);
		}
	}

#define TWO_THREADED

	void Froxelizer::clusterize_loop(const Camera& camera, span<Light*> lights)
	{
		memset(m_impl->m_cluster_sharded_data.data(), 0, m_impl->m_cluster_sharded_data.size() * sizeof(FroxelThreadData));

#ifdef TWO_THREADED
		JobSystem& js = *m_gfx.m_job_system;
		Job* parent = js.job();
		for(uint32_t i = 0; i < GROUP_COUNT; i++)
		{
			auto task = [=, &camera](JobSystem&, Job*) { this->clusterize_light_group(camera, lights, i, GROUP_COUNT); };
			js.run(js.job(parent, task));
		}
		js.complete(parent);
#else
		for(uint32_t i = 0; i < GROUP_COUNT; i++)
			this->clusterize_light_group(camera, lights, i, GROUP_COUNT);
#endif
	}

	void Froxelizer::clusterize_assign_records_compress(uint32_t num_lights)
	{
		UNUSED(num_lights);

		auto inspect = [&]()
		{
			uint32_t i = 0;
			for(FroxelEntry& entry : m_impl->m_clusters.m_data)
			{
				if((entry.count[0] > 0 || entry.count[1] > 0) && entry.offset == 0)
					printf("cluster %i has lights but offset 0\n", int(i));
				i++;
			}
		};
		UNUSED(inspect);

		// convert cluster data from N groups of M bits to LightRecord::Lights, so we can
		// easily compare adjacent clusters, for compaction. The conversion loops below get
		// inlined and vectorized in release builds.

		// keep these two loops separate, it helps the compiler a lot
		LightRecord::Lights spot_lights;

		using container_type = LightRecord::Lights::container_type;
		constexpr uint32_t r = sizeof(container_type) / sizeof(LightGroupType);

		for(uint32_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
		{
			container_type b = m_impl->m_cluster_sharded_data[i * r][0];
			for(uint32_t k = 0; k < r; k++)
				b |= (container_type(m_impl->m_cluster_sharded_data[i * r + k][0]) << (LIGHT_PER_GROUP * k));
			spot_lights.at(i) = b;
		}

		// this gets very well vectorized...
		for(uint32_t j = 1, jc = CLUSTER_BUFFER_ENTRY_COUNT_MAX; j < jc; j++)
		{
			for(uint32_t i = 0; i < LightRecord::Lights::WORLD_COUNT; i++)
			{
				container_type b = m_impl->m_cluster_sharded_data[i * r][j];
				for(uint32_t k = 0; k < r; k++)
					b |= (container_type(m_impl->m_cluster_sharded_data[i * r + k][j]) << (LIGHT_PER_GROUP * k));
				m_impl->m_light_records[j - 1].lights.at(i) = b;
			}
		}

		uint16_t offset = 0;

		auto remap = [stride = uint32_t(m_frustum.m_subdiv_x * m_frustum.m_subdiv_y)](uint32_t i) -> uint32_t
		{
			if(SUPPORTS_REMAPPED_CLUSTERS) {
				// TODO: with the non-square cluster change these would be mask ops instead of divide.
				i = (i % stride) * CONFIG_CLUSTER_SLICE_COUNT + (i / stride);
			}
			return i;
		};

		uint32_t num_clusters = m_frustum.m_cluster_count;
		for(uint32_t cluster = 0; cluster < num_clusters;)
		{
			LightRecord b = m_impl->m_light_records[cluster];
			if(b.lights.none())
			{
				m_impl->m_clusters.m_data[remap(cluster++)].u32 = 0;
				continue;
			}

			// We have a limitation of 255 spot + 255 point lights per cluster.
			uint8_t point_count = uint8_t(min(255U, uint32_t((b.lights & ~spot_lights).count())));
			uint8_t spot_count = uint8_t(min(255U, uint32_t((b.lights &  spot_lights).count())));

			FroxelEntry entry = { offset, point_count, spot_count };

			const uint8_t light_count = entry.count[0] + entry.count[1];

			if(offset + light_count >= RECORD_BUFFER_ENTRY_COUNT) //[[unlikely]]
			{
				// note: instead of dropping clusters we could look for similar records we've already
				// filed up.
				do { // this compiles to memset() when remap() is identity
					m_impl->m_clusters.m_data[remap(cluster++)].u32 = 0;
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
				// (this is a limitation of the data type used to store the light counts per cluster)
				i += (i - s < 255) ? 1 : 0;

//#ifndef USE_STD_BITSET
#if 0
			});
#else
			}
#endif

			offset += light_count;

			do {
				m_impl->m_clusters.m_data[remap(cluster++)].u32 = entry.u32;
				if(cluster >= num_clusters) break;

				if(m_impl->m_light_records[cluster].lights != b.lights && cluster >= m_frustum.m_subdiv_x)
				{
					// if this cluster record doesn't match the previous one on its left,
					// we re-try with the record above it, which saves many cluster records
					// (north of 10% in practice).
					b = m_impl->m_light_records[cluster - m_frustum.m_subdiv_x];
					entry.u32 = m_impl->m_clusters.m_data[remap(cluster - m_frustum.m_subdiv_x)].u32;
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
		// find a reasonable bounding-box in cluster space for the sphere by projecting
		// it's (clipped) bounding-box to clip-space and converting to cluster indices.
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

	void clusterize_light(ClusteredFrustum& frustum, FroxelThreadData& clusterThread, uint32_t bit, const mat4& projection, float near, const LightParams& light, float light_far)
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
								// see if this cluster intersects the cone
								bool intersect = sphere_cone_intersection(frustum.m_bounding_spheres[fi - 1], light.position, light.axis, light.invSin, light.cosSqr);
								clusterThread[fi++] |= LightGroupType(intersect) << bit;
							}
						}
						else
						{
							// this loops gets vectorized (on arm64) w/ clang
							while(bx++ != ex)
								clusterThread[fi++] |= LightGroupType(1) << bit;
						}
					}
				}
			}
		}
	}
}


module two.gfx;

#include <stl/stddef.h>
#include <stdint.h>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

namespace two
{
	inline Plane bounding_plane(const mat4& mat, Axis component, float dir)
	{
		return {
			mat[0][3] + dir * mat[0][component],
			mat[1][3] + dir * mat[1][component],
			mat[2][3] + dir * mat[2][component],
			mat[3][3] + dir * mat[3][component]
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
		auto torad = [](float d) { return d * c_pi / 180.0f; };

		const float proj_height = tan(torad(fov) * 0.5f);
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
		m_center = vec3(0.f);
		for(uint i = 0; i < 8; i++)
			m_center += m_corners[i];
		//m_center /= 8.f;
		m_center = m_center / 8.f;

		m_radius = 0.f;
		for(uint i = 0; i < 8; i++)
			m_radius = max(distance(m_center, m_corners[i]), m_radius);
	}

	Frustum optimized_frustum(Camera& camera, span<Item*> items)
	{
		if(!camera.m_optimize_ends)
			return Frustum{ camera.m_view, camera.m_fov, camera.m_aspect, camera.m_near, camera.m_far };

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

		return Frustum{ camera.m_view, camera.m_fov, camera.m_aspect, near, far };
	}

	void split_frustum_slices(Camera& camera, span<FrustumSlice*> slices, uint8_t num_splits, float near, float far, float split_distribution)
	{
		const float ratio = far / near;

		for(uint8_t i = 0; i < num_splits; ++i)
		{
			float si = float(int8_t(i * 2 + 1)) / float(num_splits * 2);

			const float split = split_distribution * (near * powf(ratio, si)) + (1 - split_distribution) * (near + (far - near) * si);
			const float slice_near = i == 0 ? near : slices[i - 1]->m_frustum.m_far * 1.005f;
			const float slice_far = i == num_splits - 1 ? far : split;

			Frustum frustum;
			if(camera.m_orthographic)
			{
				vec2 rect = { camera.m_height * camera.m_aspect, camera.m_height };
				frustum = { camera.m_view, rect, slice_near, slice_far };
			}
			else
			{
				frustum = { camera.m_view, camera.m_fov, camera.m_aspect, slice_near, slice_far };
			}

			*slices[i] = { i, frustum };
		}
	}

	void split_frustum_slices(Camera& camera, span<FrustumSlice*> slices, uint8_t num_splits, float split_distribution)
	{
		split_frustum_slices(camera, slices, num_splits, camera.m_near, camera.m_far, split_distribution);
	}
}


module two.gfx;

#include <type_traits>
//#include <limits>
#include <stdint.h>
#include <cassert>

namespace two
{
	
namespace fast {

// fast cos(x), ~8 cycles (vs. 66 cycles on ARM) // can be vectorized // x between -pi and pi
template<typename T>//, typename = typename enable_if<is_floating_point<T>::value>::type>
constexpr T cos(T x) noexcept {
    x *= T(c_invpi / 2);
    x -= T(0.25) + floor(x + T(0.25));
    x *= T(16.0) * abs(x) - T(8.0);
    x += T(0.225) * x * (abs(x) - T(1.0));
    return x;
}

// fast sin(x), ~8 cycles (vs. 66 cycles on ARM) // can be vectorized // x between -pi and pi
template <typename T>//, typename = typename enable_if<is_floating_point<T>::value>::type>
constexpr T sin(T x) noexcept {
    return cos<T>(x - T(c_pi2));
}

constexpr inline float ilog2(float x) noexcept {
    union {
        float val;
        int32_t x;
    } u = { x };
    return ((u.x >> 23) & 0xff) - 127;
}

constexpr inline float log2(float x) noexcept {
    union {
        float val;
        int32_t x;
    } u = { x };
    float ilog2 = float(((u.x >> 23) & 0xff) - 128);
    u.x = (u.x & 0x007fffff) | 0x3f800000;
    return ilog2 + (-0.34484843f * u.val + 2.02466578f) * u.val - 0.67487759f;
}

constexpr double pow(double x, unsigned int y) noexcept {
    return y == 0 ? 1.0 : x * pow(x, y - 1);
}

constexpr unsigned int factorial(unsigned int x) noexcept {
    return x == 0 ? 1 : x * factorial(x - 1);
}

constexpr double exp(double x) noexcept {
    return 1.0 + x + pow(x, 2) / factorial(2) + pow(x, 3) / factorial(3)
                   + pow(x, 4) / factorial(4) + pow(x, 5) / factorial(5)
                   + pow(x, 6) / factorial(6) + pow(x, 7) / factorial(7)
                   + pow(x, 8) / factorial(8) + pow(x, 9) / factorial(9);
}

constexpr float exp(float x) noexcept {
    return float(exp(double(x)));
}

#if defined(__ARM_NEON) && defined(__aarch64__)
inline uint8_t  qadd(uint8_t a,  uint8_t b)  noexcept { return vuqaddb_s8(a, b);  }
inline uint16_t qadd(uint16_t a, uint16_t b) noexcept { return vuqaddh_s16(a, b); }
inline uint32_t qadd(uint32_t a, uint32_t b) noexcept { return vuqadds_s32(a, b); }

inline uint8_t  qsub(uint8_t a,  uint8_t b)  noexcept { return vqsubb_s8(a, b);  }
inline uint16_t qsub(uint16_t a, uint16_t b) noexcept { return vqsubh_s16(a, b); }
inline uint32_t qsub(uint32_t a, uint32_t b) noexcept { return vqsubs_s32(a, b); }
#else
template<typename T>/*, typename = typename enable_if<
        is_same<uint8_t, T>::value ||
        is_same<uint16_t, T>::value ||
        is_same<uint32_t, T>::value>::type>*/
inline T qadd(T a, T b)  noexcept {
    T r = a + b;
    return r | -T(r < a);
}

template<typename T>/*, typename = typename enable_if<
        is_same<uint8_t, T>::value ||
        is_same<uint16_t, T>::value ||
        is_same<uint32_t, T>::value>::type>*/
inline T qsub(T a,  T b)  noexcept {
    T r = a - b;
    return r & -T(r <= a);
}
#endif

template<typename T>
inline T qinc(T a)  noexcept {
    return qadd(a, T(1));
}

template<typename T>
inline T qdec(T a)  noexcept {
    return qsub(a, T(1));
}


}
}

namespace two
{
	void compute_frustum_subdiv(ClusteredFrustum& frustum, vec2 clip_size, size_t slices)
	{
		using stl::swap;
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
		// calculate cluster dimension from CLUSTER_BUFFER_ENTRY_COUNT_MAX and viewport
		// - Start from the maximum number of clusters we can use in the x-y plane
		size_t per_slice = max_clusters / slices;
		// - compute the number of square clusters we need in width and height, rounded down
		//   solving: |  cluster_count_x * cluster_count_y == per_slice
		//            |  cluster_count_x / cluster_count_y == width / height
		size_t count_x = size_t(sqrt(per_slice * clip_size.x / clip_size.y));
		size_t count_y = size_t(sqrt(per_slice * clip_size.y / clip_size.x));
		// - copmute the clusters dimensions, rounded up
		size_t size_x = (size_t(clip_size.x) + count_x - 1) / count_x;
		size_t size_y = (size_t(clip_size.y) + count_y - 1) / count_y;
		// - and since our clusters must be square, only keep the largest dimension
		size_t size = max(size_x, size_y);

		// Here we recompute the cluster counts which may have changed a little due to the rounding
		// and the squareness requirement of clusters
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
		//  = floor((clip + 1) * ((0.5 * dimension) / clustersize))
		//  = floor((clip + 1) * constant
		//  = floor(clip * constant + constant)
		const uint xi = uint(clamp(int(clip.x * m_clip_to_cluster.x + m_clip_to_cluster.x), 0, int(m_subdiv_x - 1)));
		const uint yi = uint(clamp(int(clip.y * m_clip_to_cluster.y + m_clip_to_cluster.y), 0, int(m_subdiv_y - 1)));
		return { xi, yi };
	}

	uint ClusteredFrustum::slice(float z) const
	{
		// The vastly common case is that z<0, so we always do the math for this case
		// and we "undo" it below otherwise. This works because we're using fast::log2 which
		// doesn't care if given a negative number (we'd have to use abs() otherwise).

		// This whole function is now branch-less.

		int s = int((fast::log2(-z) - m_far_log2) * m_linearizer + m_subdiv_z);

		// there are cases where z can be negative here, e.g.:
		// - the light is visible, but its center is behind the camera
		// - the camera's near is behind the camera (e.g. with shadowmap cameras)
		// in that case just return the first slice
		s = z < 0.f ? s : 0U;

		// clamp between [0, m_subdiv_z)
		return uint(clamp(s, 0, int(m_subdiv_z - 1U)));
	}

	Plane to_plane(const vec4& p) { return{ vec3(p), p.w }; }

	Frustum ClusteredFrustum::cluster_frustum(uint x, uint y, uint z) const
	{
		assert(x < m_subdiv_x);
		assert(y < m_subdiv_y);
		assert(z < m_subdiv_z);
		Frustum cluster;
		cluster.m_planes.m_left = to_plane(m_planes_x[x]);
		cluster.m_planes.m_down = to_plane(m_planes_y[y]);
		cluster.m_planes.m_near = to_plane({ 0.f, 0.f, 1.f, -m_distances_z[z] });
		cluster.m_planes.m_right = to_plane(-m_planes_x[x + 1]);
		cluster.m_planes.m_up = to_plane(-m_planes_y[y + 1]);
		cluster.m_planes.m_far = to_plane({ 0.f, 0.f, 1.f, -m_distances_z[z + 1] });
		cluster.m_corners = frustum_corners(cluster.m_planes);
		cluster.compute();
		return cluster;
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
		{
			m_distances_z[i] = m_far * exp2f(float(i - n) * linearizer);
		}

		// for the inverse-transformation (view-space z to z-slice)
		m_linearizer = 1 / linearizer;
		m_far_log2 = log2(m_far);
	}

	void ClusteredFrustum::recompute(const mat4& projection, const vec2& clip_size)
	{
		// clip-space dimensions
		const vec2 cluster_clip_size = (2.0f * vec2(m_tile_size)) / clip_size;
		const mat4 inv_projection = inverse(projection);
		
		auto to_view_space = [](const mat4& inv_projection, vec4 p0, vec4 p1)
		{
			p0 = inv_projection * p0;
			p1 = inv_projection * p1;
			return vec4(normalize(cross(vec3(p1), vec3(p0))), 0.f);
		};

		for(uint16_t i = 0, n = m_subdiv_x; i <= n; ++i)
		{
			float x = (i * cluster_clip_size.x) - 1.0f;
			vec4 p0 = { x, -1, -1, 1 };
			vec4 p1 = { x,  1, -1, 1 };
			m_planes_x[i] = to_view_space(inv_projection, p0, p1);
		}

		for(uint16_t i = 0, n = m_subdiv_y; i <= n; ++i)
		{
			float y = (i * cluster_clip_size.y) - 1.0f;
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

			// near/far planes for all clusters at iz
			planes[4] =  vec4(0.f, 0.f, 1.f, m_distances_z[iz + 0]);
			planes[5] = -vec4(0.f, 0.f, 1.f, m_distances_z[iz + 1]);

			// min/max for z is calculated trivially because near/far planes are parallel to
			// the camera.
			minp.z = -m_distances_z[iz + 1];
			maxp.z = -m_distances_z[iz];
			assert(minp.z < maxp.z);

			for(uint16_t ix = 0; ix < m_subdiv_x; ++ix)
			{
				// left, right planes for all clusters at ix
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
				minMaxX[ix] = vec2(minp.x, maxp.x);
			}

			for(uint16_t iy = 0; iy < m_subdiv_y; ++iy)
			{
				// bottom, top planes for all clusters at iy
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
#ifndef USE_STL
module two.gfx;

namespace stl
{
	using namespace two;
	template class TWO_GFX_EXPORT vector<Texture*>;
	template class TWO_GFX_EXPORT vector<Program*>;
	template class TWO_GFX_EXPORT vector<Material*>;
	template class TWO_GFX_EXPORT vector<Animation*>;
	template class TWO_GFX_EXPORT vector<Rig*>;
	template class TWO_GFX_EXPORT vector<Light*>;
	template class TWO_GFX_EXPORT vector<Mesh*>;
	template class TWO_GFX_EXPORT vector<Model*>;
	template class TWO_GFX_EXPORT vector<Mime*>;
	template class TWO_GFX_EXPORT vector<Flare*>;
	template class TWO_GFX_EXPORT vector<Flow*>;
	template class TWO_GFX_EXPORT vector<Prefab*>;
	template class TWO_GFX_EXPORT vector<Item*>;
	template class TWO_GFX_EXPORT vector<Direct*>;
	template class TWO_GFX_EXPORT vector<Batch*>;
	template class TWO_GFX_EXPORT vector<Sound*>;
	template class TWO_GFX_EXPORT vector<Node3*>;
	template class TWO_GFX_EXPORT vector<ReflectionProbe*>;
	template class TWO_GFX_EXPORT vector<GIProbe*>;
	template class TWO_GFX_EXPORT vector<LightmapAtlas*>;
	template class TWO_GFX_EXPORT vector<LightmapItem*>;
	template class TWO_GFX_EXPORT vector<ImmediateDraw*>;
	template class TWO_GFX_EXPORT vector<Scene*>;
	template class TWO_GFX_EXPORT vector<Viewport*>;
	template class TWO_GFX_EXPORT vector<Importer*>;
	template class TWO_GFX_EXPORT vector<Renderer*>;
	template class TWO_GFX_EXPORT vector<ShaderBlock*>;
	template class TWO_GFX_EXPORT vector<GfxBlock*>;
	template class TWO_GFX_EXPORT vector<DrawBlock*>;
	template class TWO_GFX_EXPORT vector<GfxWindow*>;
	template class TWO_GFX_EXPORT vector<GfxSystem*>;
	template class TWO_GFX_EXPORT vector<Vertex>;
	template class TWO_GFX_EXPORT vector<ShapeVertex>;
	template class TWO_GFX_EXPORT vector<Tri>;
	template class TWO_GFX_EXPORT vector<ModelElem>;
	template class TWO_GFX_EXPORT vector<Item>;
	template class TWO_GFX_EXPORT vector<Direct>;
	//template class TWO_GFX_EXPORT vector<Direct::Batch>;
	template class TWO_GFX_EXPORT vector<Node3>;
	template class TWO_GFX_EXPORT vector<Joint>;
	template class TWO_GFX_EXPORT vector<Skin>;
	template class TWO_GFX_EXPORT vector<ShaderDefine>;
	template class TWO_GFX_EXPORT vector<PassJob>;
	template class TWO_GFX_EXPORT vector<Prefab::Elem>;
	template class TWO_GFX_EXPORT vector<Mesh::Morph>;
	template class TWO_GFX_EXPORT vector<Rig::MorphWeight>;
	template class TWO_GFX_EXPORT vector<AnimNode>;
	template class TWO_GFX_EXPORT vector<AnimTrack>;
	template class TWO_GFX_EXPORT vector<AnimTrack::Key>;
	template class TWO_GFX_EXPORT vector<AnimPlay>;
	template class TWO_GFX_EXPORT vector<AnimPlay::Track>;
	template class TWO_GFX_EXPORT vector<Particle>;
	template class TWO_GFX_EXPORT vector<ParticleSort>;
	template class TWO_GFX_EXPORT vector<Viewport::RenderTask>;
	template class TWO_GFX_EXPORT vector<ImmediateDraw::Batch>;
	template class TWO_GFX_EXPORT vector<ImmediateDraw::Vertex>;
	template class TWO_GFX_EXPORT vector<Lines::Segment>;
	template class TWO_GFX_EXPORT vector<Import::Item>;
	template class TWO_GFX_EXPORT vector<DrawElement>;
	template class TWO_GFX_EXPORT vector<Frustum>;
	//template class TWO_GFX_EXPORT vector<LightRecord>;
	template class TWO_GFX_EXPORT vector<Froxelizer::FroxelEntry>;
	template class TWO_GFX_EXPORT vector<array<uint, 8193>>;
	template class TWO_GFX_EXPORT vector<unique<Gnode>>;
	template class TWO_GFX_EXPORT vector<unique<GfxBlock>>;
	template class TWO_GFX_EXPORT vector<unique<Picker>>;
	template class TWO_GFX_EXPORT vector<vector<float>>;
	template class TWO_GFX_EXPORT unordered_map<int, Skeleton*>;
	template class TWO_GFX_EXPORT unordered_map<string, Material*>;
	template class TWO_GFX_EXPORT unordered_set<Model*>;
	template class TWO_GFX_EXPORT vector<function<void(Texture&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Material&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Program&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Model&, const string&, const ImportConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Flow&, const string&, const NoConfig&)>>;
	template class TWO_GFX_EXPORT vector<function<void(Prefab&, const string&, const ImportConfig&)>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Texture>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Material>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Program>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Model>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Flow>>;
	template class TWO_GFX_EXPORT unordered_map<string, unique<Prefab>>;
	template class TWO_GFX_EXPORT unordered_map<uint32_t, uint32_t>;
	template class TWO_GFX_EXPORT unordered_map<uint64_t, Program::Version>;
	template class TWO_GFX_EXPORT unordered_map<string, bgfx::UniformHandle>;

	template class TWO_GFX_EXPORT vector<bgfx::InstanceDataBuffer>;
	template class TWO_GFX_EXPORT unordered_map<uint, bgfx::VertexDecl>;
}
#endif

module two.gfx;

namespace two
{
    // Exported types
    template <> TWO_GFX_EXPORT Type& type<two::AnimTarget>() { static Type ty("AnimTarget", sizeof(two::AnimTarget)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Interpolation>() { static Type ty("Interpolation", sizeof(two::Interpolation)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureHint>() { static Type ty("TextureHint", sizeof(two::TextureHint)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureFormat>() { static Type ty("TextureFormat", sizeof(two::TextureFormat)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderType>() { static Type ty("ShaderType", sizeof(two::ShaderType)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PassType>() { static Type ty("PassType", sizeof(two::PassType)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialBlock>() { static Type ty("MaterialBlock", sizeof(two::MaterialBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureSampler>() { static Type ty("TextureSampler", sizeof(two::TextureSampler)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Lighting>() { static Type ty("Lighting", sizeof(two::Lighting)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlendMode>() { static Type ty("BlendMode", sizeof(two::BlendMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::CullMode>() { static Type ty("CullMode", sizeof(two::CullMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthDraw>() { static Type ty("DepthDraw", sizeof(two::DepthDraw)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthTest>() { static Type ty("DepthTest", sizeof(two::DepthTest)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialFlag>() { static Type ty("MaterialFlag", sizeof(two::MaterialFlag)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderColor>() { static Type ty("ShaderColor", sizeof(two::ShaderColor)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TextureChannel>() { static Type ty("TextureChannel", sizeof(two::TextureChannel)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PbrDiffuseMode>() { static Type ty("PbrDiffuseMode", sizeof(two::PbrDiffuseMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PbrSpecularMode>() { static Type ty("PbrSpecularMode", sizeof(two::PbrSpecularMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::PhongEnvBlendMode>() { static Type ty("PhongEnvBlendMode", sizeof(two::PhongEnvBlendMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::EmitterFlow>() { static Type ty("EmitterFlow", sizeof(two::EmitterFlow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ItemShadow>() { static Type ty("ItemShadow", sizeof(two::ItemShadow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ModelFormat>() { static Type ty("ModelFormat", sizeof(two::ModelFormat)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::IsometricAngle>() { static Type ty("IsometricAngle", sizeof(two::IsometricAngle)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthMethod>() { static Type ty("DepthMethod", sizeof(two::DepthMethod)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::LightType>() { static Type ty("LightType", sizeof(two::LightType)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShadowFlags>() { static Type ty("ShadowFlags", sizeof(two::ShadowFlags)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MSAA>() { static Type ty("MSAA", sizeof(two::MSAA)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Shading>() { static Type ty("Shading", sizeof(two::Shading)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BackgroundMode>() { static Type ty("BackgroundMode", sizeof(two::BackgroundMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Month>() { static Type ty("Month", sizeof(two::Month)); return ty; }
    
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::mat4>>() { static Type ty("span<two::mat4>", sizeof(stl::span<two::mat4>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Node3>>() { static Type ty("span<two::Node3>", sizeof(stl::span<two::Node3>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Item>>() { static Type ty("span<two::Item>", sizeof(stl::span<two::Item>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Batch>>() { static Type ty("span<two::Batch>", sizeof(stl::span<two::Batch>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Direct>>() { static Type ty("span<two::Direct>", sizeof(stl::span<two::Direct>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Mime>>() { static Type ty("span<two::Mime>", sizeof(stl::span<two::Mime>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Light>>() { static Type ty("span<two::Light>", sizeof(stl::span<two::Light>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Flare>>() { static Type ty("span<two::Flare>", sizeof(stl::span<two::Flare>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::span<two::Texture*>>() { static Type ty("span<two::Texture*>", sizeof(stl::span<two::Texture*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Mesh*>>() { static Type ty("vector<two::Mesh*>", sizeof(stl::vector<two::Mesh*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Model*>>() { static Type ty("vector<two::Model*>", sizeof(stl::vector<two::Model*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Texture*>>() { static Type ty("vector<two::Texture*>", sizeof(stl::vector<two::Texture*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Material*>>() { static Type ty("vector<two::Material*>", sizeof(stl::vector<two::Material*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::Animation*>>() { static Type ty("vector<two::Animation*>", sizeof(stl::vector<two::Animation*>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<stl::vector<two::AnimPlay>>() { static Type ty("vector<two::AnimPlay>", sizeof(stl::vector<two::AnimPlay>)); return ty; }
    
    template <> TWO_GFX_EXPORT Type& type<two::Node3>() { static Type ty("Node3", sizeof(two::Node3)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AnimTrack>() { static Type ty("AnimTrack", sizeof(two::AnimTrack)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Animation>() { static Type ty("Animation", sizeof(two::Animation)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Texture>() { static Type ty("Texture", sizeof(two::Texture)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Skeleton>() { static Type ty("Skeleton", sizeof(two::Skeleton)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Joint>() { static Type ty("Joint", sizeof(two::Joint)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Skin>() { static Type ty("Skin", sizeof(two::Skin)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Rig>() { static Type ty("Rig", sizeof(two::Rig)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AnimNode>() { static Type ty("AnimNode", sizeof(two::AnimNode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AnimPlay>() { static Type ty("AnimPlay", sizeof(two::AnimPlay)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Mime>() { static Type ty("Mime", sizeof(two::Mime)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderDefine>() { static Type ty("ShaderDefine", sizeof(two::ShaderDefine)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ShaderBlock>() { static Type ty("ShaderBlock", sizeof(two::ShaderBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ProgramMode>() { static Type ty("ProgramMode", sizeof(two::ProgramMode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ProgramBlock>() { static Type ty("ProgramBlock", sizeof(two::ProgramBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Program>() { static Type ty("Program", sizeof(two::Program)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Frustum>() { static Type ty("Frustum", sizeof(two::Frustum)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::FrustumSlice>() { static Type ty("FrustumSlice", sizeof(two::FrustumSlice)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ProgramVersion>() { static Type ty("ProgramVersion", sizeof(two::ProgramVersion)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Shot>() { static Type ty("Shot", sizeof(two::Shot)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Pass>() { static Type ty("Pass", sizeof(two::Pass)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::RenderFrame>() { static Type ty("RenderFrame", sizeof(two::RenderFrame)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Render>() { static Type ty("Render", sizeof(two::Render)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GfxBlock>() { static Type ty("GfxBlock", type<two::ShaderBlock>(), sizeof(two::GfxBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DrawBlock>() { static Type ty("DrawBlock", type<two::GfxBlock>(), sizeof(two::DrawBlock)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Renderer>() { static Type ty("Renderer", sizeof(two::Renderer)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::Colour>>() { static Type ty("MaterialParam<two::Colour>", sizeof(two::MaterialParam<two::Colour>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<float>>() { static Type ty("MaterialParam<float>", sizeof(two::MaterialParam<float>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialParam<two::vec4>>() { static Type ty("MaterialParam<two::vec4>", sizeof(two::MaterialParam<two::vec4>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialBase>() { static Type ty("MaterialBase", sizeof(two::MaterialBase)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialUser>() { static Type ty("MaterialUser", sizeof(two::MaterialUser)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialAlpha>() { static Type ty("MaterialAlpha", sizeof(two::MaterialAlpha)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialSolid>() { static Type ty("MaterialSolid", sizeof(two::MaterialSolid)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPoint>() { static Type ty("MaterialPoint", sizeof(two::MaterialPoint)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialLine>() { static Type ty("MaterialLine", sizeof(two::MaterialLine)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialFresnel>() { static Type ty("MaterialFresnel", sizeof(two::MaterialFresnel)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialLit>() { static Type ty("MaterialLit", sizeof(two::MaterialLit)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPbr>() { static Type ty("MaterialPbr", sizeof(two::MaterialPbr)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MaterialPhong>() { static Type ty("MaterialPhong", sizeof(two::MaterialPhong)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockMaterial>() { static Type ty("BlockMaterial", type<two::GfxBlock>(), sizeof(two::BlockMaterial)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Material>() { static Type ty("Material", sizeof(two::Material)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ModelElem>() { static Type ty("ModelElem", sizeof(two::ModelElem)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Model>() { static Type ty("Model", sizeof(two::Model)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Flow>() { static Type ty("Flow", sizeof(two::Flow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Flare>() { static Type ty("Flare", type<two::Flow>(), sizeof(two::Flare)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockParticles>() { static Type ty("BlockParticles", type<two::GfxBlock>(), sizeof(two::BlockParticles)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Batch>() { static Type ty("Batch", sizeof(two::Batch)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Item>() { static Type ty("Item", sizeof(two::Item)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ImportConfig>() { static Type ty("ImportConfig", sizeof(two::ImportConfig)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Import>() { static Type ty("Import", sizeof(two::Import)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Prefab>() { static Type ty("Prefab", sizeof(two::Prefab)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Texture>>() { static Type ty("AssetStore<two::Texture>", sizeof(two::AssetStore<two::Texture>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Program>>() { static Type ty("AssetStore<two::Program>", sizeof(two::AssetStore<two::Program>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Material>>() { static Type ty("AssetStore<two::Material>", sizeof(two::AssetStore<two::Material>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Model>>() { static Type ty("AssetStore<two::Model>", sizeof(two::AssetStore<two::Model>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Flow>>() { static Type ty("AssetStore<two::Flow>", sizeof(two::AssetStore<two::Flow>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::AssetStore<two::Prefab>>() { static Type ty("AssetStore<two::Prefab>", sizeof(two::AssetStore<two::Prefab>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Camera>() { static Type ty("Camera", sizeof(two::Camera)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::MirrorCamera>() { static Type ty("MirrorCamera", sizeof(two::MirrorCamera)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DepthParams>() { static Type ty("DepthParams", sizeof(two::DepthParams)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::DistanceParams>() { static Type ty("DistanceParams", sizeof(two::DistanceParams)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockDepth>() { static Type ty("BlockDepth", type<two::DrawBlock>(), sizeof(two::BlockDepth)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GpuMesh>() { static Type ty("GpuMesh", sizeof(two::GpuMesh)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Mesh>() { static Type ty("Mesh", sizeof(two::Mesh)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Direct>() { static Type ty("Direct", sizeof(two::Direct)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ImmediateDraw>() { static Type ty("ImmediateDraw", sizeof(two::ImmediateDraw)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::SymbolIndex>() { static Type ty("SymbolIndex", sizeof(two::SymbolIndex)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Lines>() { static Type ty("Lines", sizeof(two::Lines)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockFilter>() { static Type ty("BlockFilter", type<two::GfxBlock>(), sizeof(two::BlockFilter)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockCopy>() { static Type ty("BlockCopy", type<two::GfxBlock>(), sizeof(two::BlockCopy)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::ClusteredFrustum>() { static Type ty("ClusteredFrustum", type<two::Frustum>(), sizeof(two::ClusteredFrustum)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Light>() { static Type ty("Light", sizeof(two::Light)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GfxWindow>() { static Type ty("GfxWindow", sizeof(two::GfxWindow)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::GfxSystem>() { static Type ty("GfxSystem", type<two::BgfxSystem>(), sizeof(two::GfxSystem)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Gnode>() { static Type ty("Gnode", sizeof(two::Gnode)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Node3>>() { static Type ty("TPool<two::Node3>", sizeof(two::TPool<two::Node3>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Item>>() { static Type ty("TPool<two::Item>", sizeof(two::TPool<two::Item>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Batch>>() { static Type ty("TPool<two::Batch>", sizeof(two::TPool<two::Batch>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Direct>>() { static Type ty("TPool<two::Direct>", sizeof(two::TPool<two::Direct>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Mime>>() { static Type ty("TPool<two::Mime>", sizeof(two::TPool<two::Mime>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Light>>() { static Type ty("TPool<two::Light>", sizeof(two::TPool<two::Light>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::TPool<two::Flare>>() { static Type ty("TPool<two::Flare>", sizeof(two::TPool<two::Flare>)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Culler>() { static Type ty("Culler", sizeof(two::Culler)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Viewport>() { static Type ty("Viewport", type<two::OEntt>(), sizeof(two::Viewport)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::RenderQuad>() { static Type ty("RenderQuad", sizeof(two::RenderQuad)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::FrameBuffer>() { static Type ty("FrameBuffer", sizeof(two::FrameBuffer)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::SwapBuffer>() { static Type ty("SwapBuffer", sizeof(two::SwapBuffer)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Cascade>() { static Type ty("Cascade", sizeof(two::Cascade)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::SwapCascade>() { static Type ty("SwapCascade", sizeof(two::SwapCascade)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::RenderTarget>() { static Type ty("RenderTarget", type<two::FrameBuffer>(), sizeof(two::RenderTarget)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Sun>() { static Type ty("Sun", sizeof(two::Sun)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Radiance>() { static Type ty("Radiance", sizeof(two::Radiance)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Background>() { static Type ty("Background", sizeof(two::Background)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Skylight>() { static Type ty("Skylight", sizeof(two::Skylight)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Fog>() { static Type ty("Fog", sizeof(two::Fog)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Zone>() { static Type ty("Zone", sizeof(two::Zone)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::Scene>() { static Type ty("Scene", sizeof(two::Scene)); return ty; }
    template <> TWO_GFX_EXPORT Type& type<two::BlockSky>() { static Type ty("BlockSky", type<two::GfxBlock>(), sizeof(two::BlockSky)); return ty; }
}


#include <bx/timer.h>
#include <bx/file.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

module two.gfx;

#include <Tracy.hpp>

//#define TWO_GFX_THREADED
#define POLL_AT_END 0

namespace two
{
	struct GfxSystem::Impl
	{
		vector<string> m_resource_paths;

		vector<GfxWindow*> m_contexts;
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
		unique<AssetStore<Flow>> m_particles;
		unique<AssetStore<Prefab>> m_prefabs;

		table<ModelFormat, Importer*> m_importers;
		table<Shading, RenderFunc> m_renderers;

		Texture* m_white_texture = nullptr;
		Texture* m_black_texture = nullptr;
		Texture* m_normal_texture = nullptr;

		SymbolIndex m_symbols;

#ifdef TWO_GFX_THREADED
		vector<bgfx::Encoder*> m_encoders;
#endif
	};

	GfxWindow::GfxWindow(GfxSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main)
		: BgfxContext(gfx, name, size, fullscreen, main, false)
		, m_gfx(gfx)
		, m_target()
	{
		if(!gfx.m_initialized)
			gfx.init(*this);
		m_target = oconstruct<RenderTarget>(size, main ? nullptr : m_native_handle);
		gfx.m_impl->m_contexts.push_back(this);
	}

	GfxWindow::~GfxWindow()
	{}

	void GfxWindow::reset_fb(const uvec2& size)
	{
		bgfx::reset(uint16_t(size.x), uint16_t(size.y), BGFX_RESET_NONE);
		if(size.x == 0 || size.y == 0)
			m_target = nullptr;
		else
		{
			if(!m_target || size != m_target->m_size)
				m_target = oconstruct<RenderTarget>(size);
		}
		m_vg_handle = m_reset_vg(*this, *m_vg);
	}

	GfxSystem::GfxSystem(const string& resource_path)
		: BgfxSystem(resource_path)
		, m_impl(make_unique<Impl>())
		, m_renderer(*this)
	{
		Program::ms_gfx = this;
		Material::ms_gfx = this;
		Model::ms_gfx = this;

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
	AssetStore<Flow>& GfxSystem::flows() { return *m_impl->m_particles; }
	AssetStore<Prefab>& GfxSystem::prefabs() { return *m_impl->m_prefabs; }

	void GfxSystem::add_importer(ModelFormat format, Importer& importer)
	{
		m_impl->m_importers[format] = &importer;
	}

	Importer* GfxSystem::importer(ModelFormat format)
	{
		return m_impl->m_importers[format];
	}

	void GfxSystem::init(GfxWindow& context)
	{
		BgfxSystem::init(context);

		m_flip_y = bgfx::getCaps()->originBottomLeft;

		m_impl->m_meshes = make_unique<TPool<Mesh>>();
		m_impl->m_rigs = make_unique<TPool<Rig>>();
		m_impl->m_animations = make_unique<TPool<Animation>>();
		
		auto load_tex = [&](Texture& texture, const string& path, const NoConfig& config) { load_texture(*this, texture, path); };

		m_impl->m_textures = make_unique<AssetStore<Texture>>(*this, "textures/", load_tex);
		m_impl->m_programs = make_unique<AssetStore<Program>>(*this, "programs/", ".prg");
		m_impl->m_materials = make_unique<AssetStore<Material>>(*this, "materials/", ".mtl");
		m_impl->m_models = make_unique<AssetStore<Model>>(*this, "models/");
		m_impl->m_particles = make_unique<AssetStore<Flow>>(*this, "particles/", ".ptc");
		//m_impl->m_prefabs = make_unique<AssetStore<Prefab>>(*this, "prefabs/", ".pfb");
		m_impl->m_prefabs = make_unique<AssetStore<Prefab>>(*this, "models/");

		m_impl->m_white_texture = this->textures().file("white.png");
		m_impl->m_black_texture = this->textures().file("black.png");
		m_impl->m_normal_texture = this->textures().file("normal.png");

		// create point mesh
		{
			MeshPacker geometry;

			geometry.m_primitive = PrimitiveType::Triangles;

			geometry.m_positions = { vec3(-1, 1, 0), vec3(-1, -1, 0), vec3(1, -1, 0), vec3(1, 1, 0) };
			geometry.m_uv0s = { vec2(0, 1), vec2(0, 0), vec2(1, 0), vec2(1, 1) };
			geometry.m_indices = { 0, 1, 2, 2, 3, 0 };

			this->create_model_geo("point", geometry);
		}

		// create fat line mesh
		{
			MeshPacker geometry;

			geometry.m_positions = { vec3(-1, 2, 0), vec3(1, 2, 0), vec3(-1, 1, 0), vec3(1, 1, 0), vec3(-1, 0, 0), vec3(1, 0, 0), vec3(-1, -1, 0), vec3(1, -1, 0) };
			geometry.m_uv0s = { vec2(-1, 2), vec2(1, 2), vec2(-1, 1), vec2(1, 1), vec2(-1, -1), vec2(1, -1), vec2(-1, -2), vec2(1, -2) };
			geometry.m_indices = { 0, 2, 1, 2, 3, 1, 2, 4, 3, 4, 5, 3, 4, 6, 5, 6, 7, 5 };

			this->create_model_geo("line", geometry);
		}
	}

	void GfxSystem::default_pipeline()
	{
		this->init_pipeline(pipeline_minimal);
	}

	void GfxSystem::init_pipeline(PipelineDecl decl)
	{
#ifdef TWO_GFX_DEFERRED
		decl(*this, m_renderer, true);
#else
		decl(*this, m_renderer, false);
#endif

		for(auto& block : m_renderer.m_gfx_blocks)
			block->init_block();

		this->set_renderer(Shading::Solid, render_solid);
		this->set_renderer(Shading::Clear, render_clear);

		this->create_debug_materials();
	}

	void GfxSystem::add_resource_path(const string& path, bool relative)
	{
		printf("[info] gfx - resource path: %s\n", path.c_str());
		m_impl->m_resource_paths.push_back(relative ? m_resource_path + "/" + path : path);
	}

	void GfxSystem::set_renderer(Shading shading, const RenderFunc& renderer)
	{
		m_impl->m_renderers[shading] = renderer;
	}

	RenderFunc GfxSystem::renderer(Shading shading)
	{
		return *m_impl->m_renderers[shading];
	}

	GfxWindow& GfxSystem::context(size_t index)
	{
		return *m_impl->m_contexts[index];
	}

	RenderTarget& GfxSystem::main_target()
	{
		return *this->context(0).m_target;
	}

	bool GfxSystem::begin_frame()
	{
		m_render_frame = { m_frame, m_time, m_delta_time, Render::s_render_pass_id };

		{
			ZoneScopedNC("programs", tracy::Color::Cyan);

			for(Program* program : m_impl->m_programs->m_vector)
				program->update(*this);
		}

		{
			ZoneScopedNC("renderers", tracy::Color::Cyan);

			for(auto& block : m_renderer.m_gfx_blocks)
				block->begin_frame(m_render_frame);
		}

		bool pursue = true;
		{
			ZoneScopedNC("gfx contexts begin", tracy::Color::Cyan);
		
			for(GfxWindow* context : m_impl->m_contexts)
				pursue &= context->begin_frame();
		}

#ifdef TWO_GFX_THREADED
		{
			ZoneScopedNC("gfx begin", tracy::Color::Cyan);

			m_num_encoders = min(uint32_t(4U), bgfx::getCaps()->limits.maxEncoders);

			m_encoders[0] = bgfx::begin();
			for(size_t i = 1; i < m_num_encoders; ++i)
				m_encoders[i] = bgfx::begin(true);
		}
#endif

		return pursue;
	}

	void GfxSystem::render_contexts()
	{
		for(GfxWindow* context : m_impl->m_contexts)
			for(Viewport* viewport : context->m_viewports)
				if(viewport->m_autorender)
				{
					ZoneScopedNC("gfx viewport", tracy::Color::Cyan);

					RenderFunc renderer = this->renderer(viewport->m_shading);
					this->render(viewport->m_shading, renderer, *context->m_target, *viewport);
				}
	}

	void GfxSystem::end_frame()
	{
		{
			ZoneScopedNC("gfx contexts render", tracy::Color::Cyan);

			for(GfxWindow* context : m_impl->m_contexts)
				context->render_frame();
		}

#ifdef TWO_GFX_THREADED
		{
			ZoneScopedNC("gfx end", tracy::Color::Cyan);

			for(size_t i = 1; i < m_num_encoders; ++i)
				bgfx::end(m_encoders[i]);
		}
#endif

		{
			ZoneScopedNC("gfx contexts end", tracy::Color::Cyan);
		
			for(GfxWindow* context : m_impl->m_contexts)
				context->end_frame();
		}

		for(Program* program : m_impl->m_programs->m_vector)
			program->update(*this);

		{
			ZoneScopedNC("gfx frame", tracy::Color::Cyan);
			BgfxSystem::end_frame();
		}

		for(Program* program : m_impl->m_programs->m_vector)
			program->update(*this);
	}

	void GfxSystem::render(Shading shading, RenderFunc renderer, RenderTarget& target, Viewport& viewport)
	{
		Render render = { shading, viewport, target, m_render_frame };
		m_renderer.submit(render, renderer);
	}

	RenderFrame GfxSystem::render_frame()
	{
		return { m_frame, m_time, m_delta_time, Render::s_render_pass_id };
	}

	LocatedFile GfxSystem::locate_file(const string& file, span<string> extensions)
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
		return this->locate_file(file, { "" });
	}

	Texture& GfxSystem::default_texture(TextureHint hint)
	{
		if(hint == TextureHint::Black)
			return *m_impl->m_black_texture;
		else if(hint == TextureHint::White)
			return *m_impl->m_white_texture;
		else if(hint == TextureHint::Normal || true)
			return *m_impl->m_normal_texture;
	}

	void GfxSystem::create_debug_materials()
	{
		Material& debug = this->fetch_material("debug", "solid");
		UNUSED(debug);

		Material& alpha = this->fetch_material("debug_alpha", "solid");
		alpha.m_solid.m_colour = Colour(0.2f, 0.1f);

		Material& pbr = this->fetch_material("debug_pbr", "pbr/pbr");
		UNUSED(pbr);
	}

	Model& GfxSystem::create_model(const string& name)
	{
		Model& model = this->models().create(name);
		Mesh& mesh = model.add_mesh(name);

		model.add_item(mesh, bxidentity());
		return model;
	}

	Model& GfxSystem::create_model_geo(const string& name, const MeshPacker& geometry, bool readback, bool optimize)
	{
		Model& model = this->models().create(name);
		Mesh& mesh = model.add_mesh(name, readback);

		mesh.write(geometry, optimize);

		model.add_item(mesh, bxidentity());
		model.prepare();
		return model;
	}

	Model& GfxSystem::create_model_gpu(const string& name, const GpuMesh& gpu_mesh, bool readback, bool optimize)
	{
		Model& model = this->models().create(name);
		Mesh& mesh = model.add_mesh(name, readback);

		mesh.upload(gpu_mesh, optimize);

		model.add_item(mesh, bxidentity());
		model.prepare();
		return model;
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
			auto initializer = [&](Texture& texture) { auto data = image.read32(); texture.load_rgba(image.m_size, data); };

			Texture& texture = this->textures().fetch(image_name);
			initializer(texture);
			material = &this->fetch_material(name, "solid");
			material->m_solid.m_colour = &texture;
		}

		return *material;
	}

	Model& GfxSystem::shape(const Shape& shape, const Symbol& symbol, DrawMode draw_mode)
	{
		return m_impl->m_symbols.symbol_model(symbol, shape, draw_mode);
	}

	Material& GfxSystem::symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		if(symbol.m_image256)
			return this->fetch_image256_material(*symbol.m_image256);
		else
			return m_impl->m_symbols.symbol_material(*this, symbol, draw_mode);
	}

namespace gfx
{
	Model& model_suzanne(GfxSystem& gfx)
	{
		constexpr double position[] = { 0.46875,0.242188,0.757812,0.5,0.09375,0.6875,0.5625,0.242188,0.671875,-0.5,0.09375,0.6875,-0.46875,0.242188,0.757812,-0.5625,0.242188,0.671875,0.546875,0.0546875,0.578125,0.625,0.242188,0.5625,-0.546875,0.0546875,0.578125,-0.625,0.242188,0.5625,0.351562,-0.0234375,0.617188,-0.351562,-0.0234375,0.617188,0.4375,0.164063,0.765625,0.351562,0.03125,0.71875,-0.351562,0.03125,0.71875,-0.4375,0.164063,0.765625,0.351562,0.132813,0.78125,0.203125,0.09375,0.742188,-0.203125,0.09375,0.742188,-0.351562,0.132813,0.78125,0.15625,0.0546875,0.648438,-0.15625,0.0546875,0.648438,0.140625,0.242188,0.742188,-0.140625,0.242188,0.742188,-0.078125,0.242188,0.65625,0.242188,0.242188,0.796875,0.273438,0.164063,0.796875,-0.242188,0.242188,0.796875,0.203125,0.390625,0.742188,-0.203125,0.390625,0.742188,0.078125,0.242188,0.65625,-0.15625,0.4375,0.648438,0.351562,0.453125,0.71875,0.15625,0.4375,0.648438,-0.351562,0.453125,0.71875,-0.351562,0.515625,0.617188,0.351562,0.359375,0.78125,0.273438,0.328125,0.796875,-0.351562,0.359375,0.78125,0.4375,0.328125,0.765625,-0.4375,0.328125,0.765625,-0.5,0.390625,0.6875,0.5,0.390625,0.6875,0.351562,0.515625,0.617188,-0.546875,0.4375,0.578125,0.546875,0.4375,0.578125,0.476562,0.242188,0.773438,-0.476562,0.242188,0.773438,-0.445312,0.335938,0.78125,0.445312,0.335938,0.78125,-0.351562,0.375,0.804688,0.351562,0.375,0.804688,-0.273438,0.328125,0.796875,-0.265625,0.335938,0.820312,0.265625,0.335938,0.820312,-0.226562,0.242188,0.820312,0.265625,0.15625,0.820312,0.226562,0.242188,0.820312,-0.265625,0.15625,0.820312,0.351562,0.117188,0.804688,-0.351562,0.117188,0.804688,-0.273438,0.164063,0.796875,0.445312,0.15625,0.78125,-0.445312,0.15625,0.78125,0.351562,0.242188,0.828125,-0.351562,0.242188,0.828125,0.164062,-0.929688,0.632813,0,-0.984375,0.578125,0.179688,-0.96875,0.554688,-0.164062,-0.929688,0.632813,0,-0.945312,0.640625,0.234375,-0.914062,0.632813,0.328125,-0.945312,0.523438,-0.234375,-0.914062,0.632813,-0.179688,-0.96875,0.554688,0.367188,-0.890625,0.53125,-0.367188,-0.890625,0.53125,-0.328125,-0.945312,0.523438,0.351562,-0.695312,0.570313,0.265625,-0.820312,0.664063,-0.265625,-0.820312,0.664063,-0.351562,-0.695312,0.570313,0.3125,-0.4375,0.570312,0.25,-0.703125,0.6875,-0.25,-0.703125,0.6875,-0.3125,-0.4375,0.570312,0.203125,-0.1875,0.5625,0.398438,-0.046875,0.671875,0.125,-0.101562,0.8125,-0.398438,-0.046875,0.671875,-0.203125,-0.1875,0.5625,-0.125,-0.101562,0.8125,0.632812,-0.0390625,0.539062,0.4375,-0.140625,0.53125,-0.632812,-0.0390625,0.539062,-0.617188,0.0546875,0.625,0.726562,0.203125,0.601562,0.617188,0.0546875,0.625,-0.726562,0.203125,0.601562,0.859375,0.429688,0.59375,0.828125,0.148438,0.445312,-0.859375,0.429688,0.59375,-0.742188,0.375,0.65625,0.710938,0.484375,0.625,0.742188,0.375,0.65625,-0.710938,0.484375,0.625,-0.6875,0.414063,0.726562,0.492188,0.601563,0.6875,0.6875,0.414063,0.726562,-0.492188,0.601563,0.6875,-0.4375,0.546875,0.796875,0.3125,0.640625,0.835938,0.4375,0.546875,0.796875,-0.3125,0.640625,0.835938,0.15625,0.71875,0.757812,0.320312,0.757813,0.734375,-0.15625,0.71875,0.757812,-0.203125,0.617188,0.851562,0.0625,0.492188,0.75,0.203125,0.617188,0.851562,-0.0625,0.492188,0.75,-0.101562,0.429688,0.84375,0,0.429688,0.742188,0.101562,0.429688,0.84375,0,0.351563,0.820312,0.25,0.46875,0.757812,0.164062,0.414063,0.773438,-0.25,0.46875,0.757812,0.328125,0.476563,0.742188,0.429688,0.4375,0.71875,-0.328125,0.476563,0.742188,0.601562,0.375,0.664062,-0.429688,0.4375,0.71875,0.640625,0.296875,0.648438,-0.601562,0.375,0.664062,0.625,0.1875,0.648438,-0.640625,0.296875,0.648438,0.492188,0.0625,0.671875,-0.625,0.1875,0.648438,0.375,0.015625,0.703125,-0.492188,0.0625,0.671875,-0.375,0.015625,0.703125,0,0.046875,0.726562,0.125,0.304688,0.765625,-0.125,0.304688,0.765625,0,0.210938,0.765625,0.132812,0.210938,0.757812,-0.132812,0.210938,0.757812,0.164062,0.140625,0.75,-0.164062,0.140625,0.75,0.0625,-0.882812,0.695313,-0.0625,-0.882812,0.695313,0.117188,-0.835937,0.710938,-0.117188,-0.835937,0.710938,0.109375,-0.71875,0.734375,0.210938,-0.445312,0.710938,0.117188,-0.6875,0.734375,-0.117188,-0.6875,0.734375,-0.210938,-0.445312,0.710938,-0.109375,-0.71875,0.734375,0,-0.328125,0.742188,0.078125,-0.445312,0.75,0.0859375,-0.289062,0.742188,-0.078125,-0.445312,0.75,0,-0.445312,0.75,0,-0.679687,0.734375,0,-0.765625,0.734375,0.125,-0.226562,0.75,0.09375,-0.273437,0.78125,-0.09375,-0.273437,0.78125,-0.125,-0.226562,0.75,-0.0859375,-0.289062,0.742188,0.109375,-0.132812,0.78125,0.101562,-0.148437,0.742188,-0.109375,-0.132812,0.78125,-0.132812,-0.226562,0.796875,0.0390625,-0.125,0.78125,0,-0.140625,0.742188,-0.0390625,-0.125,0.78125,-0.101562,-0.148437,0.742188,0,-0.1875,0.796875,0,-0.195312,0.75,0,-0.320312,0.78125,0,-0.289062,0.804688,-0.078125,-0.25,0.804688,0.046875,-0.148437,0.8125,-0.046875,-0.148437,0.8125,0.09375,-0.15625,0.8125,-0.09375,-0.15625,0.8125,0.132812,-0.226562,0.796875,-0.109375,-0.226562,0.828125,0.078125,-0.25,0.804688,0.109375,-0.226562,0.828125,0,-0.203125,0.828125,0.164062,-0.242187,0.710938,-0.164062,-0.242187,0.710938,-0.179688,-0.3125,0.710938,0.179688,-0.3125,0.710938,0.257812,-0.3125,0.554688,-0.257812,-0.3125,0.554688,0.234375,-0.25,0.554688,-0.234375,-0.25,0.554688,0.09375,-0.742187,0.726563,-0.09375,-0.742187,0.726563,0,-0.773437,0.71875,0.09375,-0.820312,0.710938,-0.09375,-0.820312,0.710938,0.046875,-0.867187,0.6875,-0.046875,-0.867187,0.6875,0,-0.890625,0.6875,0,-0.875,0.6875,0,-0.859375,0.632813,-0.046875,-0.851562,0.632813,0.09375,-0.8125,0.640625,0.046875,-0.851562,0.632813,-0.09375,-0.8125,0.640625,0.09375,-0.75,0.664063,-0.09375,-0.75,0.664063,0,-0.78125,0.65625,0.1875,0.15625,0.773438,0.171875,0.21875,0.78125,-0.1875,0.15625,0.773438,-0.171875,0.21875,0.78125,0.179688,0.296875,0.78125,-0.179688,0.296875,0.78125,0.210938,0.375,0.78125,-0.210938,0.375,0.78125,-0.226562,0.109375,0.78125,0.375,0.0625,0.742188,0.226562,0.109375,0.78125,-0.375,0.0625,0.742188,0.476562,0.101563,0.71875,-0.476562,0.101563,0.71875,0.578125,0.195313,0.679688,-0.578125,0.195313,0.679688,0.585938,0.289063,0.6875,-0.585938,0.289063,0.6875,-0.5625,0.351563,0.695312,0.5625,0.351563,0.695312,-0.421875,0.398438,0.773438,0.335938,0.429688,0.757812,0.421875,0.398438,0.773438,-0.335938,0.429688,0.757812,0.273438,0.421875,0.773438,-0.273438,0.421875,0.773438,0.234375,0.359375,0.757812,0.28125,0.398438,0.765625,-0.234375,0.359375,0.757812,-0.28125,0.398438,0.765625,0.335938,0.40625,0.75,-0.335938,0.40625,0.75,0.414062,0.390625,0.75,-0.414062,0.390625,0.75,0.53125,0.335938,0.679688,-0.53125,0.335938,0.679688,0.554688,0.28125,0.671875,-0.554688,0.28125,0.671875,0.546875,0.210938,0.671875,-0.546875,0.210938,0.671875,0.460938,0.117188,0.703125,-0.460938,0.117188,0.703125,0.375,0.0859375,0.726562,-0.375,0.0859375,0.726562,0.242188,0.125,0.757812,-0.242188,0.125,0.757812,0.203125,0.171875,0.75,-0.203125,0.171875,0.75,0.195312,0.296875,0.757812,-0.195312,0.296875,0.757812,0.195312,0.226563,0.75,-0.195312,0.226563,0.75,0.109375,0.460938,0.609375,0,0.40625,0.601562,-0.109375,0.460938,0.609375,0.195312,0.664062,0.617188,-0.195312,0.664062,0.617188,-0.320312,0.757813,0.734375,-0.335938,0.6875,0.59375,0.335938,0.6875,0.59375,-0.484375,0.554688,0.554688,0.484375,0.554688,0.554688,-0.679688,0.453125,0.492187,0.796875,0.40625,0.460937,0.679688,0.453125,0.492187,-0.796875,0.40625,0.460937,-0.828125,0.148438,0.445312,-0.773438,0.164063,0.375,0.601562,1.80992e-08,0.414062,0.773438,0.164063,0.375,-0.601562,1.80992e-08,0.414062,0.4375,-0.09375,0.46875,-0.4375,-0.09375,0.46875,0,-0.484375,0.28125,0.125,-0.539062,0.359375,0,-0.570312,0.320313,-0.125,-0.539062,0.359375,-0.179688,-0.414062,0.257813,0.140625,-0.757812,0.367188,0,-0.804688,0.34375,-0.140625,-0.757812,0.367188,0.164062,-0.945312,0.4375,0,-0.976562,0.460938,-0.164062,-0.945312,0.4375,0.328125,-0.914062,0.398438,-0.328125,-0.914062,0.398438,0.289062,-0.710938,0.382813,-0.289062,-0.710938,0.382813,0.25,-0.5,0.390625,-0.25,-0.5,0.390625,0.179688,-0.414062,0.257813,0.234375,-0.351562,0.40625,-0.234375,-0.351562,0.40625,0.21875,-0.28125,0.429688,-0.21875,-0.28125,0.429688,-0.210938,-0.226562,0.46875,0.203125,-0.171875,0.5,-0.203125,-0.171875,0.5,-0.4375,-0.140625,0.53125,0.335938,0.0546875,-0.664062,0,-0.195313,-0.671875,0,0.0703125,-0.828125,-0.335938,0.0546875,-0.664062,-0.34375,-0.148438,-0.539062,0.34375,-0.148438,-0.539062,0,-0.382813,-0.351562,-0.296875,-0.3125,-0.265625,0.210938,-0.390625,0.164063,0,-0.460938,0.1875,-0.210938,-0.390625,0.164063,0.734375,-0.046875,0.0703125,0.851562,0.234375,0.0546875,-0.734375,-0.046875,0.0703125,-0.851562,0.234375,0.0546875,0.460938,0.4375,-0.703125,0,0.5625,-0.851562,-0.460938,0.4375,-0.703125,0.453125,0.851562,0.234375,0,0.984375,-0.078125,0,0.898438,0.289062,-0.453125,0.851562,0.234375,-0.453125,0.929688,-0.0703125,0.453125,0.867188,-0.382813,0,0.898438,-0.546875,-0.453125,0.867188,-0.382813,0.726562,0.40625,0.335937,0.632812,0.453125,0.28125,-0.726562,0.40625,0.335937,-0.632812,0.453125,0.28125,0.796875,0.5625,0.125,0.640625,0.703125,0.0546875,-0.796875,0.5625,0.125,-0.640625,0.703125,0.0546875,0.796875,0.617188,-0.117188,0.640625,0.75,-0.195313,-0.796875,0.617188,-0.117188,-0.640625,0.75,-0.195313,0.796875,0.539062,-0.359375,0.640625,0.679688,-0.445313,-0.796875,0.539062,-0.359375,-0.640625,0.679688,-0.445313,0.617188,0.328125,-0.585938,0.773438,0.265625,-0.4375,-0.617188,0.328125,-0.585938,0.453125,0.929688,-0.0703125,0.460938,0.523438,0.429687,-0.460938,0.523438,0.429687,0,0.570312,0.570312,0.859375,0.320312,-0.046875,-0.859375,0.320312,-0.046875,0.820312,0.328125,-0.203125,-0.820312,0.328125,-0.203125,0.296875,-0.3125,-0.265625,0.40625,-0.171875,0.148438,-0.40625,-0.171875,0.148438,-0.429688,-0.195313,-0.210937,0.59375,-0.125,-0.164062,-0.59375,-0.125,-0.164062,0.210938,-0.226562,0.46875,0.640625,-0.00781252,-0.429688,-0.640625,-0.00781252,-0.429688,-0.484375,0.0234375,-0.546875,0.429688,-0.195313,-0.210937,0.484375,0.0234375,-0.546875,0.890625,0.40625,-0.234375,1.01562,0.414062,-0.289063,1.02344,0.476562,-0.3125,-0.890625,0.40625,-0.234375,-1.01562,0.414062,-0.289063,-0.921875,0.359375,-0.21875,1.1875,0.4375,-0.390625,1.23438,0.507812,-0.421875,-1.1875,0.4375,-0.390625,-1.02344,0.476562,-0.3125,-1.23438,0.507812,-0.421875,1.35156,0.320312,-0.421875,-1.35156,0.320312,-0.421875,-1.26562,0.289062,-0.40625,1.26562,0.289062,-0.40625,1.28125,0.0546875,-0.429688,-1.28125,0.0546875,-0.429688,-1.21094,0.078125,-0.40625,1.21094,0.078125,-0.40625,1.03906,-0.101563,-0.328125,-1.03906,-0.101563,-0.328125,-1.03125,-0.0390625,-0.304688,0.828125,-0.0703125,-0.132812,0.773438,-0.140625,-0.125,-0.828125,-0.0703125,-0.132812,-0.773438,-0.140625,-0.125,1.03125,-0.0390625,-0.304688,0.882812,-0.0234375,-0.210938,-0.882812,-0.0234375,-0.210938,1.03906,-1.60503e-08,-0.367188,-1.03906,-1.60503e-08,-0.367188,1.23438,0.25,-0.445312,-1.23438,0.25,-0.445312,-1.1875,0.09375,-0.445312,1.17188,0.359375,-0.4375,-1.17188,0.359375,-0.4375,1.02344,0.34375,-0.359375,-1.02344,0.34375,-0.359375,0.945312,0.304688,-0.289062,-0.945312,0.304688,-0.289062,0.726562,-3.07346e-09,-0.0703125,-0.726562,-3.07346e-09,-0.0703125,-0.71875,-0.0234375,-0.171875,0.71875,-0.0234375,-0.171875,0.921875,0.359375,-0.21875,0.8125,-0.015625,-0.273438,-0.8125,-0.015625,-0.273438,0.71875,0.0390625,-0.1875,0.84375,0.015625,-0.273438,-0.71875,0.0390625,-0.1875,0.757812,0.09375,-0.273438,0.820312,0.0859375,-0.273438,-0.84375,0.015625,-0.273438,-0.757812,0.09375,-0.273438,-0.820312,0.0859375,-0.273438,0.796875,0.203125,-0.210938,0.835938,0.171875,-0.273438,-0.796875,0.203125,-0.210938,0.890625,0.242187,-0.265625,0.84375,0.289062,-0.210938,-0.890625,0.242187,-0.265625,-0.835938,0.171875,-0.273438,-0.84375,0.289062,-0.210938,0.890625,0.234375,-0.320312,0.953125,0.289062,-0.34375,-0.890625,0.234375,-0.320312,-0.953125,0.289062,-0.34375,-0.84375,0.171875,-0.320312,0.765625,0.09375,-0.320312,0.84375,0.171875,-0.320312,-0.765625,0.09375,-0.320312,-0.828125,0.078125,-0.320312,0.828125,0.078125,-0.320312,-0.851562,0.015625,-0.320312,0.8125,-0.015625,-0.320312,0.851562,0.015625,-0.320312,-0.8125,-0.015625,-0.320312,0.882812,-0.015625,-0.265625,-0.882812,-0.015625,-0.265625,1.03906,0.328125,-0.414062,-1.03906,0.328125,-0.414062,1.1875,0.34375,-0.484375,-1.1875,0.34375,-0.484375,1.25781,0.242187,-0.492188,-1.25781,0.242187,-0.492188,1.21094,0.0859375,-0.484375,1.1875,0.09375,-0.445312,-1.21094,0.0859375,-0.484375,1.04688,-1.84407e-08,-0.421875,-1.04688,-1.84407e-08,-0.421875,0.890625,0.109375,-0.328125,-0.890625,0.109375,-0.328125,-0.9375,0.0625,-0.335938,0.9375,0.0625,-0.335938,0.960938,0.171875,-0.351562,-0.960938,0.171875,-0.351562,-1,0.125,-0.367188,1.05469,0.1875,-0.382812,1.01562,0.234375,-0.375,-1.05469,0.1875,-0.382812,-1.01562,0.234375,-0.375,1.08594,0.273437,-0.390625,-1.08594,0.273437,-0.390625,-1.10938,0.210937,-0.390625,1.10938,0.210937,-0.390625,0.789062,-0.125,-0.328125,1.03906,-0.0859375,-0.492188,-0.789062,-0.125,-0.328125,-1.03906,-0.0859375,-0.492188,1.3125,0.0546875,-0.53125,-1.3125,0.0546875,-0.53125,1.36719,0.296875,-0.5,-1.36719,0.296875,-0.5,1.25,0.46875,-0.546875,-1.25,0.46875,-0.546875,1.02344,0.4375,-0.484375,-1.02344,0.4375,-0.484375,0.859375,0.382812,-0.382813,-0.859375,0.382812,-0.382813,-0.773438,0.265625,-0.4375,-0.164062,0.414063,0.773438,1,0.125,-0.367188 };
		constexpr uint indices[] = { 0,1,2,3,4,5,2,6,7,8,5,9,1,10,6,11,3,8,12,13,1,14,15,3,16,17,13,18,19,14,13,20,10,21,14,11,22,20,17,23,21,24,25,17,26,27,18,23,25,28,22,29,27,23,28,30,22,29,24,31,32,33,28,34,31,35,36,28,37,38,29,34,39,32,36,40,34,41,42,43,32,41,35,44,2,45,42,5,44,9,0,42,39,4,41,5,39,46,0,40,47,48,36,49,39,38,48,50,37,51,36,52,50,53,25,54,37,27,53,55,25,56,57,58,27,55,26,59,56,60,61,58,16,62,59,63,19,60,12,46,62,47,15,63,64,62,46,47,63,65,59,62,64,65,63,60,64,56,59,60,58,65,64,57,56,58,55,65,64,54,57,55,53,65,64,51,54,53,50,65,64,49,51,50,48,65,64,46,49,48,47,65,66,67,68,69,67,70,71,68,72,73,74,69,75,71,72,73,76,77,78,79,75,80,81,76,82,83,78,84,85,81,86,87,88,89,90,91,92,87,93,94,89,95,92,96,97,98,94,95,99,96,100,101,98,102,103,104,99,105,102,106,107,108,103,109,106,110,107,111,112,113,109,110,114,111,115,116,113,117,118,119,114,120,117,121,122,123,118,122,121,124,125,123,126,127,121,117,125,111,119,113,127,117,112,128,129,110,130,113,108,129,131,106,132,110,104,131,133,102,134,106,96,133,135,98,136,102,97,135,137,95,138,98,87,137,139,89,140,95,17,87,139,89,18,141,17,142,88,142,18,91,123,143,126,121,144,124,143,145,146,145,144,147,148,145,142,149,145,147,150,70,66,70,151,69,152,66,71,69,153,73,152,79,154,153,80,73,155,156,83,157,158,84,154,83,156,84,159,157,160,161,162,160,163,164,161,165,156,163,165,164,154,165,166,159,165,157,167,168,162,169,170,171,172,167,173,174,170,175,176,173,177,178,179,174,180,177,181,180,177,178,162,182,160,171,182,169,168,183,182,169,183,184,180,185,176,186,180,178,176,187,172,188,178,174,187,189,172,188,175,190,189,191,168,184,175,169,192,185,193,190,186,188,193,191,192,184,193,190,177,88,142,91,177,142,173,194,88,195,179,91,162,194,167,171,195,196,161,197,162,163,196,158,198,155,82,199,158,196,200,197,198,201,196,195,86,194,200,195,90,201,166,202,154,166,203,204,152,202,205,203,153,206,150,205,207,206,151,208,209,207,210,208,209,210,207,211,210,208,211,212,207,213,214,215,208,212,205,216,213,217,206,215,204,216,202,204,217,218,218,214,216,212,218,217,216,214,213,215,212,217,146,219,220,221,147,222,143,220,223,222,144,224,143,225,126,144,226,224,17,219,148,18,221,227,17,228,229,230,18,227,139,231,228,232,141,230,137,233,231,234,140,232,135,235,233,236,138,234,131,235,133,134,236,237,129,238,131,132,237,239,129,240,241,242,132,239,128,243,240,244,130,242,125,225,243,226,127,244,243,245,246,247,244,248,240,246,249,248,242,250,240,251,241,242,252,250,241,253,238,239,254,252,235,253,255,254,236,256,235,257,233,236,258,256,231,257,259,258,232,260,231,261,228,232,262,260,228,263,229,230,264,262,219,263,265,264,221,266,225,267,245,268,226,247,223,269,267,270,224,268,220,265,269,266,222,270,122,271,272,273,122,272,118,274,271,275,120,273,115,274,114,276,275,277,107,278,115,109,277,279,103,280,107,105,279,281,103,282,283,284,105,281,100,282,99,285,284,286,100,287,288,289,285,286,92,290,287,291,94,289,292,293,294,292,295,296,294,297,298,294,299,295,298,300,301,298,302,299,68,301,300,301,74,302,72,300,303,302,77,304,75,303,305,304,76,306,78,305,307,306,81,308,305,293,307,295,306,308,303,297,305,304,299,302,307,309,310,308,296,295,82,307,310,308,85,311,312,200,198,313,201,314,310,198,82,311,199,313,200,315,86,201,316,314,315,93,86,316,317,291,318,319,320,321,319,322,323,324,319,322,324,325,324,326,327,328,324,327,327,309,292,296,327,292,309,312,310,296,313,328,288,329,330,331,286,332,333,320,334,335,320,321,336,337,338,339,337,340,337,341,342,343,337,342,342,333,334,335,342,334,283,344,345,346,281,347,345,348,349,350,347,351,349,352,353,354,351,355,353,356,357,358,355,359,360,356,361,362,358,359,333,357,360,359,335,362,341,353,357,355,343,359,363,349,353,351,340,355,336,345,349,347,339,351,283,364,280,281,365,347,364,338,366,365,338,339,274,280,271,275,279,277,271,364,366,365,273,366,272,271,366,366,273,272,288,344,282,286,346,332,330,348,344,350,332,346,367,352,348,354,368,350,356,369,361,358,370,354,371,372,326,325,373,374,372,375,329,373,376,374,287,372,329,373,289,331,290,312,372,313,291,373,312,326,372,373,328,313,290,315,377,314,316,291,378,360,361,379,362,380,360,318,333,362,321,380,381,378,375,374,379,380,323,381,371,322,374,380,318,382,323,322,380,321,383,384,385,386,387,388,385,389,390,391,392,393,389,394,390,391,395,396,397,398,394,396,399,400,401,402,398,400,403,404,402,405,406,407,403,408,409,410,405,411,404,407,401,412,409,413,400,404,414,401,397,415,400,416,417,397,389,418,396,415,419,389,384,420,391,418,384,421,419,422,387,420,375,423,329,376,424,425,406,426,375,408,425,407,330,423,367,424,332,368,369,427,383,388,370,386,405,428,426,429,407,425,430,428,431,432,429,425,433,431,434,435,436,437,438,433,439,440,436,432,438,441,442,440,443,444,442,421,427,445,422,443,438,369,367,440,370,445,423,438,367,424,440,432,423,426,430,432,425,424,421,446,447,448,422,449,439,446,441,444,448,450,439,451,452,453,444,450,434,451,433,437,453,454,431,455,434,435,454,456,431,457,458,459,435,456,428,460,457,461,429,459,419,447,462,449,420,463,417,462,464,463,418,465,414,464,466,465,415,467,414,468,469,415,470,467,469,471,412,416,472,470,412,460,410,413,461,472,458,473,455,456,474,475,476,477,473,475,478,479,477,480,481,482,478,483,480,484,481,482,485,486,462,481,484,483,463,485,477,447,446,478,449,483,452,477,446,450,478,474,455,452,451,450,454,453,460,458,457,461,456,475,471,476,460,475,472,461,480,471,468,482,472,479,487,468,466,486,470,482,464,487,466,486,465,467,462,484,464,465,485,463,402,488,489,490,403,491,398,489,492,491,399,493,398,494,394,399,495,493,394,496,390,395,497,495,390,498,385,393,499,497,385,500,383,392,501,499,489,500,498,491,501,490,498,492,489,493,499,491,496,494,492,493,495,497,369,500,361,370,501,386,361,488,378,490,502,379,375,488,406,490,376,408,0,12,1,3,15,4,2,1,6,8,3,5,1,13,10,11,14,3,12,16,13,14,19,15,16,26,17,18,61,19,13,17,20,21,18,14,22,30,20,23,18,21,25,22,17,27,61,18,25,37,28,29,52,27,28,33,30,29,23,24,32,43,33,34,29,31,36,32,28,38,52,29,39,42,32,40,38,34,42,45,43,41,34,35,2,7,45,5,41,44,0,2,42,4,40,41,39,49,46,40,4,47,36,51,49,38,40,48,37,54,51,52,38,50,25,57,54,27,52,53,25,26,56,58,61,27,26,16,59,60,19,61,16,12,62,63,15,19,12,0,46,47,4,15,66,70,67,69,74,67,71,66,68,73,77,74,75,79,71,73,80,76,78,83,79,80,84,81,82,155,83,84,158,85,86,93,87,89,317,90,92,97,87,94,317,89,92,100,96,98,285,94,99,104,96,101,285,98,103,108,104,105,101,102,107,112,108,109,105,106,107,115,111,113,276,109,114,119,111,116,276,113,118,123,119,120,116,117,122,124,123,122,120,121,125,119,123,127,503,121,125,128,111,113,130,127,112,111,128,110,132,130,108,112,129,106,134,132,104,108,131,102,136,134,96,104,133,98,138,136,97,96,135,95,140,138,87,97,137,89,141,140,17,88,87,89,91,18,17,148,142,142,149,18,123,124,143,121,503,144,143,124,145,145,124,144,148,146,145,149,142,145,150,209,70,70,209,151,152,150,66,69,151,153,152,71,79,153,159,80,155,161,156,157,163,158,154,79,83,84,80,159,160,164,161,160,171,163,161,164,165,163,157,165,154,156,165,159,166,165,167,189,168,169,175,170,172,189,167,174,179,170,176,172,173,178,177,179,180,176,177,162,168,182,171,160,182,168,191,183,169,182,183,180,193,185,186,193,180,176,185,187,188,186,178,187,192,189,188,174,175,189,192,191,184,190,175,192,187,185,190,193,186,193,183,191,184,183,193,177,173,88,91,179,177,173,167,194,195,170,179,162,197,194,171,170,195,161,155,197,163,171,196,198,197,155,199,85,158,200,194,197,201,199,196,86,88,194,195,91,90,166,204,202,166,159,203,152,154,202,203,159,153,150,152,205,206,153,151,209,150,207,208,151,209,207,214,211,208,210,211,207,205,213,215,206,208,205,202,216,217,203,206,204,218,216,204,203,217,218,211,214,212,211,218,146,148,219,221,149,147,143,146,220,222,147,144,143,223,225,144,503,226,17,229,219,18,149,221,17,139,228,230,141,18,139,137,231,232,140,141,137,135,233,234,138,140,135,133,235,236,136,138,131,238,235,134,136,236,129,241,238,132,134,237,129,128,240,242,130,132,128,125,243,244,127,130,125,126,225,226,503,127,243,225,245,247,226,244,240,243,246,248,244,242,240,249,251,242,239,252,241,251,253,239,237,254,235,238,253,254,237,236,235,255,257,236,234,258,231,233,257,258,234,232,231,259,261,232,230,262,228,261,263,230,227,264,219,229,263,264,227,221,225,223,267,268,224,226,223,220,269,270,222,224,220,219,265,266,221,222,122,118,271,273,120,122,118,114,274,275,116,120,115,278,274,276,116,275,107,280,278,109,276,277,103,283,280,105,109,279,103,99,282,284,101,105,100,288,282,285,101,284,100,92,287,289,94,285,92,93,290,291,317,94,292,309,293,292,294,295,294,293,297,294,298,299,298,297,300,298,301,302,68,67,301,301,67,74,72,68,300,302,74,77,75,72,303,304,77,76,78,75,305,306,76,81,305,297,293,295,299,306,303,300,297,304,306,299,307,293,309,308,311,296,82,78,307,308,81,85,312,377,200,313,199,201,310,312,198,311,85,199,200,377,315,201,90,316,315,290,93,316,90,317,318,323,319,321,320,319,323,371,324,322,319,324,324,371,326,328,325,324,327,326,309,296,328,327,309,326,312,296,311,313,288,287,329,331,289,286,333,318,320,335,334,320,336,363,337,339,338,337,337,363,341,343,340,337,342,341,333,335,343,342,283,282,344,346,284,281,345,344,348,350,346,347,349,348,352,354,350,351,353,352,356,358,354,355,360,357,356,362,502,358,333,341,357,359,343,335,341,363,353,355,340,343,363,336,349,351,339,340,336,364,345,347,365,339,283,345,364,281,279,365,364,336,338,365,366,338,274,278,280,275,273,279,271,280,364,365,279,273,288,330,344,286,284,346,330,367,348,350,368,332,367,369,352,354,370,368,356,352,369,358,502,370,371,381,372,325,328,373,372,381,375,373,331,376,287,290,372,373,291,289,290,377,312,313,314,291,378,382,360,379,502,362,360,382,318,362,335,321,381,382,378,374,376,379,323,382,381,322,325,374,383,427,384,386,392,387,385,384,389,391,387,392,389,397,394,391,393,395,397,401,398,396,395,399,401,409,402,400,399,403,402,409,405,407,404,403,409,412,410,411,413,404,401,469,412,413,416,400,414,469,401,415,396,400,417,414,397,418,391,396,419,417,389,420,387,391,384,427,421,422,388,387,375,426,423,376,331,424,406,405,426,408,376,425,330,329,423,424,331,332,369,442,427,388,445,370,405,410,428,429,411,407,430,426,428,432,435,429,433,430,431,435,432,436,438,430,433,440,444,436,438,439,441,440,445,443,442,441,421,445,388,422,438,442,369,440,368,370,423,430,438,424,368,440,421,441,446,448,443,422,439,452,446,444,443,448,439,433,451,453,436,444,434,455,451,437,436,453,431,458,455,435,437,454,431,428,457,459,429,435,428,410,460,461,411,429,419,421,447,449,422,420,417,419,462,463,420,418,414,417,464,465,418,415,414,466,468,415,416,470,469,468,471,416,413,472,412,471,460,413,411,461,458,476,473,456,454,474,476,504,477,475,474,478,477,504,480,482,479,478,480,487,484,482,483,485,462,447,481,483,449,463,477,481,447,478,448,449,452,473,477,450,448,478,455,473,452,450,474,454,460,476,458,461,459,456,471,504,476,475,479,472,480,504,471,482,470,472,487,480,468,486,467,470,464,484,487,486,485,465,402,406,488,490,408,403,398,402,489,491,403,399,398,492,494,399,395,495,394,494,496,395,393,497,390,496,498,393,392,499,385,498,500,392,386,501,489,488,500,491,499,501,498,496,492,493,497,499,369,383,500,370,502,501,361,500,488,490,501,502,375,378,488,490,379,376 };

		span<double3> points = { (double3*)position, array_size(position) / 3 };
		span<uint3> faces = { (uint3*)indices, array_size(indices) / 3 };

		MeshPacker shape;

		for(uint3 face : faces)
		{
			const vec3 v0 = vec3(points[face[0]]);
			const vec3 v1 = vec3(points[face[1]]);
			const vec3 v2 = vec3(points[face[2]]);

			const vec3 normal = Plane(v0, v1, v2).m_normal;

			shape.position(v0);
			shape.position(v1);
			shape.position(v2);

			shape.normal(normal);
			shape.normal(normal);
			shape.normal(normal);
		}

		Model& model = gfx.create_model_geo("suzanne", shape);
		return model;
	}
}
}


module two.gfx;

#include <cstdio>

namespace two
{
	template class Graph<Gnode>;

	template class TPool<Node3>;
	template class TPool<Item>;
	template class TPool<Batch>;
	template class TPool<Direct>;
	template class TPool<Mime>;
	template class TPool<Light>;
	template class TPool<Flare>;

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
		if(m_batch)
		{
			m_scene->m_pool->pool<Batch>().tdestroy(*m_batch);
			m_batch = nullptr;
		}
		if(m_direct)
		{
			m_scene->m_pool->pool<Direct>().tdestroy(*m_direct);
			m_direct = nullptr;
		}
		if(m_animated)
		{
			m_scene->m_pool->pool<Mime>().tdestroy(*m_animated);
			m_animated = nullptr;
		}
		if(m_particles)
		{
			m_scene->m_pool->pool<Flare>().tdestroy(*m_particles);
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
			printf("[ERROR] sound goes out of graph but wasn't destroyed\n");
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

	template <class T, class... Args>
	inline T& create(Scene& scene, Args&&... args)
	{
		return scene.m_pool->pool<T>().construct(static_cast<Args&&>(args)...);
	}

namespace gfx
{
	void setup_pipeline_minimal(GfxSystem& gfx)
	{
		gfx.init_pipeline(pipeline_minimal);
	}

	TPool<Node3>&  nodes(Scene& scene)   { return scene.m_pool->pool<Node3>(); }
	TPool<Item>&   items(Scene& scene)   { return scene.m_pool->pool<Item>(); }
	TPool<Batch>&  batches(Scene& scene) { return scene.m_pool->pool<Batch>(); }
	TPool<Direct>& directs(Scene& scene) { return scene.m_pool->pool<Direct>(); }
	TPool<Mime>&   mimes(Scene& scene)   { return scene.m_pool->pool<Mime>(); }
	TPool<Light>&  lights(Scene& scene)  { return scene.m_pool->pool<Light>(); }
	TPool<Flare>&  flares(Scene& scene)  { return scene.m_pool->pool<Flare>(); }

	Gnode& node(Gnode& parent, const mat4& transform)
	{
		Gnode& self = parent.suba();
		//Gnode& self = parent.subi((void*)object.as_uint());
		if(!self.m_node)
		{
			self.m_node = &create<Node3>(*parent.m_scene);
			self.m_attach = self.m_node;
		}
		self.m_node->m_transform = transform;
		return self;
	}

	Gnode& node(Gnode& parent, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, bxTRS(scale, rotation, position));
	}

	Gnode& node(Gnode& parent, const Transform& transform)
	{
		return node(parent, transform.m_position, transform.m_rotation, transform.m_scale);
	}

	Gnode& transform(Gnode& parent, const vec3& position, const quat& rotation, const vec3& scale)
	{
		return node(parent, parent.m_attach->m_transform * bxTRS(scale, rotation, position));
	}

	Gnode& transform(Gnode& parent, const vec3& position, const quat& rotation)
	{
		return node(parent, parent.m_attach->m_transform * bxTRS(vec3(1.f), rotation, position));
	}

	Item& item(Gnode& parent, const Model& model, uint32_t flags, Material* material)
	{
		Gnode& self = parent.suba<Gnode>();
		bool update = (flags & ItemFlag::NoUpdate) == 0;
		if(!self.m_item)
		{
			self.m_item = &create<Item>(*self.m_scene, *self.m_attach, model, flags, material);
			update = true;
		}
		self.m_item->m_model = const_cast<Model*>(&model);
		self.m_item->m_material = material;
		if(update)
		{
			self.m_item->update_aabb();
		}
		return *self.m_item;
	}

	Batch& batch(Gnode& parent, Item& item, uint16_t stride)
	{
		Gnode& self = parent.suba<Gnode>();
		if(!self.m_batch)
		{
			self.m_batch = &create<Batch>(*self.m_scene, item, stride);
			item.m_batch = self.m_batch;
		}
		return *self.m_batch;
	}

	Batch& instances(Gnode& parent, Item& item, span<mat4> transforms)
	{
		Gnode& self = parent.suba<Gnode>();
		if(!self.m_batch)
		{
			self.m_batch = &create<Batch>(*self.m_scene, item, uint16_t(sizeof(mat4)));
			item.m_batch = self.m_batch;
		}
		self.m_batch->transforms(transforms);
		self.m_batch->update_aabb(transforms);
		return *self.m_batch;
	}

	void prefab(Gnode& parent, const Prefab& prefab, bool transform, uint32_t flags, Material* material)
	{
		Gnode& self = parent.suba<Gnode>();
		
		for(const Prefab::Elem& elem : prefab.m_items)
		{
			const Node3& n = prefab.m_nodes[elem.node];
			mat4 tr = transform ? parent.m_attach->m_transform * n.m_transform
								: n.m_transform;
			Gnode& no = node(self, tr);
			Item& it = item(no, *elem.item.m_model, elem.item.m_flags | flags, material);
			//it = prefab.m_items[i];
			//shape(self, Cube(i.m_aabb.m_center, vec3(0.1f)), Symbol::wire(Colour::Red, true));
			//shape(self, submodel->m_aabb, Symbol::wire(Colour::White));
			UNUSED(it);
		}
	}

	Item& shape_item(Gnode& parent, Model& model, const Symbol& symbol, uint32_t flags, Material* material, DrawMode draw_mode)
	{
		Item& self = item(parent, model, flags, material);
		self.m_material = material ? material : &parent.m_scene->m_gfx.symbol_material(symbol, draw_mode);
		return self;
	}

	Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags, Material* material)
	{
		Item* item = nullptr;
		static Symbol white = { Colour::White, Colour::White };
		if(symbol.fill())
			item = &shape_item(parent, parent.m_scene->m_gfx.shape(shape, white, PLAIN), symbol, flags, material, PLAIN);
		if(symbol.outline())
			item = &shape_item(parent, parent.m_scene->m_gfx.shape(shape, white, OUTLINE), symbol, flags, material, OUTLINE);
		return *item;
	}

	void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		UNUSED(flags);
		if(symbol.fill())
			scene.m_immediate->shape(transform, { symbol, &shape, PLAIN });
		if(symbol.outline())
			scene.m_immediate->shape(transform, { symbol, &shape, OUTLINE });
	}

	void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags)
	{
		draw(*parent.m_scene, parent.m_attach->m_transform, shape, symbol, flags);
	}

	Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags, Material* material)
	{
		return shape(parent, Quad(size), { image }, flags, material);
	}

	Item* model(Gnode& parent, const string& name, uint32_t flags, Material* material)
	{
		Model* model = parent.m_scene->m_gfx.models().file(name.c_str());
		if(model)
			return &item(parent, *model, flags, material);
		return nullptr;
	}

	Mime& animated(Gnode& parent, Item& item)
	{
		Gnode& self = parent.suba();
		if(!self.m_animated)
		{
			self.m_animated = &create<Mime>(*self.m_scene);
			self.m_animated->add_item(item);
		}
		return *self.m_animated;
	}

	Flare& flows(Gnode& parent, const Flow& emitter, uint32_t flags)
	{
		UNUSED(flags);
		Gnode& self = parent.suba();
		if(!self.m_particles)
			self.m_particles = &create<Flare>(*self.m_scene, self.m_attach, Sphere(1.f), 1024);
		as<Flow>(*self.m_particles) = emitter;
		self.m_particles->m_node = self.m_attach;
		self.m_particles->m_sprite = &parent.m_scene->m_particle_system->m_block.m_sprites->find_sprite(emitter.m_sprite_name.c_str());
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
		Gnode& self = node(parent, vec3(0.f), rotation);
		Light& l = light(self, LightType::Direct, true, Colour(0.8f, 0.8f, 0.7f), 1.f);
		l.m_energy = 0.6f;
		return l;
	}

	Light& sun_light(Gnode& parent, float azimuth, float elevation)
	{
		return direct_light_node(parent, sun_rotation(azimuth, elevation));
	}

	Light& direct_light_node(Gnode& parent, const vec3& direction)
	{
		return direct_light_node(parent, facing(direction));
	}

	Light& direct_light_node(Gnode& parent)
	{
		return direct_light_node(parent, quat(vec3(-c_pi4, -c_pi4, 0.f)));
	}

	void radiance(Scene& scene, const string& file, BackgroundMode background)
	{
		scene.m_env.m_radiance.m_texture = scene.m_gfx.textures().file(file.c_str());
		scene.m_env.m_background.m_mode = background;
	}

	void radiance(Gnode& parent, const string& file, BackgroundMode background)
	{
		Texture& texture = *parent.m_scene->m_gfx.textures().file(file.c_str());
		Zone& env = parent.m_scene->m_env;
		env.m_radiance.m_texture = &texture;
		env.m_radiance.m_energy = 0.3f;
		if(background == BackgroundMode::Panorama)
			env.m_background.m_texture = &texture;
		env.m_background.m_mode = background;
	}

	void custom_sky(Gnode& parent, CustomSky renderer)
	{
		parent.m_scene->m_env.m_background.m_custom_function = renderer;
		parent.m_scene->m_env.m_background.m_mode = BackgroundMode::Custom;
	}

	void manual_job(Gnode& parent, PassType pass, ManualJob job)
	{
		parent.m_scene->m_pass_jobs->m_jobs[pass].push_back(job);
	}

	Material& solid_material(GfxSystem& gfx, const string& name, const Colour& colour)
	{
		Program& program = *gfx.programs().file("solid");
		Material& material = gfx.materials().fetch(name);
		material.m_program = &program;
		material.m_solid.m_colour = colour;
		return material;
	}

	Material& pbr_material(GfxSystem& gfx, const string& name, const MaterialPbr& pbr_block)
	{
		Program& program = *gfx.programs().file("pbr/pbr");
		Material& material = gfx.materials().fetch(name);
		material.m_program = &program;
		material.m_pbr = pbr_block;
		return material;
	}

	Material& pbr_material(GfxSystem& gfx, const string& name, const Colour& albedo, float metallic, float roughness)
	{
		return pbr_material(gfx, name, { albedo, metallic, roughness });
	}
}
}


module two.gfx;

namespace two
{
	Import::Import(GfxSystem& gfx, const string& filepath, const ImportConfig& config)
		: m_gfx(gfx), m_config(config)
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

	void import_to_prefab(GfxSystem& gfx, Prefab& prefab, Import& state, uint32_t flags)
	{
		UNUSED(gfx);
		prefab.m_nodes.reserve(state.m_items.size());
		prefab.m_items.reserve(state.m_items.size());

		prefab.m_aabb = {};

		for(const Node3& node : state.m_nodes)
		{
			prefab.m_nodes.push_back({ node });
		}

		for(Import::Item& item : state.m_items)
		{
			Model& model = *item.model;
			Node3& node = prefab.m_nodes[item.node];
			prefab.m_items.push_back({ item.node, Item(node, model, ItemFlag::Default | flags) });

			prefab.m_aabb.merge(transform_aabb(model.m_aabb, node.m_transform));

			// special hack for occluders
			if(model.m_items[0].m_mesh->m_material && model.m_items[0].m_mesh->m_material->m_name == "occluder")
				prefab.m_items.back().item.m_flags = ItemFlag::Occluder;
		}

		for(Animation* anim : state.m_animations)
			prefab.m_anims.push_back(anim);
	}
}

module two.gfx;
#include <cstring>
#include <cstdio>

namespace two
{
	uint32_t item_flags(uint32_t flags)
	{
		if(flags == 0) return ItemFlag::Default;
		if((flags & ItemFlag::LodAll) == 0) return flags | ItemFlag::LodAll;
		return flags;
	}

	Item::Item() {}
	Item::Item(Node3& node, const Model& model, uint32_t flags, Material* material)
		: m_node(&node)
		, m_model(const_cast<Model*>(&model))
		, m_flags(item_flags(flags))
		, m_material(material)
	{
		this->update_aabb();
	}

	void Item::update_aabb()
	{
		if(m_batch == nullptr)
			m_aabb = transform_aabb(m_model->m_aabb, m_node->m_transform);
	}

	void Item::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelElem& item) const
	{
		if(m_rig && m_rig->m_weights.size() > 0)
		{
			float weights[4] = {};

			for(size_t i = 0; i < 4; ++i)
			{
				Rig::MorphWeight& w = m_rig->m_weights[i];
				weights[i] = w.weight;
				if(w.weight != 0.f)
					item.m_mesh->submit_morph(encoder, i, w.index);
			}

			static bgfx::UniformHandle u_morph_weights = bgfx::createUniform("u_morph_weights", bgfx::UniformType::Vec4);
			encoder.setUniform(u_morph_weights, weights);
		}

		bgfx_state |= item.m_mesh->submit(encoder);

		if(!item.m_has_transform)
			encoder.setTransform(value_ptr(m_node->m_transform));
		else
		{
			mat4 transform = m_node->m_transform * item.m_transform;
			encoder.setTransform(value_ptr(transform));
		}

		if(m_batch != nullptr)
			m_batch->submit(encoder, item);
	}

	Batch::Batch()
		: m_buffer{}
	{}

	Batch::Batch(Item& item, uint16_t stride)
		: m_item(&item)
		, m_stride(stride)
		, m_buffer{}
	{}

	void Batch::submit(bgfx::Encoder& encoder, const ModelElem& item) // const
	{
		if(m_cache.size() > 0)
			this->commit(m_cache);

		encoder.setInstanceDataBuffer(&m_buffer);
		//encoder.setInstanceDataBuffer(&m_buffers[item.m_index]);
	}

	void Batch::update_aabb(span<mat4> instances)
	{
		const Aabb& model = m_item->m_model->m_aabb;
		Aabb& aabb = m_item->m_aabb;
		aabb = {};
		for(const mat4& transform : instances)
		{
			aabb.merge(transform_aabb(model, transform));
		}
	}

	span<float> Batch::begin(uint32_t count)
	{
		uint32_t num = bgfx::getAvailInstanceDataBuffer(count, m_stride);
		if(num == 0) return {};
		bgfx::allocInstanceDataBuffer(&m_buffer, num, m_stride);
		return { (float*)m_buffer.data, num * m_stride / sizeof(float) };
	}

	void Batch::commit(span<float> data)
	{
		const uint32_t count = uint32_t(data.size() * sizeof(float) / m_stride);
		span<float> dest = this->begin(count);
		memcpy(dest.data(), data.data(), dest.size() * sizeof(float));
	}

	void Batch::cache(span<float> data)
	{
		const uint32_t count = uint32_t(m_cache.size() * sizeof(float) / m_stride);
		m_cache.assign(data.begin(), data.end());
	}

	void Batch::transform(const mat4& m)
	{
		const size_t size = m_cache.size();
		m_cache.resize(size + 16);
		memcpy(&m_cache[size], &m, 16 * sizeof(float));
	}

	void Batch::transforms(span<mat4> instances)
	{
		const Model& model = *m_item->m_model;
		if(model.m_no_transform)
		{
			bgfx::InstanceDataBuffer& buffer = m_buffer;
			uint32_t num = bgfx::getAvailInstanceDataBuffer(uint32_t(instances.size()), sizeof(mat4));
			if(num == 0) return;
			bgfx::allocInstanceDataBuffer(&buffer, num, sizeof(mat4));

			mat4* mat = (mat4*)buffer.data;
			memcpy(mat, instances.data(), instances.size() * sizeof(mat4));
		}
		else
		{
			m_buffers.resize(model.m_items.size());

			for(const ModelElem& item : model.m_items)
			{
				bgfx::InstanceDataBuffer& buffer = m_buffers[item.m_index];
				uint32_t num = bgfx::getAvailInstanceDataBuffer(uint32_t(instances.size()), sizeof(mat4));
				if(num == 0) return;
				bgfx::allocInstanceDataBuffer(&buffer, num, sizeof(mat4));

				mat4* mat = (mat4*)buffer.data;

				if(item.m_has_transform)
				{
					for(uint32_t i = 0; i < buffer.num; ++i)
						*mat++ = instances[i] * item.m_transform;
				}
				else
				{
					memcpy(mat, instances.data(), instances.size() * sizeof(mat4));
				}
			}
		}
	}
}


module two.gfx;

namespace two
{
	//static uint32_t s_light_index = 0;

	Light::Light(Node3& node, LightType type, bool shadows, Colour colour, float energy, float range)
		: m_node(&node)
		, m_type(type)
		, m_colour(colour)
		, m_range(range)
		, m_energy(energy)
		, m_shadows(shadows)
		//, m_index(s_light_index++)
	{
		m_shadow_bias = 0.01f;
		m_shadow_normal_bias = 0.f; // @todo investigate why making this higher fucks up the first shadow slice

		m_attenuation = 1.f;

		if(type != LightType::Spot)
			m_spot_angle = 0.f;

		if(type == LightType::Direct)
		{
			m_shadow_flags = CSM_Stabilize;
			m_shadow_bias = 0.1f;
#ifdef TWO_PLATFORM_EMSCRIPTEN
			m_shadow_num_splits = 2;
#else
			m_shadow_num_splits = 4;
#endif
		}
	}
}


#include <bgfx/bgfx.h>

module two.gfx;

#include <cstring>
#include <cstdio>

namespace two
{
	bool is_valid(Texture* texture) { return texture != nullptr && texture->valid(); };

	template struct MaterialParam<Colour>;
	template struct MaterialParam<float>;
	template struct MaterialParam<vec4>;

	GpuState<MaterialBase> GpuState<MaterialBase>::me;
	GpuState<MaterialAlpha> GpuState<MaterialAlpha>::me;
	GpuState<MaterialSolid> GpuState<MaterialSolid>::me;
	GpuState<MaterialPoint> GpuState<MaterialPoint>::me;
	GpuState<MaterialLine> GpuState<MaterialLine>::me;
	GpuState<MaterialLit> GpuState<MaterialLit>::me;
	GpuState<MaterialPbr> GpuState<MaterialPbr>::me;
	GpuState<MaterialPhong> GpuState<MaterialPhong>::me;
	GpuState<MaterialUser> GpuState<MaterialUser>::me;
	GpuState<Material> GpuState<Material>::me;

	void blend_state(BlendMode blend_mode, uint64_t& bgfx_state)
	{
		if(blend_mode == BlendMode::None)
			;
		else if(blend_mode == BlendMode::Mix)
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

	struct MaterialBlockBase
	{
		MaterialBlockBase() {}
		MaterialBlockBase(GfxSystem& gfx)
			: s_skeleton(bgfx::createUniform("s_skeleton", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialBase>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t skeleton = uint32_t(TextureSampler::Skeleton);
			bgfx::setViewUniform(pass.m_index, s_skeleton, &skeleton);
		}

		void upload(bgfx::Encoder& encoder, const MaterialBase& block) const
		{
			UNUSED(encoder); UNUSED(block);
#if !MATERIALS_BUFFER
			GpuState<MaterialBase>::me.upload(encoder, block);
#endif
		}

		bgfx::UniformHandle s_skeleton;
	};

	struct MaterialBlockAlpha
	{
		MaterialBlockAlpha() {}
		MaterialBlockAlpha(GfxSystem& gfx)
			: s_alpha(bgfx::createUniform("s_alpha", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialAlpha>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t alpha = uint32_t(TextureSampler::Alpha);
			bgfx::setViewUniform(pass.m_index, s_alpha, &alpha);
		}

		void upload(bgfx::Encoder& encoder, const MaterialAlpha& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialAlpha>::me.upload(encoder, block);
#endif
			if(is_valid(block.m_alpha.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Alpha), *block.m_alpha.m_texture);
		}

		bgfx::UniformHandle s_alpha;
	};

	struct MaterialBlockSolid
	{
		MaterialBlockSolid() {}
		MaterialBlockSolid(GfxSystem& gfx)
			: s_color(bgfx::createUniform("s_color", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialSolid>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint32_t color = uint32_t(TextureSampler::Color);
			bgfx::setViewUniform(pass.m_index, s_color, &color);
		}

		void upload(bgfx::Encoder& encoder, const MaterialSolid& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialSolid>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_colour.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Color), *block.m_colour.m_texture);
		}

		bgfx::UniformHandle s_color;
	};

	struct MaterialBlockPoint
	{
		MaterialBlockPoint() {}
		MaterialBlockPoint(GfxSystem& gfx)
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialPoint>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			UNUSED(pass);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPoint& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPoint>::me.upload(encoder, block);
#endif
		}
	};

	struct MaterialBlockLine
	{
		MaterialBlockLine() {}
		MaterialBlockLine(GfxSystem& gfx)
		{
			UNUSED(gfx);
#if !MATERIALS_BUFFER
			GpuState<MaterialLine>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			UNUSED(pass);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLine& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLine>::me.upload(encoder, block);
#endif
		}
	};

	struct MaterialBlockFresnel
	{
		MaterialBlockFresnel() {}
		MaterialBlockFresnel(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_fresnel(bgfx::createUniform("s_fresnel", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialFresnel>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			uint8_t color = int8_t(TextureSampler::Color);
			bgfx::setViewUniform(pass.m_index, s_fresnel, &color);
		}

		void upload(bgfx::Encoder& encoder, const MaterialFresnel& block) const
		{
#if !MATERIALS_BUFFER
			//GpuState<MaterialFresnel>::me.upload(encoder, block);
#endif

			encoder.setTexture(uint8_t(TextureSampler::Color), block.m_value.m_texture ? *block.m_value.m_texture : *m_white_tex);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_fresnel;
	};

	struct MaterialBlockUser
	{
		MaterialBlockUser() {}
		MaterialBlockUser(GfxSystem& gfx)
			: m_white_tex(&gfx.default_texture(TextureHint::White))
			, s_user0(bgfx::createUniform("s_user0", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_user1(bgfx::createUniform("s_user1", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_user2(bgfx::createUniform("s_user2", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_user3(bgfx::createUniform("s_user3", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_user4(bgfx::createUniform("s_user4", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_user5(bgfx::createUniform("s_user5", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialUser>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			const uint32_t user0 = uint32_t(TextureSampler::User0);
			const uint32_t user1 = uint32_t(TextureSampler::User1);
			const uint32_t user2 = uint32_t(TextureSampler::User2);
			const uint32_t user3 = uint32_t(TextureSampler::User3);
			const uint32_t user4 = uint32_t(TextureSampler::User4);
			const uint32_t user5 = uint32_t(TextureSampler::User5);

			bgfx::setViewUniform(pass.m_index, s_user0, &user0);
			bgfx::setViewUniform(pass.m_index, s_user1, &user1);
			bgfx::setViewUniform(pass.m_index, s_user2, &user2);
			bgfx::setViewUniform(pass.m_index, s_user3, &user3);
			bgfx::setViewUniform(pass.m_index, s_user4, &user4);
			bgfx::setViewUniform(pass.m_index, s_user5, &user5);
		}

		void upload(bgfx::Encoder& encoder, const MaterialUser& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialUser>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_tex0)) encoder.setTexture(uint8_t(TextureSampler::User0), *block.m_tex0);
			if(is_valid(block.m_tex1)) encoder.setTexture(uint8_t(TextureSampler::User1), *block.m_tex1);
			if(is_valid(block.m_tex2)) encoder.setTexture(uint8_t(TextureSampler::User2), *block.m_tex2);
			if(is_valid(block.m_tex3)) encoder.setTexture(uint8_t(TextureSampler::User3), *block.m_tex3);
			if(is_valid(block.m_tex4)) encoder.setTexture(uint8_t(TextureSampler::User4), *block.m_tex4);
			if(is_valid(block.m_tex5)) encoder.setTexture(uint8_t(TextureSampler::User5), *block.m_tex5);
		}

		Texture* m_white_tex;

		bgfx::UniformHandle s_user0;
		bgfx::UniformHandle s_user1;
		bgfx::UniformHandle s_user2;
		bgfx::UniformHandle s_user3;
		bgfx::UniformHandle s_user4;
		bgfx::UniformHandle s_user5;
	};
	
	struct MaterialBlockLit
	{
		MaterialBlockLit() {}
		MaterialBlockLit(GfxSystem& gfx)
			: m_black_tex (&gfx.default_texture(TextureHint::Black))
			, s_emissive(bgfx::createUniform("s_emissive", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_normal(bgfx::createUniform("s_normal", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_occlusion(bgfx::createUniform("s_ambient_occlusion", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_displace(bgfx::createUniform("s_displace", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLit>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			const uint32_t normal    = uint32_t(TextureSampler::Normal);
			const uint32_t emissive  = uint32_t(TextureSampler::Emissive);
			const uint32_t ao        = uint32_t(TextureSampler::AO);
			const uint32_t displace  = uint32_t(TextureSampler::Displace);

			bgfx::setViewUniform(pass.m_index, s_normal, &normal);
			bgfx::setViewUniform(pass.m_index, s_emissive, &emissive);
			bgfx::setViewUniform(pass.m_index, s_occlusion, &ao);
			bgfx::setViewUniform(pass.m_index, s_displace, &displace);
		}

		void upload(bgfx::Encoder& encoder, const MaterialLit& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialLit>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_normal.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Normal), *block.m_normal.m_texture);

			if(is_valid(block.m_emissive.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Emissive), *block.m_emissive.m_texture);
			else if(block.m_emissive.m_value.a > 0.f)
				encoder.setTexture(uint8_t(TextureSampler::Emissive), *m_black_tex);

			if(is_valid(block.m_occlusion.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::AO), *block.m_occlusion.m_texture);

			if(is_valid(block.m_displace.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Displace), *block.m_displace.m_texture);
		}

		Texture* m_black_tex;

		bgfx::UniformHandle s_emissive;
		bgfx::UniformHandle s_normal;
		bgfx::UniformHandle s_occlusion;
		//bgfx::UniformHandle s_lightmap;
		bgfx::UniformHandle s_displace;
	};

	struct MaterialBlockPbr
	{
		MaterialBlockPbr() {}
		MaterialBlockPbr(GfxSystem& gfx)
			: s_albedo(bgfx::createUniform("s_albedo", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_metallic (bgfx::createUniform("s_metallic", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_roughness(bgfx::createUniform("s_roughness", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_depth(bgfx::createUniform("s_depth", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPbr>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			const uint32_t albedo    = uint32_t(TextureSampler::Color);
			const uint32_t metallic  = uint32_t(TextureSampler::Metallic);
			const uint32_t roughness = uint32_t(TextureSampler::Roughness);
			//const uint32_t depth     = uint32_t(TextureSampler::Depth);

			bgfx::setViewUniform(pass.m_index, s_albedo, &albedo);
			bgfx::setViewUniform(pass.m_index, s_metallic, &metallic);
			bgfx::setViewUniform(pass.m_index, s_roughness, &roughness);
			//bgfx::setViewUniform(pass.m_index, s_depth, &depth);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPbr& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPbr>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_albedo.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Color), *block.m_albedo.m_texture);
			if(is_valid(block.m_metallic.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Metallic), *block.m_metallic.m_texture);
			if(is_valid(block.m_roughness.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Roughness), *block.m_roughness.m_texture);

			if(is_valid(block.m_depth.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Depth), *block.m_depth.m_texture);
		}

		bgfx::UniformHandle s_albedo;
		bgfx::UniformHandle s_metallic;
		bgfx::UniformHandle s_roughness;
		bgfx::UniformHandle s_depth;
		//bgfx::UniformHandle s_lightmap;
	};


	struct MaterialBlockPhong
	{
		MaterialBlockPhong() {}
		MaterialBlockPhong(GfxSystem& gfx)
			: s_diffuse(bgfx::createUniform("s_diffuse", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_specular(bgfx::createUniform("s_specular", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			, s_shininess(bgfx::createUniform("s_shininess", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
			//, s_lightmap(bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View))
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPhong>::me.init();
#endif
		}

		void prepare(const Pass& pass) const
		{
			const uint32_t diffuse = uint32_t(TextureSampler::Diffuse);
			const uint32_t specular = uint32_t(TextureSampler::Specular);
			const uint32_t shininess = uint32_t(TextureSampler::Shininess);

			bgfx::setViewUniform(pass.m_index, s_diffuse, &diffuse);
			bgfx::setViewUniform(pass.m_index, s_specular, &specular);
			bgfx::setViewUniform(pass.m_index, s_shininess, &shininess);
		}

		void upload(bgfx::Encoder& encoder, const MaterialPhong& block) const
		{
#if !MATERIALS_BUFFER
			GpuState<MaterialPhong>::me.upload(encoder, block);
#endif

			if(is_valid(block.m_diffuse.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Diffuse), *block.m_diffuse.m_texture);
			if(is_valid(block.m_specular.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Specular), *block.m_specular.m_texture);
			if(is_valid(block.m_shininess.m_texture))
				encoder.setTexture(uint8_t(TextureSampler::Shininess), *block.m_shininess.m_texture);
		}

		bgfx::UniformHandle s_diffuse;
		bgfx::UniformHandle s_specular;
		bgfx::UniformHandle s_shininess;
	};

	GfxSystem* Material::ms_gfx = nullptr;

	void load_material(Material& material, Program& program)
	{
		material.m_program = &program;
	}

	static uint16_t s_material_index = 0;

	static MaterialBlockBase s_base_material_block = {};
	static MaterialBlockAlpha s_alpha_material_block = {};
	static MaterialBlockSolid s_solid_material_block = {};
	static MaterialBlockLine s_line_material_block = {};
	static MaterialBlockPoint s_point_material_block = {};
	static MaterialBlockFresnel s_fresnel_material_block = {};
	static MaterialBlockLit s_lit_material_block = {};
	static MaterialBlockPbr s_pbr_material_block = {};
	static MaterialBlockPhong s_phong_material_block = {};
	static MaterialBlockUser s_user_material_block = {};

	ShaderBlock MaterialBase::s_block = ShaderBlock({ "VERTEX_COLOR", "DOUBLE_SIDED", "FLAT_SHADED" }, {});
	ShaderBlock MaterialAlpha::s_block = ShaderBlock({ "ALPHA_MAP", "ALPHA_TEST" }, {});
	ShaderBlock MaterialSolid::s_block = ShaderBlock({ "COLOR_MAP" }, {});
	ShaderBlock MaterialLine::s_block = ShaderBlock({ "DASH" }, {});
	ShaderBlock MaterialPoint::s_block = ShaderBlock();
	ShaderBlock MaterialFresnel::s_block = ShaderBlock();
	ShaderBlock MaterialLit::s_block = ShaderBlock({ "NORMAL_MAP", "EMISSIVE", "AMBIENT_OCCLUSION", "LIGHTMAP", "DISPLACEMENT" }, {});
	ShaderBlock MaterialPbr::s_block = ShaderBlock({ "ALBEDO_MAP", "ROUGHNESS_MAP", "METALLIC_MAP", "DEPTH_MAPPING", "DEEP_PARALLAX" },  // "REFRACTION", "ANISOTROPY", 
												   { "DIFFUSE_MODE", "SPECULAR_MODE" });
	ShaderBlock MaterialPhong::s_block = ShaderBlock({ "DIFFUSE_MAP", "SPECULAR_MAP", "SHININESS_MAP", "REFRACTION", "TOON" }, { "ENV_BLEND" });
	ShaderBlock MaterialUser::s_block = ShaderBlock();

	Material::Material(const string& name)
		: m_index(s_material_index++) // uint16_t(index(type<Material>(), Ref(this))))//
		, m_name(name)
	{
		m_pbr.m_diffuse_mode = PbrDiffuseMode::Lambert;

		static bool init_blocks = true;
		if(init_blocks)
		{
			s_base_material_block = { *ms_gfx };
			s_alpha_material_block = { *ms_gfx };
			s_solid_material_block = { *ms_gfx };
			s_line_material_block = { *ms_gfx };
			s_point_material_block = { *ms_gfx };
			s_fresnel_material_block = { *ms_gfx };
			s_lit_material_block = { *ms_gfx };
			s_pbr_material_block = { *ms_gfx };
			s_phong_material_block = { *ms_gfx };
			s_user_material_block = { *ms_gfx };

			init_blocks = false;
		}
	}

	ProgramVersion Material::program(const Program& program) const
	{
		ProgramVersion version = { program };

		version.set_option(MaterialBase::s_block.m_index, VERTEX_COLOR, m_base.m_shader_color == ShaderColor::Vertex);
		version.set_option(MaterialBase::s_block.m_index, DOUBLE_SIDED, m_base.m_cull_mode == CullMode::None);
		version.set_option(MaterialBase::s_block.m_index, FLAT_SHADED, m_base.m_flat_shaded);

		if(program.m_blocks[MaterialBlock::Alpha])
		{
			//version.set_option(MaterialAlpha::s_block.m_index, ALPHA, m_alpha.m_is_alpha);
			version.set_option(MaterialAlpha::s_block.m_index, ALPHA_TEST, m_alpha.m_alpha_test);
			version.set_option(MaterialAlpha::s_block.m_index, ALPHA_MAP, is_valid(m_alpha.m_alpha.m_texture));
		}

		if(program.m_blocks[MaterialBlock::Solid])
		{
			version.set_option(MaterialSolid::s_block.m_index, COLOR_MAP, is_valid(m_solid.m_colour.m_texture));
		}

		if(program.m_blocks[MaterialBlock::Line])
		{
			version.set_option(MaterialLine::s_block.m_index, DASH, m_line.m_dashed);
		}

		if(program.m_blocks[MaterialBlock::Lit])
		{
			version.set_option(MaterialLit::s_block.m_index, NORMAL_MAP, is_valid(m_lit.m_normal.m_texture));
			version.set_option(MaterialLit::s_block.m_index, EMISSIVE, is_valid(m_lit.m_emissive.m_texture) || m_lit.m_emissive.m_value.a > 0.f);
			version.set_option(MaterialLit::s_block.m_index, AMBIENT_OCCLUSION, is_valid(m_lit.m_occlusion.m_texture));
			version.set_option(MaterialLit::s_block.m_index, DISPLACEMENT, is_valid(m_lit.m_displace.m_texture));
		}

		if(program.m_blocks[MaterialBlock::Pbr])
		{
			version.set_mode(MaterialPbr::s_block.m_index, DIFFUSE_MODE, uint8_t(m_pbr.m_diffuse_mode));
			version.set_mode(MaterialPbr::s_block.m_index, SPECULAR_MODE, uint8_t(m_pbr.m_specular_mode));

			version.set_option(MaterialPbr::s_block.m_index, ALBEDO_MAP, is_valid(m_pbr.m_albedo.m_texture));
			version.set_option(MaterialPbr::s_block.m_index, ROUGHNESS_MAP, is_valid(m_pbr.m_roughness.m_texture));
			version.set_option(MaterialPbr::s_block.m_index, METALLIC_MAP, is_valid(m_pbr.m_metallic.m_texture));

			//version.set_option(MaterialPbr::s_block.m_index, REFRACTION, m_pbr.m_refraction.m_value != 0.f);
			version.set_option(MaterialPbr::s_block.m_index, DEPTH_MAPPING, is_valid(m_pbr.m_depth.m_texture));
			version.set_option(MaterialPbr::s_block.m_index, DEEP_PARALLAX, m_pbr.m_deep_parallax);
		}

		if(program.m_blocks[MaterialBlock::Phong])
		{
			version.set_mode(MaterialPhong::s_block.m_index, ENV_BLEND, uint8_t(m_phong.m_env_blend));

			version.set_option(MaterialPhong::s_block.m_index, DIFFUSE_MAP, is_valid(m_phong.m_diffuse.m_texture));
			version.set_option(MaterialPhong::s_block.m_index, SPECULAR_MAP, is_valid(m_phong.m_specular.m_texture));
			version.set_option(MaterialPhong::s_block.m_index, SHININESS_MAP, is_valid(m_phong.m_shininess.m_texture));

			version.set_option(MaterialPhong::s_block.m_index, REFRACTION, m_phong.m_refraction.m_value != 0.f);
			version.set_option(MaterialPhong::s_block.m_index, TOON, m_phong.m_toon);
		}

		return version;
	}

	ProgramVersion Material::program(const Program& program, const Item& item, const ModelElem& elem) const
	{
		ProgramVersion version = this->program(program);
		
		bool colours = (elem.m_mesh->m_vertex_format & VertexAttribute::Colour) != 0;
		colours |= (item.m_batch != nullptr); // if instancing we assume we might have colors too

		version.set_option(MaterialBase::s_block.m_index, VERTEX_COLOR, colours && m_base.m_shader_color == ShaderColor::Vertex);

		return version;
	}

	void Material::state(uint64_t& bgfx_state) const
	{
		// @todo cleanup culling flag responsibility, flipping etc
		if(m_base.m_cull_mode == CullMode::None
		|| m_base.m_cull_mode == CullMode::Front)
			bgfx_state &= ~BGFX_STATE_CULL_MASK;
		if(m_base.m_cull_mode == CullMode::Front)
			bgfx_state |= BGFX_STATE_CULL_CCW;

		if(m_base.m_depth_test == DepthTest::Disabled)
			bgfx_state &= ~BGFX_STATE_DEPTH_TEST_MASK;

		if(m_base.m_depth_draw == DepthDraw::Enabled)
			bgfx_state |= BGFX_STATE_WRITE_Z;
		if(m_base.m_depth_draw == DepthDraw::Disabled)
			bgfx_state &= ~BGFX_STATE_WRITE_Z;
	}

	void Material::submit(const Program& program, bgfx::Encoder& encoder, uint64_t& bgfx_state, const Skin* skin) const
	{
		this->state(bgfx_state);

		//if(program.m_blocks[MaterialBlock::Point])
			bgfx_state |= BGFX_STATE_POINT_SIZE(uint(m_point.m_point_size));

#if MATERIALS_BUFFER
		const BlockMaterial& block = *ms_gfx->m_renderer.block<BlockMaterial>();
		vec4 state = { 0.f, float(m_index), 0.f, 0.f };
		encoder.setUniform(block.u_state, &state);
		encoder.setUniform(block.u_state_vertex, &state);
		encoder.setTexture(uint8_t(TextureSampler::Materials), block.s_materials, block.m_materials_texture.texture, TEXTURE_POINT | TEXTURE_CLAMP);
#endif

		s_base_material_block.upload(encoder, m_base);
		if(program.m_blocks[MaterialBlock::Alpha])
			s_alpha_material_block.upload(encoder, m_alpha);
		if(program.m_blocks[MaterialBlock::Solid])
			s_solid_material_block.upload(encoder, m_solid);
		if(program.m_blocks[MaterialBlock::Point])
			s_point_material_block.upload(encoder, m_point);
		if(program.m_blocks[MaterialBlock::Line])
			s_line_material_block.upload(encoder, m_line);
		if(program.m_blocks[MaterialBlock::Lit])
			s_lit_material_block.upload(encoder, m_lit);
		if(program.m_blocks[MaterialBlock::Pbr])
			s_pbr_material_block.upload(encoder, m_pbr);
		if(program.m_blocks[MaterialBlock::Phong])
			s_phong_material_block.upload(encoder, m_phong);
		if(program.m_blocks[MaterialBlock::Fresnel])
			s_fresnel_material_block.upload(encoder, m_fresnel);
		if(program.m_blocks[MaterialBlock::User])
			s_user_material_block.upload(encoder, m_user);

		if(skin)
			encoder.setTexture(uint8_t(TextureSampler::Skeleton), skin->m_texture);

		if(m_submit)
			m_submit(encoder);
	}

	BlockMaterial::BlockMaterial(GfxSystem& gfx)
		: GfxBlock(gfx, *this)
	{}

	void BlockMaterial::init_block()
	{
		u_state = bgfx::createUniform("u_state", bgfx::UniformType::Vec4);
		u_state_vertex = bgfx::createUniform("u_state_vertex", bgfx::UniformType::Vec4);

		s_materials = bgfx::createUniform("s_materials", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
	}

	void BlockMaterial::begin_render(Render& render)
	{
		UNUSED(render);
#if MATERIALS_BUFFER
		const vector<Material*> materials = m_gfx.materials().m_vector;
		for(uint32_t i = 0; i < materials.size(); ++i)
			materials[i]->m_index = i;
		GpuState<Material>::me.pack(m_materials_texture, materials);
#endif
	}

	void BlockMaterial::submit(Render& render, const Pass& pass)
	{
		uint32_t materials = uint32_t(TextureSampler::Materials);
		bgfx::setViewUniform(pass.m_index, s_materials, &materials);

		s_base_material_block.prepare(pass);
		s_alpha_material_block.prepare(pass);
		s_solid_material_block.prepare(pass);
		s_point_material_block.prepare(pass);
		s_line_material_block.prepare(pass);
		s_fresnel_material_block.prepare(pass);
		s_lit_material_block.prepare(pass);
		s_pbr_material_block.prepare(pass);
		s_phong_material_block.prepare(pass);
		s_user_material_block.prepare(pass);
	}
}


module two.gfx;

#include <meshoptimizer.h>

#include <cstdio>
#include <cstring>

namespace two
{
	bgfx::VertexDecl create_vertex_decl(uint32_t vertex_format)
	{
		bgfx::VertexDecl decl;

		bool half_support = (bgfx::getCaps()->supported & BGFX_CAPS_VERTEX_ATTRIB_HALF) != 0;
		bool needs_half = (vertex_format & VertexAttribute::QTexCoord0) != 0
					   || (vertex_format & VertexAttribute::QTexCoord1) != 0;
		if(needs_half && !half_support)
			printf("[warning] half vertex attribute not supported but used by texcoords\n");

		bool normalize_indices = false;
#ifdef TWO_PLATFORM_EMSCRIPTEN
		normalize_indices = true;
#endif

		decl.begin();

		if((vertex_format & VertexAttribute::Position) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::Position4) != 0)
			decl.add(bgfx::Attrib::Position, 4, bgfx::AttribType::Float);
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

	GpuMesh::GpuMesh() {}
	GpuMesh::GpuMesh(PrimitiveType primitive, uint32_t vertex_count, uint32_t index_count)
		: m_primitive(primitive), m_vertex_count(vertex_count), m_index_count(index_count)
	{}

	GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count, bool index32)
	{
		GpuMesh gpu_mesh = { primitive, vertex_count, index_count };

		gpu_mesh.m_vertex_memory = bgfx::alloc(vertex_count * vertex_size(vertex_format));
		if(index_count > 0)
			gpu_mesh.m_index_memory = bgfx::alloc(index_count * (index32 ? sizeof(uint32_t) : sizeof(uint16_t)));
		gpu_mesh.m_index32 = index32;

		gpu_mesh.m_vertices = { gpu_mesh.m_vertex_memory->data, vertex_count };
		if(index_count > 0)
			gpu_mesh.m_indices = { gpu_mesh.m_index_memory->data, index_count };

		gpu_mesh.m_vertex_format = vertex_format;
		gpu_mesh.m_writer = MeshAdapter(vertex_format, gpu_mesh.m_vertices, gpu_mesh.m_indices, index32);

		return gpu_mesh;
	}

	GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		return alloc_mesh(primitive, vertex_format, vertex_count, index_count, vertex_count > UINT16_MAX);
	}

	GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		return alloc_mesh(PrimitiveType::Triangles, vertex_format, vertex_count, index_count, vertex_count > UINT16_MAX);
	}

	template <class T>
	void optimize_mesh(const GpuMesh& mesh, GpuMesh& optmesh)
	{
		size_t vertex_stride = vertex_size(mesh.m_vertex_format);

		vector<unsigned int> remap(mesh.m_vertex_count);
		uint32_t index_count = mesh.m_index_count > 0 ? mesh.m_index_count : mesh.m_vertex_count;
		size_t vertex_count = meshopt_generateVertexRemap(remap.data(), (T*)mesh.m_indices.data(), index_count, mesh.m_vertices.data(), mesh.m_vertex_count, vertex_stride);

		// we can't allocate a new mesh with different index size because meshoptimizer remap functions don't allow for different types of indices
		optmesh = alloc_mesh(mesh.m_primitive, mesh.m_vertex_format, uint32_t(vertex_count), index_count, mesh.m_index32);

		optmesh.m_writer.m_aabb = mesh.m_writer.m_aabb;
		optmesh.m_writer.m_uv0_rect = mesh.m_writer.m_uv0_rect;
		optmesh.m_writer.m_uv1_rect = mesh.m_writer.m_uv1_rect;

		meshopt_remapIndexBuffer((T*)optmesh.m_indices.data(), (T*)mesh.m_indices.data(), index_count, remap.data());

		meshopt_remapVertexBuffer(optmesh.m_vertices.data(), mesh.m_vertices.data(), mesh.m_vertex_count, vertex_stride, remap.data());

		meshopt_optimizeVertexCache((T*)optmesh.m_indices.data(), (T*)optmesh.m_indices.data(), index_count, vertex_count);

		meshopt_optimizeOverdraw((T*)optmesh.m_indices.data(), (T*)optmesh.m_indices.data(), index_count, (float*)optmesh.m_vertices.data(), vertex_count, vertex_stride, 1.05f);

		meshopt_optimizeVertexFetch(optmesh.m_vertices.data(), (T*)optmesh.m_indices.data(), index_count, optmesh.m_vertices.data(), vertex_count, vertex_stride);

		//meshopt_simplify(optmesh.m_indices, optmesh.m_indices, index_count, optmesh.m_vertices, vertex_count, vertex_stride);
	}

	template <class T>
	GpuMesh optimize_mesh(const GpuMesh& mesh)
	{
		GpuMesh optmesh;
		optimize_mesh<T>(mesh, optmesh);
		return optmesh;
	}

	static uint16_t s_mesh_index = 0;

	Mesh::Mesh(const string& name, bool readback)
		: m_name(name)
		, m_index(++s_mesh_index)
		, m_readback(readback)
		, m_material(nullptr)
	{}

	Mesh::~Mesh()
	{
		this->clear();
	}

	void Mesh::clear()
	{
		if(m_is_dynamic)
		{
			if(bgfx::isValid(m_dynamic.m_vertices)) bgfx::destroy(m_dynamic.m_vertices);
			if(bgfx::isValid(m_dynamic.m_indices)) bgfx::destroy(m_dynamic.m_indices);
		}
		else
		{
			if(bgfx::isValid(m_vertices)) bgfx::destroy(m_vertices);
			if(bgfx::isValid(m_indices)) bgfx::destroy(m_indices);
		}
	}

	void Mesh::upload(const GpuMesh& gpu_mesh, bool optimize)
	{
		if(optimize)
		{
			if(gpu_mesh.m_index32)
				return this->upload(optimize_mesh<uint32_t>(gpu_mesh));
			else
				return this->upload(optimize_mesh<uint16_t>(gpu_mesh));
		}

		this->clear();

		m_primitive = gpu_mesh.m_primitive;
		//m_draw_mode = draw_mode;
		m_vertex_format = gpu_mesh.m_vertex_format;
		m_vertex_count = gpu_mesh.m_vertex_count;
		m_index_count = gpu_mesh.m_index_count;
		m_index32 = gpu_mesh.m_index32;
		m_is_dynamic = gpu_mesh.m_dynamic;

		if(gpu_mesh.m_dynamic)
		{
			m_dynamic.m_vertices = bgfx::createDynamicVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
			if(gpu_mesh.m_index_count > 0)
				m_dynamic.m_indices = bgfx::createDynamicIndexBuffer(gpu_mesh.m_index_memory, m_index32 ? BGFX_BUFFER_INDEX32 : 0);
		}
		else
		{
			m_vertices = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
			if(gpu_mesh.m_index_count > 0)
				m_indices = bgfx::createIndexBuffer(gpu_mesh.m_index_memory, m_index32 ? BGFX_BUFFER_INDEX32 : 0);
		}

		m_aabb = aabb(gpu_mesh.m_writer.m_aabb.lo, gpu_mesh.m_writer.m_aabb.hi);
		m_uv0_rect = { gpu_mesh.m_writer.m_uv0_rect.lo, gpu_mesh.m_writer.m_uv0_rect.hi };
		m_uv1_rect = { gpu_mesh.m_writer.m_uv1_rect.lo, gpu_mesh.m_writer.m_uv1_rect.hi };

		if((gpu_mesh.m_vertex_format & VertexAttribute::Position) != 0)
		{
			MeshAdapter reader = gpu_mesh.m_writer.read();
			m_radius = 0.f;
			for(size_t i = 0; i < reader.m_vertex_count; ++i)
				m_radius = max(m_radius, length(reader.position() - m_aabb.m_center));
		}

		m_origin = m_aabb.m_center;

		if(m_readback)
			this->cache(gpu_mesh);
	}

	void Mesh::write(const MeshPacker& packer, bool optimize, bool dynamic)
	{
		m_qnormals = packer.m_quantize;

		GpuMesh gpu_mesh = alloc_mesh(packer.m_primitive, packer.vertex_format(), packer.vertex_count(), packer.index_count());
		packer.pack(gpu_mesh.m_writer);
		gpu_mesh.m_writer.rewind();
		gpu_mesh.m_dynamic = dynamic;

		this->upload(gpu_mesh, optimize);
	}

	void Mesh::xwrite(const MeshPacker& packer, const mat4& transform, bool optimize, bool dynamic)
	{
		m_qnormals = packer.m_quantize;

		GpuMesh gpu_mesh = alloc_mesh(packer.m_primitive, packer.vertex_format(), packer.vertex_count(), packer.index_count());
		packer.xpack(gpu_mesh.m_writer, transform);
		gpu_mesh.m_writer.rewind();
		gpu_mesh.m_dynamic = dynamic;

		this->upload(gpu_mesh, optimize);
	}

	void Mesh::morph(const MeshPacker& packer)
	{
		const uint32_t vertex_format = VertexAttribute::Position 
			| (!packer.m_normals.empty() ? VertexAttribute::Normal : 0);

		GpuMesh gpu_mesh = alloc_mesh(packer.m_primitive, vertex_format, packer.vertex_count(), packer.index_count());
		packer.pack(gpu_mesh.m_writer);

		Morph& morph = push(m_morphs);
		morph.m_vertices = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
	}

	void Mesh::cache(const GpuMesh& gpu_mesh)
	{
		m_cached_vertices.resize(gpu_mesh.m_vertex_memory->size);
		if(gpu_mesh.m_index_count)
			m_cached_indices.resize(gpu_mesh.m_index_memory->size);

		memcpy(m_cached_vertices.data(), gpu_mesh.m_vertex_memory->data, gpu_mesh.m_vertex_memory->size);
		if(gpu_mesh.m_index_count)
			memcpy(m_cached_indices.data(), gpu_mesh.m_index_memory->data, gpu_mesh.m_index_memory->size);

		m_cache = MeshAdapter(gpu_mesh.m_vertex_format, { m_cached_vertices.data(), m_vertex_count }, { m_cached_indices.data(), m_index_count }, m_index32);
		m_cache.rewind();
	}

	GpuMesh Mesh::begin()
	{
		return alloc_mesh(m_primitive, m_vertex_format, m_vertex_count, m_index_count, m_index32);
	}

	void Mesh::update(const GpuMesh& gpu_mesh)
	{
		bgfx::update(m_dynamic.m_vertices, 0U, gpu_mesh.m_vertex_memory);
		if(gpu_mesh.m_index_count > 0)
			bgfx::update(m_dynamic.m_indices, 0U, gpu_mesh.m_index_memory);
	}

	MeshAdapter& Mesh::direct(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		m_vertex_format = vertex_format;
		m_vertex_count = vertex_count;
		m_index_count = index_count;

		const bgfx::VertexDecl& decl = vertex_decl(vertex_format);
		bgfx::allocTransientVertexBuffer(&m_direct.m_vertices, vertex_count, decl);
		if(index_count)
			bgfx::allocTransientIndexBuffer(&m_direct.m_indices, index_count);

		m_direct.m_adapter = { vertex_format, { m_direct.m_vertices.data, vertex_count } };
		return m_direct.m_adapter;
	}

	void Mesh::submit_morph(bgfx::Encoder& encoder, size_t index, size_t morph) const
	{
		static auto morph_decl = [](VertexAttribute::Enum attrib, bgfx::Attrib::Enum battrib)
		{
			UNUSED(attrib);
			bgfx::VertexDecl decl;
			decl.begin();
			decl.add(battrib, 3, bgfx::AttribType::Float);
			decl.end();
			return bgfx::createVertexDecl(decl);
		};

		static bgfx::VertexDeclHandle morph_decls[4] =
		{
			morph_decl(VertexAttribute::MorphPosition0, bgfx::Attrib::TexCoord2),
			morph_decl(VertexAttribute::MorphPosition1, bgfx::Attrib::TexCoord3),
			morph_decl(VertexAttribute::MorphPosition2, bgfx::Attrib::TexCoord4),
			morph_decl(VertexAttribute::MorphPosition3, bgfx::Attrib::TexCoord5),
		};

		static bgfx::VertexDeclHandle normal_decls[4] =
		{
			morph_decl(VertexAttribute::MorphNormal0, bgfx::Attrib::TexCoord6),
			morph_decl(VertexAttribute::MorphNormal1, bgfx::Attrib::TexCoord7),
			morph_decl(VertexAttribute::MorphNormal2, bgfx::Attrib::Color1),
			morph_decl(VertexAttribute::MorphNormal3, bgfx::Attrib::Color2),
		};

		encoder.setVertexBuffer(1 + index, m_morphs[morph].m_vertices, 0, m_vertex_count, morph_decls[index]);
	}

	uint64_t Mesh::submit(bgfx::Encoder& encoder) const
	{
		if(m_is_dynamic)
			encoder.setVertexBuffer(0, m_dynamic.m_vertices);
		else if(m_is_direct)
			encoder.setVertexBuffer(0, &m_direct.m_vertices);
		else
			encoder.setVertexBuffer(0, m_vertices);

		if(m_index_count > 0)
		{
			if(m_is_dynamic)
				encoder.setIndexBuffer(m_dynamic.m_indices, m_range.m_start, m_range.m_count);
			else if(m_is_direct)
				encoder.setIndexBuffer(&m_direct.m_indices);
			else
				encoder.setIndexBuffer(m_indices);
		}

		constexpr table<PrimitiveType, uint64_t> bgfx_primitive =
		{
			BGFX_STATE_PT_POINTS,
			BGFX_STATE_PT_LINES,
			BGFX_STATE_PT_LINESTRIP,
			0, // default,
			BGFX_STATE_PT_TRISTRIP,
			0, // unsupported
		};

		uint64_t flags = bgfx_primitive[m_primitive];
		// line aa needs blend mode to be alpha, and it looks ugly anyway (and only works in GL)
		//if(m_primitive == PrimitiveType::Lines || m_primitive == PrimitiveType::LineStrip)
		//	flags |= BGFX_STATE_LINEAA;
		return flags;
	}
}


module two.gfx;

namespace two
{
	//static uint16_t s_model_index = 0;

	GfxSystem* Model::ms_gfx = nullptr;

	Model::Model(const string& name)
		: m_name(name)
		, m_index(uint16_t(index(type<Model>(), Ref(this))))//++s_model_index)
	{}

	Model::~Model()
	{}

	Mesh& Model::get_mesh(size_t index)
	{
		return *m_items[index].m_mesh;
	}

	Mesh& Model::add_mesh(const string& name, bool readback)
	{
		Mesh& mesh = ms_gfx->meshes().construct(name, readback);
		return mesh;
	}

	Rig& Model::add_rig(const string& name)
	{
		UNUSED(name);
		m_rig = &ms_gfx->rigs().construct();
		return *m_rig;
	}

	ModelElem& Model::add_item(Mesh& mesh, const mat4& transform, int skin, const Colour& colour, Material* material)
	{
		m_items.push_back({ m_items.size(), &mesh, transform != bxidentity(), transform, skin, colour, material });
		return m_items.back();
	}

	void Model::prepare()
	{
		m_aabb = {};
		m_radius = 0.f;

		for(const ModelElem& item: m_items)
		{
			m_geometry[item.m_mesh->m_primitive] = true;
			m_aabb.merge(transform_aabb(item.m_mesh->m_aabb, item.m_transform));
		}

		m_radius = sqrt(2.f) * max(m_aabb.m_extents.x, max(m_aabb.m_extents.y, m_aabb.m_extents.z));

		m_origin = m_aabb.m_center;
	}

	Model& model_variant(GfxSystem& gfx, Model& original, const string& name, span<string> materials, span<Material*> substitutes)
	{
		Model& variant = gfx.models().create(name);
		variant = original;

		for(ModelElem& item : variant.m_items)
			for(size_t i = 0; i < materials.size(); ++i)
			{
				if(item.m_mesh->m_material->m_name == materials[i])
					item.m_material = substitutes[i];
			}

		return variant;
	}
}

#ifndef TWO_CPP_20
#include <cstdio>
#endif

#include <bx/math.h>

module two.gfx;

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

namespace two
{
	bx::Vec3 bxvec3(const vec3& v) { return bx::Vec3(v.x, v.y, v.z); }
	mat4 bxidentity() { mat4 result; bx::mtxIdentity(value_ptr(result)); return result; }
	mat4 bxinverse(const mat4& mat) { mat4 result; bx::mtxInverse(value_ptr(result), value_ptr(mat)); return result; }
	mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans) { mat4 result; bx::mtxSRT(value_ptr(result), scale.x, scale.y, scale.z, rot.x, rot.y, rot.z, trans.x, trans.y, trans.z); return result; }
	mat4 bxscale(const vec3& scale) { mat4 result; bx::mtxScale(value_ptr(result), scale.x, scale.y, scale.z); return result; }
	mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuatLh(value_ptr(result), value_ptr(rot)); return result; }
	//mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), value_ptr(rot)); return transpose(result); }
	mat4 bxtranslation(const vec3& vec) { mat4 result; bx::mtxTranslate(value_ptr(result), vec.x, vec.y, vec.z); return result; }
	mat4 bxmul(const mat4& lhs, const mat4& rhs) { mat4 result; bx::mtxMul(value_ptr(result), value_ptr(lhs), value_ptr(rhs)); return result; }
	vec4 bxmul(const mat4& mat, const vec4& vec) { vec4 result; bx::vec4MulMtx(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	vec3 bxmul(const mat4& mat, const vec3& vec) { bx::Vec3 result = bx::mul(bxvec3(vec), value_ptr(mat)); return vec3(result.x, result.y, result.z); }
	vec3 bxmulh(const mat4& mat, const vec3& vec) { bx::Vec3 result = bx::mulH(bxvec3(vec), value_ptr(mat)); return vec3(result.x, result.y, result.z); }
	mat4 bxlookat(const vec3& eye, const vec3& at) { mat4 result; bx::mtxLookAt(value_ptr(result), bxvec3(eye), bxvec3(at), bx::Vec3(0.f, 1.f, 0.f), bx::Handness::Right); return result; }
	void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up) { bx::mtxLookAt(value_ptr(result), bxvec3(eye), bxvec3(at), bxvec3(up), bx::Handness::Right); }
	mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up) { mat4 result; bx::mtxLookAt(value_ptr(result), bxvec3(eye), bxvec3(at), bxvec3(up), bx::Handness::Right); return result; }
	mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc) { mat4 result; bx::mtxProj(value_ptr(result), fov, aspect, near, far, oglNdc, bx::Handness::Right); return result; }
	mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrtho(value_ptr(result), rect.x, rect.y, rect.z, rect.w, near, far, offset, oglNdc, bx::Handness::Right); return result; }
	mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrtho(value_ptr(result), left, right, bottom, top, near, far, offset, oglNdc, bx::Handness::Right); return result; }
	mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxtranslation(trans), bxmul(bxrotation(rot), bxscale(scale))); }
	mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxscale(scale), bxmul(bxrotation(rot), bxtranslation(trans))); }

	vec3 mat4_position(const mat4& mat) { return vec3(mat[3]); }

	void debug_print_mat(const mat4& mat)
	{
		//vec3 scale = { length(vec3(mat[0])), length(vec3{ mat[1] }), length(vec3{ mat[2] }) };
		printf("pos %.1f, %.1f, %.1f \n", mat[3].x, mat[3].y, mat[3].z);
		//printf("orientation %f, %f, %f, %f\n", m_rotation.x, bone.m_rotation.y, bone.m_rotation.z, bone.m_rotation.w);)
	}

	static uint16_t s_node_index = 0;

	Node3::Node3()
	{}

	Node3::Node3(const mat4& transform, uint32_t parent)
		: m_transform(transform)
		, m_parent(parent)
	{}

	Node3::Node3(const vec3& position, const quat& rotation, const vec3& scale)
		: Node3(bxTRS(scale, rotation, position))
	{}

	void Node3::apply(const vec3& position, const quat& rotation, const vec3& scale)
	{
		m_transform = bxTRS(scale, rotation, position);
	}

	void Node3::derive(const Node3& parent, const vec3& position, const quat& rotation, const vec3& scale)
	{
		m_transform = parent.m_transform * bxTRS(scale, rotation, position);
	}

	vec3 Node3::position() const { return mulp(m_transform, vec3(0.f)); }
	vec3 Node3::axis(const vec3& dir) const { return muln(m_transform, dir); }
	vec3 Node3::direction() const { return muln(m_transform, -Z3); }
}


#include <bx/allocator.h>
#include <bimg/bimg.h>
#include <bgfx/bgfx.h>

module two.gfx;

#define SPRITE_TEXTURE_SIZE 2048U

namespace two
{
	bgfx::VertexDecl particle_vertex_decl()
	{
		bgfx::VertexDecl decl;

		decl.begin();
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
			decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
			decl.add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Float);
		decl.end();

		return decl;

		//ms_decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour | VertexAttribute::TexCoord0);
	}

	Flow::Flow()
	{}

	Flow::Flow(const string& name)
		: m_name(name)
	{}

	Flare::Flare(Node3* node, ShapeVar shape, uint32_t max_particles)
		: m_node(node)
		, m_max(max_particles)
	{
		m_shape = shape;
		m_particles.reserve(m_max);
	}

	void Flare::upload()
	{}

	void Flare::update(float delta)
	{
		m_time += delta;

		for(Particle& particle : m_particles)
			particle.life += delta / particle.lifetime;

		remove_if(m_particles, [&](Particle& particle) { return particle.life > m_duration; });

		m_ended = m_time > m_duration && !m_loop;
		if(!m_ended && m_rate.sample(m_time) > 0)
			spawn(delta);
	}


	void Flare::spawn(float dt)
	{
		mat4 transform = m_node ? m_node->m_transform : bxidentity();

		//quat rotation = m_rotation.sample(m_time, randf(0.f, 1.f));
		//vec3 position = m_position.sample(m_time, randf(0.f, 1.f));
		//transform = bxSRT(vec3(1.f), rotation, position) * transform;

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

			float volume = m_volume.sample(m_time, randf(0.f, 1.f));

			vec3 pos = points[ii] * volume;
			vec3 dir = m_flow == EmitterFlow::Outward ? normalize(points[ii]) : m_direction;

			particle.life = time;
			particle.lifetime = m_lifetime.sample(m_time, randf(0.f, 1.f));

			particle.start = mulp(transform, pos);
			particle.dir = muln(transform, dir);
			particle.rot = ZeroQuat; // m_node->m_rotation; // @todo

			particle.speed_seed = randf(0.f, 1.f);
			particle.angle_seed = randf(0.f, 1.f);
			particle.blend_seed = randf(0.f, 1.f);
			particle.colour_seed = randf(0.f, 1.f);
			particle.scale_seed = randf(0.f, 1.f);
			particle.sprite_seed = randf(0.f, 1.f);

			time += particle_period;

			m_particles.push_back(particle);
		}
	}

	uint32_t Flare::render(const SpriteAtlas& atlas, const mat4& view, const vec3& eye, uint32_t first, uint32_t max, ParticleSort* outSort, ParticleVertex* outVertices)
	{
		m_aabb =
		{
			vec3(FLT_MAX),
			vec3(-FLT_MAX),
		};

		if(m_sprite == nullptr)
			return 0;
		
		uint32_t index = first;
		for(Particle& particle : m_particles)
		{
			if(index + 1 >= max)
				break;

			vec3 gravity = { 0.0f, -9.81f * m_gravity.sample(particle.life) * sq(particle.life), 0.0f };
			UNUSED(gravity);

			float advance = particle.life * particle.lifetime * m_speed.sample(particle.life, particle.speed_seed);
			vec3 pos = particle.start + particle.dir * advance; //+ gravity;

			ParticleSort& sort = outSort[index];
			vec3 tmp = eye - pos;
			sort.dist = sqrt(dot(tmp, tmp));
			sort.idx = index;

			float blend = m_blend.sample(particle.life, particle.blend_seed);
			float scale = m_scale.sample(particle.life, particle.scale_seed);

			Colour colour = m_colour.sample(particle.life, particle.colour_seed);
			uint32_t abgr = to_abgr(colour);

			vec3 udir;
			vec3 vdir;

			if(m_billboard)
			{
				udir = scale * vec3(view[0][0], view[1][0], view[2][0]);
				vdir = scale * vec3(view[0][1], view[1][1], view[2][1]);
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

	inline void Flare::write_vertex(ParticleVertex*& dest, ParticleVertex vertex)
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

	ParticleSystem::ParticleSystem(GfxSystem& gfx, TPool<Flare>& emitters)
		: m_gfx(gfx)
		, m_block(*gfx.m_renderer.block<BlockParticles>())
		, m_emitters(emitters)
		, m_program(gfx.programs().fetch("particle").default_version())
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
		for(Flare* emitter : m_emitters.m_vec_pool->m_objects)
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

		static bgfx::VertexDecl decl = particle_vertex_decl();

		const uint32_t numVertices = min(bgfx::getAvailTransientVertexBuffer(m_num * 4, decl), uint32_t(UINT16_MAX));
		const uint32_t numIndices = bgfx::getAvailTransientIndexBuffer(m_num * 6);
		const uint32_t max = min(numVertices / 4, numIndices / 6);
		BX_WARN(m_num == max, "Truncating transient buffer for particles to maximum available (requested %d, available %d).", m_num, max);

		if(0 < max)
		{
			bgfx::TransientVertexBuffer vertex_buffer;
			bgfx::TransientIndexBuffer index_buffer;

			bgfx::allocTransientBuffers(&vertex_buffer, decl, max * 4, &index_buffer, max * 6);

			vector<ParticleSort> particleSort{ max };

			uint32_t pos = 0;
			ParticleVertex* vertices = (ParticleVertex*)vertex_buffer.data;

			for(Flare* emitter : m_emitters.m_vec_pool->m_objects)
				pos += emitter->render(*m_block.m_sprites, view, eye, pos, max, particleSort.data(), vertices);

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

	BlockParticles::BlockParticles(GfxSystem& gfx)
		: GfxBlock(gfx, type<BlockParticles>())
		, m_sprites(construct<SpriteAtlas>(uvec2(SPRITE_TEXTURE_SIZE)))
	{}

	BlockParticles::~BlockParticles()
	{
		bgfx::destroy(m_texture);
		bgfx::destroy(s_color);
	}

	void BlockParticles::init_block()
	{
		s_color = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
		m_texture = { uvec2(SPRITE_TEXTURE_SIZE), false, TextureFormat::BGRA8 };

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

	Sprite* BlockParticles::create_sprite(cstring name, cstring pathname, uvec2 frames)
	{
		LocatedFile location = m_gfx.locate_file("textures/particles/" + string(pathname));
		bimg::ImageContainer* image = load_bgfx_image(m_gfx, location.path(true), bgfx::TextureFormat::BGRA8);
		Sprite* sprite = this->create_sprite(name, uvec2(image->m_width, image->m_height), frames, image->m_data);
		bimg::imageFree(image);
		return sprite;
	}

	Sprite* BlockParticles::create_sprite(cstring name, const uvec2& size, uvec2 frames, const void* data)
	{
		Sprite* sprite = m_sprites->add_sprite(name, size, frames);
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

	void pass_particles(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		Pass particle_pass = render.next_pass("particles", PassType::Particles);
		bgfx::Encoder& encoder = *particle_pass.m_encoder;

		render.m_scene->m_particle_system->update(render.m_frame->m_delta_time); // * timeScale
		render.m_scene->m_particle_system->render(encoder, particle_pass.m_index, render.m_camera->m_view, render.m_camera->m_eye);
	}
}


module two.gfx;

#include <bx/bx.h>
#include <bgfx/bgfx.h>

namespace two
{
#define PICKING_FOV 3.0f

	Picker::Picker(GfxSystem& gfx, FrameBuffer& target)
		: m_target(target)
		, m_size(target.m_size) //PICKING_BUFFER_SIZE)
		, m_program(gfx.programs().fetch("picking_id"))
		, m_data(target.m_size.x * target.m_size.y)
	{
		u_picking_id = bgfx::createUniform("u_picking_id", bgfx::UniformType::Vec4);
		
		uint64_t flags = TEXTURE_POINT | BGFX_SAMPLER_MIP_POINT | TEXTURE_CLAMP;

		if((bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0 && (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_READ_BACK) != 0)
			m_readback_texture = { m_size, false, TextureFormat::RGBA8, 0 | BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK | flags };

		m_fbo_texture = { m_size, false, TextureFormat::RGBA8, 0 | BGFX_TEXTURE_RT | flags };
		m_fbo_depth = { m_size, false, TextureFormat::D24S8, 0 | BGFX_TEXTURE_RT | flags };

		m_fbo = { m_size, { &m_fbo_texture, &m_fbo_depth } };
	}

	Picker::~Picker()
	{}

	void Picker::pick_point(Viewport& viewport, vec2 position, PickCallback callback, uint32_t mask)
	{
		if(m_query) return;
		const Ray ray = viewport.ray(position);
		const float fov = viewport.m_camera->m_fov / m_size.y;// / float(m_target->m_size.y);
		m_query = { { uvec2(position), uvec2(1U) }, ray, fov, viewport.m_camera->m_aspect, mask };
		m_query.m_callback = callback;
	}

	void Picker::pick_rectangle(Viewport& viewport, vec4 rect, MultipickCallback callback, uint32_t mask)
	{
		if(m_query) return;
		const Ray ray = viewport.ray(rect_center(rect));
		const float fov = viewport.m_camera->m_fov * rect.height / m_size.y;
		const float aspect = rect.width / rect.height;
		m_query = { uvec4(rect), ray, fov, aspect, mask };
		m_query.m_multi_callback = callback;
	}

	void Picker::process(Render& render, PickQuery& query)
	{
		if(!query || render.m_shot.m_items.empty()) return;

		uint8_t view = render.picking_pass();

		bgfx::setViewFrameBuffer(view, m_fbo);
		bgfx::setViewClear(view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff, 1.0f, 0);

		mat4 pickView = bxlookat(query.m_center_ray.m_start, query.m_center_ray.m_end);
		mat4 pickProj = bxproj(query.m_fov, query.m_aspect, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewName(view, "picking");
		uint16_t rect_y = bgfx::getCaps()->originBottomLeft ? uint16_t(m_size.y - query.m_rect.height) : 0;
		bgfx::setViewRect(view, 0, rect_y, uint16_t(query.m_rect.width), uint16_t(query.m_rect.height));
		bgfx::setViewTransform(view, value_ptr(pickView), value_ptr(pickProj));
		
		//Frustum frustum = { pickProj, pickView, 0.1f, 1000.f, query.m_fov, query.m_aspect };

		for(uint32_t index = 0; index < render.m_shot.m_items.size(); ++index)
		{
			Item& item = *render.m_shot.m_items[index];

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

			for(const ModelElem& elem : item.m_model->m_items)
			{
				Material& material = elem.m_mesh->m_material ? *elem.m_mesh->m_material : *item.m_material;

				ProgramVersion program = { m_program };
				program.set_option(0, BILLBOARD, item.m_flags & ItemFlag::Billboard);

				uint64_t render_state = BGFX_STATE_DEFAULT;
				material.state(render_state);
				item.submit(encoder, render_state, elem);

				encoder.setState(render_state);
				encoder.submit(view, m_program.version(program));
			}

			bgfx::end(&encoder);
		}

		// every time the blit to CPU texture is finished, we read the focused item
		if(query.m_readback_ready <= render.m_frame->m_frame)
		{
			Item* item = nullptr;
			vector<Item*> items = {};

			// not sure which is more efficient
			//vector<uint32_t> counts(render.m_items.size());
			map<uint32_t, uint32_t> counts; 
			uint32_t maxAmount = 0;

			//span<uint32_t> data = { m_data.data(), query.m_rect.width * query.m_rect.height };
			//for(const uint32_t& id : data)
			for(size_t x = 0; x < query.m_rect.width; ++x)
				for(size_t y = 0; y < query.m_rect.height; ++y)
				{
					size_t offset = x + y * m_size.x;
					const uint32_t& id = m_data[offset];

					if(id == uint32_t(255 << 24) || id >= render.m_shot.m_items.size())
						continue;

					add(items, render.m_shot.m_items[id]);

					uint32_t count = ++counts[id];
					if(count > maxAmount && id < render.m_shot.m_items.size())
					{
						maxAmount = count;
						item = render.m_shot.m_items[id];
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
				bgfx::blit(render.picking_pass(), m_readback_texture, 0, 0, m_fbo_texture, 0, 0, uint16_t(query.m_rect.width), uint16_t(query.m_rect.height));
				query.m_readback_ready = bgfx::readTexture(m_readback_texture, m_data.data());
			}
			else
			{
				query.m_readback_ready = bgfx::readTexture(m_fbo_texture, m_data.data());
			}
		}
	}
	

}


module two.gfx;

namespace two
{
	void pipeline_minimal(GfxSystem& gfx, Renderer& pipeline, bool deferred)
	{
		UNUSED(deferred);

		BlockMaterial& material = pipeline.add_block<BlockMaterial>(gfx);
		UNUSED(material);

		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx, filter);
		UNUSED(copy);

		// pipeline
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx, filter);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx);
		UNUSED(sky);
		UNUSED(particles);

		vector<ShaderBlock*> depth_blocks =  { &depth };

		auto create_programs = [&]()
		{
			Program& solid = gfx.programs().create("solid");
			solid.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Solid });

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(depth_blocks);
			depth.set_blocks({ MaterialBlock::Alpha });

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(depth_blocks);
			distance.set_blocks({ MaterialBlock::Alpha });

			Program& pbr = gfx.programs().create("pbr/pbr");
			pbr.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr });

			Program& fresnel = gfx.programs().create("fresnel");
			fresnel.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Fresnel });
		};

		create_programs();

		gfx.set_renderer(Shading::Shaded, render_minimal);
		gfx.set_renderer(Shading::Volume, render_minimal);

		pipeline.m_gather_func = gather_render;
	}

	void render_minimal(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_particles(gfx, render);
		pass_solid(gfx, render);
	}

	void render_solid(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_solid(gfx, render);
	}

	void render_clear(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
	}

	static uint8_t s_blank = 0;
	static uint8_t s_zero = 1;

	struct ClearInit
	{
		ClearInit()
		{
			bgfx::setPaletteColor(s_blank, 0.f, 0.f, 0.f, 1.f);
			bgfx::setPaletteColor(s_zero, 0.f, 0.f, 0.f, 0.f);
		};
	};

	void pass_clear_fbo(GfxSystem& gfx, Render& render, FrameBuffer& fbo, const Colour& colour, float depth)
	{
		UNUSED(gfx);
		Pass pass = render.next_pass("clear", PassType::Clear);

		bgfx::setViewRect(pass.m_index, 0, 0, uint16_t(fbo.m_size.x), uint16_t(fbo.m_size.y));
		bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, to_rgba(colour), depth);
		bgfx::setViewFrameBuffer(pass.m_index, fbo);

		bgfx::touch(pass.m_index);
	}

	void pass_clear(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		static ClearInit init;

		Pass pass = render.next_pass("clear", PassType::Clear);

		if(render.m_target && render.m_target->m_mrt) //pass.m_use_mrt)
			bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_blank, s_blank, s_blank, s_blank);
		else
			bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, to_rgba(render.m_viewport->m_clear_colour), 1.f, 0);

		bgfx::touch(pass.m_index);
	}

	void pass_gclear(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		if(render.m_target && render.m_target->m_deferred)
		{
			Pass pass = render.next_pass("clear gbuffer", PassType::Clear);
			bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_zero, s_zero, s_zero, s_zero);
			bgfx::setViewFrameBuffer(pass.m_index, render.m_target->m_gbuffer.m_fbo);
			bgfx::touch(pass.m_index);
		}
	}

	void pass_solid(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		Pass pass = render.next_pass("solid", PassType::Solid);
		
		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL
							  | BGFX_STATE_MSAA | BGFX_STATE_CULL_CW;// | BGFX_STATE_BLEND_ALPHA;

		bgfx::Encoder& encoder = *pass.m_encoder;
		for(ImmediateDraw* immediate : render.m_shot.m_immediate)
			immediate->submit(encoder, pass.m_index, pass.m_bgfx_state);

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(render);
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Solid] && !program.m_blocks[MaterialBlock::Fresnel])
				return false;

			blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

	void pass_background(GfxSystem& gfx, Render& render)
	{
		static BlockSky& block_sky = *gfx.m_renderer.block<BlockSky>();

		//Pass pass = render.next_pass("background", PassType::Background);
		block_sky.submit_pass(render);
	}

	void pass_flip(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("flip", PassType::Flip);
		gfx.m_copy->quad(pass, render.m_target->m_backbuffer, render.m_target->m_diffuse);
	}
}


module two.gfx;

namespace two
{
#ifdef TWO_PREFABNODE
	PrefabNode::PrefabNode()
	{}

	void PrefabNode::draw(Gnode& parent)
	{
		Gnode& self = gfx::node(parent); // , m_object);
		Gnode& item = gfx::node(self, m_transform.m_position, m_transform.m_rotation, m_transform.m_scale); // Ref(this), 

		if(m_call.m_callable)
			m_call.m_args[0] = Ref(&item);
		if(m_call.validate())
			m_call();
		//else
		//	printf("[warning] invalid prefab node element arguments\n");

		for(PrefabNode& node : m_nodes)
			node.draw(self);
	}
#endif

	Prefab::Prefab(const string& name)
		: m_name(name)
	{}

	void Prefab::add(Scene& scene, Mime* mime)
	{
		span<Node3> nodes = gfx::nodes(scene).addvec(m_nodes);

		for(Elem& elem : m_items)
		{
			Item& it = gfx::items(scene).add(Item(nodes[elem.node], *elem.item.m_model, elem.item.m_flags));
		}

		if(mime)
		{
			mime->add_nodes(nodes);
			mime->m_anims = m_anims;
		}
	}

	Prefab& import_prefab(GfxSystem& gfx, ModelFormat format, const string& name, const ImportConfig& config)
	{
		LocatedFile location = gfx.locate_file("models/" + name, { format == ModelFormat::obj ? ".obj" : ".gltf" });
		Prefab& prefab = gfx.prefabs().create(name);
		gfx.importer(format)->import_prefab(prefab, location.path(false), config);
		return prefab;
	}

	void destroy_prefab(GfxSystem& gfx, Prefab& prefab)
	{
		set<Model*> models;
		for(Prefab::Elem& elem : prefab.m_items)
			models.insert(elem.item.m_model);

		for(Model* model : models)
		{
			for(ModelElem& elem : model->m_items)
			{
				gfx.meshes().destroy(Ref(elem.m_mesh));
			}

			gfx.models().destroy(model->m_name);
		}
	}
}


#include <bx/platform.h>
#include <bx/readerwriter.h>
#include <bgfx/bgfx.h>

module two.gfx;

#include <cstring>
#include <cstdio>

namespace bgfx
{
	int compileShader(int _argc, const char* _argv[]);
	void getShaderError(char* _outputText, uint16_t& _outputSize);
}

namespace two
{
	static const bgfx::Memory* load_mem(bx::FileReaderI& reader, const char* file_path)
	{
		if(!bx::open(&reader, file_path))
		{
			printf("[ERROR] failed to open file %s\n", file_path);
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
			printf("[ERROR] gfx - failed to load program %s\n", shader_path.c_str());
		//else
		//	printf("[info] gfx - loaded program %s id %i\n", shader_path.c_str(), int(program.idx));

		return program;
	}

	static table<ShaderType, cstring> c_shader_suffixes = 
	{
		"_cs.sc",
		"_fs.sc",
		"_gs.sc",
		"_vs.sc",
	};

	string shader_path(GfxSystem& gfx, const string& name, ShaderType shader_type)
	{
		string suffix = c_shader_suffixes[shader_type];
		return gfx.m_resource_path + "/shaders/" + name + suffix;
	}

#ifdef TWO_LIVE_SHADER_COMPILER
	bool compile_shader(GfxSystem& gfx, const string& name, const string& suffix, ShaderType shader_type, const string& defines_in, const string& source)
	{
		string defines = defines_in;
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;

		string source_path = shader_path(gfx, name, shader_type);

		if(source != "")
		{
			write_file(source_path, source);
		}

#ifdef _DEBUG
		//bool debug = true;
#else
		//bool debug = false;
#endif

		static table<ShaderType, cstring> output_suffixes = { "_cs", "_fs", "_gs", "_vs" };

		string output_suffix = output_suffixes[shader_type];
		string output_path = gfx.m_resource_path + "/shaders/compiled/" + name + suffix + output_suffix;

		create_file_tree(output_path);

		printf("[info] gfx - compiling shader : %s\n", source_path.c_str());
		printf("[info] gfx - defines : %s\n", defines.c_str());

		string include = gfx.m_resource_path + "/shaders/";
		string varying_path = gfx.m_resource_path + "/shaders/varying.def.sc";

		enum Target { GLSL, ESSL, HLSL, Metal };
#if BX_PLATFORM_WINDOWS
		Target target = is_opengl ? GLSL : HLSL;
#elif BX_PLATFORM_LINUX
		Target target = GLSL; UNUSED(is_opengl);
#elif BX_PLATFORM_EMSCRIPTEN
		//Target target = ESSL; UNUSED(is_opengl);
		Target target = GLSL; UNUSED(is_opengl);
#elif BX_PLATFORM_OSX
		Target target = is_opengl ? GLSL : Metal;
#endif

		if(target == ESSL || target == Metal)
			defines += "NO_TEXEL_FETCH;";

		vector<cstring> args;
		auto push_arg = [&args](cstring name, cstring arg) { args.push_back(name); args.push_back(arg); };

		static table<ShaderType, cstring> types = { "compute", "fragment", "geometry", "vertex" };

		push_arg("-f", source_path.c_str());
		push_arg("-o", output_path.c_str());
		push_arg("-i", include.c_str());
		args.push_back("--depends");
		push_arg("--varyingdef", varying_path.c_str());
		push_arg("--define", defines.c_str());
		push_arg("--type", types[shader_type]);

		//if(debug)
			//args.push_back("--debug");

		args.push_back("-O3");

		if(target == GLSL)
		{
			push_arg("--platform", "linux");
			//push_arg("--profile", "120");
			push_arg("--profile", "130");
			//push_arg("--profile", "430");
		}
		else if(target == ESSL)
		{
			push_arg("--platform", "android");
		}
		else if(target == HLSL)
		{
			static table<ShaderType, cstring> profiles = { "cs_5_0", "ps_5_0", "gs_5_0", "vs_5_0" };
			push_arg("--platform", "windows");
			push_arg("--profile", profiles[shader_type]);
		}
		else if(target == Metal)
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

			printf("[ERROR] failed to compile %s (%s), defines = %s\n", source_path.c_str(), output_path.c_str(), defines.c_str());
			printf("%s\n", output_text);
			return false;
		}

		return true;
	}
#endif

	struct Program::Impl
	{
		map<uint64_t, Version> m_versions;
	};

	GfxSystem* Program::ms_gfx = nullptr;

	static uint8_t s_block_index = 1;

	ShaderBlock::ShaderBlock()
		: m_index(s_block_index++)
	{}

	ShaderBlock::ShaderBlock(span<cstring> options, span<cstring> modes)
		: m_index(s_block_index++)
	{
		for(cstring option : options)
			m_options.push_back(option);
		for(cstring mode : modes)
			m_modes.push_back(mode);
	}

	Program::Program(const string& name, bool compute)
		: m_name(name)
		, m_compute(compute)
		, m_impl(make_unique<Impl>())
	{
		static string options[] = { "INSTANCING", "BILLBOARD", "SKELETON", "MORPHTARGET", "QNORMALS", "VFLIP", "MRT", "DEFERRED", "CLUSTERED" };
		this->register_options(0, options);

		this->set_block(MaterialBlock::Base);

		if constexpr(ZONES_BUFFER)
			m_defines.push_back({ "ZONES_BUFFER" , "" });

		if constexpr(LIGHTS_BUFFER)
			m_defines.push_back({ "LIGHTS_BUFFER" , "" });

		if constexpr(MATERIALS_BUFFER)
			m_defines.push_back({ "MATERIALS_BUFFER" , "" });
	}

	Program::~Program()
	{}

	void Program::set_block(MaterialBlock type, bool enabled)
	{
		static table<MaterialBlock, ShaderBlock*> shader_blocks =
		{ {
			&MaterialBase::s_block,
			&MaterialAlpha::s_block,
			&MaterialSolid::s_block,
			&MaterialPoint::s_block,
			&MaterialLine::s_block,
			&MaterialLit::s_block,
			&MaterialPbr::s_block,
			&MaterialPhong::s_block,
			&MaterialFresnel::s_block,
			&MaterialUser::s_block,
		} };

		m_blocks[type] = enabled;
		this->register_block(*shader_blocks[type]);
	}

	void Program::set_blocks(span<MaterialBlock> blocks)
	{
		for(MaterialBlock type : blocks)
		{
			this->set_block(type);
		}
	}

	void Program::register_blocks(const Program& program)
	{
		this->register_blocks(program.m_registered_blocks);
	}

	void Program::register_blocks(span<ShaderBlock*> blocks)
	{
		for(ShaderBlock* block : blocks)
		{
			this->register_block(*block);
			m_registered_blocks.push_back(block);
		}
	}

	void Program::register_block(const ShaderBlock& block)
	{
		assert(block.m_index < 32);
		m_shader_blocks[block.m_index].m_enabled = true;
		this->register_options(block.m_index, block.m_options);
		this->register_modes(block.m_index, block.m_modes);
		if(block.m_defines.size() > 0)
			prepend(m_defines, block.m_defines);
	}

	void Program::register_options(uint8_t block, span<string> options)
	{
		assert(block < 32);
		m_shader_blocks[block].m_enabled = true;
		m_shader_blocks[block].m_option_shift = uint8_t(m_options.size());

		for(size_t i = 0; i < options.size(); ++i)
			m_options.push_back(options[i]);
	}

	void Program::register_modes(uint8_t block, span<string> modes)
	{
		assert(block < 32);
		m_shader_blocks[block].m_enabled = true;
		m_shader_blocks[block].m_mode_shift = uint8_t(m_modes.size());

		for(size_t i = 0; i < modes.size(); ++i)
			m_modes.push_back(modes[i]);
	}

	void Program::set_pass(PassType type, bool enabled)
	{
		m_passes[type] = enabled;
	}

	void Program::set_source(ShaderType type, const string& source)
	{
		m_sources[type] = source;
	}

	string Program::defines(const ProgramVersion& version) const
	{
		string defines = "";

		for(size_t option = 0; option < 32; ++option)
			if(version.m_options & uint32_t(1 << option))
				defines += m_options[option] + ";";

		for(size_t mode = 0; mode < m_modes.size(); ++mode)
			defines += m_modes[mode] + "=" + to_string(version.m_modes[mode]) + ";";

		for(const ShaderDefine& define : m_defines)
			defines += string(define.m_name) + (define.m_value.empty() ? "" : "=" + define.m_value) + ";";

		return defines;
	}

	ProgramVersion Program::program(Version& version)
	{
		ProgramVersion config = { *this };
		memcpy(&config.m_options, &version.m_version, sizeof(uint64_t));
		return config;
	}

	void Program::compile(GfxSystem& gfx, Version& version, bool compute)
	{
		const ProgramVersion config = this->program(version);

		const string suffix = "_v" + to_string(version.m_version);
		const string defines = this->defines(config);

		bool compiled = true;
#ifdef TWO_LIVE_SHADER_COMPILER
		if(compute)
		{
			compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Compute, defines, m_sources[ShaderType::Compute]);
		}
		else
		{
			compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Vertex, defines, m_sources[ShaderType::Vertex]);
			compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Fragment, defines, m_sources[ShaderType::Fragment]);

			if(file_exists(shader_path(gfx, m_name, ShaderType::Geometry).c_str()))
				compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Geometry, defines, m_sources[ShaderType::Geometry]);
		}
#endif

		const string full_name = m_name + suffix;

		if(!compiled)
		{
			printf("[warning] gfx - failed to compile program %s : using last valid version instead\n", full_name.c_str());
			version.m_update = m_update;
			return;
		}

		printf("[info] gfx - loading program %s with options %s\n", full_name.c_str(), defines.c_str());
		const string compiled_path = gfx.m_resource_path + "/shaders/compiled/" + full_name;
		version.m_program = compute ? load_compute_program(gfx.file_reader(), compiled_path)
									: load_program(gfx.file_reader(), compiled_path);
		version.m_update = m_update;
	}

	void Program::update(GfxSystem& gfx)
	{
		for(auto& hash_version : m_impl->m_versions)
		{
			Version& version = hash_version.second;
			if(version.m_update < m_update)
			{
				this->compile(gfx, version, m_compute);
			}
		}
	}

	bgfx::ProgramHandle Program::default_version()
	{
		ProgramVersion config = { *this };
		return this->version(config);
	}

	bgfx::ProgramHandle Program::version(const ProgramVersion& config)
	{
		uint64_t version_hash = config.hash();

		Version& version = m_impl->m_versions[version_hash];
		if(version.m_update < m_update)
		{
			version.m_version = version_hash;
			this->compile(*ms_gfx, version, m_compute);
		}

		return version.m_program;
	}
}


module two.gfx;

#include <Tracy.hpp>

//#define TWO_GFX_JOBS

namespace two
{
	struct RenderUniform
	{
		RenderUniform() {}
		RenderUniform(int)
			: u_render_p0(bgfx::createUniform("u_render_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View))
			, u_viewport_p0(bgfx::createUniform("u_viewport_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View))
			, u_camera_p0(bgfx::createUniform("u_camera_p0", bgfx::UniformType::Vec4, 1U, bgfx::UniformSet::View))
		{}

		bgfx::UniformHandle u_render_p0;
		bgfx::UniformHandle u_viewport_p0;
		bgfx::UniformHandle u_camera_p0;
	};

	static RenderUniform s_render_uniform;

	Render::Render(Shading shading, Viewport& viewport, RenderTarget& target, RenderFrame& frame)
		: m_shading(shading), m_scene(viewport.m_scene), m_target(&target), m_fbo(&target), m_viewport(&viewport), m_rect(viewport.m_rect)
		, m_camera(viewport.m_camera), m_frame(&frame), m_env(&viewport.m_scene->m_env)
		, m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
	{
		static bool init_uniform = true;
		if(init_uniform)
		{
			s_render_uniform = { 0 };
			init_uniform = false;
		}
	}

	Render::Render(Shading shading, Viewport& viewport, RenderTarget& target, FrameBuffer& target_fbo, RenderFrame& frame)
		: m_shading(shading), m_scene(viewport.m_scene), m_target(&target), m_fbo(&target_fbo), m_viewport(&viewport), m_rect(viewport.m_rect)
		, m_camera(viewport.m_camera), m_frame(&frame), m_env(&viewport.m_scene->m_env)
		, m_filters(viewport), m_lighting(viewport.m_lighting)
		, m_pass_index(frame.m_render_pass)
	{}

	Render::~Render()
	{}

	void Render::subrender(const Render& render)
	{
		m_shot = render.m_shot;
	}

	Pass Render::next_pass(cstring name, PassType type)
	{
		Pass pass;
		pass.m_name = name;
		pass.m_target = m_target;
		pass.m_bgfx_state = 0;
		pass.m_fbo = m_fbo;
		pass.m_viewport = m_viewport;
		pass.m_rect = m_rect;
		pass.m_use_mrt = m_needs_mrt;
		pass.m_index = m_pass_index++;
		pass.m_pass_type = type;

		pass.m_encoder = bgfx::begin();

		bgfx::setViewName(pass.m_index, name);

		//printf("[info] render pass %s\n", name.c_str());
		m_viewport->pass(pass);

		this->set_uniforms(pass);

		return pass;
	}

	Pass Render::composite_pass(cstring name)
	{
		return this->next_pass(name, PassType::PostProcess);
	}

	Pass Render::composite_pass(cstring name, FrameBuffer& fbo, const vec4& rect)
	{
		Pass pass = this->next_pass(name, PassType::PostProcess);
		pass.m_fbo = &fbo;
		pass.m_rect = rect;
		return pass;
	}

	void Render::set_uniforms(const Pass& pass) const
	{
		vec4 render_p0 = { m_frame->m_time, float(bgfx::getCaps()->originBottomLeft), 0.f, 0.f };
		bgfx::setViewUniform(pass.m_index, s_render_uniform.u_render_p0, &render_p0);

		if(m_target)
		{
			vec4 screen_p0 = { vec2(m_target->m_size), 1.0f / vec2(m_target->m_size) };
			bgfx::setViewUniform(pass.m_index, s_render_uniform.u_viewport_p0, &screen_p0);
		}

		vec4 camera_p0 = { m_camera->m_near, m_camera->m_far, m_camera->m_fov, m_camera->m_aspect };
		bgfx::setViewUniform(pass.m_index, s_render_uniform.u_camera_p0, &camera_p0);
	}

	struct DrawList : public vector<DrawElement>
	{
		struct SortByKey
		{
			inline bool operator()(const DrawElement& a, const DrawElement& b) { return a.m_sort_key < b.m_sort_key; }
		};

		DrawList(size_t size)
			: vector<DrawElement>(size)
		{}

		span<DrawElement> elements() { return{ this->first(), this->size() }; }

		DrawElement* first() { return &(*this)[0]; }

		DrawElement& add_element() { this->resize(this->size() + 1); return this->back(); }

		void sort() { quicksort<DrawElement>(*this, SortByKey()); }
	};

	struct Renderer::Impl
	{
		Impl() : m_draw_list(UINT16_MAX) {}
		DrawList m_draw_list;
	};

	Renderer::Renderer(GfxSystem& gfx)
		: m_gfx(gfx)
		, m_impl(make_unique<Impl>())
	{}

	Renderer::~Renderer()
	{}

	void Renderer::gather(Render& render)
	{
		m_gather_func(*render.m_scene, render);

		render.m_viewport->render(render);
		render.m_viewport->cull(render);
	}

	void Renderer::submit(Render& render, RenderFunc renderer)
	{
		this->gather(render);

#ifdef DEBUG_ITEMS
		scene.debug_items(render);
#endif

		if(render.m_viewport->m_rect.width != 0 && render.m_viewport->m_rect.height != 0)
			this->render(render, renderer);

		//m_gfx.m_copy->debug_show_texture(render, *render.m_env->m_background.m_texture, vec4(0.f), 0);
		//m_gfx.m_copy->debug_show_texture(render, *render.m_env->m_radiance.m_texture, vec4(0.f), 0);
		//if(render.m_env->m_radiance.m_filtered)
		//	m_gfx.m_copy->debug_show_texture(render, *render.m_env->m_radiance.m_filtered, vec4(0.f), 1);
		//copy.debug_show_texture(render, render.m_env->m_radiance.m_filtered, vec4(0.f), false, false, false, 1);
		//copy.debug_show_texture(render, bgfx::getTexture(render.m_target->m_effects.last()), vec4(0.f));
	}

	void Renderer::render(Render& render, RenderFunc renderer)
	{
		this->begin(render);
		renderer(m_gfx, render);
		this->end(render);
	}

	void Renderer::begin(Render& render)
	{
		this->block<BlockMaterial>()->begin_render(render);

		//for(const auto& block : m_gfx_blocks)
		//	block->begin_render(render);

		// @todo this temporarily fixes the MRT GL bug by forcing MRT in the shader even if not needed by any effects
		render.m_is_mrt = render.m_target && render.m_target->m_mrt;
		//render.m_is_mrt = render.m_needs_mrt && render.m_target && render.m_target->m_mrt;
	}

	void Renderer::end(Render& render)
	{
		render.m_frame->m_render_pass = render.m_pass_index;

		render.m_frame->m_num_draw_calls += render.m_num_draw_calls;
		render.m_frame->m_num_vertices += render.m_num_vertices;
		render.m_frame->m_num_triangles += render.m_num_triangles;
	}
	
	void Renderer::subrender(Render& render, Render& sub, RenderFunc renderer)
	{
		this->render(sub, renderer);
		render.m_pass_index = sub.m_pass_index;
	}

	GfxBlock::GfxBlock(GfxSystem& gfx, Type& type)
		: ShaderBlock()
		, m_gfx(gfx), m_type(type)
	{}

	GfxBlock::~GfxBlock()
	{}

	DrawElement::DrawElement(Item& item, const Program& program, const ModelElem& elem, const Material& material, const Skin* skin, uint64_t sort_key)
		: m_item(&item), m_elem(&elem), m_material(&material), m_skin(skin)
		, m_sort_key(sort_key)
	{
		this->set_program(program);
	}

	void DrawElement::set_program(const Program& program)
	{
		m_program = m_material->program(program, *m_item, *m_elem);
	}

	struct DrawPass
	{
		DrawList m_draw_elements;
	};

	void Renderer::shader_options(Render& render, Pass& pass, ProgramVersion& version) const
	{
		//for(GfxBlock* block : m_gfx.m_renderer.m_pass_blocks[pass.m_pass_type])
		//	if(block->m_draw_block)
		//		((DrawBlock*)block)->options(render, version);
	}

	void Renderer::element_options(Render& render, Pass& pass, DrawElement& element)
	{
		this->shader_options(render, pass, element.m_program);

		element.m_program.set_option(0, VFLIP, render.m_vflip && bgfx::getCaps()->originBottomLeft);
		element.m_program.set_option(0, MRT, render.m_is_mrt);

		element.m_program.set_option(0, INSTANCING, element.m_item->m_batch != nullptr);
		element.m_program.set_option(0, BILLBOARD, element.m_item->m_flags & ItemFlag::Billboard);
		element.m_program.set_option(0, SKELETON, element.m_skin != nullptr);
		element.m_program.set_option(0, MORPHTARGET, element.m_item->m_rig && !element.m_item->m_rig->m_morphs.empty());
		element.m_program.set_option(0, QNORMALS, element.m_elem->m_mesh->m_qnormals);

		Program& program = *const_cast<Program*>(element.m_program.m_program);
		element.m_bgfx_program = program.version(element.m_program);
	}

	void Renderer::add_element(Render& render, Pass& pass, DrawElement element)
	{
		this->element_options(render, pass, element);
		m_impl->m_draw_list.add_element() = element;
	}

	bool mask_primitive(uint32_t mask, PrimitiveType check)
	{
		uint32_t filter = 1 << uint(check);
		return (mask & filter) == 0;
	}

	inline Material& item_material(const Item& item, const ModelElem& elem, Material& fallback)
	{
		if(item.m_material)
			return *item.m_material;
		else if(elem.m_material)
			return *elem.m_material;
		else if(elem.m_mesh->m_material)
			return *elem.m_mesh->m_material;
		else
			return fallback;
	}

	DrawElement Renderer::draw_element(Item& item, const ModelElem& elem) const
	{
		static Material& fallback_material = m_gfx.debug_material();

		const Material& material = item_material(item, elem, fallback_material);
		const Program& program = *material.m_program;

		//if(mask_primitive(material.m_base.m_geometry_filter, elem.m_mesh->m_primitive))
		//	continue;

		const Skin* skin = (elem.m_skin > -1 && item.m_rig) ? &item.m_rig->m_skins[elem.m_skin] : nullptr;

		const uint64_t sort_key = uint64_t(material.m_index) << 0
								| uint64_t(elem.m_mesh->m_index) << 16;

		return { item, program, elem, material, skin, sort_key };
	}

	void Renderer::clear_draw_elements(Render& render, Pass& pass)
	{
		UNUSED(render); UNUSED(pass);
		m_impl->m_draw_list.clear();
	}

	void Renderer::gather_draw_elements(Render& render, Pass& pass)
	{
		for(Item* item : render.m_shot.m_items)
			for(const ModelElem& elem : item->m_model->m_items)
			{
				DrawElement element = this->draw_element(*item, elem);
				this->add_element(render, pass, element);
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

	void Renderer::submit_draw_elements(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, size_t first, size_t count) const
	{
		//printf("submit_draw_elements %i to %i\n", int(first), int(first + count));

		Pass thread_pass = pass;
		pass.m_encoder = &encoder;

		for(size_t i = first; i < first + count; ++i)
		{
			const DrawElement& element = m_impl->m_draw_list[i];
			this->submit(encoder, render, thread_pass, submit, element);
		}
	}

	void Renderer::submit(bgfx::Encoder& encoder, Render& render, Pass& pass, Submit submit, const DrawElement& element) const
	{
		//for(GfxBlock* block : m_gfx.m_renderer.m_pass_blocks[pass.m_pass_type])
		//	if(block->m_draw_block)
		//		((DrawBlock*)block)->submit(render, element, pass);

		if(submit)
			submit(m_gfx, render, pass, element);

		uint64_t render_state = 0 | pass.m_bgfx_state | element.m_bgfx_state;
		element.m_material->submit(*element.m_program.m_program, encoder, render_state, element.m_skin);
		element.m_item->submit(encoder, render_state, *element.m_elem);

		encoder.setGroup(bgfx::UniformSet::Group, element.m_material->m_index);
		encoder.setState(render_state);

		encoder.submit(pass.m_index, element.m_bgfx_program, depth_to_bits(element.m_item->m_depth));

		render.m_num_draw_calls += 1;
		render.m_num_vertices += element.m_elem->m_mesh->m_vertex_count;
		render.m_num_triangles += element.m_elem->m_mesh->m_index_count / 3;
	}

	void Renderer::begin_render_pass(Render& render, PassType pass_type)
	{
		//this->clear_draw_elements(render);
		//this->gather_draw_elements(render);

		for(PassJob& job : render.m_scene->m_pass_jobs->m_jobs[pass_type])
		{
			Pass pass = render.next_pass("job", pass_type); // pass.m_name);
			job(m_gfx, render, pass);
		}
	}

	void Renderer::submit_render_pass(Render& render, Pass& pass, Submit submit)
	{
		render.m_viewport->pass(pass);

		m_gfx.m_renderer.block<BlockMaterial>()->submit(render, pass);

		//for(GfxBlock* block : m_gfx.m_renderer.m_pass_blocks[pass.m_pass_type])
		//	if(block->m_draw_block)
		//		((DrawBlock*)block)->submit(render, pass);

#ifdef TWO_GFX_JOBS
		auto submit = [&](JobSystem& js, Job* job, size_t start, size_t count)
		{
			UNUSED(job);
			bgfx::Encoder& encoder = *m_gfx.m_encoders[js.thread()];
			this->submit_draw_elements(encoder, render, pass, start, count);
		};

		JobSystem& js = *m_gfx.m_job_system;
		Job* job = split_jobs<16>(js, nullptr, 0, uint32_t(m_impl->m_draw_elements.size()), submit);
		js.complete(job);
#else
		bgfx::Encoder& encoder = *pass.m_encoder;
		this->submit_draw_elements(encoder, render, pass, submit, 0, m_impl->m_draw_list.size());
#endif
	}

	void Renderer::pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit, bool sorted)
	{
		sorted = true;
		if(sorted)
			this->sorted_pass(render, pass, enqueue, submit);
		else
			this->direct_pass(render, pass, enqueue, submit);
	}

	void Renderer::sorted_pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit)
	{
		this->begin_render_pass(render, pass.m_pass_type);

		this->clear_draw_elements(render, pass);

		for(Item* item : render.m_shot.m_items)
			for(const ModelElem& elem : item->m_model->m_items)
			{
				DrawElement element = this->draw_element(*item, elem);
				if(enqueue(m_gfx, render, pass, element))
					this->add_element(render, pass, element);
			}

		this->submit_render_pass(render, pass, submit);
	}

	void Renderer::direct_pass(Render& render, Pass& pass, Enqueue enqueue, Submit submit)
	{
		this->begin_render_pass(render, pass.m_pass_type);

		for(Item* item : render.m_shot.m_items)
			for(const ModelElem& elem : item->m_model->m_items)
			{
				DrawElement element = this->draw_element(*item, elem);
				if(enqueue(m_gfx, render, pass, element))
				{
					this->element_options(render, pass, element);
					this->submit(*pass.m_encoder, render, pass, submit, element);
				}
			}
	}
}


#include <bgfx/bgfx.h>

module two.gfx;

#define TWO_GL_NO_MRT
//#define TWO_GFX_DEFERRED

namespace two
{
#if defined TWO_UNIFORM_BLOCKS
	TypedUniformBlock<RenderBlock> RenderBlock::s_block = { "render" };
#endif

	FrameBuffer::FrameBuffer()
	{}

	FrameBuffer::FrameBuffer(const uvec2& size, void* window)
		: m_size(size)
	{
		if(window == nullptr)
			m_fbo = BGFX_INVALID_HANDLE;
		else
			m_fbo = bgfx::createFrameBuffer(window, uint16_t(size.x), uint16_t(size.y));

#if defined TWO_UNIFORM_BLOCKS
		m_render_block.m_render_size = vec2(m_size);
		m_render_block.m_pixel_size = 1.0f / vec2(m_size);
#endif
	}

	FrameBuffer::FrameBuffer(const uvec2& size, TextureFormat format, uint64_t flags)
		: FrameBuffer(size)
	{
		m_tex = { size, false, format, flags | BGFX_TEXTURE_RT };
		m_fbo = bgfx::createFrameBuffer(1, &m_tex.m_tex, false);
	}
	
	FrameBuffer::FrameBuffer(const uvec2& size, span<Texture*> textures)
		: FrameBuffer(size)
	{
		bgfx::TextureHandle handles[6];
		for(size_t i = 0; i < textures.size(); ++i)
		{
			m_attach[i] = textures[i];
			handles[i] = textures[i]->m_tex;
		}
		m_fbo = bgfx::createFrameBuffer(uint8_t(textures.size()), handles, false);
	}

	FrameBuffer::FrameBuffer(const uvec2& size, Texture& texture, span<bgfx::Attachment> attach)
		: FrameBuffer(size)
	{
		m_fbo = bgfx::createFrameBuffer(attach.size(), attach.data(), false);
	}

	FrameBuffer::FrameBuffer(Texture& texture)
		: FrameBuffer(texture.m_size)
	{
		m_fbo = bgfx::createFrameBuffer(1, &texture.m_tex, false);
	}

	FrameBuffer::~FrameBuffer()
	{
		if(bgfx::isValid(m_fbo))
			bgfx::destroy(m_fbo);
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& other)
	{
		*this = move(other);
	}

	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other)
	{
		m_fbo = other.m_fbo;
		m_size = other.m_size;
		m_tex = move(other.m_tex);
		for(size_t i = 0; i < 6; ++i)
			m_attach[i] = other.m_attach[i];
		other.m_fbo = BGFX_INVALID_HANDLE; return *this;
	}

	bool FrameBuffer::valid() const { return bgfx::isValid(m_fbo); }

	void SwapBuffer::create(const uvec2& size, TextureFormat color_format)
	{
		m_one = { size, color_format, TEXTURE_CLAMP };// | TEXTURE_POINT);
		m_two = { size, color_format, TEXTURE_CLAMP };// | TEXTURE_POINT);
	}

	SwapBuffer::~SwapBuffer()
	{}

	void Cascade::create(const uvec2& size, TextureFormat color_format)
	{
		//const uint64_t flags = BGFX_TEXTURE_BLIT_DST | TEXTURE_CLAMP;
		const uint64_t flags = BGFX_TEXTURE_RT | TEXTURE_CLAMP;

		if(!bgfx::isTextureValid(1, false, 1, bgfx::TextureFormat::Enum(color_format), flags))
			return;

		m_texture = { size, true, color_format, flags };

		for(uint16_t i = 0; size.x > 1 && i < 9; ++i)
		{
			uvec2 level_size = uvec2(size.x >> i, size.y >> i);
			bgfx::Attachment attach = { bgfx::Access::Write, m_texture, i, 0, BGFX_RESOLVE_NONE };
			m_fbos[i] = make_unique<FrameBuffer>(level_size, m_texture, span<bgfx::Attachment>{ attach });
		}
	}

	Cascade::~Cascade()
	{
		if(bgfx::isValid(m_texture))
			bgfx::destroy(m_texture);
	}

	void SwapCascade::create(const uvec2& size, TextureFormat color_format)
	{
		m_one.create(size, color_format);
		m_two.create(size, color_format);
	}
	
	SwapCascade::~SwapCascade()
	{}

	RenderTarget::RenderTarget(const uvec2& size, void* window)
		: FrameBuffer(size)
		, m_backbuffer(size, window)
		//, m_msaa(MSAA::X16)
	{
		static const table<MSAA, uint64_t> msaa_flag = { BGFX_TEXTURE_RT, BGFX_TEXTURE_RT_MSAA_X2, BGFX_TEXTURE_RT_MSAA_X4, BGFX_TEXTURE_RT_MSAA_X8, BGFX_TEXTURE_RT_MSAA_X16 };
		
		TextureFormat color_format = TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::Enum(color_format), 0))
			color_format = TextureFormat::RGB10A2;
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::Enum(color_format), 0))
			color_format = TextureFormat::RGBA8;
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::Enum(color_format), msaa_flag[m_msaa]))
			m_msaa = MSAA::Disabled;

		//color_format = TextureFormat::RGBA8;

		const uint64_t flags = msaa_flag[m_msaa];

		m_depth = { size, false, TextureFormat::D24S8, flags | TEXTURE_DEPTH };

		m_diffuse = { size, false, color_format, flags };

		m_mrt = bgfx::getCaps()->limits.maxFBAttachments >= 4;
		
#ifdef TWO_GL_NO_MRT
		// disabling MRT on OpenGL until we figure out a fix for the visual bug
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;
		if(is_opengl)
			m_mrt = false;
#endif

		m_mrt = false;
		if(m_mrt)
		{
			m_specular = { size, false, color_format, flags };

			m_normal_rough = { size, false, TextureFormat::RGBA8, flags };

			//m_sss = { size, bgfx::TextureFormat::R8, render_target_flags };

			bgfx::TextureHandle textures[4] = { m_depth, m_diffuse, m_specular, m_normal_rough };
			m_fbo = bgfx::createFrameBuffer(4, textures, true);
		}
		else
		{
			bgfx::TextureHandle textures[2] = { m_depth, m_diffuse };
			m_fbo = bgfx::createFrameBuffer(2, textures, true);
		}

		m_ping_pong.create(size, color_format);
		m_post.create(size, color_format);

		m_cascade.create(size, color_format);

#ifdef TWO_GFX_DEFERRED
		m_deferred = true;
#else
		m_deferred = false;
#endif
		if(m_deferred)
			m_gbuffer.create(size, color_format, flags);
	}

	RenderTarget::~RenderTarget()
	{}

	void GBuffer::create(const uvec2& size, TextureFormat color_format, uint64_t flags)
	{
		m_depth    = { size, false, TextureFormat::D24S8, flags | TEXTURE_DEPTH };
		m_position = { size, false, color_format,		  flags };
		m_normal   = { size, false, color_format,		  flags };
		m_albedo   = { size, false, color_format,		  flags };
		m_surface  = { size, false, TextureFormat::RGBA8, flags };

		(FrameBuffer&)*this = { size, { &m_depth, &m_position, &m_normal, &m_albedo, &m_surface } };
	}
}


module two.gfx;

#define DEBUG_ITEMS 0

namespace two
{
	Scene::Scene(GfxSystem& gfx)
		: m_gfx(gfx)
		, m_immediate(oconstruct<ImmediateDraw>(gfx.fetch_material("immediate", "solid")))
		, m_pass_jobs(oconstruct<PassJobs>())
		, m_graph(*this)
	{
		m_pool = oconstruct<ObjectPool>();
		m_pool->create_pool<Flare>(1024);

		m_particle_system = oconstruct<ParticleSystem>(gfx, m_pool->pool<Flare>());
	}

	Scene::~Scene()
	{}

	void Scene::update()
	{
		static Clock clock;
		float timestep = float(clock.step());

		m_pool->pool<Mime>().iterate([=](Mime& animated)
		{
			animated.advance(timestep);
		});

		for(PassType pass = PassType(0); pass != PassType::Count; pass = PassType(size_t(pass) + 1))
		{
			m_pass_jobs->m_jobs[pass].clear();
		}
	}

	Gnode& Scene::begin()
	{
		this->update();
		m_immediate->begin();
		return m_graph.begin(true);
	}

	void Scene::debug_items(Render& render)
	{
		mat4 identity = bxidentity();
		bool debug = render.m_target != nullptr;
		if(debug)
			for(Item* item : render.m_shot.m_items)
			{
				Colour colour = { 1.f, 0.f, 1.f, 0.15f };
				Cube cube = Cube(item->m_aabb);
				m_immediate->shape(identity, { Symbol::wire(colour, true), &cube, OUTLINE });
				//m_immediate->draw(item->m_node->m_transform, { Symbol::wire(colour, true), &item->m_aabb, OUTLINE });
			}
	}

	void cull_items(Scene& scene, const Plane6& planes, vector<Item*>& items)
	{
		//items.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0)
				if((item.m_flags & ItemFlag::NoCull) != 0 || frustum_aabb_intersection(planes, item.m_aabb))
				{
					items.push_back(&item);
				}
		});
	}

	void gather_items(Scene& scene, const Camera& camera, vector<Item*>& items)
	{
		const Plane6 planes = frustum_planes(camera.m_proj, camera.m_view);

		const Plane near_plane = camera.near_plane();

		const vec4 lod_levels = camera.m_far * vec4(0.02f, 0.3f, 0.6f, 0.8f);

		//items.reserve(m_pool->pool<Item>().size());
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0)
			{
				const bool no_cull = (item.m_flags & ItemFlag::NoCull) != 0;
				if(!no_cull && !frustum_aabb_intersection(planes, item.m_aabb))
					return;

				const float depth = distance(near_plane, item.m_aabb.m_center);

				const vec4 comparison = vec4(greater(vec4(depth), lod_levels));
				const float index = dot(vec4(1.f), comparison);
				const uint8_t lod = uint8_t(min(index, 3.f));

				const bool has_lod = (item.m_flags & (ItemFlag::Lod0 << lod)) != 0;
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
		Plane6 planes = frustum_planes(camera.m_proj, camera.m_view);

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
		uint32_t index = 0;
		//lights.reserve(m_pool->pool<Light>().size());
		scene.m_pool->pool<Light>().iterate([&](Light& light)
		{
			if(light.m_visible)
			{
				light.m_index = index++;
				light.m_shot_index = lights.size();
				lights.push_back(&light);
			}
		});
	}

	void gather_render(Scene& scene, Render& render)
	{
		gather_items(scene, *render.m_camera, render.m_shot.m_items);
		gather_occluders(scene, *render.m_camera, render.m_shot.m_occluders);
		gather_lights(scene, render.m_shot.m_lights);

		render.m_frustum = optimized_frustum(*render.m_camera, render.m_shot.m_items);

		render.m_shot.m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}
}


module two.gfx;

#include <algorithm>

#include <cstdio>

#define SKELETON_TEXTURE_SIZE 256

namespace two
{
	Skeleton::Skeleton()
	{}

	Skeleton::Skeleton(cstring name, int num_bones)
		: m_name(name)
	{
		m_bones.reserve(num_bones);
	}

	uint32_t Skeleton::add_bone(cstring name, uint32_t parent)
	{
		const uint32_t index = uint32_t(m_bones.size());
		m_names.push_back(name);
		m_bones.push_back(Node3(mat4(), parent));
		return index;
	}

	uint32_t Skeleton::bone_index(cstring name) const
	{
		for(size_t i = 0; i < m_names.size(); i++)
			if(m_names[i] == name)
				return i;
		return UINT32_MAX;
	}

	Node3* Skeleton::find_bone(cstring name)
	{
		uint32_t index = this->bone_index(name);
		return index != UINT32_MAX ? &m_bones[index] : nullptr;
	}

	Skin::Skin() {}
	Skin::Skin(Skeleton& skeleton, int num_joints)
		: m_skeleton(&skeleton)
	{}

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
		Joint joint = { m_skeleton->bone_index(bone), inverse_bind, mat4() };
		m_joints.push_back(joint);
	}

	void Skin::update_joints()
	{
		uint height = uint(m_joints.size()) / SKELETON_TEXTURE_SIZE;
		if(m_joints.size() % SKELETON_TEXTURE_SIZE)
			height++;
		const uvec2 size = uvec2(SKELETON_TEXTURE_SIZE, height * 4);

		if(!bgfx::isValid(m_texture))
			m_texture = bgfx::createTexture2D(size.x, size.y, false, 1, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP);
			//m_texture = { size, false, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };
		
		m_memory = bgfx::alloc(size.x * size.y * 4 * sizeof(float));

		int index = 0;
		for(Joint& joint : m_joints)
		{
			joint.m_joint = m_skeleton->m_bones[joint.m_bone].m_transform * joint.m_inverse_bind;

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
			m_skins.push_back({ skin, m_skeleton });
	}

	Rig& Rig::operator=(const Rig& rig)
	{
		m_skeleton = rig.m_skeleton;
		m_skins.reserve(rig.m_skins.size());
		for(const Skin& skin : rig.m_skins)
			m_skins.push_back({ skin, m_skeleton });
		return *this;
	}

	void Rig::update_rig()
	{
		for(Skin& skin : m_skins)
			skin.update_joints();

		if(m_morphs.size() > 0)
		{
			m_weights.resize(m_morphs.size());

			for(uint32_t i = 0; i < m_morphs.size(); ++i)
			{
				m_weights[i] = { i, m_morphs[i] };
			}

			std::sort(m_weights.begin(), m_weights.end(), [](const MorphWeight& a, const MorphWeight& b) { return a.weight > b.weight; });
			// @todo fix that shit quicksort we implemented :D
			// quicksort(span<MorphWeight>(m_weights), [](const MorphWeight& a, const MorphWeight& b) { return a.weight < b.weight; });
		}
	}
}

#ifdef _DEBUG
namespace two
{
	mat4 fix_bone_pose(Node3& bone)
	{
		return bxrotation(angle_axis(-c_pi * 0.5f, X3)) * bxscale(vec3(0.009999999776482582f)) * bone.m_transform;
	}

	void debug_draw_skeleton(Gnode& parent, const vec3& position, const quat& rotation, Rig& rig)
	{
		for(Node3& bone : rig.m_skeleton.m_bones)
		{
			mat4 pose = bxrotation(rotation) * fix_bone_pose(bone);
			Gnode& node = gfx::node(parent, position + vec3(pose * vec4(vec3(0.f), 1.f)));
			gfx::shape(node, Sphere(0.02f), Symbol());
		}
	}
}
#endif


#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>
#include <bimg/encode.h>
#include <bx/readerwriter.h>
#include <bx/file.h>

module two.gfx;

#include <cstdio>
#include <cstring>

namespace two
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
			printf("[ERROR] Failed to open: %s.\n", file_path);
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

	void save_bgfx_texture(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth)
	{
		bimg::ImageContainer* source = bimg::imageAlloc(&gfx.allocator(), bimg::TextureFormat::Enum(texture_format), width, height, depth, 1, false, false);
		if(source == nullptr) return;

		for(uint8_t mip = 0; mip < source->m_numMips; ++mip)
		{
			uint32_t ready = bgfx::readTexture(texture, source->m_data, mip);
			while(bgfx::frame() != ready);
		}

		if(!bx::open(&gfx.file_writer(), file_path.c_str()))
		{
			printf("[ERROR] Unable to open output file '%s'", file_path.c_str());
			return;
		}

		bimg::ImageContainer* encoded = source;
		if(target_format != texture_format)
			encoded = bimg::imageEncode(&gfx.allocator(), bimg::TextureFormat::Enum(target_format), bimg::Quality::Default, *source);
		if(encoded == nullptr)
		{
			bimg::imageFree(source);
			return;
		}

		uint8_t stride = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(target_format)) / 8;

		if(target_format == bgfx::TextureFormat::RGBA16F)
			//bimg::imageWriteKtx(&writer, bimg::TextureFormat::RGBA16F, false, width, height, depth, source->m_numMips, 1, encoded->m_data, nullptr);
			bimg::imageWriteHdr(&gfx.file_writer(), width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA16F, false, nullptr);
		if(target_format == bgfx::TextureFormat::RGBA8)
			bimg::imageWritePng(&gfx.file_writer(), width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA8, false);
		if(target_format == bgfx::TextureFormat::BC3 || target_format == bgfx::TextureFormat::BC6H)
			bimg::imageWriteDds(&gfx.file_writer(), *encoded, encoded->m_data, encoded->m_size, nullptr);

		bx::close(&gfx.file_writer());

		bimg::imageFree(source);
		if(target_format != texture_format)
			bimg::imageFree(encoded);
	}

	bgfx::TextureHandle load_bgfx_image(GfxSystem& gfx, bimg::ImageContainer& image, const string& name, uint64_t flags, bgfx::TextureInfo* info, bool gen_mips)
	{
		// @todo implement per-type asset load options and remove this
		bool need_mips = image.m_format == bimg::TextureFormat::R8
			|| image.m_format == bimg::TextureFormat::RGB8
			|| image.m_format == bimg::TextureFormat::RGBA8;

		//need_mips = false;

		if(need_mips && gen_mips && image.m_numMips <= 1)
		{
			bimg::ImageContainer* rgba8 = bimg::imageConvert(&gfx.allocator(), bimg::TextureFormat::RGBA8, image);
			bimg::ImageContainer* mips = bimg::imageGenerateMips(&gfx.allocator(), *rgba8);
			if(mips != nullptr)
			{
				bimg::imageFree(rgba8);
				bimg::imageFree(&image);
				return load_bgfx_image(gfx, *mips, name, flags, info, false);
			}
			else
			{
				printf("[warning] could not generate mips for texture %s\n", name.c_str());
			}
		}

		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

		const bgfx::Memory* mem = bgfx::makeRef(image.m_data, image.m_size, release_bgfx_image, &image);
		uint64_t srgb = image.m_srgb ? BGFX_TEXTURE_SRGB : 0;

		printf("[info] gfx - loaded image %s srgb(%i) of size %s in memory\n", name.c_str(), int(image.m_srgb), readable_file_size(image.m_size).c_str());

		if(image.m_cubeMap)
		{
			handle = bgfx::createTextureCube(uint16_t(image.m_width), 1 < image.m_numMips,
											 image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format), flags | srgb, mem);
		}
		else if(1 < image.m_depth)
		{
			handle = bgfx::createTexture3D(uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
										   1 < image.m_numMips, bgfx::TextureFormat::Enum(image.m_format), flags | srgb, mem);
		}
		else
		{
			handle = bgfx::createTexture2D(uint16_t(image.m_width), uint16_t(image.m_height), 1 < image.m_numMips,
										   image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format), flags | srgb, mem);
		}
		
		if(info)
		{
			bgfx::calcTextureSize(*info, uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
								  image.m_cubeMap, 1 < image.m_numMips, image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format));
		}

		return handle;
	}

	bgfx::TextureHandle load_bgfx_texture(GfxSystem& gfx, const string& name, void* data, size_t size, uint64_t flags, bgfx::TextureInfo* info, bool gen_mips)
	{
		bimg::ImageContainer* image = bimg::imageParse(&gfx.allocator(), data, uint32_t(size));
		BX_FREE(&gfx.allocator(), data);

		if(!image)
			return BGFX_INVALID_HANDLE;

		return load_bgfx_image(gfx, *image, name, flags, info, gen_mips);
	}

	bgfx::TextureHandle load_bgfx_texture(GfxSystem& gfx, const string& file_path, uint64_t flags, bgfx::TextureInfo* info, bool generate_mips)
	{
		uint32_t size;
		void* data = load_mem(&gfx.file_reader(), &gfx.allocator(), file_path.c_str(), &size);
		if(!data)
			return BGFX_INVALID_HANDLE;
		else
			return load_bgfx_texture(gfx, file_path, data, size, flags, info, generate_mips);
	}

	bimg::ImageContainer* load_bgfx_image(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum dest_format)
	{
		uint32_t size = 0;
		void* data = load_mem(&gfx.file_reader(), &gfx.allocator(), file_path.c_str(), &size);
		return bimg::imageParse(&gfx.allocator(), data, size, bimg::TextureFormat::Enum(dest_format));
	}

	void save_texture(GfxSystem& gfx, Texture& tex, const string& path)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(tex.m_format);
		save_bgfx_texture(gfx, path, bformat, tex.m_tex, bformat, uint16_t(tex.m_size.x), uint16_t(tex.m_size.y));
	}

	void set_texture_info(Texture& texture, bgfx::TextureInfo& texture_info)
	{
		texture.m_size = uvec2(texture_info.width, texture_info.height);
		texture.m_format = TextureFormat(texture_info.format);
		texture.m_memsize = texture_info.storageSize;
		texture.m_bits_per_pixel = texture_info.bitsPerPixel;
		texture.m_is_cube = texture_info.cubeMap;
		texture.m_is_array = texture_info.numLayers > 1;
		texture.m_mips = texture_info.numMips > 0;
	}

	void load_texture(GfxSystem& gfx, Texture& texture, const string& path, bool srgb, bool mips)
	{
		if(file_extension(path) == "cube")
		{
			const string name = file_noext(path);
			const string format = "." + file_extension(name);
			const string base = file_noext(name);

			const string paths[] = {
				base + "/" + "px" + format, base + "/" + "nx" + format,
				base + "/" + "py" + format, base + "/" + "ny" + format,
				base + "/" + "pz" + format, base + "/" + "nz" + format
			};
			
			bimg::ImageContainer* sides[6] = {};
			for(size_t i = 0; i < 6; ++i)
			{
				uint32_t size;
				void* data = load_mem(&gfx.file_reader(), &gfx.allocator(), paths[i].c_str(), &size);
				sides[i] = bimg::imageParse(&gfx.allocator(), data, uint32_t(size));
				BX_FREE(&gfx.allocator(), data);
			}

			bimg::ImageContainer* cubemap = bimg::imageCubemapFrom6Sides(&gfx.allocator(), sides, nullptr);

			for(size_t i = 0; i < 6; ++i)
				bimg::imageFree(sides[i]);

			bgfx::TextureInfo texture_info;
			texture.m_location = path;
			texture.m_tex = load_bgfx_image(gfx, *cubemap, path.c_str(), !srgb ? BGFX_TEXTURE_NONE : BGFX_TEXTURE_SRGB, &texture_info, mips);
			set_texture_info(texture, texture_info);
		}
		else
		{
			bgfx::TextureInfo texture_info;
			texture.m_location = path;
			texture.m_tex = load_bgfx_texture(gfx, path, !srgb ? BGFX_TEXTURE_NONE : BGFX_TEXTURE_SRGB, &texture_info, mips);
			// if(!bgfx::isValid(texture.m_texture)) set placeholder "missing texture" texture instead
			set_texture_info(texture, texture_info);
		}
	}

	void load_texture_mem(GfxSystem& gfx, Texture& texture, span<uint8_t> data)
	{
		bgfx::TextureInfo texture_info;
		texture.m_tex = load_bgfx_texture(gfx, texture.m_name, (void*)data.m_pointer, data.m_count, 0U, &texture_info, true);
		// if(!bgfx::isValid(texture.m_texture)) set placeholder "missing texture" texture instead
		set_texture_info(texture, texture_info);
	}

	Texture::Texture(const string& name)
		: m_name(name)
	{}

	Texture::Texture(const uvec2& size, bool mips, TextureFormat format, uint64_t flags, bool cube)
		: m_size(size)
		, m_format(format)
		, m_is_cube(cube)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(format);
		m_tex = cube
			? bgfx::createTextureCube(uint16_t(size.x), mips, 1, bformat, flags)
			: bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), mips, 1, bformat, flags);
		m_is_depth = bformat >= bgfx::TextureFormat::D16 && bformat <= bgfx::TextureFormat::D0S8;
	}

	Texture::Texture(const uvec2& size, bool mips, int layers, TextureFormat format, uint64_t flags)
		: m_size(size)
		, m_format(format)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(format);
		m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), mips, layers, bformat, flags);
		m_is_depth = bformat >= bgfx::TextureFormat::D16 && bformat <= bgfx::TextureFormat::D0S8;
		m_is_array = true;
	}

	Texture::Texture(const uvec3& size, bool mips, TextureFormat format, uint64_t flags)
		: m_size(size.x, size.y)
		, m_depth(size.z)
		, m_format(format)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(format);
		m_tex = bgfx::createTexture3D(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), mips, bformat, flags);
		m_is_depth = bformat >= bgfx::TextureFormat::D16 && bformat <= bgfx::TextureFormat::D0S8;
	}

	Texture::~Texture()
	{
		if(bgfx::isValid(m_tex))
			bgfx::destroy(m_tex);
	}

	bool Texture::valid() const { return bgfx::isValid(m_tex); }

	void Texture::reload(GfxSystem& gfx, bool srgb, bool mips)
	{
		load_texture(gfx, *this, m_location, srgb, mips);
	}

	void Texture::load_float(const uvec2& size, const bgfx::Memory& memory, uint8_t num_components)
	{
		if(m_size == size)
		{
			bgfx::updateTexture2D(m_tex, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), &memory);
		}
		else
		{
			m_size = size;
			m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT, &memory);
		}
	}

	void Texture::load_rgba(const uvec2& size, const bgfx::Memory& memory)
	{
		if(m_size == size)
		{
			bgfx::updateTexture2D(m_tex, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), &memory);
		}
		else
		{
			m_size = size;
			m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8, TEXTURE_POINT, &memory);
		}
	}

	void Texture::load_rgba(const uvec2& size, span<uint32_t> data, bool ref)
	{
		const bgfx::Memory* memory = ref
			? bgfx::makeRef(data.data(), data.size())
			: bgfx::alloc(uint32_t(data.m_count * sizeof(uint32_t)));
		if(!ref)
			memcpy(memory->data, data.m_pointer, data.m_count * sizeof(uint32_t));
		this->load_rgba(size, *memory);
	}

	void Texture::load_float(const uvec2& size, span<float> data, bool ref)
	{
		const bgfx::Memory* memory = ref
			? bgfx::makeRef(data.data(), data.size())
			: bgfx::alloc(uint32_t(data.m_count * sizeof(float)));
		if(!ref)
			memcpy(memory->data, data.m_pointer, data.m_count * sizeof(float));
		this->load_float(size, *memory);
	}
}

#if 0

module two.gfx;

namespace two
{
	UniformBlock::UniformBlock(Type& type, const string& name)
		: m_type(type)
		, m_name(name)
	{}

	void UniformBlock::pack_member(size_t size, Member& member)
	{
		if(m_uniforms.empty() || m_uniforms.back().m_space < size)
			m_uniforms.push_back({ "u_" + m_name + "_p" + to_string(m_num_packed++), member.m_offset, bgfx::UniformType::Vec4 });

		m_uniforms.back().m_fields.push_back({ member.m_name, member.m_offset, size });
		m_uniforms.back().m_space -= size;
	}

	void UniformBlock::create_member(GfxSystem& gfx, const string& name, Member& member)
	{
		if(member.m_type->is<float>())
			pack_member(1, member);
		else if(member.m_type->is<vec2>())
			pack_member(2, member);
		else if(member.m_type->is<vec3>())
			pack_member(3, member);
		else if(member.m_type->is<vec4>() || member.m_type->is<Colour>())
			m_uniforms.push_back({ "u_" + name, member.m_offset, bgfx::UniformType::Vec4 });
		else if(member.m_type->is<Texture>())
			m_samplers.push_back({ "s_" + name, member.m_offset, uint8_t(m_samplers.size()), &gfx.default_texture(TextureHint::White), {} });
		else if(member.m_type->is<mat4>())
			m_uniforms.push_back({ "u_" + name, member.m_offset, bgfx::UniformType::Mat4 });

		else if(member.cls().m_members.size() > 0)
			for(Member& sub_member : member.cls().m_members)
				create_member(gfx, name, sub_member);
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

	void UniformBlock::create(GfxSystem& gfx)
	{
		for(Member& member : cls(m_type).m_members)
			create_member(gfx, member.m_name, member);

		for(Uniform& uniform : m_uniforms)
			uniform.create();

		for(Sampler& sampler : m_samplers)
			sampler.create();
	}
}
#endif

module two.gfx;

//#define NO_OCCLUSION_CULLING

namespace two
{
	GridECS s_viewer_ecs;
	GridECS* g_viewer_ecs = &s_viewer_ecs;

	static uint16_t viewportIndex = 1;

	Viewport::Viewport(Camera& camera, Scene& scene, const vec4& rect, bool scissor)
		: m_camera(&camera)
		, m_scene(&scene)
		, m_index(viewportIndex++)
		, m_rect(rect)
		, m_scissor(scissor)
		, m_culler(construct<Culler>(*this))
	{
		(Entt&)(*this) = { &s_viewer_ecs, s_viewer_ecs.create() };
	}

	Viewport::~Viewport()
	{}

	void Viewport::pass(const Pass& pass)
	{
		const FrameBuffer& fbo = *pass.m_fbo;
		const ushort4 rect = ushort4(m_rect * vec2(fbo.m_size));

		bgfx::setViewRect(pass.m_index, rect.x, rect.y, rect.width, rect.height);
		bgfx::setViewTransform(pass.m_index, value_ptr(m_camera->m_view), value_ptr(m_camera->m_proj));
		bgfx::setViewFrameBuffer(pass.m_index, *pass.m_fbo);
		bgfx::setViewClear(pass.m_index, BGFX_CLEAR_NONE);

		if(m_scissor)
			bgfx::setViewScissor(pass.m_index, rect.x, rect.y, rect.width, rect.height);
	}

	void Viewport::cull(Render& render)
	{
#ifndef NO_OCCLUSION_CULLING
		m_culler->render(render);
#else
		UNUSED(render);
#endif
	}

	void Viewport::render(Render& render)
	{
		if(m_rect.height != 0.f)
		{
			const vec2 size = m_rect.size * vec2(render.m_fbo->m_size);
			m_camera->m_aspect = size.x / size.y;
		}

		m_camera->update();

		if(m_clusters)
		{
			const uvec4 rect = uvec4(m_rect * vec2(render.m_fbo->m_size));
			m_clusters->m_dirty |= uint8_t(Froxelizer::Dirty::Viewport) | uint8_t(Froxelizer::Dirty::Projection);
			m_clusters->update(rect, m_camera->m_proj, m_camera->m_near, m_camera->m_far);
			m_clusters->clusterize_lights(*m_camera, render.m_shot.m_lights);
			m_clusters->upload();
		}

		for(RenderTask& task : m_tasks)
			task(render);
	}

	void Viewport::set_clustered(GfxSystem& gfx)
	{
		if(m_rect.width != 0.f && m_rect.height != 0.f && !m_clusters)
		{
			m_clustered = true;
			m_clusters = make_unique<Froxelizer>(gfx);
			m_clusters->setup();
		}
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
		float xNDC = (pos.x / float(m_rect.width)) * 2.0f - 1.0f;
		float yNDC = ((float(m_rect.height) - pos.y) / float(m_rect.height)) * 2.0f - 1.0f;

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

module two.gfx;

namespace two
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

	BlockSky::BlockSky(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_skybox_program(gfx.programs().create("skybox"))
	{
		m_skybox_program.register_block(m_filter);
	}

	void BlockSky::init_block()
	{
		u_skybox.createUniforms();
	}

	void BlockSky::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockSky::submit_pass(Render& render)
	{
		if(!render.m_env)
			return;

		BackgroundMode mode = render.m_env->m_background.m_mode;
		if(mode == BackgroundMode::Custom)
			return render.m_env->m_background.m_custom_function(m_gfx, render);
		else if(mode == BackgroundMode::Radiance || mode == BackgroundMode::Panorama)
		{
			if(mode == BackgroundMode::Radiance && render.m_env->m_radiance.m_filtered == nullptr)
				return;

			Pass pass = render.next_pass("sky", PassType::Background);
			bgfx::Encoder& encoder = *pass.m_encoder;

			Texture& texture = mode == BackgroundMode::Radiance
				? *render.m_env->m_radiance.m_filtered
				: *render.m_env->m_background.m_texture;

			unsigned int level = mode == BackgroundMode::Radiance ? 3 : 0;

			ProgramVersion program = { m_skybox_program };
			program.set_option(0, VFLIP, render.m_vflip && bgfx::getCaps()->originBottomLeft);

			m_filter.source0p(texture, program, level);

			mat4 skybox_matrix = bxinverse(render.m_camera->m_view);
			encoder.setUniform(u_skybox.u_skybox_matrix, &skybox_matrix);

			const RenderQuad quad = RenderQuad(pass.m_rect, false);
			m_filter.submit(pass, *render.m_fbo, program, quad, BGFX_STATE_DEPTH_TEST_LEQUAL);
		}
	}
}

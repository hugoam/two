//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
#include <cstdlib>
module mud.math;
#else
#include <infra/Array.h>
#include <math/Types.h>
#include <math/VecOps.h>
#include <math/Math.h>
#include <math/Grid.h>
#include <math/Axes.h>
#endif

namespace mud
{
#ifndef M_PI
	const float c_pi = 3.14159265358979323846f;
#else
	const float c_pi = M_PI;
#endif

	void register_math_conversions()
	{
#if 0
		dispatch_branch<float, vec3, copy_convert<float, vec3>>(TypeConverter::me());
		TypeConverter::me().default_converter<vec3, ivec3>();
		TypeConverter::me().default_converter<vec3, uvec3>();
#endif
	}

	const vec3 X3 = { 1.f, 0.f, 0.f };
	const vec3 Y3 = { 0.f, 1.f, 0.f };
	const vec3 Z3 = { 0.f, 0.f, 1.f };

	const vec3 Zero3 = { 0.f, 0.f, 0.f };
	const vec3 Unit3 = { 1.f, 1.f, 1.f };

	const Side c_sides[6] = { Side::Right, Side::Left, Side::Up, Side::Down, Side::Back, Side::Front };

	const vec3 c_axes[3]			 = {  X3,  Y3,  Z3 };
	const vec3 c_tangents[6]		 = {  Y3,  Z3,  Y3 };
	const vec3 c_binormals[6]		 = {  Z3,  X3,  X3 };

	const vec3 c_dirs[6]			 = {  X3, -X3,  Y3, -Y3,  Z3, -Z3 };
	const vec3 c_dirs_tangents[6]	 = {  Y3, -Z3, -Z3,  X3,  Y3,  X3 };
	const vec3 c_dirs_normals[6]	 = { -Z3,  Y3,  X3, -Z3,  X3,  Y3 };

#ifdef MUD_NO_GLM
	const quat ZeroQuat = { 0.f, 0.f, 0.f, 1.f };
#else
	const quat ZeroQuat = { 1.f, 0.f, 0.f, 0.f };
#endif

	const vec2 Zero2 = { 0.f, 0.f };
	const vec2 Unit2 = { 1.f, 1.f };

	const vec4 Zero4 = { 0.f, 0.f, 0.f, 0.f };
	const vec4 Rect4 = { 0.f, 0.f, 1.f, 1.f };

	quat average_quat(quat& cumulative, const quat& rotation, const quat& first, uint32_t count)
	{
		if(dot(rotation, first) < 0.f)
			return average_quat(cumulative, inverse(rotation), first, count);

		float factor = 1.f / float(count);
		cumulative += rotation;
		return normalize(cumulative * factor);
	}

	Transform average_transforms(array<Transform*> transforms)
	{
		Transform average;
		average.m_scale = Zero3;

		quat cumulative = { 0.f, 0.f, 0.f, 0.f };

		uint32_t count = 0;
		for(Transform* transform : transforms)
		{
			average.m_position += transform->m_position;
			average.m_scale += transform->m_scale;
			average.m_rotation = average_quat(cumulative, transform->m_rotation, transforms[0]->m_rotation, ++count);
		}
		average.m_position = average.m_position / float(transforms.size());
		average.m_scale = average.m_scale / float(transforms.size());

		return average;
	}

	float nsinf(float a) { return (sinf(a) + 1.f) / 2.f; } // @kludge can't be inline because we identify reflected functions through their pointer 
	float ncosf(float a) { return (cosf(a) + 1.f) / 2.f; }

	double nsin(double a) { return (sin(a) + 1.0) / 2.0; }
	double ncos(double a) { return (cos(a) + 1.0) / 2.0; }

	quat look_dir(const vec3& direction, const vec3& forward)
	{
		float d = dot(forward, direction);

		if(abs(d - (-1.0f)) < 0.000001f)
			return axis_angle(Y3, c_pi);
		if(abs(d - (1.0f)) < 0.000001f)
			return ZeroQuat;

		vec3 axis = normalize(cross(-Z3, direction));
		return axis_angle(axis, acos(d));
	}

	quat look_at(const vec3& source, const vec3& dest, const vec3& forward)
	{
		vec3 direction = normalize(dest - source);
		return look_dir(direction, forward);
	}

	uint32_t pack4(const vec4& colour)
	{
		vec4 clamped = clamp(colour * 255.f, 0.f, 255.f);
		uint32_t rgba = 0;
		rgba |= uint32_t(clamped[0]) << 24;
		rgba |= uint32_t(clamped[1]) << 16;
		rgba |= uint32_t(clamped[2]) << 8;
		rgba |= uint32_t(clamped[3]);
		return rgba;
	}

	uint32_t pack3(const vec3& colour)
	{
		vec3 clamped = clamp(colour * 255.f, 0.f, 255.f);
		uint32_t rgb = 0;
		rgb |= uint32_t(clamped[0]) << 16;
		rgb |= uint32_t(clamped[1]) << 8;
		rgb |= uint32_t(clamped[2]) << 0;
		return rgb;
	}

	vec3 unpack3(uint32_t rgb)
	{
		float x = ((rgb >> 16) & 0xFF) / 255.f;
		float y = ((rgb >> 8) & 0xFF) / 255.f;
		float z = ((rgb >> 0) & 0xFF) / 255.f;
		return { x, y, z };
	}

	vec4 unpack4(uint32_t rgba)
	{
		float x = (rgba >> 24) / 255.f;
		float y = ((rgba >> 16) & 0xFF) / 255.f;
		float z = ((rgba >> 8) & 0xFF) / 255.f;
		float w = ((rgba >> 0) & 0xFF) / 255.f;
		return { x, y, z, w };
	}

	Axis nearest_axis(const vec3& direction)
	{
		Axis axis = Axis::X;

		float closest_dot = 0.f;
		for(Axis a : { Axis::X, Axis::Y, Axis::Z })
		{
			float product = std::abs(dot(direction, to_vec3(a)));
			if(a == Axis::X || product > closest_dot)
			{
				axis = a;
				closest_dot = product;
			}
		}

		return axis;
	}

	float float_shortest_angle(float angle1, float angle2)
	{
		return min((2.f * c_pi) - std::abs(angle1 - angle2), std::abs(angle1 - angle2));
	}

	float trigo_angle(const vec3& vec1, const vec3& vec2)
	{
		float angle = shortest_angle(vec1, vec2);
		
		if(angle < 0)
			angle += 2 * c_pi;

		return angle;
	}

#ifdef MUD_NO_GLM
	float shortest_angle(const vec3& vec1, const vec3& vec2)
	{
		return oriented_angle(vec1, vec2, Y3);
	}
#else
	float shortest_angle(const vec3& vec1, const vec3& vec2)
	{
		float a = angle(vec1, vec2);

		if(a == 0.f)
			return a;

		vec3 clockwise = rotate(vec1, a, Y3);
		flatten(clockwise);

		if(angle(vec2, clockwise) > 0.001f)
			a = -a;

		return a;
	}
#endif

	void orthonormalize(const mat4& transform, vec3& x, vec3& y, vec3& z)
	{
		// Gram-Schmidt Process

		x = { transform[0].x, transform[1].x, transform[2].x };
		y = { transform[0].y, transform[1].y, transform[2].y };
		z = { transform[0].z, transform[1].z, transform[2].z };

		x = normalize(x);
		y = (y - x * (dot(x, y)));
		y = normalize(y);
		z = (z - x * (dot(x, z)) - y * (dot(y, z)));
		z = normalize(z);
	}

	mat4 orthonormalize(const mat4& transform)
	{
		vec3 x, y, z;
		orthonormalize(transform, x, y, z);

		mat4 result = transform;
		result[0].x = x[0]; result[1].x = x[1]; result[1].x = x[1];
		result[0].y = y[0]; result[1].y = y[1]; result[1].y = y[1];
		result[0].z = z[0]; result[1].z = z[1]; result[1].z = z[1];

		return result;
	}

	mat4 bias_mat()
	{
		return {
			0.5f, 0.f,  0.f,  0.f,
			0.f,  0.5f, 0.f,  0.f,
			0.f,  0.f,  0.5f, 0.f,
			0.5f, 0.5f, 0.5f, 1.f
		};
	}

	mat4 bias_mat_bgfx(bool origin_bottom_left, bool homogeneous_depth)
	{
		const float sy = origin_bottom_left ? 0.5f : -0.5f;
		const float sz = homogeneous_depth ? 0.5f : 1.0f;
		const float tz = homogeneous_depth ? 0.5f : 0.0f;
		return {
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, sy,   0.0f, 0.0f,
			0.0f, 0.0f, sz,   0.0f,
			0.5f, 0.5f, tz,   1.0f,
		};
	}

	mat4 rect_mat(vec4 rect)
	{
		return
		{
			rect_w(rect), 0.f, 0.f, 0.f,
			0.f, rect_h(rect), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			rect.x, rect.y, 0.f, 1.f
		};
	}

	mat4 abs(const mat4& mat)
	{
		mat4 result;
		for(mat4::length_type i = 0; i < 4; ++i)
			for(mat4::length_type j = 0; j < 4; ++j)
				result[i][j] = abs(mat[i][j]);
		return result;
	}

	void grid(const uvec3& size, vector<uvec3>& output_coords)
	{
		for(uint z = 0; z < size.z; ++z)
			for(uint y = 0; y < size.y; ++y)
				for(uint x = 0; x < size.x; ++x)
					output_coords.push_back({ x, y, z });
	}

	vec3 grid_center(const uvec3& coord, float cell_size)
	{
		return vec3(coord) * cell_size + cell_size * 0.5f;
	}

	vec3 grid_center(const uvec3& coord, const vec3& cell_size)
	{
		return vec3(coord) * cell_size + cell_size * 0.5f;
	}

	void index_list(uint32_t size, vector<uint32_t>& output_indices)
	{
		for(uint32_t i = 0; i < size; ++i)
			output_indices.push_back(i);
	}
}

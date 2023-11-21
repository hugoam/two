

#pragma once

#include <gfx-pbr/Forward.h>
#include <gfx-pbr/VoxelGI.h>

namespace two
{
	export_ template <>
	struct GpuState<GIProbe>
	{
		void init(uint16_t array_size = 1U)
		{
			u_transform   = bgfx::createUniform("u_gi_probe_transform",    bgfx::UniformType::Mat4, array_size);
			u_bounds      = bgfx::createUniform("u_gi_probe_bounds4",      bgfx::UniformType::Vec4, array_size);
			u_p0      = bgfx::createUniform("u_gi_probe_p0",       bgfx::UniformType::Vec4, array_size);
			u_inv_extents = bgfx::createUniform("u_gi_probe_inv_extents4", bgfx::UniformType::Vec4, array_size);
			u_cell_size   = bgfx::createUniform("u_gi_probe_cell_size4",   bgfx::UniformType::Vec4, array_size);
		}

		void upload(bgfx::Encoder& encoder, const GIProbe& gi_probe, const mat4& view) const
		{
			float diffuse = gi_probe.m_dynamic_range * gi_probe.m_diffuse;
			float specular = gi_probe.m_dynamic_range * gi_probe.m_specular;

			mat4 transform = gi_probe.m_transform * inverse(view);
			vec4 params = { diffuse, specular, gi_probe.m_bias, gi_probe.m_normal_bias };
			vec4 bounds = { gi_probe.m_extents * 2.f, 0.f };
			vec4 inv_extents = { vec3(1.f) / gi_probe.m_extents, 1.f };
			vec4 cell_size = { gi_probe.m_extents * 2.f / float(gi_probe.m_subdiv), 1.f };

			encoder.setUniform(u_transform, &transform);
			encoder.setUniform(u_bounds, &bounds);
			encoder.setUniform(u_p0, &params);
			encoder.setUniform(u_inv_extents, &inv_extents);
			encoder.setUniform(u_cell_size, &cell_size);
		}

		bgfx::UniformHandle u_transform;
		bgfx::UniformHandle u_bounds;
		bgfx::UniformHandle u_p0;
		bgfx::UniformHandle u_inv_extents;
		bgfx::UniformHandle u_cell_size;

		static GpuState me;
	};

	export_ template <>
	struct GpuState<GpuVoxelGI>
	{
		void init()
		{
			u_world  = bgfx::createUniform("u_voxelgi_world",  bgfx::UniformType::Mat4);
			u_normal = bgfx::createUniform("u_voxelgi_normal", bgfx::UniformType::Mat3);

			u_p0 = bgfx::createUniform("u_voxelgi_p0", bgfx::UniformType::Vec4);
			u_p1 = bgfx::createUniform("u_voxelgi_p1", bgfx::UniformType::Vec4);
		}

		void upload(bgfx::Encoder& encoder, GIProbe& gi_probe) const
		{
			vec4 voxelgi_extents = { gi_probe.m_extents, 0.f };
			vec4 voxelgi_subdiv = { vec3(float(gi_probe.m_subdiv)), 0.f };

			mat4 voxelgi_world = gi_probe.m_transform;
			//mat3 voxelgi_normal = {};

			encoder.setUniform(u_p0, &voxelgi_extents);
			encoder.setUniform(u_p1, &voxelgi_subdiv);

			encoder.setUniform(u_world, &voxelgi_world);
			//encoder.setUniform(u_normal, &voxelgi_normal);
		}

		bgfx::UniformHandle u_world;
		bgfx::UniformHandle u_normal;
		bgfx::UniformHandle u_p0;
		bgfx::UniformHandle u_p1;

		static GpuState me;

	};
}

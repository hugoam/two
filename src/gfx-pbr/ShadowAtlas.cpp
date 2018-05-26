//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx-pbr/ShadowAtlas.h>

#include <geom/Intersect.h>

#include <gfx/Light.h>
#include <gfx/Camera.h>
#include <gfx/Frustum.h>
#include <gfx/Renderer.h>

namespace mud
{
	ShadowCubemap::ShadowCubemap(uint16_t size)
		: m_size(size)
	{
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT))
			return;

		m_cubemap = bgfx::createTextureCube(m_size, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT);

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachment = { m_cubemap, 0, uint16_t(i) };
			m_fbos[i] = bgfx::createFrameBuffer(1, &attachment, true);
		}
	}

	ShadowAtlas::ShadowAtlas(uint16_t size, std::vector<uint16_t> slices_subdiv)
		: m_size(size)
	{
		m_depth = bgfx::createTexture2D(m_size, m_size * uint16_t(slices_subdiv.size()), false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP);
		m_fbo = bgfx::createFrameBuffer(1, &m_depth);

		uint16_t index = 0;
		for(uint16_t subdiv : slices_subdiv)
		{
			m_slices.emplace_back(m_size, subdiv, uvec4{ 0, index * m_size, m_size, m_size });
		}

		uint16_t max_cubemap_size = 512;
		uint16_t cubemap_size = max_cubemap_size;
		while(cubemap_size >= 32)
		{
			m_cubemaps.emplace_back(cubemap_size);
			cubemap_size >>= 1;
		}
	}

	ShadowCubemap& ShadowAtlas::light_cubemap(Light& light, uint16_t shadow_size)
	{
		UNUSED(light);
		for(int i = m_cubemaps.size() - 1; i >= 0; i--)
			if(m_cubemaps[i].m_size > shadow_size * 2)
			{
				return m_cubemaps[i];
			}

		return m_cubemaps.back();
	}

	uvec4 ShadowAtlas::light_rect(Light& light)
	{
		UNUSED(light);
		Index index = {};// = m_light_indices[light.m_light_index];
		Slice& slice = m_slices[index.m_slice];
		Slice::Slot& slot = slice.m_slots[index.m_slot];
		return slot.m_rect;
	}

	ShadowAtlas::Slice::Slice(uint32_t size, uint16_t subdiv, uvec4 rect)
		: m_size(size)
		, m_subdiv(subdiv)
		, m_rect(rect)
	{
		uint32_t subdiv_size = size / subdiv;

		for(uint16_t y = 0; y < subdiv; ++y)
			for(uint16_t x = 0; x < subdiv; ++x)
			{
				uvec4 slot_rect = { rect.x + x * subdiv_size, rect.y + y * subdiv_size,
									subdiv_size, subdiv_size };

				m_slots.push_back({ nullptr, slot_rect });
			}
	}

	void ShadowAtlas::Slice::remove_light(Light& light)
	{
		UNUSED(light);
	}

	void ShadowAtlas::Slice::add_light(Light& light)
	{
		UNUSED(light);
	}

	void ShadowAtlas::remove_light(Light& light)
	{
		UNUSED(light);
		Index index = {}; // = m_light_indices[light.m_light_index];
		Slice& slice = m_slices[index.m_slice];
		slice.m_slots[index.m_slot].m_light = nullptr;
	}

	bool ShadowAtlas::update_light(Light& light, uint64_t render, float coverage, uint64_t light_version)
	{
		UNUSED(render); UNUSED(light_version);
		uint16_t target_size = min<uint16_t>(m_size / m_slices[0].m_subdiv, uint16_t(pow2_round_up(uint(m_size * coverage))));

		// @todo check if we need to allocate a new slot

		for(Slice& slice : m_slices)
			if(slice.m_size > target_size)
			{
				if(!slice.m_free_slots.empty())
					slice.add_light(light);
			}

		return true;
	}

	uvec4 ShadowAtlas::render_update(Render& render, Light& light)
	{
		float coverage;

		Plane camera_near_plane = render.m_camera.near_plane();

		vec3 points[2];

		if(light.m_type == LightType::Point)
		{
			points[0] = light.m_node.m_position;
			points[1] = light.m_node.m_position + light.m_node.axis(X3) * light.m_range;
		}
		else if(light.m_type == LightType::Spot)
		{
			float w = light.m_range * std::sin(light.m_spot_angle);
			float d = light.m_range * std::cos(light.m_spot_angle);

			vec3 base = light.m_node.m_position + light.m_node.direction() * d;

			points[0] = base;
			points[1] = base + light.m_node.axis(X3) * w;
		}

		if(!render.m_camera.m_orthogonal)
		{
			for(int j = 0; j < 2; j++)
			{
				if(plane_distance_to(camera_near_plane, points[j]) < 0.f)
					points[j].z = -render.m_camera.m_near; //small hack to keep size constant when hitting the screen

				points[j] = plane_segment_intersection(camera_near_plane, Segment{ light.m_node.m_position, points[j] });
			}
		}

		vec2 size = frustum_viewport_size(render.m_camera.m_projection);

		float screen_diameter = distance(points[0], points[1]) * 2.f;
		coverage = screen_diameter / (size.x + size.y);

		//if(light.m_shadow_dirty) // updated when lights and objects bounds start or stop intersecting, or move
		//{
		//	light.m_last_version++;
		//	light.m_shadow_dirty = false;
		//}

		bool redraw = this->update_light(light, light.m_last_render, coverage, light.m_last_update);
		UNUSED(redraw);
		return light_rect(light);
	}
}

//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <geom/Geom.hpp>
#include <geom/Intersect.h>
#include <gfx/Light.h>
#include <gfx/Camera.h>
#include <gfx/Frustum.h>
#include <gfx/Renderer.h>
#include <gfx-pbr/ShadowAtlas.h>
#include <gfx-pbr/Shadow.h>
#endif

#include <cstdio>

namespace mud
{
	ShadowAtlas::ShadowAtlas(uint16_t size, vector<uint16_t> subdivs)
		: m_side(size)
		, m_size(size * subdivs.size(), size)
	{
		m_depth = { m_size, false, TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP };
		m_color = { m_size, false, TextureFormat::RGBA8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP };
		m_fbo = { m_size, { &m_depth, &m_color } };

		//m_depth = { m_rect_size, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP };
		//m_fbo = { m_rect_size, bgfx::createFrameBuffer(1, &m_depth) };

		const float fraction = 1.f / float(subdivs.size());
		uint8_t index = 0;
		for(uint16_t subdiv : subdivs)
		{
			m_slices.push_back({ index, m_side, subdiv, vec4(index * fraction, 0.f, fraction, 1.f) });
			index++;
		}
	}

	ShadowAtlas::Slot& ShadowAtlas::light_slot(Light& light)
	{
		union { Index index; uint32_t i; } cast;
		cast.i = light.m_shadow_index;
		Slice& slice = m_slices[cast.index.slice];
		return slice.m_slots[cast.index.slot];
	}

	ShadowAtlas::Slice& ShadowAtlas::light_slice(Light& light)
	{
		union { Index index; uint32_t i; } cast;
		cast.i = light.m_shadow_index;
		return m_slices[cast.index.slice];
	}

	ShadowAtlas::Slice::Slice(uint8_t index, uint16_t size, uint16_t subdiv, const vec4& rect)
		: m_index(index)
		//, m_size(size)
		, m_subdiv(subdiv)
		, m_rect(rect)
		, m_slot_size(size / subdiv)
	{
		const vec2 slot_size = vec2(rect.width, rect.height) / float(subdiv);

		uint16_t i = 0;
		for(uint16_t y = 0; y < subdiv; ++y)
			for(uint16_t x = 0; x < subdiv; ++x)
			{
				vec4 slot_rect = { rect.x + x * slot_size.x, rect.y + y * slot_size.y,
								   slot_size.x, slot_size.y };

				m_slots.push_back({ i++, nullptr, slot_rect });
			}

		// @todo change to highwater + free list under waterline
		for(Slot& slot : m_slots)
		{
			m_free_slots.push_back(&slot);
		}

		for(uint16_t y = 0; y < subdiv; ++y)
			for(uint16_t x = 0; x < subdiv; ++x)
			{
				bool at_block = x % 4 == 0 && y % 2 == 0;
				bool has_space = subdiv - x >= 4 && subdiv - y >= 2;
				if(at_block && has_space)
					m_free_blocks.push_back(&m_slots[x + y * subdiv]);
			}
	}

	void ShadowAtlas::remove_light(Light& light, bool block)
	{
		Slice& slice = this->light_slice(light);
		Slot& slot = this->light_slot(light);
		slot.m_light = nullptr;
		if(block)
			slice.m_free_blocks.push_back(&slot);
		else
			slice.m_free_slots.push_back(&slot);
	}

	bool ShadowAtlas::update_light(Light& light, uint64_t render, float coverage, uint64_t light_version)
	{
		UNUSED(render); UNUSED(light_version);
		uint16_t biggest = m_slices[0].m_slot_size;
		uint16_t target_size = min(biggest, uint16_t(pow2_round_up(uint(m_side * coverage))));

		if(light.m_shadow_index != UINT32_MAX)
		{
			Slice& slice = this->light_slice(light);
			if(slice.m_slot_size > target_size) return false;
			this->remove_light(light, true);
		}

		//printf("looking for a shadow atlas slot of size %i\n", int(target_size));

		for(Slice& slice : m_slices)
		{
			//if(slice.m_slot_size <= target_size)
			//	continue;

			if(light.m_type == LightType::Point && !slice.m_free_blocks.empty())
			{
				Slot* slot = pop(slice.m_free_blocks);
				// @todo remove from free_slots list
				slot->m_light = &light;
				union { Index index; uint32_t i; } cast;
				cast.index = { slice.m_index, slot->m_index };
				light.m_shadow_index = cast.i;
				return true;
			}
		}

		return false;
	}

	vec4 ShadowAtlas::render_update(Render& render, Light& light)
	{
		const Plane camera_near_plane = render.m_camera->near_plane();

		vec3 points[2];

		const Node3& node = *light.m_node;
		if(light.m_type == LightType::Point)
		{
			points[0] = node.position();
			points[1] = node.position() + node.axis(X3) * light.m_range;
		}
		else if(light.m_type == LightType::Spot)
		{
			const float w = light.m_range * sin(light.m_spot_angle);
			const float d = light.m_range * cos(light.m_spot_angle);

			const vec3 base = light.m_node->position() + node.direction() * d;

			points[0] = base;
			points[1] = base + node.axis(X3) * w;
		}

		if(!render.m_camera->m_orthographic)
		{
			for(int j = 0; j < 2; j++)
			{
				if(distance(camera_near_plane, points[j]) < 0.f)
					points[j].z = -render.m_camera->m_near; //small hack to keep size constant when hitting the screen

				points[j] = plane_segment_intersection(camera_near_plane, { node.position(), points[j] });
			}
		}

		const vec2 size = frustum_viewport_size(render.m_camera->m_projection);

		const float screen_diameter = distance(points[0], points[1]) * 2.f;
		const float coverage = screen_diameter / (size.x + size.y);

		//if(light.m_shadow_dirty) // updated when lights and objects bounds start or stop intersecting, or move
		//{
		//	light.m_last_version++;
		//	light.m_shadow_dirty = false;
		//}

		const bool redraw = this->update_light(light, light.m_last_render, coverage, light.m_last_update);
		UNUSED(redraw);
		return this->light_slot(light).m_rect;
	}
}

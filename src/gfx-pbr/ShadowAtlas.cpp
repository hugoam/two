//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx.pbr;

#include <cstdio>

namespace two
{
	ShadowAtlas::ShadowAtlas(uint16_t size, uint8_t num_slices)
		: m_side(size)
		, m_size(size * num_slices, size)
	{
#if SHADOW_SAMPLER || SHADOW_DEPTH
		// WebGPU does not support sampling D24S8 for now
		m_depth = { m_size, false, TextureFormat::D32F, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_DEPTH };
#else
		m_depth = { m_size, false, TextureFormat::D24S8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_DEPTH };
#endif
		m_color = { m_size, false, TextureFormat::RGBA8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_POINT };
		m_fbo = { m_size, { &m_depth, &m_color } };

		m_color.m_is_depth_packed = true;

		const float fraction = 1.f / float(num_slices);
		for(uint8_t i = 0; i < num_slices; ++i)
		{
			m_slices.push_back({ i, uvec2(uint(m_side)), vec4(float(i) * fraction, 0.f, fraction, 1.f) });
		}
	}

	ShadowAtlas::Slot& ShadowAtlas::light_slot(Light& light)
	{
		Slice& slice = m_slices[light.m_shadow_index.slice];
		return slice.m_slots[light.m_shadow_index.slot];
	}

	ShadowAtlas::Slice& ShadowAtlas::light_slice(Light& light)
	{
		return m_slices[light.m_shadow_index.slice];
	}

	ShadowAtlas::Slice::Slice(uint8_t index, const uvec2& size, const vec4& rect)
		: m_index(index)
		, m_size(size)
		, m_rect(rect)
	{}

	void ShadowAtlas::begin_frame(const RenderFrame& frame)
	{
		for(Slice& slice : m_slices)
			for(uint32_t i = 0; i < slice.m_slots.size(); ++i)
			{
				Slot& slot = slice.m_slots[i];
				if(slot.m_light && slot.m_frame < frame.m_frame-1)
					this->yield(slice, i);
			}
	}

	void ShadowAtlas::subdiv(Slice& slice, uint16_t subdiv)
	{
		slice.m_subdiv = subdiv;
		slice.m_slot_size = m_size / uvec2(uint(subdiv));

		const vec2 slot_size = vec2(slice.m_rect.size) / float(subdiv);
		const vec2 coord = slice.m_rect.pos;

		slice.m_slots.clear();
		slice.m_free_slots.clear();
		slice.m_free_blocks.clear();

		auto at = [&](uint x, uint y) -> uint32_t { return x + y*subdiv; };

		uint16_t slot = 0;
		for(uint16_t y = 0; y < subdiv; ++y)
			for(uint16_t x = 0; x < subdiv; ++x)
			{
				vec4 slot_rect = { coord + vec2(x, y) * slot_size, slot_size };
				uvec4 slot_trect = uvec4(slot_rect * vec2(m_size));

				slice.m_slots.push_back({ slot++, nullptr, slot_rect, slot_trect });

				bool at_block = x % 4 == 0 && y % 2 == 0;
				bool has_space = subdiv - x >= 4 && subdiv - y >= 2;
				if(at_block && has_space)
				{
					Block block = { { at(x+0, y+0), at(x+1, y+0), at(x+2, y+0), at(x+3, y+0),
									  at(x+0, y+1), at(x+1, y+1), at(x+2, y+1), at(x+3, y+1) } };
					slice.m_slots.back().m_block = uint16_t(slice.m_blocks.size());
					slice.m_blocks.push_back(block);
				}
			}

		// @todo change to high water mark + free list under water mark
		for(uint32_t i = 0; i < slice.m_slots.size(); ++i)
		{
			slice.m_free_slots.push_back(i);
		}

		for(uint32_t i = 0; i < slice.m_blocks.size(); ++i)
		{
			slice.m_free_blocks.push_back(i);
		}
	}

	ShadowAtlas::Slot& ShadowAtlas::alloc(Slice& slice, bool block6)
	{
		assert((block6 && !slice.m_free_blocks.empty()) || (!block6 && !slice.m_free_slots.empty()));
		uint32_t index = block6 ? pop(slice.m_free_blocks) : pop(slice.m_free_slots);
		if(block6)
		{
			Block& block = slice.m_blocks[index];
			remove_if(slice.m_free_slots, [&](uint32_t slot) { for(size_t i = 0; i < 6; ++i) if(block.m_slots[i] == slot) return true; return false; });
			index = block.m_slots[0];
		}
		return slice.m_slots[index];
	}

	void ShadowAtlas::yield(Slice& slice, uint32_t index)
	{
		Slot& slot = slice.m_slots[index];
		slot.m_light = nullptr;
		if(slot.m_block != UINT16_MAX)
		{
			Block& block = slice.m_blocks[slot.m_block];
			slice.m_free_blocks.push_back(slot.m_block);
			for(size_t i = 0; i < 6; ++i)
				slice.m_free_slots.push_back(block.m_slots[i]);
		}
		else
		{
			slice.m_free_slots.push_back(index);
		}

	}
	void ShadowAtlas::remove_light(Light& light, bool block)
	{
		UNUSED(block);
		Slice& slice = m_slices[light.m_shadow_index.slice];
		this->yield(slice, light.m_shadow_index.slot);
	}

	bool ShadowAtlas::update_light(Light& light, uint32_t frame, float coverage, uint32_t light_version)
	{
		UNUSED(light_version);

		if(light.m_type == LightType::Point)
			coverage /= 4.f;
			//coverage /= 6.f;

		if(light.m_shadow_index.slice != UINT8_MAX)
		{
			Slice& slice = m_slices[light.m_shadow_index.slice];
			Slot& slot = slice.m_slots[light.m_shadow_index.slot];
			slot.m_frame = frame;
			const float space = 1.f / float(slice.m_subdiv);
			if(space >= coverage) return false;
			this->remove_light(light, true);
		}

		//printf("looking for a shadow atlas slot of size %i\n", int(target_size));

		auto find_slice = [&]() -> Slice*
		{
			for(Slice& slice : m_slices)
			{
				const float space = 1.f / float(slice.m_subdiv);
				if(space < coverage)
				{
					printf("atlas slice %i subdiv %i can't hold light with coverage %.2f space %.2f\n", slice.m_index, slice.m_subdiv, coverage, space);
					continue;
				}
				if(light.m_type == LightType::Point && !slice.m_free_blocks.empty())
					return &slice;
				else if(light.m_type != LightType::Point && !slice.m_free_slots.empty())
					return &slice;
			}
			return nullptr;
		};

		auto setup_slice = [&]() -> Slice*
		{
			for(Slice& slice : m_slices)
				if(slice.m_subdiv == 0)
				{
					// slice isn't used yet, so we can subdivide it to whatever size we need
					uint16_t subdiv = next_pow2(uint16_t(1.f / coverage));
					this->subdiv(slice, subdiv);
					return &slice;
				}
			return nullptr;
		};

		Slice* slice = find_slice();
		if(slice == nullptr)
			slice = setup_slice();

		if(slice != nullptr)
		{
			Slot& slot = this->alloc(*slice, light.m_type == LightType::Point);
			slot.m_light = &light;
			slot.m_frame = frame;
			light.m_shadow_index = { slice->m_index, slot.m_index };
			return true;
		}

		return false;
	}

	vec4 ShadowAtlas::render_update(Render& render, Light& light)
	{
		if(light.m_type == LightType::Direct)
		{
			// direct light has full coverage (1.0)
			const bool redraw = this->update_light(light, render.m_frame->m_frame, 1.f, light.m_last_update);
			UNUSED(redraw);
			return this->light_slot(light).m_rect;
		}

		const Plane camera_near_plane = render.m_camera->near_plane();

		vec3 points[2];

		const Node3& node = *light.m_node;
		if(light.m_type == LightType::Point)
		{
			points[0] = node.position();
			points[1] = node.position() + node.axis(x3) * light.m_range;
		}
		else if(light.m_type == LightType::Spot)
		{
			const float w = light.m_range * sin(light.m_spot_angle);
			const float d = light.m_range * cos(light.m_spot_angle);

			const vec3 base = light.m_node->position() + node.direction() * d;

			points[0] = base;
			points[1] = base + node.axis(x3) * w;
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

		const vec2 size = frustum_viewport_size(render.m_camera->m_proj);

		const float diameter = distance(points[0], points[1]) * 2.f;
		const float coverage = diameter / (size.x + size.y);

		//if(light.m_shadow_dirty) // updated when lights and objects bounds start or stop intersecting, or move
		//{
		//	light.m_last_version++;
		//	light.m_shadow_dirty = false;
		//}

		// @todo fix coverage calculation
		const bool redraw = this->update_light(light, render.m_frame->m_frame, 1.f, light.m_last_update);
		//const bool redraw = this->update_light(light, render.m_frame->m_frame, min(coverage, 1.f), light.m_last_update);
		UNUSED(redraw);
		return this->light_slot(light).m_rect;
	}
}

//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <gfx/Cpp20.h>
module two.gfx;
#else
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <stl/map.h>
#include <stl/algorithm.h>
#include <math/Math.h>
#include <math/Vec.hpp>
#include <gfx/Picker.h>
#include <gfx/Frustum.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Shot.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Material.h>
#include <gfx/RenderTarget.h>
#include <gfx/Renderer.h>
#include <gfx/Program.h>
#include <gfx/Asset.h>
#include <gfx/Camera.h>
#include <gfx/GfxSystem.h>
#endif

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
		if(!query || render.m_shot->m_items.empty()) return;

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

			for(const ModelElem& elem : item.m_model->m_items)
			{
				Material& material = elem.m_mesh->m_material ? *elem.m_mesh->m_material : *item.m_material;

				ProgramVersion program = { m_program };

				// @todo reuse logic from Renderer to make sure this is correct
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

					if(id == uint32_t(255 << 24) || id >= render.m_shot->m_items.size())
						continue;

					add(items, render.m_shot->m_items[id]);

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

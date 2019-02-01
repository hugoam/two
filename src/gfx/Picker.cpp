//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
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

#include <bx/bx.h>
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

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <geom/Mesh.h>
#include <gfx/Culling.h>
#include <gfx/Viewport.h>
#include <gfx/Shot.h>
#include <gfx/Item.h>
#include <gfx/Model.h>
#include <gfx/Mesh.h>
#include <gfx/Camera.h>
#include <gfx/Scene.h>
#include <gfx/Filter.h>
#include <gfx/Pipeline.h>
#include <gfx/RenderTarget.h>
#include <gfx/GfxSystem.h>
#endif

#include <MaskedOcclusionCulling.h>

namespace mud
{
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
		unsigned int width, height;
		m_moc->GetResolution(width, height);

		if(width != rect_w(viewport.m_rect) || height != rect_h(viewport.m_rect))
			m_moc->SetResolution(rect_w(viewport.m_rect), rect_h(viewport.m_rect));

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
	}

	void Culler::rasterize(Render& render)
	{
		mat4 world_to_clip = render.m_camera.m_projection * render.m_camera.m_transform;

		for(Item* item : render.m_shot->m_items)
		{
			if((item->m_flags & ItemFlag::Occluder) == 0)
				continue;

			mat4 model_to_clip = world_to_clip * item->m_node->m_transform;

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
										   MaskedOcclusionCulling::BACKFACE_NONE, MaskedOcclusionCulling::CLIP_PLANE_ALL, layout);
				}
				else
				{
					uint16_t* indices = (uint16_t*)mesh.m_cached_indices.data();
					m_moc->RenderTriangles(vertices, indices, mesh.m_index_count / 3, value_ptr(model_to_clip),
										   MaskedOcclusionCulling::BACKFACE_NONE, MaskedOcclusionCulling::CLIP_PLANE_ALL, layout);
				}
			}
		}
	}

	void Culler::cull(Render& render)
	{
		mat4 world_to_clip = render.m_camera.m_projection * render.m_camera.m_transform;

		std::vector<Item*> items = render.m_shot->m_items;
		render.m_shot->m_items.clear();

		Plane near = render.m_camera.near_plane();

		struct DepthRect { vec4 corners; float depth; };
		auto project_aabb = [](const mat4& transform, const Aabb& aabb) -> DepthRect
		{
			vec4 center = transform * vec4(aabb.m_center, 1.f);
			vec4 lo = transform * vec4(aabb.m_center - aabb.m_extents, 1.f);
			vec4 hi = transform * vec4(aabb.m_center + aabb.m_extents, 1.f);
			//float mindepth = min(lo.w, hi.w);
			float depth = center.w;
			lo /= lo.w;
			hi /= hi.w;
			vec2 loclip = min(lo, hi);
			vec2 hiclip = max(lo, hi);
			return { vec4(loclip.x, loclip.y, hiclip.x, hiclip.y), depth };
		};

		for(Item* item : items)
		{
			if((item->m_flags & ItemFlag::Occluder) != 0)
			{
				render.m_shot->m_items.push_back(item);
				continue;
			}

			DepthRect bounds = project_aabb(world_to_clip, item->m_aabb);

			MaskedOcclusionCulling::CullingResult result = m_moc->TestRect(bounds.corners.x, bounds.corners.y, bounds.corners.z, bounds.corners.w, bounds.depth);
			if(result == MaskedOcclusionCulling::VISIBLE)
				render.m_shot->m_items.push_back(item);
		}
	}

	void Culler::debug(Render& render)
	{
		if(render.m_frame.m_frame % 100 == 0)
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
		copy.debug_show_texture(as<FrameBuffer>(*render.m_target), m_depth_texture);
	}
}

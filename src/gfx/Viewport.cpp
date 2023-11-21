//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <bgfx/bgfx.h>
#include <gfx/Cpp20.h>
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
			m_clusters->clusterize_lights(*m_camera, render.m_shot->m_lights);
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

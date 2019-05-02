//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx;
#else
#include <math/Vec.hpp>
#include <geom/Primitive.hpp>
#include <geom/Geom.hpp>
#include <geom/Geometry.h>
#include <geom/Shapes.h>
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
#include <gfx/Draw.h>
#include <gfx/RenderTarget.h>
#include <gfx/GfxSystem.h>
#endif

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

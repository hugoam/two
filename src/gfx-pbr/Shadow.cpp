//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <stl/algorithm.h>
#include <pool/ObjectPool.hpp>
#include <math/Math.h>
#include <math/Axes.h>
#include <geom/Geom.hpp>
#include <geom/Intersect.h>
#include <gfx/ManualRender.h>
#include <gfx/Item.h>
#include <gfx/Shot.h>
#include <gfx/Frustum.h>
#include <gfx/Model.h>
#include <gfx/Program.h>
#include <gfx/Filter.h>
#include <gfx/Pipeline.h>
#include <gfx/Scene.h>
#include <gfx/RenderTarget.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/Lighting.h>
#include <gfx-pbr/Gpu/Light.hpp>
#endif

#include <cstdio>

#define DEBUG_CSM 0
#define DEBUG_ATLAS 0

#define SHADOW_ATLAS 1

namespace mud
{
	GpuState<GpuCSM> GpuState<GpuCSM>::me;
	GpuState<GpuShadow> GpuState<GpuShadow>::me;

	float snap_step(float value, float step)
	{
		return std::floor(value / step + 0.5f) * step;
	}

	uvec4 target_rect(const LightShadow& shadow, const uvec2& shadowmap_size)
	{
		uvec4 viewport_rect = shadow.m_rect;
		if(bgfx::getCaps()->originBottomLeft)
			viewport_rect.y = shadowmap_size.y - viewport_rect.y - rect_h(viewport_rect);
		return viewport_rect;
	}

	uvec4 csm_rect(uint size, size_t num_direct, size_t index)
	{
		uvec4 light_rect;

		if(num_direct == 1)
		{
			light_rect = { 0U, 0U, size, size };
		}
		else if(num_direct == 2)
		{
			light_rect = { 0U, 0U, size, size / 2 };
			light_rect.x += index == 1 ? rect_w(light_rect) : 0;
		}
		else
		{
			light_rect = { 0U, 0U, size / 2, size / 2 };
			light_rect.x += index & 1 ? rect_w(light_rect) : 0;
			light_rect.y += index / 2 ? rect_h(light_rect) : 0;
		}

		return light_rect;
	}

	uvec4 csm_pass_rect(const uvec4& atlas_rect, Light& light, size_t pass)
	{
		uvec4 pass_rect = atlas_rect;

		if(light.m_shadow_num_splits == 4)
		{
			rect_w(pass_rect) /= 2;
			rect_h(pass_rect) /= 2;
			pass_rect.x += pass % 2 == 0 ? 0 : rect_w(pass_rect);
			pass_rect.y += pass < 2 ? 0 : rect_h(pass_rect);
		}
		else if(light.m_shadow_num_splits == 2)
		{
			rect_h(pass_rect) /= 2;
			pass_rect.y += pass == 0 ? 0 : rect_h(pass_rect);
		}

		return pass_rect;
	}

	template <class T_Filter>
	vector<Item*> filter_cull(Scene& scene, T_Filter filter, bool nofilter = false)
	{
		vector<Item*> culled;
		scene.m_pool->pool<Item>().iterate([&](Item& item) {
			if(nofilter || filter(item))
			{
				culled.push_back(&item);
			}
		});
		return culled;
	}

	template <class T_Filter>
	vector<Item*> frustum_cull(Scene& scene, const Plane6& frustum_planes, T_Filter filter, bool nofilter = false)
	{
		vector<Item*> culled;
		scene.m_pool->pool<Item>().iterate([&](Item& item) {
			if(nofilter || filter(item))
			{
				if(frustum_aabb_intersection(frustum_planes, item.m_aabb))
					culled.push_back(&item);
			}
		});
		return culled;
	}

	void cull_shadow_render(Render& render, vector<Item*>& result, const Plane6& planes)
	{
		auto filter = [](Item& item) { return item.m_visible && item.m_model->m_geometry[PrimitiveType::Triangles] && (item.m_flags & ItemFlag::Shadows) != 0; };
		result = filter_cull(render.m_scene, filter);
		//result = frustum_cull(items, planes, filter);

		for(Item* item : result)
			item->m_depth = distance(planes.m_near, item->m_aabb.m_center);
	}

	void cull_shadow_render(Render& render, vector<Item*>& result, const mat4& projection, const mat4& transform)
	{
		Plane6 planes = frustum_planes(projection, transform);
		cull_shadow_render(render, result, planes);
	}

#if 0
	void BlockShadow::light_shadow_block(Light& light, const uvec4& shadow_rect, const mat4& projection, const mat4& transform)
	{
		vec4 shadow_tex_rect = vec4(shadow_rect) / float(m_shadow_atlases[0].m_size);
		light.m_shadow_blocks.push_back({ shadow_tex_rect, projection, transform, {} });
	}
#endif

	LightBounds light_slice_bounds(const Frustum& slice, const mat4& light_transform)
	{
		LightBounds bounds;

		for(uint i = 0; i < 8; i++)
		{
			// Transform to light space.
			vec3 corner_light = vec3(light_transform * vec4(slice.m_corners[i], 1.f));

			bounds.min = min(bounds.min, corner_light);
			bounds.max = max(bounds.max, corner_light);
		}

		return bounds;
	}

	void light_slice_sphere_bounds(const FrustumSlice& slice, const mat4& light_transform, LightBounds& light_bounds, float texture_size)
	{
		float zmax = light_bounds.max.z;
		float radius = slice.m_frustum.m_radius * texture_size / (texture_size - 2.f);

		vec3 slice_center = vec3(light_transform * vec4(slice.m_frustum.m_center, 0.f));
		light_bounds.min = slice_center - radius;
		light_bounds.max = slice_center + radius;
		light_bounds.max.z = zmax;
	}

	void light_slice_cull(Render& render, Light& light, LightBounds& light_bounds, vector<Item*>& result)
	{
		vec3 x = light.m_node.axis(X3);
		vec3 y = light.m_node.axis(Y3);
		vec3 z = light.m_node.axis(Z3);

		Plane6 light_frustum_planes =
		{
			{  x,  light_bounds.max.x },
			{ -x, -light_bounds.min.x },
			{  y,  light_bounds.max.y },
			{ -y, -light_bounds.min.y },
			{  z,  light_bounds.max.z + 1e6f },
			{ -z, -light_bounds.min.z }
		};

		cull_shadow_render(render, result, light_frustum_planes);

		for(Item* item : result)
		{
			vec2 min_max = project_aabb_in_plane(Plane{ z, 0 }, item->m_aabb);
			float z_max = min_max[1];

			light_bounds.max.z = max(light_bounds.max.z, z_max);
		}
	}

	void stabilize_light_bounds(const FrustumSlice& slice, LightBounds& light_bounds, float texture_size)
	{
		float radius = slice.m_frustum.m_radius * texture_size / (texture_size - 2.f);

		float unit = radius * 2.0f / texture_size;

		light_bounds.max.x = snap_step(light_bounds.max.x, unit);
		light_bounds.min.x = snap_step(light_bounds.min.x, unit);
		light_bounds.max.y = snap_step(light_bounds.max.y, unit);
		light_bounds.min.y = snap_step(light_bounds.min.y, unit);
	}

	mat4 crop_shrink_light_proj(Light& light, const LightBounds& light_bounds, const mat4& light_proj, float texture_size)
	{
		vec2 minproj = vec2(bxmulh(light_proj, light_bounds.min));
		vec2 maxproj = vec2(bxmulh(light_proj, light_bounds.max));

		// total projection scale divided by actual projected bounds
		vec2 scale = 2.0f / (maxproj - minproj);

		if((light.m_shadow_flags & CSM_Stabilize) != 0)
		{
			const float quantizer = 64.0f;
			scale = quantizer / ceil(quantizer / scale);
		}

		vec2 offset = 0.5f * (maxproj + minproj) * scale;

		if((light.m_shadow_flags & CSM_Stabilize) != 0)
		{
			const float half_size = texture_size * 0.5f;
			offset = ceil(offset * half_size) / half_size;
		}

		vec4 rect = { offset, scale };
		mat4 light_crop = rect_mat(rect);

		// in the absence of stabilisation this is roughly equivalent to 
		// return bxortho(maxproj.x, minproj.x, maxproj.y, minproj.y, -light.m_shadow_range, light.m_shadow_range, 0.0f, bgfx::getCaps()->homogeneousDepth);
		return light_proj * light_crop;
	}
	
	void update_csm_slice(Render& render, Light& light, const mat4& light_transform, const mat4& light_proj, 
						  FrustumSlice& slice, CSMShadow& csm, LightShadow& shadow, const uvec4& atlas_rect, uint csm_size)
	{
		shadow.m_rect = csm_pass_rect(atlas_rect, light, slice.m_index);

		shadow.m_light_bounds = light_slice_bounds(slice.m_frustum, light_transform);

		shadow.m_items = render.m_shot->m_items;
		light_slice_cull(render, light, shadow.m_light_bounds, shadow.m_items);

		float texture_size = rect_w(vec4(shadow.m_rect));

		if(false)//light.m_shadow_flags == CSM_Stabilize)
		{
			light_slice_sphere_bounds(slice, light_transform, shadow.m_light_bounds, texture_size);
			stabilize_light_bounds(slice, shadow.m_light_bounds, texture_size);
		}

		shadow.m_uv_rect = vec4(shadow.m_rect) / float(csm_size);

		shadow.m_projection = crop_shrink_light_proj(light, shadow.m_light_bounds, light_proj, float(csm_size));
		shadow.m_transform = light_transform;

		mat4 crop_matrix = rect_mat(shadow.m_uv_rect) * bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, bgfx::getCaps()->homogeneousDepth);
		shadow.m_shadow_matrix = crop_matrix * shadow.m_projection * shadow.m_transform;

		shadow.m_bias_scale = slice.m_index == 0 ? 1.f : slice.m_frustum.m_radius / csm.m_frustum_slices[0].m_frustum.m_radius;

		shadow.m_frustum_slice = slice;
	}

	void BlockShadow::update_csm(Render& render, Light& light, size_t num_direct, CSMShadow& csm, size_t index)
	{
		csm.m_light = &light;
		csm.m_frustum_slices.resize(light.m_shadow_num_splits);
		split_frustum_slices(render.m_camera, csm.m_frustum_slices, light.m_shadow_num_splits, light.m_shadow_split_distribution);

		mat4 light_transform = bxlookat(-light.m_node.direction(), vec3(0.f));
		mat4 light_proj = bxortho(1.0f, -1.0f, 1.0f, -1.0f, -light.m_shadow_range, light.m_shadow_range, 0.0f, bgfx::getCaps()->homogeneousDepth);

		csm.m_slices.clear();
		csm.m_slices.resize(csm.m_frustum_slices.size());

		uvec4 atlas_rect = csm_rect(uint(m_csm.m_size), num_direct, index);

		for(size_t i = 0; i < csm.m_frustum_slices.size(); ++i)
		{
			FrustumSlice& slice = csm.m_frustum_slices[i];
			LightShadow& shadow = csm.m_slices[i];
			update_csm_slice(render, light, light_transform, light_proj, slice, csm, shadow, atlas_rect, m_csm.m_size.x);
		}
	}

	void BlockShadow::render_csm(Render& render, Light& light, CSMShadow& csm)
	{
		if(!bgfx::isValid(m_csm.m_fbo))
			return;

		for(LightShadow& slice : csm.m_slices)
		{
			ManualRender shadow_render = { render, Shading::Volume, m_csm.m_fbo, target_rect(slice, m_csm.m_size), slice.m_transform, slice.m_projection };
			shadow_render.m_sub_render.m_shot->m_items = slice.m_items;
			this->render(shadow_render, light, slice.m_depth_method, slice.m_bias_scale);
		}
	}

	void Shadowmap::create(const uvec2& size, DepthMethod method)
	{
		*this = {};
		m_size = size;
		m_depth_method = method;

		if(method == DepthMethod::Depth)
		{
			m_depth = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);
			m_fbo = bgfx::createFrameBuffer(1, &m_depth, true);
		}
		else if(method == DepthMethod::Distance)
		{
			m_color = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT | GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);
			m_fbo = bgfx::createFrameBuffer(1, &m_color, true);
		}
	}

	void ShadowmapCube::create(uint16_t size)
	{
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT))
			return;

		*this = {};
		m_size = size;
		m_depth = bgfx::createTextureCube(size, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT);

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachment = { bgfx::Access::Write, m_depth, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS };
			m_fbos[i] = bgfx::createFrameBuffer(1, &attachment, true);
		}
	}

	BlockShadow::BlockShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockLight& block_light)
		: DrawBlock(gfx, type<BlockShadow>())
		, m_block_depth(block_depth)
		, m_block_light(block_light)
	{
		static cstring options[] = { "CSM_SHADOW" };
		static cstring modes[] = { "PCF_LEVEL", "CSM_NUM_CASCADES" };
		m_shader_block->m_options = options;
		m_shader_block->m_modes = modes;

		//m_pcf_level = PCF_HARD;
		m_pcf_level = PCF_NONE;
	}

	void BlockShadow::init_block()
	{
		u_direct_shadow.createUniforms();
		u_shadow.createUniforms();

		GpuState<GpuCSM>::me.init();
		GpuState<GpuShadow>::me.init();
	}

	void BlockShadow::begin_render(Render& render)
	{
		UNUSED(render);
		if(m_direct_light && m_direct_light->m_shadows)
		{
			constexpr uint csm_size = 4096;
			if(m_csm.m_size.x != csm_size)
				m_csm.create(uvec2(csm_size));
		}

		for(Light* light : render.m_shot->m_lights)
			if(light->m_shadows && light->m_type != LightType::Direct)
			{
				if(m_atlas.m_size == 0)
					//m_atlas = { 1024U, { 4U } };
					m_atlas = { 1024U, { 2U, 4U, 8U, 16U } };

				m_atlas.render_update(render, *light);
			}

		this->setup_shadows(render);

#if DEBUG_ATLAS
		if(render.m_target)
		{
			BlockCopy& copy = *m_gfx.m_pipeline->block<BlockCopy>();
			//copy.debug_show_texture(render, m_atlas.m_depth, vec4(0.f), true);
			//copy.debug_show_texture(render, m_atlas.m_cubemaps[0].m_cubemap, vec4(0.f), true);
#if SHADOW_ATLAS
			copy.debug_show_texture(render, m_atlas.m_color, vec4(0.f));
#else
			if(m_shadowmaps.size() > 0)
				copy.debug_show_texture(render, m_shadowmaps[0].texture(), vec4(0.f), m_shadowmaps[0].m_depth_method == DepthMethod::Depth);
#endif
		}
#endif

#if DEBUG_CSM
		if(render.m_target)
		{
			BlockCopy& copy = *m_gfx.m_pipeline->block<BlockCopy>();
			copy.debug_show_texture(render, m_csm.m_depth, vec4(0.f), true);
		}
#endif
	}

	void BlockShadow::begin_pass(Render& render)
	{
		UNUSED(render);
		m_direct_light = m_block_light.m_direct_light;

		this->commit_shadows(render, render.m_camera.m_transform);
	}

	void BlockShadow::setup_shadows(Render& render)
	{
		size_t num_csm = 0;
		for(Light* light : render.m_shot->m_lights)
			if(light->m_shadows && light->m_type == LightType::Direct)
			{
				num_csm++;
			}

		size_t csm_index = 0;

		span<Light*> lights = render.m_shot->m_lights;
		lights.m_count = min(lights.m_count, size_t(c_max_forward_lights));

		m_csm_shadows.clear();
		m_shadows.clear();

		m_shadowmaps.resize(max(m_shadowmaps.size(), lights.size()));
		m_shadowmaps_cubes.resize(max(m_shadowmaps.size(), lights.size()));

		for(size_t index = 0; index < lights.size(); ++index)
		{
			Light& light = *lights[index];
			if(!light.m_shadows) continue;

			if(light.m_type == LightType::Direct)
			{
				CSMShadow& csm = push(m_csm_shadows);

				this->update_csm(render, light, num_csm, csm, csm_index++);
			}
			else if(light.m_type == LightType::Point)
			{
				if(light.m_shadow_index == UINT32_MAX)
					continue;

#if SHADOW_ATLAS
				uvec4 atlas_rect = m_atlas.light_slot(light).m_rect;
				uvec2 offset = { atlas_rect.x, atlas_rect.y };
				uint size = rect_w(atlas_rect);
#else
				uvec2 offset = uvec2(0U);
				uint size = 512U;
				Shadowmap& shadowmap = m_shadowmaps[light.m_index];
				if(shadowmap.m_size == uvec2(0U))
					shadowmap.create(uvec2(size * 4, size * 2), DepthMethod::Distance);
#endif

				mat4 projection = bxproj(90.f, 1.f, 0.01f, light.m_range, bgfx::getCaps()->homogeneousDepth);

				// These viewports map a cube-map onto a 2D texture with the
				// following orientation:
				//  xzXZ
				//   y Y

				const table<SignedAxis, uvec2> offsets =
				{
					offset + uvec2(size * 2, 0   ), // positive X
					offset + uvec2(0,		 0   ), // negative X
					offset + uvec2(size * 3, size), // positive Y
					offset + uvec2(size,     size), // negative Y
					offset + uvec2(size * 3, 0   ), // positive Z
					offset + uvec2(size,	 0   ), // negative Z
				};

#if SHADOW_ATLAS
				ShadowAtlas::Slice& slice = m_atlas.light_slice(light);
				float per_slice = float(slice.m_subdiv);
				vec2 atlas_slot = vec2(offset) / vec2(m_atlas.m_rect_size);
				vec2 atlas_subdiv = vec2(1.f / (per_slice * m_atlas.m_slices.size()), 1.f / per_slice);
#else
				vec2 atlas_slot = vec2(0.f);
				vec2 atlas_subdiv = vec2(1.f);
#endif

				m_block_light.m_gpu_shadows[index].atlas_slot = atlas_slot;
				m_block_light.m_gpu_shadows[index].atlas_subdiv = atlas_subdiv;

				for(SignedAxis axis : c_signed_axes)
				{
					// up stays up for all sides of the cube except when looking down (where it's forward aka -Z) or up (back aka Z)
					static const table<SignedAxis, vec3> view_up = { Y3, Y3, Z3, -Z3, Y3, Y3 };

					LightShadow& shadow = push(m_shadows);
					shadow.m_light = &light;
					shadow.m_rect = { offsets[axis], uvec2(size) };

					const vec3& position = light.m_node.position();
					shadow.m_transform = bxlookat(position, position + to_vec3(axis), view_up[axis]);
					shadow.m_projection = projection;
					//shadow.m_light_bounds = 

					shadow.m_items = render.m_shot->m_items;
					cull_shadow_render(render, shadow.m_items, shadow.m_projection, shadow.m_transform);

#if SHADOW_ATLAS
					shadow.m_fbo = m_atlas.m_fbo;
#else
					shadow.m_fbo = shadowmap.m_fbo;
#endif

					shadow.m_shadow_matrix = bxtranslation(-position);
					shadow.m_depth_method = DepthMethod::Distance;

				}
			}
			else if(light.m_type == LightType::Spot)
			{
				LightShadow& shadow = push(m_shadows);
				shadow.m_light = &light;
				shadow.m_rect = m_atlas.render_update(render, light);

				shadow.m_projection = bxproj(light.m_spot_angle * 2.f, 1.f, 0.01f, light.m_range, bgfx::getCaps()->homogeneousDepth);
				shadow.m_transform = light.m_node.m_transform;

				shadow.m_items = render.m_shot->m_items;
				cull_shadow_render(render, shadow.m_items, shadow.m_projection, shadow.m_transform);

				shadow.m_fbo = m_atlas.m_fbo;
				shadow.m_shadow_matrix = light.m_node.m_transform;

				//m_block_light.m_gpu_shadows[index].matrix = m_shadows.size() - 1;
			}
		}
	}

	void BlockShadow::render(ManualRender& render, Light& light, DepthMethod method, float bias_scale)
	{
		m_depth_method = method;

		m_distance_params.m_eye = light.m_node.position();
		m_distance_params.m_near = 0.01f;
		m_distance_params.m_far = light.m_range;

		m_depth_params.m_depth_bias = light.m_shadow_bias * bias_scale;
		m_depth_params.m_depth_normal_bias = light.m_shadow_normal_bias;
		m_depth_params.m_depth_z_far = light.m_shadow_range;

		Renderer& renderer = m_gfx.renderer(Shading::Volume);
		render.render(renderer);
	}

	void BlockShadow::render_shadows(Render& render)
	{
		for(CSMShadow& csm : m_csm_shadows)
			this->render_csm(render, *csm.m_light, csm);

		for(LightShadow& shadow : m_shadows)
		{
			// don't call target_rect(shadow, uvec2(1024U)) because
			ManualRender shadow_render = { render, Shading::Volume, shadow.m_fbo, shadow.m_rect, shadow.m_transform, shadow.m_projection };
			shadow_render.m_sub_render.m_shot->m_items = shadow.m_items;
			this->render(shadow_render, *shadow.m_light, shadow.m_depth_method);
		}
	}

	void BlockShadow::commit_shadows(Render& render, const mat4& view)
	{
		UNUSED(render);
		const mat4 inverse_view = inverse(view);

		for(CSMShadow& csm : m_csm_shadows)
		{
			for(uint32_t i = 0; i < csm.m_frustum_slices.size(); ++i)
			{
				m_csm_splits[i] = csm.m_frustum_slices[i].m_frustum.m_far;
				m_csm_matrix[i] = csm.m_slices[i].m_shadow_matrix * inverse_view;
			}
		}

		m_shadow_matrices.resize(m_shadows.size());

		size_t index = 0;
		for(LightShadow& shadow : m_shadows)
		{
			m_shadow_matrices[index] = shadow.m_shadow_matrix * inverse_view;

			m_block_light.m_gpu_shadows[shadow.m_light->m_index].matrix = float(index);

			index++;
		}

		m_block_light.upload_lights(render);
	}

	void BlockShadow::upload_shadows(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		GpuState<GpuCSM>::me.upload(render_pass, const_cast<BlockShadow*>(this)->m_csm_matrix, m_csm_splits);
		GpuState<GpuShadow>::me.upload(render_pass, const_cast<BlockShadow*>(this)->m_shadow_matrices);
	}

	void BlockShadow::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		shader_version.set_mode(m_index, PCF_LEVEL, uint8_t(m_pcf_level));

		if(direct && light->m_shadows)
		{
			shader_version.set_option(m_index, CSM_SHADOW);
			//shader_version.set_option(m_index, CSM_BLEND, light->m_shadow_blend_splits);
			shader_version.set_mode(m_index, CSM_NUM_CASCADES, light->m_shadow_num_splits);
		}
	}

	void BlockShadow::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);

		this->upload_shadows(render, render_pass);

		uint32_t shadow_csm = uint32_t(TextureSampler::ShadowCSM);
		bgfx::setViewUniform(render_pass.m_index, u_direct_shadow.s_csm_atlas, &shadow_csm);

		uint32_t shadow_atlas = uint32_t(TextureSampler::ShadowAtlas);
		bgfx::setViewUniform(render_pass.m_index, u_shadow.s_shadow_atlas, &shadow_atlas);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		if(direct && light->m_shadows)
		{
			vec4 csm_params = { 1.f / vec2(m_csm.m_size), vec2(0.f) };
			bgfx::setViewUniform(render_pass.m_index, u_direct_shadow.u_csm_params, &csm_params);

			vec2 pcf_offset = { 1.f, 1.f };
			vec4 pcf_params = { pcf_offset, vec2(0.f) };
			bgfx::setViewUniform(render_pass.m_index, u_shadow.u_pcf_params, &pcf_params);
		}

		if(!m_shadows.empty())
		{
			vec4 atlas_params = { vec2(m_atlas.m_rect_size), vec2(1.f) / float(m_atlas.m_size) };
			bgfx::setViewUniform(render_pass.m_index, u_shadow.u_shadow_atlas, &atlas_params);
		}
	}

	void BlockShadow::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(render_pass);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		bool shadow_sampler = false; // m_pcf_level != PCF_HARD
		uint32_t shadow_flags = shadow_sampler ? BGFX_SAMPLER_COMPARE_LESS : GFX_TEXTURE_POINT;

		if(direct && light->m_shadows)
		{
			encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), m_csm.m_depth, shadow_flags);
		}

#if SHADOW_ATLAS
		if(!m_shadows.empty())
		{
			encoder.setTexture(uint8_t(TextureSampler::ShadowAtlas), m_atlas.m_color, shadow_flags);
			//encoder.setTexture(uint8_t(TextureSampler::ShadowAtlas), m_atlas.m_depth, shadow_flags);
		}
#else
		if(!m_shadows.empty())
		{
			encoder.setTexture(uint8_t(TextureSampler::ShadowAtlas), m_shadowmaps[0].texture(), shadow_flags);
		}
#endif
	}

	PassShadowmap::PassShadowmap(GfxSystem& gfx, BlockShadow& block_shadow)
		: RenderPass(gfx, "shadowmap", PassType::Shadowmap)
		, m_block_shadow(block_shadow)
	{}

	void PassShadowmap::submit_render_pass(Render& render)
	{
		m_block_shadow.render_shadows(render);
	}

	PassShadow::PassShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockShadow& block_shadow)
		: PassDepth(gfx, "shadow", block_depth)
		, m_block_depth(block_depth)
		, m_block_shadow(block_shadow)
	{}

	void PassShadow::submit_render_pass(Render& render)
	{
		m_block_depth.m_depth_method = m_block_shadow.m_depth_method;
		m_block_depth.m_depth_params = m_block_shadow.m_depth_params;
		m_block_depth.m_distance_params = m_block_shadow.m_distance_params;

		DrawPass::submit_render_pass(render);
	}

	void PassShadow::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_program->m_blocks[MaterialBlock::Pbr] && !element.m_material->m_alpha.m_is_alpha)
			PassDepth::queue_draw_element(render, element);
	}
}

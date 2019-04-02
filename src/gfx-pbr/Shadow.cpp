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
#include <gfx/Item.h>
#include <gfx/Shot.h>
#include <gfx/Frustum.h>
#include <gfx/Camera.h>
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

#define DEBUG_ATLAS 0

namespace mud
{
	GpuState<GpuShadow> GpuState<GpuShadow>::me;

	float snap_step(float value, float step)
	{
		return std::floor(value / step + 0.5f) * step;
	}

	vec4 target_rect(const LightShadow& shadow)
	{
		vec4 rect = shadow.m_rect;
		if(bgfx::getCaps()->originBottomLeft)
			rect.y = 1.f - rect.y - rect.height;
		return rect;
	}

	vec4 csm_pass_rect(const vec4& atlas_rect, Light& light, size_t pass)
	{
		vec4 pass_rect = atlas_rect;

		if(light.m_shadow_num_splits == 4)
		{
			pass_rect.width /= 2.f;
			pass_rect.height /= 2.f;
			pass_rect.x += pass % 2 == 0 ? 0.f : pass_rect.width;
			pass_rect.y += pass < 2 ? 0.f : pass_rect.height;
		}
		else if(light.m_shadow_num_splits == 2)
		{
			pass_rect.height /= 2.f;
			pass_rect.y += pass == 0 ? 0.f : pass_rect.height;
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
		result = filter_cull(*render.m_scene, filter);
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
		vec3 x = light.m_node->axis(X3);
		vec3 y = light.m_node->axis(Y3);
		vec3 z = light.m_node->axis(Z3);

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
						  CSMSlice& slice, CSMShadow& csm, const vec4& atlas_rect, uint csm_size)
	{
		slice.m_light = &light;
		slice.m_rect = csm_pass_rect(atlas_rect, light, slice.m_index);
		
		slice.m_light_bounds = light_slice_bounds(slice.m_frustum, light_transform);

		slice.m_items = render.m_shot.m_items;
		light_slice_cull(render, light, slice.m_light_bounds, slice.m_items);

		if(false)//light.m_shadow_flags == CSM_Stabilize)
		{
			const float texture_size = float(slice.m_rect.width);
			light_slice_sphere_bounds(slice, light_transform, slice.m_light_bounds, texture_size);
			stabilize_light_bounds(slice, slice.m_light_bounds, texture_size);
		}

		slice.m_projection = crop_shrink_light_proj(light, slice.m_light_bounds, light_proj, float(csm_size));
		slice.m_transform = light_transform;

		mat4 crop_matrix = rect_mat(slice.m_rect) * bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, bgfx::getCaps()->homogeneousDepth);
		slice.m_shadow_matrix = crop_matrix * slice.m_projection * slice.m_transform;

		slice.m_bias_scale = slice.m_index == 0 ? 1.f : slice.m_frustum.m_radius / csm.m_slices[0].m_frustum.m_radius;

		slice.m_frustum_slice = slice;
	}

	void BlockShadow::update_csm(Render& render, Light& light, CSMShadow& csm)
	{
		csm.m_light = &light;
		csm.m_slices.resize(light.m_shadow_num_splits);

		vector<FrustumSlice*> slices;
		for(CSMSlice& slice : csm.m_slices)
			slices.push_back(&slice);

		split_frustum_slices(*render.m_camera, slices, light.m_shadow_num_splits, light.m_shadow_split_distribution);

		const mat4 light_transform = bxlookat(-light.m_node->direction(), vec3(0.f));
		const mat4 light_proj = bxortho(1.0f, -1.0f, 1.0f, -1.0f, -light.m_shadow_range, light.m_shadow_range, 0.0f, bgfx::getCaps()->homogeneousDepth);

		const ShadowAtlas::Slot& slot = m_atlas.light_slot(light);

		for(size_t i = 0; i < csm.m_slices.size(); ++i)
		{
			CSMSlice& slice = csm.m_slices[i];
			update_csm_slice(render, light, light_transform, light_proj, slice, csm, slot.m_rect, slot.m_trect.width);
			slice.m_fbo = &m_atlas.m_fbo;
		}
	}

	void Shadowmap::create(const uvec2& size, DepthMethod method)
	{
		//*this = {};
		m_size = size;
		m_depth_method = method;

		if(method == DepthMethod::Depth)
		{
			m_depth = { size, false, TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP };
			m_fbo = { m_depth };
		}
		else if(method == DepthMethod::Distance)
		{
			m_color = { size, false, TextureFormat::RGBA8, BGFX_TEXTURE_RT | GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP };
			m_fbo = { m_color };
		}
	}

	void ShadowmapCube::create(uint32_t size)
	{
		const uint64_t flags = BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT;
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, flags))
			return;

		m_size = size;
		m_depth = { uvec2(size), false, TextureFormat::D24S8, flags, true };

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attach = { bgfx::Access::Write, m_depth, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS };
			m_fbos[i] = { uvec2(size), m_depth, { attach } };
		}
	}

	BlockShadow::BlockShadow(GfxSystem& gfx, BlockDepth& block_depth, BlockLight& block_light)
		: DrawBlock(gfx, type<BlockShadow>())
		, m_block_depth(block_depth)
		, m_block_light(block_light)
	{
		m_shader_block.m_options = { "CSM_SHADOW" };
		m_shader_block.m_modes = { "PCF_LEVEL" };

		//m_pcf_level = PCF_HARD;
		m_pcf_level = PCF_NONE;
	}

	void BlockShadow::init_block()
	{
		u_shadow.createUniforms();

		GpuState<GpuShadow>::me.init();
	}

	void BlockShadow::begin_render(Render& render)
	{
		UNUSED(render);

		for(Light* light : render.m_shot.m_lights)
			if(light->m_shadows)
			{
				if(m_atlas.m_side == 0)
					//m_atlas = { 1024U, { 4U } };
					m_atlas = { 1024U, { 1U, 1U } };
					//m_atlas = { 1024U, { 2U, 4U, 8U, 16U } };

				m_atlas.render_update(render, *light);
			}

		this->setup_shadows(render);

#if DEBUG_ATLAS
		//m_gfx.m_copy->debug_show_texture(render, m_atlas.m_depth, vec4(0.f));
		m_gfx.m_copy->debug_show_texture(render, m_atlas.m_color, vec4(0.f));
#endif
	}

	void BlockShadow::setup_shadows(Render& render)
	{
		span<Light*> lights = render.m_shot.m_lights;
		lights.m_count = min(lights.m_count, size_t(c_max_forward_lights));

		m_csm_shadows.clear();
		m_shadows.clear();

		for(size_t index = 0; index < lights.size(); ++index)
		{
			Light& light = *lights[index];
			if(!light.m_shadows) continue;

			if(light.m_type == LightType::Direct)
			{
				CSMShadow& csm = push(m_csm_shadows);
				if(m_atlas.m_size != uvec2(0U))
					this->update_csm(render, light, csm);
			}
			else if(light.m_type == LightType::Point)
			{
				if(light.m_shadow_index == UINT32_MAX)
					continue;

				const ShadowAtlas::Slot& slot = m_atlas.light_slot(light);
				const vec4 atlas_rect = slot.m_rect;
				const vec2 slot_coord = { atlas_rect.x, atlas_rect.y };
				const vec2 slot_size = { atlas_rect.width, atlas_rect.height };

				const mat4 projection = bxproj(90.f, 1.f, 0.01f, light.m_range, bgfx::getCaps()->homogeneousDepth);

				// These viewports map a cube-map onto a 2D texture with the
				// following orientation:
				//  xzXZ
				//   y Y

				const table<SignedAxis, vec2> offsets =
				{
					slot_coord + vec2(2.f, 0.f) * slot_size, // positive X
					slot_coord + vec2(0.f, 0.f) * slot_size, // negative X
					slot_coord + vec2(3.f, 1.f) * slot_size, // positive Y
					slot_coord + vec2(1.f, 1.f) * slot_size, // negative Y
					slot_coord + vec2(3.f, 0.f) * slot_size, // positive Z
					slot_coord + vec2(1.f, 0.f) * slot_size, // negative Z
				};

				m_block_light.m_gpu_lights[index].shadow.atlas_slot = slot_coord;
				m_block_light.m_gpu_lights[index].shadow.atlas_subdiv = slot_size;

				for(SignedAxis axis : c_signed_axes)
				{
					// up stays up for all sides of the cube except when looking down (where it's forward aka -Z) or up (back aka Z)
					static const table<SignedAxis, vec3> view_up = { Y3, Y3, Z3, -Z3, Y3, Y3 };

					LightShadow& shadow = push(m_shadows);
					shadow.m_light = &light;
					shadow.m_rect = { offsets[axis], slot_size };
					shadow.m_far = light.m_range;

					const vec3& position = light.m_node->position();
					shadow.m_transform = bxlookat(position, position + to_vec3(axis), view_up[axis]);
					shadow.m_projection = projection;
					//shadow.m_light_bounds = 

					shadow.m_items = render.m_shot.m_items;
					cull_shadow_render(render, shadow.m_items, shadow.m_projection, shadow.m_transform);

					shadow.m_fbo = &m_atlas.m_fbo;

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
				shadow.m_transform = light.m_node->m_transform;

				shadow.m_items = render.m_shot.m_items;
				cull_shadow_render(render, shadow.m_items, shadow.m_projection, shadow.m_transform);

				shadow.m_fbo = &m_atlas.m_fbo;
				shadow.m_shadow_matrix = light.m_node->m_transform;

				//m_block_light.m_gpu_shadows[index].matrix = m_shadows.size() - 1;
			}
		}
	}

	void BlockShadow::commit_shadows(Render& render, const mat4& view)
	{
		UNUSED(render);
		const mat4 inverse_view = inverse(view);

		size_t index = 0;

		m_shadow_matrices.resize(m_csm_shadows.size() * 4 + m_shadows.size());

		for(const CSMShadow& csm : m_csm_shadows)
		{
			size_t i = 0;
			for(const CSMSlice& slice : csm.m_slices)
			{
				GpuCSMShadow& gpu = m_block_light.m_gpu_lights[slice.m_light->m_index].csm;

				m_shadow_matrices[index] = slice.m_shadow_matrix * inverse_view;

				gpu.num_slices = slice.m_light->m_shadow_num_splits;
				gpu.matrices[i] = float(index);
				gpu.splits[i] = slice.m_frustum.m_far;

				index++; i++;
			}
		}

		for(const LightShadow& shadow : m_shadows)
		{
			GpuShadow& gpu = m_block_light.m_gpu_lights[shadow.m_light->m_index].shadow;

			m_shadow_matrices[index] = shadow.m_shadow_matrix * inverse_view;

			gpu.matrix = float(index);
			gpu.bias = shadow.m_light->m_shadow_bias;
			gpu.radius = 1.f;
			gpu.range = shadow.m_far;

			index++;
		}

		m_block_light.upload_lights(render);
	}

	void BlockShadow::upload_shadows(Render& render, const Pass& pass) const
	{
		UNUSED(render);
		GpuState<GpuShadow>::me.upload(pass, const_cast<BlockShadow*>(this)->m_shadow_matrices);
	}

	void BlockShadow::options(Render& render, ProgramVersion& shader_version) const
	{
		UNUSED(render);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		shader_version.set_mode(m_index, PCF_LEVEL, uint8_t(m_pcf_level));

		if(direct && light->m_shadows)
		{
			shader_version.set_option(m_index, CSM_SHADOW);
			//shader_version.set_option(m_index, CSM_BLEND, light->m_shadow_blend_splits);
		}
	}

	void BlockShadow::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);

		this->upload_shadows(render, pass);

		uint32_t shadow_atlas = uint32_t(TextureSampler::Shadow);
		bgfx::setViewUniform(pass.m_index, u_shadow.s_shadow_atlas, &shadow_atlas);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		if(direct && light->m_shadows)
		{
			vec4 csm_p0 = { 1.f / vec2(m_atlas.m_size), vec2(0.f) };
			bgfx::setViewUniform(pass.m_index, u_shadow.u_csm_p0, &csm_p0);

			vec2 pcf_offset = { 1.f, 1.f };
			vec4 pcf_p0 = { pcf_offset, vec2(0.f) };
			bgfx::setViewUniform(pass.m_index, u_shadow.u_pcf_p0, &pcf_p0);
		}

		if(!m_shadows.empty())
		{
			vec4 atlas_p0 = { vec2(m_atlas.m_size), vec2(1.f) / float(m_atlas.m_side) };
			bgfx::setViewUniform(pass.m_index, u_shadow.u_shadow_atlas, &atlas_p0);
		}
	}

	void BlockShadow::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);

		bgfx::Encoder& encoder = *pass.m_encoder;

		bool shadow_sampler = false; // m_pcf_level != PCF_HARD
		uint32_t shadow_flags = shadow_sampler ? BGFX_SAMPLER_COMPARE_LESS : GFX_TEXTURE_POINT;

		// @todo for now normal shadows and direct shadows are incompatible because we use color for the former and depth for the latter
		// we should be able to switch the distance shader to write to the depth buffer
		if(!m_shadows.empty())
		{
			encoder.setTexture(uint8_t(TextureSampler::Shadow), m_atlas.m_color, shadow_flags);
		}

		if(!m_csm_shadows.empty())
		{
			encoder.setTexture(uint8_t(TextureSampler::Shadow), m_atlas.m_depth, shadow_flags);
		}
	}

	void pass_shadowmaps(GfxSystem& gfx, Render& render)
	{
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();

		auto setup_block = [&](Light& light, DepthMethod depth_method, float bias_scale = 1.f)
		{
			block_shadow.m_depth_method = depth_method;

			block_shadow.m_distance_params.m_eye = light.m_node->position();
			block_shadow.m_distance_params.m_near = 0.01f;
			block_shadow.m_distance_params.m_far = light.m_range;

			block_shadow.m_depth_params.m_depth_bias = light.m_shadow_bias * bias_scale;
			block_shadow.m_depth_params.m_depth_normal_bias = light.m_shadow_normal_bias;
			block_shadow.m_depth_params.m_depth_z_far = light.m_shadow_range;
		};

		auto render_shadow = [&](LightShadow& shadow, const vec4& rect)
		{
			Camera camera = Camera(shadow.m_transform, shadow.m_projection);
			Viewport viewport = Viewport(camera, *render.m_scene, rect);

			Render shadow_render = { Shading::Volume, viewport, *render.m_target, *shadow.m_fbo, *render.m_frame };
			shadow_render.m_shot.m_lights = render.m_shot.m_lights;
			shadow_render.m_shot.m_items = shadow.m_items;

			setup_block(*shadow.m_light, shadow.m_depth_method, shadow.m_bias_scale);

			RenderFunc renderer = gfx.renderer(Shading::Volume);
			gfx.m_renderer.subrender(render, shadow_render, gfx.renderer(Shading::Volume));
		};

		for(CSMShadow& csm : block_shadow.m_csm_shadows)
		{
			if(!block_shadow.m_atlas.m_fbo.valid())
				continue;

			for(LightShadow& slice : csm.m_slices)
				render_shadow(slice, target_rect(slice));
		}

		for(LightShadow& shadow : block_shadow.m_shadows)
		{
			render_shadow(shadow, shadow.m_rect);
		}
	}

	void pass_shadow(GfxSystem& gfx, Render& render)
	{
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();

		Pass pass = render.next_pass("shadow", PassType::Shadow);

		block_depth.m_depth_method = block_shadow.m_depth_method;
		block_depth.m_depth_params = block_shadow.m_depth_params;
		block_depth.m_distance_params = block_shadow.m_distance_params;

		block_depth.submit(render, pass);
		//block_shadow.submit(render, pass);

		pass_depth(gfx, render, pass, false);

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			if(!element.m_program->m_blocks[MaterialBlock::Lit] || element.m_material->m_alpha.m_is_alpha)
				return false;
			
			return queue_depth(gfx, render, pass, element);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

}

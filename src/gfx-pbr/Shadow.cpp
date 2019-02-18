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
#endif

//#define DEBUG_CSM

namespace mud
{
	float snap_step(float value, float step)
	{
		return std::floor(value / step + 0.5f) * step;
	}

	uvec4 csm_rect(uint size, size_t light_count, Light& light, size_t index, size_t pass)
	{
		uvec4 light_rect;

		if(light_count == 1)
		{
			light_rect = uvec4{ 0, 0, size, size };
		}
		else if(light_count == 2)
		{
			light_rect = uvec4{ 0, 0, size, size / 2 };
			light_rect.x += index == 1 ? rect_w(light_rect) : 0;
		}
		else
		{
			light_rect = uvec4{ 0, 0, size / 2, size / 2 };
			light_rect.x += index & 1 ? rect_w(light_rect) : 0;
			light_rect.y += index / 2 ? rect_h(light_rect) : 0;
		}

		uvec4 pass_rect = light_rect;

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

	struct ShadowRender : public ManualRender
	{
		ShadowRender(Render& render, Light& light, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection)
			: ManualRender(render, Shading::Volume, fbo, viewport_rect, transform, projection)
			, m_light(light)
		{}

		void render(BlockShadow& block_shadow, float bias_scale)
		{
			block_shadow.m_depth_params.m_depth_bias = m_light.m_shadow_bias * bias_scale;
			block_shadow.m_depth_params.m_depth_normal_bias = m_light.m_shadow_normal_bias;
			block_shadow.m_depth_params.m_depth_z_far = m_light.m_shadow_range;
			Renderer& renderer = block_shadow.m_gfx_system.renderer(Shading::Volume);
			ManualRender::render(renderer);
		}

		Light& m_light;
	};

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
		auto filter = [](Item& item) { return item.m_visible && item.m_model->m_geometry[PLAIN] && (item.m_flags & ItemFlag::Shadows) != 0; };
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
			vec3 corner_light = vec3(light_transform * vec4{ slice.m_corners[i], 1.f });

			bounds.min = min(bounds.min, corner_light);
			bounds.max = max(bounds.max, corner_light);
		}

		return bounds;
	}

	void light_slice_sphere_bounds(const FrustumSlice& slice, const mat4& light_transform, LightBounds& light_bounds, float texture_size)
	{
		float zmax = light_bounds.max.z;
		float radius = slice.m_frustum.m_radius * texture_size / (texture_size - 2.f);

		vec3 slice_center = vec3(light_transform * vec4{ slice.m_frustum.m_center, 0.f });
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
	
	void update_shadow_slice(Render& render, Light& light, size_t num_direct, size_t index, const mat4& light_transform, const mat4& light_proj, 
							 FrustumSlice& slice, LightShadow& shadow, LightShadow::Slice& shadow_slice, size_t csm_size)
	{
		shadow_slice.m_viewport_rect = vec4(csm_rect(uint(csm_size), num_direct, light, index, slice.m_index));

		shadow_slice.m_light_bounds = light_slice_bounds(slice.m_frustum, light_transform);

		shadow_slice.m_items = render.m_shot->m_items;
		light_slice_cull(render, light, shadow_slice.m_light_bounds, shadow_slice.m_items);

		float texture_size = float(rect_w(shadow_slice.m_viewport_rect));

		if(false)//light.m_shadow_flags == CSM_Stabilize)
		{
			light_slice_sphere_bounds(slice, light_transform, shadow_slice.m_light_bounds, texture_size);
			stabilize_light_bounds(slice, shadow_slice.m_light_bounds, texture_size);
		}

		shadow_slice.m_texture_rect = vec4(shadow_slice.m_viewport_rect) / float(csm_size);

		shadow_slice.m_projection = crop_shrink_light_proj(light, shadow_slice.m_light_bounds, light_proj, float(csm_size));
		shadow_slice.m_transform = light_transform;

		mat4 crop_matrix = rect_mat(shadow_slice.m_texture_rect) * bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, bgfx::getCaps()->homogeneousDepth);
		shadow_slice.m_shadow_matrix = crop_matrix * shadow_slice.m_projection * shadow_slice.m_transform;

		shadow_slice.m_bias_scale = slice.m_index == 0 ? 1.f : slice.m_frustum.m_radius / shadow.m_frustum_slices[0].m_frustum.m_radius;

		shadow_slice.m_frustum_slice = slice;
	}

	void BlockShadow::update_direct(Render& render, Light& light, size_t num_direct, size_t index)
	{
		LightShadow& shadow = m_shadows[index];

		shadow.m_frustum_slices.resize(light.m_shadow_num_splits);
		split_frustum_slices(render.m_camera, shadow.m_frustum_slices, light.m_shadow_num_splits, light.m_shadow_split_distribution);

		mat4 light_transform = bxlookat(-light.m_node.direction(), vec3(0.f));
		mat4 light_proj = bxortho(1.0f, -1.0f, 1.0f, -1.0f, -light.m_shadow_range, light.m_shadow_range, 0.0f, bgfx::getCaps()->homogeneousDepth);

		shadow.m_slices.clear();
		shadow.m_slices.resize(shadow.m_frustum_slices.size());

		for(size_t i = 0; i < shadow.m_frustum_slices.size(); ++i)
		{
			FrustumSlice& slice = shadow.m_frustum_slices[i];
			LightShadow::Slice& shadow_slice = shadow.m_slices[i];
			update_shadow_slice(render, light, num_direct, index, light_transform, light_proj, slice, shadow, shadow_slice, m_csm.m_size);
		}
	}

	void BlockShadow::render_direct(Render& render, Light& light, size_t index)
	{
		if(!bgfx::isValid(m_csm.m_fbo))
			return;

		LightShadow& shadow = m_shadows[index];

		for(LightShadow::Slice& slice : shadow.m_slices)
		{
			vec4 viewport_rect = slice.m_viewport_rect;
			if(bgfx::getCaps()->originBottomLeft)
				viewport_rect.y = 4096 - viewport_rect.y - rect_h(viewport_rect);

			ShadowRender shadow_render = { render, light, m_csm.m_fbo, uvec4(viewport_rect), slice.m_transform, slice.m_projection };
			shadow_render.m_sub_render.m_shot->m_items = slice.m_items;
			shadow_render.render(*this, slice.m_bias_scale);
		}
	}

	CSMShadow::CSMShadow(uint16_t size)
		: m_size(size)
	{
		m_depth = bgfx::createTexture2D(size, size, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);
		m_fbo = bgfx::createFrameBuffer(1, &m_depth, true);
	}

	BlockShadow::BlockShadow(GfxSystem& gfx_system, BlockDepth& block_depth)
		: DrawBlock(gfx_system, type<BlockShadow>())
		, m_block_depth(block_depth)
	{
		static cstring options[1] = { "CSM_SHADOW" };
		static cstring modes[2] = { "CSM_NUM_CASCADES", "CSM_PCF_LEVEL" };
		m_shader_block->m_options = { options, 1 };
		m_shader_block->m_modes = { modes, 2 };
	}

	void BlockShadow::init_block()
	{
		u_direct_shadow.createUniforms();
	}

	void BlockShadow::begin_render(Render& render)
	{
		UNUSED(render);
		if(m_direct_light && m_direct_light->m_shadows)
		{
			constexpr uint16_t csm_size = 4096;
			if(m_csm.m_size != csm_size)
				m_csm = { csm_size };
		}

		bool needs_atlases = false;
		if(needs_atlases)
		{
			m_atlas = { 1024, { 2, 4, 8, 16 } };
		}

#ifdef DEBUG_CSM
		if(render.m_target)
		{
			BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
			copy.debug_show_texture(render, m_csm.m_depth, vec4(0.f), true);
		}
#endif
	}

	void BlockShadow::update_shadows(Render& render)
	{
		size_t num_direct_shadow = 0;
		for(Light* light : render.m_shot->m_lights)
			if(light->m_shadows && light->m_type == LightType::Direct)
			{
				num_direct_shadow++;
			}

		size_t direct_shadow_index = 0;

		m_shadows.clear();

		for(Light* light : render.m_shot->m_lights)
		{
			if(!light->m_shadows)
				continue;

			m_shadows.emplace_back();

			if(light->m_type == LightType::Direct)
			{
				this->update_direct(render, *light, num_direct_shadow, direct_shadow_index);
				direct_shadow_index++;
			}
		}
	}

	void BlockShadow::render_shadows(Render& render)
	{
		size_t direct_shadow_index = 0;

		for(Light* light : render.m_shot->m_lights)
		{
			if(!light->m_shadows)
				continue;

			if(light->m_type == LightType::Direct)
			{
				this->render_direct(render, *light, direct_shadow_index);
				direct_shadow_index++;
			}
			if(light->m_type == LightType::Point)
			{
				uvec4 atlas_rect = m_atlas.render_update(render, *light);

				mat4 projection = bxproj(90.f, 1.f, 0.01f, light->m_range, bgfx::getCaps()->homogeneousDepth);

				for(int i = 0; i < 6; i++)
				{
					static const vec3 view_normals[6] = { -X3, X3, -Y3, Y3, -Z3, Z3 };
					static const vec3 view_up[6] = { -Y3, -Y3, -Z3, Z3, -Y3, -Y3 };

					mat4 transform = light->m_node.m_transform * bxlookat(vec3(0.f), view_normals[i], view_up[i]);

					ShadowCubemap& cubemap = m_atlas.light_cubemap(*light, uint16_t(rect_w(atlas_rect)));

					ShadowRender shadow_render = { render, *light, cubemap.m_fbos[i], { uvec2(0U), uvec2(uint(cubemap.m_size)) }, projection, transform };
					cull_shadow_render(render, shadow_render.m_sub_render.m_shot->m_items, projection, transform);
					shadow_render.render(*this, 1.f);
				}
			}
			else if(light->m_type == LightType::Spot)
			{
				uvec4 atlas_rect = m_atlas.render_update(render, *light);

				mat4 projection = bxproj(light->m_spot_angle * 2.f, 1.f, 0.01f, light->m_range, bgfx::getCaps()->homogeneousDepth);
				mat4 transform = light->m_node.m_transform;

				ShadowRender shadow_render = { render, *light, m_atlas.m_fbo, atlas_rect, projection, transform };
				cull_shadow_render(render, shadow_render.m_sub_render.m_shot->m_items, projection, transform);
				shadow_render.render(*this, 1.f);
			}
		}
	}

	void BlockShadow::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockShadow::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockShadow::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		if(direct && light->m_shadows)
		{
			shader_version.set_option(m_index, CSM_SHADOW);
			//shader_version.set_option(m_index, CSM_BLEND, light->m_shadow_blend_splits);
			shader_version.set_mode(m_index, CSM_NUM_CASCADES, light->m_shadow_num_splits);
			shader_version.set_mode(m_index, CSM_PCF_LEVEL, uint8_t(m_pcf_level));
		}
	}

	void BlockShadow::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		uint8_t shadow_csm = uint8_t(TextureSampler::ShadowCSM);
		bgfx::setViewUniform(render_pass.m_index, u_direct_shadow.s_csm_atlas, &shadow_csm);

		//uint8_t shadow_atlas = uint8_t(TextureSampler::ShadowAtlas);
		//bgfx::setViewUniform(render_pass.m_index, u_shadow.s_shadow_atlas, &shadow_atlas);
	}

	void BlockShadow::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		Light* light = m_direct_light;
		bool direct = light; //&& (element.m_item->m_layer_mask & light->m_layers) != 0;

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(direct && light->m_shadows)
		{
			vec2 pcf_offset = { 1.f, 1.f };
			vec4 csm_params = { vec2(1.f / float(m_csm.m_size)), pcf_offset };
			encoder.setUniform(u_direct_shadow.u_csm_params, &csm_params);

			if(m_pcf_level == CSM_HARD_PCF)
				encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), m_csm.m_depth, GFX_TEXTURE_POINT);
			else
				encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), m_csm.m_depth, BGFX_SAMPLER_COMPARE_LESS);
				//encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), u_direct_shadow.s_csm_atlas, m_csm.m_depth);
		}

		if(0)//render.m_shadow_atlas)
		{
			encoder.setTexture(uint8_t(TextureSampler::ShadowAtlas), m_atlas.m_depth, BGFX_SAMPLER_COMPARE_LESS);
			vec2 shadow_atlas_pixel_size = vec2(1.f) / float(m_atlas.m_size);
			encoder.setUniform(u_shadow.u_shadow_pixel_size, &shadow_atlas_pixel_size[0]);
		}
	}

	PassShadowmap::PassShadowmap(GfxSystem& gfx_system, BlockShadow& block_shadow)
		: RenderPass(gfx_system, "shadowmap", PassType::Shadowmap)
		, m_block_shadow(block_shadow)
	{}

	void PassShadowmap::submit_render_pass(Render& render)
	{
		m_block_shadow.update_shadows(render);
		m_block_shadow.render_shadows(render);
	}

	PassShadow::PassShadow(GfxSystem& gfx_system, BlockDepth& block_depth, BlockShadow& block_shadow)
		: PassDepth(gfx_system, block_depth)
		, m_block_depth(block_depth)
		, m_block_shadow(block_shadow)
	{}

	void PassShadow::next_draw_pass(Render& render, Pass& render_pass)
	{
		PassDepth::next_draw_pass(render, render_pass);

		m_block_depth.m_current_params = &m_block_shadow.m_depth_params;
	}

	void PassShadow::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
			PassDepth::queue_draw_element(render, element);
	}
}

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <infra/Vector.h>
#include <math/Math.h>
#include <gfx/ManualRender.h>
#include <gfx/Item.h>
#include <gfx/Shot.h>
#include <gfx/Program.h>
#include <gfx/Filter.h>
#include <gfx/Pipeline.h>
#include <gfx/RenderTarget.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/Light.h>
#endif

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
		ShadowRender(Render& render, Light& light, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect)
			: ManualRender(render, fbo, viewport_rect)
			, m_light(light)
		{
			if(bgfx::getCaps()->originBottomLeft)
				m_viewport.m_rect.y = 4096 - m_viewport.m_rect.y - rect_h(m_viewport.m_rect);
		}

		ShadowRender(Render& render, Light& light, bgfx::FrameBufferHandle fbo, const uvec4& viewport_rect, const mat4& transform, const mat4& projection)
			: ManualRender(render, fbo, viewport_rect, transform, projection)
			, m_light(light)
		{}

		void render(BlockDepth& block_depth, float bias_scale)
		{
			block_depth.m_depth_params.m_depth_bias = m_light.m_shadow_bias * bias_scale;
			block_depth.m_depth_params.m_depth_normal_bias = m_light.m_shadow_normal_bias;
			block_depth.m_depth_params.m_depth_z_far = m_light.m_shadow_range;
			Renderer& renderer = block_depth.m_gfx_system.renderer(Shading::Volume);
			ManualRender::render(renderer);
		}

		Light& m_light;
	};

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

	void light_slice_cull(ShadowRender& shadow_render, LightBounds& light_bounds)
	{
		vec3 x = shadow_render.m_light.m_node.axis(X3);
		vec3 y = shadow_render.m_light.m_node.axis(Y3);
		vec3 z = shadow_render.m_light.m_node.axis(Z3);

		Plane6 light_frustum_planes =
		{
			{  x,  light_bounds.max.x },
			{ -x, -light_bounds.min.x },
			{  y,  light_bounds.max.y },
			{ -y, -light_bounds.min.y },
			{  z,  light_bounds.max.z + 1e6f },
			{ -z, -light_bounds.min.z }
		};

		shadow_render.cull(&light_frustum_planes);

		for(Item* item : shadow_render.m_shadow_render.m_shot->m_items)
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

		if(light.m_shadow_flags & CSM_Stabilize)
		{
			const float quantizer = 64.0f;
			scale = quantizer / ceil(quantizer / scale);
		}

		vec2 offset = 0.5f * (maxproj + minproj) * scale;

		if(light.m_shadow_flags == CSM_Stabilize)
		{
			const float half_size = texture_size * 0.5f;
			offset = ceil(offset * half_size) / half_size;
		}

		vec4 rect = { offset, scale };
		mat4 light_crop = rect_mat(rect);

		return light_proj * light_crop;
	}

	void BlockShadow::render_directional(Render& render, Light& light, size_t num_directional, size_t index)
	{
		LightShadow& shadow = m_shadows[index];

		shadow.m_frustum_slices.resize(light.m_shadow_num_splits);
		split_frustum_slices(render.m_camera, to_array(shadow.m_frustum_slices), light.m_shadow_num_splits, light.m_shadow_split_distribution);

		mat4 light_transform = bxlookat(-light.m_node.direction(), Zero3);
		mat4 light_proj = bxortho(1.0f, -1.0f, 1.0f, -1.0f, -light.m_shadow_range, light.m_shadow_range, 0.0f, bgfx::getCaps()->homogeneousDepth);

		shadow.m_slices.clear();

		for(FrustumSlice& slice : shadow.m_frustum_slices)
		{
			uvec4 viewport_rect = csm_rect(m_csm.m_size, num_directional, light, index, slice.m_index);
			ShadowRender shadow_render = { render, light, m_csm.m_fbo, viewport_rect };

			LightBounds light_bounds = light_slice_bounds(slice.m_frustum, light_transform);

			light_slice_cull(shadow_render, light_bounds);

			float texture_size = float(rect_w(shadow_render.m_viewport.m_rect));

			if(false)//light.m_shadow_flags == CSM_Stabilize)
			{
				light_slice_sphere_bounds(slice, light_transform, light_bounds, texture_size);
				stabilize_light_bounds(slice, light_bounds, texture_size);
			}

			shadow_render.m_camera.m_projection = crop_shrink_light_proj(light, light_bounds, light_proj, float(m_csm.m_size));
			shadow_render.m_camera.m_transform = light_transform;

			vec4 shadow_tex_rect = vec4(viewport_rect) / float(m_csm.m_size);

			mat4 crop_matrix = rect_mat(shadow_tex_rect) * bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, bgfx::getCaps()->homogeneousDepth);
			mat4 shadow_matrix = crop_matrix * shadow_render.m_camera.m_projection * shadow_render.m_camera.m_transform;

			LightShadow::Slice shadow_slice = { shadow_tex_rect, shadow_render.m_camera.m_projection, shadow_render.m_camera.m_transform, shadow_matrix, slice, light_bounds };
			shadow.m_slices.push_back(shadow_slice);

			float bias_scale = slice.m_index == 0 ? 1.f : slice.m_frustum.m_radius / shadow.m_frustum_slices[0].m_frustum.m_radius;

			shadow_render.render(m_block_depth, bias_scale);
		}
	}

	PassShadowmap::PassShadowmap(GfxSystem& gfx_system, BlockShadow& block_shadow)
		: RenderPass(gfx_system, {}, PassType::Shadowmap)
		, m_block_shadow(block_shadow)
	{}

	void PassShadowmap::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassShadowmap::submit_render_pass(Render& render)
	{
		size_t num_csm_shadow = 0;
		for(Light* light : render.m_shot->m_lights)
			if(light->m_shadows && light->m_type == LightType::Directional)
			{
				num_csm_shadow++;
			}

		size_t directional_shadow_index = 0;

		ShadowAtlas& atlas = m_block_shadow.m_atlas; // render.m_shadow_atlas

		m_block_shadow.m_shadows.clear();

		for(Light* light : render.m_shot->m_lights)
		{
			if(!light->m_shadows)
				continue;

			m_block_shadow.m_shadows.emplace_back();

			if(light->m_type == LightType::Directional)
			{
				m_block_shadow.render_directional(render, *light, num_csm_shadow, directional_shadow_index);
				directional_shadow_index++;
			}
			else if(light->m_type == LightType::Point)
			{
				uvec4 atlas_rect = atlas.render_update(render, *light);

				mat4 projection = bxproj(90.f, 1.f, 0.01f, light->m_range, bgfx::getCaps()->homogeneousDepth);

				for(int i = 0; i < 6; i++)
				{
					static const vec3 view_normals[6] = { -X3, X3, -Y3, Y3, -Z3, Z3 };
					static const vec3 view_up[6] = { -Y3, -Y3, -Z3, Z3, -Y3, -Y3 };

					mat4 transform = light->m_node.transform() * bxlookat(Zero3, view_normals[i], view_up[i]);
					
					ShadowCubemap& cubemap = atlas.light_cubemap(*light, uint16_t(rect_w(atlas_rect)));

					ShadowRender shadow_render = { render, *light, cubemap.m_fbos[i], { uvec2(0U), uvec2(uint(cubemap.m_size)) }, projection, transform };
					shadow_render.cull();
					shadow_render.render(m_block_shadow.m_block_depth, 1.f);
				}
			}
			else if(light->m_type == LightType::Spot)
			{
				uvec4 atlas_rect = atlas.render_update(render, *light);

				mat4 projection = bxproj(light->m_spot_angle * 2.f, 1.f, 0.01f, light->m_range, bgfx::getCaps()->homogeneousDepth);

				ShadowRender shadow_render = { render, *light, atlas.m_fbo, atlas_rect, projection, light->m_node.transform() };
				shadow_render.cull();
				shadow_render.render(m_block_shadow.m_block_depth, 1.f);
			}
		}
	}


	PassShadow::PassShadow(GfxSystem& gfx_system, BlockDepth& block_depth, BlockShadow& block_shadow)
		: PassDepth(gfx_system, block_depth)
		, m_block_depth(block_depth)
		, m_block_shadow(block_shadow)
	{}

	void PassShadow::next_draw_pass(Render& render, Pass& render_pass)
	{
		PassDepth::next_draw_pass(render, render_pass);
	}

	void PassShadow::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
			PassDepth::queue_draw_element(render, element);
	}

	void PassShadow::submit_draw_element(Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass); UNUSED(element);
	}

	BlockShadow::BlockShadow(GfxSystem& gfx_system, BlockDepth& block_depth)
		: DrawBlock(gfx_system, type<BlockShadow>())
		, m_block_depth(block_depth)
		, m_atlas(1024, { 2, 4, 8, 16 })
	{
		static cstring options[1] = { "CSM_SHADOW" };
		static cstring modes[2] = { "CSM_NUM_CASCADES", "CSM_PCF_LEVEL" };
		m_shader_block->m_options = { options, 1 };
		m_shader_block->m_modes = { modes, 2 };
	}

	CSMShadow::CSMShadow(uint16_t size)
		: m_size(size)
	{
		m_depth = bgfx::createTexture2D(size, size, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);
		m_fbo = bgfx::createFrameBuffer(1, &m_depth, true);
	}

	void BlockShadow::init_gfx_block()
	{
		u_directional_shadow.createUniforms();

		uint16_t csm_size = 4096;
		m_csm = { csm_size };
	}

	void BlockShadow::begin_gfx_block(Render& render)
	{
		UNUSED(render);
		//BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
		//copy.debug_show_texture(as<FrameBuffer>(*render.m_target), m_csm.m_depth, true);
	}

	void BlockShadow::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockShadow::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockShadow::submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element)
	{
		UNUSED(render); UNUSED(render_pass);

		Light* light = m_directional_light;
		bool directional = light && (element.m_item->m_layer_mask & light->m_layers) != 0;
		
		if(directional && light->m_shadows)
		{
			element.m_shader_version.set_option(m_index, CSM_SHADOW);
			//element.shader_version.set_option(m_index, CSM_BLEND, light->m_shadow_blend_splits);

			element.m_shader_version.set_mode(m_index, CSM_NUM_CASCADES, light->m_shadow_num_splits);
			element.m_shader_version.set_mode(m_index, CSM_PCF_LEVEL, 1);

			vec2 pcf_offset = { 1.f, 1.f };
			vec4 csm_params = { vec2(1.f / float(m_csm.m_size)), pcf_offset };
			bgfx::setUniform(u_directional_shadow.u_csm_params, &csm_params);

#if 0 //def MUD_PLATFORM_EMSCRIPTEN
			bgfx::setTexture(uint8_t(TextureSampler::ShadowCSM), u_directional_shadow.s_csm_atlas, m_csm.m_depth, GFX_TEXTURE_POINT);
#else
			//bgfx::setTexture(uint8_t(TextureSampler::ShadowCSM), u_directional_shadow.s_csm_atlas, m_csm.m_depth);
			bgfx::setTexture(uint8_t(TextureSampler::ShadowCSM), u_directional_shadow.s_csm_atlas, m_csm.m_depth, BGFX_TEXTURE_COMPARE_LESS);
#endif
		}

		if(0)//render.m_shadow_atlas)
		{
			bgfx::setTexture(uint8_t(TextureSampler::ShadowAtlas), u_shadow.s_shadow_atlas, m_atlas.m_depth, BGFX_TEXTURE_COMPARE_LESS);
			vec2 shadow_atlas_pixel_size = vec2(1.f) / float(m_atlas.m_size);
			bgfx::setUniform(u_shadow.u_shadow_pixel_size, &shadow_atlas_pixel_size[0]);
		}
	}
}

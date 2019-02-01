#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/pool.h>
#include <mud/gfx.pbr.h>
#include <mud/ecs.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/vector.hpp>
#endif

namespace stl
{
	using namespace mud;
	//template class MUD_MATH_EXPORT vector<>;
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	constexpr size_t BlockLight::ShotUniform::max_lights;
	constexpr size_t BlockLight::ShotUniform::max_shadows;
	constexpr size_t BlockLight::ShotUniform::max_forward_lights;
	constexpr size_t BlockLight::ShotUniform::max_direct_lights;

	BlockLight::BlockLight(GfxSystem& gfx_system, BlockShadow& block_shadow)
		: DrawBlock(gfx_system, type<BlockLight>())
		, m_block_shadow(block_shadow)
	{
		static cstring options[2] = { "FOG", "DIRECT_LIGHT" };
		m_shader_block->m_options = { options, 2 };

		static string max_lights = to_string(ShotUniform::max_lights);
		static string max_shadows = to_string(ShotUniform::max_shadows);
		static string max_dir_lights = to_string(ShotUniform::max_direct_lights);

		static ShaderDefine defines[3] = {
			{ "MAX_LIGHTS", max_lights.c_str()  },
			{ "MAX_SHADOWS", max_shadows.c_str() },
			{ "MAX_DIRECT_LIGHTS", max_dir_lights.c_str() }
		};
		m_shader_block->m_defines = { defines, 3 };
	}

	void BlockLight::init_block()
	{
		u_shot.createUniforms();
		u_scene.createUniforms();
		u_fog.createUniforms();
	}

	void BlockLight::begin_render(Render& render)
	{
		UNUSED(render);

		m_direct_lights.clear();
		for(Light* light : render.m_shot->m_lights)
		{
			if(light->m_type == LightType::Direct && m_direct_lights.size() < ShotUniform::max_direct_lights)
				m_direct_lights.push_back(light);
		}

		m_direct_light = m_direct_lights.empty() ? nullptr : m_direct_lights[m_direct_light_index];
		m_block_shadow.m_direct_light = m_direct_light;
	}

	void BlockLight::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockLight::begin_draw_pass(Render& render)
	{
		this->update_lights(render, render.m_camera.m_transform, to_array(render.m_shot->m_lights), to_array(m_block_shadow.m_shadows));

		m_direct_light_index = 0;

		m_direct_light = m_direct_lights.empty() ? nullptr : m_direct_lights[m_direct_light_index];
		m_block_shadow.m_direct_light = m_direct_light;

#ifdef MULTIPLE_DIRECT_LIGHTS
		if(!m_direct_lights.empty())
			m_direct_light = m_direct_lights[m_direct_light_index++];

		if(m_direct_light_index > 0)
			render_pass.m_bgfx_state |= BGFX_STATE_BLEND_ADD;

		request.num_passes = m_direct_lights.empty() ? 1 : m_direct_lights.size();
#endif
	}

	void BlockLight::options(Render& render, ShaderVersion& shader_version) const
	{
		if(render.m_camera.m_clustered)
			shader_version.set_option(0, CLUSTERED, true);

		if(render.m_environment && render.m_environment->m_fog.m_enabled)
			shader_version.set_option(m_index, FOG, true);

		bool cull = !m_direct_light || false; // !(element.m_item->m_layer_mask & m_direct_light->m_layers);

		if(!cull)
			shader_version.set_option(m_index, DIRECT_LIGHT, true);
	}

	void BlockLight::submit(Render& render, const Pass& render_pass) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(render.m_camera.m_clustered)
			render.m_camera.m_clusters->submit(encoder);

		this->upload_environment(render, render_pass, render.m_environment);
		this->upload_fog(render, render_pass, render.m_scene.m_environment.m_fog);
		this->upload_lights(render_pass);

		// set to not render if not first direct pass, depending on cull
	}

	void BlockLight::upload_environment(Render& render, const Pass& render_pass, Environment* environment) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		Colour clear_color = render.m_viewport.m_clear_colour;

		vec4 radiance_color_energy = { to_vec3(clear_color), 1.f };
		vec4 ambient_params = { 0.f, 0.f, 0.f, 0.f };

		if(environment)
		{
			radiance_color_energy = { to_vec3(environment->m_radiance.m_colour), environment->m_radiance.m_energy };
			ambient_params = { environment->m_radiance.m_ambient, 0.f, 0.f, 0.f };
		}

		encoder.setUniform(u_scene.u_radiance_color_energy, &radiance_color_energy);
		encoder.setUniform(u_scene.u_ambient_params, &ambient_params);
	}

	void BlockLight::upload_fog(Render& render, const Pass& render_pass, Fog& fog) const
	{
		UNUSED(render);

		if(!fog.m_enabled)
			return;

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		vec4 fog_params_0 = { fog.m_density, to_vec3(fog.m_colour) };
		vec4 fog_params_1 = { float(fog.m_depth), fog.m_depth_begin, fog.m_depth_curve, 0.f };
		vec4 fog_params_2 = { float(fog.m_height), fog.m_height_max, fog.m_height_max, fog.m_height_curve };
		vec4 fog_params_3 = { float(fog.m_transmit), fog.m_transmit_curve, 0.f, 0.f };
		
		encoder.setUniform(u_fog.u_fog_params_0, &fog_params_0);
		encoder.setUniform(u_fog.u_fog_params_1, &fog_params_1);
		encoder.setUniform(u_fog.u_fog_params_2, &fog_params_2);
		encoder.setUniform(u_fog.u_fog_params_3, &fog_params_3);
	}

	void BlockLight::update_lights(Render& render, const mat4& view, array<Light*> all_lights, array<LightShadow> shadows)
	{
		UNUSED(render);
		mat4 inverse_view = inverse(view);

		array<Light*> lights = { all_lights.m_pointer, min(all_lights.m_count, size_t(ShotUniform::max_lights)) };
		uint16_t light_count = 0;

		m_lights_data.light_counts = Zero4;

		for(Light* light : lights)
		{
			Colour energy = to_linear(light->m_colour) * light->m_energy;
			vec3 position = mulp(view, light->m_node.position());
			vec3 direction = muln(view, light->m_node.direction());
			Colour shadow_color = to_linear(light->m_shadow_colour);
			m_lights_data.shadow_color_enabled[light_count] = { to_vec3(shadow_color), light->m_shadows ? 1.f : 0.f };

			m_lights_data.position_range[light_count] = { position, light->m_range };
			m_lights_data.energy_specular[light_count] = { to_vec3(energy), light->m_specular };
			m_lights_data.direction_attenuation[light_count] = { direction, light->m_attenuation };
			m_lights_data.spot_params[light_count] = { light->m_spot_attenuation, cos(to_radians(light->m_spot_angle)), 0.f, 0.f };

			float& light_type_count = m_lights_data.light_counts[size_t(light->m_type)];
			m_lights_data.light_indices[size_t(light_type_count)][size_t(light->m_type)] = light_count;
			light_type_count++;

			if(light->m_shadows) //&& shadows[light_count])
			{
				if(light->m_type == LightType::Direct)
				{
					for(uint32_t i = 0; i < shadows[light_count].m_frustum_slices.size(); ++i)
					{
						m_lights_data.csm_splits[light_count][i] = shadows[light_count].m_frustum_slices[i].m_frustum.m_far;
						m_lights_data.csm_matrix[light_count][i] = shadows[light_count].m_slices[i].m_shadow_matrix * inverse_view;
					}
				}
				else if(light->m_type == LightType::Point)
				{
					m_lights_data.shadow_matrix[light_count] = inverse(view * light->m_node.m_transform);
				}
				else if(light->m_type == LightType::Spot)
				{
					m_lights_data.shadow_matrix[light_count] = shadows[light_count].m_slices[0].m_shadow_matrix * inverse_view;
				}
			}

			light_count++;
		}

		m_light_count = light_count;
	}

	void BlockLight::upload_lights(const Pass& render_pass) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		
		if(m_light_count > 0)
			u_shot.u_light_array.setUniforms(encoder, m_lights_data, uint16_t(m_direct_lights.size()), m_light_count);

		encoder.setUniform(u_shot.u_light_counts, &m_lights_data.light_counts);
		encoder.setUniform(u_shot.u_light_indices, m_lights_data.light_indices, m_light_count);
	}
}

#ifdef _DEBUG
namespace mud
{
	void debug_draw_light_clusters(Gnode& parent, Camera& camera)
	{
		if (!camera.m_clustered) return;
		Froxelizer& clusters = *camera.m_clusters;

		if (clusters.m_debug_clusters.empty())
			clusters.compute_froxels();

		enum Mode { ClusterIndex, RecordIndex, LightIndex, LightCount };
		Mode mode = ClusterIndex;

		mat4 transform = inverse(bxlookat(camera.m_eye, camera.m_target));
		uint32_t i = 0;
		for (Frustum& frustum : clusters.m_debug_clusters)
		{
			if (!clusters.count(i, 0) && !clusters.count(i, 1))
			{
				//gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour(1.f, 0.02f)));
				i++;
				continue;
			}

			Colour colour = Colour(1.f, 0.02f);
			uint32_t record = clusters.record(i);
			uint32_t light = clusters.light(record);

			if (mode == ClusterIndex)
				colour = hsl_to_rgb(float(i) / (29.f * 16.f * 16.f), 1.f, 0.5f);
			else if (mode == RecordIndex)
				colour = hsl_to_rgb(float(record) / float(255.f), 1.f, 0.5f);
			else if (mode == LightIndex)
				colour = hsl_to_rgb(float(light) / 255.f, 1.f, 0.5f);
			else if (mode == LightCount)
				colour = hsl_to_rgb(float(clusters.count(i)) / 32.f, 1.f, 0.5f);

			gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(colour));
			i++;
		}
	}

	void debug_draw_light_slices(Gnode& parent, Light& light, bool frustums, bool bounds)
	{
		uint32_t index = 0; UNUSED(light);// light.m_index];

		GfxSystem& gfx_system = parent.m_scene->m_gfx_system;
		BlockShadow& block_shadow = *gfx_system.m_pipeline->block<BlockShadow>();

		if (index >= block_shadow.m_shadows.size())
			return;

		LightShadow& shadow = block_shadow.m_shadows[index];

		auto draw = [](Gnode& parent, const Shape& shape, const Symbol& symbol)
		{
			Gnode& self = gfx::node(parent, {});
			gfx::draw(self, shape, symbol);
		};

		for (size_t i = 0; i < shadow.m_slices.size(); ++i)
		{
			mat4 inverse_light = inverse(shadow.m_slices[i].m_transform);
			draw(parent, Sphere(vec3(inverse_light[3]), 1.f), Symbol::wire(Colour::White));

			if (frustums)
			{
				Frustum& frustum = shadow.m_frustum_slices[i].m_frustum;
				draw(parent, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour::White));
				if (false)
					draw(parent, Sphere(frustum.m_center, frustum.m_radius), Symbol::wire(Colour::DarkGrey));

			}

			if (bounds)
			{
				Box light_bounds = Box(aabb(shadow.m_slices[i].m_light_bounds.min, shadow.m_slices[i].m_light_bounds.max));

				for (vec3& vertex : light_bounds.m_vertices)
					vertex = vec3(inverse_light * vec4(vertex, 1.f));

				draw(parent, light_bounds, Symbol::wire(Colour::Pink));
			}
		}
	}
}
#endif


#include <bgfx/bgfx.h>
#include <xatlas.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

//#define LIGHTMAP_HDR
#define LIGHTMAP_COMPRESS
//#define LIGHTMAP_FORCE_RENDER
//#define LIGHTMAP_PIXELS
//#define LIGHTMAP_SORT

namespace mud
{
	inline bool operator>(const uvec2& lhs, const uvec2& rhs) { return lhs.x > rhs.x || (lhs.x == rhs.x && lhs.y > rhs.y); }
}

namespace mud
{
#ifdef LIGHTMAP_HDR
	static const bgfx::TextureFormat::Enum c_lightmap_format = bgfx::TextureFormat::RGBA16F;
#ifdef LIGHTMAP_COMPRESS
	static const bgfx::TextureFormat::Enum c_lightmap_file_format = bgfx::TextureFormat::BC6H;
#else
	static const bgfx::TextureFormat::Enum c_lightmap_file_format = bgfx::TextureFormat::RGBA16F;
#endif
#else
	static const bgfx::TextureFormat::Enum c_lightmap_format = bgfx::TextureFormat::RGBA8;
#ifdef LIGHTMAP_COMPRESS
	static const bgfx::TextureFormat::Enum c_lightmap_file_format = bgfx::TextureFormat::BC3;
#else
	static const bgfx::TextureFormat::Enum c_lightmap_file_format = bgfx::TextureFormat::RGBA8;
#endif
#endif

	Lightmap::Lightmap(uint32_t size)
		: m_size(size)
		, m_atlas(uvec2(size))
	{
		printf("INFO: create lightmap\n");

		//m_items.reserve(1024);
		m_items.reserve(4096);
	}

	void save_lightmap(GfxSystem& gfx_system, Lightmap& lightmap, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path)
	{
		uint16_t size = uint16_t(lightmap.m_size);
		bgfx::TextureHandle blit_texture = bgfx::createTexture2D(size, size, false, 1, source_format, BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK);
		bgfx::blit(0, blit_texture, 0, 0, 0, 0, texture, 0, 0, 0, 0, size, size, 1);
		bgfx::frame();
		bgfx::frame();

		save_bgfx_texture(gfx_system.allocator(), gfx_system.file_writer(), path.c_str(), target_format, blit_texture, source_format, uint16_t(lightmap.m_size), uint16_t(lightmap.m_size));
	}

	void load_lightmap(GfxSystem& gfx_system, Lightmap& lightmap, const string& path)
	{
		lightmap.m_texture = load_bgfx_texture(gfx_system.allocator(), gfx_system.file_reader(), path.c_str());

		for(LightmapItem& item : lightmap.m_items)
			item.m_lightmap = lightmap.m_texture;
	}

	void Lightmap::add_item(size_t index, Item& item, bool valid, const vec4& uv_scale_offset)
	{
		bgfx::TextureHandle texture = valid ? m_texture : bgfx::TextureHandle(BGFX_INVALID_HANDLE);
		m_items.push_back({ index, texture, uv_scale_offset });
		item.m_lightmaps.push_back(&m_items.back());
	}

	LightmapAtlas::LightmapAtlas(uint32_t size, float density)
		: m_size(size)
		, m_density(density)
	{}

	LightmapAtlas::~LightmapAtlas()
	{}

	PassLightmap::PassLightmap(GfxSystem& gfx_system, BlockLightmap& block_lightmap)
		: DrawPass(gfx_system, "lightmap", PassType::Lightmap)
		, m_block_lightmap(block_lightmap)
	{}

	void PassLightmap::next_draw_pass(Render& render, Pass& render_pass)
	{
		bool conservative = (bgfx::getCaps()->supported & BGFX_CAPS_CONSERVATIVE_RASTER) != 0;
		if(!conservative)
			printf("WARNING: rendering lightmap without conservative raster support will produce visible seams\n");

		UNUSED(render); UNUSED(render_pass);
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_MSAA;
	}

	void PassLightmap::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled)
		{
			element.m_program = m_block_lightmap.m_lightmap;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			this->add_element(render, element);
		}
	}

	BlockLightmap::BlockLightmap(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: DrawBlock(gfx_system, type<BlockLightmap>())
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void BlockLightmap::init_block()
	{
		u_lightmap.createUniforms();

		m_lightmap = &m_gfx_system.programs().fetch("pbr/lightmap");
	}

	struct XAtlas
	{
		XAtlas();
		~XAtlas();

		bool add_mesh(Mesh& mesh, MeshPacker& geometry);
		uvec2 generate(uint32_t rect_size, float density);
		void repack_mesh_uvs(uint32_t index, Mesh& mesh, MeshPacker& geometry);

		xatlas::Atlas* m_atlas = nullptr;
	};

	XAtlas::XAtlas()
	{
		m_atlas = xatlas::Create();
	}

	XAtlas::~XAtlas()
	{
		xatlas::Destroy(m_atlas);
	}

	bool XAtlas::add_mesh(Mesh& mesh, MeshPacker& geometry)
	{
		xatlas::InputMesh xmesh = {};
		xmesh.vertexCount = (int)mesh.m_vertex_count;
		xmesh.vertexPositionData = geometry.m_positions.data();
		xmesh.vertexPositionStride = sizeof(float) * 3;

		if((mesh.m_vertex_format & VertexAttribute::Normal) != 0)
		{
			xmesh.vertexNormalData = geometry.m_normals.data();
			xmesh.vertexNormalStride = sizeof(float) * 3;
		}

		if((mesh.m_vertex_format & VertexAttribute::TexCoord0) != 0)
		{
			xmesh.vertexUvData = geometry.m_uv0s.data();
			xmesh.vertexUvStride = sizeof(float) * 2;
		}

		xmesh.indexCount = (int)mesh.m_index_count;
		xmesh.indexData = mesh.m_cached_indices.data();
		xmesh.indexFormat = mesh.m_index32 ? xatlas::IndexFormat::UInt32 : xatlas::IndexFormat::UInt16;

		auto on_warning = [](xatlas::AddMeshWarning::Enum warning, uint32_t face, uint32_t index0, uint32_t index1, void* userData)
		{
			if(warning == xatlas::AddMeshWarning::AlreadyAddedEdge)
			{
				MeshPacker& geometry = *(MeshPacker*)userData;
				vec3 pos0 = geometry.m_positions[index0];
				vec3 pos1 = geometry.m_positions[index1];
				printf("DEBUG: already added edge %i to %i from face %i from %f, %f, %f to %f, %f, %f\n", index0, index1, face, pos0.x, pos0.y, pos0.z, pos1.x, pos1.y, pos1.z);
			}
		};

		xatlas::AddMeshError::Enum error = xatlas::AddMesh(m_atlas, xmesh, on_warning, &geometry);

		if(error != xatlas::AddMeshError::Success)
		{
			printf("ERROR: xatlas - adding mesh '%s': %s\n", mesh.m_name.c_str(), xatlas::StringForEnum(error));
		}

		return error == xatlas::AddMeshError::Success;
	}

	uvec2 XAtlas::generate(uint32_t rect_size, float density)
	{
		xatlas::PackerOptions packerOptions;
		packerOptions.method = xatlas::PackMethod::TexelArea;
		packerOptions.texelArea = density;
		packerOptions.resolution = rect_size;
		packerOptions.conservative = true;
		packerOptions.quality = 1;
		packerOptions.padding = 1;

		xatlas::Generate(m_atlas, xatlas::CharterOptions(), packerOptions);

		return { xatlas::GetWidth(m_atlas), xatlas::GetHeight(m_atlas) };
	}

	void XAtlas::repack_mesh_uvs(uint32_t index, Mesh& mesh, MeshPacker& geometry)
	{
		const xatlas::OutputMesh* xmesh = xatlas::GetOutputMeshes(m_atlas)[index];

		MeshPacker result;

		assert(xmesh->vertexCount >= mesh.m_vertex_count);
		for(size_t i = 0; i < xmesh->vertexCount; i++)
		{
			const xatlas::OutputVertex& vertex = xmesh->vertexArray[i];
			vec2 uv = { vertex.uv[0], vertex.uv[1] };

			result.m_positions.push_back(geometry.m_positions[vertex.xref]);
			if(geometry.m_colours.size() > 0)
				result.m_colours.push_back(geometry.m_colours[vertex.xref]);
			if(geometry.m_normals.size() > 0)
				result.m_normals.push_back(geometry.m_normals[vertex.xref]);
			if(geometry.m_tangents.size() > 0)
				result.m_tangents.push_back(geometry.m_tangents[vertex.xref]);
			if(geometry.m_uv0s.size() > 0)
				result.m_uv0s.push_back(geometry.m_uv0s[vertex.xref]);

			result.m_uv1s.push_back(uv);
		}

		for(size_t i = 0; i < xmesh->indexCount; i++)
		{
			result.m_indices.push_back(xmesh->indexArray[i]);
		}

		mesh.write(PLAIN, result, false);
	}

	struct ModelUnwrap
	{
		vector<bool> success;
		uvec2 size;
	};

	void unwrap_model(Model& model, ModelUnwrap& unwrap, uint32_t rect_size, float density)
	{
		unwrap.success = vector<bool>(model.m_items.size(), false);
		unwrap.size = uvec2(0U);

		bool is_unwrapped = false;
		for(size_t i = 0; i < model.m_items.size(); ++i)
		{
			Mesh& mesh = *model.m_items[i].m_mesh;
			if((mesh.m_vertex_format & VertexAttribute::TexCoord1) != 0
			|| (mesh.m_vertex_format & VertexAttribute::QTexCoord1) != 0)
			{
				unwrap.success[i] = true;
				is_unwrapped = true;
				unwrap.size = max(uvec2(mesh.m_uv1_rect.max), unwrap.size);
				// @todo this gives a different size than original packing because of margins, which means we can't reuse lightmaps baked from original model before repack
			}
		}

		if(is_unwrapped)
			return;

		printf("INFO: unwrapping model %s for lightmap\n", model.m_name.c_str());

		XAtlas atlas;

		vector<MeshPacker> geometry(model.m_items.size());
		for(size_t i = 0; i < model.m_items.size(); ++i)
		{
			Mesh& mesh = *model.m_items[i].m_mesh;
			mesh.read(geometry[i], model.m_items[i].m_transform);

			bool skip = false;
			skip |= mesh.m_draw_mode != PLAIN;
			skip |= !mesh.m_cache.m_vertex_format;

			bool success = skip ? false : atlas.add_mesh(mesh, geometry[i]);
			unwrap.success[i] = success;
		}

		unwrap.size = atlas.generate(rect_size, density);

		if(unwrap.size.x == 0 || unwrap.size.y == 0)
		{
			printf("WARNING: model %s unwrapped to zero size rect\n", model.m_name.c_str());
			return;
		}

		uint32_t mesh_index = 0;
		for(size_t i = 0; i < model.m_items.size(); ++i)
		{
			if(!unwrap.success[i]) continue;
			Mesh& mesh = *model.m_items[i].m_mesh;
			atlas.repack_mesh_uvs(mesh_index++, mesh, geometry[i]);
		}
	}

	struct LightmapUnwrap
	{
		LightmapUnwrap(string cached_path, uint32_t rect_size, float density)
			: m_cached_path(cached_path)
			, m_rect_size(rect_size)
			, m_density(density)
		{}

		ModelUnwrap& unwrap(Model& model)
		{
			if(unwraps.find(&model) == unwraps.end())
			{
				ModelUnwrap& unwrap = unwraps[&model];
				unwrap_model(model, unwrap, m_rect_size, m_density);
			}
			return unwraps[&model];
		}

		string m_cached_path;
		uint32_t m_rect_size;
		float m_density;
		map<Model*, ModelUnwrap> unwraps;
	};

	void BlockLightmap::bake_geometry(array<Item*> items, LightmapAtlas& lightmaps)
	{
		struct PackResult { Image* image; Lightmap* lightmap; };

		auto pack_texture = [&](cstring name, uvec2 size) -> PackResult
		{
			for(auto& lightmap : lightmaps.m_layers)
			{
				Image* image = lightmap->m_atlas.add_texture(name, size);
				if(image)
					return { image, lightmap.get() };
			}
			return { nullptr, nullptr };
		};

		LightmapUnwrap atlas = { lightmaps.m_save_path, lightmaps.m_size, lightmaps.m_density };
		
		vector<size_t> sorted;
		for(size_t i = 0; i < items.size(); ++i)
			sorted.push_back(i);

#ifdef LIGHTMAP_SORT
		auto compare = [&](size_t& a, size_t& b) { return atlas.unwrap(*items[a]->m_model).size.y > atlas.unwrap(*items[b]->m_model).size.y; };
		std::sort(sorted.begin(), sorted.end(), compare);
#endif

		for(size_t i : sorted)
		{
			Model& model = *items[i]->m_model;
			ModelUnwrap& unwrap = atlas.unwrap(model);

			if(unwrap.size == uvec2(0U))
				continue;

			auto pack = pack_texture(model.m_name.c_str(), unwrap.size);
			if(!pack.image)
			{
				lightmaps.add_lightmap();
				pack = pack_texture(model.m_name.c_str(), unwrap.size);
			}

			//printf("packing model %s rect size %i, %i at %i, %i\n", model.m_name.c_str(), unwrap.size.x, unwrap.size.y, pack.image->d_coord.x, pack.image->d_coord.y);

			uvec4 rect = { pack.image->d_coord, unwrap.size };

			Lightmap& lightmap = *pack.lightmap;
			for(ModelItem& model_item : model.m_items)
			{
				if(!unwrap.success[model_item.m_index])
				{
					lightmap.add_item(i, *items[i], false, vec4(0.f));
					continue;
				}

				vec2 scale = vec2(1.f / float(lightmaps.m_size));
				vec2 offset = rect_offset(vec4(rect)) / float(lightmaps.m_size);
				lightmap.add_item(i, *items[i], true, vec4(scale, offset));
			}
		}
	}

	void BlockLightmap::bake_lightmaps(Scene& scene, LightmapAtlas& atlas, const mat4& transform, const vec3& extents)
	{
		printf("INFO: bake lightmaps\n");

		vector<Item*> items;
		//Plane6 planes = frustum_planes(transform, vec2(extents.x, extents.y), -extents.z / 2.f, -extents.z / 2.f);
		//scene.cull_items(planes, items);
		scene.m_pool->pool<Item>().iterate([&](Item& item)
		{
			if((item.m_flags & ItemFlag::Render) != 0
			&& (item.m_flags & ItemFlag::Static) != 0)
				items.push_back(&item);
		});

		this->bake_geometry(items, atlas);

		vector<GIProbe*> gi_probes;
		gather_gi_probes(scene, gi_probes);

		Renderer& renderer = m_gfx_system.renderer(Shading::Lightmap);

		size_t i = 0;
		for(auto& lightmap : atlas.m_layers)
		{
#ifdef LIGHTMAP_COMPRESS
			string cached_path = atlas.m_save_path + "lightmap_" + to_string(i++) + ".dds";
#else
#ifdef LIGHTMAP_HDR
			string cached_path = atlas.m_save_path + "lightmap_" + to_string(i++) + ".hdr";
#else
			string cached_path = atlas.m_save_path + "lightmap_" + to_string(i++) + ".png";
#endif
#endif

#ifndef LIGHTMAP_FORCE_RENDER
			if(file_exists(cached_path.c_str()))
			{
				load_lightmap(m_gfx_system, *lightmap, cached_path);
				continue;
			}
#endif

			uint16_t resolution = uint16_t(atlas.m_size);
			bgfx::FrameBufferHandle fbo = bgfx::createFrameBuffer(resolution, resolution, c_lightmap_format, BGFX_TEXTURE_RT);

			RenderFrame frame = m_gfx_system.render_frame();

			Camera camera = { transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
			Viewport viewport = { camera, scene, { uvec2(0U), uvec2(lightmap->m_size) } };
			Render lightmap_render = { Shading::Lightmap, viewport, fbo, frame };
			viewport.m_clear_colour = Colour::None;

			for(LightmapItem& item : lightmap->m_items)
				lightmap_render.m_shot->m_items.push_back(items[item.m_item]);

			lightmap_render.m_shot->m_gi_probes = gi_probes;
			renderer.render(lightmap_render);

			bgfx::frame();

			save_lightmap(m_gfx_system, *lightmap, bgfx::getTexture(fbo), c_lightmap_format, c_lightmap_file_format, cached_path);
			load_lightmap(m_gfx_system, *lightmap, cached_path);

			bgfx::destroy(fbo);
		}

		printf("INFO: bake lightmaps done\n");
	}

	void BlockLightmap::begin_frame(const RenderFrame& frame)
	{
		UNUSED(frame);
		for(const BakeEntry& bake_entry : m_bake_queue)
		{
			LightmapAtlas& atlas = *bake_entry.atlas;
			this->bake_lightmaps(*bake_entry.scene, atlas, atlas.m_capture_transform, atlas.m_capture_extents);
			bake_entry.atlas->m_dirty = false;
		}
		m_bake_queue.clear();
	}

	void BlockLightmap::begin_render(Render& render)
	{
		if(render.m_shading == Shading::Lightmap)
			return;

		UNUSED(render);
		for(LightmapAtlas* atlas : render.m_shot->m_lightmaps)
			if(atlas->m_dirty)
			{
				m_bake_queue.push_back({ &render.m_scene, atlas });
			}
	}

	void BlockLightmap::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockLightmap::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockLightmap::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockLightmap::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);
	}

	void BlockLightmap::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render);

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(element.m_item->m_lightmaps.size() > 0)
		{
			LightmapItem& binding = *element.m_item->m_lightmaps[element.m_model->m_index];

			//encoder.setUniform(Material::s_base_uniform.u_uv1_scale_offset, &binding.m_uv_scale_offset);

			if(bgfx::isValid(binding.m_lightmap))
#ifdef LIGHTMAP_PIXELS
				encoder.setTexture(uint8_t(TextureSampler::Lightmap), u_lightmap.s_lightmap, binding.m_lightmap, GFX_TEXTURE_POINT);
#else
				encoder.setTexture(uint8_t(TextureSampler::Lightmap), u_lightmap.s_lightmap, binding.m_lightmap);
#endif
		}
		else
		{
			vec4 uv_scale_offset = vec4(0.f);
			//encoder.setUniform(Material::s_base_uniform.u_uv1_scale_offset, &uv_scale_offset);
		}
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

#define DEBUG_ITEMS 0
#define DEPTH_PASS 1
#define DEBUG_GBUFFERS 0

namespace mud
{
#define MUD_GFX_STATE_DEFAULT 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL \
								| BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA

#define MUD_GFX_STATE_DEFAULT_ALPHA 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS \
									  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA

	void gather_gi_probes(Scene& scene, vector<GIProbe*>& gi_probes)
	{
		//gi_probes.reserve(m_pool->pool<GIProbe>().size());
		scene.m_pool->pool<GIProbe>().iterate([&](GIProbe& gi_probe)
		{
			gi_probes.push_back(&gi_probe);
		});
	}

	void gather_lightmaps(Scene& scene, vector<LightmapAtlas*>& atlases)
	{
		//atlases.reserve(m_pool->pool<LightmapAtlas>().size());
		scene.m_pool->pool<LightmapAtlas>().iterate([&](LightmapAtlas& atlas)
		{
			atlases.push_back(&atlas);
		});
	}

	void gather_reflection_probes(Scene& scene, vector<ReflectionProbe*>& reflection_probes)
	{
		scene.m_pool->pool<ReflectionProbe>().iterate([&](ReflectionProbe& probe)
		{
			if(probe.m_visible)
			{
				reflection_probes.push_back(&probe);
				probe.m_dirty = true; // force dirty for now
			}
		});
	}

	void gather_render_pbr(Scene& scene, Render& render)
	{
		gather_items(scene, render.m_camera, render.m_shot->m_items);
		gather_occluders(scene, render.m_camera, render.m_shot->m_occluders);
		gather_lights(scene, render.m_shot->m_lights);
		gather_gi_probes(scene, render.m_shot->m_gi_probes);
		gather_lightmaps(scene, render.m_shot->m_lightmaps);
		gather_reflection_probes(scene, render.m_shot->m_reflection_probes);

		render.m_frustum = make_unique<Frustum>(optimized_frustum(render.m_camera, to_array(render.m_shot->m_items)));

		render.m_environment = &scene.m_environment;
		render.m_shot->m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}

	void pipeline_pbr(GfxSystem& gfx_system, Pipeline& pipeline, bool deferred)
	{
		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx_system);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx_system, filter);
		BlockBlur& blur = pipeline.add_block<BlockBlur>(gfx_system, filter);

		// pipeline 
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx_system);
		BlockGeometry& geometry = pipeline.add_block<BlockGeometry>(gfx_system);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx_system, filter);
		BlockRadiance& radiance = pipeline.add_block<BlockRadiance>(gfx_system, filter, copy);
		BlockShadow& shadow = pipeline.add_block<BlockShadow>(gfx_system, depth);
		BlockLight& light = pipeline.add_block<BlockLight>(gfx_system, shadow);
		BlockReflection& reflection = pipeline.add_block<BlockReflection>(gfx_system);
		BlockGITrace& gi_trace = pipeline.add_block<BlockGITrace>(gfx_system);
		BlockGIBake& gi_bake = pipeline.add_block<BlockGIBake>(gfx_system, light, gi_trace);
		BlockLightmap& lightmap = pipeline.add_block<BlockLightmap>(gfx_system, light, gi_bake);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx_system);
		UNUSED(geometry);
		UNUSED(particles);

		// mrt
		//BlockSSAO& ssao = pipeline.add_block<BlockSSAO>(gfx_system, filter, blur);
		//BlockSSR& ssr = pipeline.add_block<BlockSSR>(gfx_system);
		//BlockSSS& sss = pipeline.add_block<BlockSSS>(gfx_system);
		BlockResolve& resolve = pipeline.add_block<BlockResolve>(gfx_system, copy);

		// effects
		BlockDofBlur& dof_blur = pipeline.add_block<BlockDofBlur>(gfx_system, filter);
		//BlockExposure& exposure = pipeline.add_block<BlockExposure>(gfx_system);
		BlockGlow& glow = pipeline.add_block<BlockGlow>(gfx_system, filter, copy, blur);
		BlockTonemap& tonemap = pipeline.add_block<BlockTonemap>(gfx_system, filter, copy);

		vector<GfxBlock*> depth_blocks = { &depth };
		vector<GfxBlock*> geometry_blocks = {};
		vector<GfxBlock*> shading_blocks = { &radiance, &light, &shadow, &gi_trace, &reflection, &lightmap };
		vector<GfxBlock*> gi_blocks = { &light, &shadow, &gi_bake };
		vector<GfxBlock*> lightmap_blocks = { &light, &shadow, &gi_trace, &lightmap };

		pipeline.m_pass_blocks[size_t(PassType::Unshaded)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Background)] = { &sky };
		pipeline.m_pass_blocks[size_t(PassType::Effects)] = { /*&ssao, &ssr, &sss,*/ &resolve };
		pipeline.m_pass_blocks[size_t(PassType::PostProcess)] = { &dof_blur/*, &exposure*/, &glow, &tonemap };

		pipeline.m_pass_blocks[size_t(PassType::VoxelGI)] = gi_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Lightmap)] = lightmap_blocks;

		// forward
		pipeline.m_pass_blocks[size_t(PassType::Depth)] = depth_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Opaque)] = shading_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Alpha)] = shading_blocks;

		// deferred
		pipeline.m_pass_blocks[size_t(PassType::Geometry)] = geometry_blocks;
		pipeline.m_pass_blocks[size_t(PassType::Lights)] = shading_blocks;

		{
			Program& program_unshaded = gfx_system.programs().create("unshaded");
			program_unshaded.register_blocks(depth_blocks);

			Program& program_depth = gfx_system.programs().create("depth");
			program_depth.register_blocks(depth_blocks);
			
			Program& program_pbr = gfx_system.programs().create("pbr/pbr");
			program_pbr.register_blocks(shading_blocks);

			Program& program_geometry = gfx_system.programs().create("pbr/geometry");
			program_geometry.register_blocks(geometry_blocks);

			Program& program_lights = gfx_system.programs().create("pbr/lights");
			program_lights.register_blocks(shading_blocks);

			Program& program_fresnel = gfx_system.programs().create("fresnel");
			UNUSED(program_fresnel);

			Program& program_gi_voxelize = gfx_system.programs().create("gi/voxelize");
			program_gi_voxelize.register_blocks(gi_blocks);

			Program& program_gi_voxel_light = gfx_system.programs().create("gi/direct_light");
			program_gi_voxel_light.m_compute = true;
			program_gi_voxel_light.register_blocks(gi_blocks);

			Program& program_gi_voxel_bounce = gfx_system.programs().create("gi/bounce_light");
			program_gi_voxel_bounce.m_compute = true;
			program_gi_voxel_bounce.register_blocks(gi_blocks);

			Program& program_gi_voxel_output = gfx_system.programs().create("gi/output_light");
			program_gi_voxel_output.m_compute = true;
			program_gi_voxel_output.register_blocks(gi_blocks);

			Program& program_lightmap = gfx_system.programs().create("pbr/lightmap");
			program_lightmap.register_blocks(lightmap_blocks);
		}

		static ForwardRenderer forward_renderer = { gfx_system, pipeline };
		static DeferredRenderer deferred_renderer = { gfx_system, pipeline };
		static ShadowRenderer shadow_renderer = { gfx_system, pipeline };
		static VoxelRenderer voxel_renderer = { gfx_system, pipeline };
		static LightmapRenderer lightmap_renderer = { gfx_system, pipeline };

		if(deferred)
			gfx_system.set_renderer(Shading::Shaded, deferred_renderer);
		else
			gfx_system.set_renderer(Shading::Shaded, forward_renderer);

		gfx_system.set_renderer(Shading::Volume, shadow_renderer);

		gfx_system.set_renderer(Shading::Voxels, voxel_renderer);

		gfx_system.set_renderer(Shading::Lightmap, lightmap_renderer);

		pipeline.m_gather_func = gather_render_pbr;

		g_viewer_ecs->init<Tonemap, BCS, Glow, DofBlur>();
	}

	ForwardRenderer::ForwardRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Shaded)
	{
		this->add_pass<PassGIProbes>(gfx_system, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
#if DEPTH_PASS
		this->add_pass<PassDepth>(gfx_system, *pipeline.block<BlockDepth>());
#endif
		this->add_pass<PassOpaque>(gfx_system);
		this->add_pass<PassBackground>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		this->add_pass<PassAlpha>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassEffects>(gfx_system);
		this->add_pass<PassPostProcess>(gfx_system, *pipeline.block<BlockCopy>());
		//this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	DeferredRenderer::DeferredRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Shaded)
	{
		this->add_pass<PassGIProbes>(gfx_system, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassGeometry>(gfx_system, *pipeline.block<BlockGeometry>());
		this->add_pass<PassLights>(gfx_system, *pipeline.block<BlockFilter>());
		this->add_pass<PassBackground>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		//this->add_pass<PassAlpha>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassEffects>(gfx_system);
		this->add_pass<PassPostProcess>(gfx_system, *pipeline.block<BlockCopy>());
		//this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	ShadowRenderer::ShadowRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Volume)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassShadow>(gfx_system, *pipeline.block<BlockDepth>(), *pipeline.block<BlockShadow>());
		this->init();
	}

	VoxelRenderer::VoxelRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Voxels)
	{
		this->add_pass<PassShadowmap>(gfx_system, *pipeline.block<BlockShadow>());
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassGIBake>(gfx_system, *pipeline.block<BlockLight>(), *pipeline.block<BlockGIBake>());
		this->init();
	}

	LightmapRenderer::LightmapRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Lightmap)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassLightmap>(gfx_system, *pipeline.block<BlockLightmap>());
		this->init();
	}

	ReflectionRenderer::ReflectionRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline, Shading::Volume)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassOpaque>(gfx_system);
		this->add_pass<PassBackground>(gfx_system);
		this->add_pass<PassParticles>(gfx_system);
		this->add_pass<PassAlpha>(gfx_system);
		this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	PassOpaque::PassOpaque(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "opaque", PassType::Opaque)
	{}

	void PassOpaque::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

#ifdef DEPTH_PASS
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_EQUAL
								     | BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;
#else
		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
#endif
	}

	void PassOpaque::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, MRT, render.m_is_mrt);

			this->add_element(render, element);
		}
	}

	PassAlpha::PassAlpha(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "alpha", PassType::Alpha)
	{}

	void PassAlpha::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);

		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT_ALPHA;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthDescending);
	}

	void PassAlpha::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled && element.m_material->m_base_block.m_is_alpha)
		{
			blend_state(element.m_material->m_base_block.m_blend_mode, element.m_bgfx_state);

			this->add_element(render, element);
		}
	}

	PassGeometry::PassGeometry(GfxSystem& gfx_system, BlockGeometry& block_geometry)
		: DrawPass(gfx_system, "geometry", PassType::Geometry)
		, m_block_geometry(block_geometry)
	{}

	void PassGeometry::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
		render_pass.m_fbo = render.m_target->m_gbuffer.m_fbo;
	}

	void PassGeometry::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_shader_version.set_option(0, DEFERRED, true);

			this->add_element(render, element);
		}
	}

	PassLights::PassLights(GfxSystem& gfx_system, BlockFilter& filter)
		: RenderPass(gfx_system, "lights", PassType::Lights)
		, m_filter(filter)
		, m_program(&gfx_system.programs().fetch("pbr/lights"))
	{
		//m_program.register_block(*this);
	}

	void PassLights::submit_render_pass(Render& render)
	{
		Pass render_pass = render.next_pass(m_name);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		render_pass.m_encoder = &encoder;

		DrawCluster cluster;
		cluster.m_lights = render.m_shot->m_lights;
		cluster.m_shader_version = { m_program };

		for(GfxBlock* block : m_gfx_blocks)
			if(block->m_draw_block)
			{
				as<DrawBlock>(*block).begin_draw_pass(render);
				as<DrawBlock>(*block).options(render, cluster.m_shader_version);
				as<DrawBlock>(*block).submit(render, render_pass);
			}

		cluster.m_shader_version.set_option(0, MRT, render.m_is_mrt);

		encoder.setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_gbuffer.m_position);
		encoder.setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_gbuffer.m_normal);
		encoder.setTexture(uint8_t(TextureSampler::Source2), m_filter.u_uniform.s_source_2, render.m_target->m_gbuffer.m_albedo);
		encoder.setTexture(uint8_t(TextureSampler::Source3), m_filter.u_uniform.s_source_3, render.m_target->m_gbuffer.m_surface);

		m_filter.submit_quad(*render.m_target, render_pass.m_index, render.m_target_fbo,
							 m_program->version(cluster.m_shader_version), render.m_viewport.m_rect, BGFX_STATE_BLEND_ALPHA);

#if DEBUG_GBUFFERS
		if(render.m_target)
		{
			BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
			vec2 size = vec2(render.m_target->m_size) * 0.25f;
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_depth,    vec4(vec2(0.f, size.y * 0.f), size), true);
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_normal,   vec4(vec2(0.f, size.y * 1.f), size));
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_albedo,   vec4(vec2(0.f, size.y * 2.f), size));
			copy.debug_show_texture(render, render.m_target->m_gbuffer.m_surface,  vec4(vec2(0.f, size.y * 3.f), size));
		}
#endif
	}

	BlockGeometry::BlockGeometry(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGeometry>())
	{}

	BlockGeometry::~BlockGeometry()
	{}

	void BlockGeometry::init_block()
	{
		m_material = &m_gfx_system.fetch_material("geometry", "pbr/geometry");
		m_material_twosided = &m_gfx_system.fetch_material("geometry_twosided", "pbr/geometry");
		m_material_twosided->m_base_block.m_cull_mode = CullMode::None;
	}

	void BlockGeometry::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockGeometry::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

#include <cstdio>

namespace mud
{
	BlockRadiance::BlockRadiance(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy)
		: DrawBlock(gfx_system, type<BlockRadiance>())
		, m_filter(filter)
		, m_copy(copy)
		, m_prefilter_program(gfx_system.programs().create("filter/prefilter_envmap"))
	{
		static cstring options[2] = { "RADIANCE_ENVMAP", "RADIANCE_ARRAY" };
		m_shader_block->m_options = { options, 2 };
	}

	void BlockRadiance::init_block()
	{
		u_prefilter.createUniforms();
		u_radiance.createUniforms();
	}
	
	void BlockRadiance::begin_frame(const RenderFrame& frame)
	{
		UNUSED(frame);
		for(Radiance* radiance : m_prefilter_queue)
			this->prefilter_radiance(*radiance);
		m_prefilter_queue.clear();
	}

	void BlockRadiance::begin_render(Render& render)
	{
		if(!render.m_environment || !render.m_environment->m_radiance.m_texture)
			return;

		if(!render.m_environment->m_radiance.m_preprocessed)
			m_prefilter_queue.push_back(&render.m_environment->m_radiance);

#ifdef DEBUG_RADIANCE
		if(bgfx::isValid(render.m_environment->m_radiance.m_roughness_array))
		{
			BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
			copy.debug_show_texture(render, render.m_environment->m_radiance.m_roughness_array, vec4(0.f), false, false, false, 2);
		}
#endif
	}

	void BlockRadiance::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockRadiance::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockRadiance::options(Render& render, ShaderVersion& shader_version) const
	{
		bgfx::TextureHandle radiance = render.m_environment->m_radiance.m_roughness_array;

		if(bgfx::isValid(radiance))
			shader_version.set_option(m_index, RADIANCE_ENVMAP);
	}

	void BlockRadiance::submit(Render& render, const Pass& render_pass) const
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		bgfx::TextureHandle radiance = render.m_environment->m_radiance.m_roughness_array;

		if(bgfx::isValid(radiance))
			encoder.setTexture(uint8_t(TextureSampler::Radiance), u_radiance.s_radiance_map, radiance);
	}

	void BlockRadiance::prefilter_radiance(Radiance& radiance)
	{
		if(m_prefiltered.find(radiance.m_texture->m_texture.idx) != m_prefiltered.end())
		{
			radiance.m_roughness_array = { m_prefiltered[radiance.m_texture->m_texture.idx] };
			radiance.m_preprocessed = true;
			return;
		}

		if(!bgfx::isValid(radiance.m_texture->m_texture))
			return;

		constexpr int roughness_levels = 8;

#define MUD_RADIANCE_MIPMAPS

		if(bgfx::isValid(radiance.m_roughness_array))
			bgfx::destroy(radiance.m_roughness_array);

		RenderTarget& target = *m_gfx_system.context().m_target;
		uint16_t width = uint16_t(target.m_size.x); //radiance.m_texture->m_width;
		uint16_t height = uint16_t(target.m_size.y); //radiance.m_texture->m_height;

#ifdef MUD_RADIANCE_MIPMAPS
		uint16_t texture_layers = 1;
		bool mips = true;
#else
		uint16_t texture_layers = roughness_levels;
		bool mips = false;
#endif

		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA16F;
		if(!bgfx::isTextureValid(1, mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP))
			format = bgfx::TextureFormat::RGB10A2;

		if(!bgfx::isTextureValid(1, mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP))
		{
			printf("WARNING: could not prefilter env map roughness levels\n");
			return;
		}

		bool blit_support = false; // (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0;

		if(blit_support)
			radiance.m_roughness_array = bgfx::createTexture2D(width, height, mips, texture_layers, format, BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP);
		else
			radiance.m_roughness_array = bgfx::createTexture2D(width, height, mips, texture_layers, format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP);

		bgfx::TextureHandle radiance_array = radiance.m_roughness_array;

		uint8_t view_id = Render::s_preprocess_pass_id; //render.preprocess_pass();

		auto blit_to_array = [&](bgfx::TextureHandle texture, uvec2 size, int level)
		{
			if(blit_support)
			{
				bgfx::blit(view_id + 1, radiance_array, 0, 0, 0, uint16_t(level), texture, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), 1);
				bgfx::frame();
			}
			else
			{
				bgfx::Attachment attachment = { radiance_array, uint16_t(mips ? level : 0), uint16_t(mips ? 0 : level), BGFX_RESOLVE_NONE };
				FrameBuffer render_target = { size, bgfx::createFrameBuffer(1, &attachment, false) };
				m_copy.submit_quad(render_target, view_id + 1, texture);
				bgfx::frame();
			}
		};

		blit_to_array(radiance.m_texture->m_texture, { width, height }, 0);

		for(uint16_t i = 1; i < roughness_levels; i++)
		{
			uvec2 size = mips ? uvec2(width >> i, height >> i) : uvec2(width, height);
			FrameBuffer copy_target = { size, format, GFX_TEXTURE_POINT };

			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, radiance_array, GFX_TEXTURE_POINT);

			int source_level = i - 1;
			bgfx::setUniform(m_filter.u_uniform.u_source_0_level, &source_level);

			float roughness = i / float(roughness_levels - 1);
#ifdef MUD_PLATFORM_EMSCRIPTEN
			float num_samples = 64;
#else
			float num_samples = 512;
#endif
			vec4 prefilter_params = { roughness, float(num_samples), 0.f, 0.f };
			bgfx::setUniform(u_prefilter.u_prefilter_envmap_params, &prefilter_params);

			bgfx::ProgramHandle program = m_prefilter_program.default_version();
			m_filter.submit_quad(copy_target, view_id, program, 0U, true);

			blit_to_array(bgfx::getTexture(copy_target.m_fbo), size, i);
		}

		m_prefiltered[radiance.m_texture->m_texture.idx] = radiance.m_roughness_array.idx;
		radiance.m_preprocessed = true;
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	constexpr size_t BlockReflection::ReflectionUniform::max_reflection_probes;

	ReflectionProbe::ReflectionProbe(Node3& node)
		: m_node(node)
	{}

	ReflectionCubemap::ReflectionCubemap(uint16_t size)
		: m_size(size)
	{
		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;
		if(!bgfx::isTextureValid(0, true, 1, color_format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT))
			color_format = bgfx::TextureFormat::RGB10A2;

		m_cubemap = bgfx::createTextureCube(size, false, 1, color_format, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT);
		m_depth = bgfx::createTexture2D(size, size, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachments[2] =
			{
				{ m_depth , 0, 1, BGFX_RESOLVE_AUTO_GEN_MIPS },
				{ m_cubemap, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS }
			};
			m_fbo[i] = bgfx::createFrameBuffer(2, attachments, true);
		}
	}

	BlockReflection::BlockReflection(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockReflection>())
		, m_atlas(1024, 16)
	{}

	void BlockReflection::init_block()
	{
		int max_cubemap_size = 512;
		int cube_size = max_cubemap_size;

		while(cube_size >= 32)
		{
			//m_cubemaps.push_back(cube_size);
			cube_size >>= 1;
		}
	}

	void BlockReflection::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockReflection::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockReflection::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockReflection::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockReflection::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		if(bgfx::isValid(m_atlas.m_color_tex) && m_atlas.m_size > 0)
			encoder.setTexture(uint8_t(TextureSampler::ReflectionProbe), u_uniform.s_atlas, m_atlas.m_color_tex);

		//upload_reflection_probes(render, to_array(render.m_shot->m_reflection_probes));
	}

	void BlockReflection::upload_reflection_probes(Render& render, Pass& render_pass, array<ReflectionProbe*> probes)
	{
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		mat4 view_matrix = inverse(render.m_camera.m_transform);

		ReflectionProbeArray<16> probe_array;

		uint16_t probe_count = 0;

		for(ReflectionProbe* probe : probes)
		{
			//probe->m_last_pass = render.m_pass_index;

			probe_array.extents_intensity[probe_count] = { probe->m_extents, probe->m_intensity };

			Colour ambient_linear = to_linear(render.m_environment->m_radiance.m_ambient) * render.m_environment->m_radiance.m_energy;
			probe_array.ambient[probe_count] = { to_vec3(ambient_linear), 0.f };

			probe_array.atlas_rect[probe_count] = { m_atlas.probe_rect(*probe) };
			probe_array.matrix[probe_count] = view_matrix * probe->m_node.m_transform;

			probe_count++;
		}

		if(probe_count > 0)
			u_uniform.setUniforms(encoder, probe_array, probe_count);

		encoder.setUniform(u_uniform.u_count, &probe_array.counts);
		encoder.setUniform(u_uniform.u_indices, probe_array.indices, probe_count);
	}

	ReflectionCubemap& BlockReflection::find_cubemap(uint16_t size)
	{
		for(ReflectionCubemap& cubemap : m_cubemaps)
			if(cubemap.m_size > size * 2)
				return cubemap;
		return m_cubemaps[0];
	}

	void BlockReflection::render_reflection_probe(Render& render, ReflectionProbe& probe)
	{
		static const vec3 view_normal[6] = { -X3,  X3, -Y3,  Y3, -Z3,  Z3 };
		static const vec3 view_up[6] = { -Y3, -Y3, -Z3,  Z3, -Y3, -Y3 };

		uvec4 atlas_rect = m_atlas.render_update(render, probe);

		ReflectionCubemap& cubemap = find_cubemap(uint16_t(rect_w(atlas_rect)));

		for(int i = 0; i < 6; ++i)
		{
			vec3 edge = view_normal[i] * probe.m_extents;
			float range = abs(dot(view_normal[i], edge));

			mat4 transform = probe.m_node.m_transform * bxlookat(Zero3, view_normal[i], view_up[i]);
			mat4 projection = bxproj(90.f, 1.f, 0.01f, range, bgfx::getCaps()->homogeneousDepth);

			Renderer& renderer = m_gfx_system.renderer(Shading::Volume);

			ManualRender probe_render = { render, Shading::Volume,  cubemap.m_fbo[i], uvec4(Rect4), transform, projection };
			//probe_render.cull();
			probe_render.render(renderer);
		}
	}

	PassProbes::PassProbes(GfxSystem& gfx_system, BlockReflection& block_reflection)
		: RenderPass(gfx_system, {}, PassType::Probes)
		, m_block_reflection(block_reflection)
	{}

	void PassProbes::submit_render_pass(Render& render)
	{
		UNUSED(render);
		m_block_reflection.m_reflection_multiplier = 1.f;

#if 0
		for(ReflectionProbe* probe : render.m_shot->m_reflection_probes)
		{
			if(!probe->m_dirty)
				continue;

			m_block_reflection.render_reflection_probe(render, *probe);
			//prefilter_reflection_probe(*probe);
		}
#endif

		m_block_reflection.m_reflection_multiplier = 0.f;
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	ReflectionAtlas::ReflectionAtlas(uint16_t size, uint16_t subdiv)
		: m_size(size)
		, m_subdiv(subdiv)
	{
#if 0 // @todo: crashes in D3D11
		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, true, 1, color_format, GFX_TEXTURE_CLAMP))
			color_format = bgfx::TextureFormat::RGB10A2;

		m_color = bgfx::createTextureCube(size, true, 1, color_format, GFX_TEXTURE_CLAMP);

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachment = { m_color, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS };
			m_fbo[i] = bgfx::createFrameBuffer(1, &attachment, true);
			// clear it ? 
		}

		m_slots.reserve(subdiv * subdiv);
		for(uint x = 0; x < subdiv; ++x)
			for(uint y = 0; y < subdiv; ++y)
			{
				uint subdiv_size = m_size / m_subdiv;
				uvec4 slot_urect = { x * subdiv_size, y * subdiv_size, subdiv_size, subdiv_size };
				vec4 slot_rect = vec4(slot_urect) / float(m_size);
				m_slots.push_back({ m_slots.size(), nullptr, slot_urect, slot_rect, 0 });
			}
#endif
	}

	ReflectionAtlas::~ReflectionAtlas()
	{
#if 0
		for(int i = 0; i < 6; i++)
			bgfx::destroy(m_fbo[i]);
		bgfx::destroy(m_color);
#endif
	}

	vec4 ReflectionAtlas::probe_rect(ReflectionProbe& probe)
	{
		return m_slots[probe.m_atlas_index].m_rect;
	}

	uvec4 ReflectionAtlas::render_update(Render& render, ReflectionProbe& probe)
	{
		UNUSED(render);
		if(probe.m_atlas_index)
			return m_slots[probe.m_atlas_index].m_urect;

		Slot& slot = *pop(m_free_slots);
		slot.m_probe = &probe;
		probe.m_atlas_index = int(slot.m_index);
		return slot.m_urect;
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
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
		split_frustum_slices(render.m_camera, to_array(shadow.m_frustum_slices), light.m_shadow_num_splits, light.m_shadow_split_distribution);

		mat4 light_transform = bxlookat(-light.m_node.direction(), Zero3);
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

					mat4 transform = light->m_node.m_transform * bxlookat(Zero3, view_normals[i], view_up[i]);

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
				encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), u_direct_shadow.s_csm_atlas, m_csm.m_depth, GFX_TEXTURE_POINT);
			else
				encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), u_direct_shadow.s_csm_atlas, m_csm.m_depth, BGFX_SAMPLER_COMPARE_LESS);
				//encoder.setTexture(uint8_t(TextureSampler::ShadowCSM), u_direct_shadow.s_csm_atlas, m_csm.m_depth);
		}

		if(0)//render.m_shadow_atlas)
		{
			encoder.setTexture(uint8_t(TextureSampler::ShadowAtlas), u_shadow.s_shadow_atlas, m_atlas.m_depth, BGFX_SAMPLER_COMPARE_LESS);
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


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	ShadowCubemap::ShadowCubemap(uint16_t size)
		: m_size(size)
	{
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT))
			return;

		m_cubemap = bgfx::createTextureCube(m_size, false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP_UVW | GFX_TEXTURE_POINT);

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachment = { m_cubemap, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS };
			m_fbos[i] = bgfx::createFrameBuffer(1, &attachment, true);
		}
	}

	ShadowAtlas::ShadowAtlas(uint16_t size, vector<uint16_t> slices_subdiv)
		: m_size(size)
	{
		m_depth = bgfx::createTexture2D(m_size, m_size * uint16_t(slices_subdiv.size()), false, 1, bgfx::TextureFormat::D24S8, BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP);
		m_fbo = bgfx::createFrameBuffer(1, &m_depth);

		uint16_t index = 0;
		for(uint16_t subdiv : slices_subdiv)
		{
			m_slices.push_back({ m_size, subdiv, uvec4(0, index * m_size, m_size, m_size) });
		}

		uint16_t max_cubemap_size = 512;
		uint16_t cubemap_size = max_cubemap_size;
		while(cubemap_size >= 32)
		{
			m_cubemaps.push_back({ cubemap_size });
			cubemap_size >>= 1;
		}
	}

	ShadowCubemap& ShadowAtlas::light_cubemap(Light& light, uint16_t shadow_size)
	{
		UNUSED(light);
		for(int i = int(m_cubemaps.size()) - 1; i >= 0; i--)
			if(m_cubemaps[i].m_size > shadow_size * 2)
			{
				return m_cubemaps[i];
			}

		return m_cubemaps.back();
	}

	uvec4 ShadowAtlas::light_rect(Light& light)
	{
		UNUSED(light);
		Index index = {};// = m_light_indices[light.m_light_index];
		Slice& slice = m_slices[index.m_slice];
		Slice::Slot& slot = slice.m_slots[index.m_slot];
		return slot.m_rect;
	}

	ShadowAtlas::Slice::Slice(uint32_t size, uint16_t subdiv, uvec4 rect)
		: m_size(size)
		, m_subdiv(subdiv)
		, m_rect(rect)
	{
		uint32_t subdiv_size = size / subdiv;

		for(uint16_t y = 0; y < subdiv; ++y)
			for(uint16_t x = 0; x < subdiv; ++x)
			{
				uvec4 slot_rect = { rect.x + x * subdiv_size, rect.y + y * subdiv_size,
									subdiv_size, subdiv_size };

				m_slots.push_back({ nullptr, slot_rect });
			}
	}

	void ShadowAtlas::Slice::remove_light(Light& light)
	{
		UNUSED(light);
	}

	void ShadowAtlas::Slice::add_light(Light& light)
	{
		UNUSED(light);
	}

	void ShadowAtlas::remove_light(Light& light)
	{
		UNUSED(light);
		Index index = {}; // = m_light_indices[light.m_light_index];
		Slice& slice = m_slices[index.m_slice];
		slice.m_slots[index.m_slot].m_light = nullptr;
	}

	bool ShadowAtlas::update_light(Light& light, uint64_t render, float coverage, uint64_t light_version)
	{
		UNUSED(render); UNUSED(light_version);
		uint16_t target_size = min<uint16_t>(m_size / m_slices[0].m_subdiv, uint16_t(pow2_round_up(uint(m_size * coverage))));

		// @todo check if we need to allocate a new slot

		for(Slice& slice : m_slices)
			if(slice.m_size > target_size)
			{
				if(!slice.m_free_slots.empty())
					slice.add_light(light);
			}

		return true;
	}

	uvec4 ShadowAtlas::render_update(Render& render, Light& light)
	{
		float coverage;

		Plane camera_near_plane = render.m_camera.near_plane();

		vec3 points[2];

		if(light.m_type == LightType::Point)
		{
			points[0] = light.m_node.position();
			points[1] = light.m_node.position() + light.m_node.axis(X3) * light.m_range;
		}
		else if(light.m_type == LightType::Spot)
		{
			float w = light.m_range * std::sin(light.m_spot_angle);
			float d = light.m_range * std::cos(light.m_spot_angle);

			vec3 base = light.m_node.position() + light.m_node.direction() * d;

			points[0] = base;
			points[1] = base + light.m_node.axis(X3) * w;
		}

		if(!render.m_camera.m_orthographic)
		{
			for(int j = 0; j < 2; j++)
			{
				if(distance(camera_near_plane, points[j]) < 0.f)
					points[j].z = -render.m_camera.m_near; //small hack to keep size constant when hitting the screen

				points[j] = plane_segment_intersection(camera_near_plane, { light.m_node.position(), points[j] });
			}
		}

		vec2 size = frustum_viewport_size(render.m_camera.m_projection);

		float screen_diameter = distance(points[0], points[1]) * 2.f;
		coverage = screen_diameter / (size.x + size.y);

		//if(light.m_shadow_dirty) // updated when lights and objects bounds start or stop intersecting, or move
		//{
		//	light.m_last_version++;
		//	light.m_shadow_dirty = false;
		//}

		bool redraw = this->update_light(light, light.m_last_render, coverage, light.m_last_update);
		UNUSED(redraw);
		return light_rect(light);
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
}

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::TonemapMode>() { static Type ty("mud::TonemapMode", sizeof(mud::TonemapMode)); return ty; }
    
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BCS>() { static Type ty("BCS", sizeof(mud::BCS)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::DofBlur>() { static Type ty("DofBlur", sizeof(mud::DofBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::GIProbe>() { static Type ty("GIProbe", sizeof(mud::GIProbe)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Glow>() { static Type ty("Glow", sizeof(mud::Glow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightShadow>() { static Type ty("LightShadow", sizeof(mud::LightShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Lightmap>() { static Type ty("Lightmap", sizeof(mud::Lightmap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapAtlas>() { static Type ty("LightmapAtlas", sizeof(mud::LightmapAtlas)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::LightmapItem>() { static Type ty("LightmapItem", sizeof(mud::LightmapItem)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::ReflectionProbe>() { static Type ty("ReflectionProbe", sizeof(mud::ReflectionProbe)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::Tonemap>() { static Type ty("Tonemap", sizeof(mud::Tonemap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockBlur>() { static Type ty("BlockBlur", type<mud::GfxBlock>(), sizeof(mud::BlockBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockDofBlur>() { static Type ty("BlockDofBlur", type<mud::GfxBlock>(), sizeof(mud::BlockDofBlur)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGIBake>() { static Type ty("BlockGIBake", type<mud::DrawBlock>(), sizeof(mud::BlockGIBake)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGITrace>() { static Type ty("BlockGITrace", type<mud::DrawBlock>(), sizeof(mud::BlockGITrace)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGeometry>() { static Type ty("BlockGeometry", type<mud::DrawBlock>(), sizeof(mud::BlockGeometry)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockGlow>() { static Type ty("BlockGlow", type<mud::GfxBlock>(), sizeof(mud::BlockGlow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLight>() { static Type ty("BlockLight", type<mud::DrawBlock>(), sizeof(mud::BlockLight)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockLightmap>() { static Type ty("BlockLightmap", type<mud::DrawBlock>(), sizeof(mud::BlockLightmap)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockRadiance>() { static Type ty("BlockRadiance", type<mud::DrawBlock>(), sizeof(mud::BlockRadiance)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockReflection>() { static Type ty("BlockReflection", type<mud::DrawBlock>(), sizeof(mud::BlockReflection)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockShadow>() { static Type ty("BlockShadow", type<mud::DrawBlock>(), sizeof(mud::BlockShadow)); return ty; }
    template <> MUD_GFX_PBR_EXPORT Type& type<mud::BlockTonemap>() { static Type ty("BlockTonemap", type<mud::GfxBlock>(), sizeof(mud::BlockTonemap)); return ty; }
}


#include <bgfx/bgfx.h>
#include <xatlas.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

#include <cstdio>

#define LIGHTMAP_XATLAS

namespace mud
{
namespace gfx
{
	template <class T_Element, class... T_Args>
	inline T_Element& create(Scene& scene, T_Args&&... args)
	{
		return scene.m_pool->pool<T_Element>().construct(static_cast<T_Args&&>(args)...);
	}

	GIProbe& gi_probe(Gnode& parent, uint16_t subdiv, const vec3& extents)
	{
		Gnode& self = parent.suba();
		if(!self.m_gi_probe)
			self.m_gi_probe = &create<GIProbe>(*self.m_scene, *self.m_attach);
		if(subdiv != self.m_gi_probe->m_subdiv || extents != self.m_gi_probe->m_extents)
			self.m_gi_probe->resize(subdiv, extents);
		return *self.m_gi_probe;
	}

	LightmapAtlas& lightmap(Gnode& parent, uint32_t resolution, float density, const string& save_path)
	{
		Gnode& self = parent.suba();
		if(!self.m_lightmap_atlas)
		{
			self.m_lightmap_atlas = &create<LightmapAtlas>(*self.m_scene, resolution, density);
			self.m_lightmap_atlas->m_dirty = true;
		}
		self.m_lightmap_atlas->m_save_path = save_path;
		return *self.m_lightmap_atlas;
	}
}

	void BlockGITrace::GIProbeUniform::createUniforms()
	{
		u_transform   = bgfx::createUniform("u_gi_probe_transform",    bgfx::UniformType::Mat4, max_gi_probes);
		u_bounds      = bgfx::createUniform("u_gi_probe_bounds4",      bgfx::UniformType::Vec4, max_gi_probes);
		// multiplier, bias, normal_bias, blend_ambient
		u_params      = bgfx::createUniform("u_gi_probe_params",       bgfx::UniformType::Vec4, max_gi_probes);
		u_inv_extents = bgfx::createUniform("u_gi_probe_inv_extents4", bgfx::UniformType::Vec4, max_gi_probes);
		u_cell_size   = bgfx::createUniform("u_gi_probe_cell_size4",   bgfx::UniformType::Vec4, max_gi_probes);

		s_gi_probe = bgfx::createUniform("s_gi_probe", bgfx::UniformType::Int1, max_gi_probes);
	}

	void BlockGITrace::GIProbeUniform::setUniforms(bgfx::Encoder& encoder, GIProbe& gi_probe, const mat4& view) const
	{
		float diffuse = gi_probe.m_dynamic_range * gi_probe.m_diffuse;
		float specular = gi_probe.m_dynamic_range * gi_probe.m_specular;
		vec4 params = { diffuse, specular, gi_probe.m_bias, gi_probe.m_normal_bias };
		vec4 bounds = { gi_probe.m_extents * 2.f, 0.f };
		mat4 transform = gi_probe.m_transform * inverse(view);
		vec4 inv_extents = { Unit3 / gi_probe.m_extents, 1.f };
		vec4 cell_size = { gi_probe.m_extents * 2.f / float(gi_probe.m_subdiv), 1.f };

		encoder.setUniform(u_transform, &transform);
		encoder.setUniform(u_bounds, &bounds);
		encoder.setUniform(u_params, &params);
		encoder.setUniform(u_inv_extents, &inv_extents);
		encoder.setUniform(u_cell_size, &cell_size);
	}

	GIProbe::GIProbe(Node3& node)
		: m_node(node)
	{}

	GIProbe::~GIProbe()
	{}

	void GIProbe::resize(uint16_t subdiv, const vec3& extents)
	{
		if(bgfx::isValid(m_raster))
		{
			bgfx::destroy(m_fbo);
			bgfx::destroy(m_voxels_light_rgba);
		}

		m_transform = bxidentity();
		m_subdiv = subdiv;
		m_extents = extents;

		m_normal_bias = length(extents * 2.f / float(subdiv)) * sqrt(2.f) * 2.f;

		m_raster = bgfx::createTexture2D(subdiv, subdiv, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT);
		m_voxels_color   = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_normals = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);
		m_voxels_light   = bgfx::createTexture3D(subdiv, subdiv, subdiv, false, bgfx::TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE);

		bgfx::TextureHandle textures[4] = { m_raster, m_voxels_color, m_voxels_normals, m_voxels_light };
		m_fbo = bgfx::createFrameBuffer(4, textures, true);
		
		m_voxels_light_rgba = bgfx::createTexture3D(subdiv, subdiv, subdiv, true, bgfx::TextureFormat::RGBA16F, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPUTE_WRITE);

		m_dirty = true;
	}

	void save_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path)
	{
		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::TextureHandle texture = bgfx::createTexture3D(subdiv, subdiv, subdiv, true, source_format, BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK);
		bgfx::blit(0, texture, 0, 0, 0, 0, gi_probe.m_voxels_light_rgba, 0, 0, 0, 0, subdiv, subdiv, subdiv);
		bgfx::frame();
		bgfx::frame();

		save_bgfx_texture(gfx_system.allocator(), gfx_system.file_writer(), path.c_str(), target_format, texture, source_format, uint16_t(gi_probe.m_subdiv), uint16_t(gi_probe.m_subdiv), uint16_t(gi_probe.m_subdiv));
	}

	void load_gi_probe(GfxSystem& gfx_system, GIProbe& gi_probe, const string& path)
	{
		gi_probe.m_voxels_light_rgba = load_bgfx_texture(gfx_system.allocator(), gfx_system.file_reader(), path.c_str());
	}

	PassGIBake::PassGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: DrawPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void PassGIBake::next_draw_pass(Render& render, Pass& render_pass)
	{
		bool conservative = (bgfx::getCaps()->supported & BGFX_CAPS_CONSERVATIVE_RASTER) != 0;
		if(!conservative)
			printf("WARNING: rendering GI probe without conservative raster support will produce wrong output\n");

		UNUSED(render); UNUSED(render_pass);
		render_pass.m_bgfx_state = BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;

#ifndef VOXELGI_COMPUTE_LIGHTS
		GIProbe& gi_probe = *m_block_gi_bake.m_bake_probe; UNUSED(gi_probe);
		mat4 view = bxidentity();//gi_probe.m_transform * bxscale(1.f / gi_probe.m_extents);
		m_block_light.update_lights(render, view, to_array(render.m_shot->m_lights), to_array(m_block_light.m_block_shadow.m_shadows));
#endif
	}

	void PassGIBake::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled)
		{
			element.m_program = m_block_gi_bake.m_voxelize;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			this->add_element(render, element);
		}
	}

	PassGIProbes::PassGIProbes(GfxSystem& gfx_system, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: RenderPass(gfx_system, "voxelGI", PassType::VoxelGI)
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void PassGIProbes::submit_render_pass(Render& render)
	{
		if(!check_lighting(render.m_lighting, Lighting::VoxelGI))
			return;

		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
		{
			if(gi_probe->m_enabled && gi_probe->m_dirty)
			{
				if(gi_probe->m_mode == GIProbeMode::Voxelize)
				{
					printf("INFO: bake GIProbe\n");

					m_block_gi_bake.voxelize(render, *gi_probe);
					m_block_gi_bake.output(render, *gi_probe);

					for(int i = 0; i < gi_probe->m_bounces; ++i)
					{
						// @todo fix D3D bounce bug
						m_block_gi_bake.bounce(render, *gi_probe);
						m_block_gi_bake.output(render, *gi_probe);
					}

					gi_probe->m_dirty = false;

					printf("INFO: bake GIProbe done\n");

					//string path = m_gfx_system.m_resource_path + "/" + "gi_probe.dds";
					//save_gi_probe(m_gfx_system, *gi_probe, bgfx::TextureFormat::RGBA16F, bgfx::TextureFormat::BC6H, path);
				}

				if(gi_probe->m_mode == GIProbeMode::LoadVoxels)
				{
					string path = m_gfx_system.m_resource_path + "/" + "gi_probe.dds";
					load_gi_probe(m_gfx_system, *gi_probe, path);
				}
			}
		}
	}

	BlockGIBake::BlockGIBake(GfxSystem& gfx_system, BlockLight& block_light, BlockGITrace& block_trace)
		: DrawBlock(gfx_system, type<BlockGIBake>())
		, m_block_light(block_light)
		, m_block_trace(block_trace)
	{}

	void BlockGIBake::init_block()
	{
		u_voxelgi.createUniforms();

		m_voxelize = &m_gfx_system.programs().fetch("gi/voxelize");
		m_direct_light = &m_gfx_system.programs().fetch("gi/direct_light");
		m_bounce_light = &m_gfx_system.programs().fetch("gi/bounce_light");
		m_output_light = &m_gfx_system.programs().fetch("gi/output_light");
	}

	void BlockGIBake::voxelize(Render& render, GIProbe& gi_probe)
	{
		m_bake_probe = &gi_probe;

		vec3 extents = gi_probe.m_extents;
		
		Camera camera = { gi_probe.m_transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
		Viewport viewport = { camera, render.m_scene, { uvec2(0U), uvec2(uint(gi_probe.m_subdiv)) } };
		Render voxel_render = { Shading::Voxels, viewport, gi_probe.m_fbo, render.m_frame };

		BlockShadow& block_shadow = *m_gfx_system.m_pipeline->block<BlockShadow>();
		CSMFilterMode pcf_level = block_shadow.m_pcf_level;
		uint8_t splits = 0;
		block_shadow.m_pcf_level = CSM_NO_PCF;
		if(m_block_light.m_direct_light)
		{
			splits = m_block_light.m_direct_light->m_shadow_num_splits;
			m_block_light.m_direct_light->m_shadow_num_splits = 1;
		}

		Plane6 planes = frustum_planes(camera.m_projection, camera.m_transform);
		voxel_render.m_shot->m_lights = render.m_shot->m_lights;
		cull_items(render.m_scene, planes, voxel_render.m_shot->m_items);
		m_gfx_system.renderer(Shading::Voxels).subrender(render, voxel_render);

		if(m_block_light.m_direct_light)
		{
			m_block_light.m_direct_light->m_shadow_num_splits = splits;
		}
		block_shadow.m_pcf_level = pcf_level;

		if(m_direct_light_compute)
			this->compute(render, gi_probe);
	}

	void BlockGIBake::compute(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("gi direct");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, u_voxelgi.s_voxels_albedo,  gi_probe.m_voxels_color,   0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(1, u_voxelgi.s_voxels_normals, gi_probe.m_voxels_normals, 0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(2, u_voxelgi.s_voxels_light,   gi_probe.m_voxels_light,   0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);

		u_voxelgi.setUniforms(encoder, gi_probe);

		m_block_light.update_lights(render, bxidentity(), to_array(render.m_shot->m_lights), to_array(m_block_light.m_block_shadow.m_shadows));
		m_block_light.upload_lights(render_pass);

		ShaderVersion shader_version = { m_direct_light };
		if(m_block_light.m_direct_light)
			shader_version.set_option(m_block_light.m_index, DIRECT_LIGHT, true);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_direct_light->version(shader_version);
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}
	
	void BlockGIBake::bounce(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("gi bounce");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0,   u_voxelgi.s_voxels_normals,    gi_probe.m_voxels_normals,    0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		//encoder.setImage(1,   u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		encoder.setTexture(1, u_voxelgi.s_voxels_light_rgba, gi_probe.m_voxels_light_rgba);
		encoder.setImage(2,   u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::Write, bgfx::TextureFormat::R32U);

		u_voxelgi.setUniforms(encoder, gi_probe);
		m_block_trace.u_gi_probe.setUniforms(encoder, gi_probe, bxidentity());

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_bounce_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}

	void BlockGIBake::output(Render& render, GIProbe& gi_probe)
	{
		Pass render_pass = render.next_pass("output light");
		bgfx::Encoder& encoder = *render_pass.m_encoder;

		encoder.setImage(0, u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);
		encoder.setImage(1, u_voxelgi.s_voxels_light_rgba, gi_probe.m_voxels_light_rgba, 0, bgfx::Access::ReadWrite, bgfx::TextureFormat::RGBA16F);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_output_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(render_pass.m_index, program, subdiv / 64, subdiv, subdiv, BGFX_VIEW_NONE);
	}

	void BlockGIBake::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockGIBake::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		GIProbe& gi_probe = *m_bake_probe;

		int voxels_albedo_index  = 1;
		int voxels_normals_index = 2;
		int voxels_light_index   = 3;
		encoder.setUniform(u_voxelgi.s_voxels_albedo,  &voxels_albedo_index);
		encoder.setUniform(u_voxelgi.s_voxels_normals, &voxels_normals_index);
		encoder.setUniform(u_voxelgi.s_voxels_light,   &voxels_light_index);

		u_voxelgi.setUniforms(encoder, gi_probe);

#ifndef VOXELGI_COMPUTE_LIGHTS
		m_block_light.upload_lights(render_pass);
#endif
	}

	BlockGITrace::BlockGITrace(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockGITrace>())
	{
		static cstring options[1] = { "GI_CONETRACE" };
		m_shader_block->m_options = { options, 1 };
	}

	void BlockGITrace::init_block()
	{
		u_gi_probe.createUniforms();
	}

	void BlockGITrace::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::options(Render& render, ShaderVersion& shader_version) const
	{
		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
			if(gi_probe->m_enabled)
			{
				shader_version.set_option(m_index, GI_CONETRACE, true);
			}
	}

	void BlockGITrace::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		bgfx::Encoder& encoder = *render_pass.m_encoder;

		uint8_t index = 0;
		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
		{
			if(gi_probe->m_enabled)
			{
				encoder.setTexture(uint8_t(TextureSampler::GIProbe) + index++, u_gi_probe.s_gi_probe, gi_probe->m_voxels_light_rgba, GFX_TEXTURE_CLAMP_UVW);

				u_gi_probe.setUniforms(encoder, *gi_probe, render.m_camera.m_transform);
			}
		}
	}

	void BlockGITrace::upload_gi_probes(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);

		//bgfx::Encoder& encoder = *render_pass.m_encoder;
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	BlockBlur::BlockBlur(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program(gfx_system.programs().create("filter/gaussian_blur"))
	{
		static cstring options[2] = { "GAUSSIAN_HORIZONTAL", "GAUSSIAN_VERTICAL" };
		m_shader_block->m_options = { options, 2 };
		m_program.register_block(*this);
	}

	void BlockBlur::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockBlur::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockBlur::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockBlur::blur(Render& render)
	{
		static BlurKernel kernel = {
			{ 0.214607f, 0.189879f, 0.157305f, 0.071303f, 0.189879f, 0.157305f, 0.071303f },
			{ 0.38774f, 0.24477f, 0.06136f, 0.24477f, 0.06136f }
		};

		uvec4 rect = render.m_viewport.m_rect;

		for(uint8_t i = 0; i < 4; ++i)//render.m_target->m_effects.m_num_mips; i++)
		{
			gaussian_pass(render, rect, i, true, kernel);
			gaussian_pass(render, rect, i, false, kernel);
		}
	}

	void BlockBlur::gaussian_pass(Render& render, uvec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel)
	{
		bgfx::TextureHandle source = render.m_target->m_ping_pong.last();
		bgfx::FrameBufferHandle target = render.m_target->m_ping_pong.swap();

		// @todo: optimize this, I can't think of another way right now than to have a clear pass for EVERY blur level :/
		uint8_t clear = render.composite_pass();
		bgfx::setViewRect(clear, 0, 0, uint16_t(render.m_target->m_size.x), uint16_t(render.m_target->m_size.y));
		bgfx::setViewClear(clear, BGFX_CLEAR_COLOR);
		bgfx::setViewFrameBuffer(clear, target);
		bgfx::touch(clear);

		uvec4 source_rect = rect;
		if(horizontal)
			rect = rect / 2U;

		vec4 screen_params{ rect_size(vec4(rect)), 1.f / rect_size(vec4(rect)) };
		bgfx::setUniform(m_filter.u_uniform.u_screen_size_pixel_size, &screen_params);

		vec4 blur_params = { float(lod), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_blur_params, &blur_params);

		bgfx::setUniform(u_uniform.u_blur_kernel_0_3, horizontal ? &kernel.m_horizontal[0] : &kernel.m_vertical[0]);
		bgfx::setUniform(u_uniform.u_blur_kernel_4_7, horizontal ? &kernel.m_horizontal[4] : &kernel.m_vertical[4]);

		ShaderVersion version(&m_program);
		version.set_option(m_index, uint8_t(horizontal ? GAUSSIAN_HORIZONTAL : GAUSSIAN_VERTICAL), true);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, source);

		RenderQuad quad = { render.m_target->source_quad(vec4(source_rect), true), render.m_target->dest_quad(vec4(rect), true), true };
		m_filter.submit_quad(*render.m_target, render.composite_pass(), target, m_program.version(version), quad);
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	BlockDofBlur::BlockDofBlur(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program(gfx_system.programs().create("filter/dof_blur"))
	{
		static cstring options[1] = { "DOF_FIRST_PASS" };
		m_shader_block->m_options = { options, 1 };
		m_program.register_block(*this);
	}

	void BlockDofBlur::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockDofBlur::begin_render(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockDofBlur::begin_pass(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockDofBlur::submit_pass(Render& render)
	{
		if(render.m_filters.comp<DofBlur>().m_enabled)
			this->render(render, render.m_filters.comp<DofBlur>());
	}

	void BlockDofBlur::render(Render& render, const DofBlur& blur)
	{
		submit_blur_pass(render, blur, true);
		submit_blur_pass(render, blur, false);//, BGFX_STATE_BLEND_ALPHA);
	}

	void BlockDofBlur::submit_blur_pass(Render& render, const DofBlur& blur, bool first_pass, uint64_t bgfx_state)
	{
		ShaderVersion shader_version = { &m_program };
		shader_version.set_option(m_index, DOF_FIRST_PASS, first_pass);

		vec4 dof_near_params =
		{
			blur.m_near_distance,
			blur.m_near_distance - blur.m_near_transition,
			blur.m_near_radius,
			1.f / blur.m_near_radius,
		};

		vec4 dof_far_params =
		{
			blur.m_far_distance,
			blur.m_far_distance + blur.m_far_transition,
			blur.m_far_radius,
			0.f
		};

		vec4 dof_params = { blur.m_max_coc_radius, 0.f, 0.f, 0.f };

		bgfx::setUniform(u_uniform.u_dof_near_params, &dof_near_params);
		bgfx::setUniform(u_uniform.u_dof_far_params, &dof_far_params);
		bgfx::setUniform(u_uniform.u_dof_params, &dof_params);

		if(first_pass)
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_diffuse, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		}
		else
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_ping_pong.last(), GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
			bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_diffuse, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		}

		bgfx::setTexture(uint8_t(TextureSampler::SourceDepth), m_filter.u_uniform.s_source_depth, render.m_target->m_depth);

		bgfx::FrameBufferHandle target = first_pass ? render.m_target->m_ping_pong.swap() : render.m_target->m_post_process.swap();

		m_filter.submit_quad(*render.m_target, render.composite_pass(),
							 target, m_program.version(shader_version), render.m_viewport.m_rect, bgfx_state);
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

#define MAX_GLOW_LEVELS 7

namespace mud
{
	BlockGlow::BlockGlow(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_copy(copy)
		, m_blur(blur)
		, m_bleed_program(gfx_system.programs().create("filter/glow_bleed"))
		, m_merge_program(gfx_system.programs().create("filter/glow"))
	{
		static cstring options[1] = { "GLOW_FILTER_BICUBIC" };
		m_shader_block->m_options = { options, 1 };

		m_blur.m_program.register_block(*this);
		m_merge_program.register_block(*this);
	}

	void BlockGlow::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockGlow::begin_render(Render& render)
	{
		UNUSED(render);
#ifdef DEBUG_GLOW
		BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
		copy.debug_show_texture(render, render.m_target->m_cascade.m_texture, vec4(0.f), false, false, false, 1);
		copy.debug_show_texture(render, render.m_target->m_ping_pong.last(), vec4(0.f));
#endif
	}

	void BlockGlow::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockGlow::submit_pass(Render& render)
	{
		if(render.m_filters.comp<Glow>().m_enabled)
			this->render(render, render.m_filters.comp<Glow>());
	}

	void BlockGlow::render(Render& render, Glow& glow)
	{
		this->glow_bleed(render, glow);
		this->glow_blur(render, glow);
		this->glow_merge(render, glow);
	}

	void BlockGlow::glow_bleed(Render& render, Glow& glow)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_diffuse);
		//bgfx::setUniform(m_blur.u_uniform.u_exposure, &m_tonemap.m_exposure);

		vec4 glow_params = { 0.f, glow.m_bloom, glow.m_bleed_threshold, glow.m_bleed_scale };
		bgfx::setUniform(u_uniform.u_glow_params_0, &glow_params);

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_ping_pong.swap(), m_bleed_program.default_version(), render.m_viewport.m_rect);
	}

	void BlockGlow::glow_blur(Render& render, Glow& glow)
	{
		UNUSED(glow);
		uvec4 rect = render.m_viewport.m_rect;

		static BlurKernel kernel = {
			{ 0.174938f, 0.165569f, 0.140367f, 0.106595f, 0.165569f, 0.140367f, 0.106595f },
			{ 0.288713f, 0.233062f, 0.122581f, 0.233062f, 0.122581f }
		};

		size_t max_level = 0;

		for(vec4::length_type i = 0; i < 8; ++i)
			if((i < 4 && glow.m_levels_1_4[i]) || (i >= 4 && glow.m_levels_5_8[i - 4]))
				max_level = i;

		for(uint8_t i = 0; i < (max_level + 1); i++)
		{
			m_blur.gaussian_pass(render, rect, i, true, kernel);
			m_blur.gaussian_pass(render, rect, i, false, kernel);

			//bool blit_support = (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0;
			bool blit_support = false;

			RenderQuad quad = { render.m_target->source_quad(vec4(rect), true), render.m_target->dest_quad_mip(vec4(rect), i + 1, true), true };
			
			if(blit_support)
				bgfx::blit(render.composite_pass(),
						   render.m_target->m_cascade.m_texture, i + 1, uint16_t(rect.x), uint16_t(rect.y), 0,
						   render.m_target->m_ping_pong.last(), 0, uint16_t(rect.x), uint16_t(rect.y), 0, uint16_t(rect_w(rect)), uint16_t(rect_h(rect)), 1);
			else
				m_copy.submit_quad(*render.m_target->m_cascade.m_mips[i + 1], render.composite_pass(), render.m_target->m_ping_pong.last(), quad);
		}
	}

	void BlockGlow::glow_merge(Render& render, Glow& glow)
	{
		ShaderVersion shader_version(&m_merge_program);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_post_process.last());

		shader_version.set_option(m_index, GLOW_FILTER_BICUBIC, glow.m_bicubic_filter);

		bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_cascade.m_texture);

		vec4 glow_params = { glow.m_intensity, 0.f, float(render.m_target->m_size.x), float(render.m_target->m_size.y) };
		bgfx::setUniform(u_uniform.u_glow_params_1, &glow_params);
		bgfx::setUniform(u_uniform.u_glow_levels_1_4, &glow.m_levels_1_4);
		bgfx::setUniform(u_uniform.u_glow_levels_5_8, &glow.m_levels_5_8);

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.swap(), m_merge_program.version(shader_version), render.m_viewport.m_rect);
	}
}


#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#endif

namespace mud
{
	BlockTonemap::BlockTonemap(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_copy(copy)
		, m_program(gfx_system.programs().create("filter/tonemap"))
	{
		static cstring options[2] = {
			"ADJUST_BCS",
			"COLOR_CORRECTION",
		};
		static cstring modes[2] = {
			"TONEMAP_MODE",
		};

		m_shader_block->m_options = { options, 1 };
		m_shader_block->m_modes = { modes, 1 };

		m_program.register_block(*this);
	}

	void BlockTonemap::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockTonemap::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockTonemap::begin_pass(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockTonemap::submit_pass(Render& render)
	{
		if(render.m_filters.comp<Tonemap>().m_enabled)
			this->render(render, render.m_filters.comp<Tonemap>(), render.m_filters.comp<BCS>());
		else
			m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.last(), render.m_viewport.m_rect);
	}

	void BlockTonemap::render(Render& render, Tonemap& tonemap, BCS& bcs)
	{
		ShaderVersion shader_version(&m_program);

		m_filter.set_uniforms(render, *bgfx::begin());

		shader_version.set_mode(m_index, TONEMAP_MODE, uint8_t(tonemap.m_mode));

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_post_process.last());

		if(bgfx::isValid(tonemap.m_color_correction))
		{
			shader_version.set_option(m_index, COLOR_CORRECTION, true);
			bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, tonemap.m_color_correction);
		}

		vec4 exposure_params = { tonemap.m_exposure, tonemap.m_white_point, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_exposure_params, &exposure_params);

		if(bcs.m_enabled)
		{
			shader_version.set_option(m_index, ADJUST_BCS, true);

			vec4 bcs_values = { bcs.m_brightness, bcs.m_contrast, bcs.m_saturation, 0.f };
			bgfx::setUniform(u_uniform.u_bcs, &bcs_values);
		}

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_fbo, m_program.version(shader_version), render.m_viewport.m_rect);
	}
}

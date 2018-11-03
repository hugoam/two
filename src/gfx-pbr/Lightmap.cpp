//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx-pbr/Types.h>
#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>
#include <xatlas.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <infra/StringConvert.h>
#include <math/Random.h>
#include <geom/Intersect.h>
#include <geom/Mesh.h>
#include <pool/ObjectPool.h>
#include <gfx/Item.h>
#include <gfx/ManualRender.h>
#include <gfx/Shot.h>
#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <gfx/Assets.h>
#include <gfx/GfxSystem.h>
#include <gfx/Pipeline.h>
#include <gfx-pbr/Lightmap.h>
#include <gfx-pbr/VoxelGI.h>
#include <gfx-pbr/Light.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/Lightmap.h>
#endif

#define LIGHTMAP_HDR
//#define LIGHTMAP_COMPRESS

namespace glm
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

		save_bgfx_texture(gfx_system.m_allocator, gfx_system.file_writer(), path.c_str(), target_format, blit_texture, source_format, uint16_t(lightmap.m_size), uint16_t(lightmap.m_size));
	}

	void load_lightmap(GfxSystem& gfx_system, Lightmap& lightmap, const string& path)
	{
		lightmap.m_texture = load_bgfx_texture(gfx_system.m_allocator, gfx_system.file_reader(), path.c_str());

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

		bool add_mesh(Mesh& mesh, const mat4& transform);
		uvec2 generate(uint32_t rect_size, float density);
		void repack_mesh_uvs(uint32_t index, Mesh& mesh);

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

	bool XAtlas::add_mesh(Mesh& mesh, const mat4& transform)
	{
		MeshPacker vertices;
		mesh.read(vertices, transform);

		xatlas::InputMesh xmesh = {};
		xmesh.vertexCount = (int)mesh.m_vertex_count;
		xmesh.vertexPositionData = vertices.m_positions.data();
		xmesh.vertexPositionStride = sizeof(float) * 3;

		if((mesh.m_vertex_format & VertexAttribute::Normal) != 0)
		{
			xmesh.vertexNormalData = vertices.m_normals.data();
			xmesh.vertexNormalStride = sizeof(float) * 3;
		}

		if((mesh.m_vertex_format & VertexAttribute::TexCoord0) != 0)
		{
			xmesh.vertexUvData = vertices.m_uv0s.data();
			xmesh.vertexUvStride = sizeof(float) * 2;
		}

		xmesh.indexCount = (int)mesh.m_index_count;
		xmesh.indexData = mesh.m_cached_indices.data();
		xmesh.indexFormat = mesh.m_index32 ? xatlas::IndexFormat::UInt32 : xatlas::IndexFormat::UInt16;

		xatlas::AddMeshError error = xatlas::AddMesh(m_atlas, xmesh, true);
		//xatlas::AddMeshError error = xatlas::AddMesh(m_atlas, xmesh, true, false);
		//xatlas::AddMeshError error = xatlas::AddMesh(m_atlas, xmesh, false, false);

		if(error.code != xatlas::AddMeshErrorCode::Success)
		{
			printf("ERROR: xatlas - adding mesh '%s': %s\n", mesh.m_name.c_str(), xatlas::StringForEnum(error.code));
			if(error.code == xatlas::AddMeshErrorCode::AlreadyAddedEdge)
			{
				vec3 pos0 = vertices.m_positions[error.index0];
				vec3 pos1 = vertices.m_positions[error.index1];
				printf("DEBUG: already added edge %i to %i from face %i from %f, %f, %f to %f, %f, %f\n", error.index0, error.index1, error.face, pos0.x, pos0.y, pos0.z, pos1.x, pos1.y, pos1.z);
			}
		}

		return error.code == xatlas::AddMeshErrorCode::Success;
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

	void XAtlas::repack_mesh_uvs(uint32_t index, Mesh& mesh)
	{
		const xatlas::OutputMesh* xmesh = xatlas::GetOutputMeshes(m_atlas)[index++];

		MeshPacker source;
		mesh.read(source, bxidentity());

		MeshPacker result;

		assert(xmesh->vertexCount >= mesh.m_vertex_count);
		for(size_t i = 0; i < xmesh->vertexCount; i++)
		{
			const xatlas::OutputVertex& vertex = xmesh->vertexArray[i];
			vec2 uv = { vertex.uv[0], vertex.uv[1] };

			result.m_positions.push_back(source.m_positions[vertex.xref]);
			//result.m_colours.push_back(source.m_colours[vertex.xref]);
			result.m_normals.push_back(source.m_normals[vertex.xref]);
			result.m_tangents.push_back(source.m_tangents[vertex.xref]);
			result.m_uv0s.push_back(source.m_uv0s[vertex.xref]);

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
		Model* model;
		uvec2 size;
		std::vector<bool> success;
	};

	void unwrap_model(Model& model, ModelUnwrap& unwrap, uint32_t rect_size, float density)
	{
		printf("INFO: unwrapping model %s for lightmap\n", model.m_name.c_str());

		XAtlas atlas;

		for(ModelItem& model_item : model.m_items)
		{
			Mesh& mesh = *model_item.m_mesh;

			bool skip = false;
			skip |= mesh.m_draw_mode != PLAIN;
			skip |= !mesh.m_cache.m_vertex_format;

			bool success = skip ? false : atlas.add_mesh(mesh, bxidentity());
			unwrap.success.push_back(success);
		}

		unwrap.model = &model;
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
			atlas.repack_mesh_uvs(mesh_index++, mesh);
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
		std::map<Model*, ModelUnwrap> unwraps;
	};

	void BlockLightmap::bake_geometry(array<Item*> items, const mat4& transform, LightmapAtlas& lightmaps)
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
		
		for(size_t i = 0; i < items.size(); ++i)
		{
			Model& model = *items[i]->m_model;
			ModelUnwrap& unwrap = atlas.unwrap(model);

			if(unwrap.size == uvec2(0))
				continue;

			auto pack = pack_texture(model.m_name.c_str(), unwrap.size);
			if(!pack.image)
			{
				lightmaps.add_lightmap();
				pack = pack_texture(model.m_name.c_str(), unwrap.size);
			}

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
				vec2 offset = vec2(rect_offset(rect)) / float(lightmaps.m_size);
				lightmap.add_item(i, *items[i], true, vec4(scale, offset));
			}
		}
	}

	void BlockLightmap::bake_lightmaps(Scene& scene, const mat4& transform, const vec3& extents, LightmapAtlas& lightmaps)
	{
		printf("INFO: bake lightmaps\n");

		Plane6 planes = frustum_planes(transform, vec2(extents.x, extents.y), -extents.z / 2.f, -extents.z / 2.f);

		std::vector<Item*> items;

		//scene.cull_items(planes, items);
		scene.m_pool->iterate_objects<Item>([&](Item& item)
		{
			if(item.m_visible && (item.m_flags & ItemFlag::Render) != 0)
				items.push_back(&item);
		});

		this->bake_geometry(items, transform, lightmaps);

		std::vector<GIProbe*> gi_probes;
		scene.gather_gi_probes(gi_probes);

		Renderer& renderer = m_gfx_system.renderer(Shading::Lightmap);

		size_t i = 0;
		for(auto& lightmap : lightmaps.m_layers)
		{
#ifdef LIGHTMAP_COMPRESS
			string cached_path = lightmaps.m_save_path + "lightmap_" + to_string(i++) + ".dds";
#else
			string cached_path = lightmaps.m_save_path + "lightmap_" + to_string(i++) + ".hdr";
#endif
			if(file_exists(cached_path.c_str()))
			{
				load_lightmap(m_gfx_system, *lightmap, cached_path);
				continue;
			}

			uint16_t resolution = uint16_t(lightmaps.m_size);
			bgfx::FrameBufferHandle fbo = bgfx::createFrameBuffer(resolution, resolution, c_lightmap_format, BGFX_TEXTURE_RT);

			RenderFrame frame = m_gfx_system.render_frame();

			Camera camera = { transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
			Viewport viewport = { camera, scene, { uvec2(0), uvec2(lightmap->m_size) } };
			Render lightmap_render = { Shading::Lightmap, viewport, fbo, frame };

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
		for(BakeProbe bake_probe : m_bake_queue)
		{
			GIProbe& gi_probe = *bake_probe.m_probe;
			this->bake_lightmaps(*bake_probe.m_scene, gi_probe.m_transform, gi_probe.m_extents, *gi_probe.m_lightmaps);
			gi_probe.m_lightmaps->m_dirty = false;
		}
		m_bake_queue.clear();
	}

	void BlockLightmap::begin_render(Render& render)
	{
		if(render.m_shading == Shading::Lightmap)
			return;

		UNUSED(render);
		for(GIProbe* gi_probe : render.m_shot->m_gi_probes)
		{
			if(gi_probe->m_enabled && !gi_probe->m_dirty
			&& gi_probe->m_bake_lightmaps && gi_probe->m_lightmaps->m_dirty)
			{
				m_bake_queue.push_back({ &render.m_scene, gi_probe });
			}
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

			encoder.setUniform(Material::s_base_uniform.u_uv1_scale_offset, &binding.m_uv_scale_offset);

			if(bgfx::isValid(binding.m_lightmap))
				encoder.setTexture(uint8_t(TextureSampler::Lightmap), u_lightmap.s_lightmap, binding.m_lightmap);
		}
		else
		{
			vec4 uv_scale_offset = vec4(0.f);
			encoder.setUniform(Material::s_base_uniform.u_uv1_scale_offset, &uv_scale_offset);
		}
	}
}

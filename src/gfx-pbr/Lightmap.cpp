//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
#include <cstddef>
#include <xatlas.h>
module two.gfx.pbr;

#include <cstdio>

//#define LIGHTMAP_HDR
#define LIGHTMAP_COMPRESS
//#define LIGHTMAP_FORCE_RENDER
//#define LIGHTMAP_PIXELS
//#define LIGHTMAP_SORT

namespace two
{
	inline bool operator>(const uvec2& lhs, const uvec2& rhs) { return lhs.x > rhs.x || (lhs.x == rhs.x && lhs.y > rhs.y); }
}

namespace two
{
#ifdef LIGHTMAP_HDR
	static const TextureFormat c_lightmap_format = TextureFormat::RGBA16F;
#ifdef LIGHTMAP_COMPRESS
	static const bgfx::TextureFormat::Enum c_lightmap_file_format = bgfx::TextureFormat::BC6H;
#else
	static const bgfx::TextureFormat::Enum c_lightmap_file_format = bgfx::TextureFormat::RGBA16F;
#endif
#else
	static const TextureFormat c_lightmap_format = TextureFormat::RGBA8;
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
		info("create lightmap");

		//m_items.reserve(1024);
		m_items.reserve(4096);
	}

	void save_lightmap(GfxSystem& gfx, Lightmap& lightmap, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path)
	{
		uint16_t size = uint16_t(lightmap.m_size);
		Texture blit_texture = { uvec2(size, size), false, TextureFormat(source_format), BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK };
		bgfx::blit(0, blit_texture, 0, 0, 0, 0, texture, 0, 0, 0, 0, size, size, 1);
		bgfx::frame();
		bgfx::frame();

		save_bgfx_texture(gfx, path, target_format, blit_texture, source_format, uint16_t(lightmap.m_size), uint16_t(lightmap.m_size));
	}

	void load_lightmap(GfxSystem& gfx, Lightmap& lightmap, const string& path)
	{
		lightmap.m_texture = { "lightmap" };
		lightmap.m_texture.load(gfx, path);

		for(LightmapItem& item : lightmap.m_items)
			item.m_lightmap = &lightmap.m_texture;
	}

	void Lightmap::add_item(size_t index, Item& item, bool valid, const vec4& uv_scale_offset)
	{
		//Texture* texture = valid ? &m_texture : nullptr;
		if(valid)
			m_items.push_back({ index, m_texture, uv_scale_offset });
		item.m_lightmaps.push_back((void*) &m_items.back());
	}

	LightmapAtlas::LightmapAtlas(uint32_t size, float density)
		: m_size(size)
		, m_density(density)
	{}

	LightmapAtlas::~LightmapAtlas()
	{}

	void pass_lightmap(GfxSystem& gfx, Render& render)
	{
		static BlockLight& block_light = *gfx.m_renderer.block<BlockLight>();
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();
		static BlockGITrace& block_gi_trace = *gfx.m_renderer.block<BlockGITrace>();
		static BlockLightmap& block_lightmap = *gfx.m_renderer.block<BlockLightmap>();

		Pass pass = render.next_pass("lightmap", PassType::Lightmap);

		bool conservative = (bgfx::getCaps()->supported & BGFX_CAPS_CONSERVATIVE_RASTER) != 0;
		if(!conservative)
			warn("rendering lightmap without conservative raster support will produce visible seams");

		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_MSAA;

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(gfx); UNUSED(render); UNUSED(pass);
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Lit])
				return false;

			element.set_program(*block_lightmap.m_lightmap);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

	BlockLightmap::BlockLightmap(GfxSystem& gfx, BlockLight& block_light, BlockGIBake& block_gi_bake)
		: DrawBlock(gfx, type<BlockLightmap>())
		, m_block_light(block_light)
		, m_block_gi_bake(block_gi_bake)
	{}

	void BlockLightmap::init_block()
	{
		u_lightmap.createUniforms();

		m_lightmap = &m_gfx.programs().fetch("pbr/lightmap");
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
				printf("[debug] already added edge %i to %i from face %i from %f, %f, %f to %f, %f, %f\n", index0, index1, face, pos0.x, pos0.y, pos0.z, pos1.x, pos1.y, pos1.z);
			}
		};

		xatlas::AddMeshError::Enum result = xatlas::AddMesh(m_atlas, xmesh, on_warning, &geometry);

		if(result != xatlas::AddMeshError::Success)
		{
			error("xatlas - adding mesh '%s': %s\n", mesh.m_name.c_str(), xatlas::StringForEnum(result));
		}

		return result == xatlas::AddMeshError::Success;
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

		mesh.write(result, false);
	}

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

		info("unwrapping model %s for lightmap", model.m_name.c_str());

		XAtlas atlas;

		vector<MeshPacker> geometry(model.m_items.size());
		for(size_t i = 0; i < model.m_items.size(); ++i)
		{
			Mesh& mesh = *model.m_items[i].m_mesh;
			geometry[i].unpack(mesh.m_cache, model.m_items[i].m_transform);

			bool skip = false;
			skip |= mesh.m_primitive != PrimitiveType::Triangles;
			skip |= !mesh.m_cache.m_vertex_format;

			bool success = skip ? false : atlas.add_mesh(mesh, geometry[i]);
			unwrap.success[i] = success;
		}

		unwrap.size = atlas.generate(rect_size, density);

		if(unwrap.size.x == 0 || unwrap.size.y == 0)
		{
			warn("model %s unwrapped to zero size rect", model.m_name.c_str());
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

	void BlockLightmap::bake_geometry(span<Item*> items, LightmapAtlas& lightmaps)
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
			for(ModelElem& elem : model.m_items)
			{
				if(!unwrap.success[elem.m_index])
				{
					lightmap.add_item(i, *items[i], false, vec4(0.f));
					continue;
				}

				vec2 scale = vec2(1.f / float(lightmaps.m_size));
				vec2 offset = vec2(rect.pos) / float(lightmaps.m_size);
				lightmap.add_item(i, *items[i], true, vec4(scale, offset));
			}
		}
	}

	void BlockLightmap::bake_lightmaps(Scene& scene, LightmapAtlas& atlas, const mat4& transform, const vec3& extents)
	{
		info("bake lightmaps");

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

		RenderFunc renderer = m_gfx.renderer(Shading::Lightmap);

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
				load_lightmap(m_gfx, *lightmap, cached_path);
				continue;
			}
#endif

			uint32_t resolution = uint16_t(atlas.m_size);
			FrameBuffer fbo = { uvec2(resolution), c_lightmap_format, BGFX_TEXTURE_RT };

			RenderFrame frame = m_gfx.render_frame();
			RenderTarget& target = m_gfx.main_target();

			Camera camera = { transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
			Viewport viewport = { camera, scene, Rect4 };
			Render lightmap_render = { Shading::Lightmap, viewport, target, fbo, frame };
			viewport.m_clear_colour = Colour::None;

			for(LightmapItem& item : lightmap->m_items)
				lightmap_render.m_shot->m_items.push_back(items[item.m_item]);

			unique<PBRShot> shot = make_unique<PBRShot>();
			shot->m_gi_probes = gi_probes;
			lightmap_render.m_shot = shot.get();
			lightmap_render.m_ushot = stl::move(shot);

			m_gfx.m_renderer.render(lightmap_render, renderer);

			bgfx::frame();

			save_lightmap(m_gfx, *lightmap, bgfx::getTexture(fbo), bgfx::TextureFormat::Enum(c_lightmap_format), c_lightmap_file_format, cached_path);
			load_lightmap(m_gfx, *lightmap, cached_path);
		}

		info("bake lightmaps done");
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
		PBRShot& shot = static_cast<PBRShot&>(*render.m_shot);
		for(LightmapAtlas* atlas : shot.m_lightmaps)
			if(atlas->m_dirty)
			{
				m_bake_queue.push_back({ render.m_scene, atlas });
			}
	}

	void BlockLightmap::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(program);

		const Item& item = *element.m_item;
		const ModelElem& elem = *element.m_elem;
		if(item.m_lightmaps.size() > 0)
		{
			LightmapItem& binding = *(LightmapItem*)item.m_lightmaps[elem.m_index];
			if(binding.m_lightmap->valid())
			{
				program.set_option(MaterialLit::s_block.m_index, LIGHTMAP);
			}
		}
	}

	void BlockLightmap::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
		const uint32_t lightmap = uint32_t(TextureSampler::Lightmap);
		bgfx::setViewUniform(pass.m_index, u_lightmap.s_lightmap, &lightmap);
	}

	void BlockLightmap::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render);

		bgfx::Encoder& encoder = *pass.m_encoder;

		if(element.m_item->m_lightmaps.size() > 0)
		{
			LightmapItem& binding = *(LightmapItem*)element.m_item->m_lightmaps[element.m_elem->m_index];

			encoder.setUniform(GpuState<MaterialBase>::me.u_uv1_scale_offset, &binding.m_uv_scale_offset);

			if(binding.m_lightmap && binding.m_lightmap->valid())
#ifdef LIGHTMAP_PIXELS
				encoder.setTexture(uint8_t(TextureSampler::Lightmap), *binding.m_lightmap, TEXTURE_POINT);
#else
				encoder.setTexture(uint8_t(TextureSampler::Lightmap), *binding.m_lightmap);
#endif
		}
		else
		{
			vec4 uv_scale_offset = vec4(0.f);
			encoder.setUniform(GpuState<MaterialBase>::me.u_uv1_scale_offset, &uv_scale_offset);
		}
	}
}

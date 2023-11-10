#include <two/gfx.h>
#include <two/geom.h>
#include <two/pool.h>
#include <two/gfx.pbr.h>
#include <two/tree.h>
#include <two/ecs.h>
#include <two/math.h>
#include <two/infra.h>
#include <two/type.h>

#ifndef USE_STL
#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#endif

namespace stl
{
	using namespace two;
	template class TWO_GFX_PBR_EXPORT vector<Radiance*>;
	template class TWO_GFX_PBR_EXPORT vector<DofBlur>;;
	template class TWO_GFX_PBR_EXPORT vector<Glow>;;
	template class TWO_GFX_PBR_EXPORT vector<BCS>;;
	template class TWO_GFX_PBR_EXPORT vector<Tonemap>;
	template class TWO_GFX_PBR_EXPORT vector<MeshPacker>;
	template class TWO_GFX_PBR_EXPORT vector<GpuLight>;
	template class TWO_GFX_PBR_EXPORT vector<LightShadow>;
	template class TWO_GFX_PBR_EXPORT vector<LightmapItem>;
	template class TWO_GFX_PBR_EXPORT vector<FrustumSlice*>;
	template class TWO_GFX_PBR_EXPORT vector<CSMSlice>;
	template class TWO_GFX_PBR_EXPORT vector<CSMShadow>;
	template class TWO_GFX_PBR_EXPORT vector<AtlasIndex>;
	template class TWO_GFX_PBR_EXPORT vector<ShadowAtlas::Slice>;
	template class TWO_GFX_PBR_EXPORT vector<ShadowAtlas::Slot>;
	template class TWO_GFX_PBR_EXPORT vector<ShadowAtlas::Block>;
	template class TWO_GFX_PBR_EXPORT vector<CubeTarget>;
	template class TWO_GFX_PBR_EXPORT vector<ReflectionAtlas::Slot>;
	template class TWO_GFX_PBR_EXPORT vector<ReflectionAtlas::Slot*>;
	template class TWO_GFX_PBR_EXPORT vector<BlockLightmap::BakeEntry>;
	template class TWO_GFX_PBR_EXPORT vector<unique<Lightmap>>;
	template class TWO_GFX_PBR_EXPORT unordered_map<Model*, ModelUnwrap>;
	template class TWO_GFX_PBR_EXPORT unordered_map<Texture*, Texture*>;
	//template class TWO_GFX_PBR_EXPORT unordered_map<uint32_t, Shadowmap>;
}
#endif

#ifdef TWO_MODULES
module two.gfx-pbr;
#else
#endif

namespace two
{
    // Exported types
    template <> TWO_GFX_PBR_EXPORT Type& type<two::TonemapMode>() { static Type ty("TonemapMode", sizeof(two::TonemapMode)); return ty; }
    
    
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLight>() { static Type ty("BlockLight", type<two::DrawBlock>(), sizeof(two::BlockLight)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapItem>() { static Type ty("LightmapItem", sizeof(two::LightmapItem)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Lightmap>() { static Type ty("Lightmap", sizeof(two::Lightmap)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightmapAtlas>() { static Type ty("LightmapAtlas", sizeof(two::LightmapAtlas)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockLightmap>() { static Type ty("BlockLightmap", type<two::DrawBlock>(), sizeof(two::BlockLightmap)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGeometry>() { static Type ty("BlockGeometry", type<two::DrawBlock>(), sizeof(two::BlockGeometry)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockRadiance>() { static Type ty("BlockRadiance", type<two::DrawBlock>(), sizeof(two::BlockRadiance)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeTarget>() { static Type ty("CubeTarget", sizeof(two::CubeTarget)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CubeCamera>() { static Type ty("CubeCamera", sizeof(two::CubeCamera)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::ReflectionProbe>() { static Type ty("ReflectionProbe", sizeof(two::ReflectionProbe)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockReflection>() { static Type ty("BlockReflection", type<two::DrawBlock>(), sizeof(two::BlockReflection)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::LightShadow>() { static Type ty("LightShadow", sizeof(two::LightShadow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMSlice>() { static Type ty("CSMSlice", type<two::LightShadow>(), sizeof(two::CSMSlice)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::CSMShadow>() { static Type ty("CSMShadow", sizeof(two::CSMShadow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockShadow>() { static Type ty("BlockShadow", type<two::DrawBlock>(), sizeof(two::BlockShadow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::GIProbe>() { static Type ty("GIProbe", sizeof(two::GIProbe)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGITrace>() { static Type ty("BlockGITrace", type<two::DrawBlock>(), sizeof(two::BlockGITrace)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGIBake>() { static Type ty("BlockGIBake", type<two::DrawBlock>(), sizeof(two::BlockGIBake)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockBlur>() { static Type ty("BlockBlur", type<two::GfxBlock>(), sizeof(two::BlockBlur)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::DofParams>() { static Type ty("DofParams", sizeof(two::DofParams)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::DofBlur>() { static Type ty("DofBlur", sizeof(two::DofBlur)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockDofBlur>() { static Type ty("BlockDofBlur", type<two::GfxBlock>(), sizeof(two::BlockDofBlur)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Glow>() { static Type ty("Glow", sizeof(two::Glow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockGlow>() { static Type ty("BlockGlow", type<two::GfxBlock>(), sizeof(two::BlockGlow)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BCS>() { static Type ty("BCS", sizeof(two::BCS)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::Tonemap>() { static Type ty("Tonemap", sizeof(two::Tonemap)); return ty; }
    template <> TWO_GFX_PBR_EXPORT Type& type<two::BlockTonemap>() { static Type ty("BlockTonemap", type<two::GfxBlock>(), sizeof(two::BlockTonemap)); return ty; }
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

#include <cstring>

#include <cstdio>

namespace two
{
	GpuState<Radiance> GpuState<Radiance>::me;
	GpuState<Skylight> GpuState<Skylight>::me;
	GpuState<Fog> GpuState<Fog>::me;
	GpuState<Zone> GpuState<Zone>::me;
	GpuState<ZoneLights> GpuState<ZoneLights>::me;

	GpuState<GpuLight> GpuState<GpuLight>::me;

	BlockLight::BlockLight(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockLight>())
	{
		m_options = { "SKY_LIGHT", "FOG" };

		m_defines = {
			{ "MAX_LIGHTS", to_string(c_max_forward_lights)  },
			{ "MAX_SHADOWS", to_string(c_max_shadows) },
		};
	}

	void BlockLight::init_block()
	{
		u_shot.createUniforms();

#if !ZONES_BUFFER
		GpuState<Radiance>::me.init();
		GpuState<Skylight>::me.init();
		GpuState<Fog>::me.init();
#endif

#if !LIGHTS_BUFFER
		GpuState<GpuLight>::me.init();
#endif

#if !ZONES_LIGHTS_BUFFER
		GpuState<ZoneLights>::me.init();
#endif
	}

	void BlockLight::begin_render(Render& render)
	{
		UNUSED(render);

		this->setup_lights(render, render.m_camera->m_view);
		this->upload_lights(render);
		this->upload_zones(render);
	}

	void BlockLight::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		if(render.m_viewport->m_clustered)
			program.set_option(0, CLUSTERED, true);

		if(render.m_env && render.m_env->m_skylight.m_enabled)
			program.set_option(m_index, SKY_LIGHT, true);

		if(render.m_env && render.m_env->m_fog.m_enabled)
			program.set_option(m_index, FOG, true);
	}

	void BlockLight::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);
#if !ZONES_LIGHTS_BUFFER
		GpuState<ZoneLights>::me.upload(pass.m_index, m_zones[0]);
#endif

#if !ZONES_BUFFER
		GpuState<Zone>::me.upload(pass, render.m_scene->m_env);
#endif

#if !LIGHTS_BUFFER
		GpuState<GpuLight>::me.upload(pass, const_cast<vector<GpuLight>&>(m_gpu_lights));
#endif

#if ZONES_BUFFER
		uint32_t zones = uint32_t(TextureSampler::Zones);
		bgfx::setViewUniform(pass.m_index, u_shot.s_zones, &zones);
#endif

#if LIGHTS_BUFFER
		uint32_t lights = uint32_t(TextureSampler::Lights);
		bgfx::setViewUniform(pass.m_index, u_shot.s_lights, &lights);
#endif

		if(render.m_viewport->m_clustered)
			render.m_viewport->m_clusters->submit(pass);
	}

	void BlockLight::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(element);
		bgfx::Encoder& encoder = *pass.m_encoder;

		if(render.m_viewport->m_clustered)
			render.m_viewport->m_clusters->submit(encoder);

		this->commit_zones(render, pass); //render, pass, render.m_env);
		this->commit_lights(render, pass);

		// set to not render if not first direct pass, depending on cull
	}

	void BlockLight::setup_lights(Render& render, const mat4& view)
	{
		const vec3 skylight = muln(view, normalize(render.m_env->m_skylight.m_position));
		render.m_env->m_skylight.m_direction = skylight;

		span<Light*> lights = render.m_shot.m_lights;
		lights.m_count = min(lights.m_count, size_t(c_max_forward_lights));

		ZoneLights& zone = m_zones[0];
		zone.m_light_counts = vec4(0.f);
		zone.m_shadow_counts = vec4(0.f);

		m_gpu_lights.clear();

		for(size_t index = 0; index < lights.size(); ++index)
		{
			const Light& light = *lights[index];

			const vec3 position = mulp(view, light.m_node->position());
			const float range = light.m_range;
			const vec3 energy = to_vec3(light.m_colour * light.m_energy);
			const vec3 energy2 = to_vec3(to_linear(light.m_colour) * light.m_energy);
			const float specular = light.m_specular;
			const vec3 direction = muln(view, light.m_node->direction());
			const float attenuation = light.m_attenuation;
			const float spot_attenuation = light.m_spot_attenuation;
			const float spot_cutoff = cos(to_radians(light.m_spot_angle));

			m_gpu_lights.push_back({ position, range, energy, specular, direction, attenuation, spot_attenuation, spot_cutoff });

			float& light_type_count = zone.m_light_counts[size_t(light.m_type)];
			zone.m_light_indices[size_t(light_type_count)][size_t(light.m_type)] = float(index);
			light_type_count++;

			if(light.m_shadows)
			{
				float& shadow_type_count = zone.m_shadow_counts[size_t(light.m_type)];
				shadow_type_count++;
			}
		}

		m_light_count = uint16_t(lights.m_count);
		zone.m_light_count = uint16_t(lights.m_count);
	}

	void BlockLight::upload_lights(Render& render)
	{
		UNUSED(render);
#if LIGHTS_BUFFER
		GpuState<GpuLight>::me.pack(m_lights_texture, m_gpu_lights);
#endif
	}

	void BlockLight::upload_zones(Render& render)
	{
#if ZONES_BUFFER
		span<Zone> zones = { &render.m_scene->m_env, 1 };
		GpuState<Zone>::me.pack(m_zones_texture, zones);
#else
		UNUSED(render);
#endif
	}

	void BlockLight::commit_lights(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
#if LIGHTS_BUFFER
		bgfx::Encoder& encoder = *pass.m_encoder;
		encoder.setTexture(uint8_t(TextureSampler::Lights), m_lights_texture.texture);
#endif
	}

	void BlockLight::commit_zones(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
#if ZONES_BUFFER
		bgfx::Encoder& encoder = *pass.m_encoder;
		encoder.setTexture(uint8_t(TextureSampler::Zones), m_zones_texture);
#endif
		//GpuState<ZoneLights>::me.upload(encoder, m_zones[0]);
	}
}

#ifdef _DEBUG
namespace two
{
	void debug_draw_light_clusters(Gnode& parent, Viewport& viewport, Camera& camera)
	{
		if(!viewport.m_clustered) return;
		Froxelizer& clusters = *viewport.m_clusters;

		if(clusters.m_debug_clusters.empty())
			clusters.compute_clusters();

		enum Mode { ClusterIndex, RecordIndex, LightIndex, LightCount };
		Mode mode = ClusterIndex;

		mat4 transform = inverse(bxlookat(camera.m_eye, camera.m_target));
		uint32_t i = 0;
		for(Frustum& frustum : clusters.m_debug_clusters)
		{
			if(!clusters.count(i, 0) && !clusters.count(i, 1))
			{
				//gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour(1.f, 0.02f)));
				i++;
				continue;
			}

			Colour colour = Colour(1.f, 0.02f);
			uint32_t record = clusters.record(i);
			uint32_t light = clusters.light(record);

			if(mode == ClusterIndex)
				colour = hsl(float(i) / (29.f * 16.f * 16.f), 1.f, 0.5f);
			else if(mode == RecordIndex)
				colour = hsl(float(record) / float(255.f), 1.f, 0.5f);
			else if(mode == LightIndex)
				colour = hsl(float(light) / 255.f, 1.f, 0.5f);
			else if(mode == LightCount)
				colour = hsl(float(clusters.count(i)) / 32.f, 1.f, 0.5f);

			gfx::draw(*parent.m_scene, transform, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(colour));
			i++;
		}
	}

	void debug_draw_light_slices(Gnode& parent, Light& light, bool frustums, bool bounds)
	{
		uint32_t index = 0; UNUSED(light);// light.m_index];

		GfxSystem& gfx = parent.m_scene->m_gfx;
		BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();

		if(index >= block_shadow.m_shadows.size())
			return;

		CSMShadow& shadow = block_shadow.m_csm_shadows[index];

		auto draw = [](Gnode& parent, const Shape& shape, const Symbol& symbol)
		{
			Gnode& self = gfx::node(parent);
			gfx::draw(self, shape, symbol);
		};

		for(size_t i = 0; i < shadow.m_slices.size(); ++i)
		{
			mat4 inverse_light = inverse(shadow.m_slices[i].m_transform);
			draw(parent, Sphere(vec3(inverse_light[3]), 1.f), Symbol::wire(Colour::White));

			if(frustums)
			{
				Frustum& frustum = shadow.m_slices[i].m_frustum;
				draw(parent, Box({ &frustum.m_corners[0], 8 }), Symbol::wire(Colour::White));
				if(false)
					draw(parent, Sphere(frustum.m_center, frustum.m_radius), Symbol::wire(Colour::DarkGrey));

			}

			if(bounds)
			{
				Box light_bounds = Box(Cube(aabb(shadow.m_slices[i].m_light_bounds.min, shadow.m_slices[i].m_light_bounds.max)));

				for(vec3& vertex : light_bounds.m_vertices)
					vertex = vec3(inverse_light * vec4(vertex, 1.f));

				draw(parent, light_bounds, Symbol::wire(Colour::Pink));
			}
		}
	}
}
#endif


#include <bgfx/bgfx.h>
#include <xatlas.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

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
		printf("[info] create lightmap\n");

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
		load_texture(gfx, lightmap.m_texture, path);

		for(LightmapItem& item : lightmap.m_items)
			item.m_lightmap = &lightmap.m_texture;
	}

	void Lightmap::add_item(size_t index, Item& item, bool valid, const vec4& uv_scale_offset)
	{
		//Texture* texture = valid ? &m_texture : nullptr;
		if(valid)
			m_items.push_back({ index, m_texture, uv_scale_offset });
		item.m_lightmaps.push_back(&m_items.back());
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
			printf("[warning] rendering lightmap without conservative raster support will produce visible seams\n");

		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_MSAA;

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
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

		xatlas::AddMeshError::Enum error = xatlas::AddMesh(m_atlas, xmesh, on_warning, &geometry);

		if(error != xatlas::AddMeshError::Success)
		{
			printf("[ERROR] xatlas - adding mesh '%s': %s\n", mesh.m_name.c_str(), xatlas::StringForEnum(error));
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

		printf("[info] unwrapping model %s for lightmap\n", model.m_name.c_str());

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
			printf("[warning] model %s unwrapped to zero size rect\n", model.m_name.c_str());
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
		printf("[info] bake lightmaps\n");

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
				lightmap_render.m_shot.m_items.push_back(items[item.m_item]);

			lightmap_render.m_shot.m_gi_probes = gi_probes;
			m_gfx.m_renderer.render(lightmap_render, renderer);

			bgfx::frame();

			save_lightmap(m_gfx, *lightmap, bgfx::getTexture(fbo), bgfx::TextureFormat::Enum(c_lightmap_format), c_lightmap_file_format, cached_path);
			load_lightmap(m_gfx, *lightmap, cached_path);
		}

		printf("[info] bake lightmaps done\n");
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
		for(LightmapAtlas* atlas : render.m_shot.m_lightmaps)
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
			LightmapItem& binding = *item.m_lightmaps[elem.m_index];
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
			LightmapItem& binding = *element.m_item->m_lightmaps[element.m_elem->m_index];

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


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

#define DEBUG_ITEMS 0
#define DEPTH_PASS 0
#define DEBUG_GBUFFERS 0

namespace two
{
namespace gfx
{
	void setup_pipeline_pbr(GfxSystem& gfx)
	{
		gfx.init_pipeline(pipeline_pbr);
	}
}

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
		gather_items(scene, *render.m_camera, render.m_shot.m_items);
		gather_occluders(scene, *render.m_camera, render.m_shot.m_occluders);
		gather_lights(scene, render.m_shot.m_lights);
		gather_gi_probes(scene, render.m_shot.m_gi_probes);
		gather_lightmaps(scene, render.m_shot.m_lightmaps);
		gather_reflection_probes(scene, render.m_shot.m_reflection_probes);

		render.m_frustum = optimized_frustum(*render.m_camera, render.m_shot.m_items);

		render.m_shot.m_immediate = { scene.m_immediate.get() };

#if DEBUG_ITEMS
		scene.debug_items(render);
#endif
	}

	void pipeline_pbr(GfxSystem& gfx, Renderer& pipeline, bool deferred)
	{
		BlockMaterial& material = pipeline.add_block<BlockMaterial>(gfx);
		UNUSED(material);

		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx, filter);
		BlockBlur& blur = pipeline.add_block<BlockBlur>(gfx, filter);

		// pipeline 
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx);
		BlockGeometry& geometry = pipeline.add_block<BlockGeometry>(gfx);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx, filter);
		BlockRadiance& radiance = pipeline.add_block<BlockRadiance>(gfx, filter, copy);
		BlockLight& light = pipeline.add_block<BlockLight>(gfx);
		BlockShadow& shadow = pipeline.add_block<BlockShadow>(gfx, depth, light);
		BlockReflection& reflection = pipeline.add_block<BlockReflection>(gfx);
		BlockGITrace& gi_trace = pipeline.add_block<BlockGITrace>(gfx);
		BlockGIBake& gi_bake = pipeline.add_block<BlockGIBake>(gfx, light, shadow, gi_trace);
		BlockLightmap& lightmap = pipeline.add_block<BlockLightmap>(gfx, light, gi_bake);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx);
		UNUSED(geometry);
		UNUSED(particles);
		UNUSED(sky);

		// mrt
		//BlockSSAO& ssao = pipeline.add_block<BlockSSAO>(gfx, filter, blur);
		//BlockSSR& ssr = pipeline.add_block<BlockSSR>(gfx);
		//BlockSSS& sss = pipeline.add_block<BlockSSS>(gfx);

		// effects
		BlockDofBlur& dof_blur = pipeline.add_block<BlockDofBlur>(gfx, filter);
		//BlockExposure& exposure = pipeline.add_block<BlockExposure>(gfx);
		BlockGlow& glow = pipeline.add_block<BlockGlow>(gfx, filter, copy, blur);
		BlockTonemap& tonemap = pipeline.add_block<BlockTonemap>(gfx, filter, copy);
		UNUSED(dof_blur);
		UNUSED(glow);
		UNUSED(tonemap);

		vector<ShaderBlock*> depth_blocks = { &depth };
		vector<ShaderBlock*> geometry_blocks = {};
		vector<ShaderBlock*> shading_blocks = { &radiance, &light, &shadow, &gi_trace, &reflection, &lightmap };
		vector<ShaderBlock*> gi_blocks = { &light, &shadow, &gi_bake };
		vector<ShaderBlock*> lightmap_blocks = { &light, &shadow, &gi_trace, &lightmap };

		auto create_programs = [&]()
		{
			Program& solid = gfx.programs().create("solid");
			solid.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Solid });
			solid.register_blocks(depth_blocks);

			Program& normal = gfx.programs().create("normal");
			normal.set_blocks({ MaterialBlock::Solid });
			//normal.m_blocks[MaterialBlock::Pbr] = true;

			Program& point = gfx.programs().create("point");
			point.set_blocks({ MaterialBlock::Solid, MaterialBlock::Point });
			point.m_primitives = uint32_t(1 << uint(PrimitiveType::Points));

			Program& line = gfx.programs().create("line");
			line.set_blocks({ MaterialBlock::Solid, MaterialBlock::Line });
			line.m_primitives = uint32_t(1 << uint(PrimitiveType::Lines) | 1 << uint(PrimitiveType::LineStrip));

			Program& line_fat = gfx.programs().create("line_fat");
			line_fat.set_blocks({ MaterialBlock::Solid, MaterialBlock::Line });
			//line_fat.m_primitives = uint32_t(1 << uint(PrimitiveType::Lines) | 1 << uint(PrimitiveType::LineStrip));

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(depth_blocks);
			depth.set_blocks({ MaterialBlock::Alpha });

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(depth_blocks);
			distance.set_blocks({ MaterialBlock::Alpha });

			Program& pbr = gfx.programs().create("pbr/pbr");
			pbr.register_blocks(shading_blocks);
			pbr.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr });

			Program& lambert = gfx.programs().create("pbr/lambert");
			lambert.register_blocks(shading_blocks);
			lambert.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Phong });

			Program& phong = gfx.programs().create("pbr/phong");
			phong.register_blocks(shading_blocks);
			phong.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Phong });

			Program& three = gfx.programs().create("pbr/three");
			three.register_blocks(shading_blocks);
			three.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr });

			Program& basic = gfx.programs().create("pbr/basic");
			basic.register_blocks(shading_blocks);
			basic.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr });

			Program& geometry = gfx.programs().create("pbr/geometry");
			geometry.register_blocks(geometry_blocks);
			geometry.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr });

			Program& lights = gfx.programs().create("pbr/lights");
			lights.register_blocks(shading_blocks);

			Program& fresnel = gfx.programs().create("fresnel");
			geometry.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Fresnel });

			Program& gi_voxelize = gfx.programs().create("gi/voxelize");
			gi_voxelize.register_blocks(gi_blocks);

			Program& gi_voxel_light = gfx.programs().create("gi/direct_light");
			gi_voxel_light.m_compute = true;
			gi_voxel_light.register_blocks(gi_blocks);

			Program& gi_voxel_bounce = gfx.programs().create("gi/bounce_light");
			gi_voxel_bounce.m_compute = true;
			gi_voxel_bounce.register_blocks(gi_blocks);

			Program& gi_voxel_output = gfx.programs().create("gi/output_light");
			gi_voxel_output.m_compute = true;
			gi_voxel_output.register_blocks(gi_blocks);

			Program& lightmap = gfx.programs().create("pbr/lightmap");
			lightmap.register_blocks(lightmap_blocks);
		};

		create_programs();

		if(deferred)
			gfx.set_renderer(Shading::Shaded, render_pbr_deferred);
		else
			gfx.set_renderer(Shading::Shaded, render_pbr_forward);

		gfx.set_renderer(Shading::Volume, render_shadow);

		gfx.set_renderer(Shading::Voxels, render_voxel);

		gfx.set_renderer(Shading::Lightmap, render_lightmap);

		pipeline.m_gather_func = gather_render_pbr;

		// this (and below) seems to cause a memory corruption in emscripten
		//construct<TBuffer<Tonemap>>(type<Tonemap>());

#ifndef TWO_PLATFORM_EMSCRIPTEN
		g_viewer_ecs->init<Tonemap, BCS, Glow, DofBlur>();
#endif
	}

	struct PbrBlocks
	{
		BlockRadiance& radiance;
		BlockLight& light;
		BlockShadow& shadow;
		BlockGITrace& gi_trace;
		BlockReflection& reflection;
		BlockLightmap& lightmap;
	};

	span<DrawBlock*> pbr_blocks(GfxSystem& gfx)
	{
		static DrawBlock* blocks[] = {
			gfx.m_renderer.block<BlockRadiance>(),
			gfx.m_renderer.block<BlockLight>(),
			gfx.m_renderer.block<BlockShadow>(),
			gfx.m_renderer.block<BlockGITrace>(),
			gfx.m_renderer.block<BlockReflection>(),
			gfx.m_renderer.block<BlockLightmap>()
		};
		return blocks;
	}

	void begin_pbr_render(GfxSystem& gfx, Render& render)
	{
		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->begin_render(render);
	}

	void pbr_options(GfxSystem& gfx, Render& render, DrawElement& element)
	{
		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->options(render, element, element.m_program);
	}

	void submit_pbr_pass(GfxSystem& gfx, Render& render, const Pass& pass)
	{
		static BlockLight& block_light = *gfx.m_renderer.block<BlockLight>();
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();

		block_shadow.commit_shadows(render, render.m_camera->m_view);

		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->submit(render, pass);

		//block_pbr.submit(render, pass);
	}

	void submit_pbr_element(GfxSystem& gfx, Render& render, const DrawElement& element, Pass& pass)
	{
		static span<DrawBlock*> blocks = pbr_blocks(gfx);
		for(DrawBlock* block : blocks)
			block->submit(render, element, pass);
	}

	void render_pbr_forward(GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_gi_probes(gfx, render);
		pass_shadowmaps(gfx, render);

		//begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
#if DEPTH_PASS
		pass_depth(gfx, render);
#endif
		pass_opaque(gfx, render);
		pass_background(gfx, render);
		pass_particles(gfx, render);
		pass_alpha(gfx, render);
		pass_solid(gfx, render);
		//pass_effects(gfx, render);
		//pass_resolve(gfx, render);
		pass_post_auto(gfx, render);
	}

	void render_pbr_deferred(GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_gi_probes(gfx, render);
		pass_shadowmaps(gfx, render);
		pass_clear(gfx, render);
		pass_geometry(gfx, render);
		pass_lights(gfx, render);
		pass_background(gfx, render);
		pass_particles(gfx, render);
		//pass_alpha(gfx, render);
		pass_solid(gfx, render);
	}

	void render_shadow(GfxSystem& gfx, Render& render)
	{
		//begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
		pass_shadow(gfx, render);
	}

	void render_voxel(GfxSystem& gfx, Render& render)
	{
		//begin_pbr_render(gfx, render);

		pass_shadowmaps(gfx, render);
		pass_clear(gfx, render);
		pass_voxel_gi(gfx, render);
	}

	void render_lightmap(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_lightmap(gfx, render);
	}

	void render_reflection(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
#if DEPTH_PASS
		pass_depth(gfx, render);
#endif
		pass_opaque(gfx, render);
		pass_background(gfx, render);
		pass_particles(gfx, render);
		pass_alpha(gfx, render);
	}

	void pass_opaque(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("opaque", PassType::Opaque);

		submit_pbr_pass(gfx, render, pass);

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthAscending);

		const bool vflip = render.m_vflip && bgfx::getCaps()->originBottomLeft;
		const uint64_t cull = vflip ? BGFX_STATE_CULL_CCW : BGFX_STATE_CULL_CW;

#if DEPTH_PASS
		pass.m_bgfx_state = cull | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z 
								 | BGFX_STATE_DEPTH_TEST_EQUAL | BGFX_STATE_MSAA;
#else
		pass.m_bgfx_state = cull | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z 
								 | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_MSAA;
#endif

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(pass);
			const Program& program = *element.m_program.m_program;
			bool lit = program.m_blocks[MaterialBlock::Lit] && !element.m_material->m_alpha.m_is_alpha;
			bool opaque = program.m_passes[PassType::Opaque];
			if(!lit && !opaque) return false;

			if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			if(lit)
				pbr_options(gfx, render, element);
			return true;
		};

		auto submit_element = [](GfxSystem& gfx, Render& render, Pass& pass, const DrawElement& element)
		{
			submit_pbr_element(gfx, render, element, pass);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element, submit_element);
	}

	void pass_alpha(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("alpha", PassType::Alpha);

		submit_pbr_pass(gfx, render, pass);

		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS
							  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA;

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthDescending);

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(pass);
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Pbr] || !element.m_material->m_alpha.m_is_alpha)
				return false;

			//blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);

			pbr_options(gfx, render, element);

			return true;
		};

		auto submit_element = [](GfxSystem& gfx, Render& render, Pass& pass, const DrawElement& element)
		{
			submit_pbr_element(gfx, render, element, pass);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element, submit_element);
	}

	void pass_geometry(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		Pass pass = render.next_pass("geometry", PassType::Geometry);

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthAscending);

		const bool vflip = render.m_vflip && bgfx::getCaps()->originBottomLeft;
		const uint64_t cull = vflip ? BGFX_STATE_CULL_CCW : BGFX_STATE_CULL_CW;

		pass.m_bgfx_state = cull | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z 
								 | BGFX_STATE_DEPTH_TEST_EQUAL | BGFX_STATE_MSAA;

		pass.m_fbo = &render.m_target->m_gbuffer;

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(render); UNUSED(pass);
			const Program& program = *element.m_program.m_program;
			bool lit = program.m_blocks[MaterialBlock::Lit] && !element.m_material->m_alpha.m_is_alpha;
			bool opaque = program.m_passes[PassType::Opaque];
			if(!lit && !opaque) return false;

			if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled)
				element.m_bgfx_state |= BGFX_STATE_WRITE_Z;

			element.m_program.set_option(0, DEFERRED, true);
			return true;
		};

		auto submit_element = [](GfxSystem& gfx, Render& render, Pass& pass, const DrawElement& element)
		{
			submit_pbr_element(gfx, render, element, pass);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element, submit_element);
	}

	void pass_lights(GfxSystem& gfx, Render& render)
	{
		static Program& program = gfx.programs().fetch("pbr/lights");

		Pass pass = render.next_pass("lights", PassType::Lights);
		bgfx::Encoder& encoder = *pass.m_encoder;
		pass.m_encoder = &encoder;

		submit_pbr_pass(gfx, render, pass);

		DrawCluster cluster;
		cluster.m_lights = render.m_shot.m_lights;
		cluster.m_shader_version = { program };

		for(auto& block : gfx.m_renderer.m_gfx_blocks)
			if(block->m_draw_block)
			{
				//as<DrawBlock>(*block).options(render, cluster.m_shader_version);
				as<DrawBlock>(*block).submit(render, pass);
			}

		RenderTarget& target = *render.m_target;
		GBuffer& gbuffer = target.m_gbuffer;

		gfx.m_filter->source0(gbuffer.m_position);
		gfx.m_filter->source1(gbuffer.m_normal);
		gfx.m_filter->source2(gbuffer.m_albedo);
		gfx.m_filter->source3(gbuffer.m_surface);

		gfx.m_filter->quad(pass, *render.m_fbo, cluster.m_shader_version, BGFX_STATE_BLEND_ALPHA);

#if DEBUG_GBUFFERS
		vec2 size = vec2(target.m_size) * 0.25f;
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_depth, vec4(vec2(0.f, size.y * 0.f), size), true);
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_normal, vec4(vec2(0.f, size.y * 1.f), size));
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_albedo, vec4(vec2(0.f, size.y * 2.f), size));
		m_gfx.m_copy->debug_show_texture(render, gbuffer.m_surface, vec4(vec2(0.f, size.y * 3.f), size));
#endif
	}

	void pass_begin_post(GfxSystem& gfx, Render& render)
	{
		gfx.m_copy->quad(render.composite_pass("post begin"), render.m_target->m_post.swap(), render.m_target->m_diffuse);
	}
	
	void pass_post_auto(GfxSystem& gfx, Render& render)
	{
		Entt filters = render.m_filters;
		pass_post_effects(gfx, render, filters.comp<DofBlur>(), filters.comp<Glow>(), filters.comp<Tonemap>(), filters.comp<BCS>());
	}

	void pass_post_effects(GfxSystem& gfx, Render& render, DofBlur& dof, Glow& glow, Tonemap& tonemap, BCS& bcs)
	{
		pass_begin_post(gfx, render);

		if(dof.m_enabled)
			pass_dofblur(gfx, render, dof);

		if(glow.m_enabled)
			pass_glow(gfx, render, glow);

		if(tonemap.m_enabled || render.m_viewport->m_to_gamma)
			pass_tonemap(gfx, render, tonemap, bcs);
		else
			pass_flip(gfx, render);
	}

	BlockGeometry::BlockGeometry(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockGeometry>())
	{}

	BlockGeometry::~BlockGeometry()
	{}

	void BlockGeometry::init_block()
	{
		m_material = &m_gfx.fetch_material("geometry", "pbr/geometry");
		m_material_twosided = &m_gfx.fetch_material("geometry_twosided", "pbr/geometry");
		m_material_twosided->m_base.m_cull_mode = CullMode::None;
	}

	void BlockGeometry::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGeometry::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(program);
	}

	void BlockGeometry::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
	}

	void BlockGeometry::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

#include <cstdio>

namespace two
{
	BlockRadiance::BlockRadiance(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: DrawBlock(gfx, type<BlockRadiance>())
		, m_filter(filter)
		, m_copy(copy)
		, m_prefilter_program(gfx.programs().create("filter/prefilter_envmap"))
	{
		m_options = { "RADIANCE_ENVMAP", "RADIANCE_CUBE" };

		m_prefilter_program.register_block(filter);
		m_prefilter_program.register_block(*this);
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
		if(!render.m_env || !render.m_env->m_radiance.m_texture)
			return;

		if(!render.m_env->m_radiance.m_preprocessed && render.m_env->m_radiance.m_filter)
			m_prefilter_queue.push_back(&render.m_env->m_radiance);

#ifdef DEBUG_RADIANCE
		if(bgfx::isValid(render.m_env->m_radiance.m_filtered))
		{
			m_gfx.m_copy->debug_show_texture(render, render.m_env->m_radiance.m_filtered, vec4(0.f), false, false, false, 2);
		}
#endif
	}

	Texture* radiancemap(Radiance& radiance)
	{
		Texture* const filtered = radiance.m_filtered;
		Texture* const reflection = radiance.m_texture;
		if(filtered && filtered->valid())
			return filtered;
		else if(reflection && reflection->valid() && !radiance.m_filter)
			return reflection;
		else
			return nullptr;
	}

	void BlockRadiance::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		const bool enable = !element.m_material->m_lit.m_no_envmap;
		Texture* radiance = radiancemap(render.m_env->m_radiance);

		if(enable && radiance)
			program.set_option(m_index, RADIANCE_ENVMAP);
		if(enable && radiance && radiance->m_is_cube)
			program.set_option(m_index, RADIANCE_CUBE);
	}

	void BlockRadiance::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);
		uint32_t stage = uint32_t(TextureSampler::Radiance);
		bgfx::setViewUniform(pass.m_index, u_radiance.s_radiance, &stage);
	}

	void BlockRadiance::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(element);
		bgfx::Encoder& encoder = *pass.m_encoder;

		if(Texture* radiance = radiancemap(render.m_env->m_radiance))
			encoder.setTexture(uint8_t(TextureSampler::Radiance), *radiance);
	}

	void BlockRadiance::prefilter_radiance(Radiance& radiance)
	{
		if(m_prefiltered.find(radiance.m_texture) != m_prefiltered.end())
		{
			radiance.m_filtered = m_prefiltered[radiance.m_texture];
			radiance.m_preprocessed = true;
			return;
		}

		//if(!radiance.m_texture->valid() || radiance.m_texture->m_is_cube)
		if(!radiance.m_texture->valid())// || radiance.m_texture->m_is_cube)
			return;

		constexpr int roughness_levels = 8;

		const bool cube = radiance.m_texture->m_is_cube;
		const uvec2 size = cube
			? radiance.m_texture->m_size
			: m_gfx.main_target().m_size;

		const uint64_t flags = BGFX_TEXTURE_RT | TEXTURE_CLAMP;

		//bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA16F;
		TextureFormat format = radiance.m_texture->m_format;
		if(!bgfx::isTextureValid(1, cube, 1, bgfx::TextureFormat::Enum(format), flags))
			format = TextureFormat::RGB10A2;

		if(!bgfx::isTextureValid(1, cube, 1, bgfx::TextureFormat::Enum(format), flags))
		{
			printf("[warning] could not prefilter env map roughness levels\n");
			return;
		}

		Texture& filtered = m_gfx.textures().create(radiance.m_texture->m_name + "_filtered");
		filtered = { size, true, format, flags, cube };

		//const uint8_t view_id = Render::s_preprocess_pass_id; //render.preprocess_pass();

		auto blit_level = [&](Texture& source, const uvec2& size, int level, int face = 0)
		{
			const uvec2 level_size = uvec2(size.x >> level, size.y >> level);
			bgfx::Attachment attach = { bgfx::Access::Write, filtered, uint16_t(level), uint16_t(face), BGFX_RESOLVE_NONE };
			FrameBuffer render_target = { level_size, filtered, { attach } }; // @todo fix ownership
			m_copy.submit(Pass(), render_target, source, RenderQuad());
			bgfx::frame();
		};

		const uint16_t num_faces = cube ? 6 : 1;

		for(uint16_t i = 0; i < roughness_levels; i++)
		{
			const uvec2 level_size = uvec2(size.x >> i, size.y >> i);
			FrameBuffer target = { level_size, format, TEXTURE_POINT };

			for(uint16_t face = 0; face < num_faces; ++face)
			{
				ProgramVersion program = { m_prefilter_program };

				const int source_level = i == 0 ? 0 : i - 1;
				Texture& source = i == 0 ? *radiance.m_texture : filtered;
				m_filter.source0p(source, program, source_level, TEXTURE_POINT);

				float roughness = i / float(roughness_levels - 1);
#ifdef TWO_PLATFORM_EMSCRIPTEN
				constexpr uint num_samples = 64;
#else
				constexpr uint num_samples = 512;
#endif
				const vec4 prefilter_p0 = { roughness, float(num_samples), 0.f, 0.f };
				bgfx::setUniform(u_prefilter.u_prefilter_envmap_p0, &prefilter_p0);

				if(cube)
				{
					constexpr vec3 up[6] = { Y3, Y3, -Z3, Z3, Y3, Y3 };
					constexpr vec3 dir[6] = { X3, -X3, Y3, -Y3, Z3, -Z3 };

					const mat4 cubemat = bxlookat(vec3(0.f), vec3(0.f) + dir[face], up[face]);
					bgfx::setUniform(u_prefilter.u_prefilter_cube, &cubemat);
				}

				m_filter.submit(Pass(), target, program, RenderQuad(), 0U, true);

				blit_level(target.m_tex, size, i, face);
			}
		}

		m_prefiltered[radiance.m_texture] = &filtered;
		radiance.m_filtered = &filtered;
		radiance.m_preprocessed = true;
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

namespace two
{
	ReflectionAtlas::ReflectionAtlas(uint16_t size, uint16_t subdiv)
		: m_size(size)
		, m_subdiv(subdiv)
	{
#if 0 // @todo: crashes in D3D11
		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, true, 1, color_format, TEXTURE_CLAMP))
			color_format = bgfx::TextureFormat::RGB10A2;

		m_color = bgfx::createTextureCube(size, true, 1, color_format, TEXTURE_CLAMP);

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

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

namespace two
{
	constexpr size_t BlockReflection::ReflectionUniform::max_reflection_probes;

	ReflectionProbe::ReflectionProbe(Node3& node)
		: m_node(node)
	{}

	void CubeTarget::create(uint32_t size)
	{
		m_size = size;

		const uint64_t flags = BGFX_TEXTURE_RT | TEXTURE_CLAMP3 | TEXTURE_POINT;
		TextureFormat color_format = TextureFormat::RGBA16F;
		if(!bgfx::isTextureValid(0, true, 1, bgfx::TextureFormat::Enum(color_format), flags))
			color_format = TextureFormat::RGB10A2;

		m_cubemap = { uvec2(size), false, color_format, flags, true };
		m_depth = { uvec2(size), false, TextureFormat::D24S8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_DEPTH };

		m_cubemap.m_is_fbo = true;
		m_depth.m_is_fbo = true;

		for(int i = 0; i < 6; i++)
		{
			bgfx::Attachment attachments[2] =
			{
				{ bgfx::Access::Write, m_depth , 0, 1, BGFX_RESOLVE_AUTO_GEN_MIPS },
				{ bgfx::Access::Write, m_cubemap, 0, uint16_t(i), BGFX_RESOLVE_AUTO_GEN_MIPS }
			};
			m_fbos[i] = { uvec2(size), m_cubemap, attachments };
		}
	}

	CubeCamera::CubeCamera(Scene& scene, float near, float far, uint32_t size)
		: m_size(size)
	{
		m_cubemap.create(size);

		// up stays up for all sides of the cube except when looking down (where it's forward aka -Z) or up (back aka Z)
		const table<SignedAxis, vec3> up = { { Y3, Y3, -Z3, Z3, Y3, Y3 } };
		// cubemaps are stored in left-handed space, so we need to flip X with -X both when rendering and when sampling cubemaps
		const table<SignedAxis, vec3> dir = { { -X3, X3, Y3, -Y3, Z3, -Z3 } };

		const float fov = 90.f; const float aspect = 1.f;

		for(SignedAxis axis : c_signed_axes)
		{
			size_t i = size_t(axis);
			m_cameras[i] = Camera(vec3(0.f), dir[axis], up[axis], fov, aspect, near, far);
			m_viewports[i] = Viewport(m_cameras[i], scene, Rect4);
		}
	}

	Render CubeCamera::render(GfxSystem& gfx, Render& render, SignedAxis axis)
	{
		Render probe_render = { Shading::Shaded, m_viewports[size_t(axis)], *render.m_target, m_cubemap.m_fbos[size_t(axis)], *render.m_frame };
		probe_render.m_vflip = true;

		//probe_render.m_shot.m_lights = render.m_shot.m_lights;
		//probe_render.m_shot.m_items = render.m_shot.m_items;

		return probe_render;
	}

	void CubeCamera::render(GfxSystem& gfx, Render& render, RenderFunc renderer)
	{
		//var generateMipmaps = renderTarget.texture.generateMipmaps;

		//renderTarget.texture.generateMipmaps = false;

		for(SignedAxis axis : c_signed_axes)
		{
			//if(axis == SignedAxis(5))
			//	renderTarget.texture.generateMipmaps = generateMipmaps;

			Render probe_render = this->render(gfx, render, axis);
			gfx.m_renderer.gather(probe_render);
			gfx.m_renderer.subrender(render, probe_render, renderer);
		}
	}

	void CubeCamera::clear(GfxSystem& gfx, Render& render, Colour color, float depth, uint8_t stencil)
	{
		for(SignedAxis axis : c_signed_axes)
		{
			//renderer.setRenderTarget(renderTarget, i);
			//renderer.clear(color, depth, stencil);
		}
	}

	BlockReflection::BlockReflection(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockReflection>())
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

	void BlockReflection::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(program);
	}

	void BlockReflection::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);
		//uint32_t stage = uint32_t(TextureSampler::ReflectionProbe);
		//bgfx::setViewUniform(pass.m_index, u_uniform.s_atlas, &stage);
	}

	void BlockReflection::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element);
		bgfx::Encoder& encoder = *pass.m_encoder;

		if(m_atlas.m_color.valid() && m_atlas.m_size > 0)
			encoder.setTexture(uint8_t(TextureSampler::ReflectionProbe), m_atlas.m_color);

		//upload_reflection_probes(render, to_array(render.m_shot.m_reflection_probes));
	}

	void BlockReflection::upload_reflection_probes(Render& render, Pass& pass, span<ReflectionProbe*> probes)
	{
		bgfx::Encoder& encoder = *pass.m_encoder;
		mat4 view_matrix = inverse(render.m_camera->m_view);

		ReflectionProbeArray<16> probe_array;

		uint16_t probe_count = 0;

		for(ReflectionProbe* probe : probes)
		{
			//probe->m_last_pass = render.m_pass_index;

			probe_array.extents_intensity[probe_count] = { probe->m_extents, probe->m_intensity };

			Colour ambient_linear = to_linear(render.m_env->m_radiance.m_ambient);
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

	CubeTarget& BlockReflection::find_cubemap(uint16_t size)
	{
		for(CubeTarget& cubemap : m_cubemaps)
			if(cubemap.m_size > size * 2)
				return cubemap;
		return m_cubemaps[0];
	}

	void BlockReflection::render_reflection_probe(Render& render, ReflectionProbe& probe)
	{
		static const vec3 view_normal[6] = { -X3,  X3, -Y3,  Y3, -Z3,  Z3 };
		static const vec3 view_up[6] = { -Y3, -Y3, -Z3,  Z3, -Y3, -Y3 };

		uvec4 atlas_rect = m_atlas.render_update(render, probe);

		CubeTarget& cubemap = find_cubemap(uint16_t(atlas_rect.width));

		for(int i = 0; i < 6; ++i)
		{
			const vec3 edge = view_normal[i] * probe.m_extents;
			const float range = abs(dot(view_normal[i], edge));

			const mat4 transform = probe.m_node.m_transform * bxlookat(vec3(0.f), view_normal[i], view_up[i]);
			const mat4 projection = bxproj(90.f, 1.f, 0.01f, range, bgfx::getCaps()->homogeneousDepth);

			Camera camera = Camera(transform, projection);
			Viewport viewport = Viewport(camera, *render.m_scene, Rect4);
			Render probe_render = { Shading::Volume, viewport, *render.m_target, cubemap.m_fbos[i], *render.m_frame };
			//probe_render.cull();
			m_gfx.m_renderer.subrender(render, probe_render, m_gfx.renderer(Shading::Shaded));
		}
	}

	void pass_probes(GfxSystem& gfx, Render& render)
	{
		static BlockReflection& block_reflection = *gfx.m_renderer.block<BlockReflection>();

		Pass pass = render.next_pass("probes", PassType::Probes);

		block_reflection.m_reflection_multiplier = 1.f;

#if 0
		for(ReflectionProbe* probe : render.m_shot.m_reflection_probes)
		{
			if(!probe->m_dirty)
				continue;

			m_block_reflection.render_reflection_probe(render, *probe);
			//prefilter_reflection_probe(*probe);
		}
#endif

		block_reflection.m_reflection_multiplier = 0.f;
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

#include <cstdio>

#define DEBUG_ATLAS 0

namespace two
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

		slice.m_proj = crop_shrink_light_proj(light, slice.m_light_bounds, light_proj, float(csm_size));
		slice.m_transform = light_transform;

		mat4 crop_matrix = rect_mat(slice.m_rect) * bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, bgfx::getCaps()->homogeneousDepth);
		slice.m_shadow_matrix = crop_matrix * slice.m_proj * slice.m_transform;

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
			m_depth = { size, false, TextureFormat::D24S8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_DEPTH };
			m_fbo = { m_depth };
		}
		else if(method == DepthMethod::Distance)
		{
			m_color = { size, false, TextureFormat::RGBA8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_POINT };
			m_fbo = { m_color };
		}
	}

	void ShadowmapCube::create(uint32_t size)
	{
		const uint64_t flags = BGFX_TEXTURE_RT | TEXTURE_CLAMP3 | TEXTURE_DEPTH;
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
		m_options = { "SHADOWS", "CSM_BLEND" };
		m_modes = { "PCF_LEVEL" };

		//m_pcf_level = PCF_HARD;
		m_pcf_level = PCF_NONE;
	}

	void BlockShadow::init_block()
	{
		u_shadow.createUniforms();

		GpuState<GpuShadow>::me.init();
	}

	void BlockShadow::begin_frame(const RenderFrame& frame)
	{
		m_atlas.begin_frame(frame);
	}

	void BlockShadow::begin_render(Render& render)
	{
		UNUSED(render);

		for(Light* light : render.m_shot.m_lights)
			if(light->m_shadows)
			{
				if(m_atlas.m_side == 0)
					m_atlas = { 1024U, 4U };

				m_atlas.render_update(render, *light);
			}

		this->setup_shadows(render);

#if DEBUG_ATLAS
		m_gfx.m_copy->debug_show_texture(render, m_atlas.m_depth, vec4(0.f));
		//m_gfx.m_copy->debug_show_texture(render, m_atlas.m_color, vec4(0.f));
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
				if(light.m_shadow_index.slice == UINT8_MAX)
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
					shadow.m_proj = projection;
					//shadow.m_light_bounds = 

					shadow.m_items = render.m_shot.m_items;
					cull_shadow_render(render, shadow.m_items, shadow.m_proj, shadow.m_transform);

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

				shadow.m_proj = bxproj(light.m_spot_angle * 2.f, 1.f, 0.01f, light.m_range, bgfx::getCaps()->homogeneousDepth);
				shadow.m_transform = light.m_node->m_transform;

				shadow.m_items = render.m_shot.m_items;
				cull_shadow_render(render, shadow.m_items, shadow.m_proj, shadow.m_transform);

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

	void BlockShadow::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render);

		program.set_mode(m_index, PCF_LEVEL, uint8_t(m_pcf_level));

		const bool shadows = !m_csm_shadows.empty() || !m_shadows.empty();
		program.set_option(m_index, SHADOWS, shadows);

		//if(direct && light->m_shadows)
		//{
		//	program.set_option(m_index, CSM_SHADOW);
		//	//program.set_option(m_index, CSM_BLEND, light->m_shadow_blend_splits);
		//}
	}

	void BlockShadow::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render);

		this->upload_shadows(render, pass);

		uint32_t shadow_atlas = uint32_t(TextureSampler::Shadow);
		bgfx::setViewUniform(pass.m_index, u_shadow.s_shadow_atlas, &shadow_atlas);

		if(true) //direct && light->m_shadows)
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
		uint32_t shadow_flags = shadow_sampler ? BGFX_SAMPLER_COMPARE_LESS : TEXTURE_POINT;

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
			Camera camera = Camera(shadow.m_transform, shadow.m_proj);
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
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Lit] || element.m_material->m_alpha.m_is_alpha)
				return false;
			
			return queue_depth(gfx, render, pass, element);
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

#include <cstdio>

namespace two
{
	ShadowAtlas::ShadowAtlas(uint16_t size, uint8_t num_slices)
		: m_side(size)
		, m_size(size * num_slices, size)
	{
		m_depth = { m_size, false, TextureFormat::D24S8, BGFX_TEXTURE_RT | TEXTURE_CLAMP | TEXTURE_DEPTH };
		m_color = { m_size, false, TextureFormat::RGBA8, BGFX_TEXTURE_RT | TEXTURE_CLAMP };
		m_fbo = { m_size, { &m_depth, &m_color } };

		const float fraction = 1.f / float(num_slices);
		for(uint8_t i = 0; i < num_slices; ++i)
		{
			m_slices.push_back({ i, uvec2(uint(m_side)), vec4(float(i) * fraction, 0.f, fraction, 1.f) });
		}
	}

	ShadowAtlas::Slot& ShadowAtlas::light_slot(Light& light)
	{
		Slice& slice = m_slices[light.m_shadow_index.slice];
		return slice.m_slots[light.m_shadow_index.slot];
	}

	ShadowAtlas::Slice& ShadowAtlas::light_slice(Light& light)
	{
		return m_slices[light.m_shadow_index.slice];
	}

	ShadowAtlas::Slice::Slice(uint8_t index, const uvec2& size, const vec4& rect)
		: m_index(index)
		, m_size(size)
		, m_rect(rect)
	{}

	void ShadowAtlas::begin_frame(const RenderFrame& frame)
	{
		for(Slice& slice : m_slices)
			for(uint32_t i = 0; i < slice.m_slots.size(); ++i)
			{
				Slot& slot = slice.m_slots[i];
				if(slot.m_light && slot.m_frame < frame.m_frame-1)
					this->yield(slice, i);
			}
	}

	void ShadowAtlas::subdiv(Slice& slice, uint16_t subdiv)
	{
		slice.m_subdiv = subdiv;
		slice.m_slot_size = m_size / uvec2(uint(subdiv));

		const vec2 slot_size = vec2(slice.m_rect.size) / float(subdiv);
		const vec2 coord = slice.m_rect.pos;

		slice.m_slots.clear();
		slice.m_free_slots.clear();
		slice.m_free_blocks.clear();

		auto at = [&](uint x, uint y) -> uint32_t { return x + y*subdiv; };

		uint16_t i = 0;
		for(uint16_t y = 0; y < subdiv; ++y)
			for(uint16_t x = 0; x < subdiv; ++x)
			{
				vec4 slot_rect = { coord + vec2(x, y) * slot_size, slot_size };
				uvec4 slot_trect = uvec4(slot_rect * vec2(m_size));

				slice.m_slots.push_back({ i++, nullptr, slot_rect, slot_trect });

				bool at_block = x % 4 == 0 && y % 2 == 0;
				bool has_space = subdiv - x >= 4 && subdiv - y >= 2;
				if(at_block && has_space)
				{
					Block block = { { at(x+0, y+0), at(x+1, y+0), at(x+2, y+0), at(x+3, y+0),
									  at(x+0, y+1), at(x+1, y+1), at(x+2, y+1), at(x+3, y+1) } };
					slice.m_slots.back().m_block = slice.m_blocks.size();
					slice.m_blocks.push_back(block);
				}
			}

		// @todo change to high water mark + free list under water mark
		for(uint32_t i = 0; i < slice.m_slots.size(); ++i)
		{
			slice.m_free_slots.push_back(i);
		}

		for(uint32_t i = 0; i < slice.m_blocks.size(); ++i)
		{
			slice.m_free_blocks.push_back(i);
		}
	}

	ShadowAtlas::Slot& ShadowAtlas::alloc(Slice& slice, bool block6)
	{
		assert((block6 && !slice.m_free_blocks.empty()) || (!block6 && !slice.m_free_slots.empty()));
		uint32_t index = block6 ? pop(slice.m_free_blocks) : pop(slice.m_free_slots);
		if(block6)
		{
			Block& block = slice.m_blocks[index];
			remove_if(slice.m_free_slots, [&](uint32_t slot) { for(size_t i = 0; i < 6; ++i) if(block.m_slots[i] == slot) return true; return false; });
			index = block.m_slots[0];
		}
		return slice.m_slots[index];
	}

	void ShadowAtlas::yield(Slice& slice, uint32_t index)
	{
		Slot& slot = slice.m_slots[index];
		slot.m_light = nullptr;
		if(slot.m_block != UINT16_MAX)
		{
			Block& block = slice.m_blocks[slot.m_block];
			slice.m_free_blocks.push_back(slot.m_block);
			for(size_t i = 0; i < 6; ++i)
				slice.m_free_slots.push_back(block.m_slots[i]);
		}
		else
		{
			slice.m_free_slots.push_back(index);
		}

	}
	void ShadowAtlas::remove_light(Light& light, bool block)
	{
		Slice& slice = m_slices[light.m_shadow_index.slice];
		this->yield(slice, light.m_shadow_index.slot);
	}

	bool ShadowAtlas::update_light(Light& light, uint32_t frame, float coverage, uint32_t light_version)
	{
		UNUSED(light_version);

		if(light.m_type == LightType::Point)
			coverage /= 4.f;
			//coverage /= 6.f;

		if(light.m_shadow_index.slice != UINT8_MAX)
		{
			Slice& slice = m_slices[light.m_shadow_index.slice];
			Slot& slot = slice.m_slots[light.m_shadow_index.slot];
			slot.m_frame = frame;
			const float space = 1.f / float(slice.m_subdiv);
			if(space >= coverage) return false;
			this->remove_light(light, true);
		}

		//printf("looking for a shadow atlas slot of size %i\n", int(target_size));

		auto find_slice = [&]() -> Slice*
		{
			for(Slice& slice : m_slices)
			{
				const float space = 1.f / float(slice.m_subdiv);
				if(space < coverage)
				{
					printf("atlas slice %i subdiv %i can't hold light with coverage %.2f space %.2f\n", slice.m_index, slice.m_subdiv, coverage, space);
					continue;
				}
				if(light.m_type == LightType::Point && !slice.m_free_blocks.empty())
					return &slice;
				else if(light.m_type != LightType::Point && !slice.m_free_slots.empty())
					return &slice;
			}
			return nullptr;
		};

		auto setup_slice = [&]() -> Slice*
		{
			for(Slice& slice : m_slices)
				if(slice.m_subdiv == 0)
				{
					// slice isn't used yet, so we can subdivide it to whatever size we need
					uint16_t subdiv = next_pow2(uint16_t(1.f / coverage));
					this->subdiv(slice, subdiv);
					return &slice;
				}
			return nullptr;
		};

		Slice* slice = find_slice();
		if(slice == nullptr)
			slice = setup_slice();

		if(slice != nullptr)
		{
			Slot& slot = this->alloc(*slice, light.m_type == LightType::Point);
			slot.m_light = &light;
			slot.m_frame = frame;
			light.m_shadow_index = { slice->m_index, slot.m_index };
			return true;
		}

		return false;
	}

	vec4 ShadowAtlas::render_update(Render& render, Light& light)
	{
		if(light.m_type == LightType::Direct)
		{
			// direct light has full coverage (1.0)
			const bool redraw = this->update_light(light, render.m_frame->m_frame, 1.f, light.m_last_update);
			UNUSED(redraw);
			return this->light_slot(light).m_rect;
		}

		const Plane camera_near_plane = render.m_camera->near_plane();

		vec3 points[2];

		const Node3& node = *light.m_node;
		if(light.m_type == LightType::Point)
		{
			points[0] = node.position();
			points[1] = node.position() + node.axis(X3) * light.m_range;
		}
		else if(light.m_type == LightType::Spot)
		{
			const float w = light.m_range * sin(light.m_spot_angle);
			const float d = light.m_range * cos(light.m_spot_angle);

			const vec3 base = light.m_node->position() + node.direction() * d;

			points[0] = base;
			points[1] = base + node.axis(X3) * w;
		}

		if(!render.m_camera->m_orthographic)
		{
			for(int j = 0; j < 2; j++)
			{
				if(distance(camera_near_plane, points[j]) < 0.f)
					points[j].z = -render.m_camera->m_near; //small hack to keep size constant when hitting the screen

				points[j] = plane_segment_intersection(camera_near_plane, { node.position(), points[j] });
			}
		}

		const vec2 size = frustum_viewport_size(render.m_camera->m_proj);

		const float diameter = distance(points[0], points[1]) * 2.f;
		const float coverage = diameter / (size.x + size.y);

		//if(light.m_shadow_dirty) // updated when lights and objects bounds start or stop intersecting, or move
		//{
		//	light.m_last_version++;
		//	light.m_shadow_dirty = false;
		//}

		// @todo fix coverage calculation
		const bool redraw = this->update_light(light, render.m_frame->m_frame, 1.f, light.m_last_update);
		//const bool redraw = this->update_light(light, render.m_frame->m_frame, min(coverage, 1.f), light.m_last_update);
		UNUSED(redraw);
		return this->light_slot(light).m_rect;
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

namespace two
{
}


#include <bgfx/bgfx.h>
#include <xatlas.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <stl/algorithm.h>
#endif

#include <cstdio>

#define LIGHTMAP_XATLAS

namespace two
{
	GpuState<GpuVoxelGI> GpuState<GpuVoxelGI>::me;
	GpuState<GIProbe> GpuState<GIProbe>::me;

namespace gfx
{
	template <class T, class... Args>
	inline T& create(Scene& scene, Args&&... args)
	{
		return scene.m_pool->pool<T>().construct(static_cast<Args&&>(args)...);
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

	struct gpu_ GpuGIProbe
	{
		attr_ gpu_ mat4 transform;
		attr_ gpu_ vec4 params;
		attr_ gpu_ vec4 bounds;
		attr_ gpu_ vec4 inv_extents;
		attr_ gpu_ vec4 cell_size;
	};

	GIProbe::GIProbe(Node3& node)
		: m_node(node)
	{}

	GIProbe::~GIProbe()
	{}

	void GIProbe::resize(uint16_t subdiv, const vec3& extents)
	{
		m_transform = bxidentity();
		m_subdiv = subdiv;
		m_extents = extents;

		m_normal_bias = length(extents * 2.f / float(subdiv)) * sqrt(2.f) * 2.f;

		m_raster = { uvec2(uint(subdiv)), false, TextureFormat::RGBA8, BGFX_TEXTURE_RT };
		m_voxels_color   = { uvec3(uint(subdiv)), false, TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE };
		m_voxels_normals = { uvec3(uint(subdiv)), false, TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE };
		m_voxels_light   = { uvec3(uint(subdiv)), false, TextureFormat::R32U, BGFX_TEXTURE_COMPUTE_WRITE };

		m_fbo = { uvec2(subdiv, subdiv), { &m_raster, &m_voxels_color, &m_voxels_normals, &m_voxels_light } };
		
		m_voxels_light_rgba = { uvec3(uint(subdiv)), true, TextureFormat::RGBA16F, BGFX_TEXTURE_RT | BGFX_TEXTURE_COMPUTE_WRITE };

		m_dirty = true;
	}

	void save_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, bgfx::TextureFormat::Enum source_format, bgfx::TextureFormat::Enum target_format, const string& path)
	{
		const uint16_t subdiv = gi_probe.m_subdiv;
		Texture texture = { uvec3(subdiv, subdiv, subdiv), true, TextureFormat(source_format), BGFX_TEXTURE_BLIT_DST | BGFX_TEXTURE_READ_BACK };
		bgfx::blit(0, texture, 0, 0, 0, 0, gi_probe.m_voxels_light_rgba, 0, 0, 0, 0, subdiv, subdiv, subdiv);
		bgfx::frame();
		bgfx::frame();

		save_bgfx_texture(gfx, path, target_format, texture, source_format, subdiv, subdiv, subdiv);
	}

	void load_gi_probe(GfxSystem& gfx, GIProbe& gi_probe, const string& path)
	{
		gi_probe.m_voxels_light_rgba = { "voxels" };
		load_texture(gfx, gi_probe.m_voxels_light_rgba, path);
	}

	void pass_voxel_gi(GfxSystem& gfx, Render& render)
	{
		static BlockLight& block_light = *gfx.m_renderer.block<BlockLight>();
		static BlockShadow& block_shadow = *gfx.m_renderer.block<BlockShadow>();
		static BlockGIBake& block_gi_bake = *gfx.m_renderer.block<BlockGIBake>();

		Pass pass = render.next_pass("voxelGI", PassType::VoxelGI);

		block_light.submit(render, pass);
		block_shadow.submit(render, pass);
		block_gi_bake.submit(render, pass);

		bool conservative = (bgfx::getCaps()->supported & BGFX_CAPS_CONSERVATIVE_RASTER) != 0;
		if(!conservative)
			printf("[warning] rendering GI probe without conservative raster support will produce wrong output\n");

		UNUSED(render); UNUSED(pass);
		pass.m_bgfx_state = BGFX_STATE_CONSERVATIVE_RASTER | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA;

#ifndef VOXELGI_COMPUTE_LIGHTS
		GIProbe& gi_probe = *block_gi_bake.m_bake_probe; UNUSED(gi_probe);
		mat4 view = bxidentity();//gi_probe.m_transform * bxscale(1.f / gi_probe.m_extents);
		block_light.setup_lights(render, view);
		block_shadow.commit_shadows(render, view);
#endif

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(render);
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Lit])
				return false;

			element.set_program(*block_gi_bake.m_voxelize);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

	void pass_gi_probes(GfxSystem& gfx, Render& render)
	{
		static BlockGIBake& block_gi_bake = *gfx.m_renderer.block<BlockGIBake>();

		if(!check_lighting(render.m_lighting, Lighting::VoxelGI))
			return;

		for(GIProbe* gi_probe : render.m_shot.m_gi_probes)
		{
			if(!gi_probe->m_enabled || !gi_probe->m_dirty)
				continue;

			if(gi_probe->m_mode == GIProbeMode::Voxelize)
			{
				printf("[info] bake GIProbe\n");

				block_gi_bake.voxelize(render, *gi_probe);
				block_gi_bake.output(render, *gi_probe);

				for(int i = 0; i < gi_probe->m_bounces; ++i)
				{
					// @todo fix D3D bounce bug
					block_gi_bake.bounce(render, *gi_probe);
					block_gi_bake.output(render, *gi_probe);
				}

				gi_probe->m_dirty = false;

				printf("[info] bake GIProbe done\n");

				//string path = m_gfx.m_resource_path + "/" + "gi_probe.dds";
				//save_gi_probe(m_gfx, *gi_probe, bgfx::TextureFormat::RGBA16F, bgfx::TextureFormat::BC6H, path);
			}

			if(gi_probe->m_mode == GIProbeMode::LoadVoxels)
			{
				string path = gfx.m_resource_path + "/" + "gi_probe.dds";
				load_gi_probe(gfx, *gi_probe, path);
			}
		}
	}

	BlockGIBake::BlockGIBake(GfxSystem& gfx, BlockLight& block_light, BlockShadow& block_shadow, BlockGITrace& block_trace)
		: DrawBlock(gfx, type<BlockGIBake>())
		, m_block_light(block_light)
		, m_block_shadow(block_shadow)
		, m_block_trace(block_trace)
	{}

	void BlockGIBake::init_block()
	{
		u_voxelgi.createUniforms();

		m_voxelize = &m_gfx.programs().fetch("gi/voxelize");
		m_direct_light = &m_gfx.programs().fetch("gi/direct_light");
		m_bounce_light = &m_gfx.programs().fetch("gi/bounce_light");
		m_output_light = &m_gfx.programs().fetch("gi/output_light");
	}

	void BlockGIBake::voxelize(Render& render, GIProbe& gi_probe)
	{
		m_bake_probe = &gi_probe;

		vec3 extents = gi_probe.m_extents;
		
		Camera camera = { gi_probe.m_transform, vec2(extents.x * 2.f, extents.y * 2.f), -extents.z, extents.z };
		Viewport viewport = { camera, *render.m_scene, Rect4 };
		Render voxel_render = { Shading::Voxels, viewport, *render.m_target, gi_probe.m_fbo, *render.m_frame };

		ShadowFilterMode pcf_level = m_block_shadow.m_pcf_level;
		//uint8_t splits = 0;
		m_block_shadow.m_pcf_level = PCF_NONE;
		//if(m_block_light.m_direct_light)
		//{
		//	splits = m_block_light.m_direct_light->m_shadow_num_splits;
		//	m_block_light.m_direct_light->m_shadow_num_splits = 1;
		//}

		Plane6 planes = frustum_planes(camera.m_proj, camera.m_view);
		voxel_render.m_shot.m_lights = render.m_shot.m_lights;
		cull_items(*render.m_scene, planes, voxel_render.m_shot.m_items);
		m_gfx.m_renderer.subrender(render, voxel_render, m_gfx.renderer(Shading::Voxels));

		//if(m_block_light.m_direct_light)
		//{
		//	m_block_light.m_direct_light->m_shadow_num_splits = splits;
		//}
		m_block_shadow.m_pcf_level = pcf_level;

		if(m_direct_light_compute)
			this->compute(render, gi_probe);
	}

	void BlockGIBake::compute(Render& render, GIProbe& gi_probe)
	{
		Pass pass = render.next_pass("gi direct", PassType::VoxelGI);
		bgfx::Encoder& encoder = *pass.m_encoder;

		encoder.setImage(0, u_voxelgi.s_voxels_albedo,  gi_probe.m_voxels_color,   0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(1, u_voxelgi.s_voxels_normals, gi_probe.m_voxels_normals, 0, bgfx::Access::Read,      bgfx::TextureFormat::R32U);
		encoder.setImage(2, u_voxelgi.s_voxels_light,   gi_probe.m_voxels_light,   0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);

		GpuState<GpuVoxelGI>::me.upload(encoder, gi_probe);

		m_block_light.setup_lights(render, bxidentity());
		m_block_light.commit_lights(render, pass);
		m_block_shadow.commit_shadows(render, bxidentity());

		ProgramVersion program = { *m_direct_light };

		uint16_t subdiv = gi_probe.m_subdiv;
		if(bgfx::isValid(m_direct_light->version(program)))
			encoder.dispatch(pass.m_index, m_direct_light->version(program), subdiv / 64, subdiv, subdiv);
	}
	
	void BlockGIBake::bounce(Render& render, GIProbe& gi_probe)
	{
		Pass pass = render.next_pass("gi bounce", PassType::VoxelGI);
		bgfx::Encoder& encoder = *pass.m_encoder;

		encoder.setImage(0,   u_voxelgi.s_voxels_normals,    gi_probe.m_voxels_normals,    0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		//encoder.setImage(1,   u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::Read,  bgfx::TextureFormat::R32U);
		encoder.setTexture(1, u_voxelgi.s_voxels_light_rgba, gi_probe.m_voxels_light_rgba);
		encoder.setImage(2,   u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::Write, bgfx::TextureFormat::R32U);

		GpuState<GpuVoxelGI>::me.upload(encoder, gi_probe);
		GpuState<GIProbe>::me.upload(encoder, gi_probe, bxidentity());

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_bounce_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(pass.m_index, program, subdiv / 64, subdiv, subdiv);
	}

	void BlockGIBake::output(Render& render, GIProbe& gi_probe)
	{
		Pass pass = render.next_pass("output light", PassType::VoxelGI);
		bgfx::Encoder& encoder = *pass.m_encoder;

		encoder.setImage(0, u_voxelgi.s_voxels_light,      gi_probe.m_voxels_light,      0, bgfx::Access::ReadWrite, bgfx::TextureFormat::R32U);
		encoder.setImage(1, u_voxelgi.s_voxels_light_rgba, gi_probe.m_voxels_light_rgba, 0, bgfx::Access::ReadWrite, bgfx::TextureFormat::RGBA16F);

		uint16_t subdiv = gi_probe.m_subdiv;
		bgfx::ProgramHandle program = m_output_light->default_version();
		if(bgfx::isValid(program))
			encoder.dispatch(pass.m_index, program, subdiv / 64, subdiv, subdiv);
	}

	void BlockGIBake::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGIBake::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(program);
	}

	void BlockGIBake::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
	}

	void BlockGIBake::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element);

		bgfx::Encoder& encoder = *pass.m_encoder;

		GIProbe& gi_probe = *m_bake_probe;

		int voxels_albedo_index  = 1;
		int voxels_normals_index = 2;
		int voxels_light_index   = 3;
		encoder.setUniform(u_voxelgi.s_voxels_albedo,  &voxels_albedo_index);
		encoder.setUniform(u_voxelgi.s_voxels_normals, &voxels_normals_index);
		encoder.setUniform(u_voxelgi.s_voxels_light,   &voxels_light_index);

		GpuState<GpuVoxelGI>::me.upload(encoder, gi_probe);

#ifndef VOXELGI_COMPUTE_LIGHTS
		m_block_light.commit_lights(render, pass);
#endif
	}

	BlockGITrace::BlockGITrace(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockGITrace>())
	{
		m_options = { "GI_CONETRACE" };
	}

	void BlockGITrace::init_block()
	{
		u_gi_probe.createUniforms();
	}

	void BlockGITrace::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockGITrace::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		for(GIProbe* gi_probe : render.m_shot.m_gi_probes)
			if(gi_probe->m_enabled)
			{
				program.set_option(m_index, GI_CONETRACE, true);
			}
	}

	void BlockGITrace::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
		//uint32_t stage = uint32_t(TextureSampler::GIProbe);
		//bgfx::setViewUniform(pass.m_index, u_gi_probe.s_gi_probe, &stage);
	}

	void BlockGITrace::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);

		bgfx::Encoder& encoder = *pass.m_encoder;

		uint8_t index = 0;
		for(GIProbe* gi_probe : render.m_shot.m_gi_probes)
		{
			if(gi_probe->m_enabled)
			{
				encoder.setTexture(uint8_t(TextureSampler::GIProbe) + index++, gi_probe->m_voxels_light_rgba, TEXTURE_CLAMP3);

				GpuState<GIProbe>::me.upload(encoder, *gi_probe, render.m_camera->m_view);
			}

			return;
		}
	}

	void BlockGITrace::upload_gi_probes(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);

		//bgfx::Encoder& encoder = *pass.m_encoder;
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

namespace two
{
	BlockBlur::BlockBlur(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/gaussian_blur"))
	{
		m_options = { "GAUSSIAN_HORIZONTAL", "GAUSSIAN_VERTICAL" };
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

	void BlockBlur::blur(Render& render, RenderTarget& target)
	{
		static BlurKernel kernel = {
			{ 0.214607f, 0.189879f, 0.157305f, 0.071303f, 0.189879f, 0.157305f, 0.071303f },
			{ 0.38774f, 0.24477f, 0.06136f, 0.24477f, 0.06136f }
		};

		for(uint8_t i = 0; i < 4; ++i)//target.m_effects.m_num_mips; i++)
		{
			gaussian_pass(render, target, render.m_rect, i, true, kernel);
			gaussian_pass(render, target, render.m_rect, i, false, kernel);
		}
	}

	void BlockBlur::gaussian_pass(Render& render, RenderTarget& target, const vec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel)
	{
		Texture& source = target.m_ping_pong.last();
		FrameBuffer& fbo = target.m_ping_pong.swap();

		Pass blur_pass = render.composite_pass("blur", fbo, rect);
		vec4 blur_p0 = { float(lod), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_blur_p0, &blur_p0);

		bgfx::setUniform(u_uniform.u_blur_kernel_0_3, horizontal ? &kernel.m_horizontal[0] : &kernel.m_vertical[0]);
		bgfx::setUniform(u_uniform.u_blur_kernel_4_7, horizontal ? &kernel.m_horizontal[4] : &kernel.m_vertical[4]);

		ProgramVersion program = { m_program };
		program.set_option(m_index, uint8_t(horizontal ? GAUSSIAN_HORIZONTAL : GAUSSIAN_VERTICAL), true);

		m_filter.source0(source);

		m_filter.submit(blur_pass, fbo, program, RenderQuad(rect, true));
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

namespace two
{
	GpuState<DofBlur> GpuState<DofBlur>::me;

	BlockDofBlur::BlockDofBlur(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/dof_blur"))
	{
		m_options = { "DOF_FIRST_PASS" };
		m_program.register_block(*this);
	}

	void BlockDofBlur::init_block()
	{
		GpuState<DofBlur>::me.init();
	}

	void pass_dofblur(GfxSystem& gfx, Render& render, const DofBlur& blur)
	{
		static BlockDofBlur& block = *gfx.m_renderer.block<BlockDofBlur>();

		auto blur_pass = [](GfxSystem& gfx, Render& render, RenderTarget& target, const DofBlur& blur, bool first_pass, uint64_t bgfx_state = 0)
		{
			ProgramVersion program = { block.m_program };
			program.set_option(block.m_index, DOF_FIRST_PASS, first_pass);

			GpuState<DofBlur>::me.upload(blur);

			if(first_pass)
			{
				gfx.m_filter->source0(target.m_diffuse, TEXTURE_CLAMP | TEXTURE_POINT);
			}
			else
			{
				gfx.m_filter->source0(target.m_ping_pong.last(), TEXTURE_CLAMP | TEXTURE_POINT);
				gfx.m_filter->source1(target.m_diffuse, TEXTURE_CLAMP | TEXTURE_POINT);
			}

			gfx.m_filter->sourcedepth(target.m_depth);

			FrameBuffer& fbo = first_pass ? target.m_ping_pong.swap() : target.m_post.swap();

			Pass pass = render.composite_pass("dof blur");
			gfx.m_filter->quad(pass, fbo, program, bgfx_state);
		};

		blur_pass(gfx, render, *render.m_target, blur, true);
		blur_pass(gfx, render, *render.m_target, blur, false);//, BGFX_STATE_BLEND_ALPHA);
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

#define MAX_GLOW_LEVELS 7

namespace two
{
	GpuState<Glow> GpuState<Glow>::me;

	BlockGlow::BlockGlow(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur)
		: GfxBlock(gfx, *this)
		, m_bleed_program(gfx.programs().create("filter/glow_bleed"))
		, m_merge_program(gfx.programs().create("filter/glow"))
	{
		m_options = { "GLOW_FILTER_BICUBIC" };

		blur.m_program.register_block(*this);
		m_merge_program.register_block(*this);
	}

	void BlockGlow::init_block()
	{
		GpuState<Glow>::me.init();
	}


	void debug_glow(GfxSystem& gfx, Render& render, RenderTarget& target)
	{
		gfx.m_copy->debug_show_texture(render, target.m_cascade.m_texture, vec4(0.f), 1);
		gfx.m_copy->debug_show_texture(render, target.m_ping_pong.last(), vec4(0.f));
	}

	void glow_bleed(GfxSystem& gfx, Render& render, BlockGlow& block, Glow& glow)
	{
		gfx.m_filter->source0(render.m_target->m_diffuse);
		//bgfx::setUniform(m_blur.u_uniform.u_exposure, &m_tonemap.m_exposure);

		GpuState<Glow>::me.upload(glow);

		Pass pass = render.composite_pass("glow bleed");
		gfx.m_filter->quad(pass, render.m_target->m_ping_pong.swap(), block.m_bleed_program);
	}

	void glow_blur(GfxSystem& gfx, Render& render, BlockBlur& blur, Glow& glow)
	{
		UNUSED(glow);

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
			blur.gaussian_pass(render, *render.m_target, render.m_rect, i, true, kernel);
			blur.gaussian_pass(render, *render.m_target, render.m_rect, i, false, kernel);

			//bool blit_support = (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0;
			bool blit_support = false;

			RenderQuad quad = { render.m_rect, render.m_rect, true };

			Pass pass = render.composite_pass("glow blit");
			//if(blit_support)
			//	bgfx::blit(pass.m_index,
			//			   target.m_cascade.m_texture, i + 1, uint16_t(rect.x), uint16_t(rect.y), 0,
			//			   target.m_ping_pong.last(), 0, uint16_t(rect.x), uint16_t(rect.y), 0, uint16_t(rect.width), uint16_t(rect.height), 1);
			//else
			gfx.m_copy->submit(pass, *render.m_target->m_cascade.m_fbos[i + 1], render.m_target->m_ping_pong.last(), quad);
		}
	}

	void glow_merge(GfxSystem& gfx, Render& render, BlockGlow& block, Glow& glow)
	{
		ProgramVersion program = { block.m_merge_program };

		program.set_option(block.m_index, GLOW_FILTER_BICUBIC, glow.m_bicubic_filter);

		gfx.m_filter->source0(render.m_target->m_post.last());
		gfx.m_filter->source1(render.m_target->m_cascade.m_texture);

		GpuState<Glow>::me.upload(glow);

		Pass pass = render.composite_pass("glow merge");
		gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);
	}

	void pass_glow(GfxSystem& gfx, Render& render, Glow& glow)
	{
		static BlockGlow& block = *gfx.m_renderer.block<BlockGlow>();
		static BlockBlur& blur = *gfx.m_renderer.block<BlockBlur>();

		glow_bleed(gfx, render, block, glow);
		glow_blur(gfx, render, blur, glow);
		glow_merge(gfx, render, block, glow);
	}
}


#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#endif

namespace two
{
	GpuState<BCS> GpuState<BCS>::me;
	GpuState<Tonemap> GpuState<Tonemap>::me;

	BlockTonemap::BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: GfxBlock(gfx, *this)
		, m_program(gfx.programs().create("filter/tonemap"))
	{
		m_options = { "TO_GAMMA", "ADJUST_BCS", "COLOR_LUT" };
		m_modes = { "TONEMAP_MODE" };

		m_program.register_block(*this);
	}

	void BlockTonemap::init_block()
	{
		GpuState<BCS>::me.init();
		GpuState<Tonemap>::me.init();
	}

	void pass_tonemap(GfxSystem& gfx, Render& render, Tonemap& tonemap, BCS& bcs)
	{
		static BlockTonemap& block = *gfx.m_renderer.block<BlockTonemap>();

		ProgramVersion program = { block.m_program };

		program.set_mode(block.m_index, TONEMAP_MODE, uint8_t(tonemap.m_mode));
		program.set_option(block.m_index, TO_GAMMA, render.m_viewport->m_to_gamma);

		gfx.m_filter->source0(render.m_target->m_post.last());

		if(tonemap.m_color_lut)
		{
			program.set_option(block.m_index, COLOR_LUT, true);
			gfx.m_filter->source1(*tonemap.m_color_lut);
		}

		GpuState<Tonemap>::me.upload(tonemap);

		if(bcs.m_enabled)
		{
			program.set_option(block.m_index, ADJUST_BCS, true);

			GpuState<BCS>::me.upload(bcs);
		}

		const Pass pass = render.composite_pass("tonemap");
		gfx.m_filter->quad(pass, *render.m_fbo, program);
	}
}

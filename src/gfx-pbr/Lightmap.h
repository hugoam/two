

#pragma once

#include <gfx-pbr/Forward.h>

namespace two
{
	export_ class refl_ TWO_GFX_PBR_EXPORT LightmapItem
	{
	public:
		LightmapItem() {}
		LightmapItem(size_t item, Texture& lightmap, vec4 uv_scale_offset) : m_item(item), m_lightmap(&lightmap), m_uv_scale_offset(uv_scale_offset) {}
		size_t m_item = SIZE_MAX;
		Texture* m_lightmap = nullptr;
		vec4 m_uv_scale_offset = vec4(1.f, 1.f, 0.f, 0.f);
	};

	struct ModelUnwrap
	{
		vector<bool> success;
		uvec2 size;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT Lightmap
	{
	public:
		Lightmap(uint32_t size);

		uint32_t m_size = 0;
		float m_density = 1.f;
		bool m_dirty = false;

		TextureAtlas m_atlas;

#if !TWO_MODULES
		Texture m_texture = {};
#else
		Texture m_texture;
#endif

		vector<LightmapItem> m_items;

		void add_item(size_t index, Item& item, bool valid, const vec4& uv_scale_offset);
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT LightmapAtlas
	{
	public:
		LightmapAtlas(uint32_t size, float density);
		~LightmapAtlas();

		LightmapAtlas(const LightmapAtlas& other) = delete;
		LightmapAtlas& operator=(const LightmapAtlas& other) = delete;

		Lightmap& add_lightmap() { m_layers.push_back(make_unique<Lightmap>(m_size)); return *m_layers.back(); }

		uint32_t m_size;
		float m_density = 1.f;
		bool m_dirty = false;
		string m_save_path;

		mat4 m_capture_transform;
		vec3 m_capture_extents;

		vector<unique<Lightmap>> m_layers;
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockLightmap : public DrawBlock
	{
	public:
		BlockLightmap(GfxSystem& gfx, BlockLight& block_light, BlockGIBake& block_gi_bake);

		BlockLight& m_block_light;
		BlockGIBake& m_block_gi_bake;

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void bake_geometry(span<Item*> items, LightmapAtlas& atlas);
		void bake_lightmaps(Scene& scene, LightmapAtlas& atlas, const mat4& transform, const vec3& extents);

		struct VoxelGIUniform
		{
			void createUniforms()
			{
				s_lightmap = bgfx::createUniform("s_lightmap", bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle s_lightmap;

		} u_lightmap;

		Program* m_lightmap;

		struct BakeEntry { Scene* scene; LightmapAtlas* atlas; };
		vector<BakeEntry> m_bake_queue;
	};
}

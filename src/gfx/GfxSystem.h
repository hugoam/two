//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <obj/Unique.h>
#include <gfx/Generated/Forward.h>
#define MUD_BGFX_EXPORT MUD_GFX_EXPORT
#include <bgfx/BgfxSystem.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bx/file.h>
#endif

namespace mud
{
	class _refl_ MUD_GFX_EXPORT GfxContext : public BgfxContext
	{
	public:
		GfxContext(GfxSystem& gfx_system, cstring name, int width, int height, bool fullScreen, bool init);
		~GfxContext();

		virtual void reset(uint16_t width, uint16_t height) override;

		GfxSystem& m_gfx_system;
		object_ptr<RenderTarget> m_target;
		std::vector<Viewport*> m_viewports;
		uint16_t m_vg_handle = UINT16_MAX;
	};

	template <class T_Asset>
	class AssetStore;

	struct LocatedFile
	{
		LocatedFile() {}
		LocatedFile(cstring location, cstring name, cstring extension, size_t extension_index) : m_location(location), m_name(name), m_extension(extension), m_extension_index(extension_index) {}
		cstring m_location = nullptr;
		cstring m_name = nullptr;
		cstring m_extension = nullptr;
		size_t m_extension_index = 0;
	};

	class _refl_ MUD_GFX_EXPORT GfxSystem : public BgfxSystem
	{
	public:
		GfxSystem(array<cstring> resource_paths = {});
		~GfxSystem();

		virtual bool next_frame() final;

		virtual object_ptr<Context> create_context(cstring name, int width, int height, bool full_screen) final;

		void init(GfxContext& context);

		template <class T_Renderer>
		Renderer& renderer()
		{
			static T_Renderer renderer(*this, *m_pipeline);
			return renderer;
		}

		void render(Renderer& renderer, GfxContext& context, Viewport& viewport, RenderFrame& frame);

		bx::FileReader m_file_reader;
		bx::FileWriter m_file_writer;
		bx::DefaultAllocator m_allocator;

		LocatedFile locate_file(cstring file);
		LocatedFile locate_file(cstring file, array<cstring> extensions);

		AssetStore<Texture>& textures();
		AssetStore<Program>& programs();
		AssetStore<Material>& materials();
		AssetStore<Model>& models();
		AssetStore<ParticleGenerator>& particles();
		AssetStore<Prefab>& prefabs();

		Texture& default_texture(TextureHint hint);

		Material& debug_material();
		Material& fetch_material(cstring name, cstring shader, bool builtin = true);
		Material& fetch_image256_material(const Image256& image);

		Model& fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode);

		void create_debug_materials();

	public:
		struct Impl;
		unique_ptr<Impl> m_impl;

		unique_ptr<Pipeline> m_pipeline;
	};
}

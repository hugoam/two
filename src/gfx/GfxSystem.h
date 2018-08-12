//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <obj/Unique.h>
#endif
#include <gfx/Forward.h>
#ifndef MUD_BGFX_EXPORT
#define MUD_BGFX_EXPORT MUD_GFX_EXPORT
#endif
#include <bgfx/BgfxSystem.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

#ifndef MUD_MODULES
namespace bx
{
	struct FileReaderI;
	struct FileWriterI;
}
#endif

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT GfxContext : public BgfxContext
	{
	public:
		GfxContext(GfxSystem& gfx_system, cstring name, int width, int height, bool fullScreen, bool init);
		~GfxContext();

		virtual void reset(uint16_t width, uint16_t height) override;

		GfxSystem& m_gfx_system;

		object_ptr<RenderTarget> m_target;

		uint16_t m_vg_handle = UINT16_MAX;
		std::function<uint16_t()> m_reset_vg;

		std::vector<Viewport*> m_viewports;
	};

	template <class T_Asset>
	class TPool;

	template <class T_Asset>
	class AssetStore;

	export_ struct LocatedFile
	{
		LocatedFile() {}
		LocatedFile(cstring location, cstring name, cstring extension, size_t extension_index) : m_location(location), m_name(name), m_extension(extension), m_extension_index(extension_index) {}
		cstring m_location = nullptr;
		cstring m_name = nullptr;
		cstring m_extension = nullptr;
		size_t m_extension_index = 0;
	};

	export_ class refl_ MUD_GFX_EXPORT GfxSystem : public BgfxSystem
	{
	public:
		GfxSystem(array<cstring> resource_paths);
		~GfxSystem();
		
		virtual bool next_frame() final;

		virtual object_ptr<Context> create_context(cstring name, int width, int height, bool full_screen) final;

		void init(GfxContext& context);
		void init_pipeline();

		meth_ void add_resource_path(cstring path);

		void set_renderer(Shading shading, Renderer& renderer);
		Renderer& renderer(Shading shading);

		void render(Renderer& renderer, GfxContext& context, Viewport& viewport, RenderFrame& frame);

		GfxContext& context(size_t index = 0);

		bx::FileReaderI& file_reader();
		bx::FileWriterI& file_writer();

		LocatedFile locate_file(cstring file);
		LocatedFile locate_file(cstring file, array<cstring> extensions);

		TPool<Mesh>& meshes();
		TPool<Rig>& rigs();
		TPool<Animation>& animations();

		attr_ AssetStore<Texture>& textures();
		attr_ AssetStore<Program>& programs();
		attr_ AssetStore<Material>& materials();
		attr_ AssetStore<Model>& models();
		attr_ AssetStore<ParticleGenerator>& particles();
		attr_ AssetStore<Prefab>& prefabs();

		Texture& default_texture(TextureHint hint);

		meth_ Material& debug_material();
		meth_ Material& fetch_material(cstring name, cstring shader, bool builtin = true);
		meth_ Material& fetch_image256_material(const Image256& image);

		meth_ Model& fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		meth_ Material& fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode);

		void create_debug_materials();

	public:
		struct Impl;
		unique_ptr<Impl> m_impl;

		unique_ptr<Pipeline> m_pipeline;
	};
}

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <obj/Unique.h>
#include <gfx/Generated/Forward.h>
#define MUD_BGFX_EXPORT MUD_GFX_EXPORT
#include <bgfx/BgfxContext.h>

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

	class _refl_ MUD_GFX_EXPORT GfxSystem : public BgfxSystem
	{
	public:
		GfxSystem(array<cstring> resource_paths = {});
		~GfxSystem();
		
		virtual object_ptr<Context> create_context(cstring name, int width, int height, bool full_screen);

		void init(GfxContext& context);
		bool next_frame();

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

		cstring locate_file(cstring file, array<cstring> extensions);

		Program& create_program(cstring name, array<GfxBlock*> blocks);
		Program& get_program(cstring program);
		Texture& get_texture(cstring texture);

		Texture& default_texture(TextureHint hint);

		Texture& load_texture(cstring path, cstring texture);
		Texture& load_texture_mem(cstring texture, array<uint8_t> data);
		Texture& load_texture_rgba(cstring texture, uint16_t width, uint16_t height, array<uint8_t> data);

		Texture& fetch_image256(const Image256& image);

		ModelConfig load_model_config(cstring path, cstring name);
		void load_model(Model& model);

		Material& debug_material();
		Material& create_material(cstring name, cstring shader);
		Material* fetch_material(cstring name);
		Material& fetch_image256_material(const Image256& image);

		Model& load_model(cstring name);
		Model& fetch_model(cstring name);
		Model& fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode);

		void create_debug_materials();

	public:
		struct Impl;
		unique_ptr<Impl> m_impl;

		unique_ptr<Pipeline> m_pipeline;
	};
}

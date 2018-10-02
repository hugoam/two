//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <map>
#include <string>
#include <fstream>
#endif

#include <bx/timer.h>
#include <bx/file.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <pool/ObjectPool.h>
#include <infra/StringConvert.h>
#include <math/Image256.h>
#include <math/Stream.h>
#include <ui/Render/Renderer.h>
#include <gfx/Types.h>
#include <gfx/GfxSystem.h>
#include <gfx/Material.h>
#include <gfx/Program.h>
#include <gfx/Draw.h>
#include <gfx/Viewport.h>
#include <gfx/RenderTarget.h>
#include <gfx/Scene.h>
#include <gfx/Texture.h>
#include <gfx/Model.h>
#include <gfx/Prefab.h>
#include <gfx/Particles.h>
#include <gfx/Asset.h>
#include <gfx/Asset.impl.h>
#include <gfx/Assets.h>
#include <gfx/Pipeline.h>
#include <gfx/Filter.h>
#include <gfx/Skeleton.h>
#endif

#include <Tracy.hpp>

//#define MUD_GFX_THREADED

namespace mud
{
	GfxContext::GfxContext(GfxSystem& gfx_system, cstring name, int width, int height, bool fullScreen, bool init)
		: BgfxContext(gfx_system, name, width, height, fullScreen, false)
		, m_gfx_system(gfx_system)
		, m_target()
	{
		if(init)
			gfx_system.init(*this);
		m_target = make_object<RenderTarget>(uvec2(width, height));
	}

	GfxContext::~GfxContext()
	{}

	void GfxContext::reset(uint16_t width, uint16_t height)
	{
		bgfx::reset(width, height, BGFX_RESET_NONE);
		if(width == 0 || height == 0)
			m_target = nullptr;
		else
		{
			if(!m_target ||	width != m_target->m_size.x || height != m_target->m_size.y)
				m_target = make_object<RenderTarget>(uvec2(width, height));
		}
		m_vg_handle = m_reset_vg();
	}

	struct GfxSystem::Impl
	{
		std::vector<string> m_resource_paths;

		std::vector<GfxContext*> m_contexts;
		std::vector<Scene*> m_scenes;

		bx::FileReader m_file_reader;
		bx::FileWriter m_file_writer;

		unique_ptr<TPool<Mesh>> m_meshes;
		unique_ptr<TPool<Rig>> m_rigs;
		unique_ptr<TPool<Animation>> m_animations;

		unique_ptr<AssetStore<Texture>> m_textures;
		unique_ptr<AssetStore<Program>> m_programs;
		unique_ptr<AssetStore<Material>> m_materials;
		unique_ptr<AssetStore<Model>> m_models;
		unique_ptr<AssetStore<ParticleGenerator>> m_particles;
		unique_ptr<AssetStore<Prefab>> m_prefabs;

		std::vector<Renderer*> m_renderers;

		Texture* m_white_texture = nullptr;
		Texture* m_black_texture = nullptr;
		Texture* m_normal_texture = nullptr;

		SymbolIndex m_symbols;

#ifdef MUD_GFX_THREADED
		std::vector<bgfx::Encoder*> m_encoders;
#endif
	};

	GfxSystem::GfxSystem(array<cstring> resource_paths)
		: BgfxSystem(resource_paths[0])
		, m_impl(make_unique<Impl>())
		, m_pipeline(make_unique<Pipeline>(*this))
	{
		Program::ms_gfx_system = this;
		Material::ms_gfx_system = this;
		Model::ms_gfx_system = this;
		for(cstring path : resource_paths)
		{
			printf("INFO: resource path: %s\n", path);
			m_impl->m_resource_paths.push_back(path);
		}
	}

	GfxSystem::~GfxSystem()
	{}

	bx::FileReaderI& GfxSystem::file_reader() { return m_impl->m_file_reader; }
	bx::FileWriterI& GfxSystem::file_writer() { return m_impl->m_file_writer; }

	TPool<Mesh>& GfxSystem::meshes() { return *m_impl->m_meshes; }
	TPool<Rig>& GfxSystem::rigs() { return *m_impl->m_rigs; }
	TPool<Animation>& GfxSystem::animations() { return *m_impl->m_animations; }

	AssetStore<Texture>& GfxSystem::textures() { return *m_impl->m_textures; }
	AssetStore<Program>& GfxSystem::programs() { return *m_impl->m_programs; }
	AssetStore<Material>& GfxSystem::materials() { return *m_impl->m_materials; }
	AssetStore<Model>& GfxSystem::models() { return *m_impl->m_models; }
	AssetStore<ParticleGenerator>& GfxSystem::particles() { return *m_impl->m_particles; }
	AssetStore<Prefab>& GfxSystem::prefabs() { return *m_impl->m_prefabs; }
	
	object_ptr<Context> GfxSystem::create_context(cstring name, int width, int height, bool fullScreen)
	{
		object_ptr<GfxContext> context = make_object<GfxContext>(*this, name, width, height, fullScreen, !m_initialized);
		m_impl->m_contexts.push_back(context.get());
		return std::move(context);
	}

	void GfxSystem::init(GfxContext& context)
	{
		BgfxSystem::init(context);

		m_impl->m_meshes = make_unique<TPool<Mesh>>();
		m_impl->m_rigs = make_unique<TPool<Rig>>();
		m_impl->m_animations = make_unique<TPool<Animation>>();

		m_impl->m_textures = make_unique<AssetStore<Texture>>(*this, "textures/", load_texture);
		m_impl->m_programs = make_unique<AssetStore<Program>>(*this, "programs/", ".prg");
		m_impl->m_materials = make_unique<AssetStore<Material>>(*this, "materials/", ".mtl");
		m_impl->m_models = make_unique<AssetStore<Model>>(*this, "models/");
		m_impl->m_particles = make_unique<AssetStore<ParticleGenerator>>(*this, "particles/", ".ptc");
		m_impl->m_prefabs = make_unique<AssetStore<Prefab>>(*this, "prefabs/", ".pfb");

		m_impl->m_white_texture = this->textures().file("white.png");
		m_impl->m_black_texture = this->textures().file("black.png");
		m_impl->m_normal_texture = this->textures().file("normal.png");

		m_pipeline = make_unique<Pipeline>(*this);
	}

	void GfxSystem::init_pipeline()
	{
		for(auto& block : m_pipeline->m_gfx_blocks)
			block->init_gfx_block();

		static ClearRenderer clear_renderer = { *this, *m_pipeline };
		static UnshadedRenderer unshaded_renderer = { *this, *m_pipeline };
		static MinimalRenderer minimal_renderer = { *this, *m_pipeline };
		UNUSED(minimal_renderer);

		this->set_renderer(Shading::Unshaded, unshaded_renderer);
		this->set_renderer(Shading::Clear, clear_renderer);

		this->create_debug_materials();
	}

	void GfxSystem::add_resource_path(cstring path)
	{
		m_impl->m_resource_paths.push_back(m_resource_path + path);
	}

	void GfxSystem::set_renderer(Shading shading, Renderer& renderer)
	{
		m_impl->m_renderers.resize(max(size_t(shading) + 1, m_impl->m_renderers.size()));
		m_impl->m_renderers[size_t(shading)] = &renderer;
	}

	Renderer& GfxSystem::renderer(Shading shading)
	{
		return *m_impl->m_renderers[size_t(shading)];
	}

	GfxContext& GfxSystem::context(size_t index)
	{
		return *m_impl->m_contexts[index];
	}

	void GfxSystem::begin_frame()
	{
		RenderFrame frame = { m_frame, m_time, m_delta_time, Render::s_render_pass_id };

		{
			ZoneScopedNC("programs", tracy::Color::Cyan);

			for(auto& name_program : m_impl->m_programs->m_assets)
				name_program.second->update();
		}

		{
			ZoneScopedNC("renderers", tracy::Color::Cyan);

			for(auto& renderer : m_impl->m_renderers)
				if(renderer)
					renderer->frame(frame);
		}
	}

	bool GfxSystem::next_frame()
	{
		RenderFrame frame = { m_frame, m_time, m_delta_time, Render::s_render_pass_id };

#ifdef MUD_GFX_THREADED
		{
			ZoneScopedNC("gfx begin", tracy::Color::Cyan);

			m_num_encoders = min(uint32_t(4U), bgfx::getCaps()->limits.maxEncoders);

			m_encoders[0] = bgfx::begin();
			for(size_t i = 1; i < m_num_encoders; ++i)
				m_encoders[i] = bgfx::begin(true);
		}
#endif

		for(GfxContext* context : m_impl->m_contexts)
			for(Viewport* viewport : context->m_viewports)
				if(viewport->m_active)
				{
					ZoneScopedNC("gfx viewport", tracy::Color::Cyan);

					Renderer& renderer = this->renderer(viewport->m_shading);
					this->render(renderer, *context, *viewport, frame);
				}

#ifdef MUD_GFX_THREADED
		{
			ZoneScopedNC("gfx end", tracy::Color::Cyan);

			for(size_t i = 1; i < m_num_encoders; ++i)
				bgfx::end(m_encoders[i]);
		}
#endif

		bool pursue = true;
		{
			ZoneScopedNC("gfx contexts", tracy::Color::Cyan);

			for(GfxContext* context : m_impl->m_contexts)
				pursue &= context->next_frame();
		}

		{
			ZoneScopedNC("gfx frame", tracy::Color::Cyan);
			BgfxSystem::next_frame();
		}

		return pursue;
	}

	void GfxSystem::render(Renderer& renderer, GfxContext& context, Viewport& viewport, RenderFrame& frame)
	{
		Render render(viewport, *context.m_target, frame);
		render.m_scene.gather_render(render);
		render.m_viewport.render(render);
		
		if(rect_w(viewport.m_rect) != 0 && rect_h(viewport.m_rect) != 0)
			renderer.render(render);

		//copy.debug_show_texture(*render.m_target, render.m_environment->m_radiance.m_texture->m_texture, false, false, false, 0);
		//copy.debug_show_texture(*render.m_target, render.m_environment->m_radiance.m_roughness_array, false, false, false, 1);
		//copy.debug_show_texture(*render.m_target, bgfx::getTexture(render.m_target->m_effects.last()));
	}

	LocatedFile GfxSystem::locate_file(cstring file, array<cstring> extensions)
	{
		for(const string& path : m_impl->m_resource_paths)
			for(size_t i = 0; i < extensions.size(); ++i)
				if(std::ifstream(path + file + extensions[i]).good())
				{
					return { path.c_str(), file, extensions[i], i };
				}
		return {};
	}

	LocatedFile GfxSystem::locate_file(cstring file)
	{
		carray<cstring, 1> exts = { "" };
		return this->locate_file(file, exts);
	}

	Texture& GfxSystem::default_texture(TextureHint hint)
	{
		if(hint == TextureHint::Black)
			return *m_impl->m_black_texture;
		else if(hint == TextureHint::White)
			return *m_impl->m_white_texture;
		else //if(hint == TextureHint::Normal)
			return *m_impl->m_normal_texture;
	}

	void GfxSystem::create_debug_materials()
	{
		Material& debug = this->fetch_material("debug", "unshaded");
		debug.m_unshaded_block.m_enabled = true;

		Material& alpha = this->fetch_material("debug_alpha", "unshaded");
		alpha.m_unshaded_block.m_enabled = true;
		alpha.m_unshaded_block.m_colour = Colour{ 0.2f, 0.2f, 0.2f, 0.1f };

		Material& pbr = this->fetch_material("debug_pbr", "pbr/pbr");
		pbr.m_pbr_block.m_enabled = true;
	}

	Material& GfxSystem::debug_material()
	{
		return *this->materials().get("debug_pbr");
	}

	Material& GfxSystem::fetch_material(cstring name, cstring shader, bool builtin)
	{
		Program* program = this->programs().file(shader);
		Material& material = this->materials().fetch(name);
		material.m_builtin = builtin;
		material.m_program = program;
		return material;
	}

	Material& GfxSystem::fetch_image256_material(const Image256& image)
	{
		string name = "Image256_" + to_string((uintptr_t)&image);
		Material* material = this->materials().get(name.c_str());

		if(!material)
		{
			string image_name = "Image256_" + to_string((uintptr_t)&image);
			auto initializer = [&](Texture& texture) { auto data = image.read(); load_texture_rgba(texture, image.m_width, image.m_height, data); };

			Texture& texture = this->textures().fetch(image_name.c_str());
			initializer(texture);
			material = &this->fetch_material(name.c_str(), "unshaded");
			material->m_unshaded_block.m_enabled = true;
			material->m_unshaded_block.m_colour.m_texture = &texture;
		}

		return *material;
	}

	Model& GfxSystem::fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		return m_impl->m_symbols.symbol_model(symbol, shape, draw_mode);
	}

	Material& GfxSystem::fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		if(symbol.m_image256)
			return this->fetch_image256_material(*symbol.m_image256);
		else
			return m_impl->m_symbols.symbol_material(*this, symbol, draw_mode);
	}
}

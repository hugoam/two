//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>
#ifndef MUD_CPP_20
#include <map>
#include <string>
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <obj/Memory/ObjectPool.h>
#include <obj/String/StringConvert.h>
#include <math/Image.h>
#include <math/Stream.h>
#include <ui/Render/Renderer.h>
#include <gfx/Generated/Types.h>
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
#include <gfx/Pipeline.h>
#include <gfx/Filter.h>
#include <gfx-obj/ImporterObj.h>
#include <gfx-gltf/ImporterGltf.h>
#include <gfx-pbr/Shadow.h>
#endif

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <bx/timer.h>
#include <bx/file.h>

namespace mud
{
	template class AssetStore<Texture>;
	template class AssetStore<Program>;
	template class AssetStore<Material>;
	template class AssetStore<Model>;
	template class AssetStore<ParticleGenerator>;
	template class AssetStore<Prefab>;

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
		m_target = make_object<RenderTarget>(uvec2(width, height));
		m_vg_handle = m_gfx_system.m_vg_renderer->load_texture(m_target->m_diffuse.idx);
	}

	struct GfxSystem::Impl
	{
		std::vector<string> m_resource_paths;

		std::vector<GfxContext*> m_contexts;
		std::vector<Scene*> m_scenes;

		bx::FileReader m_file_reader;
		bx::FileWriter m_file_writer;

		unique_ptr<ImporterOBJ> m_importerOBJ;
		unique_ptr<ImporterGltf> m_importerGltf;

		unique_ptr<AssetStore<Texture>> m_textures;
		unique_ptr<AssetStore<Program>> m_programs;
		unique_ptr<AssetStore<Material>> m_materials;
		unique_ptr<AssetStore<Model>> m_models;
		unique_ptr<AssetStore<ParticleGenerator>> m_particles;
		unique_ptr<AssetStore<Prefab>> m_prefabs;

		Texture* m_white_texture = nullptr;
		Texture* m_black_texture = nullptr;
		Texture* m_normal_texture = nullptr;
	};

	GfxSystem::GfxSystem(array<cstring> resource_paths)
		: BgfxSystem(resource_paths[0])
		, m_impl(make_unique<Impl>())
		, m_pipeline(make_unique<Pipeline>(*this))
	{
		Material::ms_gfx_system = this;
		Program::ms_gfx_system = this;
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

	ModelConfig load_model_config(cstring path, cstring model_name)
	{
		std::ifstream file = std::ifstream(string(path) + "models/" + model_name + ".cfg");
		ModelConfig model_config = { ModelFormat::obj, bxidentity() };

		if(!file.good())
		{
			if(std::ifstream(string(path) + "models/" + model_name + ".gltf").good())
				model_config.m_format = ModelFormat::gltf;
			return model_config;
		}

		return model_config;
	}

	void GfxSystem::init(GfxContext& context)
	{
		BgfxSystem::init(context);

		m_impl->m_importerOBJ = make_unique<ImporterOBJ>(*this);
		m_impl->m_importerGltf = make_unique<ImporterGltf>(*this);

		static std::vector<string> model_formats = { ".obj", ".gltf" };

		static auto load_obj = [](GfxSystem& gfx_system, Model& model, cstring path)
		{
			ModelConfig config = load_model_config(path, model.m_name.c_str());
			gfx_system.m_impl->m_importerOBJ->import_model(model, path, config);
		};

		static auto load_gltf = [](GfxSystem& gfx_system, Model& model, cstring path)
		{
			ModelConfig config = load_model_config(path, model.m_name.c_str());
			gfx_system.m_impl->m_importerGltf->import_model(model, path, config);
		};

		static std::vector<std::function<void(GfxSystem& gfx_system, Model& model, cstring path)>> model_loaders = { load_obj, load_gltf };

		m_impl->m_textures = make_unique<AssetStore<Texture>>(*this, "textures/", load_texture);
		m_impl->m_programs = make_unique<AssetStore<Program>>(*this, "programs/", ".prg");
		m_impl->m_materials = make_unique<AssetStore<Material>>(*this, "materials/", ".mtl");
		m_impl->m_models = make_unique<AssetStore<Model>>(*this, "models/", model_formats, model_loaders);
		m_impl->m_particles = make_unique<AssetStore<ParticleGenerator>>(*this, "particles/", ".ptc");
		m_impl->m_prefabs = make_unique<AssetStore<Prefab>>(*this, "prefabs/", ".pfb");

		m_impl->m_white_texture = this->textures().file("white.png");
		m_impl->m_black_texture = this->textures().file("black.png");
		m_impl->m_normal_texture = this->textures().file("normal.png");

		m_pipeline = make_unique<PipelinePbr>(*this);

		for(auto& block : m_pipeline->m_gfx_blocks)
			block->init_gfx_block();

		this->create_debug_materials();
	}

	Renderer& viewport_renderer(GfxSystem& gfx_system, Viewport& viewport)
	{
		//static MinimalRenderer renderer(*this, static_cast<Pipeline&>(*m_pipeline));

		if(viewport.m_shading == Shading::Shaded)
			return gfx_system.renderer<MainRenderer>();
		else if(viewport.m_shading == Shading::Unshaded)
			return gfx_system.renderer<UnshadedRenderer>();
		else if(viewport.m_shading == Shading::Clear)
			return gfx_system.renderer<ClearRenderer>();

		return gfx_system.renderer<MainRenderer>();
	}

	bool GfxSystem::next_frame()
	{
		RenderFrame frame = { m_frame, m_time, m_delta_time, Render::s_render_pass_id };

		for(GfxContext* context : m_impl->m_contexts)
			for(Viewport* viewport : context->m_viewports)
			{
				Renderer& renderer = viewport_renderer(*this, *viewport);
				this->render(renderer, *context, *viewport, frame);
			}
		
		return BgfxSystem::next_frame();
	}

	void GfxSystem::render(Renderer& renderer, GfxContext& context, Viewport& viewport, RenderFrame& frame)
	{
		Render render(viewport, *context.m_target, frame);
		render.m_scene.gather_render(render);
		render.m_viewport.render(render);
		renderer.render(render);

		//BlockCopy& copy = *m_pipeline->block<BlockCopy>();
		//copy.debug_show_texture(*render.m_target, m_pipeline->block<BlockShadow>()->m_csm.m_depth, true);
		//copy.debug_show_texture(*render.m_target, render.m_target->m_effects.m_cascade, false, false, false, 2);
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
		return this->materials().fetch(name, [&](Material& material) { material.m_builtin = builtin; material.m_program = program; });
	}

	Material& GfxSystem::fetch_image256_material(const Image256& image)
	{
		string name = "Image256_" + to_string((uintptr_t)&image);
		Material* material = this->materials().get(name.c_str());

		if(!material)
		{
			string image_name = "Image256_" + to_string((uintptr_t)&image);
			auto initializer = [&](Texture& texture) { auto data = image.read(); load_texture_rgba(texture, image.m_width, image.m_height, data); };

			material = &this->fetch_material(name.c_str(), "unshaded");
			material->m_unshaded_block.m_enabled = true;
			material->m_unshaded_block.m_colour.m_texture = &this->textures().fetch(image_name.c_str(), initializer);
		}

		return *material;
	}

	Model& GfxSystem::fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		return SymbolIndex::me().symbolModel(symbol, shape, draw_mode);
	}

	Material& GfxSystem::fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		if(symbol.m_image256)
			return this->fetch_image256_material(*symbol.m_image256);
		else
			return SymbolIndex::me().symbolMaterial(*this, symbol, draw_mode);
	}
}

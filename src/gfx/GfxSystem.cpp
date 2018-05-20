//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Generated/Types.h>
#include <gfx/GfxSystem.h>

#include <obj/Memory/ObjectPool.h>
#include <obj/String/StringConvert.h>
#include <math/Image.h>
#include <math/Stream.h>

#include <ui/Render/Renderer.h>
#include <gfx/Material.h>
#include <gfx/Program.h>
#include <gfx/Draw.h>
#include <gfx/Viewport.h>
#include <gfx/RenderTarget.h>
#include <gfx/Scene.h>
#include <gfx/Texture.h>
#include <gfx/Pipeline.h>
#include <gfx/Import/ImporterObj.h>
#include <gfx/Import/ImporterGltf.h>

#include <gfx/Filter.h>
#include <gfx/Blocks/Shadow.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <bx/timer.h>

#include <map>
#include <string>
#include <fstream>

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
		m_target = make_object<RenderTarget>(uvec2(width, height));
		m_vg_handle = m_gfx_system.m_vg_renderer->load_texture(m_target->m_diffuse.idx);
	}

	struct GfxSystem::Impl
	{
		std::vector<string> m_resource_paths;

		std::vector<GfxContext*> m_contexts;
		std::vector<Scene*> m_scenes;

		std::map<string, unique_ptr<Texture>> m_textures;
		std::map<string, unique_ptr<Program>> m_programs;
		std::vector<object_ptr<Material>> m_materials;
		std::vector<object_ptr<Model>> m_models;

		unique_ptr<ImporterOBJ> m_importerOBJ;
		unique_ptr<ImporterGltf> m_importerGltf;

		object_ptr<Texture> m_white_texture;
		object_ptr<Texture> m_black_texture;
		object_ptr<Texture> m_normal_texture;
	};

	GfxSystem::GfxSystem(array<cstring> resource_paths)
		: BgfxSystem(resource_paths[0])
		, m_impl(make_unique<Impl>())
		, m_pipeline(make_unique<Pipeline>(*this))
	{
		Material::ms_gfx_system = this;
		for(cstring path : resource_paths)
		{
			printf("INFO: resource path: %s\n", path);
			m_impl->m_resource_paths.push_back(path);
		}
	}

	GfxSystem::~GfxSystem()
	{}

	object_ptr<Context> GfxSystem::create_context(cstring name, int width, int height, bool fullScreen)
	{
		object_ptr<GfxContext> context = make_object<GfxContext>(*this, name, width, height, fullScreen, !m_initialized);
		m_impl->m_contexts.push_back(context.get());
		return std::move(context);
	}

	void GfxSystem::init(GfxContext& context)
	{
		BgfxSystem::init(context);

		m_impl->m_importerOBJ = make_unique<ImporterOBJ>(*this);
		m_impl->m_importerGltf = make_unique<ImporterGltf>(*this);

		m_impl->m_white_texture = make_object<Texture>(*this, "white.png");
		m_impl->m_black_texture = make_object<Texture>(*this, "black.png");
		m_impl->m_normal_texture = make_object<Texture>(*this, "normal.png");

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

	cstring GfxSystem::locate_file(cstring file, array<cstring> extensions)
	{
		for(const string& path : m_impl->m_resource_paths)
			for(cstring extension : extensions)
				if(std::ifstream(path + file + extension).good())
				{
					return path.c_str();
				}
		return nullptr;
	}

	Program& GfxSystem::get_program(cstring program)
	{
		if(m_impl->m_programs.find(program) == m_impl->m_programs.end())
			m_impl->m_programs[program] = make_unique<Program>(*this, program, array<GfxBlock*>{});
		return *m_impl->m_programs[program];
	}
	
	Texture& GfxSystem::get_texture(cstring texture)
	{
		if(m_impl->m_textures.find(texture) == m_impl->m_textures.end())
			m_impl->m_textures[texture] = make_unique<Texture>(*this, texture);
		return *m_impl->m_textures[texture];
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

	Texture& GfxSystem::load_texture(cstring path, cstring texture)
	{
		if(m_impl->m_textures.find(texture) == m_impl->m_textures.end())
			m_impl->m_textures[texture] = make_unique<Texture>(*this, path, texture);
		return *m_impl->m_textures[texture];
	}

	Texture& GfxSystem::load_texture_mem(cstring texture, array<uint8_t> data)
	{
		// @todo
		UNUSED(data);
		return *m_impl->m_textures[texture];
	}

	Texture& GfxSystem::load_texture_rgba(cstring texture, uint16_t width, uint16_t height, array<uint8_t> data)
	{
		if(m_impl->m_textures.find(texture) == m_impl->m_textures.end())
			m_impl->m_textures[texture] = make_unique<Texture>(*this, texture, width, height, data);
		return *m_impl->m_textures[texture];
	}

	Texture& GfxSystem::fetch_image256(const Image256& image)
	{
		string name = "Image256_" + to_string((uintptr_t)&image);
		std::vector<uint8_t> data = image.read();
		return this->load_texture_rgba(name.c_str(), image.m_width, image.m_height, { data.data(), data.size() });
	}

	ModelConfig GfxSystem::load_model_config(cstring path, cstring model_name)
	{
		std::ifstream file = std::ifstream(string(path) + "models/" + model_name + ".cfg");
		ModelConfig model_config = { ModelFormat::obj, bxidentity() };

		if(!file.good())
		{
			if(std::ifstream(string(path) + "models/" + model_name + ".gltf").good())
				model_config.m_format = ModelFormat::gltf;
			return model_config;
		}

		vec3 scale = Unit3;
		vec3 position = Zero3;
		vec3 rotation = Zero3;
		//quat rotation = ZeroQuat;

		for(std::string line; std::getline(file, line);)
		{
			std::istringstream stream(line);

			string command = read<string>(stream);
			if(command == "format")
			{
				string format = read<string>(stream);
				model_config.m_format = format == "obj" ? ModelFormat::obj : ModelFormat::gltf;
			}
			else if(command == "scale")
				scale = read<vec3>(stream);
			else if(command == "position")
				position = read<vec3>(stream);
			else if(command == "rotation")
				rotation = read<vec3>(stream);
			//else if(command == "rotation")
			//	rotation = read<quat>(stream);
			//else if(command == "filter")
			//	model_config.m_filter.push_back(read<string>(stream));
		}

		model_config.m_transform = bxSRT(scale, rotation, position);

		return model_config;
	}

	void GfxSystem::load_model(Model& model)
	{
		carray<cstring, 3> formats = { ".cfg", ".obj", ".gltf" };

		cstring path = this->locate_file(("models/" + string(model.m_name)).c_str(), formats);
		if(path == nullptr)
		{
			printf("ERROR: couldn't locate model %s\n", model.m_name.c_str());
			return;
		}

		ModelConfig config = load_model_config(path, model.m_name.c_str());

		if(config.m_format == ModelFormat::obj)
			m_impl->m_importerOBJ->import_model(model, (string(path) + "models/").c_str(), string(model.m_name), config);
		else if(config.m_format == ModelFormat::gltf)
			m_impl->m_importerGltf->import_model(model, (string(path) + "models/").c_str(), string(model.m_name), config);
	}

	void GfxSystem::create_debug_materials()
	{
		this->create_material("debug", "unshaded").m_unshaded_block.m_enabled = true;
		this->create_material("debug_pbr", "pbr/pbr").m_pbr_block.m_enabled = true;
	}

	Material& GfxSystem::debug_material()
	{
		return *m_impl->m_materials.front();
	}

	Program& GfxSystem::create_program(cstring name, array<GfxBlock*> blocks)
	{
		m_impl->m_programs[name] = make_unique<Program>(*this, name, blocks);
		return *m_impl->m_programs[name];
	}

	Material& GfxSystem::create_material(cstring name, cstring shader)
	{
		m_impl->m_materials.emplace_back(make_object<Material>(name, shader));
		return *m_impl->m_materials.back();
	}

	Material* GfxSystem::fetch_material(cstring name)
	{
		for(auto& material : m_impl->m_materials)
			if(material->m_name == name)
				return material.get();
		return nullptr;
	}

	Material& GfxSystem::fetch_image256_material(const Image256& image)
	{
		string name = "Image256_" + to_string((uintptr_t)&image);
		Material* material = fetch_material(name.c_str());

		if(!material)
		{
			material = &this->create_material(name.c_str(), "unshaded");
			material->m_unshaded_block.m_enabled = true;
			material->m_unshaded_block.m_colour.m_texture = &this->fetch_image256(image);
		}

		return *material;
	}

	Model& GfxSystem::load_model(cstring name)
	{
		m_impl->m_models.emplace_back(make_object<Model>(*this, name));
		this->load_model(*m_impl->m_models.back());
		return *m_impl->m_models.back();
	}

	Model& GfxSystem::fetch_model(cstring name)
	{
		for(auto& model : m_impl->m_models)
			if(model->m_name == name)
				return *model;

		return load_model(name);
	}

	Model& GfxSystem::fetch_symbol(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		return SymbolIndex::me().symbolModel(*this, symbol, shape, draw_mode);
	}

	Material& GfxSystem::fetch_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		if(symbol.m_image256)
			return this->fetch_image256_material(*symbol.m_image256);
		else
			return SymbolIndex::me().symbolMaterial(*this, symbol, draw_mode);
	}
}

//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Renderer.h>

namespace two
{
	export_ class refl_ TWO_GFX_EXPORT GfxWindow : public BgfxContext
	{
	public:
		GfxWindow(GfxSystem& gfx, const string& name, const uvec2& size, bool fullscreen, bool main = true);
		~GfxWindow();

		virtual void reset_fb(const uvec2& size) override;

		GfxSystem& m_gfx;
		void* m_vg = nullptr;

		object<RenderTarget> m_target;

		uint16_t m_vg_handle = UINT16_MAX;
		using ResetVg = uint16_t(*)(GfxWindow&, void*); ResetVg m_reset_vg;

		vector<Viewport*> m_viewports;
	};

	export_ template <class T_Asset>
	class AssetStore;

	export_ struct LocatedFile
	{
		LocatedFile() {}
		LocatedFile(string location, string name, string extension, size_t extension_index)
			: m_located(true), m_location(location), m_name(name), m_extension(extension), m_extension_index(extension_index)
		{}
		bool m_located = false;
		string m_location;
		string m_name;
		string m_extension;
		size_t m_extension_index = 0;
		string path(bool ext) { return m_location + "/" + m_name + (ext ? m_extension : ""); }
		explicit operator bool() { return m_located; }
	};

	export_ class refl_ TWO_GFX_EXPORT GfxSystem : public BgfxSystem
	{
	public:
		constr_ GfxSystem(const string& resource_path);
		~GfxSystem();

		JobSystem* m_job_system = nullptr;

		bgfx::Encoder* m_encoders[8] = {};
		size_t m_num_encoders = 0;

		attr_ Renderer m_renderer;

		attr_ BlockCopy* m_copy = nullptr;
		attr_ BlockFilter* m_filter = nullptr;

		attr_ bool m_flip_y = false;

		attr_ RenderFrame m_render_frame;

		meth_ RenderTarget& main_target();

		virtual bool begin_frame() final;
		virtual void end_frame() final;

		void render_contexts();

		void init(GfxWindow& context);

		using PipelineDecl = void(*)(GfxSystem& gfx, Renderer& pipeline, bool deferred);
		void init_pipeline(PipelineDecl pipeline);

		meth_ void default_pipeline();

		meth_ void add_resource_path(const string& path, bool relative = true);

		void set_renderer(Shading shading, const RenderFunc& renderer);
		RenderFunc renderer(Shading shading);

		void render(Shading shading, RenderFunc renderer, RenderTarget& target, Viewport& viewport);
		RenderFrame render_frame();

		GfxWindow& context(size_t index = 0);

		bx::FileReaderI& file_reader();
		bx::FileWriterI& file_writer();

		LocatedFile locate_file(const string& file);
		LocatedFile locate_file(const string& file, span<string> extensions);

		TPool<Mesh>& meshes();
		TPool<Rig>& rigs();
		TPool<Animation>& animations();

		attr_ AssetStore<Texture>& textures();
		attr_ AssetStore<Program>& programs();
		attr_ AssetStore<Material>& materials();
		attr_ AssetStore<Model>& models();
		attr_ AssetStore<Flow>& flows();
		attr_ AssetStore<Prefab>& prefabs();

		void add_importer(ModelFormat format, Importer& importer);
		Importer* importer(ModelFormat format);

		Texture& default_texture(TextureHint hint);

		meth_ Material& debug_material();
		meth_ Model& create_model(const string& name);
		meth_ Model& create_model_geo(const string& name, const MeshPacker& geometry, bool readback = false, bool optimize = false);
		meth_ Model& create_model_gpu(const string& name, const GpuMesh& gpu_mesh, bool readback = false, bool optimize = false);
		meth_ Material& fetch_material(const string& name, const string& shader, bool builtin = true);
		meth_ Material& fetch_image256_material(const Image256& image);

		meth_ Model& shape(const Shape& shape, const Symbol& symbol = {}, DrawMode draw_mode = PLAIN);
		meth_ Material& symbol_material(const Symbol& symbol, DrawMode draw_mode = PLAIN);

		void create_debug_materials();

	public:
		struct Impl;
		unique<Impl> m_impl;
	};
}

//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/GfxSystem.h>

namespace two
{
	using cstring = const char*;

	struct NoConfig {};

	export_ template <class T_Asset>
	struct AssetConfig { using type = NoConfig; };

	export_ template <class T_Asset>
	class refl_ AssetStore
	{
	public:
		using Config = typename AssetConfig<T_Asset>::type;

		using Loader = function<void(T_Asset&, const string&, const Config&)>;
		using Init = function<void(T_Asset&)>;

		AssetStore(GfxSystem& gfx, const string& path)
			: m_gfx(gfx)
			, m_path(path)
		{}

		AssetStore(GfxSystem& gfx, const string& path, const Loader& loader)
			: m_gfx(gfx)
			, m_path(path)
			, m_loader(loader)
		{}

		AssetStore(GfxSystem& gfx, const string& path, const string& format)
			: m_gfx(gfx)
			, m_path(path)
		{
			UNUSED(format);
		}


		AssetStore(const AssetStore& other) = delete;
		AssetStore& operator=(const AssetStore& other) = delete;

		void add_format(const string& format, const Loader& loader)
		{
			m_formats.push_back(format);
			m_format_loaders.push_back(loader);
		}

		GfxSystem& m_gfx;

		string m_path;
		Loader m_loader;

		vector<string> m_formats;
		vector<Loader> m_format_loaders;

		//meth_ bool locate(const string& name);
		meth_ T_Asset* get(const string& name)
		{
			if (m_assets.find(name) == m_assets.end())
				return nullptr;
			return m_assets[name].get();
		}
		meth_ T_Asset& create(const string& name)
		{
			if (m_assets.find(name) != m_assets.end())
			{
				warn("creating asset %s of already existing name: previous asset deleted", name.c_str());
				remove(m_vector, &*m_assets[name]);
			}
			m_assets[name] = make_unique<T_Asset>(name);
			m_vector.push_back(&*m_assets[name]);
			return *m_assets[name];
		}

		meth_ T_Asset& fetch(const string& name)
		{
			if (m_assets.find(name) == m_assets.end())
				return this->create(name);
			return *m_assets[name];
		}
		      T_Asset* file(const string& name, const Config& config)
		{
			if(m_assets.find(name) == m_assets.end())
			{
				string filename = m_path + string(name);
				LocatedFile location = m_formats.size() > 0 ? m_gfx.locate_file(filename, m_formats)
															: m_gfx.locate_file(filename);

				if(!location)
					return nullptr;

				T_Asset& asset = this->create(name);
				Loader& loader = m_formats.size() > 0 ? m_format_loaders[location.m_extension_index] : m_loader;
				loader(asset, location.path(false), config);
			}
			return m_assets[name].get();
		}
		meth_ T_Asset* file(const string& name) { return this->file(name, {}); }
		      T_Asset& file_at(const string& path, const string& name, const Config& config)
		{
			if (m_assets.find(name) == m_assets.end())
			{
				T_Asset& asset = this->create(name);
				m_loader(asset, path + "/" + name, config);
			}
			return *m_assets[name];
		}

		meth_ T_Asset& file_at(const string& path, const string& name) { return this->file_at(path, name, {}); }
			  T_Asset* load(const string& path, const string& file, const Config& config)
		{
			string filename = file;
			for (size_t i = 0; i < m_formats.size(); ++i)
				if (filename.find(m_formats[i]) != string::npos)
				{
					string name = filename.substr(0, filename.size() - m_formats[i].size());
					T_Asset& asset = this->create(name);
					m_format_loaders[i](asset, path + "/" + name, config);
					return &asset;
				}
			return nullptr;
		}
		meth_ T_Asset* load(const string& path, const string& name) { return this->load(path, name, {}); }
		meth_ void destroy(const string& name)
		{
			remove(m_vector, &*m_assets[name]);
			m_assets[name] = nullptr;
		}
		meth_ void clear()
		{
			m_vector.clear();
			m_assets.clear();
		}

		T_Asset& create(const string& name, const Init& init)
		{
			T_Asset& asset = this->create(name);
			init(asset);
			return asset;
		}

		void load_files(const string& path)
		{
			auto visit_file = [&](const string& file)
			{
				this->load(path, file);
			};

			auto visit_folder = [&](const string& folder)
			{
				this->load_files(path + "/" + folder);
			};

			visit_files(path, visit_file);
			visit_folders(path, visit_folder);
		}

		map<string, unique<T_Asset>> m_assets;
		vector<T_Asset*> m_vector;
	};
	
	export_ template <>
	struct AssetConfig<Prefab> { using type = ImportConfig; };
	
	export_ template <>
	struct AssetConfig<Model> { using type = ImportConfig; };
}

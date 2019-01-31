//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/File.h>
#include <infra/Array.h>
//#include <srlz/Serial.h>
#endif
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>

#include <cstdio>

namespace mud
{
	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, const string& path)
		: m_gfx_system(gfx_system)
		, m_path(path)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, const string& path, const Loader& loader)
		: m_gfx_system(gfx_system)
		, m_path(path)
		, m_loader(loader)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, const string& path, const string& format)
		: m_gfx_system(gfx_system)
		, m_path(path)
	{
		UNUSED(format);
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::add_format(const string& format, const Loader& loader)
	{
		m_formats.push_back(format);
		m_format_loaders.push_back(loader);
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::get(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
			return nullptr;
		return m_assets[name].get();
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::create(const string& name)
	{
		if(m_assets.find(name) != m_assets.end())
			printf("WARNING: creating asset of already existing name: previous asset deleted\n");
		m_assets[name] = make_unique<T_Asset>(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::destroy(const string& name)
	{
		m_assets[name] = nullptr;
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::fetch(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
			return this->create(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::file_at(const string& path, const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			m_assets[name] = make_unique<T_Asset>(name);
			m_loader(*m_assets[name], path + "/" + name);
		}
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::file(const string& name)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			string filename = m_path + string(name);
			LocatedFile location = m_formats.size() > 0 ? m_gfx_system.locate_file(filename, m_formats)
														: m_gfx_system.locate_file(filename);

			if(!location)
				return nullptr;

			m_assets[name] = make_unique<T_Asset>(name);
			Loader& loader = m_formats.size() > 0 ? m_format_loaders[location.m_extension_index] : m_loader;
			loader(*m_assets[name], location.path(false));
		}
		return m_assets[name].get();
	}
	
	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::load(const string& path, const string& file)
	{
		string filename = file;
		for(size_t i = 0; i < m_formats.size(); ++i)
			if(filename.find(m_formats[i]) != string::npos)
			{
				string name = filename.substr(0, filename.size() - m_formats[i].size());
				T_Asset& asset = this->create(name);
				m_format_loaders[i](asset, path + "/" + name);
				return &asset;
			}
		return nullptr;
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::load_files(const string& path)
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
}

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/File.h>
#include <srlz/Serial.h>
#endif
#include <gfx/Asset.h>

namespace mud
{
	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, cstring path)
		: m_gfx_system(gfx_system)
		, m_path(path)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, cstring path, const Loader& loader)
		: m_gfx_system(gfx_system)
		, m_path(path)
		, m_loader(loader)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, cstring path, cstring format)
		: m_gfx_system(gfx_system)
		, m_path(path)
	{
		auto loader = [&](GfxSystem& gfx_system, T_Asset& asset, cstring path)
		{
			UNUSED(gfx_system);
			unpack_json_file(Ref(&asset), string(path) + m_cformats[0]); // @kludge: fix extensions assumed in loaders (gltf, obj, etc...)
		};

		this->add_format(format, loader);
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::add_format(cstring format, const Loader& loader)
	{
		m_formats.push_back(format);
		m_cformats.push_back(format);
		m_format_loaders.push_back(loader);
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::get(cstring name)
	{
		if(m_assets.find(name) == m_assets.end())
			return nullptr;
		return m_assets[name].get();
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::create(cstring name)
	{
		if(m_assets.find(name) != m_assets.end())
			printf("WARNING: creating asset of already existing name: previous asset deleted\n");
		m_assets[name] = make_unique<T_Asset>(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::destroy(cstring name)
	{
		m_assets[name] = nullptr;
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::fetch(cstring name)
	{
		if(m_assets.find(name) == m_assets.end())
			return this->create(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::file_at(cstring path, cstring name)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			m_assets[name] = make_unique<T_Asset>(name);
			m_loader(m_gfx_system, *m_assets[name], (string(path) + name).c_str());
		}
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset* AssetStore<T_Asset>::file(cstring name)
	{
		if(m_assets.find(name) == m_assets.end())
		{
			string filename = m_path + string(name);
			LocatedFile location = m_cformats.size() > 0 ? m_gfx_system.locate_file(filename.c_str(), m_cformats)
														 : m_gfx_system.locate_file(filename.c_str());

			if(location.m_location == nullptr)
				return nullptr;

			m_assets[name] = make_unique<T_Asset>(name);
			if(m_cformats.size() > 0)
				m_format_loaders[location.m_extension_index](m_gfx_system, *m_assets[name], (string(location.m_location) + location.m_name).c_str());
			else
				m_loader(m_gfx_system, *m_assets[name], (string(location.m_location) + location.m_name).c_str());
		}
		return m_assets[name].get();
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::load_files(cstring path)
	{
		auto visit_file = [&](cstring path, cstring file)
		{
			string filename = file;
			for (size_t i = 0; i < m_cformats.size(); ++i)
				if (filename.find(m_formats[i]) != string::npos)
				{
					string name = filename.substr(0, filename.size() - m_formats[i].size());
					m_assets[name] = make_unique<T_Asset>(file);
					m_format_loaders[i](m_gfx_system, *m_assets[name], (path + name).c_str());
					break;
				}
		};

		auto visit_folder = [&](cstring path, cstring folder)
		{
			this->load_files((string(path) + folder + "/").c_str());
		};

		visit_files(path, visit_file);
		visit_folders(path, visit_folder);
	}
}

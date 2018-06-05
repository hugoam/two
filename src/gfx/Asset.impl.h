//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
#ifdef _MSC_VER
import std.memory; // std.memory exists only in Visual Studio experimental modules
#endif
#endif
#include <gfx/Asset.h>

#ifndef MUD_MODULES
#include <obj/Serial/Serial.h>
#include <obj/System/System.h>
#endif

namespace mud
{
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

		this->setup({ format }, { loader });
	}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, cstring path, const std::vector<string>& formats, const std::vector<Loader>& loaders)
		: m_gfx_system(gfx_system)
		, m_path(path)
		, m_formats(formats)
		, m_format_loaders(loaders)
	{
		this->setup(formats, loaders);
	}

	template <class T_Asset>
	void AssetStore<T_Asset>::setup(const std::vector<string>& formats, const std::vector<Loader>& loaders)
	{
		m_formats = formats;
		m_format_loaders = loaders;
		for(const string& format : m_formats)
			m_cformats.push_back(format.c_str());
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
		m_assets[name] = make_unique<T_Asset>(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::create(cstring name, const Initializer& initializer)
	{
		m_assets[name] = make_unique<T_Asset>(name);
		initializer(*m_assets[name]);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::fetch(cstring name)
	{
		if(m_assets.find(name) == m_assets.end())
			return this->create(name);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::fetch(cstring name, const Initializer& initializer)
	{
		if(m_assets.find(name) == m_assets.end())
			return this->create(name, initializer);
		return *m_assets[name];
	}

	template <class T_Asset>
	T_Asset& AssetStore<T_Asset>::file(cstring path, cstring name)
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

		system().visit_files(path, visit_file);
		system().visit_folders(path, visit_folder);
	}
}

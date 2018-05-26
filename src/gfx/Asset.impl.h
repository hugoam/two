//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Asset.h>

namespace mud
{
	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, cstring path, const Loader& loader)
		: m_gfx_system(gfx_system)
		, m_path(path)
		, m_loader(loader)
	{}

	template <class T_Asset>
	AssetStore<T_Asset>::AssetStore(GfxSystem& gfx_system, cstring path, const std::vector<string>& formats, const std::vector<Loader>& loaders)
		: m_gfx_system(gfx_system)
		, m_path(path)
		, m_formats(formats)
		, m_format_loaders(loaders)
	{
		for(const string& format : formats)
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
}

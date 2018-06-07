//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Unique.h>
#include <obj/Array.h>
#include <obj/NonCopy.h>
#endif
#include <gfx/Generated/Forward.h>
#include <gfx/GfxSystem.h>

#ifndef MUD_CPP_20
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#endif

namespace mud
{
	using cstring = const char*;
	using string = std::string;

	export_ template <class T_Asset>
	class AssetStore : public NonCopy
	{
	public:
		using Initializer = std::function<void(T_Asset&)>;
		using Loader = std::function<void(GfxSystem&, T_Asset&, cstring)>;

		AssetStore(GfxSystem& gfx_system, cstring path);
		AssetStore(GfxSystem& gfx_system, cstring path, const Loader& loader);
		AssetStore(GfxSystem& gfx_system, cstring path, cstring format);

		void add_format(cstring format, const Loader& loader);

		GfxSystem& m_gfx_system;

		//class Impl;
		//unique_ptr<Impl> m_impl;

		string m_path;
		Loader m_loader;

		std::vector<string> m_formats;
		std::vector<cstring> m_cformats;
		std::vector<Loader> m_format_loaders;

		T_Asset* get(cstring name);
		T_Asset& create(cstring name);
		T_Asset& create(cstring name, const Initializer& initializer);
		T_Asset& fetch(cstring name);
		T_Asset& fetch(cstring name, const Initializer& initializer);
		T_Asset& file(cstring path, cstring name);
		T_Asset* file(cstring name);

		void load_files(cstring path);

		std::map<string, unique_ptr<T_Asset>> m_assets;
	};
}

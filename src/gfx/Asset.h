//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Unique.h>
#include <infra/Array.h>
#include <infra/NonCopy.h>
#endif
#include <gfx/Forward.h>
#include <gfx/GfxSystem.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/map.h>
#endif

namespace mud
{
	using cstring = const char*;

	export_ template <class T_Asset>
	class refl_ AssetStore : public NonCopy
	{
	public:
		struct Loader
		{
			void* loader;
			using Handler = void(*)(void*, T_Asset&, cstring); Handler load;
		};

		AssetStore(GfxSystem& gfx_system, cstring path);
		AssetStore(GfxSystem& gfx_system, cstring path, const Loader& loader);
		AssetStore(GfxSystem& gfx_system, cstring path, cstring format);

		void add_format(cstring format, const Loader& loader);

		GfxSystem& m_gfx_system;

		//class Impl;
		//unique<Impl> m_impl;

		string m_path;
		Loader m_loader;

		vector<string> m_formats;
		vector<cstring> m_cformats;
		vector<Loader> m_format_loaders;

		meth_ T_Asset* get(cstring name);
		meth_ T_Asset& create(cstring name);
		meth_ T_Asset& fetch(cstring name);
		meth_ T_Asset& file_at(cstring path, cstring name);
		meth_ T_Asset* file(cstring name);
		meth_ void destroy(cstring name);

		T_Asset* load(cstring path, cstring name);
		void load_files(cstring path);

		map<string, unique<T_Asset>> m_assets;
	};
}

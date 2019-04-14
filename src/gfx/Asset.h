//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/function.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>

namespace mud
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

		AssetStore(GfxSystem& gfx, const string& path);
		AssetStore(GfxSystem& gfx, const string& path, const Loader& loader);
		AssetStore(GfxSystem& gfx, const string& path, const string& format);

		AssetStore(const AssetStore& other) = delete;
		AssetStore& operator=(const AssetStore& other) = delete;

		void add_format(const string& format, const Loader& loader);

		GfxSystem& m_gfx;

		string m_path;
		Loader m_loader;

		vector<string> m_formats;
		vector<Loader> m_format_loaders;

		//meth_ bool locate(const string& name);
		meth_ T_Asset* get(const string& name);
		meth_ T_Asset& create(const string& name);
		meth_ T_Asset& fetch(const string& name);
		      T_Asset* file(const string& name, const Config& config);
		meth_ T_Asset* file(const string& name) { return this->file(name, {}); }
		      T_Asset& file_at(const string& path, const string& name, const Config& config);
		meth_ T_Asset& file_at(const string& path, const string& name) { return this->file_at(path, name, {}); }
			  T_Asset* load(const string& path, const string& name, const Config& config);
		meth_ T_Asset* load(const string& path, const string& name) { return this->load(path, name, {}); }
		meth_ void destroy(const string& name);
		meth_ void clear();

		T_Asset& create(const string& name, const Init& init);

		void load_files(const string& path);

		map<string, unique<T_Asset>> m_assets;
		vector<T_Asset*> m_vector;
	};
	
	export_ template <>
	struct AssetConfig<Prefab> { using type = ImportConfig; };
	
	export_ template <>
	struct AssetConfig<Model> { using type = ImportConfig; };
}

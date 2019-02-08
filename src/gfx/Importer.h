//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/map.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Item.h>
#include <gfx/Node3.h>

namespace mud
{
	export_ enum class refl_ ModelFormat : unsigned int
	{
		obj,
		gltf,

		Count
	};

	export_ struct refl_ MUD_GFX_EXPORT ImportConfig
	{
		ImportConfig() {}

		attr_ ModelFormat m_format = ModelFormat::obj;
		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;
		attr_ mat4 m_transform = bxidentity();
		attr_ vector<string> m_exclude_elements; // = {};
		attr_ vector<string> m_exclude_materials; // = {};
		attr_ vector<string> m_include_elements; // = {};
		attr_ vector<string> m_include_materials; // = {};
		attr_ string m_suffix;
		attr_ bool m_force_reimport = false;
		attr_ bool m_cache_geometry = false;
		attr_ bool m_optimize_geometry = false;
		attr_ uint32_t m_flags = ItemFlag::None;

		bool filter_element(const string& name) const;
		bool filter_material(const string& name) const;
	};

	export_ class MUD_GFX_EXPORT Import
	{
	public:
		Import(GfxSystem& gfx_system, const string& filepath, const ImportConfig& config);

		string m_name;
		string m_file;
		string m_path;

		GfxSystem& m_gfx_system;
		const ImportConfig& m_config;

		vector<Mesh*> m_meshes;
		vector<Model*> m_models;
		vector<Texture*> m_images;
		vector<Material*> m_materials;

		map<int, Skeleton*> m_skeletons;

		struct Item { mat4 transform; Model* model; int skin; };
		vector<Item> m_items;
	};

	export_ class MUD_GFX_EXPORT Importer
	{
	public:
		virtual ~Importer() {}
		virtual void import(Import& import, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) = 0;
		virtual void repack(const string& filepath, const ImportConfig& config) = 0;
	};

	export_ MUD_GFX_EXPORT void import_to_prefab(GfxSystem& gfx_system, Prefab& prefab, Import& state, uint32_t flags = 0);
}

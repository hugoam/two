//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Item.h>
#include <gfx/Node3.h>

namespace two
{
	export_ enum class refl_ ModelFormat : unsigned int
	{
		obj,
		ply,
		gltf,

		Count
	};

	export_ struct refl_ TWO_GFX_EXPORT ImportConfig
	{
		ImportConfig() {}

		attr_ ModelFormat m_format = ModelFormat::obj;
		attr_ vec3 m_position = vec3(0.f);
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = vec3(1.f);
		attr_ mat4 m_transform = bxidentity();
		attr_ vector<string> m_exclude_elements; // = {};
		attr_ vector<string> m_exclude_materials; // = {};
		attr_ vector<string> m_include_elements; // = {};
		attr_ vector<string> m_include_materials; // = {};
		attr_ string m_suffix;
		attr_ bool m_force_reimport = false;
		attr_ bool m_cache_geometry = false;
		attr_ bool m_optimize_geometry = false;
		attr_ bool m_need_normals = true;
		attr_ bool m_need_uvs = true;
		attr_ bool m_no_transforms = false;
		attr_ uint32_t m_flags = ItemFlag::None;

		bool filter_element(const string& name) const;
		bool filter_material(const string& name) const;
	};

	export_ class refl_ TWO_GFX_EXPORT Import
	{
	public:
		Import(GfxSystem& gfx, const string& filepath, const ImportConfig& config);

		attr_ string m_name;
		attr_ string m_file;
		attr_ string m_path;

		GfxSystem& m_gfx;
		attr_ ImportConfig m_config;

		attr_ vector<Mesh*> m_meshes;
		attr_ vector<Model*> m_models;
		attr_ vector<Texture*> m_images;
		attr_ vector<Material*> m_materials;
		attr_ vector<Animation*> m_animations;

		map<int, Skeleton*> m_skeletons;

		vector<Node3> m_nodes;

		struct Item { uint32_t node; Model* model; int skin; };
		vector<Item> m_items;
	};

	export_ class TWO_GFX_EXPORT Importer
	{
	public:
		virtual ~Importer() {}
		virtual void import(Import& import, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_model(Model& model, const string& filepath, const ImportConfig& config) = 0;
		virtual void import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config) = 0;
		virtual void repack(const string& filepath, const ImportConfig& config) = 0;
	};

	export_ TWO_GFX_EXPORT void import_to_prefab(GfxSystem& gfx, Prefab& prefab, Import& state, uint32_t flags = 0);
}

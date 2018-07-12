//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <obj/Indexer.h>
#include <pool/Pool.h>
#include <geom/Geom.h>
#include <gfx/Types.h>
#include <gfx/Model.h>
#include <gfx/Mesh.h>
#include <gfx/Skeleton.h>
#include <gfx/Asset.h>
#include <gfx/Material.h>
#include <gfx/GfxSystem.h>
#endif

namespace mud
{
	ModelConfig load_model_config(cstring path, cstring model_name)
	{
		std::ifstream file = std::ifstream(string(path) + "models/" + model_name + ".cfg");
		ModelConfig model_config = { ModelFormat::obj, bxidentity() };

		if(!file.good())
		{
			if(std::ifstream(string(path) + "models/" + model_name + ".gltf").good())
				model_config.m_format = ModelFormat::gltf;
			return model_config;
		}

		return model_config;
	}

	//static uint16_t s_model_index = 0;

	GfxSystem* Model::ms_gfx_system = nullptr;

	Model::Model(cstring id)
		: m_name(id)
		, m_index(index(type<Model>(), Ref(this)))//++s_model_index)
	{}

	Model::~Model()
	{}

	Mesh& Model::add_mesh(cstring name, bool readback)
	{
		Mesh& mesh = ms_gfx_system->meshes().construct(name, readback);
		m_meshes.push_back(&mesh);
		return mesh;
	}

	Rig& Model::add_rig(cstring name)
	{
		m_rig = &ms_gfx_system->rigs().construct();
		return *m_rig;
	}

	void Model::prepare()
	{
		m_aabb = { Zero3, Zero3 };
		m_radius = 0.f;

		for(ModelItem& item: m_items) //Mesh& mesh : m_meshes)
		{
			m_geometry[item.m_mesh->m_draw_mode] = true;
			m_aabb.merge(transform_aabb(item.m_mesh->m_aabb, item.m_transform));
			//m_radius = max(item.m_mesh->m_radius, m_radius);
		}

		m_radius = sqrt(2.f) * max(m_aabb.m_extents.x, max(m_aabb.m_extents.y, m_aabb.m_extents.z));

		m_origin = m_aabb.m_center;
	}

	Model& model_variant(GfxSystem& gfx_system, Model& original, cstring name, array<cstring> materials, array<Material*> substitutes)
	{
		Model& variant = gfx_system.models().create(name);
		variant = original;

		for(ModelItem& item : variant.m_items)
			for(size_t i = 0; i < materials.size(); ++i)
			{
				if(item.m_mesh->m_material->m_name == materials[i])
					item.m_material = substitutes[i];
			}

		return variant;
	}
}

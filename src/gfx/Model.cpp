//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <type/Indexer.h>
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
	//static uint16_t s_model_index = 0;

	GfxSystem* Model::ms_gfx_system = nullptr;

	Model::Model(const string& name)
		: m_name(name)
		, m_index(uint16_t(index(type<Model>(), Ref(this))))//++s_model_index)
	{}

	Model::~Model()
	{}

	Mesh& Model::add_mesh(const string& name, bool readback)
	{
		Mesh& mesh = ms_gfx_system->meshes().construct(name, readback);
		return mesh;
	}

	Rig& Model::add_rig(const string& name)
	{
		UNUSED(name);
		m_rig = &ms_gfx_system->rigs().construct();
		return *m_rig;
	}

	ModelItem& Model::add_item(Mesh& mesh, mat4 transform, int skin, Colour colour, Material* material)
	{
		m_items.push_back({ m_items.size(), &mesh, transform != bxidentity(), transform, skin, colour, material });
		return m_items.back();
	}

	void Model::prepare()
	{
		m_aabb = {};
		m_radius = 0.f;

		for(const ModelItem& item: m_items)
		{
			m_geometry[item.m_mesh->m_draw_mode] = true;
			m_aabb.mergeSafe(transform_aabb(item.m_mesh->m_aabb, item.m_transform));
		}

		m_radius = sqrt(2.f) * max(m_aabb.m_extents.x, max(m_aabb.m_extents.y, m_aabb.m_extents.z));

		m_origin = m_aabb.m_center;
	}

	Model& model_variant(GfxSystem& gfx_system, Model& original, const string& name, array<string> materials, array<Material*> substitutes)
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

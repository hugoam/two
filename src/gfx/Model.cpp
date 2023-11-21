//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	//static uint16_t s_model_index = 0;

	GfxSystem* Model::ms_gfx = nullptr;

	Model::Model(const string& name)
		: m_name(name)
		, m_index(uint16_t(index(type<Model>(), Ref(this))))//++s_model_index)
	{}

	Model::~Model()
	{}

	Mesh& Model::get_mesh(size_t index)
	{
		return *m_items[index].m_mesh;
	}

	Mesh& Model::add_mesh(const string& name, bool readback)
	{
		Mesh& mesh = ms_gfx->meshes().construct(name, readback);
		return mesh;
	}

	Rig& Model::add_rig(const string& name)
	{
		UNUSED(name);
		m_rig = &ms_gfx->rigs().construct();
		return *m_rig;
	}

	ModelElem& Model::add_item(Mesh& mesh, const mat4& transform, int skin, const Colour& colour, Material* material)
	{
		m_items.push_back({ m_items.size(), &mesh, transform != bxidentity(), transform, skin, colour, material });
		return m_items.back();
	}

	void Model::prepare()
	{
		m_aabb = {};
		m_radius = 0.f;

		for(const ModelElem& item: m_items)
		{
			m_geometry[item.m_mesh->m_primitive] = true;
			m_aabb.merge(transform_aabb(item.m_mesh->m_aabb, item.m_transform));
		}

		m_radius = sqrt(2.f) * max(m_aabb.m_extents.x, max(m_aabb.m_extents.y, m_aabb.m_extents.z));

		m_origin = m_aabb.m_center;
	}

	Model& model_variant(GfxSystem& gfx, Model& original, const string& name, span<string> materials, span<Material*> substitutes)
	{
		Model& variant = gfx.models().create(name);
		variant = original;

		for(ModelElem& item : variant.m_items)
			for(size_t i = 0; i < materials.size(); ++i)
			{
				if(item.m_mesh->m_material->m_name == materials[i])
					item.m_material = substitutes[i];
			}

		return variant;
	}
}

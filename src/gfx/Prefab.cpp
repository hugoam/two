//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx;
#else
#include <stl/set.h>
#include <stl/hash_base.hpp>
#include <pool/Pool.h>
#include <gfx/Types.h>
#include <gfx/Prefab.h>
#include <gfx/Animated.h>
#include <gfx/Gfx.h>
#include <gfx/Assets.h>
#include <gfx/Importer.h>
#include <gfx/GfxSystem.h>
#endif

namespace two
{
#ifdef TWO_PREFABNODE
	PrefabNode::PrefabNode()
	{}

	void PrefabNode::draw(Gnode& parent)
	{
		Gnode& self = gfx::node(parent); // , m_object);
		Gnode& item = gfx::node(self, m_transform.m_position, m_transform.m_rotation, m_transform.m_scale); // Ref(this), 

		if(m_call.m_callable)
			m_call.m_args[0] = Ref(&item);
		if(m_call.validate())
			m_call();
		//else
		//	printf("[warning] invalid prefab node element arguments\n");

		for(PrefabNode& node : m_nodes)
			node.draw(self);
	}
#endif

	Prefab::Prefab(const string& name)
		: m_name(name)
	{}

	void Prefab::add(Scene& scene, Mime* mime)
	{
		span<Node3> nodes = gfx::nodes(scene).addvec(m_nodes);

		for(Elem& elem : m_items)
		{
			Item& it = gfx::items(scene).add(Item(nodes[elem.node], *elem.item.m_model, elem.item.m_flags));
		}

		if(mime)
		{
			mime->add_nodes(nodes);
			mime->m_anims = m_anims;
		}
	}

	Prefab& import_prefab(GfxSystem& gfx, ModelFormat format, const string& name, const ImportConfig& config)
	{
		LocatedFile location = gfx.locate_file("models/" + name, { format == ModelFormat::obj ? ".obj" : ".gltf" });
		Prefab& prefab = gfx.prefabs().create(name);
		gfx.importer(format)->import_prefab(prefab, location.path(false), config);
		return prefab;
	}

	void destroy_prefab(GfxSystem& gfx, Prefab& prefab)
	{
		set<Model*> models;
		for(Prefab::Elem& elem : prefab.m_items)
			models.insert(elem.item.m_model);

		for(Model* model : models)
		{
			for(ModelElem& elem : model->m_items)
			{
				gfx.meshes().destroy(Ref(elem.m_mesh));
			}

			gfx.models().destroy(model->m_name);
		}
	}
}

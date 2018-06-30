//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <bgfx/bgfx.h>
#include <bx/math.h>

#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Node3.h>
#endif

namespace mud
{
	Item::Item(Node3& node, const Model& model, uint32_t flags, Material* material, size_t instances)
		: m_node(node)
		, m_model(const_cast<Model*>(&model))
		, m_flags(flags)
		, m_material(material)
		, m_instances(instances)
	{
		if((flags & ITEM_LOD_ALL) == 0)
			m_flags |= ITEM_LOD_ALL;
	}

	Item::~Item()
	{}

	void Item::submit(uint64_t& bgfx_state, const ModelItem& item)
	{
		bgfx_state |= item.m_mesh->submit();

		mat4 transform = m_node.transform() * item.m_transform;
		bgfx::setTransform(value_ptr(transform));

		if(!m_instances.empty())
			submit_instances(item);
	}

	void Item::submit_instances(const ModelItem& item)
	{
		const uint16_t stride = sizeof(mat4);
		bgfx::allocInstanceDataBuffer(&m_instance_buffer, m_instances.size(), stride);

		uint8_t* data = m_instance_buffer.data;
		for(uint32_t i = 0; i < m_instance_buffer.num; ++i)
		{
			mat4* mat = (mat4*)data;
			*mat = m_instances[i] * item.m_transform;
			data += stride;
		}

		bgfx::setInstanceDataBuffer(&m_instance_buffer);
	}
}

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

	void Item::update()
	{
		//if(!m_instances.empty())
		//	this->update_instances();
	}

	void Item::update_instances()
	{
		m_instance_buffers.resize(m_model->m_items.size());

		for(const ModelItem& item : m_model->m_items)
		{
			bgfx::InstanceDataBuffer& buffer = m_instance_buffers[item.m_index];
			uint32_t num = bgfx::getAvailInstanceDataBuffer(m_instances.size(), sizeof(mat4));
			if(num == 0)
				return;
			bgfx::allocInstanceDataBuffer(&buffer, num, sizeof(mat4));

			mat4* mat = (mat4*)buffer.data;

			if(item.m_has_transform)
			{
				for(uint32_t i = 0; i < buffer.num; ++i)
					*mat++ = m_instances[i] * item.m_transform;
			}
			else
			{
				std::copy(m_instances.begin(), m_instances.end(), mat);
			}
		}
	}

	void Item::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelItem& item) const
	{
		bgfx_state |= item.m_mesh->submit(encoder);

		mat4 transform = m_node.transform() * item.m_transform;
		encoder.setTransform(value_ptr(transform));

		if(!m_instances.empty())
			encoder.setInstanceDataBuffer(&m_instance_buffers[item.m_index]);
	}
}

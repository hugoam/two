//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <bgfx/bgfx.h>

#include <math/Vec.hpp>
#include <geom/Geom.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Node3.h>
#endif

#include <cstring>

namespace mud
{
	Item::Item() {}
	Item::Item(Node3& node, const Model& model, uint32_t flags, Material* material)
		: m_node(&node)
		, m_model(const_cast<Model*>(&model))
		, m_flags(flags)
		, m_material(material)
	{
		if(flags == 0)
			m_flags = ItemFlag::Default;
		if((flags & ItemFlag::LodAll) == 0)
			m_flags |= ItemFlag::LodAll;

		this->update_aabb();
	}

	void Item::update_aabb()
	{
		if(m_batch == nullptr)
			m_aabb = transform_aabb(m_model->m_aabb, m_node->m_transform);
	}

	void Item::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelItem& item) const
	{
		bgfx_state |= item.m_mesh->submit(encoder);

		if(!item.m_has_transform)
			encoder.setTransform(value_ptr(m_node->m_transform));
		else
		{
			mat4 transform = m_node->m_transform * item.m_transform;
			encoder.setTransform(value_ptr(transform));
		}

		if(m_batch != nullptr)
			m_batch->submit(encoder, item);
	}

	Batch::Batch()
	{}

	Batch::Batch(Item& item)
		: m_item(&item)
	{
		item.m_batch = this;
	}

	void Batch::submit(bgfx::Encoder& encoder, const ModelItem& item) const
	{
		encoder.setInstanceDataBuffer(&m_buffer);
		//encoder.setInstanceDataBuffer(&m_buffers[item.m_index]);
	}

	void Batch::update_aabb(span<mat4> instances)
	{
		const Aabb& model = m_item->m_model->m_aabb;
		Aabb& aabb = m_item->m_aabb;
		aabb = {};
		for(const mat4& transform : instances)
		{
			aabb.merge(transform_aabb(model, transform));
		}
	}

	span<float> Batch::begin(uint32_t count, uint16_t stride)
	{
		uint32_t num = bgfx::getAvailInstanceDataBuffer(count, stride);
		if(num == 0) return {};
		bgfx::allocInstanceDataBuffer(&m_buffer, num, stride);
		return { (float*)m_buffer.data, num };
	}

	void Batch::transforms(span<mat4> instances)
	{
		const Model& model = *m_item->m_model;
		m_buffers.resize(model.m_items.size());

		for(const ModelItem& item : model.m_items)
		{
			bgfx::InstanceDataBuffer& buffer = m_buffers[item.m_index];
			uint32_t num = bgfx::getAvailInstanceDataBuffer(uint32_t(instances.size()), sizeof(mat4));
			if(num == 0) return;
			bgfx::allocInstanceDataBuffer(&buffer, num, sizeof(mat4));

			mat4* mat = (mat4*)buffer.data;

			if(item.m_has_transform)
			{
				for(uint32_t i = 0; i < buffer.num; ++i)
					*mat++ = instances[i] * item.m_transform;
			}
			else
			{
				memcpy(mat, instances.data(), instances.size() * sizeof(mat4));
			}
		}
	}
}

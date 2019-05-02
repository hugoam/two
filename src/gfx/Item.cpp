//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx;
#else
#include <bgfx/bgfx.h>

#include <math/Vec.hpp>
#include <geom/Geom.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Node3.h>
#include <gfx/Skeleton.h>
#endif

#include <cstring>

#include <cstdio>

namespace two
{
	uint32_t item_flags(uint32_t flags)
	{
		if(flags == 0) return ItemFlag::Default;
		if((flags & ItemFlag::LodAll) == 0) return flags | ItemFlag::LodAll;
		return flags;
	}

	Item::Item() {}
	Item::Item(Node3& node, const Model& model, uint32_t flags, Material* material)
		: m_node(&node)
		, m_model(const_cast<Model*>(&model))
		, m_flags(item_flags(flags))
		, m_material(material)
	{
		this->update_aabb();
	}

	void Item::update_aabb()
	{
		if(m_batch == nullptr)
			m_aabb = transform_aabb(m_model->m_aabb, m_node->m_transform);
	}

	void Item::submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelElem& item) const
	{
		if(m_rig && m_rig->m_weights.size() > 0)
		{
			float weights[4] = {};

			for(size_t i = 0; i < 4; ++i)
			{
				Rig::MorphWeight& w = m_rig->m_weights[i];
				weights[i] = w.weight;
				if(w.weight != 0.f)
					item.m_mesh->submit_morph(encoder, i, w.index);
			}

			static bgfx::UniformHandle u_morph_weights = bgfx::createUniform("u_morph_weights", bgfx::UniformType::Vec4);
			encoder.setUniform(u_morph_weights, weights);
		}

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
		: m_buffer{}
	{}

	Batch::Batch(Item& item, uint16_t stride)
		: m_item(&item)
		, m_stride(stride)
		, m_buffer{}
	{}

	void Batch::submit(bgfx::Encoder& encoder, const ModelElem& item) // const
	{
		if(m_cache.size() > 0)
			this->commit(m_cache);

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

	span<float> Batch::begin(uint32_t count)
	{
		uint32_t num = bgfx::getAvailInstanceDataBuffer(count, m_stride);
		if(num == 0) return {};
		bgfx::allocInstanceDataBuffer(&m_buffer, num, m_stride);
		return { (float*)m_buffer.data, num * m_stride / sizeof(float) };
	}

	void Batch::commit(span<float> data)
	{
		const uint32_t count = uint32_t(data.size() * sizeof(float) / m_stride);
		span<float> dest = this->begin(count);
		memcpy(dest.data(), data.data(), dest.size() * sizeof(float));
	}

	void Batch::cache(span<float> data)
	{
		const uint32_t count = uint32_t(m_cache.size() * sizeof(float) / m_stride);
		m_cache.assign(data.begin(), data.end());
	}

	void Batch::transform(const mat4& m)
	{
		const size_t size = m_cache.size();
		m_cache.resize(size + 16);
		memcpy(&m_cache[size], &m, 16 * sizeof(float));
	}

	void Batch::transforms(span<mat4> instances)
	{
		const Model& model = *m_item->m_model;
		if(model.m_no_transform)
		{
			bgfx::InstanceDataBuffer& buffer = m_buffer;
			uint32_t num = bgfx::getAvailInstanceDataBuffer(uint32_t(instances.size()), sizeof(mat4));
			if(num == 0) return;
			bgfx::allocInstanceDataBuffer(&buffer, num, sizeof(mat4));

			mat4* mat = (mat4*)buffer.data;
			memcpy(mat, instances.data(), instances.size() * sizeof(mat4));
		}
		else
		{
			m_buffers.resize(model.m_items.size());

			for(const ModelElem& item : model.m_items)
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
}

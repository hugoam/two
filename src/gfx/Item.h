//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

namespace two
{
	export_ struct ItemFlag
	{
		enum Enum : unsigned int
		{
			None = 0,
			Render = 1 << 0,
			Shadows = 1 << 1,
			Occluder = 1 << 2,
			Billboard = 1 << 3,
			Static = 1 << 4,
			Selectable = 1 << 5,
			Ui = 1 << 6,
			NoUpdate = 1 << 7,
			NoCull = 1 << 8,
			Lod0 = 1 << 9,
			Lod1 = 1 << 10,
			Lod2 = 1 << 11,
			Lod3 = 1 << 12,
			LodAll = Lod0 | Lod1 | Lod2 | Lod3,
			Default = Render | Shadows | LodAll
		};
	};

	export_ enum class refl_ ItemShadow : unsigned int
	{
		Default,
		DoubleSided
	};

	export_ struct refl_ TWO_GFX_EXPORT Batch
	{
		constr_ Batch();
		constr_ Batch(Item& item, uint16_t stride);

		attr_ Item* m_item = nullptr;
		attr_ uint16_t m_stride;

		bgfx::InstanceDataBuffer m_buffer;
		vector<bgfx::InstanceDataBuffer> m_buffers;
		vector<float> m_cache;
		//span<mat4> m_transforms;

		meth_ void update_aabb(span<mat4> instances);
		meth_ void transforms(span<mat4> instances);

		meth_ span<float> begin(uint32_t count);
		meth_ void commit(span<float> data);
		meth_ void cache(span<float> data);

		meth_ void transform(const mat4& m);

		void submit(bgfx::Encoder& encoder, const ModelElem& item); // const;
	};

	export_ class refl_ TWO_GFX_EXPORT Item
	{
	public:
		constr_ Item();
		constr_ Item(Node3& node, const Model& model, uint32_t flags = 0, Material* material = nullptr);

		attr_ Node3* m_node = nullptr;
		attr_ Model* m_model = nullptr;
		attr_ uint32_t m_flags = 0;
		attr_ Colour m_colour = Colour::White;
		attr_ Material* m_material = nullptr;
		attr_ bool m_visible = true;
		attr_ ItemShadow m_shadow = ItemShadow::Default;
		attr_ Rig* m_rig = nullptr;

		attr_ Aabb m_aabb;
		attr_ Batch* m_batch = nullptr;

		meth_ void update_aabb();

		void submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelElem& item) const;

		// @TODO fix this ugliness (probably can be indexed by lightmap itself ?)
		vector<void*> m_lightmaps;

		float m_depth = 0.f;
		uint32_t m_layer_mask = 1;
	};
}

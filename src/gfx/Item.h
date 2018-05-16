//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Colour.h>
#include <geom/Aabb.h>
#include <gfx/Generated/Forward.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#include <vector>

namespace mud
{
	enum _refl_ ItemFlag : unsigned int
	{
		ITEM_BILLBOARD = 1 << 0,
		ITEM_WORLD_GEOMETRY = 1 << 1,
		ITEM_SELECTABLE = 1 << 2,
		ITEM_UI = 1 << 3,
		ITEM_SHADEABLE = 1 << 4,
		ITEM_LOD_0 = 1 << 5,
		ITEM_LOD_1 = 1 << 6,
		ITEM_LOD_2 = 1 << 7,
		ITEM_LOD_3 = 1 << 8,
		ITEM_LOD_ALL = (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8)
	};

	enum class _refl_ ItemShadow : unsigned int
	{
		Off,
		On,
		DoubleSided,
		OnlyShadow
	};

	class _refl_ MUD_GFX_EXPORT Item
	{
	public:
		Item(Node3& node, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
		~Item();

		_attr_ Node3& m_node;
		_attr_ _mut_ Model* m_model = nullptr;
		_attr_ _mut_ uint32_t m_flags = 0;
		_attr_ _mut_ Colour m_colour = Colour::White;
		_attr_ _mut_ Material* m_material = nullptr;
		_attr_ _mut_ bool m_visible = true;
		_attr_ _mut_ ItemShadow m_cast_shadows = ItemShadow::On;
		_attr_ Rig* m_rig = nullptr;

		Aabb m_aabb;

		uint64_t submit(const ModelItem& item);
		void submit_instances();

		std::vector<mat4> m_instances;

		bgfx::InstanceDataBuffer m_instance_buffer;

		std::vector<Light*> m_lights;
		std::vector<ReflectionProbe*> m_reflection_probes;
		//std::vector<GIProbe*> m_gi_probes;

		float m_depth = 0.f;
		uint32_t m_layer_mask = 1;
	};
}

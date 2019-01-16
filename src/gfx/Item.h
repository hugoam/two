//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <geom/Aabb.h>
#include <geom/Geom.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
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
			Lod0 = 1 << 8,
			Lod1 = 1 << 9,
			Lod2 = 1 << 10,
			Lod3 = 1 << 11,
			LodAll = Lod0 | Lod1 | Lod2 | Lod3,
			Default = Render | Shadows | LodAll
		};
	};

	export_ enum class refl_ ItemShadow : unsigned int
	{
		Default,
		DoubleSided
	};

	export_ class refl_ MUD_GFX_EXPORT Item
	{
	public:
		Item(Node3& node, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
		~Item();

		attr_ Node3* m_node;
		attr_ Model* m_model = nullptr;
		attr_ uint32_t m_flags = 0;
		attr_ Colour m_colour = Colour::White;
		attr_ Material* m_material = nullptr;
		attr_ bool m_visible = true;
		attr_ ItemShadow m_shadow = ItemShadow::Default;
		attr_ Rig* m_rig = nullptr;

		Aabb m_aabb;

		void update();
		void update_instances();

		void submit(bgfx::Encoder& encoder, uint64_t& bgfx_state, const ModelItem& item) const;

		vector<mat4> m_instances;

		vector<bgfx::InstanceDataBuffer> m_instance_buffers;
		
		vector<Light*> m_lights;
		//vector<ReflectionProbe*> m_reflection_probes;
		//vector<GIProbe*> m_gi_probes;
		
		vector<LightmapItem*> m_lightmaps;

		float m_depth = 0.f;
		uint32_t m_layer_mask = 1;
	};
}

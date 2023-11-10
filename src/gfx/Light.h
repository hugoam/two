//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Colour.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>

namespace two
{
	export_ enum class refl_ LightType : unsigned int
	{
		Direct,
		Point,
		Spot,
		Count
	};

	export_ enum refl_ ShadowFlags : unsigned int
	{
		CSM_Stabilize = 1 << 0,
		CSM_Optimize = 1 << 1,
		CSM_BlendSplits = 1 << 2
	};

	export_ struct AtlasIndex { uint8_t slice = UINT8_MAX; uint16_t slot = UINT16_MAX; };

	export_ class refl_ TWO_GFX_EXPORT Light
	{
	public:
		constr_ Light(Node3& node, LightType type = LightType::Point, bool shadows = false, Colour colour = Colour::White, float energy = 1.f, float range = 1.f);

		attr_ Node3* m_node = nullptr;
		attr_ LightType m_type = LightType::Point;
		attr_ bool m_visible = true;
		attr_ Colour m_colour = Colour::White;
		attr_ float m_range = 1.f;
		attr_ float m_energy = 1.f;
		attr_ float m_specular = 1.f;
		attr_ float m_attenuation = 0.5f;
		attr_ bool m_shadows = false;
		attr_ float m_shadow_range = 100.f;
		attr_ uint32_t m_layers = 0xFFFFFFFF;

		attr_ uint32_t m_last_render = 0;
		attr_ uint32_t m_last_update = 0;

		// spotlight
		attr_ float m_spot_angle = 45.f;
		attr_ float m_spot_attenuation = 0.5f;

		attr_ ShadowFlags m_shadow_flags = ShadowFlags(0 | CSM_Optimize);
		attr_ uint8_t m_shadow_num_splits = 1;
		attr_ float m_shadow_split_distribution = 0.6f;

		attr_ float m_shadow_normal_bias = 0.1f;
		attr_ float m_shadow_bias = 0.f;

		size_t m_shot_index = 0;

		uint32_t m_index = 0;
		AtlasIndex m_shadow_index = {};
	};
}

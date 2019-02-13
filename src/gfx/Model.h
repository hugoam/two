//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/span.h>
#include <math/Colour.h>
#include <math/Vec.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>

namespace mud
{
	export_ struct refl_ ModelItem
	{
		attr_ size_t m_index;
		attr_ Mesh* m_mesh;
		attr_ bool m_has_transform;
		attr_ mat4 m_transform;
		attr_ int m_skin;
		attr_ Colour m_colour;
		attr_ Material* m_material;
	};

	export_ class refl_ MUD_GFX_EXPORT Model
	{
	public:
		Model(const string& name);
		~Model();

		attr_ string m_name;
		attr_ uint16_t m_index;

		Rig* m_rig = nullptr;

		vector<ModelItem> m_items;

		/*attr_*/ bool m_geometry[2] = { false, false };
		attr_ Aabb m_aabb = { vec3(0.f), vec3(0.f) };
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = vec3(0.f);

		Mesh& add_mesh(const string& name, bool readback = false);
		Rig& add_rig(const string& name);
		ModelItem& add_item(Mesh& mesh, mat4 transform, int skin = -1, Colour colour = Colour::White, Material* material = nullptr);
		void prepare();

		static GfxSystem* ms_gfx_system;
	};

	export_ MUD_GFX_EXPORT Model& model_variant(GfxSystem& gfx_system, Model& original, const string& name, span<string> materials, span<Material*> substitutes);
}

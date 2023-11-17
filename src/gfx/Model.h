//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Node3.h>

namespace two
{
	export_ struct refl_ ModelElem
	{
		attr_ size_t m_index;
		attr_ Mesh* m_mesh;
		attr_ bool m_has_transform;
		attr_ mat4 m_transform;
		attr_ int m_skin;
		attr_ Colour m_colour;
		attr_ Material* m_material;
	};

	export_ class refl_ TWO_GFX_EXPORT Model
	{
	public:
		Model(const string& name);
		~Model();

		attr_ string m_name;
		attr_ uint16_t m_index;

		vector<ModelElem> m_items;
		bool m_no_transform = true;

		attr_ Aabb m_aabb = { vec3(0.f), vec3(0.f) };
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = vec3(0.f);

		table<PrimitiveType, bool> m_geometry = { { 0 } };

		Rig* m_rig = nullptr;

		vector<Animation*> m_anims;

		meth_ Mesh& get_mesh(size_t index);
		meth_ Mesh& add_mesh(const string& name, bool readback = false);
		meth_ Rig& add_rig(const string& name);
		meth_ ModelElem& add_item(Mesh& mesh, const mat4& transform, int skin = -1, const Colour& colour = Colour::White, Material* material = nullptr);
		meth_ void prepare();

		static GfxSystem* ms_gfx;
	};

	export_ TWO_GFX_EXPORT Model& model_variant(GfxSystem& gfx, Model& original, const string& name, span<string> materials, span<Material*> substitutes);
}

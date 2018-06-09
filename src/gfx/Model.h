//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/NonCopy.h>
#include <obj/Unique.h>
#include <infra/Array.h>
#include <infra/Strung.h>
#include <math/Colour.h>
#include <math/Vec.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	enum class ModelFormat : unsigned int
	{
		obj,
		gltf
	};

	export_ struct MUD_GFX_EXPORT ModelConfig
	{
		ModelFormat m_format;
		Transform m_transform;
		//std::vector<string> m_filter;
	};

	export_ MUD_GFX_EXPORT ModelConfig load_model_config(cstring path, cstring model_name);

	export_ struct refl_ ModelItem
	{
		attr_ mat4 m_transform;
		attr_ Mesh* m_mesh;
		attr_ int m_skin;
		attr_ Colour m_colour;
	};

	export_ class refl_ MUD_GFX_EXPORT Model : public NonCopy
	{
	public:
		Model(cstring id);
		~Model();

		attr_ string m_name;
		attr_ uint16_t m_index;

		std::vector<Mesh> m_meshes;
		object_ptr<Rig> m_rig;

		std::vector<ModelItem> m_items;
		//std::vector<Material> m_materials;

		/*attr_*/ bool m_geometry[2] = { false, false };
		attr_ Aabb m_aabb = { Zero3, Zero3 };
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = Zero3;

		Mesh& add_mesh(cstring name, bool readback = false);
		void prepare();
	};
}

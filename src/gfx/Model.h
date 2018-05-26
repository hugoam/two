//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/NonCopy.h>
#include <obj/Unique.h>
#include <obj/Array.h>
#include <obj/Strung.h>
#include <math/Colour.h>
#include <math/Vec.h>
#include <geom/Aabb.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#include <vector>

namespace mud
{
	enum class ModelFormat : unsigned int
	{
		obj,
		gltf
	};

	struct MUD_GFX_EXPORT ModelConfig
	{
		ModelFormat m_format;
		Transform m_transform;
		//std::vector<string> m_filter;
	};

	struct _refl_ ModelItem
	{
		_attr_ mat4 m_transform;
		_attr_ Mesh* m_mesh;
		_attr_ int m_skin;
		_attr_ Colour m_colour;
	};

	class _refl_ MUD_GFX_EXPORT Model : public NonCopy
	{
	public:
		Model(cstring id);
		~Model();

		_attr_ strung m_name;
		_attr_ uint16_t m_index;

		std::vector<Mesh> m_meshes;
		object_ptr<Rig> m_rig;

		std::vector<ModelItem> m_items;
		//std::vector<Material> m_materials;

		/*_attr_*/ bool m_geometry[2] = { false, false };
		_attr_ Aabb m_aabb = { Zero3, Zero3 };
		_attr_ float m_radius = 0.f;
		_attr_ vec3 m_origin = Zero3;

		Mesh& add_mesh(cstring name, bool readback = false);
		void prepare();
	};
}

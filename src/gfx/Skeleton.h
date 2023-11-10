//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <bgfx/bgfx.h>
#include <stl/vector.h>
#include <stl/string.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Texture.h>
#include <gfx/Animation.h>

namespace two
{
	TWO_GFX_EXPORT mat4 fix_bone_pose(Node3& bone);

	TWO_GFX_EXPORT void debug_draw_skeleton(Gnode& parent, const quat& position, const quat& rotation, Rig& rig);

	export_ class refl_ TWO_GFX_EXPORT Skeleton
	{
	public:
		Skeleton();
		Skeleton(cstring name, int num_bones);

		uint32_t add_bone(cstring name, uint32_t parent = UINT32_MAX);
		uint32_t bone_index(cstring name) const;
		Node3* find_bone(cstring name);

		cstring m_name;
		vector<string> m_names;
		vector<Node3> m_bones;
	};

	export_ struct refl_ TWO_GFX_EXPORT Joint
	{
		size_t m_bone;
		mat4 m_inverse_bind;
		mat4 m_joint;
	};

	export_ class refl_ TWO_GFX_EXPORT Skin
	{
	public:
		Skin();
		Skin(Skeleton& skeleton, int num_joints);
		Skin(const Skin& copy, Skeleton& skeleton);
		~Skin();

		void add_joint(cstring bone, const mat4& inverse_bind);
		void update_joints();
		bool valid() const { return bgfx::isValid(m_texture); }

		Skeleton* m_skeleton;

		//Texture m_texture;
		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		const bgfx::Memory* m_memory = nullptr;
		//vector<float> m_texture_data;

		vector<Joint> m_joints;
	};

	export_ class refl_ TWO_GFX_EXPORT Rig
	{
	public:
		Rig();

		Rig(const Rig& rig);
		Rig& operator=(const Rig& rig);

		void update_rig();

		Skeleton m_skeleton;
		vector<Skin> m_skins;

		vector<float> m_morphs;

		struct MorphWeight { uint32_t index; float weight; };
		vector<MorphWeight> m_weights;
	};
}

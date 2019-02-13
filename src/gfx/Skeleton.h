//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Animation.h>

#include <bgfx/bgfx.h>

namespace mud
{
	MUD_GFX_EXPORT mat4 fix_bone_pose(Bone& bone);

	MUD_GFX_EXPORT void debug_draw_skeleton(Gnode& parent, const quat& position, const quat& rotation, Rig& rig);

	export_ struct refl_ MUD_GFX_EXPORT Bone
	{
		Bone() {}
		Bone(cstring name, int index, int parent = -1) : m_name(name), m_index(index), m_parent(parent) {}

		string m_name = "";
		int m_index = 0;
		int m_parent = -1;

		attr_ vec3 m_position = vec3(0.f);
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = vec3(1.f);

		mat4 m_pose_local;
		mat4 m_pose;

		vector<Node3*> m_attached_nodes;
	};

	export_ class refl_ MUD_GFX_EXPORT Skeleton
	{
	public:
		Skeleton();
		Skeleton(cstring name, int num_bones);

		Bone& add_bone(cstring name, int parent = -1);
		Bone* find_bone(cstring name);
		void update_bones();

		cstring m_name;
		vector<Bone> m_bones;
		vector<Animation*> m_animations;
	};

	export_ struct refl_ MUD_GFX_EXPORT Joint
	{
		size_t m_bone;
		mat4 m_inverse_bind;
		mat4 m_joint;
	};

	export_ class refl_ MUD_GFX_EXPORT Skin
	{
	public:
		Skin();
		Skin(Skeleton& skeleton, int num_joints);
		Skin(const Skin& copy, Skeleton& skeleton);
		~Skin();

		void add_joint(cstring bone, const mat4& inverse_bind);
		Joint* find_bone_joint(cstring name);
		void update_joints();

		Skeleton* m_skeleton;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		const bgfx::Memory* m_memory = nullptr;
		//vector<float> m_texture_data;

		vector<Joint> m_joints;
	};

	export_ class refl_ MUD_GFX_EXPORT Rig
	{
	public:
		Rig();

		Rig(const Rig& rig);
		Rig& operator=(const Rig& rig);

		void update_rig();

		Skeleton m_skeleton;
		vector<Skin> m_skins;
	};
}

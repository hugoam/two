//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Animation.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#include <vector>
#include <string>

namespace mud
{
	using string = std::string;

	struct _refl_ MUD_GFX_EXPORT Bone
	{
		Bone() {}
		Bone(cstring name, int index, int parent = -1) : m_name(name), m_index(index), m_parent(parent) {}

		string m_name = "";
		int m_index = 0;
		int m_parent = -1;

		_attr_ _mut_ vec3 m_position = Zero3;
		_attr_ _mut_ quat m_rotation = ZeroQuat;
		_attr_ _mut_ vec3 m_scale = Unit3;

		mat4 m_pose_local;
		mat4 m_pose;

		std::vector<Node3*> m_attached_nodes;
	};

	class _refl_ MUD_GFX_EXPORT Skeleton
	{
	public:
		Skeleton();
		Skeleton(cstring name, int num_bones);

		Bone& add_bone(cstring name, int parent = -1);
		Bone* find_bone(cstring name);
		void update_bones();

		cstring m_name;
		std::vector<Bone> m_bones;
	};

	struct _refl_ MUD_GFX_EXPORT Joint
	{
		size_t m_bone;
		mat4 m_inverse_bind;
		mat4 m_joint;
	};

	class _refl_ MUD_GFX_EXPORT Skin
	{
	public:
		Skin(Skeleton& skeleton, int num_joints);
		Skin(const Skin& copy, Skeleton& skeleton);

		void add_joint(cstring bone, const mat4& inverse_bind);
		void update_joints();

		Skeleton* m_skeleton;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		std::vector<float> m_texture_data;

		std::vector<Joint> m_joints;
	};

	class _refl_ MUD_GFX_EXPORT Rig
	{
	public:
		Rig();

		Rig(const Rig& rig);
		Rig& operator=(const Rig& rig);

		void update_rig();

		Skeleton m_skeleton;
		std::vector<Skin> m_skins;
		std::vector<Animation> m_animations;
	};
}

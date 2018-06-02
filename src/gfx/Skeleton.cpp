//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Skeleton.h>
#include <gfx/Renderer.h>
#endif

#include <bx/math.h>

#define SKELETON_TEXTURE_SIZE 256

namespace mud
{
	Skeleton::Skeleton()
	{}

	Skeleton::Skeleton(cstring name, int num_bones)
		: m_name(name)
	{
		m_bones.reserve(num_bones);
	}

	void Skeleton::update_bones()
	{
		for(Bone& bone : m_bones)
		{
			if(bone.m_parent > -1)
				bone.m_pose = m_bones[bone.m_parent].m_pose * bone.m_pose_local;
			else
				bone.m_pose = bone.m_pose_local;
		}
	}

	Bone& Skeleton::add_bone(cstring name, int parent)
	{		
		m_bones.emplace_back(name, m_bones.size(), parent);
		return m_bones.back();
	}

	Bone* Skeleton::find_bone(cstring name)
	{
		for(size_t i = 0; i < m_bones.size(); i++)
			if(m_bones[i].m_name == name)
				return &m_bones[i];
		return nullptr;
	}

	Skin::Skin(Skeleton& skeleton, int num_joints)
		: m_skeleton(&skeleton)
	{
		int height = num_joints / SKELETON_TEXTURE_SIZE;
		if(num_joints % SKELETON_TEXTURE_SIZE)
			height++;

		m_texture = bgfx::createTexture2D(SKELETON_TEXTURE_SIZE, uint16_t(height * 4), false, 1, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT | GFX_TEXTURE_CLAMP);
		m_texture_data.resize(SKELETON_TEXTURE_SIZE * height * 4 * 4);
	}

	Skin::Skin(const Skin& copy, Skeleton& skeleton)
		: Skin(skeleton, copy.m_joints.size())
	{
		m_joints = copy.m_joints;
		m_skeleton = &skeleton;
	}

	void Skin::add_joint(cstring bone, const mat4& inverse_bind)
	{
		Joint joint = { size_t(m_skeleton->find_bone(bone)->m_index), inverse_bind, mat4{} };
		m_joints.push_back(joint);
	}

	void Skin::update_joints()
	{
		int height = m_joints.size() / SKELETON_TEXTURE_SIZE;
		if(m_joints.size() % SKELETON_TEXTURE_SIZE)
			height++;

		int index = 0;
		for(Joint& joint : m_joints)
		{
			joint.m_joint = m_skeleton->m_bones[joint.m_bone].m_pose * joint.m_inverse_bind;

			float* texture = m_texture_data.data();
			int offset = ((index / SKELETON_TEXTURE_SIZE) * SKELETON_TEXTURE_SIZE) * 4 * 4 + (index % SKELETON_TEXTURE_SIZE) * 4;
			index++;

			//debug_print_mat(joint.m_joint);

			for(int i = 0; i < 4; ++i)
			{
				texture[offset + 0] = joint.m_joint[0][i];
				texture[offset + 1] = joint.m_joint[1][i];
				texture[offset + 2] = joint.m_joint[2][i];
				texture[offset + 3] = joint.m_joint[3][i];
				offset += SKELETON_TEXTURE_SIZE * 4;
			}
		}

		const bgfx::Memory* mem = bgfx::makeRef(m_texture_data.data(), sizeof(float) * m_texture_data.size());
		bgfx::updateTexture2D(m_texture, 0, 0, 0, 0, SKELETON_TEXTURE_SIZE, uint16_t(height * 4), mem);
	}

	Rig::Rig()
	{}

	Rig::Rig(const Rig& rig)
		: m_skeleton(rig.m_skeleton)
	{
		for(const Skin& skin : rig.m_skins)
			m_skins.emplace_back(skin, m_skeleton);
	}

	Rig& Rig::operator=(const Rig& rig)
	{
		m_skeleton = rig.m_skeleton;
		for(const Skin& skin : rig.m_skins)
			m_skins.emplace_back(skin, m_skeleton);
		m_animations = rig.m_animations;
		return *this;
	}

	void Rig::update_rig()
	{
		m_skeleton.update_bones();

		for(Skin& skin : m_skins)
			skin.update_joints();
	}
}


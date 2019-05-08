//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx;
#else
#include <infra/Sort.h>
#include <math/Vec.hpp>
#include <gfx/Skeleton.h>
#include <gfx/Renderer.h>
#endif

#include <algorithm>

#include <cstdio>

#define SKELETON_TEXTURE_SIZE 256

namespace two
{
	Skeleton::Skeleton()
	{}

	Skeleton::Skeleton(cstring name, int num_bones)
		: m_name(name)
	{
		m_bones.reserve(num_bones);
	}

	uint32_t Skeleton::add_bone(cstring name, uint32_t parent)
	{
		const uint32_t index = uint32_t(m_bones.size());
		m_names.push_back(name);
		m_bones.push_back(Node3(mat4(), parent));
		return index;
	}

	uint32_t Skeleton::bone_index(cstring name) const
	{
		for(size_t i = 0; i < m_names.size(); i++)
			if(m_names[i] == name)
				return i;
		return UINT32_MAX;
	}

	Node3* Skeleton::find_bone(cstring name)
	{
		uint32_t index = this->bone_index(name);
		return index != UINT32_MAX ? &m_bones[index] : nullptr;
	}

	Skin::Skin() {}
	Skin::Skin(Skeleton& skeleton, int num_joints)
		: m_skeleton(&skeleton)
	{}

	Skin::Skin(const Skin& copy, Skeleton& skeleton)
		: Skin(skeleton, int(copy.m_joints.size()))
	{
		m_joints = copy.m_joints;
		m_skeleton = &skeleton;
	}

	Skin::~Skin()
	{
		if(bgfx::isValid(m_texture))
			bgfx::destroy(m_texture);
	}

	void Skin::add_joint(cstring bone, const mat4& inverse_bind)
	{
		Joint joint = { m_skeleton->bone_index(bone), inverse_bind, mat4() };
		m_joints.push_back(joint);
	}

	void Skin::update_joints()
	{
		uint height = uint(m_joints.size()) / SKELETON_TEXTURE_SIZE;
		if(m_joints.size() % SKELETON_TEXTURE_SIZE)
			height++;
		const uvec2 size = uvec2(SKELETON_TEXTURE_SIZE, height * 4);

		if(!bgfx::isValid(m_texture))
			m_texture = bgfx::createTexture2D(size.x, size.y, false, 1, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP);
			//m_texture = { size, false, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT | TEXTURE_CLAMP };
		
		m_memory = bgfx::alloc(size.x * size.y * 4 * sizeof(float));

		int index = 0;
		for(Joint& joint : m_joints)
		{
			joint.m_joint = m_skeleton->m_bones[joint.m_bone].m_transform * joint.m_inverse_bind;

			float* texture = (float*)m_memory->data;
			//float* texture = m_texture_data.data();
			int offset = ((index / SKELETON_TEXTURE_SIZE) * SKELETON_TEXTURE_SIZE) * 4 * 4 + (index % SKELETON_TEXTURE_SIZE) * 4;
			index++;

			//debug_print_mat(joint.m_joint);

			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 4; ++j)
					texture[offset + j] = joint.m_joint[j][i];
				offset += SKELETON_TEXTURE_SIZE * 4;
			}
		}

		//const bgfx::Memory* mem = bgfx::makeRef(m_texture_data.data(), sizeof(float) * m_texture_data.size());
		bgfx::updateTexture2D(m_texture, 0, 0, 0, 0, SKELETON_TEXTURE_SIZE, uint16_t(height * 4), m_memory);
	}

	Rig::Rig()
	{}

	Rig::Rig(const Rig& rig)
		: m_skeleton(rig.m_skeleton)
	{
		for(const Skin& skin : rig.m_skins)
			m_skins.push_back({ skin, m_skeleton });
	}

	Rig& Rig::operator=(const Rig& rig)
	{
		m_skeleton = rig.m_skeleton;
		m_skins.reserve(rig.m_skins.size());
		for(const Skin& skin : rig.m_skins)
			m_skins.push_back({ skin, m_skeleton });
		return *this;
	}

	void Rig::update_rig()
	{
		for(Skin& skin : m_skins)
			skin.update_joints();

		if(m_morphs.size() > 0)
		{
			m_weights.resize(m_morphs.size());

			for(uint32_t i = 0; i < m_morphs.size(); ++i)
			{
				m_weights[i] = { i, m_morphs[i] };
			}

			std::sort(m_weights.begin(), m_weights.end(), [](const MorphWeight& a, const MorphWeight& b) { return a.weight > b.weight; });
			// @todo fix that shit quicksort we implemented :D
			// quicksort(span<MorphWeight>(m_weights), [](const MorphWeight& a, const MorphWeight& b) { return a.weight < b.weight; });
		}
	}
}

#ifdef _DEBUG
#include <gfx/Gfx.h>
#include <math/Vec.hpp>
#include <geom/Shapes.h>
#include <geom/Symbol.h>
namespace two
{
	mat4 fix_bone_pose(Node3& bone)
	{
		return bxrotation(angle_axis(-c_pi * 0.5f, x3)) * bxscale(vec3(0.009999999776482582f)) * bone.m_transform;
	}

	void debug_draw_skeleton(Gnode& parent, const vec3& position, const quat& rotation, Rig& rig)
	{
		for(Node3& bone : rig.m_skeleton.m_bones)
		{
			mat4 pose = bxrotation(rotation) * fix_bone_pose(bone);
			Gnode& node = gfx::node(parent, position + vec3(pose * vec4(vec3(0.f), 1.f)));
			gfx::shape(node, Sphere(0.02f), Symbol());
		}
	}
}
#endif

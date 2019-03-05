//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#if 0
#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <refl/Class.h>
#include <infra/ToString.h>
#include <gfx/Types.h>
#include <gfx/Uniform.h>
#include <gfx/GfxSystem.h>
#include <gfx/Texture.h>
#endif

namespace mud
{
	UniformBlock::UniformBlock(Type& type, const string& name)
		: m_type(type)
		, m_name(name)
	{}

	void UniformBlock::pack_member(size_t size, Member& member)
	{
		if(m_uniforms.empty() || m_uniforms.back().m_space < size)
			m_uniforms.push_back({ "u_" + m_name + "_params_" + to_string(m_num_packed++), member.m_offset, bgfx::UniformType::Vec4 });

		m_uniforms.back().m_fields.push_back({ member.m_name, member.m_offset, size });
		m_uniforms.back().m_space -= size;
	}

	void UniformBlock::create_member(GfxSystem& gfx, const string& name, Member& member)
	{
		if(member.m_type->is<float>())
			pack_member(1, member);
		else if(member.m_type->is<vec2>())
			pack_member(2, member);
		else if(member.m_type->is<vec3>())
			pack_member(3, member);
		else if(member.m_type->is<vec4>() || member.m_type->is<Colour>())
			m_uniforms.push_back({ "u_" + name, member.m_offset, bgfx::UniformType::Vec4 });
		else if(member.m_type->is<Texture>())
			m_samplers.push_back({ "s_" + name, member.m_offset, uint8_t(m_samplers.size()), &gfx.default_texture(TextureHint::White), {} });
		else if(member.m_type->is<mat4>())
			m_uniforms.push_back({ "u_" + name, member.m_offset, bgfx::UniformType::Mat4 });

		else if(member.cls().m_members.size() > 0)
			for(Member& sub_member : member.cls().m_members)
				create_member(gfx, name, sub_member);
	}

	string UniformBlock::shader_decl()
	{
		for(Uniform& uniform : m_uniforms)
			if(!uniform.m_fields.empty())
			{
				string uniform_decl = "uniform vec4 " + uniform.m_name + "\n";
				for(Uniform::Field& field : uniform.m_fields)
					uniform_decl += "#define u_" + field.m_name + uniform.m_name + "";
			}

		return "";
	}

	void UniformBlock::create(GfxSystem& gfx)
	{
		for(Member& member : cls(m_type).m_members)
			create_member(gfx, member.m_name, member);

		for(Uniform& uniform : m_uniforms)
			uniform.create();

		for(Sampler& sampler : m_samplers)
			sampler.create();
	}
}
#endif

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#include <obj/Type.h>
#include <obj/TypeUtils.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Texture.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#endif

namespace mud
{
	using string = std::string;

	// @todo automatical definition of structs to uniforms using reflection
	// - vectors and floats are packed to Vec4 in the order they appear, adding padding if next vector is too big to fit
	// - enums are sent as a define switch using enum value label
	// - booleans are sent as a define switch using parameter name

	export_ struct MUD_GFX_EXPORT Uniform
	{
		Uniform(const string& name, Address member, bgfx::UniformType::Enum type) : m_name(name), m_member(member), m_type(type), m_floats(16) {}

		string m_name;
		Address m_member;
		bgfx::UniformType::Enum m_type;
		bgfx::UniformHandle m_uniform;
		std::vector<float> m_floats;

		struct Field
		{
			string m_name;
			Address m_member;
			size_t m_size;
		};
		std::vector<Field> m_fields;
		size_t m_space = 4;

		void create()
		{
			m_uniform = bgfx::createUniform(m_name.c_str(), m_type);
		}

		template <class T>
		void upload(T& object)
		{
			if(m_fields.empty())
			{
				void* T::* mem = reinterpret_cast<void* T::*>(m_member.value);
				bgfx::setUniform(m_uniform, &(object.*mem));
			}
			else
			{
				size_t offset = 0;
				for(Field& field : m_fields)
				{
					void* T::* mem = reinterpret_cast<void* T::*>(field.m_member.value);
					float* value = (float*) &(object.*mem);
					std::copy(value, value + field.m_size, m_floats.data() + offset);
					offset += field.m_size;
				}
				bgfx::setUniform(m_uniform, m_floats.data());
			}
		}
	};

	export_ struct MUD_GFX_EXPORT Sampler
	{
		string m_name;
		Address m_member;
		uint8_t m_stage;
		Texture* m_default;
		bgfx::UniformHandle m_uniform;

		void create()
		{
			m_uniform = bgfx::createUniform(m_name.c_str(), bgfx::UniformType::Int1);
		}

		template <class T>
		void upload(T& object)
		{
			void* T::* mem = reinterpret_cast<void* T::*>(m_member.value);
			Texture* texture = (Texture*)(object.*mem);
			bgfx::setTexture(m_stage, m_uniform, texture ? texture->m_texture : m_default->m_texture);
		}
	};

	export_ struct MUD_GFX_EXPORT UniformBlock
	{
		UniformBlock(Type& type, const string& name);

		Type& m_type;
		string m_name;
		std::vector<Uniform> m_uniforms;
		std::vector<Sampler> m_samplers;
		string m_shader_decl;
		size_t m_num_packed = 0;

		void pack_member(size_t size, Member& member);
		void create_member(GfxSystem& gfx_system, const string& name, Member& member);
		string shader_decl();
		void create(GfxSystem& gfx_system);
	};
	
	template <class T>
	struct TypedUniformBlock : public UniformBlock
	{
		TypedUniformBlock(const string& name)
			: UniformBlock(type<T>(), name)
		{}

		void upload(T& object)
		{
			for(Uniform& uniform : m_uniforms)
				uniform.upload<T>(object);

			for(Sampler& sampler : m_samplers)
				sampler.upload<T>(object);
		}
	};
}

//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <obj/Unique.h>
#endif
#include <gfx/Forward.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

namespace mud
{
	using cstring = const char*;

	export_ enum class refl_ ShaderType : unsigned int
	{
		Fragment,
		Vertex,
		Count
	};

	export_ struct MUD_GFX_EXPORT ShaderDefine
	{
		cstring m_name;
		cstring m_value;
	};

	export_ struct MUD_GFX_EXPORT ShaderBlock
	{
		array<cstring> m_options;
		array<cstring> m_modes;
		array<ShaderDefine> m_defines;
	};

	export_ struct MUD_GFX_EXPORT ProgramBlock
	{
		// maps a block shader option to the program option shift
		uint8_t m_option_shift;
		uint8_t m_mode_shift;
	};

	export_ struct MUD_GFX_EXPORT ProgramBlockArray
	{
		// maps a block index to its shader options array
		ProgramBlock m_shader_blocks[32];
		uint8_t m_next_option = 0;
	};

	export_ class refl_ MUD_GFX_EXPORT Program
	{
	public:
		struct Version
		{
			uint32_t m_update;
			bgfx::ProgramHandle m_program;
		};

	public:
		Program(cstring name);
		Program(cstring name, array<GfxBlock*> blocks, array<cstring> sources);
		~Program();

		attr_ cstring name();

		uint8_t block_option_shift(uint8_t block)
		{
			return m_blocks.m_shader_blocks[block].m_option_shift;
		}

		uint8_t block_mode_shift(uint8_t block)
		{
			return m_blocks.m_shader_blocks[block].m_mode_shift;
		}

		void reload() { m_update++; }

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ShaderVersion& config);

		void register_blocks(array<GfxBlock*> blocks);
		void register_block(const GfxBlock& block);
		void register_options(uint8_t block, array<cstring> options);
		void register_modes(uint8_t block, array<cstring> modes);

		ProgramBlockArray m_blocks;

		cstring m_sources[size_t(ShaderType::Count)] = { nullptr, nullptr };

		uint32_t m_update;

		struct Impl;
		unique_ptr<Impl> m_impl;

		static GfxSystem* ms_gfx_system;
	};
}

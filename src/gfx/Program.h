//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/decls.h>
#include <infra/Array.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
{
	using cstring = const char*;
	
	export_ enum class refl_ ShaderType : unsigned int
	{
		Compute,
		Fragment,
		Geometry,
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
			Version() {}
			uint64_t m_version = 0;
			uint32_t m_update = 0;
			bgfx::ProgramHandle m_program = BGFX_INVALID_HANDLE;
		};

	public:
		Program(const string& name, bool compute = false);
		Program(const string& name, array<GfxBlock*> blocks, array<cstring> sources);
		~Program();

		attr_ cstring name();

		uint8_t block_option_shift(uint8_t block) const
		{
			return m_blocks.m_shader_blocks[block].m_option_shift;
		}

		uint8_t block_mode_shift(uint8_t block) const
		{
			return m_blocks.m_shader_blocks[block].m_mode_shift;
		}

		void reload() { m_update++; }

		void compile(GfxSystem& gfx_system, Version& version, bool compute = false);

		void update(GfxSystem& gfx_system);

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ShaderVersion& config);

		ShaderVersion shader_version(Version& version);

		void register_blocks(array<GfxBlock*> blocks);
		void register_block(const GfxBlock& block);
		void register_options(uint8_t block, array<cstring> options);
		void register_modes(uint8_t block, array<cstring> modes);

		ProgramBlockArray m_blocks;

		cstring m_sources[size_t(ShaderType::Count)] = {};

		bool m_compute = false;
		uint32_t m_update = 1;

		struct Impl;
		unique<Impl> m_impl;

		static GfxSystem* ms_gfx_system;
	};
}

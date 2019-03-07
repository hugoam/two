//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/span.h>
#include <stl/table.h>
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
		span<cstring> m_options;
		span<cstring> m_modes;
		span<ShaderDefine> m_defines;
	};

	export_ struct ProgramBlock
	{
		// maps a block shader option to the program option shift
		uint8_t m_option_shift;
		uint8_t m_mode_shift;
	};

	export_ enum class refl_ MaterialBlock : unsigned int
	{
		Base,
		Alpha,
		Solid,
		Point,
		Line,
		Pbr,
		Fresnel,
		User,
		Count
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
		~Program();

		attr_ string m_name;

		meth_ void set_source(ShaderType type, const string& source);

		string defines(const ShaderVersion& version) const;

		uint8_t block_option_shift(uint8_t block) const
		{
			return m_shader_blocks[block].m_option_shift;
		}

		uint8_t block_mode_shift(uint8_t block) const
		{
			return m_shader_blocks[block].m_mode_shift;
		}

		void reload() { m_update++; }

		void compile(GfxSystem& gfx, Version& version, bool compute = false);

		void update(GfxSystem& gfx);

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ShaderVersion& config);

		ShaderVersion shader_version(Version& version);

		void register_blocks(span<GfxBlock*> blocks);
		void register_block(const GfxBlock& block);
		void register_options(uint8_t block, span<cstring> options);
		void register_modes(uint8_t block, span<cstring> modes);

		// maps a block index to its shader options span
		ProgramBlock m_shader_blocks[32];
		uint8_t m_next_option = 0;

		table<ShaderType, string> m_sources = {};
		table<MaterialBlock, bool> m_blocks = {};

		bool m_compute = false;
		uint32_t m_update = 1;

		struct Impl;
		unique<Impl> m_impl;

		static GfxSystem* ms_gfx_system;
	};
}

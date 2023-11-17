//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>

namespace two
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

	export_ enum class refl_ PassType : unsigned int
	{
		VoxelGI,
		Lightmap,
		Shadowmap,
		Probes,
		Clear,
		Depth,
		Normals,
		Shadow,
		Geometry,
		Lights,
		Opaque,
		Background,
		Particles,
		Alpha,
		Solid,
		Effects,
		PostProcess,
		Flip,

		Count
	};

	export_ struct refl_ TWO_GFX_EXPORT ShaderDefine
	{
		attr_ string m_name;
		attr_ string m_value;
	};

	export_ struct refl_ TWO_GFX_EXPORT ShaderBlock
	{
		constr_ ShaderBlock();
		ShaderBlock(span<cstring> options, span<cstring> modes);

		attr_ uint8_t m_index;
		attr_ vector<string> m_options;
		attr_ vector<string> m_modes;
		vector<ShaderDefine> m_defines;

		meth_ void add_option(const string& name) { m_options.push_back(name); }
		meth_ void add_mode(const string& name) { m_modes.push_back(name); }
		meth_ void add_define(const string& name, const string& value) { m_defines.push_back({ name, value }); }
	};

	export_ struct refl_ TWO_GFX_EXPORT ProgramMode
	{
		attr_ string name;
		attr_ uint32_t size;
		attr_ uint32_t shift;
		attr_ uint32_t mask;
	};

	export_ struct refl_ TWO_GFX_EXPORT ProgramBlock
	{
		// maps a block shader option to the program option shift
		attr_ bool m_enabled = false;
		attr_ uint8_t m_option_shift = 0;
		attr_ uint8_t m_mode_shift = 0;
	};

	export_ enum class refl_ MaterialBlock : unsigned int
	{
		Base,
		Alpha,
		Solid,
		Point,
		Line,
		Lit,
		Pbr,
		Phong,
		Fresnel,
		User,
		Count
	};

	export_ class refl_ TWO_GFX_EXPORT Program
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

		meth_ void set_block(MaterialBlock block, bool enabled = true);
		meth_ void set_pass(PassType type, bool enabled = true);
		meth_ void set_source(ShaderType type, const string& source);

		string defines(const ProgramVersion& version) const;

		void reload() { m_update++; }

		void compile(GfxSystem& gfx, Version& version, bool compute = false);

		void update(GfxSystem& gfx);

		bgfx::ProgramHandle default_version();
		bgfx::ProgramHandle version(const ProgramVersion& config);

		ProgramVersion program(Version& version);

		meth_ void register_blocks(const Program& program);

		meth_ void register_block(const ShaderBlock& block);

		void set_blocks(span<MaterialBlock> blocks);
		void register_blocks(span<ShaderBlock*> blocks);
		void register_options(uint8_t block, span<string> options);
		void register_modes(uint8_t block, span<string> modes);

		// maps a block index to its shader options span
		ProgramBlock m_shader_blocks[32] = {};
		uint8_t m_next_option = 0;
		vector<ShaderBlock*> m_registered_blocks;

		table<MaterialBlock, bool> m_blocks = {};
		table<ShaderType, string> m_sources = {};
		table<PassType, bool> m_passes = {};

		vector<string> m_options;
		vector<string> m_modes;

		vector<ShaderDefine> m_defines;

		bool m_compute = false;
		uint32_t m_update = 1;

		uint32_t m_primitives = 0;

		static GfxSystem* ms_gfx;

	private:
		struct Impl;
		unique<Impl> m_impl;
	};
}

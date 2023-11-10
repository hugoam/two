//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <cstring>
#include <cstdio>
#include <bx/platform.h>
#include <bx/readerwriter.h>
#include <bgfx/bgfx.h>
#include <gfx/Cpp20.h>
module two.gfx;
#else
#include <cstring>
#include <cstdio>
#include <bx/platform.h>
#include <bx/readerwriter.h>
#include <bgfx/bgfx.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <stl/hash_base.hpp>
#include <stl/algorithm.h>
#include <stl/table.h>
#include <infra/ToString.h>
#include <infra/Log.h>
#include <infra/File.h>
#include <gfx/Program.h>
#include <gfx/GfxSystem.h>
#include <gfx/Texture.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Shader.h>
#include <gfx/Renderer.h>
#include <gfx/Pipeline.h>
#endif

namespace bgfx
{
	int compileShader(int _argc, const char* _argv[]);
	void getShaderError(char* _outputText, uint16_t& _outputSize);
}

namespace two
{
	static const bgfx::Memory* load_mem(bx::FileReaderI& reader, const char* file_path)
	{
		if(!bx::open(&reader, file_path))
		{
			error("failed to open file %s", file_path);
			return nullptr;
		}

		uint32_t size = uint32_t(bx::getSize(&reader));
		const bgfx::Memory* mem = bgfx::alloc(size + 1);
		bx::read(&reader, mem->data, size);
		bx::close(&reader);
		mem->data[mem->size - 1] = '\0';
		return mem;
	}

	bgfx::ShaderHandle load_shader(bx::FileReaderI& reader, cstring path)
	{
		if(!file_exists(path))
			return BGFX_INVALID_HANDLE;

		bgfx::ShaderHandle shader = bgfx::createShader(load_mem(reader, path));
		bgfx::setName(shader, file_name(path).c_str());
		return shader;
	}

	bgfx::ProgramHandle load_compute_program(bx::FileReaderI& reader, const string& shader_path)
	{
		const string  cs_path = shader_path + "_cs";

		bgfx::ShaderHandle compute_shader = load_shader(reader, cs_path.c_str());

		return bgfx::createProgram(compute_shader, true);
	}

	bgfx::ProgramHandle load_program(bx::FileReaderI& reader, const string& shader_path)
	{
		const string vs_path = shader_path + "_vs";
		const string gs_path = shader_path + "_gs";
		const string fs_path = shader_path + "_fs";

		bgfx::ShaderHandle vertex_shader = load_shader(reader, vs_path.c_str());
		bgfx::ShaderHandle geometry_shader = load_shader(reader, gs_path.c_str());
		bgfx::ShaderHandle fragment_shader = load_shader(reader, fs_path.c_str());

		bgfx::ProgramHandle program = bgfx::isValid(geometry_shader) ? bgfx::createProgram(vertex_shader, geometry_shader, fragment_shader, true)
																	 : bgfx::createProgram(vertex_shader, fragment_shader, true);

		if(!bgfx::isValid(program))
			error("gfx - failed to load program %s", shader_path.c_str());
		//else
		//	info("gfx - loaded program %s id %i", shader_path.c_str(), int(program.idx));

		return program;
	}

	static table<ShaderType, cstring> c_shader_suffixes = 
	{
		"_cs.sc",
		"_fs.sc",
		"_gs.sc",
		"_vs.sc",
	};

	string shader_path(GfxSystem& gfx, const string& name, ShaderType shader_type)
	{
		string suffix = c_shader_suffixes[shader_type];
		return gfx.m_resource_path + "/shaders/" + name + suffix;
	}

#ifdef TWO_LIVE_SHADER_COMPILER
	bool compile_shader(GfxSystem& gfx, const string& name, const string& suffix, ShaderType shader_type, const string& defines_in, const string& source)
	{
		string defines = defines_in;
		string source_path = shader_path(gfx, name, shader_type);

		if(source != "")
		{
			write_file(source_path, source);
		}

#ifdef _DEBUG
		//bool debug = true;
#else
		//bool debug = false;
#endif

		static table<ShaderType, cstring> output_suffixes = { "_cs", "_fs", "_gs", "_vs" };

		string output_suffix = output_suffixes[shader_type];
		string output_path = gfx.m_resource_path + "/shaders/compiled/" + name + suffix + output_suffix;

		create_file_tree(output_path);

		info("gfx - compiling shader : %s", source_path.c_str());

		string include = gfx.m_resource_path + "/shaders/";
		string varying_path = gfx.m_resource_path + "/shaders/varying.def.sc";

		enum class Target { GLSL, ESSL, HLSL, Metal, SPIRV };

		auto get_target = []
		{
			using RendererType = bgfx::RendererType;
			auto renderer = bgfx::getRendererType();

			if (renderer == RendererType::OpenGLES)			return Target::GLSL;
			else if (renderer == RendererType::OpenGL)		return Target::GLSL;
			else if (renderer == RendererType::Direct3D11)	return Target::HLSL;
			else if (renderer == RendererType::Direct3D12)	return Target::HLSL;
			else if (renderer == RendererType::Metal)		return Target::Metal;
			else if (renderer == RendererType::Vulkan)		return Target::SPIRV;
			else if (renderer == RendererType::WebGPU)		return Target::SPIRV;
			else return Target::GLSL;
		};

		Target target = get_target();

		if(target == Target::ESSL || target == Target::Metal)
			defines += "NO_TEXEL_FETCH;";

		vector<cstring> args;
		auto push_arg = [&args](cstring name, cstring arg) { args.push_back(name); args.push_back(arg); };

		static table<ShaderType, cstring> types = { "compute", "fragment", "geometry", "vertex" };

		push_arg("-f", source_path.c_str());
		push_arg("-o", output_path.c_str());
		push_arg("-i", include.c_str());
		args.push_back("--depends");
		push_arg("--varyingdef", varying_path.c_str());
		push_arg("--define", defines.c_str());
		push_arg("--type", types[shader_type]);

		//if(debug)
			//args.push_back("--debug");

		args.push_back("-O3");

		if(target == Target::GLSL)
		{
			push_arg("--platform", "linux");
			//push_arg("--profile", "120");
			push_arg("--profile", "130");
			//push_arg("--profile", "430");
		}
		else if(target == Target::ESSL)
		{
			push_arg("--platform", "android");
		}
		else if(target == Target::HLSL)
		{
			static table<ShaderType, cstring> profiles = { "cs_5_0", "ps_5_0", "gs_5_0", "vs_5_0" };
			push_arg("--platform", "windows");
			push_arg("--profile", profiles[shader_type]);
		}
		else if(target == Target::Metal)
		{
			push_arg("--platform", "osx");
			push_arg("--profile", "metal");
		}
		else if (target == Target::SPIRV)
		{
			push_arg("--platform", "linux");
			push_arg("--profile", "spirv");
		}

		int result = bgfx::compileShader(uint32_t(args.size()), args.data());

		if(result == EXIT_FAILURE)
		{
			char output_text[1024 * 128];
			uint16_t output_size;
			bgfx::getShaderError(output_text, output_size);

			error("failed to compile %s (%s), defines = %s\n", source_path.c_str(), output_path.c_str(), defines.c_str());
			printf("%s\n", output_text);
			return false;
		}

		return true;
	}
#endif

	struct Program::Impl
	{
		map<uint64_t, Version> m_versions;
	};

	GfxSystem* Program::ms_gfx = nullptr;

	static uint8_t s_block_index = 1;

	ShaderBlock::ShaderBlock()
		: m_index(s_block_index++)
	{}

	ShaderBlock::ShaderBlock(span<cstring> options, span<cstring> modes)
		: m_index(s_block_index++)
	{
		for(cstring option : options)
			m_options.push_back(option);
		for(cstring mode : modes)
			m_modes.push_back(mode);
	}

	Program::Program(const string& name, bool compute)
		: m_name(name)
		, m_compute(compute)
		, m_impl(make_unique<Impl>())
	{
		static string options[] = { "INSTANCING", "BILLBOARD", "SKELETON", "MORPHTARGET", "QNORMALS", "VFLIP", "MRT", "DEFERRED", "CLUSTERED" };
		this->register_options(0, options);

		this->set_block(MaterialBlock::Base);

		if (normalize_bone_indices())
			m_defines.push_back({ "NORMALIZED_BONES", "" });

		if constexpr(ZONES_BUFFER)
			m_defines.push_back({ "ZONES_BUFFER" , "" });

		if constexpr(LIGHTS_BUFFER)
			m_defines.push_back({ "LIGHTS_BUFFER" , "" });

		if constexpr(MATERIALS_BUFFER)
			m_defines.push_back({ "MATERIALS_BUFFER" , "" });
	}

	Program::~Program()
	{}

	void Program::set_block(MaterialBlock type, bool enabled)
	{
		static table<MaterialBlock, ShaderBlock*> shader_blocks =
		{ {
			&MaterialBase::s_block,
			&MaterialAlpha::s_block,
			&MaterialSolid::s_block,
			&MaterialPoint::s_block,
			&MaterialLine::s_block,
			&MaterialLit::s_block,
			&MaterialPbr::s_block,
			&MaterialPhong::s_block,
			&MaterialFresnel::s_block,
			&MaterialUser::s_block,
		} };

		m_blocks[type] = enabled;
		this->register_block(*shader_blocks[type]);
	}

	void Program::set_blocks(span<MaterialBlock> blocks)
	{
		for(MaterialBlock type : blocks)
		{
			this->set_block(type);
		}
	}

	void Program::register_blocks(const Program& program)
	{
		this->register_blocks(program.m_registered_blocks);
	}

	void Program::register_blocks(span<ShaderBlock*> blocks)
	{
		for(ShaderBlock* block : blocks)
		{
			this->register_block(*block);
			m_registered_blocks.push_back(block);
		}
	}

	void Program::register_block(const ShaderBlock& block)
	{
		assert(block.m_index < 32);
		m_shader_blocks[block.m_index].m_enabled = true;
		this->register_options(block.m_index, block.m_options);
		this->register_modes(block.m_index, block.m_modes);
		if(block.m_defines.size() > 0)
			prepend(m_defines, block.m_defines);
	}

	void Program::register_options(uint8_t block, span<string> options)
	{
		assert(block < 32);
		m_shader_blocks[block].m_enabled = true;
		m_shader_blocks[block].m_option_shift = uint8_t(m_options.size());

		for(size_t i = 0; i < options.size(); ++i)
			m_options.push_back(options[i]);
	}

	void Program::register_modes(uint8_t block, span<string> modes)
	{
		assert(block < 32);
		m_shader_blocks[block].m_enabled = true;
		m_shader_blocks[block].m_mode_shift = uint8_t(m_modes.size());

		for(size_t i = 0; i < modes.size(); ++i)
			m_modes.push_back(modes[i]);
	}

	void Program::set_pass(PassType type, bool enabled)
	{
		m_passes[type] = enabled;
	}

	void Program::set_source(ShaderType type, const string& source)
	{
		m_sources[type] = source;
	}

	string Program::defines(const ProgramVersion& version) const
	{
		string defines = "";

		for(size_t option = 0; option < 32; ++option)
			if(version.m_options & uint32_t(1 << option))
				defines += m_options[option] + ";";

		for(size_t mode = 0; mode < m_modes.size(); ++mode)
			defines += m_modes[mode] + "=" + to_string(version.m_modes[mode]) + ";";

		for(const ShaderDefine& define : m_defines)
			defines += string(define.m_name) + (define.m_value.empty() ? "" : "=" + define.m_value) + ";";

		return defines;
	}

	ProgramVersion Program::program(Version& version)
	{
		ProgramVersion config = { *this };
		memcpy(&config.m_options, &version.m_version, sizeof(uint64_t));
		return config;
	}

	void Program::compile(GfxSystem& gfx, Version& version, bool compute)
	{
		const ProgramVersion config = this->program(version);

		const string suffix = "_v" + to_string(version.m_version);
		const string defines = this->defines(config);

		const string full_name = m_name + suffix;

		info("gfx - compiling program %s", full_name.c_str());
		info("gfx - with defines: %s", defines.c_str());

		bool compiled = true;
#ifdef TWO_LIVE_SHADER_COMPILER
		if(compute)
		{
			compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Compute, defines, m_sources[ShaderType::Compute]);
		}
		else
		{
			compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Vertex, defines, m_sources[ShaderType::Vertex]);
			compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Fragment, defines, m_sources[ShaderType::Fragment]);

			if(file_exists(shader_path(gfx, m_name, ShaderType::Geometry).c_str()))
				compiled &= compile_shader(gfx, m_name, suffix, ShaderType::Geometry, defines, m_sources[ShaderType::Geometry]);
		}
#endif

		if(!compiled)
		{
			warn("gfx - failed to compile program %s : using last valid version instead", full_name.c_str());
			version.m_update = m_update;
			return;
		}

		const string compiled_path = gfx.m_resource_path + "/shaders/compiled/" + full_name;
		version.m_program = compute ? load_compute_program(gfx.file_reader(), compiled_path)
									: load_program(gfx.file_reader(), compiled_path);
		version.m_update = m_update;
	}

	void Program::update(GfxSystem& gfx)
	{
		for(auto& hash_version : m_impl->m_versions)
		{
			Version& version = hash_version.second;
			if(version.m_update < m_update)
			{
				this->compile(gfx, version, m_compute);
			}
		}
	}

	bgfx::ProgramHandle Program::default_version()
	{
		ProgramVersion config = { *this };
		return this->version(config);
	}

	bgfx::ProgramHandle Program::version(const ProgramVersion& config)
	{
		uint64_t version_hash = config.hash();

		Version& version = m_impl->m_versions[version_hash];
		if(version.m_update < m_update)
		{
			version.m_version = version_hash;
			this->compile(*ms_gfx, version, m_compute);
		}

		return version.m_program;
	}
}

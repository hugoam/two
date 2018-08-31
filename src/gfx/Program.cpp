//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <string>
#include <map>
#include <vector>
#include <fstream>
#endif

#include <bx/readerwriter.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <infra/EnumArray.h>
#include <infra/File.h>
#include <srlz/Serial.h>
#include <infra/StringConvert.h>
#include <gfx/Program.h>
#include <gfx/GfxSystem.h>
#include <gfx/Texture.h>
#include <gfx/Material.h>
#endif

namespace bgfx
{
	int compileShader(int _argc, const char* _argv[]);
	void getShaderError(char* _outputText, uint16_t& _outputSize);
}

namespace mud
{
	using string = std::string;

	static const bgfx::Memory* load_mem(bx::FileReaderI& reader, const char* file_path)
	{
		if(!bx::open(&reader, file_path))
		{
			printf("ERROR: failed to open file %s\n", file_path);
			return nullptr;
		}

		uint32_t size = uint32_t(bx::getSize(&reader));
		const bgfx::Memory* mem = bgfx::alloc(size + 1);
		bx::read(&reader, mem->data, size);
		bx::close(&reader);
		mem->data[mem->size - 1] = '\0';
		return mem;
	}

	bgfx::ProgramHandle load_program(bx::FileReaderI& reader, const string& shader_path)
	{
		const string vs_path = shader_path + "_vs";
		const string fs_path = shader_path + "_fs";

		bgfx::ShaderHandle vertexShader = bgfx::createShader(load_mem(reader, vs_path.c_str()));
		bgfx::ShaderHandle fragmentShader = bgfx::createShader(load_mem(reader, fs_path.c_str()));

		bgfx::ProgramHandle program = bgfx::createProgram(vertexShader, fragmentShader, true);

		if(!bgfx::isValid(program))
			printf("ERROR: failed to load program %s\n", shader_path.c_str());
		else
			printf("INFO: loaded program %s id %i\n", shader_path.c_str(), int(program.idx));

		return program;
	}

#ifdef MUD_LIVE_SHADER_COMPILER
	bool compile_shader(GfxSystem& gfx_system, cstring name, cstring suffix, ShaderType shader_type, cstring defines_in, cstring source)
	{
		string defines = defines_in;
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;

		string source_suffix = shader_type == ShaderType::Vertex ? "_vs.sc" : "_fs.sc";
		string source_path = string(gfx_system.m_resource_path) + "shaders/" + name + source_suffix;

		if(source != nullptr)
		{
			write_file(source_path.c_str(), source);
		}

#ifdef _DEBUG
		//bool debug = true;
#else
		//bool debug = false;
#endif

		string output_suffix = shader_type == ShaderType::Vertex ? "_vs" : "_fs";
		string output_path = string(gfx_system.m_resource_path) + "shaders/compiled/" + name + suffix + output_suffix;

		printf("INFO: Compiling Shader : %s\n", source_path.c_str());
		printf("INFO: Defines : %s\n", defines.c_str());

		string include = string(gfx_system.m_resource_path) + "shaders/";
		string varying_path = string(gfx_system.m_resource_path) + "shaders/varying.def.sc";

		enum Target { GLSL, ESSL, HLSL, Metal };
#if defined MUD_PLATFORM_WINDOWS
		Target target = is_opengl ? GLSL : HLSL;
#elif defined MUD_PLATFORM_LINUX
		Target target = GLSL;
#elif defined MUD_PLATFORM_EMSCRIPTEN
		Target target = ESSL;
#elif defined MUD_PLATFORM_OSX
		Target target = is_opengl ? GLSL : Metal;
#endif

		if(target == ESSL || target == Metal)
			defines += "NO_TEXEL_FETCH;";

		std::vector<cstring> args;
		auto push_arg = [](std::vector<cstring>& args, cstring name, cstring arg) { args.push_back(name); args.push_back(arg); };

		push_arg(args, "-f", source_path.c_str());
		push_arg(args, "-o", output_path.c_str());
		push_arg(args, "-i", include.c_str());
		args.push_back("--depends");
		push_arg(args, "--varyingdef", varying_path.c_str());
		push_arg(args, "--define", defines.c_str());
		push_arg(args, "--type", shader_type == ShaderType::Vertex ? "vertex" : "fragment");

		//if(debug)
			//args.push_back("--debug");

#ifndef MUD_PLATFORM_EMSCRIPTEN
		args.push_back("-O3");
#endif

		if (target == GLSL)
		{
			push_arg(args, "--platform", "linux");
			//push_arg(args, "--profile", "120");
			push_arg(args, "--profile", "130");
		}
		else if(target == ESSL)
		{
			push_arg(args, "--platform", "android");
		}
		else if(target == HLSL)
		{
			push_arg(args, "--platform", "windows");
			push_arg(args, "--profile", shader_type == ShaderType::Vertex ? "vs_5_0" : "ps_5_0");
		}
		else if (target == Metal)
		{
			push_arg(args, "--platform", "osx");
			push_arg(args, "--profile", "metal");
		}

		int result = bgfx::compileShader(args.size(), args.data());

		if(result == EXIT_FAILURE)
		{
			char output_text[90000];
			uint16_t output_size;
			bgfx::getShaderError(output_text, output_size);

			printf("ERROR: Failed to compile %s (%s), defines = %s\n", source_path.c_str(), output_path.c_str(), defines.c_str());
			printf("%s", output_text);
			return false;
		}

		return true;
	}
#endif

	struct Program::Impl
	{
		string m_name;

		std::map<uint64_t, Version> m_versions;
		std::vector<string> m_option_names;
		std::vector<string> m_mode_names;

		std::vector<ShaderDefine> m_defines;
	};

	GfxSystem* Program::ms_gfx_system = nullptr;

	Program::Program(cstring name)
		: m_impl(make_unique<Impl>())
	{
		m_impl->m_name = name;
		PbrBlock& pbr = pbr_block(*ms_gfx_system);

		static cstring options[6] = { "SKELETON", "INSTANCING", "BILLBOARD", "MRT", "DEFERRED", "CLUSTERED" };
		this->register_options(0, { options, 6 });
		this->register_options(pbr.m_index, pbr.m_shader_block->m_options);
	}

	Program::Program(cstring name, array<GfxBlock*> blocks, array<cstring> sources)
		: Program(name)
	{
		this->register_blocks(blocks);

		for(ShaderType shader_type = ShaderType(0); shader_type != ShaderType::Count; shader_type = ShaderType(uint32_t(shader_type) + 1))
			m_sources[size_t(shader_type)] = sources[size_t(shader_type)];
	}

	Program::~Program()
	{}

	cstring Program::name()
	{
		return m_impl->m_name.c_str();
	}

	bgfx::ProgramHandle Program::default_version()
	{
		ShaderVersion config(this);
		return this->version(config);
	}

	bgfx::ProgramHandle Program::version(const ShaderVersion& config)
	{
		uint64_t config_hash = config.hash();

		if(m_impl->m_versions.find(config_hash) == m_impl->m_versions.end() || m_impl->m_versions[config_hash].m_update < m_update)
		{
			string suffix = "_v" + to_string(config_hash);
			string full_name = m_impl->m_name + suffix;
			string defines = "";

			for(size_t option = 0; option < 32; ++option)
				if(config.m_options & uint32_t(1 << option))
					defines += m_impl->m_option_names[option] + ";";

			for(size_t mode = 0; mode < m_impl->m_mode_names.size(); ++mode)
				defines += m_impl->m_mode_names[mode] + "=" + to_string(config.m_modes[mode]) + ";";

			for(const ShaderDefine& define : m_impl->m_defines)
				defines += string(define.m_name) + "=" + define.m_value + ";";

			bool compiled = true;
#ifdef MUD_LIVE_SHADER_COMPILER
			compiled &= compile_shader(*ms_gfx_system, m_impl->m_name.c_str(), suffix.c_str(), ShaderType::Vertex, defines.c_str(), m_sources[size_t(ShaderType::Vertex)]);
			compiled &= compile_shader(*ms_gfx_system, m_impl->m_name.c_str(), suffix.c_str(), ShaderType::Fragment, defines.c_str(), m_sources[size_t(ShaderType::Fragment)]);
#endif

			if(compiled)
			{
				printf("INFO: loading program %s with options %s\n", full_name.c_str(), defines.c_str());
				string compiled_path = string(ms_gfx_system->m_resource_path) + "/shaders/compiled/" + full_name;
				m_impl->m_versions[config_hash] = { m_update, load_program(ms_gfx_system->file_reader(), compiled_path) };
			}
			else
			{
				printf("WARNING: failed to compile program %s : using last valid version instead\n", full_name.c_str());
				m_impl->m_versions[config_hash].m_update = m_update;
			}
		}

		return m_impl->m_versions[config_hash].m_program;
		//printf("Program name %s index %i\n", name.c_str(), m_program.idx);
	}

	template <class T, class U>
	inline void vector_prepend(std::vector<T>& vector, const U& other)
	{
		vector.insert(vector.begin(), other.begin(), other.end());
	}

	void Program::register_blocks(array<GfxBlock*> blocks)
	{
		for(GfxBlock* block : blocks)
			this->register_block(*block);
	}

	void Program::register_block(const GfxBlock& block)
	{
		this->register_options(block.m_index, block.m_shader_block->m_options);
		this->register_modes(block.m_index, block.m_shader_block->m_modes);
		vector_prepend(m_impl->m_defines, block.m_shader_block->m_defines);
	}

	void Program::register_options(uint8_t block, array<cstring> options)
	{
		m_blocks.m_shader_blocks[block].m_option_shift = uint8_t(m_impl->m_option_names.size());

		for(size_t i = 0; i < options.size(); ++i)
			m_impl->m_option_names.emplace_back(options[i]);
	}

	void Program::register_modes(uint8_t block, array<cstring> modes)
	{
		m_blocks.m_shader_blocks[block].m_mode_shift = uint8_t(m_impl->m_mode_names.size());

		for(size_t i = 0; i < modes.size(); ++i)
			m_impl->m_mode_names.emplace_back(modes[i]);
	}
}

//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.gltf;
#else
#include <cassert>
#include <iostream>
#include <fstream>

#include <json11.hpp>
using Json = json11::Json;

#include <type/DispatchDecl.h>
#include <stl/algorithm.h>
#include <infra/Log.h>
#include <infra/File.h>
#include <infra/StringOps.h>
#include <infra/StringConvert.h>
#include <type/Var.h>
#include <math/Stream.h>
#include <pool/Pool.h>
#include <srlz/Serial.h>
#include <refl/System.h>
#include <refl/Class.h>
#include <refl/Convert.h>
#include <math/VecJson.h>
#include <math/Interp.h>
#include <geom/Geometry.h>
#include <gltf/Gltf.h>
#include <gltf/Types.h>
#endif

#include <cstdio>

namespace two
{
	inline void from_json(const Json& j, PrimitiveType& mat)
	{
		mat = static_cast<PrimitiveType>(j.int_value());
	}
}

namespace two
{
	FromJson gltf_unpacker()
	{
		FromJson unpacker;
		dispatch_branch<mat4>(unpacker, +[](mat4& result, const Json& json) { from_json(json, result); });
		dispatch_branch<quat>(unpacker, +[](quat& result, const Json& json) { from_json(json, result); });
		return unpacker;
	}

	ToJson gltf_packer()
	{
		ToJson packer;
		dispatch_branch<glTFType>         (packer, +[](glTFType&          value, Json& json_value) { json_value = to_string(Ref(&value)); });
		dispatch_branch<glTFInterpolation>(packer, +[](glTFInterpolation& value, Json& json_value) { json_value = to_string(Ref(&value)); });
		dispatch_branch<glTFAlphaMode>    (packer, +[](glTFAlphaMode&     value, Json& json_value) { json_value = to_string(Ref(&value)); });
		return packer;
	}

	void setup_gltf(Module& gltf)
	{
		System::instance().load_modules({ &gltf });

		static vector<string> fixed_members(256);

		size_t index = 0;
		for(Type* type : system().m_types)
			if(string(type->m_name).find("glTF") == 0 && g_class[type->m_id] && !type->is<glTFAttributes>())
			{
				for(Member& member : cls(*type).m_members)
				{
					fixed_members[index] = to_camelcase(member.m_name);
					//printf("renamed member %s to %s\n", member.m_name, fixed_members[index].c_str());
					member.m_name = fixed_members[index].c_str();
					index++;
					assert(index < fixed_members.size());
				}
			}
	}

	template <class T>
	inline T bread(std::istream& stream) { T result; stream.read((char*)&result, sizeof(T)); return result; }

	void parse_glb(const string& path, Json& json, vector<uint8_t>& buffer)
	{
		std::ifstream file = std::ifstream(path.c_str(), std::ios::binary);

		uint32_t magic = bread<uint32_t>(file);
		uint32_t version = bread<uint32_t>(file);
		uint32_t length = bread<uint32_t>(file);
		UNUSED(length);

		if(magic != 0x46546C67 || version != 2)
		{
			error(".glb contents invalid");
			return;
		}

		while(!file.eof())
		{
			uint32_t chunk_length = bread<uint32_t>(file);
			uint32_t chunk_type = bread<uint32_t>(file);

			if(chunk_type == 0x4E4F534A)
			{
				std::string errors;
				string strjson = read(file, chunk_length);
				//printf("[debug] gltf .glb json contents: %s\n", strjson.c_str());
				json = Json::parse(strjson.c_str(), errors);
			}
			else if(chunk_type == 0x004E4942)
			{
				read(file, chunk_length, buffer);
			}
		}
	}

	// spec, for reference:
	// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#data-alignment

	struct glTFComponentLayout
	{
		int num_components;
		int component_size;
		int skip_every;
		int skip_bytes;
		int element_size;
	};

	static int type_num_components[] = { 1, 2, 3, 4, 4, 9, 16 };
	static int component_type_size[] = { 1, 1, 2, 2, 0, 4, 4 };

	// @todo the current approach is really over-complicated when outside of these edge cases
	glTFComponentLayout component_layout(glTFType type, glTFComponentType component_type)
	{
		int num_components = type_num_components[size_t(type)];
		int component_size = component_type_size[size_t(component_type) - 5120U];
		int element_size = num_components * component_size;

		glTFComponentLayout layout = { num_components, component_size, 0, 0, element_size };

		if(component_type == glTFComponentType::BYTE || component_type == glTFComponentType::UNSIGNED_BYTE)
		{
			if(type == glTFType::MAT2)
				layout = { num_components, component_size, 2, 2, 8 };
			if(type == glTFType::MAT3)
				layout = { num_components, component_size, 3, 1, 12 };
		}

		if(component_type == glTFComponentType::SHORT || component_type == glTFComponentType::UNSIGNED_SHORT)
		{
			if(type == glTFType::MAT3)
				layout = { num_components, component_size, 6, 4, 16 };
		}

		return layout;
	}

	int encode_accessor(glTF& gltf, int buffer_index, glTFAccessor& a, vector<double>& values, bool for_vertex)
	{
		glTFComponentLayout layout = component_layout(a.type, a.component_type);
		size_t stride = layout.element_size;
		if(for_vertex && stride % 4)
			stride += 4 - (stride % 4); // according to spec must be multiple of 4

		vector<uint8_t>& buffer = gltf.m_binary_buffers[buffer_index];

		glTFBufferView buffer_view;
		buffer_view.byte_stride = stride;
		buffer_view.byte_offset = buffer.size();
		buffer_view.byte_length = a.count * layout.element_size;

		buffer.resize(buffer.size() + buffer_view.byte_length);
		gltf.m_buffers[buffer_index].byte_length += buffer_view.byte_length;

		double* source = values.data();

		size_t offset = buffer_view.byte_offset;
		for(int i = 0; i < a.count; i++)
		{
			uint8_t* dest = &buffer[offset + i * stride];

			for(int j = 0; j < layout.num_components; j++)
			{
				if(layout.skip_every && j > 0 && (j % layout.skip_every) == 0)
					dest += layout.skip_bytes;

				double& d = *source++;

				switch(a.component_type) {
				case glTFComponentType::BYTE: {
					*(int8_t*)dest = a.normalized ? int8_t(d * 128.0) : int8_t(d);
				} break;
				case glTFComponentType::UNSIGNED_BYTE: {
					*(uint8_t*)dest = a.normalized ? uint8_t(d * 255.0) : uint8_t(d);
				} break;
				case glTFComponentType::SHORT: {
					*(int16_t*)dest = a.normalized ? int16_t(d * 32768.0) : int16_t(d);
				} break;
				case glTFComponentType::UNSIGNED_SHORT: {
					*(uint16_t*)dest = a.normalized ? uint16_t(d * 65535.0) : uint16_t(d);
				} break;
				case glTFComponentType::INT: {
					*(int*)dest = int(d);
				} break;
				case glTFComponentType::FLOAT: {
					*(float*)dest = float(d);
				} break;
				}

				dest += layout.component_size;
			}
		}

		gltf.m_buffer_views.push_back(buffer_view);
		a.buffer_view = int(gltf.m_buffer_views.size() - 1);
		a.byte_offset = 0;

		gltf.m_accessors.push_back(a);
		return int(gltf.m_accessors.size() - 1);
	}

	void decode_buffer_view(const glTF& gltf, const glTFAccessor& a, const glTFComponentLayout& layout, double* dest, bool for_vertex)
	{
		const glTFBufferView& buffer_view = gltf.m_buffer_views[a.buffer_view];

		size_t stride = buffer_view.byte_stride ? buffer_view.byte_stride : layout.element_size;
		if(for_vertex && stride % 4)
			stride += 4 - (stride % 4); // according to spec must be multiple of 4

		size_t offset = buffer_view.byte_offset + a.byte_offset;
		const vector<uint8_t>& buffer = gltf.m_binary_buffers[buffer_view.buffer];
		//const size_t size = buffer.size();

		for(int i = 0; i < a.count; i++)
		{
			const uint8_t* src = &buffer[offset + i * stride];

			for(int j = 0; j < layout.num_components; j++)
			{
				if(layout.skip_every && j > 0 && (j % layout.skip_every) == 0)
					src += layout.skip_bytes;

				double d = 0;

				switch(a.component_type) {
				case glTFComponentType::BYTE: {
					int8_t b = int8_t(*src);
					d = a.normalized ? (double(b) / 128.0) : double(b);
				} break;
				case glTFComponentType::UNSIGNED_BYTE: {
					uint8_t b = *src;
					d = a.normalized ? (double(b) / 255.0) : double(b);
				} break;
				case glTFComponentType::SHORT: {
					int16_t s = *(int16_t*)src;
					d = a.normalized ? (double(s) / 32768.0) : double(s);
				} break;
				case glTFComponentType::UNSIGNED_SHORT: {
					uint16_t s = *(uint16_t*)src;
					d = a.normalized ? (double(s) / 65535.0) : double(s);
				} break;
				case glTFComponentType::INT: {
					d = *(int*)src;
				} break;
				case glTFComponentType::FLOAT: {
					d = *(float*)src;
				} break;
				}

				*dest++ = d;
				src += layout.component_size;
			}
		}
	}
	
	vector<double> decode_accessor(const glTF& gltf, size_t accessor, bool for_vertex)
	{
		const glTFAccessor& a = gltf.m_accessors[accessor];

		glTFComponentLayout layout = component_layout(a.type, a.component_type);

		vector<double> dest_buffer;
		dest_buffer.resize(layout.num_components * a.count);

		if(a.buffer_view == -1)
			return dest_buffer;

		decode_buffer_view(gltf, a, layout, dest_buffer.data(), for_vertex);

		if(a.sparse.count > 0)
		{
			vector<double> indices;
			indices.resize(a.sparse.count);
			int indices_component_size = component_type_size[size_t(a.sparse.indices.component_type) - 5120U];

			glTFAccessor indices_accessor = { a.sparse.indices.buffer_view, a.sparse.indices.byte_offset, a.sparse.indices.component_type, false, a.sparse.count, glTFType::SCALAR };
			glTFComponentLayout indices_layout = { 1, indices_component_size, 0, 0, indices_component_size };
			decode_buffer_view(gltf, indices_accessor, indices_layout, indices.data(), false);

			vector<double> data;
			data.resize(layout.num_components * a.sparse.count);
			glTFAccessor values_accessor = { a.sparse.values.buffer_view, a.sparse.values.byte_offset, a.component_type, a.normalized, a.sparse.count, a.type };
			decode_buffer_view(gltf, values_accessor, layout, data.data(), for_vertex);

			for(size_t i = 0; i < indices.size(); i++)
			{
				int write_offset = int(indices[i]) * layout.num_components;

				for(int j = 0; j < layout.num_components; j++)
					dest_buffer[write_offset + j] = data[i * layout.num_components + j];
			}
		}

		return dest_buffer;
	}

	void unpack_gltf(const string& path, const string& file, glTF& gltf)
	{
		Json data;

		//bool glb = ends_with(to_lower(path), ".glb");
		bool glb = file_exists(path + "/" + file + ".glb");
		if(glb)
		{
			vector<uint8_t> buffer;
			parse_glb(path + "/" + file + ".glb", data, buffer);
			gltf.m_binary_buffers.push_back(buffer);
		}
		else
		{
			parse_json_file(path + "/" + file + ".gltf", data);
		}

		Json asset = data["asset"];
		string version = asset["version"].string_value().c_str();

		static FromJson unpacker = gltf_unpacker();
		Var gltfvar = Ref(&gltf);
		unpack(unpacker, gltfvar, data);
	}

	void repack_gltf(glTF& gltf, const string& path, const string& file, const glTFRepack& repack)
	{
		gltf.m_buffers.clear();
		gltf.m_buffer_views.clear();
		gltf.m_accessors.clear();
		gltf.m_binary_buffers.clear();

		glTFBuffer buffer;
		buffer.name = file;
		buffer.uri = file + ".repack.bin";
		buffer.byte_length = 0;

		gltf.m_binary_buffers.emplace_back();
		gltf.m_buffers.push_back(buffer);

		size_t model_index = 0;
		for(glTFMesh& gltf_mesh : gltf.m_meshes)
		{
			string model_name = gltf_mesh.name == "" ? file + ":" + to_string(model_index++) : gltf_mesh.name;

			size_t mesh_index = 0;
			for(glTFPrimitive& primitive : gltf_mesh.primitives)
			{
				string name = model_name + ":" + to_string(mesh_index++);
				repack(gltf, name, primitive);
			}
		}

		write_binary_file(path + "/" + buffer.uri, gltf.m_binary_buffers[0]);

		ToJson packer = gltf_packer();
		pack_json_file(packer, Ref(&gltf), path + "/" + file + ".repack.gltf");
	}
}

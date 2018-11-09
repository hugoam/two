//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <iostream>
#include <fstream>
#endif

#ifdef MUD_MODULES
#include <cpp/stdguard.h>
#endif
#include <base64.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.gltf;
#else
#include <json11.hpp>
using json = json11::Json;

#include <type/DispatchDecl.h>
#include <infra/Vector.h>
#include <infra/File.h>
#include <infra/String.h>
#include <infra/StringConvert.h>
#include <pool/Pool.h>
#include <srlz/Serial.h>
#include <refl/System.h>
#include <refl/Class.h>
#include <refl/Convert.h>
#include <math/VecJson.h>
#include <math/Interp.h>
#include <math/Stream.h>
#include <geom/Mesh.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Prefab.h>
#include <gfx/Material.h>
#include <gfx/Skeleton.h>
#include <gfx/Animation.h>
#include <gfx/Texture.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-gltf/Types.h>
#include <gfx-gltf/ImporterGltf.h>
#endif

#define KUPOMAN_EXPORTER 1

namespace mud
{
	inline void from_json(const json& j, PrimitiveType& mat)
	{
		mat = static_cast<PrimitiveType>(j.int_value());
	}
}

namespace mud
{
	float* value_ptr(Colour& colour) { return &colour.m_r; }
	const float* value_ptr(const Colour& colour) { return &colour.m_r; }
}

namespace mud
{
	FromJson gltf_unpacker()
	{
		FromJson unpacker;
		dispatch_branch<mat4>(unpacker, [&](mat4& result, Ref&, const json& json) { from_json(json, result); });
		dispatch_branch<quat>(unpacker, [&](quat& result, Ref&, const json& json) { from_json(json, result); });
		return unpacker;
	}

	ToJson gltf_packer()
	{
		ToJson packer;
		dispatch_branch<glTFType>         (packer, [](glTFType&          value, json& json_value) { json_value = to_string(Ref(&value)); });
		dispatch_branch<glTFInterpolation>(packer, [](glTFInterpolation& value, json& json_value) { json_value = to_string(Ref(&value)); });
		dispatch_branch<glTFAlphaMode>    (packer, [](glTFAlphaMode&     value, json& json_value) { json_value = to_string(Ref(&value)); });
		return packer;
	}

	string extensions[] = { "gltf", "glb" };

	ImporterGltf::ImporterGltf(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
	{
		static std::vector<string> fixed_members(256);

		size_t index = 0;
		for(Type* type : system().m_types)
			if(string(type->m_name).find("glTF") == 0 && g_class[type->m_id] && !type->is<glTFAttributes>())
			{
				for(Member& member : cls(*type).m_members)
				{
					fixed_members[index] = to_camelcase(string(member.m_name));
					member.m_name = fixed_members[index].c_str();
					index++;
					assert(index < fixed_members.size());
				}
			}

		static auto load_gltf_model = [&](GfxSystem& gfx_system, Model& model, cstring path)
		{
			UNUSED(gfx_system);
			ImportConfig config = load_model_config(path, model.m_name.c_str());
			this->import_model(model, path, config);
		};

		static auto load_gltf_prefab = [&](GfxSystem& gfx_system, Prefab& prefab, cstring path)
		{
			UNUSED(gfx_system);
			ImportConfig config = load_model_config(path, prefab.m_name.c_str());
			this->import_prefab(prefab, path, config);
		};

		gfx_system.add_importer(ModelFormat::gltf, *this);
		gfx_system.models().add_format(".gltf", load_gltf_model);
		gfx_system.prefabs().add_format(".gltf", load_gltf_prefab);
	}

	void parse_glb(const string& path, json& json, std::vector<uint8_t>& buffer)
	{
		std::ifstream file = std::ifstream(path, std::ios::binary);

		uint32_t magic = read<uint32_t>(file);
		uint32_t version = read<uint32_t>(file);
		read<uint32_t>(file); // uint32_t length

		if(magic != 0x46546C67 || version != 2)
		{
			printf("ERROR: .glb contents invalid\n");
			return;
		}

		while(!file.eof())
		{
			uint32_t chunk_length = read<uint32_t>(file);
			uint32_t chunk_type = read<uint32_t>(file);

			if(chunk_type == 0x4E4F534A)
			{
				string errors;
				string json_string = read(file, chunk_length);
				json = json::parse(json_string, errors);
			}
			else if(chunk_type == 0x004E4942)
			{
				buffer.reserve(chunk_length);
				buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
			}
		}
	}

	static std::vector<uint8_t> read_base64_uri(const string& uri)
	{
		string decoded = decode_base64(uri.substr(uri.find(",") + 1));
		return std::vector<uint8_t>(decoded.begin(), decoded.end());
	}

	std::vector<uint8_t> read_uri(const string& base_path, const string& uri)
	{
		if(uri.find("data:application/octet-stream;base64") == 0)
			return read_base64_uri(uri);
		else
			return read_binary_file(base_path + replace_all(uri, "\\", "/"));
	}

	void import_buffers(glTF& gltf, Import& state)
	{
		for(const glTFBuffer& buffer : gltf.m_buffers)
			if(buffer.uri != "")
			{
				gltf.m_binary_buffers.push_back(read_uri(state.m_path, buffer.uri));
			}
	}

	void import_images(glTF& gltf, Import& state)
	{
		auto import_image_mem = [&](array<uint8_t> data)
		{
			string name = state.m_file + to_string(state.m_images.size());
			Texture& texture = state.m_gfx_system.textures().create(name.c_str());
			load_texture_mem(state.m_gfx_system, texture, data);
			state.m_images.push_back(&texture);
		};

		for(const glTFImage& image : gltf.m_images)
		{
			if(image.uri != "")
			{
				if(image.uri.find("data:application/octet-stream;base64") == 0)
				{
					std::vector<uint8_t> data = read_base64_uri(image.uri);
					import_image_mem(data);
				}
				else
				{
					string path = string(state.m_path) + state.m_file + "/";
					Texture& texture = state.m_gfx_system.textures().file_at(path.c_str(), image.uri.c_str());
					//Texture& texture = state.m_gfx_system.textures().file(image.uri.c_str());
					state.m_images.push_back(&texture);
				}
			}
			else if(image.buffer_view != -1)
			{
				const glTFBufferView& buffer_view = gltf.m_buffer_views[image.buffer_view];
				array<uint8_t> data = { gltf.m_binary_buffers[buffer_view.buffer].data() + buffer_view.byte_offset, buffer_view.byte_length };
				import_image_mem(data);
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

	int encode_accessor(glTF& gltf, int buffer_index, glTFAccessor& a, std::vector<double>& values, bool for_vertex)
	{
		glTFComponentLayout layout = component_layout(a.type, a.component_type);
		size_t stride = layout.element_size;
		if(for_vertex && stride % 4)
			stride += 4 - (stride % 4); // according to spec must be multiple of 4

		std::vector<uint8_t>& buffer = gltf.m_binary_buffers[buffer_index];

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
		const std::vector<uint8_t>& buffer = gltf.m_binary_buffers[buffer_view.buffer];

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
	
	std::vector<double> decode_accessor(const glTF& gltf, size_t accessor, bool for_vertex)
	{
		const glTFAccessor& a = gltf.m_accessors[accessor];

		glTFComponentLayout layout = component_layout(a.type, a.component_type);

		std::vector<double> dest_buffer;
		dest_buffer.resize(layout.num_components * a.count);

		if(a.buffer_view == -1)
			return dest_buffer;

		decode_buffer_view(gltf, a, layout, dest_buffer.data(), for_vertex);

		if(a.sparse.count > 0)
		{
			std::vector<double> indices;
			indices.resize(a.sparse.count);
			int indices_component_size = component_type_size[size_t(a.sparse.indices.component_type) - 5120U];

			glTFAccessor indices_accessor = { a.sparse.indices.buffer_view, a.sparse.indices.byte_offset, a.sparse.indices.component_type, false, a.sparse.count, glTFType::SCALAR };
			glTFComponentLayout indices_layout = { 1, indices_component_size, 0, 0, indices_component_size };
			decode_buffer_view(gltf, indices_accessor, indices_layout, indices.data(), false);

			std::vector<double> data;
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

	template <class T>
	std::vector<T> unpack_accessor(const glTF& gltf, size_t accessor, bool for_vertex)
	{
		std::vector<double> attribs = decode_accessor(gltf, accessor, for_vertex);
		std::vector<T> ret;
		vector_cast(attribs, ret);
		return ret;
	}

	template <class T, size_t size>
	std::vector<T> unpack_accessor(const glTF& gltf, size_t accessor, bool for_vertex)
	{
		std::vector<double> attribs = decode_accessor(gltf, accessor, for_vertex);
		std::vector<T> ret(attribs.size() / size);
		using U = std::remove_pointer_t<decltype(value_ptr(ret.front()))>;
		std::transform(attribs.begin(), attribs.end(), value_ptr(ret.front()), [](double v) { return static_cast<U>(v); });
		return ret;
	}

	template <class T>
	int pack_accessor(glTF& gltf, int buffer_index, glTFAccessor& accessor, const std::vector<T>& values, bool for_vertex)
	{
		std::vector<double> attribs(values.size());
		std::transform(values.begin(), values.end(), attribs.begin(), [](int v) { return static_cast<double>(v); });
		return encode_accessor(gltf, buffer_index, accessor, attribs, for_vertex);
	}

	template <class T, size_t size>
	int pack_accessor(glTF& gltf, int buffer_index, glTFAccessor& accessor, const std::vector<T>& values, bool for_vertex)
	{
		std::vector<double> attribs(values.size() * size);
		using U = std::remove_pointer_t<decltype(value_ptr(values.front()))>;
		std::transform(value_ptr(values.front()), value_ptr(values.back()) + size, attribs.begin(), [](U v) { return static_cast<double>(v); });
		return encode_accessor(gltf, buffer_index, accessor, attribs, for_vertex);
	}

	template <class T, size_t size>
	int pack_accessor_float(glTF& gltf, int buffer_index, const std::vector<T>& values, bool for_vertex)
	{
		static_assert(size > 0 && size <= 4, "incorrect size");
		glTFAccessor accessor = { 0, 0, glTFComponentType::FLOAT, false, int(values.size()), glTFType(size - 1) };
		int result = pack_accessor<T, size>(gltf, buffer_index, accessor, values, for_vertex);
		std::vector<T> debug = unpack_accessor<T, size>(gltf, result, for_vertex);
		return result;
	}

	void export_attributes(glTF& gltf, int buffer_index, const MeshPacker& mesh, glTFAttributes& attributes)
	{
		if(mesh.m_positions.size() > 0)
			attributes.POSITION = pack_accessor_float<vec3, 3>(gltf, buffer_index, mesh.m_positions, true);
		if(mesh.m_normals.size() > 0)
			attributes.NORMAL = pack_accessor_float<vec3, 3>(gltf, buffer_index, mesh.m_normals, true);
		if(mesh.m_tangents.size() > 0)
			attributes.TANGENT = pack_accessor_float<vec4, 4>(gltf, buffer_index, mesh.m_tangents, true);
		if(mesh.m_uv0s.size() > 0)
			attributes.TEXCOORD_0 = pack_accessor_float<vec2, 2>(gltf, buffer_index, mesh.m_uv0s, true);
		if(mesh.m_uv1s.size() > 0)
			attributes.TEXCOORD_1 = pack_accessor_float<vec2, 2>(gltf, buffer_index, mesh.m_uv1s, true);
		if(mesh.m_colours.size() > 0)
			attributes.COLOR_0 = pack_accessor_float<Colour, 4>(gltf, buffer_index, mesh.m_colours, true);
		//if(mesh.m_bones.size() > 0)
		//	attributes.JOINTS_0 = pack_accessor<ivec4, 4>(gltf, buffer_index, mesh.m_bones, true);
		//if(mesh.m_weights.size() > 0)
		//	attributes.WEIGHTS_0 = pack_accessor<vec4, 4>(gltf, buffer_index, mesh.m_weights, true);
	}

	int export_indices(glTF& gltf, int buffer_index, const MeshPacker& mesh)
	{
		glTFAccessor accessor = { 0, 0, glTFComponentType::INT, false, int(mesh.m_indices.size()), glTFType::SCALAR };
		return pack_accessor<uint32_t>(gltf, buffer_index, accessor, mesh.m_indices, false);
	}

	void import_attributes(const glTF& gltf, MeshPacker& mesh, const glTFAttributes& attributes)
	{
		if(attributes.POSITION != -1)
			mesh.m_positions = unpack_accessor<vec3, 3>(gltf, attributes.POSITION, true);
		if(attributes.NORMAL != -1)
			mesh.m_normals = unpack_accessor<vec3, 3>(gltf, attributes.NORMAL, true);
		if(attributes.TANGENT != -1)
			mesh.m_tangents = unpack_accessor<vec4, 4>(gltf, attributes.TANGENT, true);
		if(attributes.TEXCOORD_0 != -1)
			mesh.m_uv0s = unpack_accessor<vec2, 2>(gltf, attributes.TEXCOORD_0, true);
		if(attributes.TEXCOORD_1 != -1)
		{
			std::vector<vec2> uv1s = unpack_accessor<vec2, 2>(gltf, attributes.TEXCOORD_1, true);
			if(!std::equal(uv1s.begin() + 1, uv1s.end(), uv1s.begin())) // probably full of zeroes, skip it
				mesh.m_uv1s = uv1s;
		}
		if(attributes.COLOR_0 != -1)
		{
			if(gltf.m_accessors[attributes.COLOR_0].type == glTFType::VEC4)
				mesh.m_colours = unpack_accessor<Colour, 4>(gltf, attributes.COLOR_0, true);
			//else if(gltf.accessors[attributes.COLOR_0].type == glTFType::VEC3)
			//	mesh.m_colours = unpack_accessor<Colour, 4>(gltf, attributes.COLOR_0, true);
		}
		if(attributes.JOINTS_0 != -1)
			mesh.m_bones = unpack_accessor<ivec4, 4>(gltf, attributes.JOINTS_0, true);
		if(attributes.WEIGHTS_0 != -1)
			mesh.m_weights = unpack_accessor<vec4, 4>(gltf, attributes.WEIGHTS_0, true);
	}

	void import_meshes(const glTF& gltf, Import& state, const ImportConfig& config)
	{
		size_t index = 0;
		for(const glTFMesh& gltf_mesh : gltf.m_meshes)
		{
			string model_name = gltf_mesh.name == "" ? state.m_file + ":" + to_string(index++) : gltf_mesh.name;
			if(config.m_suffix != "")
				model_name += ":" + config.m_suffix;

			if(state.m_gfx_system.models().get(model_name.c_str()) && !config.m_force_reimport)
				continue;
			Model& model = state.m_gfx_system.models().create(model_name.c_str());

			size_t primindex = 0;
			for(const glTFPrimitive& primitive : gltf_mesh.primitives)
			{
				string name = model_name + ":" + to_string(primindex++);
				bool occluder = false;

				//printf("DEBUG: importing mesh %s\n", name.c_str());

				if(primitive.material != -1)
				{
					occluder |= state.m_materials[primitive.material]->m_name == "occluder";

					if(config.filter_material(state.m_materials[primitive.material]->m_name))
					{
						state.m_meshes.push_back(nullptr);
						continue;
					}
				}

				Mesh& mesh = state.m_gfx_system.meshes().construct(name.c_str(), config.m_cache_geometry || occluder);
				state.m_meshes.push_back(&mesh);
				model.add_item(mesh, bxidentity());

				MeshPacker packer;
				//packer.m_quantize = true;

				packer.m_primitive = PrimitiveType::Triangles;//static_cast<PrimitiveType>(primitive.mode);
				import_attributes(gltf, packer, primitive.attributes);

				if(primitive.indices != -1)
				{
					std::vector<int> indices = unpack_accessor<int>(gltf, primitive.indices, false);
					packer.m_indices = std::vector<uint32_t>(indices.begin(), indices.end());
				}

				std::vector<MeshPacker> morphs;

				for(const glTFMorphTarget& morph_target : primitive.targets)
				{
					morphs.emplace_back(packer);

					MeshPacker& morph_shape = morphs.back();
					morph_shape.m_indices = {};

					if(morph_target.POSITION != -1)
						morph_shape.m_positions = unpack_accessor<vec3, 3>(gltf, morph_target.POSITION, true);
					if(morph_target.NORMAL != -1)
						morph_shape.m_normals = unpack_accessor<vec3, 3>(gltf, morph_target.NORMAL, true);
					if(morph_target.TANGENT != -1)
					{
						std::vector<vec3> tangents = unpack_accessor<vec3, 3>(gltf, morph_target.TANGENT, true);
						morph_shape.m_tangents.resize(tangents.size());

						for(size_t i = 0; i < packer.m_tangents.size(); ++i)
							morph_shape.m_tangents[i] = vec4{ tangents[i], packer.m_tangents[i].w };
					}

					morphs.push_back(morph_shape);
				}

				if(primitive.material != -1)
					mesh.m_material = state.m_materials[primitive.material];

				if(packer.m_tangents.empty() && !packer.m_uv0s.empty())
					packer.generate_tangents();
				if(packer.m_tangents.empty() && packer.m_uv0s.empty())
					printf("WARNING: mesh %s imported without tangents (no uvs)\n", name.c_str());

				mesh.write(PLAIN, packer, config.m_optimize_geometry);
				//mesh.write(PLAIN, packer);
			}

			if(model.m_items.size() == 0)
			{
				state.m_gfx_system.models().destroy(model_name.c_str());
				state.m_models.push_back(nullptr);
				continue;
			}

			model.prepare();
			state.m_models.push_back(&model);
		}
	}

	Texture* get_texture(const glTF& gltf, const Import& state, int texture)
	{
		int image = gltf.m_textures[texture].source;
		return state.m_images[image];
	}

	void import_material(const glTF& gltf, const Import& state, const glTFMaterial& gltf_material, Material& material)
	{
		//if(gltf_material.pbr_metallic_roughness)
		{
			glTFMaterialPBR pbr_material = gltf_material.pbr_metallic_roughness;

			material.m_pbr_block.m_enabled = true;
			material.m_pbr_block.m_albedo.m_value = to_colour(pbr_material.base_color_factor);

			if(pbr_material.base_color_texture.index != -1)
			{
				material.m_pbr_block.m_albedo.m_value = Colour::White;
				material.m_pbr_block.m_albedo.m_texture = get_texture(gltf, state, pbr_material.base_color_texture.index);
			}

			material.m_pbr_block.m_metallic.m_value = pbr_material.metallic_factor;
			material.m_pbr_block.m_roughness.m_value = pbr_material.roughness_factor;

			if(pbr_material.metallic_roughness_texture.index != -1)
			{
				Texture* texture = get_texture(gltf, state, pbr_material.metallic_roughness_texture.index);
				material.m_pbr_block.m_metallic.m_texture = texture;
				material.m_pbr_block.m_metallic.m_channel = TextureChannel::Blue;
				material.m_pbr_block.m_roughness.m_texture = texture;
				material.m_pbr_block.m_roughness.m_channel = TextureChannel::Green;
			}
		}

		if(gltf_material.normal_texture.index != -1)
		{
			material.m_pbr_block.m_normal.m_texture = get_texture(gltf, state, gltf_material.normal_texture.index);
			material.m_pbr_block.m_normal.m_value = gltf_material.normal_texture.scale;
		}

		if(gltf_material.occlusion_texture.index != -1)
		{
			material.m_pbr_block.m_ambient_occlusion.m_texture = get_texture(gltf, state, gltf_material.occlusion_texture.index);
			material.m_pbr_block.m_ambient_occlusion.m_channel = TextureChannel::Red;
		}

		vec3 emissive = gltf_material.emissive_factor;
#if KUPOMAN_EXPORTER
		emissive *= vec3(gltf_material.pbr_metallic_roughness.base_color_factor);
#endif
		float emissive_factor = (emissive.r + emissive.g + emissive.b) / 3.f;
		material.m_pbr_block.m_emissive.m_value = to_colour(vec4(emissive / emissive_factor, emissive_factor));

		if(gltf_material.emissive_texture.index != -1)
		{
			material.m_pbr_block.m_emissive.m_texture = get_texture(gltf, state, gltf_material.emissive_texture.index);
			material.m_pbr_block.m_emissive.m_value = Colour::Black;
			material.m_pbr_block.m_emissive.m_value.m_a = emissive_factor;
		}

		if(gltf_material.double_sided)
			material.m_base_block.m_cull_mode = CullMode::None;

		if(gltf_material.alpha_mode != glTFAlphaMode::OPAQUE)
			material.m_base_block.m_is_alpha = true;
	}

	void import_materials(const glTF& gltf, Import& state)
	{
		size_t index = 0;
		for(const glTFMaterial& gltf_material : gltf.m_materials)
		{
			string name = gltf_material.name == "" ? state.m_file + ":" + to_string(index++) : gltf_material.name;
			Material& material = state.m_gfx_system.fetch_material(name.c_str(), "pbr/pbr", false);
			import_material(gltf, state, gltf_material, material);
			state.m_materials.push_back(&material);
		}
	}

	void setup_nodes(glTF& gltf)
	{
		for(glTFNode& node : gltf.m_nodes)
			if(node.matrix == mat4())
			{
				node.matrix = bxTRS(node.scale, node.rotation, node.translation);
			}

		for(size_t i = 0; i < gltf.m_nodes.size(); i++)
			for(size_t j = 0; j < gltf.m_nodes[i].children.size(); j++)
			{
				int child = gltf.m_nodes[i].children[j];
				gltf.m_nodes[child].parent = int(i);
			}
	}

	void create_bone(const glTF& gltf, const glTFNode& node, Skeleton& skeleton, int parent)
	{
		//printf("INFO:      - adding bone %s\n", node.name.c_str());
		Bone& bone = skeleton.add_bone(node.name.c_str(), parent);

		for(int child : node.children)
			if(gltf.m_nodes[child].is_joint)
				create_bone(gltf, gltf.m_nodes[child], skeleton, bone.m_index);
	}

	void create_skeleton(const glTF& gltf, Import& state, Model& model, int node, int num_bones)
	{
		const glTFNode& skeleton_node = gltf.m_nodes[node];

		printf("INFO: Gltf - adding skeleton %s\n", skeleton_node.name.c_str());
		model.m_rig->m_skeleton = { skeleton_node.name.c_str(), num_bones };
		state.m_skeletons[node] = &model.m_rig->m_skeleton;

		create_bone(gltf, skeleton_node, model.m_rig->m_skeleton, -1);
	}

	void import_skeletons(glTF& gltf, Import& state, Model& model)
	{
		std::map<int, int> skeleton_sizes;

		for(const glTFSkin& skin : gltf.m_skins)
			skeleton_sizes[skin.skeleton] = max(int(skin.joints.size()), skeleton_sizes[skin.skeleton]);

		for(const glTFSkin& skin : gltf.m_skins)
			for(int joint : skin.joints)
				gltf.m_nodes[joint].is_joint = true;

		for(auto& skeleton_num_bones : skeleton_sizes)
			create_skeleton(gltf, state, model, skeleton_num_bones.first, skeleton_num_bones.second);

		for(glTFSkin& gltf_skin : gltf.m_skins)
		{
			printf("INFO: Gltf - adding skin %s\n", gltf_skin.name.c_str());
			model.m_rig->m_skins.emplace_back(*state.m_skeletons[gltf_skin.skeleton], int(gltf_skin.joints.size())); // gltf_skin.name
			Skin& skin = model.m_rig->m_skins.back();

			std::vector<mat4> bind_matrices;

			if(gltf_skin.inverse_bind_matrices != -1)
				bind_matrices = unpack_accessor<mat4, 16>(gltf, gltf_skin.inverse_bind_matrices, false);

			size_t index = 0;
			for(int joint : gltf_skin.joints)
				skin.add_joint(gltf.m_nodes[joint].name.c_str(), bind_matrices[index++]);
		}
	}

	template <class T>
	void import_track(const glTFNode& node, glTFInterpolation interpolation, const std::vector<float>& times, const std::vector<T>& values, Animation& animation, size_t bone, AnimationTarget target)
	{
		AnimationTrack track = { animation, bone, node.name.c_str(), target };

		track.m_interpolation = interpolation == glTFInterpolation::STEP ? Interpolation::Nearest
																		 : Interpolation::Linear;
		for(size_t i = 0; i < times.size(); i++)
			track.m_keys.push_back({ times[i], values[i] });

		animation.tracks.push_back(track);
	}

	void import_animation(const glTF& gltf, Import& state, size_t index, Skeleton& skeleton)
	{
		const glTFAnimation& gltf_anim = gltf.m_animations[index];

		Animation& animation = state.m_gfx_system.animations().construct(gltf_anim.name.c_str());
		skeleton.m_animations.push_back(&animation);

		animation.m_length = 0.f;

		printf("INFO: Gltf - importing animation %s\n", animation.m_name.c_str());

		for(const glTFAnimationChannel& channel : gltf_anim.channels)
		{
			const glTFAnimationSampler& sampler = gltf_anim.samplers[channel.sampler];
			const glTFNode& node = gltf.m_nodes[channel.target.node];

			Bone* bone = skeleton.find_bone(node.name.c_str());
			size_t bone_index = bone ? bone->m_index : SIZE_MAX;

			std::vector<float> times = unpack_accessor<float>(gltf, sampler.input, false);

			float length = 0.f;

			for(float time : times)
				length = max(length, time);

			animation.m_length = max(animation.m_length, length);

			if(channel.target.path == "translation")
			{
				std::vector<vec3> translations = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, translations, animation, bone_index, AnimationTarget::Position); // member(&Bone::m_position)
			}
			else if(channel.target.path == "rotation")
			{
				std::vector<quat> rotations = unpack_accessor<quat, 4>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, rotations, animation, bone_index, AnimationTarget::Rotation); // member(&Bone::m_rotation)
			}
			else if(channel.target.path == "scale")
			{
				std::vector<vec3> scales = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, scales, animation, bone_index, AnimationTarget::Scale); // member(&Bone::m_scale)
			}
			else if(channel.target.path == "weights")
			{
				std::vector<float> weights = unpack_accessor<float>(gltf, sampler.output, false);
				size_t track_key_size = gltf.m_meshes[node.mesh].weights.size();
				// mud doesn't implement morph targets so far :/ this 
				UNUSED(weights); UNUSED(track_key_size);
			}
		}
	}

	void import_rig(glTF& gltf, Import& state, Model& model)
	{
		Rig& rig = model.add_rig(model.m_name.c_str());
		rig.m_skins.reserve(gltf.m_skins.size());

		import_skeletons(gltf, state, model);

		for(size_t i = 0; i < gltf.m_animations.size(); i++)
			import_animation(gltf, state, int(i), rig.m_skeleton);
	}

	mat4 derive_transform(const glTF& gltf, const glTFNode& node)
	{
		// not handling the matrix case here : waiting for c++17 optionals since matrix is almost never used
		if(node.parent > -1)
			return derive_transform(gltf, gltf.m_nodes[node.parent]) * node.matrix;
		else
			return node.matrix;
	}

	void import_items(const glTF& gltf, Import& state, const ImportConfig& config)
	{
		for(const glTFNode& node : gltf.m_nodes)
		{
			if(config.filter_element(node.name))
				continue;

			if(node.mesh > -1)
			{
				Model* model = state.m_models[node.mesh];
				if(!model) continue;
				mat4 node_transform = config.m_transform * derive_transform(gltf, node);
				state.m_items.push_back({ node_transform, model, node.skin });
			}

			//if(node.camera)
			//	;
		}
	}

	void unpack_gltf(const string& path, const string& file, glTF& gltf)
	{
		json data;

		bool glb = false; // to_lower(path).ends_with("glb")
		if(glb)
		{
			std::vector<uint8_t> buffer;
			parse_glb(path + file + ".glb", data, buffer);
			gltf.m_binary_buffers.push_back(buffer);
		}
		else
		{
			parse_json_file(path + file + ".gltf", data);
		}

		json asset = data["asset"];
		string version = asset["version"].string_value();

		static FromJson unpacker = gltf_unpacker();
		Var gltfvar = Ref(&gltf);
		unpack(unpacker, gltfvar, data);
	}

	void import_gltf(glTF& gltf, Import& state, const ImportConfig& config)
	{
		setup_nodes(gltf);

		import_buffers(gltf, state);
		import_images(gltf, state);
		import_materials(gltf, state);
		import_meshes(gltf, state, config);
		import_items(gltf, state, config);
	}

	void export_repack(GfxSystem& gfx_system, glTF& gltf, const string& path, const string& file)
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
				Mesh* mesh = gfx_system.meshes().find([&](Mesh& mesh) { return mesh.m_name == name; });
				if(!mesh) continue;
				MeshPacker packer;
				mesh->read(packer, bxidentity());
				primitive.attributes = {};
				export_attributes(gltf, 0, packer, primitive.attributes);
				primitive.indices = export_indices(gltf, 0, packer);
			}
		}

		write_binary_file(path + buffer.uri, gltf.m_binary_buffers[0]);

		ToJson packer = gltf_packer();
		pack_json_file(packer, Ref(&gltf), path + file + ".repack.gltf");
	}

	void ImporterGltf::import(Import& state, const string& filepath, const ImportConfig& config)
	{
		printf("INFO: gltf - loading scene %s\n", filepath.c_str());

		glTF gltf;
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
	}

	void ImporterGltf::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		printf("INFO: gltf - loading model %s\n", filepath.c_str());

		Import state = { m_gfx_system, filepath, config };

		glTF gltf;
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
		import_rig(gltf, state, model);

		for(const Import::Item& item : state.m_items)
		{
			for(const ModelItem& model_item : item.model->m_items)
				model.add_item(*model_item.m_mesh, item.transform, item.skin);
		}

		model.prepare();
	}

	void ImporterGltf::import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config)
	{
		printf("INFO: gltf - loading prefab %s\n", filepath.c_str());

		Import state = { m_gfx_system, filepath, config };

		glTF gltf;
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
		import_to_prefab(m_gfx_system, prefab, state, config.m_flags);
	}

	void ImporterGltf::repack(const string& filepath, const ImportConfig& config)
	{
		UNUSED(config);
		printf("INFO: gltf - repacking asset %s\n", filepath.c_str());

		string path = file_directory(filepath);
		string file = file_name(filepath);

		glTF gltf;
		unpack_gltf(path, file, gltf);
		//import_gltf(gltf, state, config);
		export_repack(m_gfx_system, gltf, path, file);
	}
}

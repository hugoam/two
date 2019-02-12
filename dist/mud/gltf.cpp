#include <mud/pool.h>
#include <mud/geom.h>
#include <mud/srlz.h>
#include <mud/gltf.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifndef MUD_CPP_20
#include <cassert>
#include <iostream>
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.gltf;
#else
#include <json11.hpp>
using json = json11::Json;

#include <stl/algorithm.h>
#endif

namespace mud
{
	inline void from_json(const json& j, PrimitiveType& mat)
	{
		mat = static_cast<PrimitiveType>(j.int_value());
	}
}

namespace mud
{
	FromJson gltf_unpacker()
	{
		FromJson unpacker;
		dispatch_branch<mat4>(unpacker, +[](mat4& result, const json& json) { from_json(json, result); });
		dispatch_branch<quat>(unpacker, +[](quat& result, const json& json) { from_json(json, result); });
		return unpacker;
	}

	ToJson gltf_packer()
	{
		ToJson packer;
		dispatch_branch<glTFType>         (packer, +[](glTFType&          value, json& json_value) { json_value = to_string(Ref(&value)); });
		dispatch_branch<glTFInterpolation>(packer, +[](glTFInterpolation& value, json& json_value) { json_value = to_string(Ref(&value)); });
		dispatch_branch<glTFAlphaMode>    (packer, +[](glTFAlphaMode&     value, json& json_value) { json_value = to_string(Ref(&value)); });
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

	void parse_glb(const string& path, json& json, vector<uint8_t>& buffer)
	{
		std::ifstream file = std::ifstream(path.c_str(), std::ios::binary);

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
				std::string errors;
				string json_string = read(file, chunk_length);
				json = json::parse(json_string.c_str(), errors);
			}
			else if(chunk_type == 0x004E4942)
			{
				buffer.reserve(chunk_length);
#ifndef USE_STL
#else
				buffer.insert(buffer.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
#endif
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
		json data;

		bool glb = ends_with(to_lower(path), ".glb");
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

		json asset = data["asset"];
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
#ifndef USE_STL
#ifdef MUD_MODULES
module mud.gltf;
#else
#include <stl/vector.hpp>
#include <stl/unordered_map.hpp>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_GLTF_EXPORT vector<int>;
	template class MUD_GLTF_EXPORT vector<double>;
	template class MUD_GLTF_EXPORT vector<uchar>;
	template class MUD_GLTF_EXPORT vector<vector<uchar>>;
	template class MUD_GLTF_EXPORT vector<glTFAnimationSampler>;
	template class MUD_GLTF_EXPORT vector<glTFAnimationChannel>;
	template class MUD_GLTF_EXPORT vector<glTFMorphTarget>;
	template class MUD_GLTF_EXPORT vector<glTFPrimitive>;
	template class MUD_GLTF_EXPORT vector<glTFBuffer>;
	template class MUD_GLTF_EXPORT vector<glTFBufferView>;
	template class MUD_GLTF_EXPORT vector<glTFAccessor>;
	template class MUD_GLTF_EXPORT vector<glTFImage>;
	template class MUD_GLTF_EXPORT vector<glTFTexture>;
	template class MUD_GLTF_EXPORT vector<glTFMaterial>;
	template class MUD_GLTF_EXPORT vector<glTFMesh>;
	template class MUD_GLTF_EXPORT vector<glTFNode>;
	template class MUD_GLTF_EXPORT vector<glTFSkin>;
	template class MUD_GLTF_EXPORT vector<glTFAnimation>;
	template class MUD_GLTF_EXPORT vector<glTFCamera>;
	template class MUD_GLTF_EXPORT vector<glTFSampler>;
	template class MUD_GLTF_EXPORT vector<glTFScene>;
	template class MUD_GLTF_EXPORT unordered_map<string, int>;
	template class MUD_GLTF_EXPORT unordered_map<int, int>;
}
#endif

#ifdef MUD_MODULES
module mud.gltf;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_GLTF_EXPORT Type& type<glTFAlphaMode>() { static Type ty("glTFAlphaMode", sizeof(glTFAlphaMode)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFComponentType>() { static Type ty("glTFComponentType", sizeof(glTFComponentType)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFInterpolation>() { static Type ty("glTFInterpolation", sizeof(glTFInterpolation)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFPrimitiveType>() { static Type ty("glTFPrimitiveType", sizeof(glTFPrimitiveType)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFType>() { static Type ty("glTFType", sizeof(glTFType)); return ty; }
    
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAccessor>>() { static Type ty("vector<glTFAccessor>", sizeof(stl::vector<glTFAccessor>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAnimation>>() { static Type ty("vector<glTFAnimation>", sizeof(stl::vector<glTFAnimation>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAnimationChannel>>() { static Type ty("vector<glTFAnimationChannel>", sizeof(stl::vector<glTFAnimationChannel>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAnimationSampler>>() { static Type ty("vector<glTFAnimationSampler>", sizeof(stl::vector<glTFAnimationSampler>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFBuffer>>() { static Type ty("vector<glTFBuffer>", sizeof(stl::vector<glTFBuffer>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFBufferView>>() { static Type ty("vector<glTFBufferView>", sizeof(stl::vector<glTFBufferView>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFCamera>>() { static Type ty("vector<glTFCamera>", sizeof(stl::vector<glTFCamera>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFImage>>() { static Type ty("vector<glTFImage>", sizeof(stl::vector<glTFImage>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFMaterial>>() { static Type ty("vector<glTFMaterial>", sizeof(stl::vector<glTFMaterial>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFMesh>>() { static Type ty("vector<glTFMesh>", sizeof(stl::vector<glTFMesh>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFMorphTarget>>() { static Type ty("vector<glTFMorphTarget>", sizeof(stl::vector<glTFMorphTarget>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFNode>>() { static Type ty("vector<glTFNode>", sizeof(stl::vector<glTFNode>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFPrimitive>>() { static Type ty("vector<glTFPrimitive>", sizeof(stl::vector<glTFPrimitive>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFSampler>>() { static Type ty("vector<glTFSampler>", sizeof(stl::vector<glTFSampler>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFScene>>() { static Type ty("vector<glTFScene>", sizeof(stl::vector<glTFScene>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFSkin>>() { static Type ty("vector<glTFSkin>", sizeof(stl::vector<glTFSkin>)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFTexture>>() { static Type ty("vector<glTFTexture>", sizeof(stl::vector<glTFTexture>)); return ty; }
    
    template <> MUD_GLTF_EXPORT Type& type<glTF>() { static Type ty("glTF", sizeof(glTF)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFAccessor>() { static Type ty("glTFAccessor", sizeof(glTFAccessor)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFAnimation>() { static Type ty("glTFAnimation", sizeof(glTFAnimation)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFAnimationChannel>() { static Type ty("glTFAnimationChannel", sizeof(glTFAnimationChannel)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFAnimationSampler>() { static Type ty("glTFAnimationSampler", sizeof(glTFAnimationSampler)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFAnimationTarget>() { static Type ty("glTFAnimationTarget", sizeof(glTFAnimationTarget)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFAttributes>() { static Type ty("glTFAttributes", sizeof(glTFAttributes)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFBuffer>() { static Type ty("glTFBuffer", sizeof(glTFBuffer)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFBufferView>() { static Type ty("glTFBufferView", sizeof(glTFBufferView)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFCamera>() { static Type ty("glTFCamera", sizeof(glTFCamera)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFImage>() { static Type ty("glTFImage", sizeof(glTFImage)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFMaterial>() { static Type ty("glTFMaterial", sizeof(glTFMaterial)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFMaterialPBR>() { static Type ty("glTFMaterialPBR", sizeof(glTFMaterialPBR)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFMesh>() { static Type ty("glTFMesh", sizeof(glTFMesh)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFMorphTarget>() { static Type ty("glTFMorphTarget", sizeof(glTFMorphTarget)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFNode>() { static Type ty("glTFNode", sizeof(glTFNode)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFNodeExtras>() { static Type ty("glTFNodeExtras", sizeof(glTFNodeExtras)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFOrthographic>() { static Type ty("glTFOrthographic", sizeof(glTFOrthographic)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFPerspective>() { static Type ty("glTFPerspective", sizeof(glTFPerspective)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFPrimitive>() { static Type ty("glTFPrimitive", sizeof(glTFPrimitive)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFSampler>() { static Type ty("glTFSampler", sizeof(glTFSampler)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFScene>() { static Type ty("glTFScene", sizeof(glTFScene)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFSkin>() { static Type ty("glTFSkin", sizeof(glTFSkin)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFSparse>() { static Type ty("glTFSparse", sizeof(glTFSparse)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFSparseIndices>() { static Type ty("glTFSparseIndices", sizeof(glTFSparseIndices)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFSparseValues>() { static Type ty("glTFSparseValues", sizeof(glTFSparseValues)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFTexture>() { static Type ty("glTFTexture", sizeof(glTFTexture)); return ty; }
    template <> MUD_GLTF_EXPORT Type& type<glTFTextureInfo>() { static Type ty("glTFTextureInfo", sizeof(glTFTextureInfo)); return ty; }
}

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

#include <obj/DispatchDecl.h>
#include <infra/Vector.h>
#include <srlz/Serial.h>
#include <refl/System.h>
#include <infra/File.h>
#include <refl/Class.h>
#include <infra/String.h>
#include <math/VecJson.h>
#include <math/Interp.h>
#include <math/Stream.h>
#include <geom/Mesh.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
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
}

namespace mud
{
	class glTFImport
	{
	public:
		glTFImport(GfxSystem& gfx_system, Model& model, const ModelConfig& model_config)
			: m_gfx_system(gfx_system), m_model(model), m_model_config(model_config)
		{}

		GfxSystem& m_gfx_system;
		Model& m_model;
		const ModelConfig& m_model_config;

		json m_json;
		std::vector<uint8_t> m_glb;

		glTF m_gltf;

		std::vector<Texture*> m_imported_images;
		std::vector<Material*> m_imported_materials;

		std::map<int, Skeleton*> m_skeletons;
	};

	FromJson gltf_unpacker()
	{
		FromJson unpacker;
		dispatch_branch<mat4>(unpacker, [&](mat4& result, Ref&, const json& json) { from_json(json, result); });
		dispatch_branch<quat>(unpacker, [&](quat& result, Ref&, const json& json) { from_json(json, result); });
		return unpacker;
	}

	template <class T>
	T gltf_unpackt(const json& json_value)
	{
		static FromJson unpacker = gltf_unpacker();
		Var value = unpack(unpacker, type<T>(), json_value);
		return val<T>(value);
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

		static auto load_gltf = [&](GfxSystem& gfx_system, Model& model, cstring path)
		{
			ModelConfig config = load_model_config(path, model.m_name.c_str());
			this->import_model(model, path, config);
		};

		gfx_system.models().add_format(".gltf", load_gltf);
	}

	void parse_glb(const string& path, glTFImport& state)
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
				state.m_json = json::parse(json_string, errors);
			}
			else if(chunk_type == 0x004E4942)
			{
				state.m_glb.reserve(chunk_length);
				state.m_glb.insert(state.m_glb.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
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

	void import_buffers(glTF& gltf, glTFImport& state, const string& base_path)
	{
		if(!state.m_glb.empty())
			gltf.m_binary_buffers.push_back(state.m_glb);

		for(const glTFBuffer& buffer : gltf.m_buffers)
			if(buffer.uri != "")
			{
				gltf.m_binary_buffers.push_back(read_uri(base_path, buffer.uri));
			}
	}

	void import_images(glTF& gltf, glTFImport& state, const string& path, const string& file)
	{
		for(const glTFImage& image : gltf.m_images)
		{
			if(image.uri != "")
			{
				if(image.uri.find("data:application/octet-stream;base64") == 0)
				{
					std::vector<uint8_t> data = read_base64_uri(image.uri);
					auto load_image_mem = [](Texture&) {  }; // to_array(data)
					Texture& texture = state.m_gfx_system.textures().create("temp", load_image_mem);
					state.m_imported_images.push_back(&texture);
				}
				else
				{
					Texture& texture = state.m_gfx_system.textures().file((string(path) + file + "/").c_str(), image.uri.c_str());
					//Texture& texture = state.m_gfx_system.textures().file(image.uri.c_str());
					state.m_imported_images.push_back(&texture);
				}
			}
			else if(image.buffer_view != -1)
			{
				//const glTFBufferView& buffer_view = gltf.m_buffer_views[image.buffer_view];
				//array<uint8_t> data = { gltf.m_binary_buffers[buffer_view.buffer].data() + buffer_view.byte_offset, buffer_view.byte_length };
				auto load_image_mem = [](Texture&) {}; // to_array(data)
				Texture& texture = state.m_gfx_system.textures().create("temp", load_image_mem);
				state.m_imported_images.push_back(&texture);
			}
		}
	}

	struct glTFComponentLayout
	{
		int num_components;
		int component_size;
		int skip_every;
		int skip_bytes;
		int element_size;
	};

	void decode_buffer_view(const glTF& gltf, const glTFAccessor& a, const glTFComponentLayout& layout, double* dest, bool for_vertex)
	{
		const glTFBufferView& buffer_view = gltf.m_buffer_views[a.buffer_view];

		int stride = buffer_view.byte_stride ? buffer_view.byte_stride : layout.element_size;
		if(for_vertex && stride % 4)
			stride += 4 - (stride % 4); //according to spec must be multiple of 4

		uint32_t offset = buffer_view.byte_offset + a.byte_offset;
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
		// spec, for reference:
		// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#data-alignment

		const glTFAccessor& a = gltf.m_accessors[accessor];

		static int type_num_components[] = { 1, 2, 3, 4, 4, 9, 16 };
		static int component_type_size[] = { 1, 1, 2, 2, 0, 4, 4 };

		int num_components = type_num_components[size_t(a.type)];
		int component_size = component_type_size[size_t(a.component_type) - 5120U];
		int element_size = num_components * component_size;

		glTFComponentLayout layout = { num_components, component_size, 0, 0, element_size };

		if(a.component_type == glTFComponentType::BYTE || a.component_type == glTFComponentType::UNSIGNED_BYTE)
		{
			if(a.type == glTFType::MAT2)
				layout = { num_components, component_size, 2, 2, 8 };
			if(a.type == glTFType::MAT3)
				layout = { num_components, component_size, 3, 1, 12 };
		}

		if(a.component_type == glTFComponentType::SHORT || a.component_type == glTFComponentType::UNSIGNED_SHORT)
		{
			if(a.type == glTFType::MAT3)
				layout = { num_components, component_size, 6, 4, 16 };
		}

		std::vector<double> dest_buffer;
		dest_buffer.resize(num_components * a.count);

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
			data.resize(num_components * a.sparse.count);
			glTFAccessor values_accessor = { a.sparse.values.buffer_view, a.sparse.values.byte_offset, a.component_type, a.normalized, a.sparse.count, a.type };
			decode_buffer_view(gltf, values_accessor, layout, data.data(), for_vertex);

			for(size_t i = 0; i < indices.size(); i++)
			{
				int write_offset = int(indices[i]) * num_components;

				for(int j = 0; j < num_components; j++)
					dest_buffer[write_offset + j] = data[i * num_components + j];
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
		std::transform(attribs.begin(), attribs.end(), value_ptr(ret[0]), [](double v) { return static_cast<float>(v); });
		return ret;
	}

	void import_attributes(const glTF& gltf, MeshPacker& shape, const glTFAttributes& attributes)
	{
		if(attributes.POSITION != -1)
			shape.m_positions = unpack_accessor<vec3, 3>(gltf, attributes.POSITION, true);
		if(attributes.NORMAL != -1)
			shape.m_normals = unpack_accessor<vec3, 3>(gltf, attributes.NORMAL, true);
		if(attributes.TANGENT != -1)
			shape.m_tangents = unpack_accessor<vec4, 4>(gltf, attributes.TANGENT, true);
		if(attributes.TEXCOORD_0 != -1)
			shape.m_uv0s = unpack_accessor<vec2, 2>(gltf, attributes.TEXCOORD_0, true);
		if(attributes.TEXCOORD_1 != -1)
			shape.m_uv1s = unpack_accessor<vec2, 2>(gltf, attributes.TEXCOORD_1, true);
		if(attributes.COLOR_0 != -1)
		{
			if(gltf.m_accessors[attributes.COLOR_0].type == glTFType::VEC4)
				shape.m_colours = unpack_accessor<Colour, 4>(gltf, attributes.COLOR_0, true);
			//else if(gltf.accessors[attributes.COLOR_0].type == glTFType::VEC3)
			//	shape.m_colours = unpack_accessor<Colour, 4>(gltf, attributes.COLOR_0, true);
		}
		if(attributes.JOINTS_0 != -1)
			shape.m_bones = unpack_accessor<ivec4, 4>(gltf, attributes.JOINTS_0, true);
		if(attributes.WEIGHTS_0 != -1)
			shape.m_weights = unpack_accessor<vec4, 4>(gltf, attributes.WEIGHTS_0, true);

	}

	void import_meshes(const glTF& gltf, glTFImport& state)
	{
		size_t index = 0;

		for(const glTFMesh& gltf_mesh : gltf.m_meshes)
		{
			for(const glTFPrimitive& primitive : gltf_mesh.primitives)
			{
				Mesh& mesh = state.m_model.add_mesh((state.m_model.m_name + to_string(index++)).c_str(), true);
				
				MeshPacker shape;

				shape.m_primitive = PrimitiveType::Triangles;//static_cast<PrimitiveType>(primitive.mode);
				import_attributes(gltf, shape, primitive.attributes);

				if(primitive.indices != -1)
				{
					std::vector<int> indices = unpack_accessor<int>(gltf, primitive.indices, false);
					shape.m_indices = std::vector<ShapeIndex>(indices.begin(), indices.end());
				}

				std::vector<MeshPacker> morphs;

				for(const glTFMorphTarget& morph_target : primitive.targets)
				{
					morphs.emplace_back(shape);

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

						for(size_t i = 0; i < shape.m_tangents.size(); ++i)
							morph_shape.m_tangents[i] = vec4{ tangents[i], shape.m_tangents[i].w };
					}

					morphs.push_back(morph_shape);
				}

				if(primitive.material != -1)
					mesh.m_material = state.m_imported_materials[primitive.material];

				shape.pack_vertices(bxidentity()); //state.m_model_config.m_transform);

				if(shape.m_indices.empty())
					shape.generate_indices();

				mesh.write(PLAIN, to_array(shape.m_vertices), to_array(shape.m_indices));
			}
		}
	}

	Texture* get_texture(const glTFImport& state, int texture)
	{
		int image = state.m_gltf.m_textures[texture].source;
		return state.m_imported_images[image];
	}

	void import_material(const glTFImport& state, const glTFMaterial& gltf_material, Material& material)
	{
		//if(gltf_material.pbr_metallic_roughness)
		{
			glTFMaterialPBR pbr_material = gltf_material.pbr_metallic_roughness;

			material.m_pbr_block.m_enabled = true;
			material.m_pbr_block.m_albedo.m_value = to_colour(pbr_material.base_color_factor); //.toSRGB();

			if(pbr_material.base_color_texture.index != -1)
				material.m_pbr_block.m_albedo.m_texture = get_texture(state, pbr_material.base_color_texture.index);

			material.m_pbr_block.m_metallic.m_value = pbr_material.metallic_factor;
			material.m_pbr_block.m_roughness.m_value = pbr_material.roughness_factor;

			if(pbr_material.metallic_roughness_texture.index != -1)
			{
				Texture* texture = get_texture(state, pbr_material.metallic_roughness_texture.index);
				material.m_pbr_block.m_metallic.m_texture = texture;
				material.m_pbr_block.m_metallic.m_channel = TextureChannel::Blue;
				material.m_pbr_block.m_roughness.m_texture = texture;
				material.m_pbr_block.m_roughness.m_channel = TextureChannel::Green;
			}
		}

		if(gltf_material.normal_texture.index != -1)
		{
			material.m_pbr_block.m_normal.m_texture = get_texture(state, gltf_material.normal_texture.index);
			material.m_pbr_block.m_normal.m_value = gltf_material.normal_texture.scale;
		}

		if(gltf_material.occlusion_texture.index != -1)
		{
			material.m_pbr_block.m_ambient_occlusion.m_texture = get_texture(state, gltf_material.occlusion_texture.index);
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
			material.m_pbr_block.m_emissive.m_texture = get_texture(state, gltf_material.emissive_texture.index);
			material.m_pbr_block.m_emissive.m_value = Colour::Black;
			material.m_pbr_block.m_emissive.m_value.m_a = 2.f;
		}

		if(gltf_material.double_sided)
			material.m_base_block.m_cull_mode = CullMode::None;

		if(gltf_material.alpha_mode != glTFAlphaMode::OPAQUE)
			material.m_base_block.m_is_alpha = true;
	}

	void import_materials(const glTF& gltf, glTFImport& state)
	{
		for(const glTFMaterial& gltf_material : gltf.m_materials)
		{
			Material& material = state.m_gfx_system.fetch_material(gltf_material.name.c_str(), "pbr/pbr", false);
			import_material(state, gltf_material, material);
			state.m_imported_materials.push_back(&material);
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
				gltf.m_nodes[child].parent = i;
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

	void create_skeleton(const glTF& gltf, glTFImport& state, Model& model, int node, int num_bones)
	{
		const glTFNode& skeleton_node = gltf.m_nodes[node];

		printf("INFO: Gltf - adding skeleton %s\n", skeleton_node.name.c_str());
		model.m_rig->m_skeleton = { skeleton_node.name.c_str(), num_bones };
		state.m_skeletons[node] = &model.m_rig->m_skeleton;

		create_bone(gltf, skeleton_node, model.m_rig->m_skeleton, -1);
	}

	void import_skeletons(glTF& gltf, glTFImport& state, Model& model)
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
			model.m_rig->m_skins.emplace_back(*state.m_skeletons[gltf_skin.skeleton], gltf_skin.joints.size()); // gltf_skin.name
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
	void import_track(const glTFNode& node, glTFInterpolation interpolation, const std::vector<float>& times, const std::vector<T>& values, Animation& animation, size_t bone, Member& member)
	{
		AnimationTrack track = { animation, bone, node.name.c_str(), member };

		track.m_interpolation = interpolation == glTFInterpolation::STEP ? Interpolation::Nearest
																		 : Interpolation::Linear;
		for(size_t i = 0; i < times.size(); i++)
			track.m_keys.push_back(AnimationTrack::Key{ times[i], var(values[i]) });

		animation.tracks.push_back(track);
	}

	void import_animation(const glTF& gltf, size_t index, Model& model)
	{
		const glTFAnimation& gltf_anim = gltf.m_animations[index];

		model.m_rig->m_animations.push_back({ gltf_anim.name.c_str() });
		Animation& animation = model.m_rig->m_animations.back();
		animation.m_length = 0.f;

		printf("INFO: Gltf - importing animation %s\n", animation.m_name.c_str());

		for(const glTFAnimationChannel& channel : gltf_anim.channels)
		{
			const glTFAnimationSampler& sampler = gltf_anim.samplers[channel.sampler];
			const glTFNode& node = gltf.m_nodes[channel.target.node];

			Bone* bone = model.m_rig->m_skeleton.find_bone(node.name.c_str());
			size_t bone_index = bone ? bone->m_index : SIZE_MAX;

			std::vector<float> times = unpack_accessor<float>(gltf, sampler.input, false);

			float length = 0.f;

			for(float time : times)
				length = max(length, time);

			animation.m_length = max(animation.m_length, length);

			if(channel.target.path == "translation")
			{
				std::vector<vec3> translations = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, translations, animation, bone_index, member(&Bone::m_position));
			}
			else if(channel.target.path == "rotation")
			{
				std::vector<quat> rotations = unpack_accessor<quat, 4>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, rotations, animation, bone_index, member(&Bone::m_rotation));
			}
			else if(channel.target.path == "scale")
			{
				std::vector<vec3> scales = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, scales, animation, bone_index, member(&Bone::m_scale));
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

	mat4 derive_transform(const glTF& gltf, const glTFNode& node)
	{
		// not handling the matrix case here : waiting for c++17 optionals since matrix is almost never used
		if(node.parent > -1)
			return derive_transform(gltf, gltf.m_nodes[node.parent]) * node.matrix;
		else
			return node.matrix;
	}

	void import_items(const glTF& gltf, Model& model)
	{
		std::map<int, std::vector<int>> primitives;
		
		size_t primitive_index = 0;
		for(size_t mesh_index = 0; mesh_index < gltf.m_meshes.size(); ++mesh_index)
			for(size_t prim = 0; prim < gltf.m_meshes[mesh_index].primitives.size(); ++prim)
				primitives[mesh_index].push_back(primitive_index++);

		for(const glTFNode& node : gltf.m_nodes)
		{
			if(node.mesh > -1)
			{
				for(int primitive : primitives[node.mesh])
				{
					mat4 transform = derive_transform(gltf, node);
					model.m_items.emplace_back(ModelItem{ transform, model.m_meshes[primitive], node.skin, Colour::White, nullptr });
				}
			}

			//if(node.camera)
			//	;
		}
	}

	string file_directory(const string& path)
	{
		return path.substr(0, path.rfind('/') + 1);
	}

	string file_name(const string& path)
	{
		return path.substr(path.rfind('/') + 1);
	}

	void ImporterGltf::import_model(Model& model, const string& filepath, const ModelConfig& config)
	{
		printf("INFO: Gltf - loading model %s\n", filepath.c_str());

		string path = file_directory(filepath);
		string file = file_name(filepath);

		glTFImport state{ m_gfx_system, model, config };

		bool glb = false; // to_lower(path).ends_with("glb")
		if(glb)
			parse_glb(path + file + ".glb", state);
		else
			parse_json_file(path + file + ".gltf", state.m_json);

		json asset = state.m_json["asset"];
		string version = asset["version"].string_value();

		static FromJson unpacker = gltf_unpacker();
		Var gltf = Ref(&state.m_gltf);
		unpack(unpacker, gltf, state.m_json);

		setup_nodes(state.m_gltf);

		import_buffers(state.m_gltf, state, path);
		import_images(state.m_gltf, state, path, file);
		import_materials(state.m_gltf, state);
		import_meshes(state.m_gltf, state);

		model.add_rig(model.m_name.c_str());
		model.m_rig->m_skins.reserve(state.m_gltf.m_skins.size());
		model.m_rig->m_animations.reserve(state.m_gltf.m_animations.size());

		import_skeletons(state.m_gltf, state, model);

		for(size_t i = 0; i < state.m_gltf.m_animations.size(); i++)
			import_animation(state.m_gltf, int(i), model);

		import_items(state.m_gltf, model);

		model.prepare();
	}
}

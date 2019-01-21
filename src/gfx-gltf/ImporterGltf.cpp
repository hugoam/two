//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

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

#include <infra/Vector.h>
#include <infra/File.h>
#include <infra/String.h>
#include <infra/ToString.h>
#include <pool/Pool.h>
#include <srlz/Serial.h>
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
#include <gltf/Gltf.h>
#include <meta/gltf/Module.h>
#include <gfx-gltf/Types.h>
#include <gfx-gltf/ImporterGltf.h>
#endif

#define KUPOMAN_EXPORTER 1

namespace mud
{
	float* value_ptr(Colour& colour) { return &colour.m_r; }
	const float* value_ptr(const Colour& colour) { return &colour.m_r; }
}

namespace mud
{
	static ImportConfig load_model_config(cstring path, cstring model_name)
	{
		ImportConfig config = {};

		string config_path = file_directory(path) + "/" + model_name + ".cfg";
		if(file_exists(config_path.c_str()))
			unpack_json_file(Ref(&config), config_path);

		config.m_transform = bxSRT(config.m_scale, config.m_rotation, config.m_position);

		return config;
	}

	string extensions[] = { "gltf", "glb" };

	ImporterGltf::ImporterGltf(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
	{
		setup_gltf(mud_gltf::m());

		static auto load_gltf_model = [&](Model& model, cstring path)
		{
			ImportConfig config = load_model_config(path, model.m_name.c_str());
			this->import_model(model, path, config);
		};

		static auto load_gltf_prefab = [&](Prefab& prefab, cstring path)
		{
			ImportConfig config = load_model_config(path, prefab.m_name.c_str());
			this->import_prefab(prefab, path, config);
		};

		gfx_system.add_importer(ModelFormat::gltf, *this);
		gfx_system.models().add_format(".gltf", load_gltf_model);
		gfx_system.prefabs().add_format(".gltf", load_gltf_prefab);
	}

	static vector<uint8_t> read_base64_uri(const string& uri)
	{
		string decoded = decode_base64(uri.substr(uri.find(",") + 1).c_str()).c_str();
		return {};//vector_convert<uint8_t>(decoded);
	}

	vector<uint8_t> read_uri(const string& base_path, const string& uri)
	{
		if(uri.find("data:application/octet-stream;base64") == 0)
			return read_base64_uri(uri);
		else
			return read_binary_file(base_path + replace(uri, "\\", "/"));
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
					vector<uint8_t> data = read_base64_uri(image.uri);
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
			vector<vec2> uv1s = unpack_accessor<vec2, 2>(gltf, attributes.TEXCOORD_1, true);
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
		map<string, int> duplicate_names;

		size_t index = 0;
		for(const glTFMesh& gltf_mesh : gltf.m_meshes)
		{
#if 0
			string model_name = gltf_mesh.name == "" ? state.m_file + ":" + to_string(index++) : gltf_mesh.name;
			model_name += "_" + to_string(duplicate_names[model_name]++);
#else
			string model_name = state.m_file + ":" + to_string(index++);
#endif
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
#ifndef MUD_PLATFORM_EMSCRIPTEN
				//packer.m_quantize = true;
#endif

				packer.m_primitive = PrimitiveType::Triangles;//static_cast<PrimitiveType>(primitive.mode);
				import_attributes(gltf, packer, primitive.attributes);

				if(primitive.indices != -1)
				{
					vector<int> indices = unpack_accessor<int>(gltf, primitive.indices, false);
					packer.m_indices = vector_convert<uint32_t>(indices);
				}

				vector<MeshPacker> morphs;

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
						vector<vec3> tangents = unpack_accessor<vec3, 3>(gltf, morph_target.TANGENT, true);
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

#ifdef MUD_PLATFORM_EMSCRIPTEN
				mesh.write(PLAIN, packer, false);
#else
				mesh.write(PLAIN, packer, config.m_optimize_geometry);
#endif
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
		map<int, int> skeleton_sizes;

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

			vector<mat4> bind_matrices;

			if(gltf_skin.inverse_bind_matrices != -1)
				bind_matrices = unpack_accessor<mat4, 16>(gltf, gltf_skin.inverse_bind_matrices, false);

			size_t index = 0;
			for(int joint : gltf_skin.joints)
				skin.add_joint(gltf.m_nodes[joint].name.c_str(), bind_matrices[index++]);
		}
	}

	template <class T>
	void import_track(const glTFNode& node, glTFInterpolation interpolation, const vector<float>& times, const vector<T>& values, Animation& animation, size_t bone, AnimationTarget target)
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

			vector<float> times = unpack_accessor<float>(gltf, sampler.input, false);

			float length = 0.f;

			for(float time : times)
				length = max(length, time);

			animation.m_length = max(animation.m_length, length);

			if(channel.target.path == "translation")
			{
				vector<vec3> translations = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, translations, animation, bone_index, AnimationTarget::Position); // member(&Bone::m_position)
			}
			else if(channel.target.path == "rotation")
			{
				vector<quat> rotations = unpack_accessor<quat, 4>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, rotations, animation, bone_index, AnimationTarget::Rotation); // member(&Bone::m_rotation)
			}
			else if(channel.target.path == "scale")
			{
				vector<vec3> scales = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track(node, sampler.interpolation, times, scales, animation, bone_index, AnimationTarget::Scale); // member(&Bone::m_scale)
			}
			else if(channel.target.path == "weights")
			{
				vector<float> weights = unpack_accessor<float>(gltf, sampler.output, false);
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

	void import_gltf(glTF& gltf, Import& state, const ImportConfig& config)
	{
		setup_nodes(gltf);

		import_buffers(gltf, state);
		import_images(gltf, state);
		import_materials(gltf, state);
		import_meshes(gltf, state, config);
		import_items(gltf, state, config);
	}

	void export_repack(glTF& gltf, const string& path, const string& file)
	{
		auto repack = [](glTF& gltf, const string& name, glTFPrimitive& primitive)
		{
			GfxSystem& gfx = *(GfxSystem*)gltf.m_user;
			Mesh* mesh = gfx.meshes().find([&](Mesh& mesh) { return mesh.m_name == name; });
			if(!mesh) return;
			MeshPacker packer;
			mesh->read(packer, bxidentity());
			primitive.attributes = {};
			export_attributes(gltf, 0, packer, primitive.attributes);
			primitive.indices = export_indices(gltf, 0, packer); 
		};

		repack_gltf(gltf, path, file, repack);
	}

	void ImporterGltf::import(Import& state, const string& filepath, const ImportConfig& config)
	{
		printf("INFO: gltf - loading scene %s\n", filepath.c_str());

		glTF gltf = { &m_gfx_system };
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
	}

	void ImporterGltf::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		printf("INFO: gltf - loading model %s\n", filepath.c_str());

		Import state = { m_gfx_system, filepath, config };

		glTF gltf = { &m_gfx_system };
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

		glTF gltf = { &m_gfx_system };
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

		glTF gltf = { &m_gfx_system };
		unpack_gltf(path, file, gltf);
		export_repack(gltf, path, file);
	}
}

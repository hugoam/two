#include <two/gfx.h>
#include <two/gfx.gltf.h>
#include <two/pool.h>
#include <two/geom.h>
#include <two/srlz.h>
#include <two/gltf.h>
#include <two/math.h>
#include <two/infra.h>
#include <two/type.h>
#include <two/gltf.refl.h>


#ifdef TWO_MODULES
module two.gfx-gltf;
#else
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>() { static Type ty("ImporterGltf", sizeof(two::ImporterGltf)); return ty; }
}


//#include <base64.h>
#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.gltf;
#else
#include <stl/algorithm.h>
#include <stl/hash_base.hpp>
#endif

#include <cstdio>

#define KUPOMAN_EXPORTER 1

namespace two
{
	float* value_ptr(Colour& colour) { return &colour.r; }
	const float* value_ptr(const Colour& colour) { return &colour.r; }
}

namespace two
{
	static ImportConfig load_model_config(const string& path, const string& model_name, const ImportConfig& inconfig)
	{
		ImportConfig config = inconfig;

		string config_path = file_directory(path) + "/" + model_name + ".cfg";
		if(file_exists(config_path))
			unpack_json_file(Ref(&config), config_path);

		config.m_transform = bxSRT(config.m_scale, config.m_rotation, config.m_position);

		return config;
	}

	string extensions[] = { "gltf", "glb" };

	ImporterGltf::ImporterGltf(GfxSystem& gfx)
		: m_gfx(gfx)
	{
		setup_gltf(two_gltf::m());

		static auto load_gltf_model = [&](Model& model, const string& path, const ImportConfig& inconfig)
		{
			ImportConfig config = load_model_config(path, model.m_name, inconfig);
			this->import_model(model, path, config);
		};

		static auto load_gltf_prefab = [&](Prefab& prefab, const string& path, const ImportConfig& inconfig)
		{
			ImportConfig config = load_model_config(path, prefab.m_name, inconfig);
			this->import_prefab(prefab, path, config);
		};

		gfx.add_importer(ModelFormat::gltf, *this);

		gfx.models().add_format(".gltf", load_gltf_model);
		gfx.prefabs().add_format(".gltf", load_gltf_prefab);

		gfx.models().add_format(".glb", load_gltf_model);
		gfx.prefabs().add_format(".glb", load_gltf_prefab);
	}

	mat4 derive_transform(const glTF& gltf, const glTFNode& node)
	{
		// not handling the matrix case here : waiting for c++17 optionals since matrix is almost never used
		if(node.parent > -1)
			return derive_transform(gltf, gltf.m_nodes[node.parent]) * node.matrix;
		else
			return node.matrix;
	}

	static vector<uint8_t> read_base64_uri(const string& uri)
	{
		//std::string base64 = uri.substr(uri.find(",") + 1).c_str();
		string decoded;// = decode_base64(base64).c_str();
		return {};//convert<uint8_t>(decoded);
	}

	vector<uint8_t> read_uri(const string& base_path, const string& uri)
	{
		if(uri.find("data:application/octet-stream;base64") == 0)
			return read_base64_uri(uri);
		else
			return read_binary_file(base_path + "/" + replace(uri, "\\", "/"));
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
		auto import_image_mem = [&](span<uint8_t> data)
		{
			string name = state.m_file + to_string(state.m_images.size());
			Texture& texture = state.m_gfx.textures().create(name.c_str());
			load_texture_mem(state.m_gfx, texture, data);
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
					string path = state.m_path + "/" + state.m_file;
					Texture& texture = state.m_gfx.textures().file_at(path.c_str(), image.uri.c_str());
					//Texture& texture = state.m_gfx.textures().file(image.uri.c_str());
					state.m_images.push_back(&texture);
				}
			}
			else if(image.buffer_view != -1)
			{
				const glTFBufferView& buffer_view = gltf.m_buffer_views[image.buffer_view];
				span<uint8_t> data = { gltf.m_binary_buffers[buffer_view.buffer].data() + buffer_view.byte_offset, buffer_view.byte_length };
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
			// add it only if not filled with zeroes
			if(find_if(uv1s, [](const vec2& uv) { return uv != vec2(0.f);}) != uv1s.end())
				mesh.m_uv1s = uv1s;
		}
		if(attributes.COLOR_0 != -1)
		{
			if(gltf.m_accessors[attributes.COLOR_0].type == glTFType::VEC4)
				mesh.m_colours = unpack_accessor<Colour, 4>(gltf, attributes.COLOR_0, true);
			else if(gltf.m_accessors[attributes.COLOR_0].type == glTFType::VEC3)
			{
				vector<vec3> colours = unpack_accessor<vec3, 3>(gltf, attributes.COLOR_0, true);
				mesh.m_colours = convert<Colour, vec3>(colours, [](const vec3& v) { return to_colour(v); });
			}
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

			Model* existing = state.m_gfx.models().get(model_name.c_str());
			if(existing && !config.m_force_reimport)
			{
				state.m_models.push_back(existing);
				continue;
			}

			Model& model = state.m_gfx.models().create(model_name.c_str());

			size_t primindex = 0;
			for(const glTFPrimitive& primitive : gltf_mesh.primitives)
			{
				string name = model_name + ":" + to_string(primindex++);
				bool occluder = false;

				//printf("[debug] importing mesh %s\n", name.c_str());

				if(primitive.material != -1)
				{
					occluder |= state.m_materials[primitive.material]->m_name == "occluder";

					if(config.filter_material(state.m_materials[primitive.material]->m_name))
					{
						state.m_meshes.push_back(nullptr);
						continue;
					}
				}

				Mesh& mesh = model.add_mesh(name.c_str(), config.m_cache_geometry || occluder);
				state.m_meshes.push_back(&mesh);
				model.add_item(mesh, bxidentity());

				MeshPacker packer;
#ifndef TWO_PLATFORM_EMSCRIPTEN
				//packer.m_quantize = true;
#endif

				packer.m_primitive = PrimitiveType::Triangles;//static_cast<PrimitiveType>(primitive.mode);
				import_attributes(gltf, packer, primitive.attributes);

				if(primitive.indices != -1)
				{
					vector<int> indices = unpack_accessor<int>(gltf, primitive.indices, false);
					packer.m_indices = convert<uint32_t, int>(indices);
				}

				for(const glTFMorphTarget& morph_target : primitive.targets)
				{
					MeshPacker morph;
					
					auto test = gltf.m_accessors[morph_target.POSITION].type;

					if(morph_target.POSITION != -1)
						morph.m_positions = unpack_accessor<vec3, 3>(gltf, morph_target.POSITION, true);
					if(morph_target.NORMAL != -1)
						morph.m_normals = unpack_accessor<vec3, 3>(gltf, morph_target.NORMAL, true);
					if(morph_target.TANGENT != -1)
					{
						vector<vec3> tangents = unpack_accessor<vec3, 3>(gltf, morph_target.TANGENT, true);
						morph.m_tangents.resize(tangents.size());

						for(size_t i = 0; i < packer.m_tangents.size(); ++i)
							morph.m_tangents[i] = { tangents[i], packer.m_tangents[i].w };
					}

					mesh.morph(morph);
				}

				if(primitive.material != -1)
					mesh.m_material = state.m_materials[primitive.material];

				// @todo add external control for this behavior (normals/flat normals etc...)
				if(packer.m_normals.empty())
					packer.gen_normals();

				if(packer.m_tangents.empty() && !packer.m_normals.empty() && !packer.m_uv0s.empty())
					packer.gen_tangents();
				if(packer.m_tangents.empty() && packer.m_uv0s.empty())
					printf("[warning] mesh %s imported without tangents (no uvs)\n", name.c_str());

				bool optimize = config.m_optimize_geometry;
#ifdef TWO_PLATFORM_EMSCRIPTEN
				optimize = false;
#endif

				if(config.m_no_transforms)
				{
					const mat4 transform = config.m_transform * derive_transform(gltf, gltf.m_nodes[gltf_mesh.node]);
					mesh.xwrite(packer, transform);
				}
				else
					mesh.write(packer, optimize);
			}

			if(model.m_items.size() == 0)
			{
				state.m_gfx.models().destroy(model_name.c_str());
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

			//material.m_base.m_shader_color = ShaderColor::Vertex;
			//material.m_base.m_flat_shaded = true;

			material.m_pbr.m_albedo.m_value = to_colour(pbr_material.base_color_factor);

			if(pbr_material.base_color_texture.index != -1)
			{
				material.m_pbr.m_albedo.m_value = Colour::White;
				material.m_pbr.m_albedo = get_texture(gltf, state, pbr_material.base_color_texture.index);
			}

			material.m_pbr.m_metallic.m_value = pbr_material.metallic_factor;
			material.m_pbr.m_roughness.m_value = pbr_material.roughness_factor;

			if(pbr_material.metallic_roughness_texture.index != -1)
			{
				Texture* texture = get_texture(gltf, state, pbr_material.metallic_roughness_texture.index);
				material.m_pbr.m_metallic = texture;
				material.m_pbr.m_metallic.m_channel = TextureChannel::Blue;
				material.m_pbr.m_roughness = texture;
				material.m_pbr.m_roughness.m_channel = TextureChannel::Green;
			}
		}

		if(gltf_material.normal_texture.index != -1)
		{
			material.m_lit.m_normal = get_texture(gltf, state, gltf_material.normal_texture.index);
			material.m_lit.m_normal.m_value = gltf_material.normal_texture.scale;
		}

		if(gltf_material.occlusion_texture.index != -1)
		{
			material.m_lit.m_occlusion = get_texture(gltf, state, gltf_material.occlusion_texture.index);
			material.m_lit.m_occlusion.m_channel = TextureChannel::Red;
		}

		vec3 emissive = gltf_material.emissive_factor;
#if KUPOMAN_EXPORTER
		emissive *= vec3(gltf_material.pbr_metallic_roughness.base_color_factor);
#endif
		float emissive_factor = (emissive.r + emissive.g + emissive.b) / 3.f;
		material.m_lit.m_emissive.m_value = to_colour(vec4(emissive / emissive_factor, emissive_factor));

		if(gltf_material.emissive_texture.index != -1)
		{
			material.m_lit.m_emissive = get_texture(gltf, state, gltf_material.emissive_texture.index);
			material.m_lit.m_emissive.m_value = Colour::Black;
			material.m_lit.m_emissive.m_value.a = emissive_factor;
		}

		//if(gltf_material.double_sided)
		//	material.m_base.m_cull_mode = CullMode::None;

		if(gltf_material.alpha_mode != glTFAlphaMode::OPAQUE)
		{
			material.m_alpha.m_is_alpha = true;
			material.m_alpha.m_alpha = material.m_pbr.m_albedo.m_value.a;
			material.m_base.m_depth_draw = DepthDraw::Disabled;
		}

		if(gltf_material.alpha_mode == glTFAlphaMode::BLEND)
			material.m_base.m_blend_mode = BlendMode::Alpha;
	}

	void import_materials(const glTF& gltf, Import& state)
	{
		size_t index = 0;
		for(const glTFMaterial& gltf_material : gltf.m_materials)
		{
			string name = gltf_material.name == "" ? state.m_file + ":" + to_string(index++) : gltf_material.name;
			Material& material = state.m_gfx.fetch_material(name.c_str(), "pbr/pbr", false);
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
		{
			if(gltf.m_nodes[i].mesh != -1)
				gltf.m_meshes[gltf.m_nodes[i].mesh].node = i;

			for(size_t j = 0; j < gltf.m_nodes[i].children.size(); j++)
			{
				int child = gltf.m_nodes[i].children[j];
				gltf.m_nodes[child].parent = int(i);
			}
		}
	}

	void create_bone(const glTF& gltf, const glTFNode& node, Skeleton& skeleton, uint32_t parent)
	{
		//printf("[info]      - adding bone %s index %i\n", node.name.c_str(), skeleton.m_bones.size());
		uint32_t bone = skeleton.add_bone(node.name.c_str(), parent);

		for(int child : node.children)
			if(gltf.m_nodes[child].is_joint)
				create_bone(gltf, gltf.m_nodes[child], skeleton, bone);
	}

	void create_skeleton(const glTF& gltf, Import& state, Model& model, int node, int num_bones)
	{
		const glTFNode& skeleton_node = gltf.m_nodes[node];

		printf("[info] Gltf - adding skeleton %s\n", skeleton_node.name.c_str());
		model.m_rig->m_skeleton = { skeleton_node.name.c_str(), num_bones };
		state.m_skeletons[node] = &model.m_rig->m_skeleton;

		create_bone(gltf, skeleton_node, model.m_rig->m_skeleton, UINT32_MAX);
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
			printf("[info] Gltf - adding skin %s\n", gltf_skin.name.c_str());
			model.m_rig->m_skins.push_back({ *state.m_skeletons[gltf_skin.skeleton], int(gltf_skin.joints.size()) }); // gltf_skin.name
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
	void import_track(glTFInterpolation interpolation, const string& name, span<float> times, span<T> values, Animation& animation, size_t node, AnimTarget target)
	{
		AnimTrack track = { animation, node, name.c_str(), target };

		track.m_interpolation = interpolation == glTFInterpolation::STEP ? Interpolation::Nearest
																		 : Interpolation::Linear;
		for(size_t i = 0; i < times.size(); i++)
			track.m_keys.push_back({ times[i], values[i] });

		animation.tracks.push_back(track);
	}

	void import_animation(const glTF& gltf, Import& state, size_t index, Rig* rig = nullptr)
	{
		const glTFAnimation& gltf_anim = gltf.m_animations[index];

		Animation& animation = state.m_gfx.animations().construct(gltf_anim.name.c_str());
		state.m_animations.push_back(&animation);

		animation.m_length = 0.f;

		printf("[info] Gltf - importing animation %s\n", animation.m_name.c_str());

		for(const glTFAnimationChannel& channel : gltf_anim.channels)
		{
			const glTFAnimationSampler& sampler = gltf_anim.samplers[channel.sampler];
			const glTFNode& node = gltf.m_nodes[channel.target.node];

			size_t node_index = SIZE_MAX;
			if(node.is_joint)
			{
				uint32_t bone = rig->m_skeleton.bone_index(node.name.c_str());
				node_index = bone != UINT32_MAX ? bone : SIZE_MAX;
			}
			else
			{
				node_index = channel.target.node;
			}

			vector<float> times = unpack_accessor<float>(gltf, sampler.input, false);

			float length = 0.f;

			for(float time : times)
				length = max(length, time);

			animation.m_length = max(animation.m_length, length);

			if(channel.target.path == "translation")
			{
				const vector<vec3> translations = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track<vec3>(sampler.interpolation, node.name, times, translations, animation, node_index, AnimTarget::Position);
			}
			else if(channel.target.path == "rotation")
			{
				const vector<quat> rotations = unpack_accessor<quat, 4>(gltf, sampler.output, false);
				import_track<quat>(sampler.interpolation, node.name, times, rotations, animation, node_index, AnimTarget::Rotation);
			}
			else if(channel.target.path == "scale")
			{
				const vector<vec3> scales = unpack_accessor<vec3, 3>(gltf, sampler.output, false);
				import_track<vec3>(sampler.interpolation, node.name, times, scales, animation, node_index, AnimTarget::Scale);
			}
			else if(channel.target.path == "weights")
			{
				const vector<float> weights = unpack_accessor<float>(gltf, sampler.output, false);
				const size_t key_size = gltf.m_meshes[node.mesh].weights.size();

				vector<vector<float>> track;
				for(size_t i = 0; i < weights.size(); i += key_size)
				{
					vector<float>& key = push(track);
					for(size_t n = 0; n < key_size; ++n)
						key.push_back(weights[i + n]);
				}

				import_track<vector<float>>(sampler.interpolation, node.name, times, track, animation, node_index, AnimTarget::Weights);
			}
		}
	}

	void import_rig(glTF& gltf, Import& state, Model& model)
	{
		Rig& rig = model.add_rig(model.m_name.c_str());
		rig.m_skins.reserve(gltf.m_skins.size());

		import_skeletons(gltf, state, model);
	}

	void import_animations(glTF& gltf, Import& state, Rig* rig = nullptr)
	{
		for(size_t i = 0; i < gltf.m_animations.size(); i++)
			import_animation(gltf, state, int(i), rig);
	}

	void import_items(const glTF& gltf, Import& state, const ImportConfig& config)
	{
		state.m_nodes.reserve(gltf.m_nodes.size());
		
		uint32_t i = 0;
		for(const glTFNode& node : gltf.m_nodes)
		{
			if(config.filter_element(node.name))
				continue;

			static const mat4 identity = bxidentity();
			const mat4 transform = config.m_no_transforms
				? identity
				: config.m_transform * derive_transform(gltf, node);

			state.m_nodes.push_back(Node3(transform, node.parent));
			Node3& n = state.m_nodes.back();

			if(node.mesh > -1)
			{
				Model* model = state.m_models[node.mesh];
				if(!model) { i++; continue; }
				const size_t item = state.m_items.size();
				state.m_items.push_back({ i, model, node.skin });
			}

			i++;

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
			packer.unpack(mesh->m_cache, bxidentity());
			primitive.attributes = {};
			export_attributes(gltf, 0, packer, primitive.attributes);
			primitive.indices = export_indices(gltf, 0, packer); 
		};

		repack_gltf(gltf, path, file, repack);
	}

	void ImporterGltf::import(Import& state, const string& filepath, const ImportConfig& config)
	{
		printf("[info] gltf - loading scene %s\n", filepath.c_str());

		glTF gltf = { &m_gfx };
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
	}

	void ImporterGltf::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		printf("[info] gltf - loading model %s\n", filepath.c_str());

		Import state = { m_gfx, filepath, config };

		glTF gltf = { &m_gfx };
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
		import_rig(gltf, state, model);
		import_animations(gltf, state, model.m_rig);

		for(const Import::Item& item : state.m_items)
		{
			const Node3& node = state.m_nodes[item.node];
			for(const ModelElem& elem : item.model->m_items)
				model.add_item(*elem.m_mesh, node.m_transform, item.skin);
		}

		for(Animation* anim : state.m_animations)
			model.m_anims.push_back(anim);

		model.prepare();
	}

	void ImporterGltf::import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config)
	{
		printf("[info] gltf - loading prefab %s\n", filepath.c_str());

		Import state = { m_gfx, filepath, config };

		glTF gltf = { &m_gfx };
		unpack_gltf(state.m_path, state.m_file, gltf);

		import_gltf(gltf, state, config);
		import_animations(gltf, state);
		import_to_prefab(m_gfx, prefab, state, config.m_flags);
	}

	void ImporterGltf::repack(const string& filepath, const ImportConfig& config)
	{
		UNUSED(config);
		printf("[info] gltf - repacking asset %s\n", filepath.c_str());

		string path = file_directory(filepath);
		string file = file_name(filepath);

		glTF gltf = { &m_gfx };
		unpack_gltf(path, file, gltf);
		export_repack(gltf, path, file);
	}
}

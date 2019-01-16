//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <fstream>
#include <sstream>
#include <string>
#endif

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.obj;
#else
#include <infra/Vector.h>
#include <infra/File.h>
#include <infra/ToString.h>
#include <pool/Pool.h>
#include <math/Timer.h>
#include <math/Stream.h>
#include <math/VecOps.h>
#include <geom/Mesh.h>
#include <srlz/Serial.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Prefab.h>
#include <gfx/Draw.h>
#include <gfx/Node3.h>
#include <gfx/Texture.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-obj/Types.h>
#include <gfx-obj/ImporterObj.h>
#endif

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

	ImporterOBJ::ImporterOBJ(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
	{
		static auto load_obj_model = [](void* self, Model& model, cstring path)
		{
			ImportConfig config = load_model_config(path, model.m_name.c_str());
			((ImporterOBJ*)self)->import_model(model, path, config);
		};

		static auto load_obj_prefab = [](void* self, Prefab& prefab, cstring path)
		{
			ImportConfig config = load_model_config(path, prefab.m_name.c_str());
			((ImporterOBJ*)self)->import_prefab(prefab, path, config);
		};

		gfx_system.add_importer(ModelFormat::obj, *this);
		gfx_system.models().add_format(".obj", { this, load_obj_model });
		gfx_system.prefabs().add_format(".obj", { this, load_obj_prefab });
	}

	void import_material_library(GfxSystem& gfx_system, const string& path, MaterialMap& material_map)
	{
		string models_path = "models/" + path;
		string materials_path = "materials/" + path;
		LocatedFile location = gfx_system.locate_file(models_path.c_str());
		if(location.m_location == nullptr)
			location = gfx_system.locate_file(materials_path.c_str());

		string filepath = string(location.m_location) + location.m_name;
		std::ifstream file = std::ifstream(filepath.c_str());

		if(!file.good())
			return;

		Material* current = nullptr;

		std::string line;
		while(std::getline(file, line))
		{
			std::istringstream stream(line);

			std::string command = read<std::string>(stream);

			// "Ka" ambient rgb
			// "Kd" diffuse rgb
			// "Ks" specular rgb
			// "Kt" "Tf" transmittance rgb
			// "Ni" ior(index of refraction) float
			// "Ke" emission rgb
			// "Ns" shininess float
			// "illum" illum model
			// "d" dissolve
			// "Tr" transparency
			// "Pr" PBR: roughness
			// "Pm" PBR: metallic
			// "Ps" PBR: sheen
			// "Pc" PBR: clearcoat thickness
			// "Pcr" PBR: clearcoat roughness
			// "aniso" PBR: anisotropy
			// "anisor" PBR: anisotropy rotation

			auto fetch_texture = [&](const string& path) -> Texture*
			{
				// @todo replace backslashes with slashes ?
				if(gfx_system.locate_file(("textures/" + path).c_str()).m_location)
					return gfx_system.textures().file(path.c_str());
				else
					return nullptr;
			};

			if(command == "newmtl")
			{
				string name = read<std::string>(stream).c_str();
				current = &gfx_system.fetch_material(name.c_str(), "pbr/pbr");
				current->m_pbr_block.m_enabled = true;
				material_map[name] = current;
			}
			else if(command == "Ka")
			{
				// nothing
			}
			else if(command == "Kd")
			{
				Colour albedo = read<Colour>(stream);
				current->m_pbr_block.m_albedo.m_value = albedo;
			}
			else if(command == "Ks")
			{
				Colour specular = read<Colour>(stream);
				current->m_pbr_block.m_metallic.m_value = max(specular.m_r, max(specular.m_g, specular.m_b));
			}
			else if(command == "Ke")
			{
				Colour emissive = read<Colour>(stream);
				current->m_pbr_block.m_emissive.m_value = emissive;
				current->m_pbr_block.m_emissive.m_value.m_a = length(to_vec3(emissive));
			}
			else if(command == "Ns")
			{
				float specular = read<float>(stream);
				current->m_pbr_block.m_metallic.m_value = (1000.f - specular) / 1000.f;
			}
			else if(command == "d")
			{
				float d = read<float>(stream);
				current->m_pbr_block.m_albedo.m_value.m_a = d;
			}
			else if(command == "Tr")
			{
				float tr = read<float>(stream);
				current->m_pbr_block.m_albedo.m_value.m_a = 1.f - tr;
			}
			else if(command == "Pr")
			{
				float roughness = read<float>(stream);
				current->m_pbr_block.m_roughness.m_value = roughness;
			}
			else if(command == "Pm")
			{
				float metallic = read<float>(stream);
				current->m_pbr_block.m_metallic.m_value = metallic;
			}
			else if(command.substr(0, 4) == "map")
			{
				string map = read<std::string>(stream).c_str();
				if(command == "map_Ka ") // ambient texture
				{
					// nothing
				}
				else if(command == "map_Kd") // diffuse texture
				{
					current->m_pbr_block.m_albedo.m_texture = fetch_texture(map);
				}
				else if(command == "map_Ks") // specular texture
				{
					//current->m_pbr_block.m_metallic.m_value = 1.f;
					current->m_pbr_block.m_metallic.m_texture = fetch_texture(map);
				}
				else if(command == "map_Ke") // emissive texture
				{
					current->m_pbr_block.m_emissive.m_texture = fetch_texture(map);
					current->m_pbr_block.m_emissive.m_value.m_a = 2.f;
				}
				else if(command == "map_Ns") // specular highlight texture
				{
					current->m_pbr_block.m_roughness.m_texture = fetch_texture(map);
				}
				else if(command == "map_bump" || command == "bump") // bump texture
				{
					current->m_pbr_block.m_normal.m_texture = fetch_texture(map);
				}
				else if(command == "map_Pr") // PBR: roughness texture
				{
					current->m_pbr_block.m_roughness.m_texture = fetch_texture(map);
				}
				else if(command == "map_Pm") // PBR: metallic texture
				{
					//current->m_pbr_block.m_metallic.m_value = 1.f;
					current->m_pbr_block.m_metallic.m_texture = fetch_texture(map);
				}
			}

			// "map_d"  alpha texture
			// "disp"   displacement texture
			// "refl"   reflection map
			// "map_Pr" PBR: roughness texture
			// "map_Pm" PBR: metallic texture
			// "map_Ps" PBR: sheen texture
			// "norm"   PBR: normal map texture
		}
	}

	void ImporterOBJ::import(Import& scene, const string& path, const ImportConfig& config)
	{
		auto tof = [](const string& s) { return float(atof(s.c_str())); };
		auto toi = [](const string& s) { return atoi(s.c_str()); };

		printf("INFO: gltf - loading scene %s\n", scene.m_file.c_str());

		Clock clock;
		clock.step();

		bool generate_tangents = true;

		vector<vec3> vertices;
		vector<vec3> normals;
		vector<vec2> uvs;
		map<string, Material*> materials;
		
		enum VertAttrib
		{
			POSITION,
			TEXCOORD,
			NORMAL
		};

		struct MeshWriter
		{
			MeshWriter(const ImportConfig& config, Import& import, bool generate_tangents)
				: m_config(config)
				, m_import(import)
				, m_name(import.m_name)
				, m_generate_tangents(generate_tangents)
			{}

			~MeshWriter()
			{
				if(m_shape.vertex_count() == 0 || m_skip)
					return;

				Mesh& mesh = m_import.m_gfx_system.meshes().construct(m_name.c_str(), true);
				m_shape.bake(!m_normals, m_generate_tangents && m_uvs);
				mesh.write(PLAIN, m_shape, m_config.m_optimize_geometry);
				mesh.m_material = m_material;
				m_import.m_meshes.push_back(&mesh);

				Model& model = m_import.m_gfx_system.models().create(m_name.c_str());
				model.add_item(mesh, bxidentity());
				model.prepare();
				m_import.m_models.push_back(&model);

				m_import.m_items.push_back({ bxidentity(), &model, -1 });

				//printf("INFO: ImporterOBJ imported mesh %s material %s with %u vertices and %u faces\n", 
				//	   m_mesh.m_name.c_str(), m_mesh.m_material->m_name.c_str(), m_shape.m_positions.size(), m_shape.m_indices.size() / 3);
			}

			inline void face(ShapeVertex* face, size_t a, size_t b, size_t c)
			{
				auto vertex = [&](ShapeVertex& vertex)
				{
					m_shape.m_positions.push_back(vertex.m_position);
					m_shape.m_normals.push_back(vertex.m_normal);
					m_shape.m_uv0s.push_back(vertex.m_uv0);
				};
				// bool flip_faces;
				// int i = !flip_faces && i < 2 ? 1 ^ i : i;
				vertex(face[a]);
				vertex(face[b]);
				vertex(face[c]);
			}

			const ImportConfig& m_config;
			Import& m_import;
			string m_name;
			Material* m_material = nullptr;
			MeshPacker m_shape;
			bool m_generate_tangents;
			bool m_normals = true;
			bool m_uvs = true;
			int m_smoothing_group = 0;
			bool m_skip = false;
		};

		string filename = path + ".obj";
		std::ifstream filestream(filename.c_str());

		if(!filestream.good())
		{
			printf("ERROR: could not locate model %s\n", filename.c_str());
			return;
		}

		unique<MeshWriter> mesh_writer = make_unique<MeshWriter>(config, scene, generate_tangents);

		std::string line;

		while(std::getline(filestream, line))
		{
			if(line.back() == '\r')
				line.pop_back();

			string tokens[5];
			split(line.c_str(), " ", { tokens, 5 });

			const string& command = tokens[0];

			if(command == "o" || command == "g")
			{
				mesh_writer = nullptr;
				mesh_writer = make_unique<MeshWriter>(config, scene, generate_tangents);
			}
			if(command == "o")
			{
				const string& name = tokens[1];
				scene.m_name = name.c_str();
			}
			else if(command == "g")
			{
				const string& name = tokens[1];
				mesh_writer->m_name = name.c_str();
				if(config.filter_element(name))
					mesh_writer->m_skip = true;
			}
			else if(command == "usemtl")
			{
				const string& material = tokens[1];
				mesh_writer->m_material = materials[material];
				if(config.filter_material(material))
					mesh_writer->m_skip = true;
			}
			else if(command == "s") //smoothing
			{
				const string& value = tokens[1];
				mesh_writer->m_smoothing_group = value == "off" ? 0
																: toi(value);
			}
			else if(command == "v")
			{
				vec3 vert = { tof(tokens[1]), tof(tokens[2]), tof(tokens[3]) };
				vert = mulp(config.m_transform, vert);
				vertices.emplace_back(vert);
			}
			else if(command == "vt")
			{
				vec2 uv = { tof(tokens[1]), tof(tokens[2]) };
				uvs.push_back({ uv.x, 1.f - uv.y });
			}
			else if(command == "vn")
			{
				vec3 norm = { tof(tokens[1]), tof(tokens[2]), tof(tokens[3]) };
				norm = muln(config.m_transform, norm);
				normals.emplace_back(norm);
			}
			else if(command == "f")
			{
				ShapeVertex verts[4];

				size_t num_vertices = tokens[4] == "" ? 3 : 4;
				for(size_t i = 0; i < num_vertices; ++i)
				{
					string ids[3];
					split(tokens[i + 1], "/", { ids, 3 });

					int face[3] = { toi(ids[0]), toi(ids[1]), toi(ids[2]) };

					verts[i].m_position = face[POSITION] >= 0 ? vertices[face[POSITION] - 1] : vertices[face[POSITION] + vertices.size()];
					if(face[TEXCOORD] != 0)
						verts[i].m_uv0 = face[TEXCOORD] >= 0 ? uvs[face[TEXCOORD] - 1] : uvs[face[TEXCOORD] + uvs.size()];
					if(face[NORMAL] != 0)
						verts[i].m_normal = face[NORMAL] >= 0 ? normals[face[NORMAL] - 1] : normals[face[NORMAL] + normals.size()];
				}

				mesh_writer->face(verts, 0, 1, 2);

				if(!tokens[4].empty())
					mesh_writer->face(verts, 0, 2, 3);
			}
			else if(command == "mtllib")
			{
				const string& lib_path = tokens[1];
				import_material_library(m_gfx_system, lib_path, materials);
			}
		}

		printf("INFO: obj - imported %i vertices in %.2f seconds\n", int(vertices.size()), clock.step());
		
		mesh_writer = nullptr;
	}

	void ImporterOBJ::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx_system, filepath, config };

		this->import(state, filepath, config);

		for(const Import::Item& item : state.m_items)
		{
			for(const ModelItem& model_item : item.model->m_items)
				model.add_item(*model_item.m_mesh, item.transform, item.skin);
		}

		model.prepare();
	}

	void ImporterOBJ::import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx_system, filepath, config };

		this->import(state, filepath, config);

		import_to_prefab(m_gfx_system, prefab, state, config.m_flags);
	}

	void ImporterOBJ::repack(const string& filepath, const ImportConfig& config)
	{
		UNUSED(filepath); UNUSED(config);
		printf("WARNING: obj - repack for this format not supported\n");
	}
}

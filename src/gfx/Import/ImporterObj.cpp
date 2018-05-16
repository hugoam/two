
#include <gfx/Generated/Types.h>
#include <gfx/Import/ImporterObj.h>

#include <obj/Vector.h>
#include <obj/Util/Timer.h>

#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/GfxSystem.h>
#include <gfx/Draw.h>
#include <gfx/Node3.h>

#include <obj/String/StringConvert.h>
#include <math/Stream.h>

#include <array>

#include <fstream>
#include <sstream>
#include <string>

namespace mud
{
	ImporterOBJ::ImporterOBJ(GfxSystem& gfx_system)
		: m_gfx_system(gfx_system)
	{}

	void ImporterOBJ::import_material_library(const string& path, MaterialMap& material_map)
	{
		carray<cstring, 1> exts = { "" };
		string base_path = m_gfx_system.locate_file(("models/" + path).c_str(), exts);
		if(base_path == "")
			base_path = m_gfx_system.locate_file(("materials/" + path).c_str(), exts);

		std::ifstream file = std::ifstream(base_path + "models/" + path);

		if(!file.good())
		{
			base_path = base_path + "materials/";
			file = std::ifstream(base_path + path);
		}

		if(!file.good())
			return;

		Material* current = nullptr;

		string line;
		while(std::getline(file, line))
		{
			std::istringstream stream(line);

			string command = read<string>(stream);

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
				// @todo replace backslashes with slashes  ?
				if(m_gfx_system.locate_file(("textures/" + path).c_str(), exts))
					return &m_gfx_system.get_texture(path.c_str());
				else
					return nullptr;
			};

			if(command == "newmtl")
			{
				string name = read<string>(stream);
				current = &m_gfx_system.create_material(name.c_str(), "pbr/pbr");
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
				current->m_pbr_block.m_emissive.m_value.m_a = 2.f;
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
			else if(command == "map_Ka ") // ambient texture
			{
				// nothing
			}
			else if(command == "map_Kd") // diffuse texture
			{
				string map = read<string>(stream);
				current->m_pbr_block.m_albedo.m_texture = fetch_texture(map);
			}
			else if(command == "map_Ks") // specular texture
			{
				string map = read<string>(stream);
				current->m_pbr_block.m_metallic.m_texture = fetch_texture(map);
			}
			else if(command == "map_Ke") // emissive texture
			{
				string map = read<string>(stream);
				current->m_pbr_block.m_emissive.m_texture = fetch_texture(map);
				current->m_pbr_block.m_emissive.m_value.m_a = 2.f;
			}
			else if(command == "map_Ns") // specular highlight texture
			{
				string map = read<string>(stream);
				current->m_pbr_block.m_roughness.m_texture = fetch_texture(map);
			}
			else if(command == "map_bump" || command == "bump") // bump texture
			{
				string map = read<string>(stream);
				current->m_pbr_block.m_normal.m_texture = fetch_texture(map);
			}
			else if(command == "map_Pm") // PBR: metallic texture
			{
				string map = read<string>(stream);
				current->m_pbr_block.m_metallic.m_texture = fetch_texture(map);
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

	void ImporterOBJ::import_model(Model& model, const string& path, const string& file, const ModelConfig& config)
	{
		printf("INFO: Importing OBJ model %s\n", model.m_name.c_str());

		Clock clock;
		clock.step();

		model.m_meshes.reserve(1024);

		bool generate_tangents = false;

		std::vector<vec3> vertices;
		std::vector<vec3> normals;
		std::vector<vec2> uvs;
		std::map<string, Material*> materials;
		
		enum VertAttrib
		{
			POSITION,
			TEXCOORD,
			NORMAL
		};

		struct MeshWriter
		{
			MeshWriter(Model& model, const string& name, bool generate_tangents)
				: m_model(model)
				, m_mesh(model.add_mesh(name.c_str(), true))
				, m_generate_tangents(generate_tangents)
			{}

			~MeshWriter()
			{
				if(m_shape.m_vertices.empty() || m_skip)
				{
					m_model.m_meshes.pop_back();
					return;
				}
				m_shape.bake(!m_normals, m_generate_tangents && m_uvs);
				m_mesh.write(PLAIN, to_array(m_shape.m_vertices), to_array(m_shape.m_indices));
				m_model.m_items.emplace_back(ModelItem{ bxidentity(), &m_mesh, -1, Colour::White });
				//printf("INFO: ImporterOBJ imported mesh %s material %s with %u vertices and %u faces\n", m_mesh.m_name.c_str(), m_mesh.m_material->m_name.c_str(), m_shape.m_vertices.size(), m_shape.m_indices.size() / 3);
			}

			inline void face(ShapeVertex* face, size_t a, size_t b, size_t c)
			{
				// bool flip_faces;
				// int i = !flip_faces && i < 2 ? 1 ^ i : i;
				m_shape.vertex() = face[a];
				m_shape.vertex() = face[b];
				m_shape.vertex() = face[c];
			}

			Model& m_model;
			Mesh& m_mesh;
			MeshPacker m_shape;
			bool m_generate_tangents;
			bool m_normals = true;
			bool m_uvs = true;
			int m_smoothing_group = 0;
			bool m_skip = false;
		};

		string filename = path + file + ".obj";
		std::ifstream filestream(filename);

		if(!filestream.good())
		{
			printf("ERROR: could not locate model %s\n", filename.c_str());
			return;
		}

		unique_ptr<MeshWriter> mesh_writer = make_unique<MeshWriter>(model, string(model.m_name), generate_tangents);

		string line;
		string tokens[5];

		while(std::getline(filestream, line))
		{
			if(line.back() == '\r')
				line.pop_back();

			split_string(line, " ", { tokens, 5 });

			const string& command = tokens[0];

			if(command == "o" || command == "g")
			{
				mesh_writer = nullptr;
				mesh_writer = make_unique<MeshWriter>(model, string(model.m_name), generate_tangents);
			}
			if(command == "o")
			{
				const string& name = tokens[1];
				model.m_name = name.c_str();
			}
			else if(command == "g")
			{
				const string& name = tokens[1];
				mesh_writer->m_mesh.m_name = name.c_str();
				//if(vector_has(config.m_filter, name))
				//	mesh_writer->m_skip = true;
			}
			else if(command == "usemtl")
			{
				const string& material = tokens[1];
				mesh_writer->m_mesh.m_material = materials[material];
			}
			else if(command == "s") //smoothing
			{
				const string& value = tokens[1];
				mesh_writer->m_smoothing_group = value == "off" ? 0
																: std::stoi(value);
			}
			else if(command == "v")
			{
				vec3 vert = { std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]) };
				vert = bxmul(config.m_transform, vert);
				vertices.emplace_back(vert);
			}
			else if(command == "vt")
			{
				vec2 uv = { std::stof(tokens[1]), std::stof(tokens[2]) };
				uvs.push_back({ uv.x, 1.f - uv.y });
			}
			else if(command == "vn")
			{
				vec3 norm = { std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]) };
				norm = bxmul(config.m_transform, norm);
				normals.emplace_back(norm);
			}
			else if(command == "f")
			{
				std::array<ShapeVertex, 4> verts;

				size_t num_vertices = tokens[4] == "" ? 3 : 4;
				for(size_t i = 0; i < num_vertices; ++i)
				{
					string ids[3];
					split_string(tokens[i + 1], "/", { ids, 3 });

					int face[3] = { std::stoi(ids[0]), std::stoi(ids[1]), std::stoi(ids[2]) };

					verts[i].m_position = face[POSITION] >= 0 ? vertices[face[POSITION] - 1] : vertices[face[POSITION] + vertices.size()];
					if(face[TEXCOORD] != 0)
						verts[i].m_uv0 = face[TEXCOORD] >= 0 ? uvs[face[TEXCOORD] - 1] : uvs[face[TEXCOORD] + uvs.size()];
					if(face[NORMAL] != 0)
						verts[i].m_normal = face[NORMAL] >= 0 ? normals[face[NORMAL] - 1] : normals[face[NORMAL] + normals.size()];
				}

				mesh_writer->face(verts.data(), 0, 1, 2);

				if(!tokens[4].empty())
					mesh_writer->face(verts.data(), 0, 2, 3);
			}
			else if(command == "mtllib")
			{
				const string& lib_path = tokens[1];
				import_material_library(lib_path, materials);
			}
		}

		printf("INFO: Imported %i vertices in %.2f seconds\n", int(vertices.size()), clock.step());

		model.prepare();
	}
}
//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx.obj;
#else
#include <stl/algorithm.h>
#include <infra/File.h>
#include <infra/ToString.h>
#include <math/Timer.h>
#include <math/Vec.hpp>
#include <geom/Geometry.h>
#include <srlz/Serial.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Prefab.h>
#include <gfx/Node3.h>
#include <gfx/Texture.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-obj/Types.h>
#include <gfx-obj/ImporterObj.h>
#endif

#include <cstdio>

namespace mud
{
	static ImportConfig load_model_config(const string& path, const string& model_name)
	{
		ImportConfig config = {};

		string config_path = file_directory(path) + "/" + model_name + ".cfg";
		if(file_exists(config_path))
			unpack_json_file(Ref(&config), config_path);

		config.m_transform = bxSRT(config.m_scale, config.m_rotation, config.m_position);

		return config;
	}

	ImporterOBJ::ImporterOBJ(GfxSystem& gfx)
		: m_gfx(gfx)
	{
		static auto load_obj_model = [&](Model& model, const string& path)
		{
			ImportConfig config = load_model_config(path, model.m_name);
			this->import_model(model, path, config);
		};

		static auto load_obj_prefab = [&](Prefab& prefab, const string& path)
		{
			ImportConfig config = load_model_config(path, prefab.m_name);
			this->import_prefab(prefab, path, config);
		};

		gfx.add_importer(ModelFormat::obj, *this);
		gfx.models().add_format(".obj", load_obj_model);
		gfx.prefabs().add_format(".obj", load_obj_prefab);
	}

	using MaterialMap = map<string, Material*>;

	void import_material_library(GfxSystem& gfx, const string& path, MaterialMap& material_map)
	{
		auto tof = [](const string& s) { return float(atof(s.c_str())); };
		auto tocol = [&](const string tokens[]) { return Colour{ tof(tokens[1]), tof(tokens[2]), tof(tokens[3]), tof(tokens[4]) }; };

		LocatedFile location = gfx.locate_file("models/" + path);
		if(!location)
			location = gfx.locate_file("materials/" + path);

		string filename = location.path(false);

		if(!file_exists(filename))
			return;

		Material* current = nullptr;

		read_text_file(filename, [&](string line)
		{
			string tokens[5];
			line = replace(line, "\t", "");
			split(line, " ", tokens);

			const string& command = tokens[0];

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
				if(gfx.locate_file("textures/" + path))
					return gfx.textures().file(path);
				else
					return nullptr;
			};

			if(command == "newmtl")
			{
				string name = tokens[1];
				current = &gfx.fetch_material(name, "pbr/pbr");
				material_map[name] = current;
			}
			else if(command == "Ka")
			{
				// nothing
			}
			else if(command == "Kd")
			{
				Colour albedo = tocol(tokens);
				current->m_pbr.m_albedo.m_value = albedo;
			}
			else if(command == "Ks")
			{
				Colour specular = tocol(tokens);
				current->m_pbr.m_metallic.m_value = max(specular.r, max(specular.g, specular.b));
			}
			else if(command == "Ke")
			{
				Colour emissive = tocol(tokens);
				current->m_lit.m_emissive.m_value = emissive;
				current->m_lit.m_emissive.m_value.a = length(to_vec3(emissive));
			}
			else if(command == "Ns")
			{
				float specular = tof(tokens[1]);
				current->m_pbr.m_metallic.m_value = (1000.f - specular) / 1000.f;
			}
			else if(command == "d")
			{
				float d = tof(tokens[1]);
				current->m_pbr.m_albedo.m_value.a = d;
			}
			else if(command == "Tr")
			{
				float tr = tof(tokens[1]);
				current->m_pbr.m_albedo.m_value.a = 1.f - tr;
			}
			else if(command == "Pr")
			{
				float roughness = tof(tokens[1]);
				current->m_pbr.m_roughness.m_value = roughness;
			}
			else if(command == "Pm")
			{
				float metallic = tof(tokens[1]);
				current->m_pbr.m_metallic.m_value = metallic;
			}
			else if(command.substr(0, 3) == "map")
			{
				string map = tokens[1];
				if(command == "map_Ka ") // ambient texture
				{
					// nothing
				}
				else if(command == "map_Kd") // diffuse texture
				{
					current->m_pbr.m_albedo = fetch_texture(map);
				}
				else if(command == "map_Ks") // specular texture
				{
					//current->m_pbr.m_metallic.m_value = 1.f;
					current->m_pbr.m_metallic = fetch_texture(map);
				}
				else if(command == "map_Ke") // emissive texture
				{
					current->m_lit.m_emissive = fetch_texture(map);
					current->m_lit.m_emissive.m_value.a = 2.f;
				}
				else if(command == "map_Ns") // specular highlight texture
				{
					current->m_pbr.m_roughness = fetch_texture(map);
				}
				else if(command == "map_bump" || command == "bump") // bump texture
				{
					current->m_lit.m_normal = fetch_texture(map);
				}
				else if(command == "map_Pr") // PBR: roughness texture
				{
					current->m_pbr.m_roughness = fetch_texture(map);
				}
				else if(command == "map_Pm") // PBR: metallic texture
				{
					//current->m_pbr.m_metallic.m_value = 1.f;
					current->m_pbr.m_metallic = fetch_texture(map);
				}
			}

			// "map_d"  alpha texture
			// "disp"   displacement texture
			// "refl"   reflection map
			// "map_Pr" PBR: roughness texture
			// "map_Pm" PBR: metallic texture
			// "map_Ps" PBR: sheen texture
			// "norm"   PBR: normal map texture

			return true;
		});
	}

	void ImporterOBJ::import(Import& scene, const string& path, const ImportConfig& config)
	{
		auto tof = [](const string& s) { return float(atof(s.c_str())); };
		auto toi = [](const string& s) { return atoi(s.c_str()); };

		printf("INFO: gltf - loading scene %s\n", scene.m_file.c_str());

		Clock clock;
		clock.step();

		bool generate_tangents = true;
		bool as_model = scene.m_models.size() > 0;

		struct Geometry
		{
			vector<vec3> vertices;
			vector<vec3> normals;
			vector<vec2> uvs;
			map<string, Material*> materials;
		} g;

		enum VertAttrib
		{
			POSITION,
			TEXCOORD,
			NORMAL
		};

		struct MeshWriter
		{
			MeshWriter(const ImportConfig& config, Import& import, bool as_model, bool generate_tangents)
				: m_config(config)
				, m_import(import)
				, m_name(import.m_name)
				, m_as_model(as_model)
				, m_generate_tangents(generate_tangents)
			{}

			void next()
			{
				if(m_shape.vertex_count() == 0 || m_skip)
					return;

				Model& model = m_as_model ? *m_import.m_models[0] : m_import.m_gfx.models().create(m_name);
				Mesh& mesh = model.add_mesh(m_name, true);

				m_shape.bake(!m_normals, m_generate_tangents && m_uvs);
				mesh.write(m_shape, m_config.m_optimize_geometry);
				mesh.m_material = m_material;
				m_import.m_meshes.push_back(&mesh);

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
			bool m_as_model;
			bool m_generate_tangents;
			bool m_normals = true;
			bool m_uvs = true;
			int m_smoothing_group = 0;
			bool m_skip = false;
		};

		string filename = path + ".obj";

		if(!file_exists(filename))
		{
			printf("ERROR: could not locate model %s\n", filename.c_str());
			return;
		}

		MeshWriter mesh_writer = { config, scene, as_model, generate_tangents };

		static string tokens[5];
		static string faceids[3];

		read_text_file(filename, [&](const string& line)
		{
			for(size_t i = 0; i < 5; ++i)
				tokens[i].clear();

			split(line, " ", tokens);

			const string& command = tokens[0];

			if(command == "o" || command == "g")
			{
				mesh_writer.next();
			}
			if(command == "o")
			{
				const string& name = tokens[1];
				scene.m_name = name;
			}
			else if(command == "g")
			{
				const string& name = tokens[1];
				mesh_writer.m_name = name;
				if(config.filter_element(name))
					mesh_writer.m_skip = true;
			}
			else if(command == "usemtl")
			{
				const string& material = tokens[1];
				mesh_writer.m_material = g.materials[material];
				if(config.filter_material(material))
					mesh_writer.m_skip = true;
			}
			else if(command == "s") //smoothing
			{
				const string& value = tokens[1];
				mesh_writer.m_smoothing_group = value == "off" ? 0
																: toi(value);
			}
			else if(command == "v")
			{
				vec3 vert = { tof(tokens[1]), tof(tokens[2]), tof(tokens[3]) };
				vert = mulp(config.m_transform, vert);
				g.vertices.push_back(vert);
			}
			else if(command == "vt")
			{
				vec2 uv = { tof(tokens[1]), tof(tokens[2]) };
				g.uvs.push_back({ uv.x, 1.f - uv.y });
			}
			else if(command == "vn")
			{
				vec3 norm = { tof(tokens[1]), tof(tokens[2]), tof(tokens[3]) };
				norm = muln(config.m_transform, norm);
				g.normals.push_back(norm);
			}
			else if(command == "f")
			{
				ShapeVertex verts[4];

				size_t num_vertices = tokens[4] == "" ? 3 : 4;
				for(size_t i = 0; i < num_vertices; ++i)
				{
					split(tokens[i + 1], "/", faceids);

					int face[3] = { toi(faceids[0]), toi(faceids[1]), toi(faceids[2]) };

					verts[i].m_position = g.vertices[face[POSITION] >= 0 ? face[POSITION] - 1 : face[POSITION] + g.vertices.size()];
					if(face[TEXCOORD] != 0)
						verts[i].m_uv0 = g.uvs[face[TEXCOORD] >= 0 ? face[TEXCOORD] - 1 : face[TEXCOORD] + g.uvs.size()];
					if(face[NORMAL] != 0)
						verts[i].m_normal = g.normals[face[NORMAL] >= 0 ? face[NORMAL] - 1 : face[NORMAL] + g.normals.size()];
				}

				mesh_writer.face(verts, 0, 1, 2);

				if(!tokens[4].empty())
					mesh_writer.face(verts, 0, 2, 3);
			}
			else if(command == "mtllib")
			{
				const string& lib_path = tokens[1];
				import_material_library(m_gfx, lib_path, g.materials);
			}

			return true;
		});

		mesh_writer.next();

		printf("INFO: obj - imported %i vertices in %.2f seconds\n", int(g.vertices.size()), clock.step());
	}

	void ImporterOBJ::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx, filepath, config };
		state.m_models.push_back(&model);

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
		Import state = { m_gfx, filepath, config };

		this->import(state, filepath, config);

		import_to_prefab(m_gfx, prefab, state, config.m_flags);
	}

	void ImporterOBJ::repack(const string& filepath, const ImportConfig& config)
	{
		UNUSED(filepath); UNUSED(config);
		printf("WARNING: obj - repack for this format not supported\n");
	}
}

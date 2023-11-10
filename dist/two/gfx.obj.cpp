#include <two/gfx.h>
#include <two/gfx.obj.h>
#include <two/geom.h>
#include <two/srlz.h>
#include <two/math.h>
#include <two/infra.h>
#include <two/type.h>


#ifdef TWO_MODULES
module two.gfx-obj;
#else
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterOBJ>() { static Type ty("ImporterOBJ", sizeof(two::ImporterOBJ)); return ty; }
    template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterPLY>() { static Type ty("ImporterPLY", sizeof(two::ImporterPLY)); return ty; }
}


#ifdef TWO_MODULES
module two.gfx.obj;
#else
#include <stl/algorithm.h>
#endif

#include <cstdio>

#define DEBUG_MESHES 0

namespace two
{
	static ImportConfig load_model_config(const string& path, const string& model_name, const ImportConfig& input)
	{
		ImportConfig config = input;

		string config_path = file_directory(path) + "/" + model_name + ".cfg";
		if(file_exists(config_path))
			unpack_json_file(Ref(&config), config_path);

		config.m_transform = bxSRT(config.m_scale, config.m_rotation, config.m_position);

		return config;
	}

	ImporterOBJ::ImporterOBJ(GfxSystem& gfx)
		: m_gfx(gfx)
	{
		static auto load_obj_model = [&](Model& model, const string& path, const ImportConfig& inconfig)
		{
			ImportConfig config = load_model_config(path, model.m_name, inconfig);
			this->import_model(model, path, config);
		};

		static auto load_obj_prefab = [&](Prefab& prefab, const string& path, const ImportConfig& inconfig)
		{
			ImportConfig config = load_model_config(path, prefab.m_name, inconfig);
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

		printf("[info] obj - loading scene %s\n", scene.m_file.c_str());

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

				m_import.m_nodes.push_back(bxidentity());
				m_import.m_items.push_back({ 0, &model, -1 });

#if DEBUG_MESHES
				printf("[info] obj - imported mesh %s with %u vertices and %u faces\n", 
					   mesh.m_name.c_str(), m_shape.m_positions.size(), m_shape.m_indices.size() / 3);
#endif

				m_shape = {};
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
			printf("[ERROR] could not locate model %s\n", filename.c_str());
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

		printf("[info] obj - imported %i vertices in %.2f seconds\n", int(g.vertices.size()), clock.step());
	}

	void ImporterOBJ::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx, filepath, config };
		state.m_models.push_back(&model);

		this->import(state, filepath, config);
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
		printf("[warning] obj - repack for this format not supported\n");
	}
}


#ifdef TWO_MODULES
module two.gfx.obj;
#else
#include <stl/algorithm.h>
#endif

#include <stl/vector.hpp>

#include <cstdio>

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

	ImporterPLY::ImporterPLY(GfxSystem& gfx)
		: m_gfx(gfx)
	{
		static auto load_model = [&](Model& model, const string& path, const ImportConfig& inconfig)
		{
			ImportConfig config = load_model_config(path, model.m_name, inconfig);
			this->import_model(model, path, config);
		};

		static auto load_prefab = [&](Prefab& prefab, const string& path, const ImportConfig& inconfig)
		{
			ImportConfig config = load_model_config(path, prefab.m_name, inconfig);
			this->import_prefab(prefab, path, config);
		};

		gfx.add_importer(ModelFormat::ply, *this);
		gfx.models().add_format(".ply", load_model);
		gfx.prefabs().add_format(".ply", load_prefab);
	}
	
	struct Property
	{
		string type;
		string name;
		string countType;
		string itemType;
	};

	struct Element
	{
		string name;
		size_t count;
		vector<Property> properties;
	};

	struct Header
	{
		string format;
		string version;
		vector<string> comments;
		vector<Element> elements;
		bool has_normals = false;
		bool has_uvs = false;
		bool has_colours = false;
		size_t length;
	};

	Header read_header(const string& filename)
	{
		Header header;
		string text = read_text_file(filename);
		string end = "end_header";
		header.length = text.find(end) + end.size() + 1;

		Element element;
		bool haselement = false;

		read_text_file(filename, [&](const string& line)
		{
			//printf("line %s\n", line.c_str());
			if(line == "end_header")
				return false;

			if(line == "") return true;

			vector<string> tokens = split(line, " ");
			string command = shift(tokens);

			if(command == "format")
			{
				header.format = tokens[0];
				header.version = tokens[1];
			}
			else if(command == "comment")
			{
				header.comments.push_back(join(tokens, " "));
			}
			else if(command == "element")
			{
				if(haselement)
					header.elements.push_back(element);

				element = {};
				element.name = tokens[0];
				element.count = to_value<size_t>(tokens[1]);
				element.properties = {};

				haselement = true;
			}
			else if(command == "property")
			{
				Property property = { tokens[0] };

				if(property.type == "list")
				{
					property.name = tokens[3];
					property.countType = tokens[1];
					property.itemType = tokens[2];
				}
				else
				{
					property.name = tokens[1];
				}

				if(property.name == "nx")  header.has_normals = true;
				if(property.name == "s")   header.has_uvs = true;
				if(property.name == "red") header.has_colours = true;

				//if(mapping.find(property.name) != mapping.end())
				//	property.name = mapping[property.name];

				element.properties.push_back(property);
			}
			else
			{
				//console.log("unhandled", lineType, lineValues);
			}

			return true;
		});

		if(haselement)
			header.elements.push_back(element);

		return header;
	}

	struct Buffer
	{
		vector<uint32_t> indices;
		vector<vec3> vertices;
		vector<vec3> normals;
		vector<vec2> uvs;
		//vector<> faceVertexUvs;
		vector<Colour> colors;
	};

	void pack(Buffer buffer, MeshPacker& geometry)
	{
		geometry.m_indices = buffer.indices;
		geometry.m_positions = buffer.vertices;
		geometry.m_normals = buffer.normals;
		geometry.m_uv0s = buffer.uvs;
		geometry.m_colours = buffer.colors;

		//if(buffer.faceVertexUvs.length > 0) {
		//	geometry = geometry.toNonIndexed();
		//	geometry.addAttribute("uv", new THREE.Float32BufferAttribute(buffer.faceVertexUvs, 2));
		//}
	}

	void vertex(const Header& header, Buffer& buffer, const Element& element, span<double> data)
	{
		// @todo make this faster... this is ridiculous
		vec3 position;
		vec3 normal;
		vec2 uv;
		vec3 colour;

		size_t i = 0;
		for(const Property& prop : element.properties)
		{
			if(prop.name == "x") position.x = float(data[i]);
			if(prop.name == "y") position.y = float(data[i]);
			if(prop.name == "z") position.z = float(data[i]);

			if(header.has_normals)
			{
				if(prop.name == "nx") normal.x = float(data[i]);
				if(prop.name == "ny") normal.y = float(data[i]);
				if(prop.name == "nz") normal.z = float(data[i]);
			}

			if(header.has_uvs)
			{
				if(prop.name == "s") uv.x = float(data[i]);
				if(prop.name == "t") uv.y = float(data[i]);
			}

			if(header.has_colours)
			{
				if(prop.name == "red")   colour.r = float(data[i]) / 255.f;
				if(prop.name == "green") colour.g = float(data[i]) / 255.f;
				if(prop.name == "blue")  colour.b = float(data[i]) / 255.f;
			}

			i++;
		}

		buffer.vertices.push_back(position);
		if(header.has_normals) buffer.normals.push_back(normal);
		if(header.has_uvs)     buffer.uvs.push_back(uv);
		if(header.has_colours) buffer.colors.push_back(to_colour(colour));
	}

	void face(const Header& header, Buffer& buffer, const Element& element, span<double> data)
	{
		size_t i = 0;
		for(const Property& prop : element.properties)
		{
			if(prop.name == "texcoord")
			{
				//if(texcoord && texcoord.length == 6) {
				//	buffer.faceVertexUvs.push(texcoord[0], texcoord[1]);
				//	buffer.faceVertexUvs.push(texcoord[2], texcoord[3]);
				//	buffer.faceVertexUvs.push(texcoord[4], texcoord[5]);
				//}
			}

			if(prop.name == "vertex_indices" || prop.name == "vertex_index")
			{
				const size_t count = size_t(data[i++]);

				const uint32_t a = uint32_t(data[i++]);
				const uint32_t b = uint32_t(data[i++]);
				const uint32_t c = uint32_t(data[i++]);
				
				if(count == 3)
				{
					extend(buffer.indices, { a, b, c });
				}
				else if(count == 4)
				{
					uint32_t d = uint32_t(data[i++]);

					extend(buffer.indices, { a, b, d });
					extend(buffer.indices, { b, c, d });
				}
			}
		}
	}

	void read_text(const Header& header, const string& filename, MeshPacker& geometry)
	{
		// PLY ascii format specification, as per http://en.wikipedia.org/wiki/PLY_(file_format)

		Buffer buffer;

		const size_t num_elements = header.elements.size();
		Element element = header.elements[0];
		size_t section = 0;
		size_t count = 0;
		bool start = false;

		read_text_file(filename, [&](const string& line)
		{
			if(line == "end_header")
			{
				start = true;
				return true;
			}

			if(line == "" || !start)
				return true;

			if(count >= element.count)
			{
				assert(header.elements.size() > section);
				element = header.elements[++section];
				count = 0;
			}

			const vector<string> tokens = split(line, " ");
			size_t token = 0;

			vector<double> values;
			for(Property& prop : element.properties)
			{
				if(prop.type == "list")
				{
					size_t n = to_value<size_t>(tokens[token++]);
					values.push_back(double(n));
					for(size_t j = 0; j < n; j++)
						values.push_back(to_value<double>(tokens[token++]));
				}
				else
				{
					values.push_back(to_value<double>(tokens[token++]));
				}
			}

			if(element.name == "vertex")
				vertex(header, buffer, element, values);
			else if(element.name == "face")
				face(header, buffer, element, values);

			count++;
			return true;
		});

		pack(buffer, geometry);
	}

	void read_binary(const Header& header, vector<uint8_t> data, MeshPacker& geometry)
	{
		bool little_endian = (header.format == "binary_little_endian");
		uchar* cursor = data.data() + header.length;

		auto read = [](const string& type, uchar*& data) -> double
		{
			// @todo handle little endian
			// corespondences for non-specific length types here match rply:
			if(type == "int8"    || type == "char")   return double(*((int8_t*&)data)++);
			if(type == "uint8"   || type == "uchar")  return double(*((uint8_t*&)data)++);
			if(type == "int16"   || type == "short")  return double(*((int16_t*&)data)++);
			if(type == "uint16"  || type == "ushort") return double(*((uint16_t*&)data)++);
			if(type == "int32"   || type == "int")    return double(*((int32_t*&)data)++);
			if(type == "uint32"  || type == "uint")   return double(*((uint32_t*&)data)++);
			if(type == "float32" || type == "float")  return double(*((float*&)data)++);
			if(type == "float64" || type == "double") return double(*((double*&)data)++);
		};

		Buffer buffer;

		for(const Element& element : header.elements)
		{
			for(size_t i = 0; i < element.count; i++)
			{
				vector<double> values;

				for(const Property& prop : element.properties)
				{
					if(prop.type == "list")
					{
						size_t n = size_t(read(prop.countType, cursor));
						values.push_back(double(n));
						for(size_t j = 0; j < n; j++)
							values.push_back(read(prop.itemType, cursor));
					}
					else
					{
						values.push_back(read(prop.type, cursor));
					}
				}

				if(element.name == "vertex")
					vertex(header, buffer, element, values);
				else if(element.name == "face")
					face(header, buffer, element, values);
			}
		}

		pack(buffer, geometry);
	}

	void ImporterPLY::import(Import& scene, const string& path, const ImportConfig& config)
	{
		printf("[info] gltf - loading scene %s\n", scene.m_file.c_str());

		bool as_model = scene.m_models.size() > 0;
		Model& model = as_model
			? *scene.m_models[0]
			: m_gfx.models().create(scene.m_name);

		Mesh& mesh = model.add_mesh(scene.m_name, true);

		MeshPacker geometry;

		const string filename = path + ".ply";

		Header header = read_header(filename);
		if(header.format == "ascii")
			read_text(header, filename, geometry);
		else
			read_binary(header, read_binary_file(filename), geometry);

		geometry.bake(config.m_need_normals, false);
		mesh.write(geometry, config.m_optimize_geometry);
		scene.m_meshes.push_back(&mesh);

		model.add_item(mesh, bxidentity());
		model.prepare();
		
		if(!as_model)
		{
			scene.m_models.push_back(&model);
			scene.m_nodes.push_back(bxidentity());;
			scene.m_items.push_back({ 0, &model, -1 });
		}
	}

	void ImporterPLY::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx, filepath, config };
		state.m_name = file_name(filepath);
		state.m_models.push_back(&model);

		this->import(state, filepath, config);
	}

	void ImporterPLY::import_prefab(Prefab& prefab, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx, filepath, config };

		this->import(state, filepath, config);

		import_to_prefab(m_gfx, prefab, state, config.m_flags);
	}

	void ImporterPLY::repack(const string& filepath, const ImportConfig& config)
	{
		UNUSED(filepath); UNUSED(config);
		printf("[warning] ply - repack for this format not supported\n");
	}
}

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
#include <infra/ToValue.h>
#include <math/Vec.hpp>
#include <geom/Geometry.h>
#include <srlz/Serial.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Prefab.h>
#include <gfx/Node3.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-obj/Types.h>
#include <gfx-obj/ImporterPly.h>
#endif

#include <stl/vector.hpp>

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

	ImporterPLY::ImporterPLY(GfxSystem& gfx)
		: m_gfx(gfx)
	{
		static auto load_model = [&](Model& model, const string& path)
		{
			ImportConfig config = load_model_config(path, model.m_name);
			this->import_model(model, path, config);
		};

		static auto load_prefab = [&](Prefab& prefab, const string& path)
		{
			ImportConfig config = load_model_config(path, prefab.m_name);
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
				element = header.elements[section++];

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
		printf("INFO: gltf - loading scene %s\n", scene.m_file.c_str());

		Model& model = scene.m_models.size() > 0
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
		scene.m_models.push_back(&model);

		scene.m_items.push_back({ bxidentity(), &model, -1 });
	}

	void ImporterPLY::import_model(Model& model, const string& filepath, const ImportConfig& config)
	{
		Import state = { m_gfx, filepath, config };
		state.m_name = file_name(filepath);
		state.m_models.push_back(&model);

		this->import(state, filepath, config);

		for(const Import::Item& item : state.m_items)
		{
			for(const ModelItem& model_item : item.model->m_items)
				model.add_item(*model_item.m_mesh, item.transform, item.skin);
		}

		model.prepare();
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
		printf("WARNING: ply - repack for this format not supported\n");
	}
}

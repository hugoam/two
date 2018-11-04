//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.srlz;
#else
#include <json11.hpp>

#include <infra/File.h>
#include <type/Vector.h>
#include <refl/System.h>
#include <refl/Convert.h>
#include <refl/Sequence.h>
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <refl/Injector.h>
#include <refl/Member.h>
#include <refl/Method.h>
#include <srlz/Types.h>
#include <srlz/Serial.h>
#endif

//#define MUD_DEBUG_SERIAL
#define NO_HUMAN_READABLE
#define NO_PACK_DEFAULT

namespace mud
{
	void parse_json_file(const string& path, json& data)
	{
		if(!std::ifstream(path).good())
		{
			printf("ERROR: couldn't open file %s\n", path.c_str());
			return;
		}

		string text = read_text_file(path);
		string errors;
		data = json::parse(text, errors);
	}

	json parse_json_file(const string& path)
	{
		json data;
		parse_json_file(path, data);
		return data;
	}

#ifndef MUD_CPP_20
	void dump_json_file(const string& path, const json& value)
	{
		std::ofstream file = std::ofstream(path);
		if(!file.good())
			printf("ERROR: couldn't open file %s\n", path.c_str());
		string content = value.dump();
		file << content;
	}
#endif

	void visit_json(json& json_value, const JsonVisitor& visitor)
	{
		visitor(json_value);

		if(json_value.is_object())
			for(auto& key_value : json_value.object_items())
				visit_json(const_cast<json&>(key_value.second), visitor);
		else if(json_value.is_array())
			for(const json& value : json_value.array_items())
				visit_json(const_cast<json&>(value), visitor);
	}

	FromJson::FromJson()
	{
		dispatch_branch<int>    (*this, [](int&    value, Ref&, const json& json_value) { value = json_value.int_value(); });
		dispatch_branch<ushort> (*this, [](ushort& value, Ref&, const json& json_value) { value = ushort(json_value.int_value()); });
		dispatch_branch<uint>   (*this, [](uint&   value, Ref&, const json& json_value) { value = uint(json_value.int_value()); });
		dispatch_branch<ulong>  (*this, [](ulong&  value, Ref&, const json& json_value) { value = ulong(json_value.number_value()); });
		dispatch_branch<ulong2> (*this, [](ulong2& value, Ref&, const json& json_value) { value = ulong2(json_value.number_value()); });
		dispatch_branch<float>  (*this, [](float&  value, Ref&, const json& json_value) { value = float(json_value.number_value()); });
		dispatch_branch<double> (*this, [](double& value, Ref&, const json& json_value) { value = json_value.number_value(); });
		// cstring can't be deserialized I believe, or we need to memoize them ?
		dispatch_branch<string>(*this, [](string& value, Ref&, const json& json_value) { value = json_value.string_value(); });
		dispatch_branch<bool>(*this, [](bool& value, Ref&, const json& json_value) { value = json_value.bool_value(); });

		dispatch_branch<std::vector<Var>>(*this, [](std::vector<Var>& values, Ref&, const json& json_value)
		{
			for(const json& value : json_value.array_items())
				values.push_back(unpack_typed(value));
		});

		dispatch_branch<Call>(*this, [](Call& call, Ref&, const json& json_value)
		{
			call.m_callable = System::instance().find_function(json_value["callable"].string_value().c_str());
			call.m_arguments = unpackt<std::vector<Var>>(json_value["arguments"]);
		});
	}

	ToJson::ToJson()
	{
		dispatch_branch<int>     (*this, [](int&     value, json& json_value) { json_value = json(value); });
		dispatch_branch<uint>    (*this, [](uint&    value, json& json_value) { json_value = json(int(value)); });
		dispatch_branch<ushort>  (*this, [](ushort&  value, json& json_value) { json_value = json(int(value)); });
		dispatch_branch<ulong>   (*this, [](ulong&   value, json& json_value) { json_value = json(double(value)); });
		dispatch_branch<ulong2>  (*this, [](ulong2&  value, json& json_value) { json_value = json(double(value)); });
		dispatch_branch<float>   (*this, [](float&   value, json& json_value) { json_value = value; });
		dispatch_branch<double>  (*this, [](double&  value, json& json_value) { json_value = value; });
		dispatch_branch<cstring> (*this, [](cstring  value, json& json_value) { json_value = string(value); });
		dispatch_branch<string>  (*this, [](string&  value, json& json_value) { json_value = value; });
		dispatch_branch<bool>    (*this, [](bool&    value, json& json_value) { json_value = value; });

		dispatch_branch<Type>(*this, [](Type& type, json& json_value) { json_value = type.m_name; });

		dispatch_branch<std::vector<Var>>(*this, [](std::vector<Var>& values, json& json_value)
		{
			std::vector<json> json_values = std::vector<json>(values.size());
			for (size_t i = 0; i < values.size(); ++i)
				pack_typed(values[i], json_values[i]);
			json_value = json_values;
		});

		dispatch_branch<Call>(*this, [](Call& call, json& json_value)
		{
			std::map<std::string, json> json_values;
			json_values["callable"] = string(call.m_callable->m_name);
			pack(Ref(&call.m_arguments), json_values["arguments"]);
			json_value = json_values;
		});
	}

	inline void enum_set_value(Ref value, size_t enum_value)
	{
		memcpy(value.m_value, &enum_value, meta(value).m_size);
	}

	Var unpack(Type& type, const json& json_value)
	{
		static FromJson unpacker;
		return unpack(unpacker, type, json_value);
	}

	void unpack(Var& value, const json& json_value)
	{
		static FromJson unpacker;
		unpack(unpacker, value, json_value);
	}

	void unpack(Ref object, const json& json_value)
	{
		static FromJson unpacker;
		Var value = object;
		unpack(unpacker, value, json_value);
	}
	
	Var unpack(FromJson& unpacker, Type& type, const json& json_value, bool typed)
	{
		Var result = meta(type).m_empty_var;
		unpack(unpacker, result, json_value, typed);
		return result;
	}

	void unpack(FromJson& unpacker, Var& value, const json& json_value, bool typed)
	{
		if(json_value.is_null())
			return;

		// @note: we MUST take a Var& as parameter of this function for this specific case
		// -> polymorphic objects must be created by value since we don't know in advance the actual type we are loading
		if(g_class[type(value).m_id] && cls(value).m_type_member && !typed) // @kludge this parameter is only there to tell us we were called from the typed variant of this function, couldn't think of a better design at this time of the day
		{
			value = unpack_typed(unpacker, json_value);
			return;
		}

		if(unpacker.check(value))
		{
			unpacker.dispatch(value, value.m_ref, json_value);
			return;
		}
		else if(is_enum(type(value)) && json_value.is_number()) // is_number_integer
		{
			enum_set_value(value, json_value.int_value());
			return;
		}
		else if(g_convert[type(value).m_id] && json_value.is_string())
		{
			convert(type(value)).m_from_string(json_value.string_value(), value);
			return;
		}
		else if(is_sequence(type(value)))
		{
			for(const json& json_element : json_value.array_items())
			{
				Var element = unpack(unpacker, *cls(value).m_content, json_element);
				add_sequence(value, element);
			}
			return;
		}

		size_t size = json_value.is_array() ? json_value.array_items().size() : json_value.object_items().size();

		if(!g_class[type(value).m_id])
		{
			printf("WARNING: unpack - type %s is not a class\n", type(value).m_name);
			return;
		}

		const Class& cls = mud::cls(value);
		const Constructor* constructor = cls.constructor(size);

		if(!constructor)
		{
			auto unpack_member = [&](const Member& member, const json& member_value)
			{
#ifdef MUD_DEBUG_SERIAL
				printf("DEBUG: unpacking member %s :: %s\n", type(value).m_name, member.m_name);
#endif
				member.set(value, unpack(unpacker, *member.m_type, member_value));
			};

			if(json_value.is_object())
			{
				for(const Member& member : cls.m_members)
					if(!json_value[member.m_name].is_null())
					{
						unpack_member(member, json_value[member.m_name]);
					}
			}
			else if(json_value.is_array())
			{
				for(size_t index = 0; index < size; ++index)
				{
					unpack_member(cls.m_members[index], json_value[index]);
				}
			}
		}
		else
		{
			Call construct = { *constructor };

			for(size_t index = 0; index < size; ++index)
			{
#ifdef MUD_DEBUG_SERIAL
				printf("DEBUG: unpacking member %s :: %s\n", type(value).m_name, construct.m_callable->m_params[index + 1].m_name);
#endif
				const json& json_field = json_value.is_array() ? json_value[index]
															   : json_value[construct.m_callable->m_params[index + 1].m_name];

				unpack(unpacker, construct.m_arguments[index + 1], json_field);
			}

			construct(value);
		}
	}

	Var unpack_typed(FromJson& unpacker, const json& json_typed_value)
	{
		string type_name = json_typed_value["type"].string_value();
		json json_value = json_typed_value["value"];
		return unpack(unpacker, *System::instance().find_type(type_name.c_str()), json_value, true);
	}

	Var unpack_typed(const json& json_value)
	{
		static FromJson unpacker;
		return unpack_typed(unpacker, json_value);
	}

	void pack(ToJson& packer, const Var& value, json& json_value, bool typed)
	{
		if(packer.check(value.m_ref))
		{
			packer.dispatch(value.m_ref, json_value);
		}
		else if(is_base_type(type(value)))
		{
			json_value = to_string(value);
		}
		else if(is_enum(type(value)))
		{
#ifdef NO_HUMAN_READABLE
			json_value = int(enu(value).value(value));
#else
			json_value = to_string(value);
#endif
		}
		else if(is_sequence(type(value)))
		{
			size_t i = 0;
			std::vector<json> json_values = std::vector<json>(sequence_size(value.m_ref));
			iterate_sequence(value.m_ref, [&](Ref element) {
				pack(packer, element, json_values[i++]);
			});
			json_value = json_values;
		}
		else if(is_object(type(value)) || is_struct(type(value)))
		{
			if(value.null())
				json_value = nullptr;
			else if(cls(value).m_type_member && !typed)
				pack_typed(packer, value, json_value);
			else if(is_array(type(value)))
			{
				std::vector<json> json_members;
				json_members.resize(cls(value).m_members.size());

				for(Member& member : cls(value).m_members)
					if(&member != cls(value).m_type_member)
					{
						Var member_val = member.get(value.m_ref);
						pack(packer, member_val, json_members[member.m_index]);
					}

				json_value = json_members;
			}
			else
			{
				std::map<std::string, json> json_members;

				for(Member& member : cls(value).m_members)
					if(&member != cls(value).m_type_member)
					{
						Var member_val = member.get(value.m_ref);
#ifdef NO_PACK_DEFAULT
						if(memcmp(member_val.m_ref.m_value, member.m_default_value.m_ref.m_value, meta(member_val).m_size) == 0)
							continue;
#endif
						pack(packer, member_val, json_members[member.m_name]);
					}

				json_value = json_members;
			}
		}
	}

	void pack(const Var& value, json& json_value)
	{
		static ToJson packer;
		pack(packer, value, json_value);
	}

	json pack(const Var& value)
	{
		json json_value;
		pack(value, json_value);
		return json_value;
	}

	void pack_typed(ToJson& packer, const Var& value, json& json_value)
	{
		std::map<std::string, json> json_values;
		json_values["type"] = type(value).m_name;
		pack(packer, value, json_values["value"], true);
		json_value = json_values;
	}

	void pack_typed(const Var& value, json& json_value)
	{
		static ToJson packer;
		pack_typed(packer, value, json_value);
	}

	string pack_json(const Var& value)
	{
		json json_value;
		pack(value, json_value);
		return json_value.dump();
	}

	void pack_json_file(const Var& value, const string& path)
	{
		json json_value;
		pack(value, json_value);
		dump_json_file(path, json_value);
	}

	void pack_json_file(ToJson& packer, const Var& value, const string& path)
	{
		json json_value;
		pack(packer, value, json_value);
		dump_json_file(path, json_value);
	}

	void unpack_json_file(Ref value, const string& path)
	{
		json json_value;
		parse_json_file(path, json_value); // @kludge: fix extensions assumed in loaders (gltf, obj, etc...)
		unpack(value, json_value);
	}
}

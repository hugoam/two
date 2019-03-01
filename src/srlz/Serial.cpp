//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <map>
#include <cstring>
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
#include <srlz/Serial.hpp>
#endif

#define MUD_DEBUG_SERIAL 0
#define NO_HUMAN_READABLE
#define NO_PACK_DEFAULT

namespace mud
{
	void parse_json_file(const string& path, json& data)
	{
		if(!file_exists(path))
		{
			printf("ERROR: couldn't open file %s\n", path.c_str());
			return;
		}

		string text = read_text_file(path);
		std::string errors;
		data = json::parse(text.c_str(), errors);
	}

	json parse_json_file(const string& path)
	{
		json data;
		parse_json_file(path, data);
		return data;
	}

	void dump_json_file(const string& path, const json& value)
	{
		if(!file_exists(path))
			printf("ERROR: couldn't open file %s\n", path.c_str());
		std::string text = value.dump();
		write_file(path, string(text.data(), text.data() + text.size()));
	}

#if 0
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
#endif

	FromJson::FromJson()
	{
		dispatch_branch<int>    (*this, +[](int&    value, const json& json_value) { value = json_value.int_value(); });
		dispatch_branch<ushort> (*this, +[](ushort& value, const json& json_value) { value = ushort(json_value.int_value()); });
		dispatch_branch<uint>   (*this, +[](uint&   value, const json& json_value) { value = uint(json_value.int_value()); });
		dispatch_branch<ulong>  (*this, +[](ulong&  value, const json& json_value) { value = ulong(json_value.number_value()); });
		dispatch_branch<ullong> (*this, +[](ullong& value, const json& json_value) { value = ullong(json_value.number_value()); });
		dispatch_branch<float>  (*this, +[](float&  value, const json& json_value) { value = float(json_value.number_value()); });
		dispatch_branch<double> (*this, +[](double& value, const json& json_value) { value = json_value.number_value(); });
		// cstring can't be deserialized I believe, or we need to memoize them ?
		dispatch_branch<string> (*this, +[](string& value, const json& json_value) { value = json_value.string_value().c_str(); });
		dispatch_branch<bool>   (*this, +[](bool& value,   const json& json_value) { value = json_value.bool_value(); });

		dispatch_branch<vector<Var>>(*this, +[](vector<Var>& values, const json& json_value)
		{
			for(const json& value : json_value.array_items())
				values.push_back(unpack_typed(value));
		});

		dispatch_branch<Call>(*this, +[](Call& call, const json& json_value)
		{
			call.m_callable = System::instance().find_function(json_value["callable"].string_value().c_str());
			call.m_args = unpackt<vector<Var>>(json_value["arguments"]);
		});
	}

	ToJson::ToJson()
	{
		dispatch_branch<int>     (*this, +[](int&     value, json& json_value) { json_value = json(value); });
		dispatch_branch<uint>    (*this, +[](uint&    value, json& json_value) { json_value = json(int(value)); });
		dispatch_branch<ushort>  (*this, +[](ushort&  value, json& json_value) { json_value = json(int(value)); });
		dispatch_branch<ulong>   (*this, +[](ulong&   value, json& json_value) { json_value = json(double(value)); });
		dispatch_branch<ullong>  (*this, +[](ullong&  value, json& json_value) { json_value = json(double(value)); });
		dispatch_branch<float>   (*this, +[](float&   value, json& json_value) { json_value = value; });
		dispatch_branch<double>  (*this, +[](double&  value, json& json_value) { json_value = value; });
		dispatch_branch<cstring> (*this, +[](cstring  value, json& json_value) { json_value = string(value); });
		dispatch_branch<string>  (*this, +[](string&  value, json& json_value) { json_value = value; });
		dispatch_branch<bool>    (*this, +[](bool&    value, json& json_value) { json_value = value; });

		dispatch_branch<Type>(*this, +[](Type& type, json& json_value) { json_value = type.m_name; });

		dispatch_branch<vector<Var>>(*this, +[](vector<Var>& values, json& json_value)
		{
			std::vector<json> json_values = std::vector<json>(values.size());
			for(size_t i = 0; i < values.size(); ++i)
				pack_typed(values[i], json_values[i]);
			json_value = json_values;
		});

		dispatch_branch<Call>(*this, +[](Call& call, json& json_value)
		{
			std::map<std::string, json> json_values;
			json_values["callable"] = string(call.m_callable->m_name);
			pack(Ref(&call.m_args), json_values["arguments"]);
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
	
	Var unpack(FromJson& unpacker, Type& type, const json& json_value)
	{
		Var result = meta(type).m_empty_var;
		unpack(unpacker, result.m_ref, json_value);
		return result;
	}

	void unpack(FromJson& unpacker, Var& value, const json& json_value)
	{
		if(json_value.is_null())
			return;

		// @note: we MUST take a Var& as parameter of this function for this specific case
		// -> polymorphic objects must be created by value since we don't know in advance the actual type we are loading
		if(is_abstract(type(value)))
		{
			value = unpack_typed(unpacker, json_value);
			return;
		}

		unpack(unpacker, value.m_ref, json_value);
	}

	void unpack(FromJson& unpacker, Ref value, const json& json_value)
	{
		if(unpacker.check(value))
		{
			unpacker.dispatch(value, json_value);
			return;
		}
		else if(is_enum(type(value)) && json_value.is_number()) // is_number_integer
		{
			enum_set_value(value, json_value.int_value());
			return;
		}
		else if(g_convert[type(value).m_id] && json_value.is_string())
		{
			convert(type(value)).to_value(json_value.string_value().c_str(), value);
			return;
		}
		else if(is_sequence(type(value)))
		{
			for(const json& json_element : json_value.array_items())
			{
				sequence(value).push(value);
				Ref element = iter(value).back(value);
				unpack(unpacker, element, json_element);
				//Var element = unpack(unpacker, *iter(value).m_element_type, json_element);
				//sequence(value).add(value, element);
			}
			return;
		}

		size_t size = json_value.is_array() ? json_value.array_items().size() : json_value.object_items().size();

		if(!g_class[type(value).m_id])
		{
			printf("WARNING: unpack - type %s is not a class\n", type(value).m_name);
			return;
		}

		const Class& cl = cls(value);
		const Constructor* constructor = cl.constructor(size);

		if(is_struct(*value.m_type)) // true) //!constructor)
		{
			auto unpack_member = [&](const Member& member, const json& member_value)
			{
#if MUD_DEBUG_SERIAL
				printf("DEBUG: unpacking member %s :: %s\n", type(value).m_name, member.m_name);
#endif
				if(is_abstract(*member.m_type))
					member.set(value, unpack_typed(unpacker, member_value));
				else
					unpack(unpacker, member.get(value), member_value);
			};

			if(json_value.is_object())
			{
				for(const Member& member : cl.m_members)
					if(!json_value[member.m_name].is_null())
					{
						unpack_member(member, json_value[member.m_name]);
					}
			}
			else if(json_value.is_array())
			{
				for(size_t index = 0; index < size; ++index)
				{
					unpack_member(cl.m_members[index], json_value[index]);
				}
			}
		}
		else
		{
			Call construct = { *constructor };

			for(size_t index = 0; index < size; ++index)
			{
				const Param& param = construct.m_callable->m_params[index + 1];
#ifdef MUD_DEBUG_SERIAL
				printf("DEBUG: unpacking param %s :: %s\n", type(value).m_name, param.m_name);
#endif
				const json& json_field = json_value.is_array() ? json_value[index]
															   : json_value[param.m_name];

				if(is_abstract(*param.m_type))
					construct.m_args[index + 1] = unpack_typed(unpacker, json_field);
				else
					unpack(unpacker, construct.m_args[index + 1], json_field);
			}

			construct.prepare();
			construct(value);
		}
	}

	Var unpack_typed(FromJson& unpacker, const json& json_typed_value)
	{
		cstring type_name = json_typed_value["type"].string_value().c_str();
		json json_value = json_typed_value["value"];
		Type& type = *System::instance().find_type(type_name);
		return unpack(unpacker, type, json_value);
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
			json_value = to_string(value.m_ref);
		}
		else if(is_enum(type(value)))
		{
#ifdef NO_HUMAN_READABLE
			json_value = int(enu(value).value(value));
#else
			json_value = to_string(value.m_ref);
#endif
		}
		else if(is_sequence(type(value)))
		{
			size_t i = 0;
			std::vector<json> json_values = std::vector<json>(iter(value).size(value));
			iter(value).iterate(value, [&](Ref element) {
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
						if(memcmp(member_val.m_ref.m_value, member.m_default_value.m_value, meta(member_val).m_size) == 0)
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
		return json_value.dump().c_str();
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

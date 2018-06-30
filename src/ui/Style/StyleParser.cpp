//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <refl/Class.h>
#include <srlz/Serial.h>
#include <infra/String.h>
#include <math/VecJson.h>
#include <ui/Types.h>
#include <ui/Style/StyleParser.h>
#include <ui/Style/Style.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Styler.h>
#include <ui/UiWindow.h>
#endif

#include <json11.hpp>

namespace mud
{
	void load_style(Styler& styler, const string& name, const json& json_style);

	void decline_images(Styler& styler, const string& style, Options& skin_def, const string& state)
	{
		for(size_t i = 0; i < skin_def.m_fields.size(); ++i)
			if(!skin_def.m_fields[i].none() && (type(skin_def.m_fields[i]).is<Image>()
											|| type(skin_def.m_fields[i]).is<ImageSkin>()))
			{
				Member& member = cls<InkStyle>().m_members[i];

				Var value = skin_def.m_fields[member.m_index];
				Options& declined_skin_def = styler.m_skin_definitions[style + ":" + state];

				if(type(value).is<Image>())
				{
					string image_name = string(val<Image>(value).d_name) + "_" + replace_all(state, "|", "_");
					Image& declined_image = *styler.m_uiWindow.find_image(image_name.c_str());
					declined_skin_def.set(member.m_index, Ref(&declined_image));
				}
				else if(type(value).is<ImageSkin>())
				{
					string image_name = string(val<ImageSkin>(value).d_image->d_name) + "_" + replace_all(state, "|", "_");
					Image& declined_image = *styler.m_uiWindow.find_image(image_name.c_str());
					declined_skin_def.set(member.m_index, var(ImageSkin(declined_image, val<ImageSkin>(value))));
				}
			}
	}

	void decline(Styler& styler, const string& style, Options& skin_def, const json& json_states)
	{
		for(const json& state : json_states.array_items())
			decline_images(styler, style, skin_def, state.string_value());
	}

	FromJson style_unpacker(UiWindow& ui_window)
	{
		FromJson unpacker;
		unpacker.function<Image>([&](Ref, Ref& result, const json& json)
		{
			result = json == "null" ? Ref((Image*) nullptr)
									: Ref(ui_window.find_image(json.string_value().c_str()));
		});
		return unpacker;
	}

	void load_member(Styler& styler, Options& definition, Member& member, const json& json_value)
	{
		static FromJson unpacker = style_unpacker(styler.m_uiWindow);
		Var value = member.m_default_value;
		unpack(unpacker, value, json_value);
		definition.set(member.m_index, value);
	}

	void load_style_attr(Styler& styler, const string& style, Options& layout_def, Options& skin_def, string key, const json& json_value)
	{
		string skin_key = replace_all(key, "skin_", "");

		if(key == "selector" || key == "reset_skin")
			;
		else if(key == "copy_skin")
			skin_def.merge(styler.m_skin_definitions[json_value.string_value()]);
		else if(key == "decline")
			decline(styler, style, skin_def, json_value);
		else if(cls<Layout>().has_member(key.c_str()))
			load_member(styler, layout_def, cls<Layout>().member(key.c_str()), json_value);
		else if(cls<InkStyle>().has_member(skin_key.c_str()))
			load_member(styler, skin_def, cls<InkStyle>().member(skin_key.c_str()), json_value);
		else if(key.find("comment") != string::npos)
			;
		else // if(vector_has(meta<WidgetState>().m_enumIds, to_upper(key)))
		{
			std::vector<string> states = split_string(replace_all(key, " ", ""), ",");
			
			for(const string& state : states)
				load_style(styler, style + ":" + state, json_value);
		}
	}

	void load_style(Styler& styler, const string& selector, const json& json_style)
	{
		std::vector<string> names = split_string(replace_all(selector, " ", ""), ",");
		
		for(const string& name : names)
		{
			Options& layout_def = styler.m_layout_definitions[name];
			Options& skin_def = styler.m_skin_definitions[name];

			for(auto& key_value : json_style.object_items())
				load_style_attr(styler, name, layout_def, skin_def, key_value.first, key_value.second);
		}
	}

	void replace_colours(const std::map<string, Colour>& colours, json& json_value)
	{
		visit_json(json_value, [&](json& json_value)
		{
			if(json_value.is_string() && colours.find(json_value.string_value()) != colours.end())
				to_json(colours.at(json_value.string_value()), json_value);
		});
	}

	void load_colours(std::map<string, Colour>& colours, const json& json_colours)
	{
		for(auto& key_value : json_colours.object_items())
			from_json(key_value.second, colours[key_value.first]);
	}

	void load_style_sheet(Styler& styler, cstring path)
	{
		json style_sheet;
		parse_json_file(path, style_sheet);

		const json& includes = style_sheet["includes"];
		for(size_t i = 0; i < includes.array_items().size(); ++i)
		{
			load_style_sheet(styler, (string(styler.m_uiWindow.m_resource_path) + "interface/styles/" + includes[i].string_value()).c_str());
		}

		std::map<string, Colour> colours;
		load_colours(colours, style_sheet["colours"]);
		replace_colours(colours, const_cast<json&>(style_sheet["styles"]));

		const json& styles = style_sheet["styles"];
		for(size_t i = 0; i < styles.array_items().size(); ++i)
			load_style(styler, styles[i]["selector"].string_value(), styles[i]);
	}

	void set_style_sheet(Styler& styler, cstring path)
	{
		styler.clear();

		load_style_sheet(styler, path);

		styler.setup();
	}

	void set_default_style_sheet(Styler& styler)
	{
		styler.clear();
		styler.setup();
	}
}

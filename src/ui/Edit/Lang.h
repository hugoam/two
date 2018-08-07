//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Edit/TypeIn.h>

#ifndef MUD_CPP_20
#include <unordered_set>
#include <unordered_map>

#include <map>
#include <regex>
#endif

namespace mud
{
	struct Identifier
	{
		uvec2 m_location;
		string m_declaration;
	};

	struct LanguageDefinition
	{
		string m_name;
		std::vector<string> m_punctuation;
		std::vector<string> m_operators;
		std::unordered_set<string> m_keywords;
		std::unordered_map<string, Identifier> m_identifiers;
		std::unordered_map<string, Identifier> m_functions;
		std::unordered_map<string, Identifier> m_preproc_identifiers;
		string m_comment_start;
		string m_comment_end;

		std::vector<std::pair<string, PaletteIndex>> m_regex_string_tokens;
		std::vector<std::pair<std::regex, PaletteIndex>> m_regex_tokens;

		bool m_case_sensitive;
	};

	LanguageDefinition& LanguageCpp();
	LanguageDefinition& LanguageHLSL();
	LanguageDefinition& LanguageGLSL();
	LanguageDefinition& LanguageC();
	LanguageDefinition& LanguageLua();
	LanguageDefinition& LanguageWren();
}

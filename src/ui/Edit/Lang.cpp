//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Edit/Lang.h>
#endif

#include <stl/tinystl/hash_base.impl.h>

namespace mud
{
	template<class T, size_t N>
	constexpr size_t size(T(&)[N]) { return N; }

	vector<uint32_t>& TextEdit::OkaidaPalette()
	{
		static vector<uint32_t> palette = vector<uint32_t>(size_t(CodePalette::Count));

		palette[Text::Default] = 0xffffffff;
		palette[Text::Background] = 0x000000ff;
		//palette[Text::Background] = 0x1e1e1eff;
		//palette[Text::Background] = 0x1f1f1fff;
		palette[Text::Cursor] = 0xe0e0e0ff;
		palette[Text::Selection] = 0x264f78ff;
		palette[Text::LineNumber] = 0x2b91afff;
		palette[Text::CurrentLineFill] = 0x0f0f0fff;
		palette[Text::CurrentLineFillInactive] = 0x242424ff;
		palette[Text::CurrentLineEdge] = 0x282828ff;

		palette[size_t(CodePalette::Word)] = 0xf8f8f2ff;
		palette[size_t(CodePalette::Keyword)] = 0xF92672ff;
		palette[size_t(CodePalette::Number)] = 0xae81ffff;
		palette[size_t(CodePalette::String)] = 0xa6e22eff;
		palette[size_t(CodePalette::CharLiteral)] = 0xa6e22eff;
		palette[size_t(CodePalette::Punctuation)] = 0xbebec5ff;
		palette[size_t(CodePalette::Operator)] = 0xF92672ff;
		palette[size_t(CodePalette::Preprocessor)] = 0x9b9b9bff;
		palette[size_t(CodePalette::Variable)] = 0x9b9b9bff;
		palette[size_t(CodePalette::Identifier)] = 0x7fc6efff;
		palette[size_t(CodePalette::Function)] = 0xe6db74ff;
		palette[size_t(CodePalette::Parameter)] = 0x7d7d7dff;
		palette[size_t(CodePalette::Field)] = 0x7d7d7dff;
		palette[size_t(CodePalette::PreprocIdentifier)] = 0xc040a0ff;
		palette[size_t(CodePalette::Comment)] = 0x708090ff;
		palette[size_t(CodePalette::Error)] = 0xffffffff;
		palette[size_t(CodePalette::ErrorMarker)] = 0xa30100ff;
		palette[size_t(CodePalette::Breakpoint)] = 0xf0800040;

		return palette;
	}

	vector<uint32_t>& TextEdit::DarkPalette()
	{
		static vector<uint32_t> palette = vector<uint32_t>(size_t(CodePalette::Count));

		palette[Text::Default]                 = 0xffffffff;
		palette[Text::Background]              = 0x1e1e1eff;
		//palette[Text::Background]              = 0x000000ff;
		palette[Text::Cursor]                  = 0xe0e0e0ff;
		palette[Text::Selection]               = 0x264f78ff;
		palette[Text::LineNumber]              = 0x2b91afff;
		palette[Text::CurrentLineFill]         = 0x0f0f0fff;
		palette[Text::CurrentLineFillInactive] = 0x242424ff;
		palette[Text::CurrentLineEdge]         = 0x282828ff;

		palette[size_t(CodePalette::Word)]				= 0xc8c8c8ff;
		palette[size_t(CodePalette::Keyword)]           = 0x569cd6ff;
		palette[size_t(CodePalette::Number)]            = 0xb5cea8ff;
		palette[size_t(CodePalette::String)]            = 0xd69d85ff;
		palette[size_t(CodePalette::CharLiteral)]       = 0xd69d85ff; //0xff70a0e0
		palette[size_t(CodePalette::Punctuation)]       = 0xbebec5ff;
		palette[size_t(CodePalette::Operator)]			= 0xffffffff;
		palette[size_t(CodePalette::Preprocessor)]      = 0x9b9b9bff;
		palette[size_t(CodePalette::Variable)]			= 0x9b9b9bff;
		palette[size_t(CodePalette::Identifier)]		= 0x4ec9b0ff;
		palette[size_t(CodePalette::Function)]			= 0xffffffff;
		palette[size_t(CodePalette::Parameter)]			= 0x7d7d7dff;
		palette[size_t(CodePalette::Field)]				= 0x9b9b9bff;
		palette[size_t(CodePalette::PreprocIdentifier)] = 0xc040a0ff;
		palette[size_t(CodePalette::Comment)]           = 0x494949ff;
		palette[size_t(CodePalette::Error)]				= 0xffffffff;
		palette[size_t(CodePalette::ErrorMarker)]       = 0xa30100ff;
		palette[size_t(CodePalette::Breakpoint)]        = 0xf0800040;

		return palette;
	}

	void builtin_keywords(LanguageDefinition& language, array<cstring> keywords)
	{
		for(cstring i : keywords)
			language.m_keywords.insert(string(i));
	}

	void builtin_identifiers(LanguageDefinition& language, array<cstring> identifiers)
	{
		for (cstring k : identifiers)
		{
			Identifier id = { {}, "Built-in identifier" };
			language.m_identifiers.insert({ string(k), id });
		}
	}

	void builtin_functions(LanguageDefinition& language, array<cstring> functions)
	{
		for (cstring k : functions)
		{
			Identifier id = { {}, "Built-in function" };
			language.m_functions.insert({ string(k), id });
		}
	}

	void add_token_regex(LanguageDefinition& lang, const string& token, CodePalette index)
	{
		lang.m_regex_string_tokens.push_back({ token, PaletteIndex(index) });
		lang.m_regex_tokens.push_back({ std::regex(token.c_str(), std::regex_constants::optimize), PaletteIndex(index) });
	}

	string list_regex(const vector<string>& tokens)
	{
		string r = "[";
		for(const string& token : tokens)
			r += "\\" + token;
		r += "]";
		return r;
	}

	LanguageDefinition& LanguageCpp()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "(", ")", ";", "," };

			lang.m_operators = { "+", "-", "*", "/", "=", "~", "|", "<", ">", "?", "/", ".", "!", "%", "^", "&" };

			static cstring keywords[] =
			{
				"alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", "char16_t", "char32_t", "class",
				"compl", "concept", "const", "constexpr", "const_cast", "continue", "decltype", "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export_", "extern", "false", "float",
				"for", "friend", "goto", "if", "import", "inline", "int", "long", "m", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public",
				"register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", "switch", "synchronized", "template", "this", "thread_local",
				"throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
				"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "printf", "sprintf", "snprintf", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper",
				"std", "string", "vector", "map", "unordered_map", "set", "unordered_set", "min", "max"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "C++";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageHLSL()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", ".]" };

			lang.m_operators = {};

			static cstring keywords[] =
			{
				"AppendStructuredBuffer", "asm", "asm_fragment", "BlendState", "bool", "break", "Buffer", "ByteAddressBuffer", "case", "cbuffer", "centroid", "class", "column_major", "compile", "compile_fragment",
				"CompileShader", "const", "continue", "ComputeShader", "ConsumeStructuredBuffer", "default", "DepthStencilState", "DepthStencilView", "discard", "do", "double", "DomainShader", "dword", "else",
				"export_", "extern", "false", "float", "for", "fxgroup", "GeometryShader", "groupshared", "half", "Hullshader", "if", "in", "inline", "inout", "InputPatch", "int", "interface", "line", "lineadj",
				"linear", "LineStream", "matrix", "min16float", "min10float", "min16int", "min12int", "min16uint", "namespace", "nointerpolation", "noperspective", "NULL", "out", "OutputPatch", "packoffset",
				"pass", "pixelfragment", "PixelShader", "point", "PointStream", "precise", "RasterizerState", "RenderTargetView", "return", "register", "row_major", "RWBuffer", "RWByteAddressBuffer", "RWStructuredBuffer",
				"RWTexture1D", "RWTexture1DArray", "RWTexture2D", "RWTexture2DArray", "RWTexture3D", "sample", "sampler", "SamplerState", "SamplerComparisonState", "shared", "snorm", "stateblock", "stateblock_state",
				"static", "string", "struct", "switch", "StructuredBuffer", "tbuffer", "technique", "technique10", "technique11", "texture", "Texture1D", "Texture1DArray", "Texture2D", "Texture2DArray", "Texture2DMS",
				"Texture2DMSArray", "Texture3D", "TextureCube", "TextureCubeArray", "true", "typedef", "triangle", "triangleadj", "TriangleStream", "uint", "uniform", "unorm", "unsigned", "vector", "vertexfragment",
				"VertexShader", "void", "volatile", "while",
				"bool1","bool2","bool3","bool4","double1","double2","double3","double4", "float1", "float2", "float3", "float4", "int1", "int2", "int3", "int4", "in", "out", "inout",
				"uint1", "uint2", "uint3", "uint4", "dword1", "dword2", "dword3", "dword4", "half1", "half2", "half3", "half4",
				"float1x1","float2x1","float3x1","float4x1","float1x2","float2x2","float3x2","float4x2",
				"float1x3","float2x3","float3x3","float4x3","float1x4","float2x4","float3x4","float4x4",
				"half1x1","half2x1","half3x1","half4x1","half1x2","half2x2","half3x2","half4x2",
				"half1x3","half2x3","half3x3","half4x3","half1x4","half2x4","half3x4","half4x4",
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "all", "AllMemoryBarrier", "AllMemoryBarrierWithGroupSync", "any", "asdouble", "asfloat", "asin", "asint", "asint", "asuint",
				"asuint", "atan", "atan2", "ceil", "CheckAccessFullyMapped", "clamp", "clip", "cos", "cosh", "countbits", "cross", "D3DCOLORtoUBYTE4", "ddx",
				"ddx_coarse", "ddx_fine", "ddy", "ddy_coarse", "ddy_fine", "degrees", "determinant", "DeviceMemoryBarrier", "DeviceMemoryBarrierWithGroupSync",
				"distance", "dot", "dst", "errorf", "EvaluateAttributeAtCentroid", "EvaluateAttributeAtSample", "EvaluateAttributeSnapped", "exp", "exp2",
				"f16tof32", "f32tof16", "faceforward", "firstbithigh", "firstbitlow", "floor", "fma", "fmod", "frac", "frexp", "fwidth", "GetRenderTargetSampleCount",
				"GetRenderTargetSamplePosition", "GroupMemoryBarrier", "GroupMemoryBarrierWithGroupSync", "InterlockedAdd", "InterlockedAnd", "InterlockedCompareExchange",
				"InterlockedCompareStore", "InterlockedExchange", "InterlockedMax", "InterlockedMin", "InterlockedOr", "InterlockedXor", "isfinite", "isinf", "isnan",
				"ldexp", "length", "lerp", "lit", "log", "log10", "log2", "mad", "max", "min", "modf", "msad4", "mul", "noise", "normalize", "pow", "printf",
				"Process2DQuadTessFactorsAvg", "Process2DQuadTessFactorsMax", "Process2DQuadTessFactorsMin", "ProcessIsolineTessFactors", "ProcessQuadTessFactorsAvg",
				"ProcessQuadTessFactorsMax", "ProcessQuadTessFactorsMin", "ProcessTriTessFactorsAvg", "ProcessTriTessFactorsMax", "ProcessTriTessFactorsMin",
				"radians", "rcp", "reflect", "refract", "reversebits", "round", "rsqrt", "saturate", "sign", "sin", "sincos", "sinh", "smoothstep", "sqrt", "step",
				"tan", "tanh", "tex1D", "tex1D", "tex1Dbias", "tex1Dgrad", "tex1Dlod", "tex1Dproj", "tex2D", "tex2D", "tex2Dbias", "tex2Dgrad", "tex2Dlod", "tex2Dproj",
				"tex3D", "tex3D", "tex3Dbias", "tex3Dgrad", "tex3Dlod", "tex3Dproj", "texCUBE", "texCUBE", "texCUBEbias", "texCUBEgrad", "texCUBElod", "texCUBEproj", "transpose", "trunc"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "HLSL";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageGLSL()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", "." };

			static cstring keywords[] =
			{
				"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
				"signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
				"_Noreturn", "_Static_assert", "_Thread_local"
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
				"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "GLSL";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageC()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", "." };

			static cstring keywords[] =
			{
				"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
				"signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
				"_Noreturn", "_Static_assert", "_Thread_local"
			};

			static cstring identifiers[] =
			{
				"abort", "abs", "acos", "asin", "atan", "atexit", "atof", "atoi", "atol", "ceil", "clock", "cosh", "ctime", "div", "exit", "fabs", "floor", "fmod", "getchar", "getenv", "isalnum", "isalpha", "isdigit", "isgraph",
				"ispunct", "isspace", "isupper", "kbhit", "log10", "log2", "log", "memcmp", "modf", "pow", "putchar", "putenv", "puts", "rand", "remove", "rename", "sinh", "sqrt", "srand", "strcat", "strcmp", "strerror", "time", "tolower", "toupper"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[ \t]*#[ \\t]*[a-zA-Z_]+", CodePalette::Preprocessor);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "C";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageLua()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "[", "]", "{", "}", "!", "%", "^", "&", "*", "(", ")", "-", "+", "=", "~", "|", "<", ">", "?", "/", ";", ",", "." };

			static cstring keywords[] =
			{
				"and", "break", "do", "", "else", "elseif", "end", "false", "for", "function", "if", "in", "", "local", "nil", "not", "or", "repeat", "return", "then", "true", "until", "while"
			};

			static cstring identifiers[] =
			{
				"_G",  "_VERSION", "coroutine", "table", "io", "os", "string", "utf8", "bit32", "math", "debug", "package"
			};

			static cstring functions[] =
			{
				"assert", "collectgarbage", "dofile", "error", "getmetatable", "ipairs", "loadfile", "load", "loadstring",  "next",  "pairs",  "pcall",  "print",  "rawequal",  "rawlen",  "rawget",  "rawset",
				"select",  "setmetatable",  "tonumber",  "tostring",  "type",  "xpcall", "arshift", "band", "bnot", "bor", "bxor", "btest", "extract", "lrotate", "lshift", "replace",
				"rrotate", "rshift", "create", "resume", "running", "status", "wrap", "yield", "isyieldable", "debug","getuservalue", "gethook", "getinfo", "getlocal", "getregistry", "getmetatable",
				"getupvalue", "upvaluejoin", "upvalueid", "setuservalue", "sethook", "setlocal", "setmetatable", "setupvalue", "traceback", "close", "flush", "input", "lines", "open", "output", "popen",
				"read", "tmpfile", "type", "write", "close", "flush", "lines", "read", "seek", "setvbuf", "write", "__gc", "__tostring", "abs", "acos", "asin", "atan", "ceil", "cos", "deg", "exp", "tointeger",
				"floor", "fmod", "ult", "log", "max", "min", "modf", "rad", "random", "randomseed", "sin", "sqrt", "string", "tan", "type", "atan2", "cosh", "sinh", "tanh",
				"pow", "frexp", "ldexp", "log10", "pi", "huge", "maxinteger", "mininteger", "loadlib", "searchpath", "seeall", "preload", "cpath", "path", "searchers", "loaded", "m", "require", "clock",
				"date", "difftime", "execute", "exit", "getenv", "remove", "rename", "setlocale", "time", "tmpname", "byte", "char", "dump", "find", "format", "gmatch", "gsub", "len", "lower", "match", "rep",
				"reverse", "sub", "upper", "pack", "packsize", "unpack", "concat", "maxn", "insert", "pack", "unpack", "remove", "move", "sort", "offset", "codepoint", "char", "len", "codes", "charpattern"
			};

			builtin_keywords(lang, { keywords, size(keywords) });
			builtin_identifiers(lang, { identifiers, size(identifiers) });
			builtin_functions(lang, { functions, size(functions) });

			add_token_regex(lang, "\\-\\-.*", CodePalette::Comment);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\\'[^\\\']*\\\'", CodePalette::String);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);

			lang.m_comment_start = "\\-\\-\\[\\[";
			lang.m_comment_end = "\\]\\]";

			lang.m_case_sensitive = true;

			lang.m_name = "Lua";

			inited = true;
		}
		return lang;
	}

	LanguageDefinition& LanguageWren()
	{
		static bool inited = false;
		static LanguageDefinition lang;
		if(!inited)
		{
			lang.m_punctuation = { "{", "}", "(", ")", ",", "." };

			lang.m_operators = { "[", "]", "!", "%", "^", "&", "*", "-", "+", "=", "~", "|", "<", ">", "?", "/", ":", ";" };

			static cstring keywords[] =
			{
				"class", "construct", "continue", "else", "false", "for", "foreign", "if", "import", "in", "is", "new", "null", "return", "static", "this", "true", "var", "while"
			};

			builtin_keywords(lang, { keywords, size(keywords) });

			add_token_regex(lang, "//.*", CodePalette::Comment);
			add_token_regex(lang, "[A-Z][a-zA-Z0-9_]*", CodePalette::Identifier);
			add_token_regex(lang, "[_][a-zA-Z0-9_]*", CodePalette::Field);
			add_token_regex(lang, "[a-z0-9_]+(?=\\()", CodePalette::Function);
			add_token_regex(lang, "[a-zA-Z_][a-zA-Z0-9_]*", CodePalette::Word);
			add_token_regex(lang, list_regex(lang.m_punctuation), CodePalette::Punctuation);
			add_token_regex(lang, list_regex(lang.m_operators), CodePalette::Operator);
			add_token_regex(lang, "L?\\\"(\\\\.|[^\\\"])*\\\"", CodePalette::String);
			add_token_regex(lang, "\\'\\\\?[^\\']\\'", CodePalette::CharLiteral);
			add_token_regex(lang, "0[xX][0-9a-fA-F]+[uU]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", CodePalette::Number);
			add_token_regex(lang, "0[0-7]+[Uu]?[lL]?[lL]?", CodePalette::Number);
			add_token_regex(lang, "[+-]?[0-9]+[Uu]?[lL]?[lL]?", CodePalette::Number);

			lang.m_comment_start = "/*";
			lang.m_comment_end = "*/";

			lang.m_case_sensitive = true;

			lang.m_name = "Wren";

			inited = true;
		}
		return lang;
	}
}

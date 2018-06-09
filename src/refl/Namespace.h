//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	using cstring = const char*;

	export_ class refl_ MUD_REFL_EXPORT Namespace
	{
	public:
		Namespace(cstring name = nullptr, Namespace* parent = nullptr);

		bool is_root() { return m_name == nullptr; }

		cstring m_name;
		Namespace* m_parent;
		std::vector<cstring> m_path;
	};

	export_ MUD_REFL_EXPORT Namespace& namspc(std::vector<cstring> path);
}

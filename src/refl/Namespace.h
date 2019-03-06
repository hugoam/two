//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/span.h>
#include <stl/string.h>
#include <refl/Forward.h>

namespace mud
{
	using cstring = const char*;

	export_ class refl_ MUD_REFL_EXPORT Namespace
	{
	public:
		Namespace(cstring name = nullptr, Namespace* parent = nullptr);

		bool is_root() { return m_name[0] == 0; }

		cstring m_name;
		Namespace* m_parent;
		vector<cstring> m_path;
	};

	export_ MUD_REFL_EXPORT Namespace& namspc(span<cstring> path);
}

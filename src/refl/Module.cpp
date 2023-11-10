//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.refl;
#else
#include <refl/Module.h>
#endif

namespace two
{
	Module::Module(cstring name, vector<Module*> deps)
		: m_name(name)
		, m_deps(deps)
	{}
}

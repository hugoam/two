//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <mud/Forward.h>

using namespace mud;

#ifdef DOCKBAR
void ex_04_lights(Shell& app, Widget& parent, Dockbar& dockbar);
#else
void ex_04_lights(Shell& app, Widget& parent);
#endif

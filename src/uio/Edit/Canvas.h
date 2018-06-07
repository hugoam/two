//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <lang/Script.h>
#endif
#include <uio/Edit/Section.h>

namespace mud
{
	struct ProcessStructure;
	struct ProcessConstruct;

	export_ MUD_UIO_EXPORT void process_display(Widget& parent, ProcessDisplay& process);
	export_ MUD_UIO_EXPORT void process_display_structure(Widget& parent, ProcessStructure& process);
	export_ MUD_UIO_EXPORT void process_construct(Widget& parent, ProcessConstruct& process);
	export_ MUD_UIO_EXPORT void visual_script_edit(Widget& parent, VisualScript& script, ActionList actions = {});
}

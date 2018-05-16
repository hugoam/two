//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <lang/Script.h>
#include <uio/Edit/Section.h>

namespace mud
{
	MUD_UIO_EXPORT void process_display(Widget& parent, ProcessDisplay& process);
	//void process_display_structure(Widget& nodeProcessStructure& process);
	// show object_structure
	//void process_construct(Widget& nodeProcessConstruct& process);
	// show object_meta_creator
	MUD_UIO_EXPORT void visual_script_edit(Widget& parent, VisualScript& script, ActionList actions = {});
}

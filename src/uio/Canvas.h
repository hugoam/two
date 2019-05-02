//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <lang/Script.h>
#endif
#include <ui/Section.h>

namespace two
{
	struct ProcessStructure;
	struct ProcessConstruct;

	export_ TWO_UIO_EXPORT void process_display(Widget& parent, ProcessDisplay& process);
	export_ TWO_UIO_EXPORT void process_display_structure(Widget& parent, ProcessStructure& process);
	export_ TWO_UIO_EXPORT void process_construct(Widget& parent, ProcessConstruct& process);
	export_ TWO_UIO_EXPORT Section& visual_script_edit(Widget& parent, VisualScript& script);
}

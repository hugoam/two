//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Generated/Forward.h>
#include <uio/Unode.h>

namespace mud
{
	MUD_UIO_EXPORT void object_indexer(Widget& parent, Indexer& indexer);
	MUD_UIO_EXPORT Ref object_selector(Widget& parent, Indexer& indexer);
	MUD_UIO_EXPORT void object_indexer_modal(Widget& parent, Indexer& indexer);

	MUD_UIO_EXPORT Ref object_picker(Widget& parent, Type& type);
	MUD_UIO_EXPORT Ref object_picker_modal(Widget& parent, Type& type);
}

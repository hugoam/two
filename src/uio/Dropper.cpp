//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.uio;
#else
#include <uio/Dropper.h>
#endif

namespace mud
{
#if 0
	Dropper::Dropper(Widget& parent, Type& deviceType)
		: Widget(parent, deviceType)
	{}

	void Dropper::drop(Widget& parent, , size_t index)
	{
		Dropper& source = static_cast<Dropper&>(*node.m_parent);
		Widget* swap = this->swapdrop(node, source);
		size_t swapindex = node.m_index;

		if(!this->candrop(node, source))
			return;

		if(swap)
		{
			if(!source.candrop(*swap, *this))
				return;
		}

		source.dropout(node, *this);
		this->dropin(node, source, index);

		if(swap)
		{
			this->dropout(*swap, source);
			source.dropin(*swap, *this, swapindex);
		}
	}
#endif
}

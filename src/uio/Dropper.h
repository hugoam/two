//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Forward.h>

namespace two
{
#if 0
	export_ class TWO_UIO_EXPORT Dropper : public Widget
	{
	public:
		Dropper(Widget& parent, Type& deviceType);

		void drop(Widget& parent, , size_t position);

	protected:
		virtual Widget* swapdrop(Widget& parent, , Dropper& source) = 0;
		virtual bool candrop(Widget& parent, , Dropper& source) = 0;
		virtual void dropin(Widget& parent, , Dropper& source, size_t index) = 0;
		virtual void dropout(Widget& parent, , Dropper& source) = 0;
	};
#endif
}

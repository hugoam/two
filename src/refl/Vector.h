//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/algorithm.h>
#include <infra/TypeTraits.h>
#endif
#include <refl/Forward.h>

namespace two
{
	export_ template <class T>
	enable_if<is_comparable<T>, void> vector_remove_any(vector<T>& vector, T value) { remove(vector, value); }

	export_ template <class T>
	enable_if<!is_comparable<T>, void> vector_remove_any(vector<T>& vector, T& value) { remove_object(vector, value); }
}

//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <type/Any.h>
#include <infra/Vector.h>

namespace mud
{
	export_ template <class T>
	typename std::enable_if<is_comparable<T>::value, void>::type vector_remove_any(vector<T>& vector, T value) { vector_remove(vector, value); }

	export_ template <class T>
	typename std::enable_if<!is_comparable<T>::value, void>::type vector_remove_any(vector<T>& vector, T& value) { vector_remove_object(vector, value); }
}

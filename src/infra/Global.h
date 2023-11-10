//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

namespace two
{
	export_ template <class T>
	class Global
	{
	public:
		static T me;
	};

	template <class T>
	T Global<T>::me;

	export_ template <class T>
	class LazyGlobal
	{
	public:
		static T& me() { static T instance; return instance; }
	};
}

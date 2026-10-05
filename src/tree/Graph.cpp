//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.tree;

namespace two
{
	template <class T>
	void number_to_key(T& number, NodeKey& key)
	{
		key = { uint64_t(number) };
	}

	void null_to_key(decltype(nullptr)& null, NodeKey& key)
	{
		UNUSED(null);
		key = {};
	}

	void register_tree_conversions()
	{
		dispatch_branch<decltype(nullptr), NodeKey, null_to_key>(TypeConverter::me());
		dispatch_branch<int, NodeKey, number_to_key<int>>(TypeConverter::me());
		dispatch_branch<uint, NodeKey, number_to_key<uint>>(TypeConverter::me());
		dispatch_branch<ullong, NodeKey, number_to_key<ullong>>(TypeConverter::me());
		dispatch_branch<float, NodeKey, number_to_key<float>>(TypeConverter::me());
		dispatch_branch<double, NodeKey, number_to_key<double>>(TypeConverter::me());
	}
}

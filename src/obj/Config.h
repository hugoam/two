//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Pragma.h>

#ifndef MUD_META_GENERATOR
#define _refl_   // Reflect
#define _struct_ // Struct
#define _array_	 // Array type
#define _extern_ // Extern type
#define _comp_   // Component
#define _constr_ // Constructor
#define _meth_   // Method
#define _func_   // Function
#define _attr_   // Attribute
#define _mut_    // Mutable Attribute
#define _graph_  // Graph / Structure Attribute
#define _link_   // Link / Reference Attribute
#define _pool_   // Pool Attribute
#endif

#if defined _WIN32 || defined __CYGWIN__
	#if defined __GNUC__
		#define MUD_EXPORT __attribute__ ((dllexport))
		#define MUD_IMPORT __attribute__ ((dllimport))
	#else
		#define MUD_EXPORT __declspec(dllexport)
		#define MUD_IMPORT __declspec(dllimport)
	#endif
	#define DLL_LOCAL
#elif __GNUC__ >= 4
	#define MUD_EXPORT __attribute__ ((visibility ("default")))
	#define MUD_IMPORT
	#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
	#define MUD_EXPORT
	#define MUD_IMPORT
	#define DLL_LOCAL
#endif

#define MUD_FUNC_EXPORT __cdecl

#define UNUSED(x) (void)(x)

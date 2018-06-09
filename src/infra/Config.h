//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Pragma.h>

#ifndef MUD_META_GENERATOR
#define refl_   // Reflect
#define struct_ // Struct
#define array_	// Array type
#define extern_ // Extern type
#define comp_   // Component
#define constr_ // Constructor
#define meth_   // Method
#define func_   // Function
#define attr_   // Attribute
#define mut_    // Mutable Attribute
#define graph_  // Graph / Structure Attribute
#define link_   // Link / Reference Attribute
#define pool_   // Pool Attribute
#endif

#ifdef MUD_STATIC
#define MUD_EXPORT
#define MUD_IMPORT
#else
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
#endif

#define MUD_FUNC_EXPORT __cdecl

#define UNUSED(x) (void)(x)

#if defined _MSC_VER && _MSC_VER >= 1914
//#define MUD_MODULES
#endif

#ifdef MUD_MODULES
#define export_ export
#else
#define export_ 
#endif

#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif
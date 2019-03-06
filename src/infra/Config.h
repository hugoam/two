//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Pragma.h>

#ifndef MUD_META_GENERATOR
#define base_   // Base type
#define refl_   // Reflect
#define struct_ // Struct
#define nocopy_ // Nocopy type
#define array_	// Array type
#define seque_	// Sequence type
#define extern_ // Extern type
#define gpu_    // Gpu type
#define comp_   // Component
#define constr_ // Constructor
#define meth_   // Method
#define func_   // Function
#define attr_   // Attribute
#define nomut_  // Non Mutable Attribute
#define graph_  // Graph / Structure Attribute
#define link_   // Link / Reference Attribute
#define pool_   // Pool Attribute
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

#ifdef MUD_STATIC
#undef MUD_IMPORT
#define MUD_IMPORT
#endif

#define MUD_FUNC_EXPORT __cdecl

#define UNUSED(x) (void)(x)

#if defined _MSC_VER && _MSC_VER >= 1914
//#define MUD_MODULES
#endif

#ifdef MUD_MODULES
#define export_ export
#undef MUD_EXPORT
#define MUD_EXPORT
#else
#define export_ 
#endif

#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif

#ifdef MUD_META_GENERATOR
base_ static void* dvoidptr;
base_ static bool dbool;
base_ static char dchar;
base_ static signed char dschar;
base_ static short dshort;
base_ static int dint;
base_ static long dlong;
base_ static unsigned char duchar;
base_ static unsigned short dushort;
base_ static unsigned int duint;
base_ static unsigned long dulong;
base_ static unsigned long long dullong;
base_ static long long dllong;
base_ static long double dldouble;
base_ static float dfloat;
base_ static double ddouble;
base_ static const char* dcstring;
#include <stdint.h>
#include <stddef.h>
#endif

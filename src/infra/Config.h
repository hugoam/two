//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Pragma.h>

#ifndef TWO_META_GENERATOR
#define base_   // Base type
#define refl_   // Reflect
#define struct_ // Struct
#define nocopy_ // Nocopy type
#define array_	// Array type
#define span_	// Span type
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
		#define TWO_EXPORT __attribute__ ((dllexport))
		#define TWO_IMPORT __attribute__ ((dllimport))
	#else
		#define TWO_EXPORT __declspec(dllexport)
		#define TWO_IMPORT __declspec(dllimport)
	#endif
	#define DLL_LOCAL
#elif __GNUC__ >= 4
	#define TWO_EXPORT __attribute__ ((visibility ("default")))
	#define TWO_IMPORT
	#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
	#define TWO_EXPORT
	#define TWO_IMPORT
	#define DLL_LOCAL
#endif

#ifdef TWO_STATIC
#undef TWO_IMPORT
#define TWO_IMPORT
#endif

#define TWO_FUNC_EXPORT __cdecl

#define UNUSED(x) (void)(x)

#if defined _MSC_VER && _MSC_VER >= 1914
//#define TWO_MODULES
#endif

#ifdef TWO_MODULES
#define export_ export
#undef TWO_EXPORT
#define TWO_EXPORT
#else
#define export_ 
#endif

#ifndef TWO_INFRA_EXPORT
#define TWO_INFRA_EXPORT TWO_IMPORT
#endif

#ifdef TWO_META_GENERATOR
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

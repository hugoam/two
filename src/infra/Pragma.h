//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#if defined _MSC_VER
#	pragma warning (disable : 4201) // anonymous structs are supported by all target compilers
#	pragma warning (disable : 4251) // members are private, so there's no risk them being accessed by the user
#	pragma warning (disable : 4577) // two doesn't use exceptions
#	pragma warning (disable : 4459) // we are okay with hiding global declarations


#ifdef TWO_MODULES
#	pragma warning (disable : 4996) // with c++20 modules we can't pass _CRT_SECURE_NO_WARNINGS
// these are warnings in the experimental Visual Studio std module
#	pragma warning (disable : 4530) 
#	pragma warning (disable : 4127)
#	pragma warning (disable : 4100)
#	pragma warning (disable : 4244)
#	pragma warning (disable : 4522)
#	pragma warning (disable : 5050)
#	pragma warning (disable : 5202) // warning C5202: a global module fragment can only contain preprocessor directives
#endif

#endif


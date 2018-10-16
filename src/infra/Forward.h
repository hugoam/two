

#pragma once

#include <infra/Config.h>


#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

	using ushort = unsigned short;
	using uint = unsigned int;
	using ulong = unsigned long;
	using ulong2 = unsigned long long;

    template <class T> struct array;
    
    struct Filepath;
    struct swallow;
    class NonCopy;
    class Movabl;
}


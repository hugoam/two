#ifdef MUD_MODULES
#include <cpp/preimport.h>

module stb.rect_pack;

#ifdef STBRP_STATIC
#define STBRP_DEF static
#else
#define STBRP_DEF extern
#endif

#define STB_INCLUDE_STB_RECT_PACK_H
#endif

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb_rect_pack.h>

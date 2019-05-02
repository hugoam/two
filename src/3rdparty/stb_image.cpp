#ifdef TWO_MODULES
#include <cpp/preimport.h>

module stb.image;

#ifdef STB_IMAGE_STATIC
#define STBIDEF static
#else
#define STBIDEF extern
#endif

#define STBI_INCLUDE_STB_IMAGE_H
#endif

#if defined _MSC_VER
#pragma warning (disable : 4100)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

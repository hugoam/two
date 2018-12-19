

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <wfc/Types.h>
#include <wfc/Api.h>
#include <type/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_WFC_EXPORT Type& type<mud::Result>() { static Type ty("mud::Result"); return ty; }
    
    template <> MUD_WFC_EXPORT Type& type<mud::Tile>() { static Type ty("Tile"); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::Tileset>() { static Type ty("Tileset"); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::Wave>() { static Type ty("Wave"); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::TileWave>() { static Type ty("TileWave", type<mud::Wave>()); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::WaveTileset>() { static Type ty("WaveTileset", type<mud::Tileset>()); return ty; }
}

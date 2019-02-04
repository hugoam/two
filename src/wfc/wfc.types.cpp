#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <wfc/Types.h>
#include <wfc/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_WFC_EXPORT Type& type<mud::Result>() { static Type ty("mud::Result", sizeof(mud::Result)); return ty; }
    
    template <> MUD_WFC_EXPORT Type& type<mud::Tile>() { static Type ty("Tile", sizeof(mud::Tile)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::Tileset>() { static Type ty("Tileset", sizeof(mud::Tileset)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::Wave>() { static Type ty("Wave", sizeof(mud::Wave)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::TileWave>() { static Type ty("TileWave", type<mud::Wave>(), sizeof(mud::TileWave)); return ty; }
    template <> MUD_WFC_EXPORT Type& type<mud::WaveTileset>() { static Type ty("WaveTileset", type<mud::Tileset>(), sizeof(mud::WaveTileset)); return ty; }
}

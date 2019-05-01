#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-ui;
#else
#include <gfx-ui/Types.h>
#include <gfx-ui/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_UI_EXPORT Type& type<mud::ui::OrbitMode>() { static Type ty("OrbitMode", sizeof(mud::ui::OrbitMode)); return ty; }
    
    
    template <> MUD_GFX_UI_EXPORT Type& type<mud::SpaceSheet>() { static Type ty("SpaceSheet", type<mud::Ui>(), sizeof(mud::SpaceSheet)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::ViewerController>() { static Type ty("ViewerController", sizeof(mud::ViewerController)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::Viewer>() { static Type ty("Viewer", type<mud::Widget>(), sizeof(mud::Viewer)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::SceneViewer>() { static Type ty("SceneViewer", type<mud::Viewer>(), sizeof(mud::SceneViewer)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::OrbitController>() { static Type ty("OrbitController", type<mud::ViewerController>(), sizeof(mud::OrbitController)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::TrackballController>() { static Type ty("TrackballController", type<mud::ViewerController>(), sizeof(mud::TrackballController)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::OrbitControls>() { static Type ty("OrbitControls", type<mud::ViewerController>(), sizeof(mud::OrbitControls)); return ty; }
    template <> MUD_GFX_UI_EXPORT Type& type<mud::FreeOrbitController>() { static Type ty("FreeOrbitController", type<mud::OrbitController>(), sizeof(mud::FreeOrbitController)); return ty; }
}

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx-ui;
#else
#include <gfx-ui/Types.h>
#include <gfx-ui/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_GFX_UI_EXPORT Type& type<two::ui::OrbitMode>() { static Type ty("OrbitMode", sizeof(two::ui::OrbitMode)); return ty; }
    
    
    template <> TWO_GFX_UI_EXPORT Type& type<two::SpaceSheet>() { static Type ty("SpaceSheet", type<two::Ui>(), sizeof(two::SpaceSheet)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::ViewerController>() { static Type ty("ViewerController", sizeof(two::ViewerController)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::Viewer>() { static Type ty("Viewer", type<two::Widget>(), sizeof(two::Viewer)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::SceneViewer>() { static Type ty("SceneViewer", type<two::Viewer>(), sizeof(two::SceneViewer)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitController>() { static Type ty("OrbitController", type<two::ViewerController>(), sizeof(two::OrbitController)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::TrackballController>() { static Type ty("TrackballController", type<two::ViewerController>(), sizeof(two::TrackballController)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::OrbitControls>() { static Type ty("OrbitControls", type<two::ViewerController>(), sizeof(two::OrbitControls)); return ty; }
    template <> TWO_GFX_UI_EXPORT Type& type<two::FreeOrbitController>() { static Type ty("FreeOrbitController", type<two::OrbitController>(), sizeof(two::FreeOrbitController)); return ty; }
}

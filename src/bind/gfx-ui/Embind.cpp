#include <gfx-ui/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_gfx_ui)
{
    
    // Enums
    enum_<mud::ui::OrbitMode>("mud::ui::OrbitMode")
        .value("ThirdPerson", mud::ui::OrbitMode::ThirdPerson)
        .value("Isometric", mud::ui::OrbitMode::Isometric)
        .value("PseudoIsometric", mud::ui::OrbitMode::PseudoIsometric)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    
    // Classes
    class_<mud::Object>("Object")
        ;
    class_<mud::ViewerController>("ViewerController")
        ;
    class_<mud::OrbitController>("OrbitController")
        .property("position", &mud::OrbitController::m_position)
        .property("yaw", &mud::OrbitController::m_yaw)
        .property("pitch", &mud::OrbitController::m_pitch)
        .property("distance", &mud::OrbitController::m_distance)
        .function("set_eye", &mud::OrbitController::set_eye)
        .function("set_target", &mud::OrbitController::set_target)
        ;
    class_<mud::FreeOrbitController>("FreeOrbitController")
        ;
    class_<mud::SpaceSheet>("SpaceSheet")
        ;
    class_<mud::Viewer>("Viewer")
        .property("scene", &mud::Viewer::m_scene)
        .property("viewport", &mud::Viewer::m_viewport)
        .property("position", &mud::Viewer::m_position)
        .property("size", &mud::Viewer::m_size)
        ;
    class_<mud::SceneViewer>("SceneViewer")
        ;
    
    // Functions
    function("viewer", &mud::ui::viewer);
    function("scene_viewer", &mud::ui::scene_viewer);
    function("orbit_controller", &mud::ui::orbit_controller);
    function("free_orbit_controller", &mud::ui::free_orbit_controller);
    function("isometric_controller", &mud::ui::isometric_controller);
    function("hybrid_controller", &mud::ui::hybrid_controller);
    function("velocity_controller", &mud::ui::velocity_controller);
    
}

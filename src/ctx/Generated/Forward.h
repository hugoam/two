

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <math/Generated/Forward.h>

#if defined MUD_CTX_LIB
#define MUD_CTX_EXPORT MUD_EXPORT
#else
#define MUD_CTX_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace glm {

    
    
}

namespace json11 {

    
    
}

namespace mud {

    enum KeyCode : unsigned int;
    enum MouseButtonCode : unsigned int;
    enum class InputModifier : unsigned int;
    enum class DeviceType : unsigned int;
    enum class DeviceMask : unsigned int;
    enum class EventType : unsigned int;
    
    
    class RenderSystem;
    class Context;
    struct ModalControl;
    class ControlNode;
    struct InputEvent;
    struct MouseEvent;
    struct KeyEvent;
    struct EventBatch;
    class EventDispatcher;
    class InputDevice;
    class Keyboard;
    class MouseButton;
    class Mouse;
}

namespace mud {
namespace detail {

    
    
}
}


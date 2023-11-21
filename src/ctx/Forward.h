#pragma once

#include <infra/Config.h>

#ifndef TWO_CTX_EXPORT
#define TWO_CTX_EXPORT TWO_IMPORT
#endif

#include <stdint.h>

namespace two
{
    export_ enum class Key : uint16_t;
    export_ enum MouseButtonCode : unsigned int;
    export_ enum class InputMod : uint8_t;
    export_ enum class DeviceType : unsigned int;
    export_ enum class DeviceMask : unsigned int;
    export_ enum class EventType : unsigned int;
    
    
    export_ class RenderSystem;
    export_ class Context;
    export_ struct InputEvent;
    export_ struct MouseEvent;
    export_ struct KeyEvent;
    export_ struct ModalControl;
    export_ class ControlNode;
    export_ struct EventBatch;
    export_ class EventDispatcher;
    export_ class InputDevice;
    export_ class Keyboard;
    export_ class MouseButton;
    export_ class Mouse;
}

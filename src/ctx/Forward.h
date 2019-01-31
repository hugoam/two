#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>

#ifndef MUD_CTX_EXPORT
#define MUD_CTX_EXPORT MUD_IMPORT
#endif

#include <stdint.h>

namespace mud
{
    enum class Key : uint16_t;
    enum MouseButtonCode : unsigned int;
    enum class InputMod : uint8_t;
    enum class DeviceType : unsigned int;
    enum class DeviceMask : unsigned int;
    enum class EventType : unsigned int;
    
    
    class RenderSystem;
    class Context;
    struct InputEvent;
    struct MouseEvent;
    struct KeyEvent;
    struct ModalControl;
    class ControlNode;
    struct EventBatch;
    class EventDispatcher;
    class InputDevice;
    class Keyboard;
    class MouseButton;
    class Mouse;
}

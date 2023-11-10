-- two library
-- lua dependency

function uses_glfw()
    configuration { "osx" }
        linkoptions {
            "-framework Cocoa",
            "-framework OpenGL",
            "-framework IOKit",
            "-framework CoreVideo",
        }
           
    configuration {}
end

GLFW_DIR = path.join(TWO_3RDPARTY_DIR, "glfw")

glfw = dep(nil, "glfw", false, uses_glfw)
	kind "StaticLib"
    
    files {
        path.join(GLFW_DIR, "src/context.c"),
        path.join(GLFW_DIR, "src/init.c"),
        path.join(GLFW_DIR, "src/input.c"),
        path.join(GLFW_DIR, "src/monitor.c"),
        path.join(GLFW_DIR, "src/vulkan.c"),
        path.join(GLFW_DIR, "src/window.c"),
    }
    
    configuration { "windows" }
        files {
            path.join(GLFW_DIR, "src/win32_init.c"),
            path.join(GLFW_DIR, "src/win32_joystick.c"),
            path.join(GLFW_DIR, "src/win32_monitor.c"),
            path.join(GLFW_DIR, "src/win32_time.c"),
            path.join(GLFW_DIR, "src/win32_thread.c"),
            path.join(GLFW_DIR, "src/win32_window.c"),
            path.join(GLFW_DIR, "src/wgl_context.c"),
            path.join(GLFW_DIR, "src/egl_context.c"),
            path.join(GLFW_DIR, "src/osmesa_context.c"),
        }
        
        defines { "_GLFW_WIN32" }
        
    configuration { "vs*" }
        buildoptions {
            "/wd4204", -- warning C4204: nonstandard extension used: non-constant aggregate initializer
            "/wd4152", -- warning C4152: nonstandard extension, function/data pointer conversion in expression
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'short', possible loss of data
            "/wd4456", -- warning C4456: declaration of 'js' hides previous local declaration
            "/wd4457", -- warning C4457: declaration of 'width' hides function parameter
            "/wd4100", -- warning C4100: 'handle': unreferenced formal parameter
        }
        
    configuration { "mingw* or linux or osx" }
        buildoptions {
            "-Wno-unused-parameter",
            "-Wno-sign-compare",
            "-Wno-missing-field-initializers",
        }
        
    configuration { "osx or *-clang* or wasm*" }
        buildoptions {
            "-Wno-shadow",
        }
        
    configuration { "clang" }
        buildoptions {
            "-Wno-deprecated-declarations",
        }
        
    configuration { "linux" }
        files {
            path.join(GLFW_DIR, "src/linux_joystick.c"),
            path.join(GLFW_DIR, "src/posix_thread.c"),
            path.join(GLFW_DIR, "src/posix_time.c"),
            path.join(GLFW_DIR, "src/xkb_unicode.c"),
            path.join(GLFW_DIR, "src/egl_context.c"),
            path.join(GLFW_DIR, "src/osmesa_context.c"),
        }
        
    configuration { "linux" } -- and not wayland
        files {
            path.join(GLFW_DIR, "src/x11_init.c"),
            path.join(GLFW_DIR, "src/x11_monitor.c"),
            path.join(GLFW_DIR, "src/x11_window.c"),
            path.join(GLFW_DIR, "src/glx_context.c"),
        }
        
        defines { "_GLFW_X11" }
      
    --configuration { "wayland" }
        --files {
        --    path.join(GLFW_DIR, "src/wl_init.c"),
        --    path.join(GLFW_DIR, "src/wl_monitor.c"),
        --    path.join(GLFW_DIR, "src/wl_window.c"),
        --    path.join(GLFW_DIR, "src/wayland-pointer-constraints-unstable-v1-client-protocol.c"),
        --    path.join(GLFW_DIR, "src/wayland-relative-pointer-unstable-v1-client-protocol.c"),
        --}
        
    --configuration { __FreeBSD__ || __OpenBSD__ ||  __NetBSD__ }
        --files {
        --    path.join(GLFW_DIR, "src/x11_init.c"),
        --    path.join(GLFW_DIR, "src/x11_monitor.c"),
        --    path.join(GLFW_DIR, "src/x11_window.c"),
        --    path.join(GLFW_DIR, "src/xkb_unicode.c"),
        --    // TODO: Joystick implementation
        --    path.join(GLFW_DIR, "src/null_joystick.c"),
        --    path.join(GLFW_DIR, "src/posix_time.c"),
        --    path.join(GLFW_DIR, "src/posix_thread.c"),
        --    path.join(GLFW_DIR, "src/glx_context.c"),
        --    path.join(GLFW_DIR, "src/egl_context.c"),
        --    path.join(GLFW_DIR, "src/osmesa_context.c"),
        --}
        
        --defines { "_GLFW_X11" }
      
    configuration { "osx" }
        files {
            path.join(GLFW_DIR, "src/cocoa_init.m"),
            path.join(GLFW_DIR, "src/cocoa_joystick.m"),
            path.join(GLFW_DIR, "src/cocoa_monitor.m"),
            path.join(GLFW_DIR, "src/cocoa_window.m"),
            path.join(GLFW_DIR, "src/cocoa_time.c"),
            path.join(GLFW_DIR, "src/posix_thread.c"),
            path.join(GLFW_DIR, "src/nsgl_context.m"),
            path.join(GLFW_DIR, "src/egl_context.c"),
            path.join(GLFW_DIR, "src/osmesa_context.c"),
        }
        
        defines {
            "_GLFW_COCOA",
            "_GLFW_USE_CHDIR",    -- To chdir to the Resources subdirectory of the application bundle during glfwInit
            "_GLFW_USE_MENUBAR",  -- To create and populate the menu bar when the first window is created
            "_GLFW_USE_RETINA",   -- To have windows use the full resolution of Retina displays
        }
        
    configuration {}

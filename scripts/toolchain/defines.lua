-- two toolchain
-- defines

function two_defines()
    configuration { "osx or *-clang* or wasm*" }
        buildoptions {
            "-Wno-invalid-offsetof",
        }

    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/we4238", -- warning C4238: nonstandard extension used: class rvalue used as lvalue
        }

    configuration { "cpp-modules" }
        defines {
            "TWO_MODULES",
            "TWO_STD_MODULES",
        }

    configuration { "windows", "not wasm*" }
        defines { "TWO_PLATFORM_WINDOWS" }

    configuration { "linux" }
        defines { "TWO_PLATFORM_LINUX" }

    configuration { "osx" }
        defines { "TWO_PLATFORM_OSX" }

    configuration { "wasm*" }
        defines { "TWO_PLATFORM_EMSCRIPTEN" }

    configuration {}

    configuration { "renderer-gl" }
        defines { "TWO_RENDERER_GL" }

    configuration { "renderer-bgfx" }
        defines { "TWO_RENDERER_BGFX" }

    configuration { "context-glfw" }
        defines { "TWO_CONTEXT_GLFW" }

    configuration { "context-wasm" }
        defines { "TWO_CONTEXT_WASM" }

    configuration { "context-native" }
        defines { "TWO_CONTEXT_NATIVE" }

    configuration { "windows", "context-native" }
        defines { "TWO_CONTEXT_WINDOWS" }

    configuration { "context-ogre" }
        defines { "TWO_CONTEXT_OGRE" }

    configuration {}

    configuration { "wasm*" }
        defines { "TWO_STATIC" }

    configuration {}
end

function two_binary_config()
    targetprefix ""

    two_defines()

    configuration { "wasm*" }
        linkoptions {
            --"--memory-init-file 1",
            --"--llvm-lto 3",
        }

        linkoptions {
            "--preload-file ../../../data/interface",
            "--preload-file ../../../data/shaders",
            "--preload-file ../../../data/textures",
            "--shell-file ../../../scripts/emshell.html",
        }

        linkoptions {
            --"-s EXPORTED_FUNCTIONS=\"['_main', '_copy', '_paste']\"",
            --"-s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\"",
        }

        linkoptions {
            --"-s ALLOW_MEMORY_GROWTH=1",
            --"-s SAFE_HEAP=1",
            "-s TOTAL_MEMORY=512MB",
            "-s ALIASING_FUNCTION_POINTERS=0",
        }

        defines {
            "TWO_RESOURCE_PATH=\"/data/\"",
        }

    configuration { "wasm*", "not webgpu" }
        linkoptions {
            "-s USE_WEBGL2=1",
        }

    configuration { "wasm*", "webgpu" }
        linkoptions {
            "-s USE_WEBGPU=1",
        }

    configuration { "not osx", "not wasm*" }
        defines {
            "TWO_RESOURCE_PATH=\"" .. path.join(TWO_DIR, "data") .. "\"",
        }

    configuration { "osx", "not wasm*" }
        defines {
            "TWO_RESOURCE_PATH=\\\"" .. path.join(TWO_DIR, "data") .. "\\\"",
        }

    configuration {}
end

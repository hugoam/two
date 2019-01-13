-- mud toolchain
-- defines

function mud_defines()
    configuration { "cpp-modules" }
        defines {
            "MUD_NO_GLM",
            "MUD_CPP_20",
            "MUD_MODULES",
        }
        
    configuration { "windows", "not asmjs" }
        defines { "MUD_PLATFORM_WINDOWS" }
        
    configuration { "linux" }
        defines { "MUD_PLATFORM_LINUX" }

    configuration { "osx" }
        defines { "MUD_PLATFORM_OSX" }
        
    configuration { "asmjs" }
        defines { "MUD_PLATFORM_EMSCRIPTEN" }
        
    configuration {}
  
    configuration { "renderer-gl" }
        defines { "MUD_RENDERER_GL" }
        
    configuration { "renderer-bgfx" }
        defines { "MUD_RENDERER_BGFX" }
        
    configuration { "context-glfw" }
        defines { "MUD_CONTEXT_GLFW" }
            
    configuration { "context-wasm" }
        defines { "MUD_CONTEXT_WASM" }
        
    configuration { "context-native" }
        defines { "MUD_CONTEXT_NATIVE" }
        
    configuration { "windows and context-native" }
        defines { "MUD_CONTEXT_WINDOWS" }
        
    configuration { "context-ogre" }
        defines { "MUD_CONTEXT_OGRE" }
        
    configuration {}
        
    configuration { "asmjs" }
        defines { "MUD_STATIC" }
            
    configuration { "webgl2" }
        defines { "MUD_WEBGL2" }
            
    configuration {}
end

function mud_binary_config()
    targetprefix ""
    
    mud_defines()
    
    configuration { "asmjs" }
        linkoptions {
            "--memory-init-file 1",
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
            "-s ALLOW_MEMORY_GROWTH=1",
            "-s ALIASING_FUNCTION_POINTERS=0",
        }
        
    configuration { "asmjs", "webgl2" }
        linkoptions {
            "-s USE_WEBGL2=1",
        }

    configuration { "not osx", "not asmjs" }
        defines {
            "MUD_RESOURCE_PATH=\"" .. path.join(PROJECT_DIR, "data") .. "/\"",
        }

    configuration { "osx", "not asmjs" }
        defines {
            "MUD_RESOURCE_PATH=\\\"" .. path.join(PROJECT_DIR, "data") .. "/\\\"",
        }

    configuration {}
end

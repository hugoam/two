-- mud library

group "3rdparty"
dofile(path.join(MUD_DIR, "scripts/3rdparty/lua.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/glfw.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/bgfx.lua"))

group "lib"

if _OPTIONS["mud-libs"] then
    group "lib/mud"
    dofile(path.join(MUD_DIR, "scripts/mud_obj.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_math.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_lang.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_gen.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_util.lua"))
    --dofile(path.join(MUD_DIR, "scripts/mud_db.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_ctx.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_ui.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_uio.lua"))
    dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))
    group "lib"
else
    project "mud"
        kind "SharedLib"
        
        includedirs {
            path.join(MUD_SRC_DIR),
            path.join(MUD_3RDPARTY_DIR, "glm"),
            path.join(MUD_3RDPARTY_DIR, "stb"),
            path.join(MUD_3RDPARTY_DIR, "rectpacking"),
            path.join(MUD_3RDPARTY_DIR, "json", "src"),
            path.join(MUD_3RDPARTY_DIR, "mikkt"),
            path.join(MUD_3RDPARTY_DIR, "lua"),
            path.join(MUD_3RDPARTY_DIR, "sqlite3"),
            path.join(MUD_3RDPARTY_DIR, "FastNoise"),
            path.join(MUD_3RDPARTY_DIR, "base64"),
        }
        
        mud_module("obj",  MUD_SRC_DIR, "obj",  "MUD_OBJ")
        mud_module("math", MUD_SRC_DIR, "math", "MUD_MATH")
        mud_module("geom", MUD_SRC_DIR, "geom", "MUD_GEOM")
        mud_module("lang", MUD_SRC_DIR, "lang", "MUD_LANG")
        mud_module("ctx",  MUD_SRC_DIR, "ctx",  "MUD_CTX")
        mud_module("ui",   MUD_SRC_DIR, "ui",   "MUD_UI")
        mud_module("uio",  MUD_SRC_DIR, "uio",  "MUD_UIO")
        
        files {
            path.join(MUD_SRC_DIR, "mud",    "**.h"),
            --path.join(MUD_SRC_DIR, "mud",    "**.cpp"),
            path.join(MUD_3RDPARTY_DIR, "rectpacking", "**.cpp"),
            path.join(MUD_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
        }
        
        removefiles {
            path.join(MUD_UI_DIR, "Backend/**.h"),
            path.join(MUD_UI_DIR, "Backend/**.cpp"),
        }
        
        --defines { "MUD_UI_DRAW_CACHE" }
        
        links {
            "lua",
        }
        
        if _OPTIONS["sound"] then
            includedirs {
                path.join(MUD_3RDPARTY_DIR, "vorbis", "include"),
                path.join(MUD_3RDPARTY_DIR, "ogg", "include"),
            }

            links{
                "vorbis",
                "vorbisfile",
                "ogg",
                "OpenAL32",
            }
            
            mud_module("snd", MUD_SRC_DIR, "snd", "MUD_SND")
        end
end
    
function uses_mud()
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "stb"),
        path.join(MUD_3RDPARTY_DIR, "json/src"),
        path.join(MUD_3RDPARTY_DIR, "FastNoise"),
    }
    
    if project().name ~= "mud" then
        links { "mud" }
    end
    
end

function mud_binary(name)
    targetprefix ""
    
    defines { "_" .. name:upper() .. "_EXE" }
        
    configuration { "context-glfw", "not asmjs" }
        links {
            "glfw",
        }
    
    configuration { "asmjs" }
        linkoptions {
            "--separate-asm",
            "--memory-init-file 1",
            --"--llvm-lto 3",
        }
        
        linkoptions {
            "--preload-file ../../../data/interface",
            "--preload-file ../../../data/shaders",
            "--preload-file ../../../data/textures",
            "--shell-file ../../../scripts/emshell.html",
        }
            
    configuration { "asmjs", "context-glfw" }
        linkoptions {
            "-s USE_GLFW=3",
        }
        
    configuration { "asmjs", "webgl2" }
        linkoptions {
            "-s USE_WEBGL2=1",
        }
        
    configuration { "asmjs", "Debug" }
        linkoptions {
            --"-s TOTAL_MEMORY=268435456",
            "-s TOTAL_MEMORY=536870912",
            --"-s ALLOW_MEMORY_GROWTH=1",
        }
        
    configuration { "asmjs", "Release" }
        linkoptions {
            "-s WASM=1",
            "-s ALLOW_MEMORY_GROWTH=1",
            "-s ALIASING_FUNCTION_POINTERS=0",
        }
        
    configuration { "not linux", "not asmjs" }
        defines {
            "MUD_RESOURCE_PATH=\"" .. path.join(PROJECT_DIR, "data") .. "/\"",
        }

    configuration { "linux", "not asmjs" }
        defines {
            "MUD_RESOURCE_PATH=\\\"" .. path.join(PROJECT_DIR, "data") .. "/\\\"",
        }

    configuration {}
end

function mud_shell(name)
    mud_binary(name)
    
    files {
        path.join(MUD_DIR, "src", "mud", "Shell.cpp"),
    }
end

if _OPTIONS["renderer-gl"] then
    dofile(path.join(MUD_DIR, "scripts/mud_gl.lua"))
elseif _OPTIONS["renderer-bgfx"] then
    dofile(path.join(MUD_DIR, "scripts/mud_gfx.lua"))
end

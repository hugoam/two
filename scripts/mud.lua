-- mud library

if _OPTIONS["cpp-modules"] then
    dofile(path.join(MUD_DIR, "scripts/3rdparty/std.lua"))
end

group "3rdparty"
dofile(path.join(MUD_DIR, "scripts/3rdparty/json11.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/stb.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/lua.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/glfw.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/vg.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/bgfx.lua"))


dofile(path.join(MUD_DIR, "scripts/mud_obj.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_srlz.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_math.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_geom.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_lang.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_ctx.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_ui.lua"))
dofile(path.join(MUD_DIR, "scripts/mud_uio.lua"))

--dofile(path.join(MUD_DIR, "scripts/mud_bgfx.lua"))
--dofile(path.join(MUD_DIR, "scripts/mud_db.lua"))
--dofile(path.join(MUD_DIR, "scripts/mud_gen.lua"))
--dofile(path.join(MUD_DIR, "scripts/mud_util.lua"))

group "lib"

mud = {}

if _OPTIONS["as-libs"] then
    group "lib/mud"
        mud_obj(true)
        mud_srlz(true)
        mud_math(true)
        mud_geom(true)
        mud_lang(true)
        mud_ctx(true)
        mud_ui(true)
        mud_uio(true)
    group "lib"
else
    project "mud"
        kind "SharedLib"
        
        includedirs {
            path.join(MUD_3RDPARTY_DIR, "stb"),
        }
        
        mud_obj(false)
        mud_srlz(false)
        mud_math(false)
        mud_geom(false)
        mud_lang(false)
        mud_ctx(false)
        mud_ui(false)
        mud_uio(false)
        
        files {
            path.join(MUD_SRC_DIR, "mud", "**.h"),
        }
        
        --defines { "MUD_UI_DRAW_CACHE" }
        
        if _OPTIONS["sound"] then
            mud_snd(false)
        end  
end
    
function uses_mud()
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
    
    if _OPTIONS["as-libs"] then
        links { "mud_obj", "mud_srlz", "mud_math", "mud_geom", "mud_lang", "mud_ctx", "mud_ui", "mud_uio" }
    else
        links { "mud" }
    end
end

function mud_binary(name)
    targetprefix ""
    
    mud_defines()
    
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
    mud_defines()
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

-- mud library
-- bgfx dependency module

group "bgfx"

dofile(path.join(BX_DIR, "scripts/bx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))
dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))
bgfxProject("", "StaticLib", {})

project "bgfx"
    configuration { "Debug" }
        defines {
            "BGFX_CONFIG_DEBUG_UNIFORM=0",
        }
        
    configuration { "not asmjs",  }
        --defines {
        --    "BGFX_CONFIG_RENDERER_OPENGL=33",
        --}
        
    configuration { "asmjs", "webgl2" }
        defines {
            "BGFX_CONFIG_RENDERER_OPENGLES=30",
        }
        
    configuration {}

dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/shaderc.lua"))

function uses_bx()
    includedirs {
        path.join(BX_DIR,    "include"),
    }
end

function uses_bimg()
    includedirs {
        path.join(BIMG_DIR,  "include"),
    }
end

function uses_bgfx()
    includedirs {
        path.join(BGFX_DIR,  "include"),
    }
    
    configuration { "linux" }
        links {
            "X11",
            "GLU",
            "GL",
            "Xext",
        }
    
    configuration { "vs20*", "not asmjs" }
        links {
            "psapi",
        }
    
    configuration { "osx or linux*" }
        links {
            "pthread",
        }
    
    configuration {}
end

function uses_shaderc()
    defines { "MUD_LIVE_SHADER_COMPILER" }
        
    links {
        "fcpp",
        "glslang",
        "glsl-optimizer",
        "spirv-opt",
    }
end

bx          = mud_dep(nil, "bx",            false, uses_bx)
bimg        = mud_dep(nil, "bimg",          false, uses_bimg)
bimg.decode = mud_dep(nil, "bimg_decode",   false, uses_bimg)
bgfx        = mud_dep(nil, "bgfx",          false, uses_bgfx,   { bx })
shaderc     = mud_dep(nil, "shaderc",       false, uses_shaderc)
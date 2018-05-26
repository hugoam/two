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

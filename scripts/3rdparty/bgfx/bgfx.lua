-- mud library
-- bgfx dependency module

group "bgfx"

dofile(path.join(BX_DIR, "scripts/bx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_encode.lua"))
dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))
bgfxProject("", "StaticLib", {})

project "bgfx"
    configuration { "Debug" }
        defines {
            "BGFX_CONFIG_DEBUG_UNIFORM=0",
        }
        
    configuration { "osx",  }
        defines {
            "BGFX_CONFIG_RENDERER_OPENGL=31",
        }
        
    configuration { "asmjs", "webgl2" }
        defines {
            "BGFX_CONFIG_RENDERER_OPENGLES=30",
        }
        
    configuration {}

project "bimg_encode"
	configuration { "mingw* or linux or osx or asmjs" }
		buildoptions {
			"-Wno-undef"
        }
        
    configuration {}
        
dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/shaderc.lua"))

function uses_bx()
    includedirs {
        path.join(BX_DIR,    "include"),
    }
    
	configuration { "vs*", "not orbis", "not asmjs" }
		includedirs { path.join(BX_DIR, "include/compat/msvc") }
    
    configuration {}
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
    
    configuration { "linux", "not asmjs" }
        links {
            "X11",
            "GLU",
            "GL",
            "Xext",
        }
    
    configuration { "osx" }
        linkoptions {
            "-framework Metal",
            "-framework QuartzCore",
        }
        
    configuration { "vs20*", "not asmjs" }
        links {
            "psapi",
        }
    
    configuration { "osx or linux*", "not asmjs" }
        links {
            "pthread",
        }
    
    configuration {}
end

function uses_shaderc()
    defines { "MUD_LIVE_SHADER_COMPILER" }
    
    --print(" links fcpp, glslang, etc...")
    links {
        "fcpp",
        "glslang",
        "glsl-optimizer",
        "spirv-opt",
    }
end

--fcpp        = mud_dep(nil, "fcpp",          false, nil)
--glslang     = mud_dep(nil, "glslang",       false, nil)
--glslopt     = mud_dep(nil, "glsl-optimizer",false, nil)
--spirvopt    = mud_dep(nil, "fcpp",          false, nil)

bx          = mud_dep(nil, "bx",            false, uses_bx)
bimg        = mud_dep(nil, "bimg",          false, uses_bimg,       { bx })
bimg.decode = mud_dep(nil, "bimg_decode",   false, uses_bimg        { bx })
bimg.encode = mud_dep(nil, "bimg_encode",   false, uses_bimg        { bx })
bgfx        = mud_dep(nil, "bgfx",          false, uses_bgfx,       { bx, bimg })
shaderc     = mud_dep(nil, "shaderc",       false, uses_shaderc,    { bx, bimg, bgfx })

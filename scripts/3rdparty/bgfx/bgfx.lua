-- two library
-- bgfx dependency module

group "bgfx"

dofile(path.join(BX_DIR, "scripts/bx.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_decode.lua"))
dofile(path.join(BIMG_DIR, "scripts/bimg_encode.lua"))
dofile(path.join(BGFX_DIR, "scripts/bgfx.lua"))
bgfxProject("", "StaticLib", {})

if _OPTIONS["webgpu"] then
project "bgfx"
    includedirs {
        path.join(DAWN_DIR, "src"),
        path.join(DAWN_DIR, "src/include"),
        path.join(DAWN_DIR, "out/Default/gen")
    }
    
    defines {
        "BGFX_CONFIG_RENDERER_WEBGPU=1",
    }
end

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
            "-Wno-undef",
            "-Wno-class-memaccess",
        }

    configuration { "osx or *-clang* or asmjs" }
        buildoptions {
            "-Wno-shadow",
            "-Wno-macro-redefined",
            "-Wno-tautological-compare",
        }

    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'vtype', possible loss of data
        }

    configuration {}

dofile(path.join(TWO_DIR, "scripts/3rdparty/bgfx/shaderc.lua"))

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
        path.join(BX_DIR,    "include"),
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
    defines { "TWO_LIVE_SHADER_COMPILER" }
    
    --print(" links fcpp, glslang, etc...")
    links {
        "fcpp",
        "glslang",
        "glsl-optimizer",
        "spirv-opt",
        "spirv-cross",
    }
end

--fcpp        = dep(nil, "fcpp",          false, nil)
--glslang     = dep(nil, "glslang",       false, nil)
--glslopt     = dep(nil, "glsl-optimizer",false, nil)
--spirvopt    = dep(nil, "fcpp",          false, nil)

bx          = dep(nil, "bx",            false, uses_bx)
bimg        = dep(nil, "bimg",          false, uses_bimg,       { bx })
bimg.decode = dep(nil, "bimg_decode",   false, uses_bimg        { bx })
bimg.encode = dep(nil, "bimg_encode",   false, uses_bimg        { bx })
bgfx        = dep(nil, "bgfx",          false, uses_bgfx,       { bx, bimg })
shaderc     = dep(nil, "shaderc",       false, uses_shaderc,    { bx, bimg, bgfx })

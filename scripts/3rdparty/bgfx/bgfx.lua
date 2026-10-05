-- two library
-- bgfx dependency module

if _OPTIONS["webgpu"] then
    _OPTIONS["with-webgpu"] = ""
end

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

    configuration { "wasm*" }
        defines {
            "BGFX_CONFIG_RENDERER_OPENGL=0",
            "BGFX_CONFIG_RENDERER_OPENGLES=0",
        }

    configuration {}
end

project "bgfx"
    defines {
      --"BGFX_CONFIG_RENDERER_OPENGL=31",
      --"BGFX_CONFIG_RENDERER_OPENGL=46",
    }
    configuration { "Debug" }
        defines {
            "BGFX_CONFIG_DEBUG_UNIFORM=0",
        }

    configuration { "osx" }
        defines {
            "BGFX_CONFIG_RENDERER_OPENGL=31",
        }

    -- the bgfx script only sets up the DirectX headers for the vs and mingw toolchains
    configuration { "windows-clang" }
        includedirs {
            path.join(BGFX_DIR, "3rdparty/directx-headers/include/directx"),
        }

if not _OPTIONS["webgpu"] then
    configuration { "wasm*" }
        defines {
            "BGFX_CONFIG_RENDERER_OPENGLES=30",
        }
end

    configuration {}

project "bimg_encode"
    configuration { "wasm*" }
        buildoptions {
            "-Wno-fortify-source",
            "-Wno-deprecated-copy",
        }

    configuration { "mingw* or linux or osx or wasm*" }
        buildoptions {
            "-Wno-undef",
            --"-Wno-class-memaccess",
        }

    configuration { "osx or *-clang* or wasm*" }
        buildoptions {
            "-Wno-shadow",
            "-Wno-macro-redefined",
            "-Wno-tautological-compare",
        }

    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'vtype', possible loss of data
        }

    configuration {}

dofile(path.join(TWO_DIR, "scripts/3rdparty/bgfx/shaderc.lua"))

function uses_bx()
    -- it's redundant with some of this function the link bx part but I think this is OK
    using_bx()

    includedirs {
        path.join(BX_DIR,    "include"),
    }
    
    configuration { "vs*", "not orbis", "not wasm*" }
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

    if _OPTIONS["webgpu"] then
        usesWebGPU()
    end

    configuration { "linux", "not wasm*" }
        links {
            "X11",
            "GL",
            "Xext",
        }
    
    configuration { "osx" }
        linkoptions {
            "-framework Metal",
            "-framework QuartzCore",
        }
        
    configuration { "vs20*", "not wasm*" }
        links {
            "psapi",
        }
    
    configuration { "osx or linux*", "not wasm*" }
        links {
            "pthread",
        }
    
    configuration {}
end

function uses_shaderc()
    defines { "TWO_LIVE_SHADER_COMPILER" }
    
	links {
		"glslang",
		"spirv-opt",
		"spirv-cross",
		"tint-api",
		"tint-lang",
		"tint-core",
	}
end

glslang     = dep(nil, "glslang",       false, nil)
spirvopt    = dep(nil, "spirv-opt",     false, nil)
spirvcross  = dep(nil, "spirv-cross",   false, nil)
tintapi     = dep(nil, "tint-api",      false, nil)
tintlang    = dep(nil, "tint-lang",     false, nil)
tintcore    = dep(nil, "tint-core",     false, nil)

bimg        = dep(nil, "bimg",          false, uses_bimg,       { bx })
bimg.decode = dep(nil, "bimg_decode",   false, uses_bimg        { bx })
bimg.encode = dep(nil, "bimg_encode",   false, uses_bimg        { bx })
bgfx        = dep(nil, "bgfx",          false, uses_bgfx,       { bx, bimg })
shaderc     = dep(nil, "shaderc",       false, uses_shaderc,    { bx, bimg, bgfx })

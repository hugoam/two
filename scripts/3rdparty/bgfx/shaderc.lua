
--dofile(path.join(BGFX_DIR, "scripts/shaderc.lua"))
dofile(path.join(MUD_DIR, "scripts/3rdparty/bgfx/shaderc_bgfx.lua"))

project "glsl-optimizer"
    configuration { "asmjs" }
        defines {
            "HAVE___BUILTIN_FFS",
            "HAVE___BUILTIN_FFSLL",
        }

    configuration {}
    
    
project "shaderc"
	kind "StaticLib"

	links {
		"bx",
		"bimg",
        "bgfx",
	}
    
    files {
        path.join(MUD_DIR, "scripts/3rdparty/bgfx/shaderc_spirv.cpp"),
        path.join(MUD_DIR, "scripts/3rdparty/bgfx/shaderc.cpp"),
        path.join(MUD_DIR, "scripts/3rdparty/bgfx/shaderc.h"),
    }
    
    removefiles {
        path.join(BGFX_DIR, "tools/shaderc/shaderc_spirv.cpp"),
        path.join(BGFX_DIR, "tools/shaderc/shaderc.cpp"),
        path.join(BGFX_DIR, "tools/shaderc/shaderc.h"),
        path.join(BGFX_DIR, "src/**.h"),
        path.join(BGFX_DIR, "src/**.cpp"),
    }
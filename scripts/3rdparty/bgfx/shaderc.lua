
--dofile(path.join(BGFX_DIR, "scripts/shaderc.lua"))
dofile(path.join(TWO_DIR, "scripts/3rdparty/bgfx/shaderc_bgfx.lua"))

project "glslang"
    removeflags { "Cpp17" }
    flags       { "Cpp14" }

    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/wd4267", -- warning C (used as a base class to provide typedefs) is deprecated in C++17.
        }

project "spirv-opt"
    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/wd4996", -- warning C4996: warning STL4015: The std::iterator class template (used as a base class to provide typedefs) is deprecated in C++17.
        }

    configuration {}
    
project "shaderc"
    kind "StaticLib"

    links {
        "bx",
        "bimg",
        "bgfx",
    }

    removefiles {
        path.join(BGFX_DIR, "src/**.h"),
        path.join(BGFX_DIR, "src/**.cpp"),
    }
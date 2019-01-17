-- mud library
-- masked occlusion culling 3rdparty module

function uses_culling()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "culling"),
    }
end

culling = mud_dep(nil, "culling", false, uses_culling)
    kind "StaticLib"

    includedirs {
        path.join(MUD_3RDPARTY_DIR, "culling"),
    }

    files {
        path.join(MUD_3RDPARTY_DIR, "culling", "*.cpp"),
        --path.join(MUD_3RDPARTY_DIR, "culling", "MaskedOcclusionCulling.cpp"),
    }

    configuration { "asmjs" }
        removeflags {
            "OptimizeSpeed", -- emscripten SIMD bug
        }

    configuration { "mingw* or linux or osx or asmjs" }
        buildoptions {
            "-mssse3"
        }

    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4100", -- warning C4100: unreferenced formal parameter
            "/wd4005", -- warning C4005: macro redefinition
            "/wd4127", -- warning C4127: conditional expression is constant
            "/wd4456", -- warning C4456: declaration hides previous local declaration
            "/wd4245", -- warning C4245: conversion from 'int' to 'unsigned int', signed/unsigned mismatch
            "/wd4310", -- warning C4310: cast truncates constant value
        }

    configuration {}

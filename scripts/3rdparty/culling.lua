-- two library
-- masked occlusion culling 3rdparty module

function uses_culling()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "culling"),
    }
end

function culling_config()
    kind "StaticLib"

    includedirs {
        path.join(TWO_3RDPARTY_DIR, "culling"),
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
end

cullingavx2 = two_dep(nil, "cullingavx2", false, uses_culling)
    culling_config()
    
    files {
        path.join(TWO_3RDPARTY_DIR, "culling", "MaskedOcclusionCullingAVX2.cpp"),
    }

    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/arch:AVX2",
        }
        
    configuration {}
        
cullingavx512 = two_dep(nil, "cullingavx512", false, uses_culling)
    culling_config()
    
    files {
        path.join(TWO_3RDPARTY_DIR, "culling", "MaskedOcclusionCullingAVX512.cpp"),
    }

    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/arch:AVX2",
        }
        
    configuration {}
    
culling = two_dep(nil, "culling", false, uses_culling, { cullingavx2, cullingavx512 })
    culling_config()
    
    files {
        path.join(TWO_3RDPARTY_DIR, "culling", "MaskedOcclusionCulling.cpp"),
    }

-- two library
-- xatlas 3rdparty module

xatlas = two_dep(nil, "xatlas")
	kind "StaticLib"
    
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "xatlas"),
    }

    files {
        path.join(TWO_3RDPARTY_DIR, "xatlas", "xatlas.cpp"),
    }

    configuration { "mingw* or linux or osx or asmjs" }
        buildoptions {
            "-Wno-sign-compare",
            "-Wno-reorder",
            "-Wno-unused-function",
            "-Wno-shadow",
        }
        
        buildoptions {
            "-Wno-type-limits",
        }
        
    configuration { "osx or *-clang* or asmjs" }
        buildoptions {
            "-Wno-macro-redefined", -- for __STDC_LIMIT_MACROS, we can't touch the source and don't want to touch the toolchain
            "-Wno-tautological-compare",
        }
        
    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4005", -- warning C4005: '__STDC_LIMIT_MACROS': macro redefinition
            "/wd4267", -- warning C4267: 'argument': conversion from 'size_t' to 'uint32_t', possible loss of data
            "/wd4244", -- warning C4244: 'initializing': conversion from '__int64' to 'uint32_t', possible loss of data
            "/wd4245", -- warning C4245: 'argument': conversion from 'int' to 'const T', signed/unsigned mismatch
            "/wd4456", -- warning C4456: declaration of 'i' hides previous local declaration
            "/wd4505", -- warning C4505: unreferenced local function has been removed
            "/wd4701", -- warning C4701: potentially uninitialized local variable 'warning' used
        }

    configuration {}

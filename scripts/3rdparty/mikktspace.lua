-- two library
-- mikktspace 3rdparty module

mikktspace = dep(nil, "mikktspace")
    kind "StaticLib"
    
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "mikkt"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
    }
    
    configuration { "osx or *-clang* or wasm*" }
        buildoptions {
            "-Wno-shadow",
        }

    configuration { "vs*", "not wasm*" }
        buildoptions {
            "/wd4204", -- warning C4204: nonstandard extension used: non-constant aggregate initializer
            "/wd4456", -- warning C4456: declaration of 'i' hides previous local declaration
        }
        
    configuration {}

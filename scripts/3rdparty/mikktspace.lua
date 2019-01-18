-- mud library
-- mikktspace 3rdparty module

mikktspace = mud_dep(nil, "mikktspace")
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "mikkt"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
    }
    
    configuration { "osx or *-clang* or asmjs" }
        buildoptions {
            "-Wno-shadow",
        }

    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4204", -- warning C4204: nonstandard extension used: non-constant aggregate initializer
            "/wd4456", -- warning C4456: declaration of 'i' hides previous local declaration
        }
        
    configuration {}

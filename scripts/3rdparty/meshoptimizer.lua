-- mud library
-- meshopt 3rdparty module

meshopt = mud_dep(nil, "meshopt")
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "meshoptimizer", "src"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "meshoptimizer", "src/**.cpp"),
    }

    configuration {}

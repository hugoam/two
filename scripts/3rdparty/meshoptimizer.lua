-- two library
-- meshopt 3rdparty module

meshopt = dep(nil, "meshopt")
    kind "StaticLib"
    
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "meshoptimizer", "src"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "meshoptimizer", "src/**.cpp"),
    }

    configuration {}

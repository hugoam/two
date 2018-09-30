-- mud library
-- tracy 3rdparty module

tracy = mud_dep(nil, "tracy")
	kind "StaticLib"
    
	includedirs {
        path.join(MUD_3RDPARTY_DIR, "tracy"),
	}

	files {
        path.join(MUD_3RDPARTY_DIR, "tracy", "TracyClient.hpp"),
        path.join(MUD_3RDPARTY_DIR, "tracy", "TracyClient.cpp"),
	}
    
    configuration { "not osx" } -- kludge: disabling for OSX until we fix compile errors and add a proper profiling build option
        defines { "TRACY_ENABLE" }

    configuration {}
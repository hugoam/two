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
    
    defines { "TRACY_ENABLE" }

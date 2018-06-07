-- mud library
-- json11 3rdparty module

json11 = mud_dep(nil, "json11", true)
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "json11", "json11.h"),
        path.join(MUD_SRC_DIR, "3rdparty", "json11.cpp"),
        path.join(MUD_SRC_DIR, "3rdparty", "json11.mxx"),
    }
    
    mud_mxx({ path.join(MUD_SRC_DIR, "3rdparty", "json11.cpp") }, json11)

-- mud library
-- mud srlz module

project "json11"
    kind "StaticLib"
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "json11", "json11.cpp"),
        path.join(MUD_SRC_DIR, "3rdparty", "json11.mxx"),
        path.join(MUD_SRC_DIR, "3rdparty", "json11.cppm"),
    }
    
function mud_srlz(as_project)
    mud_module(as_project, "mud", "srlz", MUD_SRC_DIR, "srlz")
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    links {
        "json11",
    }
end


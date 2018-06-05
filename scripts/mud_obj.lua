-- mud library
-- mud obj module

function mud_obj(as_project)
    mud_module(as_project, "mud", "obj", MUD_SRC_DIR, "obj")
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    files {
        path.join(MUD_SRC_DIR, "3rdparty", "json11.cpp"),
    }
end


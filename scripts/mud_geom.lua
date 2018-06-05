-- mud library
-- mud geom module

function mud_geom(as_project)
    mud_module(as_project, "mud", "geom", MUD_SRC_DIR, "geom", { "obj", "math" })

    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "mikkt"),
    }
    
    files {
        path.join(MUD_3RDPARTY_DIR, "mikkt", "mikktspace.c"),
    }
end

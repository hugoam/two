-- mud library
-- mud uio module

function mud_uio(as_project)
    mud_module(as_project, "mud", "uio", MUD_SRC_DIR, "uio", { "obj", "math", "lang", "ctx", "ui" })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
end

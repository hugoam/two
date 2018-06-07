-- mud library
-- mud math module

function mud_math(as_project)
    mud.math = mud_module(as_project, "mud", "math", MUD_SRC_DIR, "math", { json11, mud.obj, mud.srlz })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

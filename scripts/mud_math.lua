-- mud library
-- mud math module

function mud_math(as_project)
    mud_module(as_project, "mud", "math", MUD_SRC_DIR, "math", { "obj" })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    --local name = project().name
    --usage(name)
    --    includedirs {
    --        path.join(MUD_3RDPARTY_DIR, "glm"),
    --    }
    --usage()
end

-- mud library
-- mud ctx module

function mud_ctx(as_project)
    mud.ctx = mud_module(as_project, "mud", "ctx", MUD_SRC_DIR, "ctx", { mud.obj, mud.math })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
end

-- mud library
-- mud uio module

function mud_uio(as_project)
    mud.uio = mud_module(as_project, "mud", "uio", MUD_SRC_DIR, "uio", { mud.obj, mud.math, mud.lang, mud.ctx, mud.ui })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
    }
end

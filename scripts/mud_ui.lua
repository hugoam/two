-- mud library
-- mud ui module

function mud_ui(as_project)
    mud.ui = mud_module(as_project, "mud", "ui", MUD_SRC_DIR, "ui", { json11, stb.image, stb.rect_pack, mud.obj, mud.srlz, mud.math, mud.ctx })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "stb"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end

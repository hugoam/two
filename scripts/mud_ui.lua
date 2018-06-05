-- mud library
-- mud ui module

function mud_ui(as_project)
    mud_module(as_project, "mud", "ui", MUD_SRC_DIR, "ui", { "obj", "math", "ctx" })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "stb"),
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
    
    files {
        path.join(MUD_SRC_DIR, "3rdparty", "stb_image.cpp"),
        path.join(MUD_SRC_DIR, "3rdparty", "stb_rect_pack.cpp"),
    }
end

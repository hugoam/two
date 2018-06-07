-- mud library
-- mud lang module

function mud_lang(as_project)
    mud.lang = mud_module(as_project, "mud", "lang", MUD_SRC_DIR, "lang", { lua, mud.obj })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "lua"),
    }
end

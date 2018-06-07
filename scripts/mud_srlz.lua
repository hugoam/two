-- mud library
-- mud srlz module

function mud_srlz(as_project)
    mud.srlz = mud_module(as_project, "mud", "srlz", MUD_SRC_DIR, "srlz", { json11, mud.obj })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "json11"),
    }
end


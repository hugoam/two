-- mud library
-- mud snd module

function mud_snd(as_project)
    mud.snd = mud_module(as_project, "mud", "snd", MUD_SRC_DIR, "snd", { mud.obj })
    
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "vorbis", "include"),
        path.join(MUD_3RDPARTY_DIR, "ogg", "include"),
        path.join(MUD_DIR, "scripts/3rdparty/ogg/"),
    }
    
    links {
		"vorbis",
		"vorbisfile",
		"ogg",
        "OpenAL32",
	}
end

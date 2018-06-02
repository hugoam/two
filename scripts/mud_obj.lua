-- mud library
-- mud obj module

project "mud_obj"
	kind "SharedLib"

	includedirs {
		path.join(MUD_SRC_DIR),
        path.join(MUD_3RDPARTY_DIR, "json11"),
	}

	files {
		path.join(MUD_OBJ_DIR, "**.h"),
		path.join(MUD_OBJ_DIR, "**.cpp"),
		path.join(MUD_OBJ_DIR, "Metagen/*.py"),
		path.join(MUD_OBJ_DIR, "Metagen/*.mako"),
	}

    defines { "MUD_OBJ_LIB" }


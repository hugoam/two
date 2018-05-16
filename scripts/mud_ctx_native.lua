-- mud library
-- mud ctx native module

project "mud_ctx_native"
	kind "StaticLib"

    mud_module("ctx-win", MUD_SRC_DIR, "ctx-win", "MUD_CTX_WIN")        
    uses_mud()
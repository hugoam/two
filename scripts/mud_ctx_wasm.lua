-- mud library
-- mud ctx wasm module

project "mud_ctx_wasm"
	kind "StaticLib"
    
    mud_module("ctx-wasm", MUD_SRC_DIR, "ctx-wasm", "MUD_CTX_WASM")
    uses_mud()
    
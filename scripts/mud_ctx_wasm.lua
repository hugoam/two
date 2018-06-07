-- mud library
-- mud ctx wasm module

function mud_ctx_backend(parent)
    mud.ctxbackend = mud_module(false, "mud", "ctx-wasm", MUD_SRC_DIR, "ctx-wasm", { mud.ctx })
    table.insert(parent.deps, mud.ctxbackend)
end

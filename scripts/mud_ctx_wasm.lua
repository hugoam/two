-- mud library
-- mud ctx wasm module

mud.ctx.wasm = mud_module("mud", "ctx-wasm", MUD_SRC_DIR, "ctx-wasm", nil, nil, false, { mud.math, mud.ctx })

function mud_ctx_backend()
    return mud.ctx.wasm
end

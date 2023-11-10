-- two library
-- two ctx wasm module

two.ctx.wasm = module("two", "ctx-wasm", TWO_SRC_DIR, "ctx-wasm", nil, nil, false, { two.math, two.ctx })

function two_ctx_backend()
    return two.ctx.wasm
end

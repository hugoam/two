-- two library
-- bx dependency module

dofile(path.join(BX_DIR, "scripts/bx.lua"))

function uses_bx()
    -- it's redundant with some of this function the link bx part but I think this is OK
    using_bx()

    includedirs {
        path.join(BX_DIR,    "include"),
    }
    
    configuration { "vs*", "not orbis", "not wasm*" }
        includedirs { path.join(BX_DIR, "include/compat/msvc") }
    
    configuration {}
end

bx = dep(nil, "bx", false, uses_bx)

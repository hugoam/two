-- two library
-- stb 3rdparty module

function stb_module(name)
local m = two_dep('stb', name, true)
    kind "StaticLib"
    
    includedirs {
        path.join(TWO_SRC_DIR),
        path.join(TWO_3RDPARTY_DIR, "stb"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "stb", "stb_" .. name .. ".h"),
        path.join(TWO_SRC_DIR, "3rdparty", "stb_" .. name .. ".cpp"),
        path.join(TWO_SRC_DIR, "3rdparty", "stb." .. name .. ".mxx"),
    }
        
    two_mxx({ path.join(TWO_SRC_DIR, "3rdparty", "stb_" .. name .. ".cpp") }, m)
    
    configuration { "*-gcc*" }
        buildoptions {
            "-Wno-unused-but-set-variable",
            "-Wno-type-limits",
        }
    
    return m
end

stb = {}
stb.image     = stb_module("image")
stb.rect_pack = stb_module("rect_pack")

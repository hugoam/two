-- two library
-- stb 3rdparty module

function stb_module(name, cppmodule)
local m = dep('stb', name, cppmodule)
    kind "StaticLib"
    
    includedirs {
        path.join(TWO_SRC_DIR),
        path.join(TWO_3RDPARTY_DIR, "stb"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "stb", "stb_" .. name .. ".h"),
    }

    if not cppmodule or not _OPTIONS["cpp-modules"] then
        files { path.join(TWO_SRC_DIR, "3rdparty", "stb_" .. name .. ".cpp") }
    end

    configuration { "*-gcc*" }
        buildoptions {
            "-Wno-unused-but-set-variable",
            "-Wno-type-limits",
        }
    
    return m
end

stb = {}
-- @todo fix module on clang
stb.image     = stb_module("image", false)
stb.rect_pack = stb_module("rect_pack", false)

-- two library
-- two ui bgfx renderer module

function two_ui_vg()
    includedirs {
        path.join(TWO_NANOVG_DIR, "src"),
        path.join(TWO_3RDPARTY_DIR, "stb"),
    }
end

function uses_two_ui_vg()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "vg-renderer", "include"),
    }
    
    defines {
        "TWO_VG_VG",
    }
end

function two_ui_nvg()
    includedirs {
        path.join(TWO_NANOVG_DIR, "src"),
    }
    
    files {
        path.join(TWO_NANOVG_DIR, "src/nanovg.c"),
        path.join(TWO_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
    }
end

function uses_two_ui_nvg()
    defines {
        "TWO_VG_NANOVG",
    }
end

if TWO_STATIC then
    two.ui.vg   = two_module("two", "ui-vg",        TWO_SRC_DIR, "ui-vg",        two_ui_vg,   uses_two_ui_vg,   false,  { bgfx, vg, two.infra, two.type, two.math, two.ui })
else
    two.ui.vg   = two_module("two", "ui-vg",        TWO_SRC_DIR, "ui-vg",        two_ui_vg,   uses_two_ui_vg,   false,  { stb.image, bgfx, vg, two.infra, two.type, two.math, two.ui })
end
two.ui.nvg      = two_module("two", "ui-nvg",       TWO_SRC_DIR, "ui-nvg",       nil,         nil,              false,  {})
two.ui.nvg.bgfx = two_module("two", "ui-nvg-bgfx",  TWO_SRC_DIR, "ui-nvg-bgfx",  two_ui_nvg,  uses_two_ui_nvg,  false,  { bgfx, two.infra, two.type, two.math, two.ui })
    
function two_ui_backend()
    if _OPTIONS["vg-vg"] then
        return two.ui.vg
    end
    if _OPTIONS["vg-nvg"] then
        return two.ui.nvg.bgfx
    end
end

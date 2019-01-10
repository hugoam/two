-- mud library
-- mud ui bgfx renderer module

function mud_ui_vg()
    includedirs {
        path.join(MUD_NANOVG_DIR, "src"),
        path.join(MUD_3RDPARTY_DIR, "stb"),
    }
end

function uses_mud_ui_vg()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
    }
    
    defines {
        "MUD_VG_VG",
    }
end

function mud_ui_nvg()
    includedirs {
        path.join(MUD_NANOVG_DIR, "src"),
    }
    
    files {
        path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
        path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
    }
end

function uses_mud_ui_nvg()
    defines {
        "MUD_VG_NANOVG",
    }
end

if MUD_STATIC then
    mud.ui.vg   = mud_module("mud", "ui-vg",        MUD_SRC_DIR, "ui-vg",        mud_ui_vg,   uses_mud_ui_vg,   false,  { bgfx, vg, mud.infra, mud.type, mud.math, mud.ui })
else
    mud.ui.vg   = mud_module("mud", "ui-vg",        MUD_SRC_DIR, "ui-vg",        mud_ui_vg,   uses_mud_ui_vg,   false,  { stb.image, bgfx, vg, mud.infra, mud.type, mud.math, mud.ui })
end
mud.ui.nvg      = mud_module("mud", "ui-nvg",       MUD_SRC_DIR, "ui-nvg",       nil,         nil,              false,  {})
mud.ui.nvg.bgfx = mud_module("mud", "ui-nvg-bgfx",  MUD_SRC_DIR, "ui-nvg-bgfx",  mud_ui_nvg,  uses_mud_ui_nvg,  false,  { bgfx, mud.infra, mud.type, mud.math, mud.ui })
    
function mud_ui_backend()
    if _OPTIONS["vg-vg"] then
        return mud.ui.vg
    end
    if _OPTIONS["vg-nvg"] then
        return mud.ui.nvg.bgfx
    end
end

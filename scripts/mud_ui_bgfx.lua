-- mud library
-- mud ui bgfx renderer module

function mud_ui_vg()
    includedirs {
        path.join(MUD_NANOVG_DIR, "src"),
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

function mud_ui_nanovg()
    includedirs {
        path.join(MUD_NANOVG_DIR, "src"),
    }
    
    files {
        path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
        path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
    }
end

function uses_mud_ui_nanovg()
    defines {
        "MUD_VG_NANOVG",
    }
end

mud.ui.vg       = mud_module("mud", "ui-vg",           MUD_SRC_DIR, "ui-vg",           nil,     mud_ui_vg,      uses_mud_ui_vg,         { bgfx, vg, mud.infra, mud.obj, mud.math, mud.ui })
mud.ui.nanovg   = mud_module("mud", "ui-nanovg",       MUD_SRC_DIR, "ui-nanovg",       nil,     nil,            nil,                    {})
mud.ui.nanobgfx = mud_module("mud", "ui-nanovg-bgfx",  MUD_SRC_DIR, "ui-nanovg-bgfx",  nil,     mud_ui_nanovg,  uses_mud_ui_nanovg,     { bgfx, mud.infra, mud.obj, mud.math, mud.ui })
    
function mud_ui_backend()
    if _OPTIONS["vg-vg"] then
        return mud.ui.vg
    end
    if _OPTIONS["vg-nanovg"] then
        return mud.ui.nanobgfx
    end
end

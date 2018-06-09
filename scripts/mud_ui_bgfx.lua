-- mud library
-- mud ui bgfx renderer module

function mud_ui_vg()
    includedirs {
        path.join(MUD_NANOVG_DIR, "src"),
    }
    
    uses_bgfx()
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
    
    uses_bgfx()
end

function uses_mud_ui_nanovg()
    defines {
        "MUD_VG_NANOVG",
    }
end

mud.ui.vg       = mud_module(mud_module_decl, "mud", "ui-vg",           MUD_SRC_DIR, "ui-vg",           mud_ui_vg,      uses_mud_ui_vg,         { vg, mud.infra, mud.obj, mud.math, mud.ui })
mud.ui.nanovg   = mud_module(mud_module_decl, "mud", "ui-nanovg",       MUD_SRC_DIR, "ui-nanovg",       nil,            nil,                    {})
mud.ui.nanobgfx = mud_module(mud_module_decl, "mud", "ui-nanovg-bgfx",  MUD_SRC_DIR, "ui-nanovg-bgfx",  mud_ui_nanovg,  uses_mud_ui_nanovg,     { mud.infra, mud.obj, mud.math, mud.ui })
    
function mud_ui_backend()
    if _OPTIONS["vg-vg"] then
        return mud.ui.vg
    end
    if _OPTIONS["vg-nanovg"] then
        return mud.ui.nanobgfx
    end
end

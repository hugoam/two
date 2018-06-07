-- mud library
-- mud ui bgfx renderer module

function mud_ui_backend(parent)
    if _OPTIONS["vg-vg"] then
        mud.uibackend = mud_module(false, "mud", "ui-vg", MUD_SRC_DIR, "ui-vg", { vg, mud.obj, mud.math, mud.ui })
        table.insert(parent.deps, vg)
        
        defines {
            "MUD_VG_VG",
        }
    end
        
    if _OPTIONS["vg-nanovg"] then
        mud.uibackend = mud_module(false, "mud", "ui-nanovg-bgfx", MUD_SRC_DIR, "ui-nanovg-bgfx", { mud.obj, mud.math, mud.ui })
        
        mud_module(false, "mud", "ui-nanovg", MUD_SRC_DIR, "ui-nanovg")
        
        files {
            path.join(MUD_NANOVG_DIR, "src/nanovg.c"),
            path.join(MUD_NANOVG_DIR, "src/nanovg_bgfx.cpp"),
        }
    
        defines {
            "MUD_VG_NANOVG",
        }
    end
    
    includedirs {
        path.join(BX_DIR,    "include"),
        path.join(BGFX_DIR,    "include"),
        path.join(MUD_3RDPARTY_DIR, "glm"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_NANOVG_DIR, "src"),
    }

    defines {
        --"MUD_UI_DRAW_CACHE",
    }
    
    table.insert(parent.deps, mud.uibackend)
end

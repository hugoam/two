-- mud
-- mud example application

mud.examples = {}
mud.examples.all = mud_module(nil, "example", MUD_DIR, "example", nil, nil, nil, {}, true)
        
if _OPTIONS["renderer-bgfx"] then
    project "mud_example"
        kind "ConsoleApp"
        
        mud.examples.all.decl(mud.examples.all, false)
        
        includedirs {
            path.join(MUD_DIR, "example"),
        }
        
        defines { "_00_UI_EXPORT=MUD_EXPORT", "_00_TUTORIAL_EXPORT=MUD_EXPORT", "_15_SCRIPT_EXPORT=MUD_EXPORT" }
        
        mud_depends(mud.all)
        mud_shell("mud_example")
        
    --project "mud_shell"
    --    kind "ConsoleApp"
        
    --    uses_mud()
    --    uses_mud_coregfx()
    --    mud_shell("mud_shell")  
end

function mud_example_module_decl(m, as_project)
    mud_module_decl(m, as_project)
    
    configuration { "asmjs" }
        linkoptions {
            "--preload-file ../../../data/examples/" .. m.name .. "@data/",
        }
    
    configuration {}
end

function mud_example(name, gfx, deps, ismodule)

    if _OPTIONS["renderer-gl"] and gfx then
        return
    end

    project(name)
        kind "ConsoleApp"
        
        _G[name] = mud_module(nil, "_" .. name, path.join(MUD_DIR, "example"), name, mud_example_module_decl, nil, nil, {}, not ismodule)
        
        if ismodule then
            mud_refl(_G[name])
            mud_module_decl(_G[name].refl, false)
        end
        
        _G[name].decl(_G[name], false)
        
		for _, depname in ipairs(deps) do
            _G[depname].decl(_G[depname], false)
        end
        
        if gfx then
            files {
                path.join(MUD_DIR, "src", "mud", "Shell.cpp"),
            }
    
            mud_depends(mud.all)
        else
            if _OPTIONS["renderer-gl"] then
                mud_depends({ mud.gl, mud.uibackend })
            elseif _OPTIONS["renderer-bgfx"] then
                mud_depends({ mud.bgfx, mud.uibackend })
            end
            mud_depends(mud.core)
        end
        
        mud_binary(name)
end

mud_example("00_tutorial",          true, {}, true)
mud_example("00_cube",              true, {})
--mud_example("00_ui",                false, {})
mud_example("01_shapes",            true, {})
mud_example("03_materials",         true, {})
mud_example("02_camera",            true, { "03_materials" })
mud_example("04_lights",            true, { "01_shapes", "03_materials" })
mud_example("04_sponza",            true, { "01_shapes", "03_materials" })
--mud_example("05_character",       true, "03_materials")
mud_example("06_particles",         true, {})
mud_example("07_gltf",              true, {})
mud_example("07_prefabs",           true, { "07_gltf" })
mud_example("08_sky",               true, { "01_shapes", "03_materials" })
mud_example("09_live_shader",       true, {})
mud_example("10_post_process",      true, { "01_shapes", "03_materials" })
mud_example("11_selection",         true, { "01_shapes", "03_materials" })
mud_example("12_ui",                true, { "01_shapes", "03_materials" })
mud_example("13_live_ui",           true, {})
mud_example("14_live_gfx",          true, {})
mud_example("14_live_gfx_visual",   true, {})
mud_example("15_script",            true, { "01_shapes", "03_materials" }, true)
mud_example("16_visual_script",     true, { "01_shapes", "03_materials" })
mud_example("17_wfc",               true, {})
--mud_example("18_pathfinding",     true, {})
mud_example("19_multi_viewport",    true, {})
mud_example("20_meta",              true, { "01_shapes", "03_materials" })

if _OPTIONS["renderer-bgfx"] then
    project "09_live_shader"
        configuration { "asmjs" }
            uses_shaderc()
end

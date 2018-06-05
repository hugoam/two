-- mud
-- mud example application

if _OPTIONS["renderer-bgfx"] then
    project "mud_example"
        kind "ConsoleApp"
        
        includedirs {
            path.join(MUD_DIR, "example"),
        }
        
        mud_module(false, "mud", "example", MUD_DIR, "example") --, "_EXAMPLE")

        defines { "_00_UI_LIB", "_00_TUTORIAL_LIB", "_15_SCRIPT_LIB" }
        
        uses_mud_gfx()
        uses_mud()
        mud_shell("mud_example")
        
    --project "mud_shell"
    --    kind "ConsoleApp"
        
    --    uses_mud_gfx()
    --    uses_mud()
    --    mud_shell("mud_shell")  
end

function mud_example(name, gfx, deps)

    if _OPTIONS["renderer-gl"] and gfx then
        return
    end

    project(name)
        kind "ConsoleApp"

        mud_module(false, "", name, path.join(MUD_DIR, "example"), name, "_" .. name:upper())
        
		for _, depname in ipairs(deps) do
            mud_module(false, "", depname, path.join(MUD_DIR, "example"), depname, "_" .. depname:upper())
            
            configuration { "asmjs" }
                linkoptions {
                    "--preload-file ../../../data/examples/" .. depname .. "@data/",
                }
            
            configuration {}
        end
        
        if gfx then
            files {
                path.join(MUD_DIR, "src", "mud", "Shell.cpp"),
            }
    
            uses_mud_gfx()
        else
            if _OPTIONS["renderer-gl"] then
                uses_mud_gl()
            elseif _OPTIONS["renderer-bgfx"] then
                uses_mud_bgfx()
            end
        end
        
        uses_mud()
        mud_binary(name)
        
        configuration { "asmjs" }
            linkoptions {
                "--preload-file ../../../data/examples/" .. name .. "@data/",
            }
        
        configuration {}
end

mud_example("00_tutorial",          true, {})
mud_example("00_cube",              true, {})
mud_example("00_ui",                false, {})
mud_example("01_shapes",            true, {})
mud_example("02_camera",            true, { "03_materials" })
mud_example("03_materials",         true, {})
mud_example("04_lights",            true, { "01_shapes", "03_materials" })
mud_example("04_sponza",            true, { "01_shapes", "03_materials" })
--mud_example("05_character",       true, "03_materials")
mud_example("06_particles",         true, {})
mud_example("07_prefabs",           true, { "07_gltf" })
mud_example("07_gltf",              true, {})
mud_example("08_sky",               true, { "01_shapes", "03_materials" })
mud_example("09_live_shader",       true, {})
mud_example("10_post_process",      true, { "01_shapes", "03_materials" })
mud_example("11_selection",         true, { "01_shapes", "03_materials" })
mud_example("12_ui",                true, { "01_shapes", "03_materials" })
mud_example("13_live_ui",           true, {})
mud_example("14_live_gfx",          true, {})
mud_example("14_live_gfx_visual",   true, {})
mud_example("15_script",            true, { "01_shapes", "03_materials" })
mud_example("16_visual_script",     true, { "01_shapes", "03_materials" })
mud_example("17_wfc",               true, {})
--mud_example("18_pathfinding",     true, {})
mud_example("19_multi_viewport",    true, {})
mud_example("20_meta",              true, { "01_shapes", "03_materials" })

if _OPTIONS["renderer-bgfx"] then
    project "09_live_shader"
        uses_shaderc()
end

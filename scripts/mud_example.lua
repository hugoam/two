-- mud
-- mud example application

project "mud_example"
	kind "ConsoleApp"
    
    includedirs {
        path.join(MUD_DIR, "example"),
    }
    
    mud_module("example", MUD_DIR, "example", "_EXAMPLE")

    defines { "_00_UI_LIB", "_00_TUTORIAL_LIB", "_15_SCRIPT_LIB" }
    
    uses_mud_gfx()
    uses_mud()
    mud_shell("mud_example")

function example_project(name, gfx, ...)
    project(name)
        kind "ConsoleApp"

        mud_module(name, path.join(MUD_DIR, "example"), name, "_" .. name:upper())
        
		for _, depname in ipairs({...}) do
            mud_module(depname, path.join(MUD_DIR, "example"), depname, "_" .. depname:upper())
        end
        
        if gfx then
            files {
                path.join(MUD_DIR, "src", "mud", "Shell.cpp"),
            }
    
            uses_mud_gfx()
        else
            uses_mud_bgfx()
        end
        
        uses_mud()
        mud_binary(name)
        
        configuration { "asmjs" }
            linkoptions {
                "--preload-file ../../../data/examples/" .. name .. "@data/",
            }
        
        configuration {}
end

example_project("00_tutorial", true)
example_project("00_cube", true)
example_project("00_ui", false)
example_project("01_shapes", true)
example_project("02_camera", true, "03_materials")
example_project("03_materials", true)
example_project("04_lights", true, "01_shapes", "03_materials")
example_project("04_sponza", true, "01_shapes", "03_materials")
--example_project("05_character", true, "03_materials")
example_project("06_particles", true)
example_project("07_prefabs", true)
example_project("07_gltf", true)
example_project("08_sky", true, "01_shapes", "03_materials")
example_project("09_live_shader", true)
example_project("10_post_process", true, "01_shapes", "03_materials")
example_project("11_selection", true, "01_shapes", "03_materials")
example_project("12_ui", true, "01_shapes", "03_materials")
example_project("13_live_ui", true)
example_project("14_live_gfx", true)
example_project("14_live_gfx_visual", true)
example_project("15_script", true, "01_shapes", "03_materials")
example_project("16_visual_script", true, "01_shapes", "03_materials")
example_project("17_wfc", true)
--example_project("18_pathfinding", true)
example_project("19_multi_viewport", true)
example_project("20_meta", true, "01_shapes", "03_materials")

project "09_live_shader"
    uses_shaderc()


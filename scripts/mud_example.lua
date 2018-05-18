-- mud
-- mud example application

function uses_mud_bgfx() 
	includedirs {
		path.join(MUD_SRC_DIR),
		path.join(MUD_DIR, "example"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "include"),
        path.join(MUD_3RDPARTY_DIR, "vg-renderer", "src"),
	}

	files {
        path.join(MUD_SRC_DIR, "bgfx/**.h"),
        path.join(MUD_SRC_DIR, "bgfx/**.cpp"),
	}
end


project "mud_example"
	kind "ConsoleApp"
    
    includedirs {
        path.join(MUD_DIR, "example"),
    }
    
	files {
        path.join(MUD_DIR, "example", "**.h"),
        path.join(MUD_DIR, "example", "**.cpp"),
	}
    
    defines { "MUD_VG_RENDERER" }
    defines { "_00_UI_LIB", "_00_TUTORIAL_LIB", "_15_SCRIPT_LIB" }
    
    uses_mud_gfx()
    uses_mud()
    mud_binary("mud_example")

function example_project(name, ...)
    project(name)
        kind "ConsoleApp"

        mud_module(name, path.join(MUD_DIR, "example"), name, "_" .. name:upper())
        
		for _, depname in ipairs({...}) do
            mud_module(depname, path.join(MUD_DIR, "example"), depname, "_" .. depname:upper())
        end
        
        --uses_mud_bgfx()
        uses_mud_gfx()
        uses_mud()
        mud_binary(name)
        
        configuration { "asmjs" }
            linkoptions {
                "--preload-file ../../../data/examples/" .. name .. "@data/",
            }
        
        configuration {}
end

example_project("00_tutorial")
example_project("00_cube")
example_project("00_ui")
example_project("01_shapes")
example_project("02_camera", "03_materials")
example_project("03_materials")
example_project("04_lights", "01_shapes", "03_materials")
example_project("04_sponza", "01_shapes", "03_materials")
--example_project("05_character", "03_materials")
example_project("06_particles")
example_project("07_prefabs")
example_project("07_gltf")
example_project("08_sky", "01_shapes", "03_materials")
example_project("09_live_shader")
example_project("10_post_process", "01_shapes", "03_materials")
example_project("11_selection", "01_shapes", "03_materials")
example_project("12_ui", "01_shapes", "03_materials")
example_project("13_live_ui")
example_project("14_live_gfx")
example_project("14_live_gfx_visual")
example_project("15_script", "01_shapes", "03_materials")
example_project("16_visual_script", "01_shapes", "03_materials")
example_project("17_wfc")
--example_project("18_pathfinding")
example_project("19_multi_viewport")
example_project("20_meta", "01_shapes", "03_materials")

project "09_live_shader"
    uses_shaderc()


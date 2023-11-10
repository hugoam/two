-- two library
-- tracy 3rdparty module

function uses_tracy()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "tracy"),
    }
end

tracy = dep(nil, "tracy", false, uses_tracy)
	kind "StaticLib"
    
	includedirs {
        path.join(TWO_3RDPARTY_DIR, "tracy"),
	}

	files {
        path.join(TWO_3RDPARTY_DIR, "tracy", "TracyClient.hpp"),
        path.join(TWO_3RDPARTY_DIR, "tracy", "TracyClient.cpp"),
	}
    
    configuration { "mingw* or linux or osx or wasm*" }
        buildoptions {
            "-Wno-unused-parameter",
            "-Wno-deprecated-declarations",
        }
        
	configuration { "osx or *-clang* or wasm*" }
		buildoptions {
			"-Wno-undef",
			"-Wno-unused-private-field",
		}

    configuration { "not osx" } -- kludge: disabling for OSX until we fix compile errors and add a proper profiling build option
        defines { "TRACY_ENABLE" }

    configuration {}

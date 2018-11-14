function uses_culling()
    includedirs {
        path.join(MUD_3RDPARTY_DIR, "culling"),
    }
end

culling = mud_dep(nil, "culling", false, uses_culling)
        kind "StaticLib"

        removeflags {
            "OptimizeSpeed", -- emscripten SIMD bug
        }

        includedirs {
            path.join(MUD_3RDPARTY_DIR, "culling"),
        }

        files {
            path.join(MUD_3RDPARTY_DIR, "culling", "MaskedOcclusionCulling.cpp"),
        }

       buildoptions {
            "-mssse3"
       }

-- two library
-- base64 3rdparty module

base64 = two_dep(nil, "base64")
    kind "StaticLib"
    
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "base64"),
    }

    files {
        path.join(TWO_3RDPARTY_DIR, "base64", "**.h"),
        path.join(TWO_3RDPARTY_DIR, "base64", "**.cpp"),
    }
    
    configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'char', possible loss of data
        }

    configuration {}

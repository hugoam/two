-- two library
-- json11 3rdparty module

json11 = dep(nil, "json11", true)
    kind "StaticLib"
    
    includedirs {
        path.join(TWO_SRC_DIR),
        path.join(TWO_3RDPARTY_DIR, "json11"),
    }
    
    files {
        path.join(TWO_3RDPARTY_DIR, "json11", "json11.h"),
        path.join(TWO_SRC_DIR, "3rdparty", "json11.cpp"),
        path.join(TWO_SRC_DIR, "3rdparty", "json11.mxx"),
    }
    
    mxx({ path.join(TWO_SRC_DIR, "3rdparty", "json11.cpp") }, json11)

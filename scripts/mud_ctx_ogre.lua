-- mud engine
-- mud ctx ogre module

project "mud_ctx_ogre"
	kind "SharedLib"
    
    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
    includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(MUD_3RDPARTY_DIR, "OIS", "includes"),
    }
    
    mud_module("ctx-ogre", MUD_SRC_DIR, "ctx-ogre", "MUD_CTX_OGRE")    
    uses_mud()
    
    links {
        "OgreMain",
        "ois",
        "OpenGL32",
    }
        
    configuration { "windows" }
        links {
            "dxguid",
            "dinput8",
        }

    configuration {}
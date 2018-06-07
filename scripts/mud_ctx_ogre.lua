-- mud engine
-- mud ctx ogre module

function mud_ctx_backend(parent)
    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
    includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(MUD_3RDPARTY_DIR, "OIS", "includes"),
    }
    
    mud.ctxbackend = mud_module(false, "mud", "ctx-ogre", MUD_SRC_DIR, "ctx-ogre")
    table.insert(parent.deps, mud.ctxbackend)
  
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
end

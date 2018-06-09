-- mud engine
-- mud ctx ogre module

function mud_ctx_ogre()
    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
    includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(MUD_3RDPARTY_DIR, "OIS", "includes"),
    }
    
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

function mud_ctx_backend()
    return mud_module("mud", "ctx-ogre", MUD_SRC_DIR, "ctx-ogre", nil, mud_ctx_ogre, nil, { mud.math, mud.ctx })
end

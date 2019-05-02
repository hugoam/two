-- two engine
-- two ctx ogre module

function two_ctx_ogre()
    removeflags {
        "NoRTTI",
        "NoExceptions",
    }
    
    includedirs {
        path.join(BUILD_DIR, "ogre"),
        path.join(OGRE_DIR, "OgreMain", "include"),
        path.join(TWO_3RDPARTY_DIR, "OIS", "includes"),
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

two.ctx.ogre = two_module("two", "ctx-ogre", TWO_SRC_DIR, "ctx-ogre", two_ctx_ogre, nil, false, { two.math, two.ctx })

function two_ctx_backend()
    return two.ctx.ogre
end

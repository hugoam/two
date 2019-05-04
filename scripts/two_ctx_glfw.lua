-- two library
-- two ctx glfw module

function two_ctx_glfw()
    includedirs {
        path.join(TWO_3RDPARTY_DIR, "glfw", "include"),
    }
end

function uses_two_ctx_glfw()
    configuration { "not asmjs" }
        links {
            "glfw",
        }
    
    configuration { "asmjs" }
        linkoptions {
            "-s USE_GLFW=3",
        }
        
    configuration {}
end

two.ctx.glfw = module("two", "ctx-glfw", TWO_SRC_DIR, "ctx-glfw", two_ctx_glfw, uses_two_ctx_glfw, false, { glfw, two.math, two.ctx })

function two_ctx_backend()
    return two.ctx.glfw 
end

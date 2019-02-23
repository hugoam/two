$input v_position, v_texcoord0

#include <common.sh>

void main()
{
    vec2 uv = v_texcoord0.xy;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

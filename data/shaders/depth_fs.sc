$input v_position, v_uv0

#include <common.sh>

void main()
{
    vec2 uv = v_uv0;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

$input v_position, v_uv0

#include <common.sh>
#include <encode.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    
    vec2 uv = v_uv0;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);

    float depth = gl_FragCoord.z;
    gl_FragColor = packFloatToRgba(depth);
}

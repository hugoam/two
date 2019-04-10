$input v_world, v_uv0

#include <common.sh>
#include <encode.sh>
#include <depth.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    
    vec2 uv = v_uv0;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    float dist = length(v_world - u_eye);
    dist = (dist - u_near_distance) / (u_far_distance - u_near_distance);
    dist = saturate(dist);
    gl_FragColor = packFloatToRgba(dist);
}

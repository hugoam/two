$input v_position, v_texcoord0

#include <common.sh>
#include <encode.sh>
#include <depth.sh>

void main()
{
    vec2 uv = v_texcoord0.xy;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    float dist = length(v_position.xyz - u_eye);
    dist = (dist - u_near_distance) / (u_far_distance - u_near_distance);
    dist = saturate(dist);
    gl_FragColor = packFloatToRgba(dist);
}

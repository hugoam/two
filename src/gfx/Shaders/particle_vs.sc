$input a_position, a_color0, a_texcoord0, a_texcoord1
$output v_color, v_uv0, v_particle

#include <common.sh>

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));

    v_color = a_color0;
    v_uv0 = a_texcoord0;
    v_particle = a_texcoord1;
}

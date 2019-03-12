$input a_position, a_texcoord0
$output v_uv0

#include <common.sh>

void main()
{
    v_uv0 = a_texcoord0;
    gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
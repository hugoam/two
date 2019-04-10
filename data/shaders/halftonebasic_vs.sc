$input a_position, a_normal, a_texcoord0
$output v_normal, v_uv0
#include <common.sh>
void main()
{
v_uv0 = a_texcoord0;
v_normal = vec3(a_normal);
gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
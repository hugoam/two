$input a_position, a_texcoord0
$output v_uv0, v_dir

#include <common.sh>

uniform mat4 u_prefilter_cube;

void main()
{
    v_uv0 = a_texcoord0;
    
     // uvs are relative to top-left, so we need to reverse y to get NDC
    vec2 uv0ndc = vec2(v_uv0.x, 1.0 - v_uv0.y) * 2.0 - 1.0;
    
    v_dir = mul(u_prefilter_cube, vec4(vec3(uv0ndc, -1.0), 0.0)).xyz;
    v_dir.x = -v_dir.x; // cubemap space has x flipped
    
    gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}

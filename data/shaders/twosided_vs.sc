
$input a_position, a_normal
$output v_view, v_normal

#include <common.sh>

void main()
{
    v_view = mul(u_modelView, vec4(a_position.xyz, 1.0)).xyz;

    v_normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)).xyz);
        
    gl_Position = mul(u_proj, vec4(v_view, 1.0));
}

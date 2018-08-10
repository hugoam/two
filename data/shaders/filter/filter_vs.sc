$input a_position, a_texcoord0
$output v_texcoord0

#include <filter/filter.sh>

void main()
{
	v_texcoord0 = a_texcoord0;
	v_texcoord0.xy = u_source_0_crop.xy + v_texcoord0.xy * u_source_0_crop.zw;

    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
}

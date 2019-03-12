$input a_position, a_texcoord0
$output v_uv0

#include <filter/filter.sh>

void main() {
	v_uv0 = u_source_0_crop.xy + a_texcoord0 * u_source_0_crop.zw;
	gl_Position = u_modelViewProj * vec4(a_position.xyz, 1.0);
}

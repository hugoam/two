$input a_position, a_texcoord0
$output v_uv0
#include <filter.sh>
uniform vec4 u_bloom_blur_p0;
#define u_increment u_bloom_blur_p0.xy
void main() {
v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
v_uv0 = v_uv0 - ((float(KERNEL_SIZE) - 1.0) / 2.0) * u_increment;
gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}

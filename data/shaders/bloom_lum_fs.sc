$input v_uv0
#include <filter.sh>
uniform vec4 u_glow_lum_p0;
#define u_threshold    u_glow_lum_p0.x
#define u_smooth_width u_glow_lum_p0.y
void main() {
vec4 texel = texture2D(s_source_0, v_uv0);
vec3 luma = vec3(0.299, 0.587, 0.114);
float v = dot(texel.xyz, luma);
vec4 outputColor = vec4_splat(0.0);
float alpha = smoothstep(u_threshold, u_threshold + u_smooth_width, v);
gl_FragColor = mix(outputColor, texel, alpha);
}

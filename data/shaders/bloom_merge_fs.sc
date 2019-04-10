$input v_uv0
#include <filter.sh>
uniform vec4 u_glow_merge_p0;
#define u_glow_strength u_glow_merge_p0.x
#define u_glow_radius u_glow_merge_p0.y
uniform vec4 u_glow_levels[2];
uniform vec4 u_glow_colors[5];
float bloomFactor(float factor) { 
	float mirrorFactor = 1.2 - factor;
	return mix(factor, mirrorFactor, u_glow_radius);
}
void main() {
	vec4 bloom = u_glow_strength * (bloomFactor(u_glow_levels[0].x) * u_glow_colors[0] * texture2DLod(s_source_1, v_uv0, 1.0) + 
									bloomFactor(u_glow_levels[0].y) * u_glow_colors[1] * texture2DLod(s_source_1, v_uv0, 2.0) + 
									bloomFactor(u_glow_levels[0].z) * u_glow_colors[2] * texture2DLod(s_source_1, v_uv0, 3.0) + 
									bloomFactor(u_glow_levels[0].w) * u_glow_colors[3] * texture2DLod(s_source_1, v_uv0, 4.0) + 
									bloomFactor(u_glow_levels[1].x) * u_glow_colors[4] * texture2DLod(s_source_1, v_uv0, 5.0));
	gl_FragColor = texture2DLod(s_source_0, v_uv0, 0.0) + bloom;}

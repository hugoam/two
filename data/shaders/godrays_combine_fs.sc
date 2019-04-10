$input v_uv0
#include <filter.sh>
uniform vec4 u_godrays_combine_p0;
#define u_intensity u_godrays_combine_p0.x
void main() {
	float amount = u_intensity * (1.0 - texture2D(s_source_1, v_uv0).r);
	gl_FragColor = texture2D(s_source_0, v_uv0) + vec4_splat(amount);
	gl_FragColor.a = 1.0;
}

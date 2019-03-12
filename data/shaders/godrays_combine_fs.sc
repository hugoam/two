$input v_uv0

#include <filter.sh>

uniform vec4 u_godrays_combine_p0;
#define u_intensity u_godrays_combine_p0.x

void main() {


	gl_FragColor = texture2D(s_source_0, v_uv0) + u_intensity * vec4(1.0 - texture2D(s_source_1, v_uv0).r);
	gl_FragColor.a = 1.0;

}
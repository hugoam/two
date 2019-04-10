$input v_uv0
#include <filter.sh>
uniform vec4 u_godrays_sun_p0;
#define u_bg_color u_godrays_sun_p0.xyz
uniform vec4 u_godrays_sun_p1;
#define u_sun_color u_godrays_sun_p1.xyz
uniform vec4 u_godrays_sun_p2;
#define u_sun_xy u_godrays_sun_p2.xy
void main() {
	vec2 diff = v_uv0 - u_sun_xy;
	diff.x *= u_aspect;
	float prop = clamp(length(diff) / 0.5, 0.0, 1.0);
	prop = 0.35 * pow(1.0 - prop, 3.0);
	gl_FragColor.xyz = mix(u_sun_color, u_bg_color, 1.0 - prop);
	gl_FragColor.w = 1.0;
}

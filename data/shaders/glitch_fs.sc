$input v_uv0
#include <filter.sh>
uniform vec4 u_glitch_p0;
#define u_amount u_glitch_p0.x
#define u_angle u_glitch_p0.y
#define u_seed u_glitch_p0.y
uniform vec4 u_glitch_p1;
#define u_scale u_glitch_p1.xy
#define u_distort u_glitch_p1.zw
float rand2(vec2 co){
	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}
void main() {
	const float col_s = 0.5;
	vec2 p = v_uv0;
	float xs = floor(gl_FragCoord.x / 0.5);
	float ys = floor(gl_FragCoord.y / 0.5);
	//based on staffantans glitch shader for unity https://github.com/staffantan/unityglitch 
	vec4 normal = texture2D(s_source_1, p * u_seed * u_seed);
	if(p.y < u_distort.x + col_s && p.y > u_distort.x - col_s * u_seed) {
		if(u_scale.x > 0.0) {
			p.y = 1.0 - (p.y + u_distort.y);
		}
		else {
			p.y = u_distort.y;
		}
	}
	if(p.x < u_distort.y + col_s && p.x > u_distort.y - col_s * u_seed) {
		if(u_scale.y > 0.0){
			p.x = u_distort.x;
		}
		else {
			p.x = 1.0 - (p.x + u_distort.x);
		}
	}
	p.x += normal.x * u_scale.x * (u_seed / 5.0);
	p.y += normal.y * u_scale.y * (u_seed / 5.0);
	//base from RGB shift shader
	vec2 offset = u_amount * vec2(cos(u_angle), sin(u_angle));
	vec4 cr = texture2D(s_source_0, p + offset);
	vec4 cga = texture2D(s_source_0, p);
	vec4 cb = texture2D(s_source_0, p - offset);
	gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);
	//add noise
	vec4 snow = 200.0 * u_amount * vec4_splat(rand2(vec2(xs * u_seed, ys * u_seed * 50.0)) * 0.2);
	gl_FragColor = gl_FragColor + snow;
}

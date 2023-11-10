$input v_dir, v_wpos, v_color, v_uv0

#include <common.sh>

// Star Nest by Pablo Román Andrioli
// This content is under the MIT License.
// https://www.shadertoy.com/view/XlfGRj

#define u_iterations 13
#define u_formuparam 0.53

#define u_volsteps 5
#define u_stepsize 0.2

#define u_zoom   0.800
#define u_tile   0.850
#define u_speed  0.0001 

#define u_brightness 0.0010
#define u_darkmatter 0.300
#define u_distfading 0.730
#define u_saturation 0.550

void main()
{
	// get coords and direction
	float time = u_time * u_speed + .25;
    vec3 from = v_wpos * 0.001;
	from += vec3(time * 2.0, time, -2.0);
    vec3 dir = v_dir;
        
	// volumetric rendering
	float s = 0.1;
    float fade = 1.0;
	vec3 v = vec3_splat(0.);
	for (int r = 0; r < u_volsteps; r++) {
		vec3 p = from + s * dir * 0.5;
		p = abs(vec3_splat(u_tile) - mod(p, vec3_splat(u_tile * 2.0))); // tiling fold
		float pa,a = pa =0.;
		for (int i = 0 ; i < u_iterations; i++) { 
			p = abs(p) / dot(p, p) - u_formuparam; // the magic formula
			a += abs(length(p) - pa); // absolute sum of average change
			pa = length(p);
		}
		float dm = max(0. , u_darkmatter - a * a * .001); //dark matter
		a *= a*a; // add contrast
		if (r>6) fade *= 1. - dm; // dark matter, don't render near
		//v+=vec3(dm,dm*.5,0.);
		v += fade;
		v += vec3(s, s*s, s*s*s*s) * a * u_brightness * fade; // coloring based on distance
		fade *= u_distfading; // distance fading
		s += u_stepsize;
	}
	v = mix(vec3_splat(length(v)), v, u_saturation); // color adjust
	gl_FragColor = toLinear(vec4(clamp(v * 0.01, vec3_splat(0.0), vec3_splat(1.0)), 0.0));
}
$input v_uv0
#include <filter.sh>
#define TAPS_PER_PASS 6.0
uniform vec4 u_godrays_p0;
#define u_sun u_godrays_p0.xy
#define u_step_size u_godrays_p0.z
void main() {
vec2 delta = u_sun - v_uv0;
float dist = length(delta);
vec2 stepv = u_step_size * delta / dist;
float iters = dist / u_step_size;
vec2 uv = v_uv0;
float col = 0.0;
if (0.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;
uv += stepv;
if (1.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;
uv += stepv;
if (2.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;
uv += stepv;
if (3.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;
uv += stepv;
if (4.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;
uv += stepv;
if (5.0 <= iters && uv.y < 1.0) col += texture2D(s_source_0, uv).r;
uv += stepv;
gl_FragColor = vec4(col/TAPS_PER_PASS, 0.0, 0.0, 1.0);
}

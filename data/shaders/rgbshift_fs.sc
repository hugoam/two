$input v_uv0
#include <filter.sh>
uniform vec4 u_rgbshift_p0;
#define u_amount u_rgbshift_p0.xy
#define u_angle  u_rgbshift_p0.z
#define s_diffuse s_source_0
void main() {
vec2 offset = u_amount * vec2(cos(u_angle), sin(u_angle));
vec4 cr = texture2D(s_diffuse, v_uv0 + offset);
vec4 cga = texture2D(s_diffuse, v_uv0);
vec4 cb = texture2D(s_diffuse, v_uv0 - offset);
gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);
}

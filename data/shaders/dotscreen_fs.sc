$input v_uv0
#include <filter.sh>
uniform vec4 u_dotscreen_p0;
#define u_center u_dotscreen_p0.xy
#define u_angle  u_dotscreen_p0.z
#define u_scale  u_dotscreen_p0.w
uniform vec4 u_dotscreen_p1;
#define u_size u_dotscreen_p1.xy
#define s_diffuse s_source_0
float pattern(vec2 uv) {
float s = sin(u_angle), c = cos(u_angle);
vec2 tex = uv * u_size - u_center;
vec2 p = vec2(c * tex.x - s * tex.y, s * tex.x + c * tex.y) * u_scale;
return (sin(p.x) * sin(p.y)) * 4.0;
}
void main() {
vec4 color = texture2D(s_diffuse, v_uv0);
float average = (color.r + color.g + color.b) / 3.0;
gl_FragColor = vec4(vec3_splat(average * 10.0 - 5.0 + pattern(v_uv0)), color.a);
}

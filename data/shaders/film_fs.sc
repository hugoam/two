$input v_uv0
#include <filter.sh>
uniform vec4 u_film_p0;
#define u_noise     u_film_p0.x
#define u_intensity u_film_p0.y
#define u_count     int(u_film_p0.z)
#define u_grayscale bool(u_film_p0.w)
void main() {
vec3 source = texture2D(s_source_0, v_uv0).rgb;
float dx = rand(v_uv0 + u_time);
vec3 color = source + source * clamp(0.1 + dx, 0.0, 1.0);
vec2 sc = vec2(sin(v_uv0.y * u_count), cos(v_uv0.y * u_count));
color += source * vec3(sc.x, sc.y, sc.x) * u_intensity;
color = source + clamp(u_noise, 0.0, 1.0) * (color - source);
if(u_grayscale) {
color = vec3_splat(color.r * 0.3 + color.g * 0.59 + color.b * 0.11);
}
gl_FragColor = vec4(color, 1.0);
}
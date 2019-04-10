$input v_world, v_mirrored
#include <common.sh>
#define s_mirror s_user0
#define s_normal s_user1
vec4 getNoise(vec2 uv) {
vec2 uv0 = (uv / 103.0) + vec2(u_time / 17.0, u_time / 29.0);
vec2 uv1 = uv / 107.0 - vec2(u_time / -19.0, u_time / 31.0);
vec2 uv2 = uv / vec2(8907.0, 9803.0) + vec2(u_time / 101.0, u_time / 97.0);
vec2 uv3 = uv / vec2(1091.0, 1027.0) - vec2(u_time / 109.0, u_time / -113.0);
vec4 noise = texture2D(s_normal, uv0) +
texture2D(s_normal, uv1) +
texture2D(s_normal, uv2) +
texture2D(s_normal, uv3);
return noise * 0.5 - 1.0;
}
void sunLight(vec3 normal, vec3 view, vec3 sundir, vec3 suncolor, float shiny, float fspec, float fdiff, inout vec3 diffuse, inout vec3 specular) {
vec3 reflection = normalize(reflect(-sundir, normal));
float direction = max(0.0, dot(view, reflection));
specular += pow(direction, shiny) * suncolor * fspec;
diffuse += max(dot(sundir, normal), 0.0) * suncolor * fdiff;
}
void main() {
int material_index = int(u_state_material);
UserMaterial mat = read_user_material(material_index);
float alpha      = mat.p0.x;
float size       = mat.p0.y;
float distortion = mat.p0.z;
vec3 suncolor    = mat.p1.xyz;
vec3 sundir      = mat.p2.xyz;
vec3 eye         = mat.p3.xyz;
vec3 water_color = mat.p4.xyz;
vec4 noise = getNoise(v_world.xz * size);
vec3 normal = normalize(noise.xzy * vec3(1.5, 1.0, 1.5));
vec3 diffuse = vec3_splat(0.0);
vec3 specular = vec3_splat(0.0);
vec3 ray = eye - v_world.xyz;
float distance = length(ray);
vec3 dir = normalize(ray);
sunLight(normal, dir, sundir, suncolor, 100.0, 2.0, 0.5, diffuse, specular);
vec2 distort = normal.xz * (0.001 + 1.0 / distance) * distortion;
vec3 reflection = texture2D(s_mirror, v_mirrored.xy / v_mirrored.w + distort).rgb;
float theta = max(dot(dir, normal), 0.0);
float rf0 = 0.3;
float reflectance = rf0 + (1.0 - rf0) * pow((1.0 - theta), 5.0);
vec3 scatter = max(0.0, dot(normal, dir)) * water_color;
diffuse = (suncolor * diffuse * 0.3 + scatter);
specular = (vec3_splat(0.1) + reflection * 0.9 + reflection * specular);
vec3 albedo = mix(diffuse, specular, reflectance);
vec3 light = albedo;
gl_FragColor = vec4(light, alpha);
}

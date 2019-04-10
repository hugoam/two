$input v_normal
#include <common.sh>
#define u_dot_color u_user_p0.xyz
#define u_light_dir u_user_p1.xyz
#define u_light_color u_user_p2.xyz
#define u_ambient u_user_p3.xyz
void main()
{
int material_index = int(u_state_material);
SolidMaterial solid = read_solid_material(material_index);
float directionalLightWeighting = max(dot(normalize(v_normal), -u_light_dir), 0.0);
vec3 lightWeighting = u_ambient + u_light_color * directionalLightWeighting;
gl_FragColor = vec4(solid.color.rgb, 1.0);
if (length(lightWeighting) < 1.00) {
if ((mod(gl_FragCoord.x, 4.001) + mod(gl_FragCoord.y, 4.0)) > 6.00) {
gl_FragColor = vec4(u_dot_color, 1.0);
}
}
if (length(lightWeighting) < 0.50) {
if ((mod(gl_FragCoord.x + 2.0, 4.001) + mod(gl_FragCoord.y + 2.0, 4.0)) > 6.00) {
gl_FragColor = vec4(u_dot_color, 1.0);
}
}
}

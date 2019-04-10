$input v_world
#include <common.sh>
void main()
{
int material_index = int(u_state_material);
UserMaterial mat = read_user_material(material_index);
vec3 top_color    = mat.p0.xyz;
vec3 bottom_color = mat.p1.xyz;
float offset      = mat.p2.x;
float exponent    = mat.p2.y;
float h = normalize(v_world + offset).y;
gl_FragColor = vec4(mix(bottom_color, top_color, max(pow(max(h, 0.0), exponent), 0.0)), 1.0);
gl_FragColor = vec4(pow(gl_FragColor.rgb, vec3_splat(2.0)), 1.0);
}

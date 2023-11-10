//$input v_color, v_uv0
$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <common.sh>

void main()
{
    vec3 normal = normalize(v_normal);
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    
#include "fs_alpha.sh"
#include "fs_alphatest.sh"
    
    gl_FragColor = vec4(normalize(normal) * 0.5 + 0.5, 1.0);
}

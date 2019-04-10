    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    LitMaterial   matlit   = read_lit_material(material_index);
    PhongMaterial matphong = read_phong_material(material_index);
    UserMaterial  matuser  = read_user_material(material_index);

#include "fs_depth.sh"

    vec2 uv = fragment.uv;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    matphong.diffuse *= sample_material_texture(s_diffuse, fragment.uv).rgb;
    matphong.specular *= sample_material_texture(s_specular, fragment.uv).rgb;
    matphong.shininess *= sample_material_texture(s_shininess, fragment.uv).r;

#ifdef VERTEX_COLOR
    matphong.diffuse *= v_color.rgb;
    alpha *= v_color.a;
#endif

#include "fs_normal.sh"
#include "fs_emission.sh"
#include "fs_ao.sh"

    fragment.NoV = dot(fragment.normal, fragment.view);
    fragment.cNoV = max(dot(fragment.normal, fragment.view), 0.0);

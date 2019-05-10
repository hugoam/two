    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    LitMaterial   matlit   = read_lit_material(material_index);
    PbrMaterial   matpbr   = read_pbr_material(material_index);

#include "fs_depth.sh"

    vec2 uv = fragment.uv;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

#ifdef ALBEDO_MAP
    matpbr.albedo.rgb *= sample_material_texture(s_albedo, fragment.uv).rgb;
#endif
#ifdef ROUGHNESS_MAP
    matpbr.roughness *= sample_material_texture(s_roughness, fragment.uv)[ int(matpbr.roughness_channel) ];
#endif
#ifdef METALLIC_MAP
    matpbr.metallic *= sample_material_texture(s_metallic, fragment.uv)[ int(matpbr.metallic_channel) ];
#endif
    
    Material material;
    material.albedo = matpbr.albedo.rgb;
    material.roughness = matpbr.roughness;
    material.metallic = matpbr.metallic;
    material.specular = matpbr.specular;
    material.refraction = matpbr.refraction;

#ifdef VERTEX_COLOR
    material.albedo *= v_color.rgb;
    alpha *= v_color.a;
#endif

#include "fs_normal.sh"
#include "fs_emission.sh"
#include "fs_anisotropy.sh"
#include "fs_ao.sh"

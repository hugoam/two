    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    LitMaterial   matlit   = read_lit_material(material_index);
    PbrMaterial   matpbr   = read_pbr_material(material_index);

#include "fs_depth.sh"

    vec2 uv = fragment.uv;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    if(u_albedo_map)
        matpbr.albedo.rgb *= sample_material_texture(s_albedo, fragment.uv).rgb;
        
    if(u_roughness_map)
        matpbr.roughness *= sample_material_texture(s_roughness, fragment.uv)[ int(matpbr.roughness_channel) ];

    if(u_metallic_map)
        matpbr.metallic *= sample_material_texture(s_metallic, fragment.uv)[ int(matpbr.metallic_channel) ];
        
    Material material;
    material.albedo = matpbr.albedo.rgb;
    material.roughness = matpbr.roughness;
    material.metallic = matpbr.metallic;
    material.specular = matpbr.specular;
    
    if(u_vertex_color)
    {
        material.albedo *= v_color.rgb;
        alpha *= v_color.a;
    }

#include "fs_normal.sh"
#include "fs_emission.sh"
//#include "fs_anisotropy.sh"
#include "fs_ao.sh"

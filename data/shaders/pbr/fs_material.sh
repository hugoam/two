    int material_index = int(u_state_material);
    PbrMaterial pbr = read_pbr_material(material_index);

#include "fs_depth.sh"

    vec2 uv = fragment.uv;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    Material material;
    material.albedo = pbr.albedo.rgb * sample_material_texture(s_albedo, fragment.uv).rgb;
    material.alpha = alpha;
    material.roughness = pbr.roughness * sample_material_texture(s_roughness, fragment.uv)[ int(pbr.roughness_channel) ];
    material.metallic = pbr.metallic * sample_material_texture(s_metallic, fragment.uv)[ int(pbr.metallic_channel) ];
    material.specular = pbr.specular;
    material.emission = vec4_splat(0.0);

#include "fs_normal.sh"
#include "fs_emission.sh"
#include "fs_anisotropy.sh"
#include "fs_ao.sh"

$input v_position, v_normal, v_color, v_uv0

#include <pbr/pbr.sh>
#include <pbr/light.sh>

#include <gi/gi.sh>
#include <gi/light.sh>

#include <encode.sh>
#include <bgfx_compute.sh>

UIMAGE3D_RW(s_voxels_albedo,  r32ui, 1);
UIMAGE3D_RW(s_voxels_normals, r32ui, 2);
UIMAGE3D_RW(s_voxels_light,   r32ui, 3);

#define COMPUTE_VOXEL_LIGHT

void main()
{
    if (abs(v_position.z) > VOXELGI_RESOLUTION_Z || abs(v_position.x) > 1.0 || abs(v_position.y) > 1.0) return;
    vec3 position = v_position.xyz * u_voxelgi_extents;
    //position += u_eye_snap;

    Fragment fragment;
	fragment.position = position;
	fragment.normal = normalize(v_normal);
	fragment.uv = v_uv0;
	fragment.color = v_color;
    
    int material_index = int(u_state_material);
    PbrMaterial matpbr = read_pbr_material(material_index);
    
    vec3 albedo = matpbr.albedo.rgb * sample_material_texture(s_albedo, fragment.uv).rgb;

	vec4 emission = vec4_splat(0.0);
#include <pbr/fs_emission.sh>

    fragment.color = vec4(albedo + emission.rgb, 1.0);
    
    vec3 voxel = v_position.xyz * 0.5 + 0.5; // [-1,1] to [0,1]
    ivec3 coord = ivec3(u_voxelgi_subdiv * voxel);
    
    uint color_enc = encodeColor(fragment.color);
#if BGFX_SHADER_LANGUAGE_HLSL
    InterlockedMax(s_voxels_albedo.m_texture[coord], color_enc);
#else
    imageAtomicMax(s_voxels_albedo, coord, color_enc);
#endif

    uint normal_enc = encodeNormal(fragment.normal);
#if BGFX_SHADER_LANGUAGE_HLSL
    InterlockedMax(s_voxels_normals.m_texture[coord], normal_enc);
#else
    imageAtomicMax(s_voxels_normals, coord, normal_enc);
#endif

#ifdef COMPUTE_VOXEL_LIGHT
    vec3 diffuse = compute_voxel_lights(fragment.position, fragment.color.rgb, fragment.normal);
    uint light_enc = encodeColor(vec4(diffuse + emission.rgb, 1.0));
#else
    uint light_enc = encodeColor(vec4(emission.rgb, 1.0));
#endif
    
#if BGFX_SHADER_LANGUAGE_HLSL
    InterlockedMax(s_voxels_light.m_texture[coord], light_enc);
#else
    imageAtomicMax(s_voxels_light, coord, light_enc);
#endif

}

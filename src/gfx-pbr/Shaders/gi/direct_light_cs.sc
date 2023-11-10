#include <pbr/pbr.sh>
#include <pbr/light.sh>

#include <gi/gi.sh>
#include <gi/light.sh>

#include <encode.sh>
#include <bgfx_compute.sh>

UIMAGE3D_RO(s_voxels_albedo,  r32ui, 0);
UIMAGE3D_RO(s_voxels_normals, r32ui, 1);
UIMAGE3D_RW(s_voxels_light,   r32ui, 2);

NUM_THREADS(64, 1, 1)
void main()
{
    ivec3 coord = ivec3(gl_GlobalInvocationID.xyz);
    vec4 voxel_color = decodeColor(imageLoad(s_voxels_albedo, coord).x);
    if (voxel_color.a == 0.0) return;

    uint unor = imageLoad(s_voxels_normals, coord).r;
    vec3 voxel_normal = normalize(decodeNormal(unor));

    const vec3 half_res = u_voxelgi_subdiv / 2.0;
    vec3 voxel_position = ((gl_GlobalInvocationID.xyz - half_res) / half_res) * u_voxelgi_extents;
    voxel_position -= voxel_normal * 0.01; // offset

    vec3 diffuse = compute_voxel_lights(voxel_position, voxel_color.rgb, voxel_normal);
    
    uint color_enc = encodeColor(vec4(diffuse, 1.0));
    
#if BGFX_SHADER_LANGUAGE_HLSL
    InterlockedAdd(s_voxels_light.m_texture[coord], color_enc);
#else
    imageAtomicAdd(s_voxels_light, coord, color_enc);
#endif
}

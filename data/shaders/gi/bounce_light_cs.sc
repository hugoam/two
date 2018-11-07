#include <pbr/pbr.sh>
#include <pbr/light.sh>

#include <gi/gi.sh>
#include <gi/light.sh>
#include <gi/conetrace.sh>

#include <encode.sh>
#include <bgfx_compute.sh>

UIMAGE3D_RO(s_voxels_normals,    r32ui, 0);
//UIMAGE3D_RO(s_voxels_light,    r32ui, 1);
SAMPLER3D(s_voxels_light_rgba, 1);
UIMAGE3D_WR(s_voxels_light,      r32ui, 2);

#define CONETRACE_MAT3

NUM_THREADS(64, 1, 1)
void main()
{
    ivec3 coord = ivec3(gl_GlobalInvocationID.xyz);
    
    vec4 color = texelFetch(s_voxels_light_rgba, coord, 0);
    if (color.a == 0.0) {
        // imageStore(voxelsTo, coord, color);
    	imageStore(s_voxels_light, coord, uvec4_splat(0u));
    	return;
    }

    const vec3 half_res = u_voxelgi_subdiv / 2.0;
    vec3 voxel_coord = (gl_GlobalInvocationID.xyz - half_res) / half_res;
    vec3 voxel_position = voxel_coord * u_voxelgi_extents;

    uint unor = imageLoad(s_voxels_normals, coord).r;
    vec3 voxel_normal = normalize(decodeNormal(unor));
    //vec3 voxel_normal = vec3(0.0, 1.0, 0.0);

    float multiplier = u_gi_probe_diffuse;
	vec3 position = voxel_position + voxel_normal * u_gi_probe_normal_bias;
#ifdef CONETRACE_MAT3
    mat3 normal_mat = cone_normal_mat(voxel_normal);
#endif
    
#ifdef CONETRACE_MAT3
    color.rgb += trace_diffuse(s_voxels_light_rgba, position, voxel_normal, normal_mat, 0.8).rgb * multiplier * 0.5;
#else
    color.rgb += trace_diffuse(s_voxels_light_rgba, position, voxel_normal, 0.8).rgb * multiplier * 0.5;
#endif
    //color.rgb = texture3DLod(s_voxels_light_rgba, voxel_coord * 0.5 + 0.5, 2.0).rgb;
    
    //color.rgb = debug_trace_diffuse(s_voxels_light_rgba, voxel_normal).rgb;
    //color.rgb = debug_trace_diffuse(s_voxels_light_rgba, voxel_normal, normal_mat).rgb;
    
    color = clamp(color, vec4_splat(0.0), vec4_splat(1.0));

    uint ucolor = encodeColor(color);
    imageStore(s_voxels_light, coord, uvec4_splat(ucolor));
}

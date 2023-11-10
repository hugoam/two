#include <common.sh>
#include <encode.sh>
#include <bgfx_compute.sh>

UIMAGE3D_RW(s_voxels_light, r32ui, 0);
IMAGE3D_RW(s_voxels_light_rgba, rgba16f, 1);

NUM_THREADS(64, 1, 1)
void main()
{
    ivec3 coord = ivec3(gl_GlobalInvocationID.xyz);
    
    vec4 color = decodeColor(imageLoad(s_voxels_light, coord).x);

    if (color.a > 0.0)
    {
#ifdef TEMPORAL_SMOOTHING
        if (u_voxelgi_moved)
        {
            imageStore(s_voxels_light_rgba, coord, vec4(color.rgb, 1.0));
        }
        else
        {
            vec4 previous = imageLoad(s_voxels_light_rgba, coord);
            imageStore(s_voxels_light_rgba, coord, mix(previous, vec4(color.rgb, 1.0), 0.2));
        }
#else
        imageStore(s_voxels_light_rgba, coord, vec4(color.rgb, 1.0));
#endif
    }
    else
    {
        imageStore(s_voxels_light_rgba, coord, vec4_splat(0.0));
    }

    imageStore(s_voxels_light, coord, uvec4_splat(0u));
}

$input v_voxposition, v_wnormal, v_vcolor, v_texcoord0

// #extension GL_ARB_shader_image_load_store : enable

#include <compiled.inc>
#include <std/math.glsl>
#include <std/imageatomic.glsl>
#include <std/gbuffer.glsl>

layout(r32ui) uimage3D voxels;
layout(r32ui) uimage3D voxelsNor;

void main()
{
    if (abs(voxposition.z) > ' + rpdat.rp_voxelgi_resolution_z + ' || abs(voxposition.x) > 1 || abs(voxposition.y) > 1) return;
    vec3 wposition = voxposition * voxelgiHalfExtents;
    //if rpdat.arm_voxelgi_revoxelize and rpdat.arm_voxelgi_camera:
    //    frag.add_uniform('vec3 eyeSnap', '_cameraPositionSnap
    //    wposition += eyeSnap;

    vec3 basecol;
    float roughness;
    float metallic;
    float occlusion;
    float specular;
    //parse_opacity = rpdat.arm_voxelgi_refraction
    //if parse_opacity:
    //    float opacity;
    float dotNV = 0.0;
    //cycles.parse(mat_state.nodes, con_voxel, vert, frag, geom, tesc, tese, parse_opacity=parse_opacity, parse_displacement=False, basecol_only=True)

    if not frag.contains('vec3 n =:
        frag.write_pre = True
        vec3 n;
        frag.write_pre = False

    vec3 voxel = voxposition * 0.5 + 0.5;
    uint val = convVec4ToRGBA8(vec4(basecol, 1.0) * 255);
    imageAtomicMax(voxels, ivec3(voxelgiResolution * voxel), val);

    val = encNor(wnormal);;
    imageAtomicMax(voxelsNor, ivec3(voxelgiResolution * voxel), val);
        
        // imageStore(voxels, ivec3(voxelgiResolution * voxel), vec4(color, 1.0));
        // imageAtomicRGBA8Avg(voxels, ivec3(voxelgiResolution * voxel), vec4(color, 1.0));
        //   
        // ivec3 coords = ivec3(voxelgiResolution * voxel);
        // if parse_opacity:
        //     vec4 val = vec4(color, opacity);
        // else:
        //     vec4 val = vec4(color, 1.0);
        // val *= 255.0;
        // uint newVal = encUnsignedNibble(convVec4ToRGBA8(val), 1);
        // uint prevStoredVal = 0;
        // uint currStoredVal;
        // # int counter = 0;
        // # while ((currStoredVal = imageAtomicCompSwap(voxels, coords, prevStoredVal, newVal)) != prevStoredVal && counter < 16) {
        // while ((currStoredVal = imageAtomicCompSwap(voxels, coords, prevStoredVal, newVal)) != prevStoredVal) {
        //     vec4 rval = convRGBA8ToVec4(currStoredVal & 0xFEFEFEFE);
        //     uint n = decUnsignedNibble(currStoredVal);
        //     rval = rval * n + val;
        //     rval /= ++n;
        //     rval = round(rval / 2) * 2;
        //     newVal = encUnsignedNibble(convVec4ToRGBA8(rval), n);
        //     prevStoredVal = currStoredVal;
        // #     counter++;
        // }
        //
        // val.rgb *= 255.0f;
        // uint newVal = convVec4ToRGBA8(val);
        // uint prevStoredVal = 0;
        // uint curStoredVal;
        // while ((curStoredVal = imageAtomicCompSwap(voxels, coords, prevStoredVal, newVal)) != prevStoredVal) {
        //     prevStoredVal = curStoredVal;
        //     vec4 rval = convRGBA8ToVec4(curStoredVal);
        //     rval.xyz = (rval.xyz * rval.w);
        //     vec4 curValF = rval + val;
        //     curValF.xyz /= (curValF.w);
        //     newVal = convVec4ToRGBA8(curValF);
        // }
}

$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0/*, v_texcoord1*/, v_binormal
//    geom.ins = vert.outs
$output g_voxposition, g_wnormal, g_vcolor, g_texcoord

#include <compiled.inc>

uniform mat4 W // _worldMatrix
uniform mat3 N // _normalMatrix

uniform vec3 u_eyeSnap; //_cameraPositionSnap

void main()
{
    g_vcolor = col;
    g_texcoord = tex;

    //if rpdat.arm_voxelgi_revoxelize and rpdat.arm_voxelgi_camera:
    //g_voxposition = (vec3(W * vec4(pos, 1.0)) - eyeSnap) / voxelgiHalfExtents;')
    //else: 
    g_voxposition = vec3(W * vec4(pos, 1.0)) / voxelgiHalfExtents;
    g_wnormal = normalize(N * nor);
    
    //gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}
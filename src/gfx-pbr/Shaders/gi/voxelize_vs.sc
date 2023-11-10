#ifdef SKELETON
#define SKELETON_INPUTS , a_indices, a_weight
#else
#define SKELETON_INPUTS
#endif

#ifdef INSTANCING
#define INSTANCING_INPUTS , i_data0, i_data1, i_data2, i_data3
#else
#define INSTANCING_INPUTS
#endif

$input a_position, a_normal, a_tangent, a_color0, a_texcoord0 SKELETON_INPUTS INSTANCING_INPUTS
$output g_position, g_normal, g_color, g_texcoord0

#include <common.sh>
#include <convert.sh>
#include <skeleton.sh>

#include <gi/gi.sh>

//uniform vec3 u_eye_snap; // camera position snap

void main()
{
#include "modelview.sh"

    mat4 normalModelView = transpose(inverse(modelView));
    
    //mat4 probe = mul(u_voxelgi_world, u_model[0]);
    //mat4 normalProbe = transpose(inverse(u_model[0]));

	g_color = a_color0;
	g_texcoord0 = a_texcoord0;

	g_position = mul(modelView, vec4(a_position.xyz, 1.0)).xyz / u_voxelgi_extents;
    //g_position = (mul(modelView, vec4(pos, 1.0)).xyz - u_eye_snap) / u_voxelgi_extents;
    g_normal = normalize(mul(normalModelView, vec4(a_normal, 0.0)).xyz);

    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}
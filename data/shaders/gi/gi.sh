#ifndef MUD_SHADER_GI
#define MUD_SHADER_GI

#include <common.sh>

//uniform mat4 u_voxelgi_world;
//uniform mat3 u_voxelgi_normal;

uniform vec4 u_voxelgi_params_0;
#define u_voxelgi_extents u_voxelgi_params_0.xyz

uniform vec4 u_voxelgi_params_1;
#define u_voxelgi_subdiv u_voxelgi_params_1.xyz

uniform highp mat4 u_gi_probe_transform;

uniform highp vec4 u_gi_probe_bounds4;
#define u_gi_probe_bounds u_gi_probe_bounds4.xyz

uniform highp vec4 u_gi_probe_inv_extents4;
#define u_gi_probe_inv_extents u_gi_probe_inv_extents4.xyz

uniform highp vec4 u_gi_probe_inv_cell_size4;
#define u_gi_probe_cell_size u_gi_probe_inv_cell_size4.xyz

uniform highp vec4 u_gi_probe_params;
#define u_gi_probe_diffuse          u_gi_probe_params.x
#define u_gi_probe_specular         u_gi_probe_params.y
#define u_gi_probe_bias             u_gi_probe_params.z
#define u_gi_probe_normal_bias      u_gi_probe_params.w
//#define u_gi_probe_blend_ambient    u_gi_probe_params.w

CONST(float) u_gi_probe_blend_ambient = 0.0;

#define VOXELGI_RESOLUTION_Z 1.0

#endif

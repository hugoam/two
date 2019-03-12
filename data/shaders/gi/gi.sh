#ifndef MUD_SHADER_GI
#define MUD_SHADER_GI

#include <common.sh>

//uniform mat4 u_voxelgi_world;
//uniform mat3 u_voxelgi_normal;

uniform vec4 u_voxelgi_p0;
#define u_voxelgi_extents u_voxelgi_p0.xyz

uniform vec4 u_voxelgi_p1;
#define u_voxelgi_subdiv u_voxelgi_p1.xyz

uniform highp mat4 u_gi_probe_transform;

uniform highp vec4 u_gi_probe_bounds4;
#define u_gi_probe_bounds u_gi_probe_bounds4.xyz

uniform highp vec4 u_gi_probe_inv_extents4;
#define u_gi_probe_inv_extents u_gi_probe_inv_extents4.xyz

uniform highp vec4 u_gi_probe_inv_cell_size4;
#define u_gi_probe_cell_size u_gi_probe_inv_cell_size4.xyz

uniform highp vec4 u_gi_probe_p0;
#define u_gi_probe_diffuse          u_gi_probe_p0.x
#define u_gi_probe_specular         u_gi_probe_p0.y
#define u_gi_probe_bias             u_gi_probe_p0.z
#define u_gi_probe_normal_bias      u_gi_probe_p0.w
//#define u_gi_probe_blend_ambient    u_gi_probe_p0.w

CONST(float) u_gi_probe_blend_ambient = 0.0;

#define VOXELGI_RESOLUTION_Z 1.0

#endif

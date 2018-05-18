
//SAMPLER2D(s_skybox_map, 0);
#define s_skybox_map s_source_0

uniform mat4 u_skybox_matrix;

uniform vec4 u_skybox_params;
#define u_skybox_level u_skybox_params.x
#define u_skybox_invert u_skybox_params.y


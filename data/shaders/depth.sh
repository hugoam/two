uniform highp vec4 u_depth_params;
#define u_depth_bias u_depth_params.x
#define u_depth_normal_bias u_depth_params.y
            
void render_depth(vec3 normal, inout vec3 vertex)
{
	vertex.z -= u_depth_bias;
	vertex.z -= (1.0 - abs(normal.z)) * u_depth_normal_bias;
}

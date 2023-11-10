uniform highp vec4 u_distance_p0;
#define u_eye u_distance_p0.xyz

uniform highp vec4 u_distance_p1;
#define u_near_distance u_distance_p1.x
#define u_far_distance u_distance_p1.y

uniform highp vec4 u_depth_p0;
#define u_depth_bias u_depth_p0.x
#define u_depth_normal_bias u_depth_p0.y
            
void render_depth(vec3 normal, inout vec3 vertex)
{
    vertex.z -= u_depth_bias;
    vertex.z -= (1.0 - abs(normal.z)) * u_depth_normal_bias;
}

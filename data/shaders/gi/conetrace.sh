#ifndef MUD_SHADER_CONETRACE
#define MUD_SHADER_CONETRACE

#include <common.sh>
#include <encode.sh>
#include <convert.sh>
#include <gi/gi.sh>

#define CONETRACE_MAT3

SAMPLER3D(s_gi_probe, 14);

CONST(float) sqrt2 = 1.41421356237;

#if 1 //def VCT_QUALITY_HIGH
#define NUM_CONES 6
    CONST(ARRAY_BEGIN(vec3, cone_dirs, NUM_CONES))
		vec3( 0,         0,        1),
		vec3( 0.866025,  0,        0.5),
		vec3( 0.267617,  0.823639, 0.5),
		vec3(-0.700629,  0.509037, 0.5),
		vec3(-0.700629, -0.509037, 0.5),
		vec3( 0.267617, -0.823639, 0.5)
    ARRAY_END();

	CONST(ARRAY_BEGIN(float, cone_weights, NUM_CONES)) 0.25, 0.15, 0.15, 0.15, 0.15, 0.15 ARRAY_END();
	CONST(float) cone_angle_tan = 0.577;
    CONST(float) cone_distance_factor = 1.0;
	CONST(float) min_ref_tan = 0.0;
#else
#define NUM_CONES 4
    CONST(ARRAY_BEGIN(vec3, cone_dirs, NUM_CONES))
        vec3( 0.707107,  0,        0.707107),
        vec3( 0,         0.707107, 0.707107),
        vec3(-0.707107,  0,        0.707107),
        vec3( 0,        -0.707107, 0.707107)
    ARRAY_END();

	CONST(ARRAY_BEGIN(float, cone_weights, NUM_CONES)) 0.25, 0.25, 0.25, 0.25 ARRAY_END();
	CONST(float) cone_angle_tan = 0.98269;
    CONST(float) cone_distance_factor = 0.5;
	CONST(float) min_ref_tan = 0.2;
#endif

vec3 cone_trace(sampler3D probe, vec3 inv_extents, vec3 pos, vec3 direction, float tan_half_angle, float max_distance, float bias)
{
    float dist = bias;
    float alpha = 0.0;
    vec3 color = vec3_splat(0.0);

    while(dist < max_distance && alpha < 0.95) {
        float diameter = max(1.0, 2.0 * tan_half_angle * dist);
        vec3 coord = (pos + dist * direction) * inv_extents * 0.5 + 0.5;
        vec4 scolor = texture3DLod(probe, coord, log2(diameter));
        float a = (1.0 - alpha);
        color += a * scolor.rgb;
        alpha += a * scolor.a;
        dist += diameter * 0.5;
    }
    
	return color * alpha;
}

#if 0
mat3 cone_normal_mat(vec3 n, vec3 t, vec3 b, mat4 probe)
{
    vec3 nloc = mul(probe, vec4(n, 0.0)).xyz;
    vec3 bloc = mul(probe, vec4(b, 0.0)).xyz;
    vec3 tloc = mul(probe, vec4(t, 0.0)).xyz;
    mat3 normal_mat = mat3(tloc, bloc, nloc);
#if BGFX_SHADER_LANGUAGE_HLSL
    return normal_mat;
#else
    return transpose(normal_mat);
#endif
}
#endif

mat3 cone_normal_mat(vec3 normal)
{
	//find arbitrary tangent and bitangent, then build a matrix
	vec3 v0 = abs(normal.z) < 0.999 ? vec3(0, 0, 1) : vec3(0, 1, 0);
	vec3 tangent = normalize(cross(v0, normal));
	vec3 bitangent = normalize(cross(tangent, normal));
	mat3 normal_mat = mat3(tangent, bitangent, normal);
#if BGFX_SHADER_LANGUAGE_HLSL
    return normal_mat;
#else
    return transpose(normal_mat);
#endif
}

vec3 cone_direction_mat(vec3 direction, mat3 normal_mat)
{
	vec3 dir = normalize(mul(normal_mat, direction));
    return dir;
}

vec3 cone_direction(vec3 normal, vec3 direction)
{
    vec3 dir = normalize(direction + normal);
    // if point on sphere is facing below normal (so it's located on bottom hemisphere), put it on the opposite hemisphere instead:
    float dotsign = dot(dir, normal) < 0.0 ? -1.0 : 1.0;
    return dir * dotsign;
}

vec3 debug_trace_diffuse(sampler3D probe, vec3 normal, mat3 normal_mat)
{
	vec3 light = vec3_splat(0.0);
	for(int i = 0; i < NUM_CONES; i++)
    {
        vec3 dir = cone_direction_mat(cone_dirs[i], normal_mat);
        light += dir;
	}
    light /= float(NUM_CONES);
    return abs(normalize(light) - normal);
}

vec3 trace_diffuse(sampler3D probe, vec3 pos, vec3 normal, mat3 normal_mat, float bias)
{
	float max_distance = length(u_gi_probe_bounds) * cone_distance_factor;
	
	vec3 light = vec3_splat(0.0);
	for(int i = 0; i < NUM_CONES; i++)
    {
        vec3 dir = cone_direction_mat(cone_dirs[i], normal_mat);
        //bias = length(u_gi_probe_cell_size * direction);
		light += cone_weights[i] * cone_trace(probe, u_gi_probe_inv_extents, pos, dir, cone_angle_tan, max_distance, bias);
	}

    //light = cone_direction_mat(cone_dirs[0], normal_mat);
    return light;
}

vec3 debug_trace_diffuse(sampler3D probe, vec3 normal)
{
	vec3 light = vec3_splat(0.0);
	for(int i = 0; i < NUM_CONES; i++)
    {
        vec3 dir = cone_direction(cone_dirs[i], normal);
        light += dir;
	}
    light /= float(NUM_CONES);
    return abs(normalize(light) - normal);
}

vec3 trace_diffuse(sampler3D probe, vec3 pos, vec3 normal, float bias)
{
	float max_distance = length(u_gi_probe_bounds) * cone_distance_factor;
	
	vec3 light = vec3_splat(0.0);
	for(int i = 0; i < NUM_CONES; i++)
    {
        vec3 dir = cone_direction(cone_dirs[i], normal);
        //bias = length(u_gi_probe_cell_size * direction);
		light += cone_weights[i] * cone_trace(probe, u_gi_probe_inv_extents, pos, dir, cone_angle_tan, max_distance, bias);
	}

    //light = cone_direction(cone_dirs[0], normal);
    return light;
}

vec3 trace_specular(sampler3D probe, vec3 pos, vec3 refl_vec, float roughness, float bias)
{
	float max_distance = length(u_gi_probe_bounds) * cone_distance_factor;
    float tan_half_angle = max(min_ref_tan, tan(roughness * 0.5 * PI));
    
    return vec3_splat(0.0);
	return cone_trace(probe, u_gi_probe_inv_extents, pos, refl_vec, tan_half_angle, max_distance, bias);
}

vec3 gi_probe_debug(vec3 pos, float lod)
{
	vec3 probe_pos = mul(u_gi_probe_transform, vec4(pos, 1.0)).xyz;
    vec3 probe_coord = probe_pos * u_gi_probe_inv_extents * 0.5 + 0.5; // [-1,1] to [0,1]
    if(!( any(greaterThan(probe_coord, vec3_splat(1.0))) 
       || any(lessThan(probe_coord, vec3_splat(0.0))) ))
    {
        vec4 probe_color = texture3DLod(s_gi_probe, probe_coord, lod);
        //return probe_coord;
        return probe_color.rgb;
    }
    return vec3_splat(0.0);
}

struct ConeStart
{
    vec3 pos;
    vec3 normal;
    vec3 refl;
#ifdef CONETRACE_MAT3
    mat3 normal_mat;
#endif
};

ConeStart cone_start(vec3 pos, vec3 normal)
{
    ConeStart cone;
    
	cone.pos = mul(u_gi_probe_transform, vec4(pos, 1.0)).xyz;
    cone.normal = mul(u_gi_probe_transform, vec4(normal, 0.0)).xyz;
	cone.pos += cone.normal * u_gi_probe_normal_bias;
    
	vec3 refl = normalize(reflect(normalize(pos), normal));
	cone.refl = mul(u_gi_probe_transform, vec4(refl, 0.0)).xyz;
    
#ifdef CONETRACE_MAT3
    cone.normal_mat = cone_normal_mat(cone.normal);
#endif

    return cone;
}

void trace_gi_probe(ConeStart cone, float roughness, inout vec3 diffuse, inout vec3 specular)
{
    vec3 extents = u_gi_probe_bounds * 0.5;
	if (any(bvec2(any(lessThan(cone.pos, -extents)), any(greaterThan(cone.pos, extents))))) {
		return;
	}

#ifdef CONETRACE_MAT3
    vec3 probe_diffuse = trace_diffuse(s_gi_probe, cone.pos, cone.normal, cone.normal_mat, u_gi_probe_bias) * u_gi_probe_diffuse;
#else
    vec3 probe_diffuse = trace_diffuse(s_gi_probe, cone.pos, cone.normal, u_gi_probe_bias) * u_gi_probe_diffuse;
#endif
    vec3 probe_specular = trace_specular(s_gi_probe, cone.pos, cone.refl, roughness * roughness, u_gi_probe_bias) * u_gi_probe_specular;
    
	if (bool(u_gi_probe_blend_ambient))
    {
		diffuse = probe_diffuse; //mix(diffuse, probe_diffuse.rgb, min(1.0, probe_diffuse.a / 0.95));
		specular = probe_specular; //mix(specular, probe_specular.rgb, min(1.0, probe_specular.a / 0.95));
	}
    else
    {
        diffuse = probe_diffuse;
        specular = probe_specular;
    }
}

#if 0
static const float3 CONES[] = 
{
	float3( 0.57735,   0.57735,   0.57735),
	float3( 0.57735,  -0.57735,  -0.57735),
	float3(-0.57735,   0.57735,  -0.57735),
	float3(-0.57735,  -0.57735,   0.57735),
	float3(-0.903007, -0.182696, -0.388844),
	float3(-0.903007,  0.182696,  0.388844),
	float3( 0.903007, -0.182696,  0.388844),
	float3( 0.903007,  0.182696, -0.388844),
	float3(-0.388844, -0.903007, -0.182696),
	float3( 0.388844, -0.903007,  0.182696),
	float3( 0.388844,  0.903007, -0.182696),
	float3(-0.388844,  0.903007,  0.182696),
	float3(-0.182696, -0.388844, -0.903007),
	float3( 0.182696,  0.388844, -0.903007),
	float3(-0.182696,  0.388844,  0.903007),
	float3( 0.182696, -0.388844,  0.903007)
};
#endif

#endif

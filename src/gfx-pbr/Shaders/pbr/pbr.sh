#ifndef TWO_SHADER_PBR
#define TWO_SHADER_PBR

#include <common.sh>
#include <srgb.sh>
#include <gpu/material.sh>

SAMPLER2D(s_albedo, 0);
SAMPLER2D(s_metallic, 1);
SAMPLER2D(s_roughness, 2);
SAMPLER2D(s_emissive, 3);

#ifdef NORMAL_MAP
SAMPLER2D(s_normal, 4);
#endif

#ifdef DEPTH_MAPPING
SAMPLER2D(s_depth, 12);
#endif

#ifdef AMBIENT_OCCLUSION
SAMPLER2D(s_ambient_occlusion, 11);
#endif

#ifdef LIGHTMAP
SAMPLER2D(s_lightmap, 7);
#endif

#if 0
SAMPLER2D(s_anisotropy, 6);
SAMPLER2D(s_refraction, 7);
SAMPLER2D(s_subsurface, 8);
SAMPLER2D(s_rim, 9);
SAMPLER2D(s_clearcoat, 10);

SAMPLER2D(s_albedo_detail, 11);
SAMPLER2D(s_normal_detail, 12);
#endif

uniform vec4 u_lightmap_params;
#define u_lightmap_offset u_lightmap_params.xy
#define u_lightmap_factor u_lightmap_params.zw

struct Fragment
{
    vec4 coord;
    vec3 position;
    float depth;
    vec3 view;
    vec3 normal;
    vec3 binormal;
    vec3 tangent;
    vec2 uv;
    vec2 uv2;
    vec4 color;
    
    float NoV;
};

struct Material
{
    vec3 albedo;
    float roughness;
    float metallic;
    float specular;
    vec3 f0;
    float alpha;
    float ao;
    float anisotropy;
    float rim;
    float clearcoat;
    float clearcoat_gloss;
};

struct Radiance
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#endif



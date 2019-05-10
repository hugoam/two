#ifndef MUD_SHADER_PBR
#define MUD_SHADER_PBR

#include <common.sh>
#include <srgb.sh>
#include <gpu/material.sh>

SAMPLER2D(s_albedo, 0);
SAMPLER2D(s_metallic, 2);
SAMPLER2D(s_roughness, 3);

SAMPLER2D(s_diffuse, 0);
SAMPLER2D(s_specular, 2);
SAMPLER2D(s_shininess, 3);

#ifdef EMISSIVE
SAMPLER2D(s_emissive, 4);
#endif

#ifdef NORMAL_MAP
SAMPLER2D(s_normal, 5);
#endif

#ifdef AMBIENT_OCCLUSION
SAMPLER2D(s_ambient_occlusion, 6);
#endif

#ifdef DEPTH_MAPPING
SAMPLER2D(s_depth, 7);
#endif

#ifdef LIGHTMAP
SAMPLER2D(s_lightmap, 12);
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

uniform vec4 u_lightmap_p0;
#define u_lightmap_offset u_lightmap_p0.xy
#define u_lightmap_factor u_lightmap_p0.zw

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
    float cNoV;
};

struct Material
{
    vec3 albedo;
    float alpha;
    float roughness;
    float metallic;
    float specular;
    vec3 f0;
    float refraction;
    float ao;
    float anisotropy;
    float rim;
    float clearcoat;
    float clearcoat_gloss;
};

struct Radiance
{
    vec3 diffuse;
    vec3 specular;
};

#endif



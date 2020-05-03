#ifndef TWO_SHADER_PBR
#define TWO_SHADER_PBR

#include <common.sh>
#include <srgb.sh>
#include <gpu/material.sh>

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



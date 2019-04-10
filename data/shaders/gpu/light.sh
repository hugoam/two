#ifndef MUD_GPU_LIGHT
#define MUD_GPU_LIGHT

#define LIGHTS_TEXTURE_WIDTH 1024
#define LIGHTS_TEXTURE_HEIGHT 9

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(LIGHTS_TEXTURE_WIDTH), float(LIGHTS_TEXTURE_HEIGHT)), _level)
#endif

#ifdef LIGHTS_BUFFER
SAMPLER2D(s_lights, 9);
#else
uniform vec4 u_light_position_range[MAX_LIGHTS];
uniform vec4 u_light_energy_specular[MAX_LIGHTS];
uniform vec4 u_light_direction_attenuation[MAX_LIGHTS];
uniform vec4 u_light_spot_p0[MAX_LIGHTS];
uniform vec4 u_light_shadow_p0[MAX_LIGHTS];
uniform vec4 u_light_shadowmap_p0[MAX_LIGHTS];
uniform vec4 u_light_csm_p0[MAX_LIGHTS];
uniform vec4 u_light_csm_p1[MAX_LIGHTS];
uniform vec4 u_light_csm_p2[MAX_LIGHTS];
#endif

uniform vec4 u_skylight_p0;
uniform vec4 u_skylight_p1;
uniform vec4 u_skylight_p2;

struct Shadow
{
    int index;
    float bias;
    float radius;
    float range;
    vec2 atlas_slot;
    vec2 atlas_subdiv;
};

struct CSMShadow
{
    int count;
    ivec4 matrices;
    vec4 splits;
};

struct Light
{
    vec3 position;
    float range;
    vec3 energy;
    float specular;
    vec3 direction;
    float attenuation;
    float spot_attenuation;
    float spot_cutoff;
    float spot_inner;
};

struct Skylight
{
    vec3 direction;
    vec3 color;
    vec3 ground;
};

Skylight read_skylight()
{
    Skylight skylight;
    
    skylight.direction = u_skylight_p0.xyz;
    skylight.color = u_skylight_p1.xyz;
    skylight.ground = u_skylight_p2.xyz;
    
    return skylight;
}

Light read_light(int index)
{
    Light light;
    
#ifndef LIGHTS_BUFFER
    light.position = u_light_position_range[index].xyz;
    light.range = u_light_position_range[index].w;
    light.energy = u_light_energy_specular[index].xyz;
    light.specular = u_light_energy_specular[index].w;
    light.direction = u_light_direction_attenuation[index].xyz;
    light.attenuation = u_light_direction_attenuation[index].w;
    light.spot_attenuation = u_light_spot_p0[index].x;
    light.spot_cutoff = u_light_spot_p0[index].y;
    light.spot_inner = light.spot_cutoff; //@todo
#else
    int x = int(mod(index, LIGHTS_TEXTURE_WIDTH));
    
    vec4 position_range = texelFetch(s_lights, ivec2(x, 0), 0);
    light.position = position_range.xyz;
    light.range = position_range.w;
    
    vec4 energy_specular = texelFetch(s_lights, ivec2(x, 1), 0);
    light.energy = energy_specular.xyz;
    light.specular = energy_specular.w;
    
    vec4 direction_attenuation = texelFetch(s_lights, ivec2(x, 2), 0);
    light.direction = direction_attenuation.xyz;
    light.attenuation = direction_attenuation.w;
    
    vec4 spot_p0 = texelFetch(s_lights, ivec2(x, 3), 0);
    light.spot_attenuation = spot_p0.x;
    light.spot_cutoff = spot_p0.y;
    light.spot_inner = light.spot_cutoff; //@todo
#endif

    return light;
}

Shadow read_shadow(int index)
{
    Shadow shadow;
    
#ifndef LIGHTS_BUFFER
    shadow.index = int(u_light_shadow_p0[index].x);
    shadow.bias = u_light_shadow_p0[index].y;
    shadow.radius = u_light_shadow_p0[index].z;
    shadow.range = u_light_shadow_p0[index].w;
    shadow.atlas_slot = u_light_shadowmap_p0[index].xy;
    shadow.atlas_subdiv = u_light_shadowmap_p0[index].zw;
#else
    int x = int(mod(index, LIGHTS_TEXTURE_WIDTH));
    
    vec4 shadow_p0 = texelFetch(s_lights, ivec2(x, 4), 0);
    shadow.index = int(shadow_p0.x);
    shadow.bias = shadow_p0.y;
    shadow.radius = shadow_p0.z;
    shadow.range = shadow_p0.w;
    
    vec4 shadowmap_p0 = texelFetch(s_lights, ivec2(x, 5), 0);
    shadow.atlas_slot = shadowmap_p0.xy;
    shadow.atlas_subdiv = shadowmap_p0.zw;
#endif
    
    return shadow;
}

CSMShadow read_csm_shadow(int index)
{
    CSMShadow csm;
    
#ifndef LIGHTS_BUFFER
    csm.count = int(u_light_csm_p0[index].x);
    csm.matrices = ivec4(u_light_csm_p1[index]);
    csm.splits = u_light_csm_p2[index];
#else
    int x = int(mod(index, LIGHTS_TEXTURE_WIDTH));
    
    vec4 csm_p0 = texelFetch(s_lights, ivec2(x, 6), 0);
    csm.count = int(csm_p0.x);
    
    vec4 csm_p1 = texelFetch(s_lights, ivec2(x, 7), 0);
    csm.matrices = ivec4(csm_p1);
    
    vec4 csm_p2 = texelFetch(s_lights, ivec2(x, 8), 0);
    csm.splits = csm_p2;
#endif
    
    return csm;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

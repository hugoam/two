#ifndef MUD_GPU_LIGHT
#define MUD_GPU_LIGHT

#define LIGHTS_TEXTURE_WIDTH 1024
#define LIGHTS_TEXTURE_HEIGHT 5

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(LIGHTS_TEXTURE_WIDTH), float(LIGHTS_TEXTURE_HEIGHT)), _level)
#endif

#ifdef LIGHTS_BUFFER
SAMPLER2D(s_lights, 9);
#else
uniform vec4 u_light_position_range[MAX_LIGHTS];
uniform vec4 u_light_energy_specular[MAX_LIGHTS];
uniform vec4 u_light_direction_attenuation[MAX_LIGHTS];
uniform vec4 u_light_spot_params[MAX_LIGHTS];
uniform vec4 u_light_shadow_params[MAX_LIGHTS];
uniform vec4 u_light_shadowmap_params[MAX_LIGHTS];
#endif

struct Shadow
{
    int index;
    float bias;
    float radius;
    vec2 atlas_slot;
    vec2 atlas_subdiv;
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
    bool shadows;
    Shadow shadow;
};

Shadow read_shadow(int index);

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
    light.spot_attenuation = u_light_spot_params[index].x;
    light.spot_cutoff = u_light_spot_params[index].y;
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
    
    vec4 spot_params = texelFetch(s_lights, ivec2(x, 3), 0);
    light.spot_attenuation = spot_params.x;
    light.spot_cutoff = spot_params.y;
    light.spot_inner = light.spot_cutoff; //@todo
#endif

    light.shadow = read_shadow(index);
    light.shadows = light.shadow.index != MAX_SHADOWS;
    
    return light;
}

Shadow read_shadow(int index)
{
    Shadow shadow;
    
#ifndef LIGHTS_BUFFER
    shadow.index = int(u_light_shadow_params[index].x);
    shadow.bias = u_light_shadow_params[index].y;
    shadow.radius = u_light_shadow_params[index].z;
    shadow.atlas_slot = u_light_shadowmap_params[index].xy;
    shadow.atlas_subdiv = u_light_shadowmap_params[index].zw;
#else
    int x = int(mod(index, LIGHTS_TEXTURE_WIDTH));
    
    vec4 shadow_params = texelFetch(s_lights, ivec2(x, 4), 0);
    shadow.index = int(shadow_params.x);
    shadow.bias = shadow_params.y;
    shadow.radius = shadow_params.z;
    
    vec4 shadowmap_params = texelFetch(s_lights, ivec2(x, 5), 0);
    shadow.atlas_slot = shadowmap_params.xy;
    shadow.atlas_subdiv = shadowmap_params.zw;
#endif
    
    return shadow;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

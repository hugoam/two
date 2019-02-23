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
uniform vec4 u_light_shadow[MAX_SHADOWS];
uniform mat4 u_light_shadow_matrix[MAX_SHADOWS];
#endif

struct LightShadow
{
    int shadow;
    float shadowBias;
    float shadowRadius;
    vec2 shadowMapSize;
};

Light read_light(int index)
{
    Light light;
    
#ifndef LIGHTS_BUFFER
    light.shadow_color = u_light_shadow[index].xyz;
    light.shadows = bool(u_light_shadow[index].w);
#else
    int x = int(mod(index, LIGHTS_TEXTURE_WIDTH));
    
    vec4 shadow_enabled_color = texelFetch(s_lights, ivec2(x, 3), 0);
    light.shadows = bool(shadow_enabled_color.x);
    light.shadow_color = shadow_enabled_color.yzw;
#endif

    return light;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

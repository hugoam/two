#ifndef MUD_GPU_ZONE
#define MUD_GPU_ZONE

#define ZONES_TEXTURE_WIDTH 1024
#define ZONES_TEXTURE_HEIGHT 6

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(ZONES_TEXTURE_WIDTH), float(ZONES_TEXTURE_HEIGHT)), _level)
#endif

#ifdef ZONES_BUFFER
SAMPLER2D(s_zones, 9);
#else
uniform vec4 u_ambient_p0;
uniform vec4 u_radiance_p0;
#endif

struct Zone
{
    vec3 ambient;
    vec3 radiance;
    float energy;
};

Zone read_zone(int index)
{
    Zone z;
    
#ifndef ZONES_BUFFER
    z.radiance = u_radiance_p0.xyz;
    z.energy = 1.0;
    z.ambient = u_ambient_p0.xyz;
#else
    int x = int(mod(index, ZONES_TEXTURE_WIDTH));
    
    vec4 radiance = texelFetch(s_zones, ivec2(x, 0), 0);
    z.radiance = radiance.xyz;
    z.energy = 1.0;
    
    vec4 ambient = texelFetch(s_zones, ivec2(x, 1), 0);
    z.ambient = ambient.xyz;
#endif

    return z;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

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
uniform vec4 u_radiance_p0;
uniform vec4 u_ambient_p0;
#endif

struct Zone
{
    float ambient;
    vec3 radiance_color;
    float radiance_energy;
};

Zone read_zone(int index)
{
    Zone z;
    
#ifndef ZONES_BUFFER
    z.radiance_color = u_radiance_p0.rgb;
    z.radiance_energy = u_radiance_p0.w;
    z.ambient = u_ambient_p0.x;
#else
    int x = int(mod(index, ZONES_TEXTURE_WIDTH));
    
    vec4 radiance_color_energy = texelFetch(s_zones, ivec2(x, 0), 0);
    z.radiance_color = radiance_color_energy.rgb;
    z.radiance_energy = radiance_color_energy.w;
    
    vec4 ambient = texelFetch(s_zones, ivec2(x, 1), 0);
    z.ambient = ambient.x;
#endif

    return z;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

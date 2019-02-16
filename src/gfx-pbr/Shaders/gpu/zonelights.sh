#ifndef MUD_GPU_ZONELIGHTS
#define MUD_GPU_ZONELIGHTS

struct ZoneLights
{
    vec4 light_counts;
    vec4 light_indices[MAX_LIGHTS];
};

ZoneLights read_zone_lights(int index)
{
    ZoneLights z;
    
#ifndef ZONES_BUFFER
    z.light_counts = u_light_counts;
    z.light_indices = u_light_indices;
#else
    int x = int(mod(index, ZONES_TEXTURE_WIDTH));
    
    z.light_counts = texelFetch(s_materials, ivec2(x, 0), 0);
    
	for(int i = 0; i < int(MAX_LIGHTS); i++)
    {
        z.light_indices[i] = texelFetch(s_materials, ivec2(x, 1 + i), 0);
    }
#endif

    return m;
}

#endif

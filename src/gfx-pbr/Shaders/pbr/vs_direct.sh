
v_light = vec3_splat(0.0);
#ifdef DOUBLE_SIDED
v_light_back = vec3_splat(0.0);
#endif

int i = 0;

for(i = 0; i < int(u_light_counts[LIGHT_DIRECT]); i++)
{
    Light direct = read_light(int(u_light_indices[i][LIGHT_DIRECT]));
    
    float dotNL = dot(v_normal, -direct.direction);
    vec3 diffuse = PI * direct.energy;

    v_light += saturate(dotNL) * diffuse;
#ifdef DOUBLE_SIDED
    v_light_back += saturate(-dotNL) * diffuse;
#endif
}

for(i = 0; i < int(u_light_counts[LIGHT_POINT]); i++)
{
    Light light = read_light(int(u_light_indices[i][LIGHT_POINT]));
    vec3 l = light.position - v_view;
    float a = omni_attenuation(l, light);
    
    float dotNL = dot(v_normal, normalize(l));
    vec3 diffuse = PI * light.energy * a;

    v_light += saturate(dotNL) * diffuse;
#ifdef DOUBLE_SIDED
    v_light_back += saturate(-dotNL) * diffuse;
#endif
}

for(i = 0; i < int(u_light_counts[LIGHT_SPOT]); i++)
{
    Light light = read_light(int(u_light_indices[i][LIGHT_SPOT]));
    vec3 l = light.position - v_view;
    float a = spot_attenuation(l, light); // * (i < int(u_shadow_counts[LIGHT_SPOT]) ? spot_shadows[i] : 1.0);

    float dotNL = dot(v_normal, normalize(l));
    vec3 diffuse = PI * light.energy * a;

    v_light += saturate(dotNL) * diffuse;
#ifdef DOUBLE_SIDED
    v_light_back += saturate(-dotNL) * diffuse;
#endif
}

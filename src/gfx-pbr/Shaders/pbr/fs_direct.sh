
int i = 0;

#ifdef SHADOWS
float direct_shadows[4];
float point_shadows[MAX_LIGHTS];
float spot_shadows[MAX_LIGHTS];

for(i = 0; i < int(u_shadow_counts[LIGHT_DIRECT]); i++)
{
    CSMShadow shadow = read_csm_shadow(int(u_light_indices[i][LIGHT_DIRECT]));
    direct_shadows[i] = shadow_csm(shadow, fragment.position, fragment.depth);
}

for(i = 0; i < int(u_shadow_counts[LIGHT_POINT]); i++)
{
    Shadow shadow = read_shadow(int(u_light_indices[i][LIGHT_POINT]));
    point_shadows[i] = shadow_point(shadow, fragment.position);
}

for(i = 0; i < int(u_shadow_counts[LIGHT_SPOT]); i++)
{
    Shadow shadow = read_shadow(int(u_light_indices[i][LIGHT_SPOT]));
    spot_shadows[i] = shadow_spot(shadow, fragment.position);
}
#endif

for(i = 0; i < int(u_light_counts[LIGHT_DIRECT]); i++)
{
    Light direct = read_light(int(u_light_indices[i][LIGHT_DIRECT]));
    float factor = 1.0;
#ifdef SHADOWS
    factor *= (i < int(u_shadow_counts[LIGHT_DIRECT]) ? direct_shadows[i] : 1.0);
#endif
    direct_brdf(direct.energy * factor, -direct.direction, fragment, material, diffuse, specular);
}

for(i = 0; i < int(u_light_counts[LIGHT_POINT]); i++)
{
    Light light = read_light(int(u_light_indices[i][LIGHT_POINT]));
    vec3 l = light.position - fragment.position;
    float a = omni_attenuation(l, light);
#ifdef SHADOWS
    a *= (i < int(u_shadow_counts[LIGHT_POINT]) ? point_shadows[i] : 1.0);
#endif
    direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
}

for(i = 0; i < int(u_light_counts[LIGHT_SPOT]); i++)
{
    Light light = read_light(int(u_light_indices[i][LIGHT_SPOT]));
    vec3 l = light.position - fragment.position;
    float a = spot_attenuation(l, light);
#ifdef SHADOWS
    a *= (i < int(u_shadow_counts[LIGHT_SPOT]) ? spot_shadows[i] : 1.0);
#endif
    direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
}

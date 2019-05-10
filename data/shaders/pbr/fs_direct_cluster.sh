
uint cluster_index = cluster_index(fragment.coord.xyz);
LightCluster cluster = read_cluster(cluster_index);

uint offset = cluster.record_offset;

int i  = 0;

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

offset = cluster.record_offset;

for(i = 0; i < int(u_light_counts[LIGHT_DIRECT]); i++)
{
    Light direct = read_light(int(u_light_indices[i][LIGHT_DIRECT]));
    float factor = 1.0;
#ifdef SHADOWS
    factor *= direct_shadows[i];
#endif
    direct_brdf(direct.energy * factor, -direct.direction, fragment, material, diffuse, specular);
}

for(uint last_point = offset + cluster.point_count; offset < last_point; offset++)
{
    int index = clustered_light_index(offset);
    Light light = read_light(index);
    vec3 l = light.position - fragment.position;
    float a = omni_attenuation(l, light);
#ifdef SHADOWS
    a *= (index < int(u_shadow_counts[LIGHT_POINT]) ? point_shadows[index] : 1.0);
#endif
    direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
}

for(uint last_spot = offset + cluster.spot_count; offset < last_spot; offset++)
{
    int index = clustered_light_index(offset);
    Light light = read_light(index);
    vec3 l = light.position - fragment.position;
    float a = spot_attenuation(l, light);
#ifdef SHADOWS
    a *= (index < int(u_shadow_counts[LIGHT_SPOT]) ? spot_shadows[index] : 1.0);
#endif
    direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
}

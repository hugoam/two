#ifndef MUD_LIGHT_CLUSTER
#define MUD_LIGHT_CLUSTER

#include <common.sh>
#include <pbr/pbr.sh>
#include <gpu/light.sh>

uniform vec4 u_cluster_p0;
uniform vec4 u_cluster_z;
uniform vec4 u_cluster_f;
#define u_cluster_inv_dimension u_cluster_p0.xy
#define u_cluster_origin u_cluster_p0.zw

SAMPLER2D(s_light_clusters, 13);
SAMPLER2D(s_light_records, 14);
//USAMPLER2D(s_light_clusters, 13);
//USAMPLER2D(s_light_records, 14);
    
#define CLUSTER_BUFFER_WIDTH_SHIFT  6u
#define CLUSTER_BUFFER_WIDTH        (1u << CLUSTER_BUFFER_WIDTH_SHIFT)
#define CLUSTER_BUFFER_WIDTH_MASK   (CLUSTER_BUFFER_WIDTH - 1u)

#define RECORD_BUFFER_WIDTH_SHIFT   5u
#define RECORD_BUFFER_WIDTH         (1u << RECORD_BUFFER_WIDTH_SHIFT)
#define RECORD_BUFFER_WIDTH_MASK    (RECORD_BUFFER_WIDTH - 1u)

struct LightCluster
{
    uint record_offset; // offset at which the list of lights for this cluster starts
    uint point_count;   // number of point lights in this cluster
    uint spot_count;    // number of spot lights in this cluster
};

uvec3 cluster_coord(vec3 frag_coord)
{
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	frag_coord.y = u_screen_size.y - frag_coord.y;
#endif
    uvec3 cluster_coord;
    cluster_coord.xy = uvec2((frag_coord.xy - u_cluster_origin) * u_cluster_inv_dimension);
    cluster_coord.z = uint(max(0.0, log2(u_cluster_z.x * frag_coord.z + u_cluster_z.y) * u_cluster_z.z + u_cluster_z.w));
    return cluster_coord;
}

uint cluster_index(vec3 frag_coord)
{
    uvec3 cluster_coord = cluster_coord(frag_coord);
    return cluster_coord.x * uint(u_cluster_f.x) +
           cluster_coord.y * uint(u_cluster_f.y) +
           cluster_coord.z * uint(u_cluster_f.z);
}

ivec2 cluster_uv(uint cluster_index)
{
    return ivec2(cluster_index & CLUSTER_BUFFER_WIDTH_MASK, cluster_index >> CLUSTER_BUFFER_WIDTH_SHIFT);
}

LightCluster read_cluster(uint cluster_index)
{
    ivec2 uv = cluster_uv(cluster_index);
    //uvec2 entry = texelFetch(s_light_clusters, uv, 0).rg;
    uvec2 entry = uvec2(texelFetch(s_light_clusters, uv, 0).rg * 65535.0);

    LightCluster cluster;
    cluster.record_offset = entry.r;
    cluster.point_count = entry.g & 0xFFu;
    cluster.spot_count = entry.g >> 8u;
    return cluster;
}

ivec2 record_uv(uint index)
{
    return ivec2(index & RECORD_BUFFER_WIDTH_MASK, index >> RECORD_BUFFER_WIDTH_SHIFT);
}

int clustered_light_index(uint record_offset)
{
    ivec2 uv = record_uv(record_offset);
    //uint light_index = texelFetch(s_light_records, uv, 0).r;
    uint light_index = uint(texelFetch(s_light_records, uv, 0).r * 255.0);
    return int(light_index);
}

#endif

#ifndef MUD_GPU_MATERIAL
#define MUD_GPU_MATERIAL

#define MATERIALS_BUFFER
#define MATERIALS_TEXTURE_WIDTH 1024
#define MATERIALS_TEXTURE_HEIGHT 8

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(MATERIALS_TEXTURE_WIDTH), float(MATERIALS_TEXTURE_HEIGHT)), _level)
#endif

#ifdef MATERIALS_BUFFER
SAMPLER2D(s_materials, 7);
#else
uniform vec4 u_material_params_0;
uniform vec4 u_material_params_1;
#endif

struct BaseMaterial
{
    vec2 uv0_scale;
    vec2 uv0_offset;
    vec2 uv1_scale;
    vec2 uv1_offset;
};

BaseMaterial read_base_material(int index)
{
    BaseMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.uv0_scale = u_material_params_0.xy;
    m.uv0_offset = u_material_params_0.zw;
    m.uv1_scale = u_material_params_1.xy;
    m.uv1_offset = u_material_params_1.zw;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    
    vec4 uv0_scale_offset = texelFetch(s_materials, ivec2(x, 0), 0);
    m.uv0_scale = uv0_scale_offset.xy;
    m.uv0_offset = uv0_scale_offset.zw;
    
    vec4 uv1_scale_offset = texelFetch(s_materials, ivec2(x, 1), 0);
    m.uv1_scale = uv1_scale_offset.xy;
    m.uv1_offset = uv1_scale_offset.zw;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_color;
#endif

struct UnshadedMaterial
{
    vec4 color;
};

UnshadedMaterial read_unshaded_material(int index)
{
    UnshadedMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.color = u_color;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    
    m.color = texelFetch(s_materials, ivec2(x, 2), 0);
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_albedo;
uniform vec4 u_pbr_params_0;
uniform vec4 u_emissive;
uniform vec4 u_pbr_channels_0;
uniform vec4 u_pbr_params_1;
uniform vec4 u_pbr_params_2;
#endif

struct PbrMaterial
{
    vec3 albedo;
    float specular;
    float metallic;
    float roughness;
    float normal_scale;
    vec3 emissive;
    float emissive_energy;
    float roughness_channel;
    float metallic_channel;
    float anisotropy;
    float refaction;
    float subsurface;
    float depth_scale;
    float rim;
    float rim_tint;
    float clearcoat;
    float clearcoat_gloss;
};

PbrMaterial read_pbr_material(int index)
{
    PbrMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.albedo = u_albedo.xyz;
    m.specular = u_pbr_params_0.x;
    m.metallic = u_pbr_params_0.y;
    m.roughness = u_pbr_params_0.z;
    m.normal_scale = u_pbr_params_0.w;
    m.emissive = u_emissive.xyz;
    m.emissive_energy = u_emissive.w;
    m.roughness_channel = u_pbr_channels_0.x;
    m.metallic_channel = u_pbr_channels_0.y;
    m.anisotropy = u_pbr_params_1.x;
    m.refaction = u_pbr_params_1.y;
    m.subsurface = u_pbr_params_1.z;
    m.depth_scale = u_pbr_params_1.w;
    m.rim = u_pbr_params_2.x;
    m.rim_tint = u_pbr_params_2.y;
    m.clearcoat = u_pbr_params_2.z;
    m.clearcoat_gloss = u_pbr_params_2.w;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    
    vec4 albedo = texelFetch(s_materials, ivec2(x, 3), 0);
    m.albedo = albedo.xyz;
    
    vec4 params_0 = texelFetch(s_materials, ivec2(x, 4), 0);
    m.specular = params_0.x;
    m.metallic = params_0.y;
    m.roughness = params_0.z;
    m.normal_scale = params_0.w;

    vec4 emissive = texelFetch(s_materials, ivec2(x, 5), 0);
    m.emissive = emissive.xyz;
    m.emissive_energy = emissive.w;
    
    vec4 channels = texelFetch(s_materials, ivec2(x, 6), 0);
    m.roughness_channel = channels.x;
    m.metallic_channel = channels.y;
    
    vec4 params_1 = texelFetch(s_materials, ivec2(x, 7), 0);
    m.anisotropy = params_1.x;
    m.refaction = params_1.y;
    m.subsurface = params_1.z;
    m.depth_scale = params_1.w;
    
    vec4 params_2 = texelFetch(s_materials, ivec2(x, 8), 0);
    m.rim = params_2.x;
    m.rim_tint = params_2.y;
    m.clearcoat = params_2.z;
    m.clearcoat_gloss = params_2.w;
#endif

    return m;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

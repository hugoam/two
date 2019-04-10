#ifndef MUD_GPU_MATERIAL
#define MUD_GPU_MATERIAL

#define MATERIALS_TEXTURE_WIDTH 1024
#define MATERIALS_TEXTURE_HEIGHT 23

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(MATERIALS_TEXTURE_WIDTH), float(MATERIALS_TEXTURE_HEIGHT)), _level)
#endif

#ifdef MATERIALS_BUFFER
SAMPLER2D(s_materials, 8);
#else
uniform vec4 u_material_p0;
uniform vec4 u_material_p1;
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
    m.uv0_scale = u_material_p0.xy;
    m.uv0_offset = u_material_p0.zw;
    m.uv1_scale = u_material_p1.xy;
    m.uv1_offset = u_material_p1.zw;
#else
    //int x = index % MATERIALS_TEXTURE_WIDTH;
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 uv0_scale_offset = texelFetch(s_materials, ivec2(x, y + 0), 0);
    m.uv0_scale = uv0_scale_offset.xy;
    m.uv0_offset = uv0_scale_offset.zw;
    
    vec4 uv1_scale_offset = texelFetch(s_materials, ivec2(x, y + 1), 0);
    m.uv1_scale = uv1_scale_offset.xy;
    m.uv1_offset = uv1_scale_offset.zw;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_alpha;
#endif

struct AlphaMaterial
{
    float alpha;
};

AlphaMaterial read_alpha_material(int index)
{
    AlphaMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.alpha = u_alpha.x;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 params = texelFetch(s_materials, ivec2(x, y + 2), 0);
    m.alpha = params.x;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_color;
#endif

struct SolidMaterial
{
    vec4 color;
};

SolidMaterial read_solid_material(int index)
{
    SolidMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.color = u_color;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    m.color = texelFetch(s_materials, ivec2(x, y + 3), 0);
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_point_p0;
#endif

struct PointMaterial
{
    float point_size;
    bool project;
};

PointMaterial read_point_material(int index)
{
    PointMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.point_size = u_point_p0.x;
    m.project = bool(u_point_p0.y);
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 params = texelFetch(s_materials, ivec2(x, y + 4), 0);
    m.point_size = params.x;
    m.project = bool(params.y);
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_line_p0;
uniform vec4 u_line_p1;
#endif

struct LineMaterial
{
    float line_width;
    float dash_scale;
    float dash_size;
    float dash_gap;
};

LineMaterial read_line_material(int index)
{
    LineMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.line_width = u_line_p0.x;
    m.dash_scale = u_line_p0.y;
    m.dash_size = u_line_p1.x;
    m.dash_gap = u_line_p1.y;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 params = texelFetch(s_materials, ivec2(x, y + 5), 0);
    m.line_width = params.x;
    m.dash_scale = params.y;
    m.dash_size = params.z;
    m.dash_gap = params.w;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_lit_p0;
uniform vec4 u_lit_p1;
uniform vec4 u_emissive;
#endif

struct LitMaterial
{
    float normal_scale;
    vec3 emissive;
    float energy;
    float ao;
    float ao_channel;
    float displace;
    float displace_bias;
};

LitMaterial read_lit_material(int index)
{
    LitMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.normal_scale = u_lit_p0.x;
    m.emissive = u_emissive.xyz;
    m.energy = u_emissive.w;
    m.ao = u_lit_p0.y;
    m.ao_channel = 0.0; // u_lit_p0.y; //u_pbr_channels_0.z;
    m.displace = u_lit_p1.x;
    m.displace_bias = u_lit_p1.y;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 params_0 = texelFetch(s_materials, ivec2(x, y + 6), 0);
    m.normal_scale = params_0.x;

    vec4 emissive = texelFetch(s_materials, ivec2(x, y + 7), 0);
    m.emissive = emissive.xyz;
    m.energy = emissive.w;
    
    vec4 params_1 = texelFetch(s_materials, ivec2(x, y + 8), 0);
    m.displace = params_1.x;
    m.displace_bias = params_1.y;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_albedo;
uniform vec4 u_pbr_p0;
uniform vec4 u_pbr_channels_0;
uniform vec4 u_pbr_p1;
uniform vec4 u_pbr_p2;
#endif

struct PbrMaterial
{
    vec3 albedo;
    float alpha;
    float specular;
    float metallic;
    float roughness;
    float roughness_channel;
    float metallic_channel;
    float ao_channel;
    float anisotropy;
    float refraction;
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
    m.alpha = u_albedo.w;
    m.specular = u_pbr_p0.x;
    m.metallic = u_pbr_p0.y;
    m.roughness = u_pbr_p0.z;
    m.roughness_channel = u_pbr_channels_0.x;
    m.metallic_channel = u_pbr_channels_0.y;
    //m.ao_channel = u_pbr_channels_0.z;
    m.anisotropy = u_pbr_p1.x;
    m.refraction = u_pbr_p1.y;
    m.subsurface = u_pbr_p1.z;
    m.depth_scale = u_pbr_p1.w;
    m.rim = u_pbr_p2.x;
    m.rim_tint = u_pbr_p2.y;
    m.clearcoat = u_pbr_p2.z;
    m.clearcoat_gloss = u_pbr_p2.w;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 albedo = texelFetch(s_materials, ivec2(x, y + 9), 0);
    m.albedo = albedo.xyz;
    m.alpha = albedo.w;
    
    vec4 params_0 = texelFetch(s_materials, ivec2(x, y + 10), 0);
    m.specular = params_0.x;
    m.metallic = params_0.y;
    m.roughness = params_0.z;

    vec4 channels = texelFetch(s_materials, ivec2(x, y + 11), 0);
    m.roughness_channel = channels.x;
    m.metallic_channel = channels.y;
    //m.ao_channel = channels.z;
    
    vec4 params_1 = texelFetch(s_materials, ivec2(x, y + 12), 0);
    m.anisotropy = params_1.x;
    m.refraction = params_1.y;
    m.subsurface = params_1.z;
    m.depth_scale = params_1.w;
    
    vec4 params_2 = texelFetch(s_materials, ivec2(x, y + 13), 0);
    m.rim = params_2.x;
    m.rim_tint = params_2.y;
    m.clearcoat = params_2.z;
    m.clearcoat_gloss = params_2.w;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_diffuse;
uniform vec4 u_specular;
uniform vec4 u_phong_p0;
#endif

struct PhongMaterial
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float reflectivity;
    float refraction;
};

PhongMaterial read_phong_material(int index)
{
    PhongMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.diffuse = u_diffuse.xyz;
    m.specular = u_specular.xyz;
    m.shininess = u_phong_p0.x;
    m.reflectivity = u_phong_p0.y;
    m.refraction = u_phong_p0.z;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    vec4 diffuse = texelFetch(s_materials, ivec2(x, y + 14), 0);
    m.diffuse = diffuse.xyz;
    
    vec4 specular = texelFetch(s_materials, ivec2(x, y + 15), 0);
    m.specular = specular.xyz;
    
    vec4 params_0 = texelFetch(s_materials, ivec2(x, y + 16), 0);
    m.shininess = params_0.x;
    m.reflectivity = params_0.y;
    m.refraction = params_0.z;
#endif

    return m;
}

#ifndef MATERIALS_BUFFER
uniform vec4 u_user_p0;
uniform vec4 u_user_p1;
uniform vec4 u_user_p2;
uniform vec4 u_user_p3;
uniform vec4 u_user_p4;
uniform vec4 u_user_p5;
#endif

struct UserMaterial
{
    vec4 p0;
    vec4 p1;
    vec4 p2;
    vec4 p3;
    vec4 p4;
    vec4 p5;
};

UserMaterial read_user_material(int index)
{
    UserMaterial m;
    
#ifndef MATERIALS_BUFFER
    m.p0 = u_user_p0;
    m.p1 = u_user_p1;
    m.p2 = u_user_p2;
    m.p3 = u_user_p3;
    m.p4 = u_user_p4;
    m.p5 = u_user_p5;
#else
    int x = int(mod(index, MATERIALS_TEXTURE_WIDTH));
    int y = (index / MATERIALS_TEXTURE_WIDTH) * MATERIALS_TEXTURE_HEIGHT;
    
    m.p0 = texelFetch(s_materials, ivec2(x, y + 17), 0);
    m.p1 = texelFetch(s_materials, ivec2(x, y + 18), 0);
    m.p2 = texelFetch(s_materials, ivec2(x, y + 19), 0);
    m.p3 = texelFetch(s_materials, ivec2(x, y + 20), 0);
    m.p4 = texelFetch(s_materials, ivec2(x, y + 21), 0);
    m.p5 = texelFetch(s_materials, ivec2(x, y + 22), 0);
#endif

    return m;
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif

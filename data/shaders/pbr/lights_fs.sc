$input v_texcoord0

#include <filter/filter.sh>

#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/radiance.sh>

#ifdef FOG
#include <pbr/fog.sh>
#endif

#define s_gposition s_source_0
#define s_gnormal s_source_1
#define s_galbedo s_source_2
#define s_gsurface s_source_3

float to_depth(float device_depth)
{
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	return device_depth;
#else
	return device_depth * 2.0 - 1.0;
#endif
}

vec3 clip_to_world(mat4 inv_view_proj, vec3 clip_position)
{
	vec4 wpos = mul(inv_view_proj, vec4(clip_position, 1.0) );
	return wpos.xyz / wpos.w;
}

vec3 reconstruct_position(vec2 uv, mat4 inv_view_proj, float device_depth)
{
	float depth = to_depth(device_depth);
    
	vec3 clip = vec3(uv * 2.0 - 1.0, depth);
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	clip.y = -clip.y;
#endif
	return clip_to_world(inv_view_proj, clip);
}

void main()
{
    // @todo we can get rid of one buffer by reconstructing position from depth
	//float device_depth = texture2D(s_depth, v_texcoord0).x
	//vec3 position = reconstruct_position(v_texcoord0.xy, u_view_proj, device_depth);
    
    Fragment fragment;
    fragment.coord = gl_FragCoord;
    vec4 position = texture2DLod(s_gposition, v_texcoord0.xy, 0.0);
	fragment.position = position.xyz;
    fragment.coord.z = position.w;
	fragment.normal = texture2DLod(s_gnormal, v_texcoord0.xy, 0.0).rgb;
	fragment.view = normalize(-fragment.position);
    fragment.depth = -fragment.position.z;

    Material material;
    vec4 surface = texture2DLod(s_gsurface, v_texcoord0.xy, 0.0).rgba;
	vec4 colour = texture2DLod(s_galbedo, v_texcoord0.xy, 0.0).rgba;
    material.albedo = colour.rgb;
    material.roughness = surface.x;
	material.metallic = surface.y;
    material.specular = surface.z;
	material.alpha = 1.0;

    // metallic energy conservation
	vec3 dielectric = vec3_splat(0.034) * material.specular * 2.0;
	material.f0 = mix(dielectric, material.albedo, material.metallic);
    material.albedo = mix(material.albedo, vec3_splat(0.0), material.metallic);
   
	fragment.NoV = saturate(dot(fragment.normal, fragment.view));
    
    // Radiance radiance;
	vec3 specular = vec3_splat(0.0);
	vec3 diffuse = vec3_splat(0.0);
	vec3 ambient = vec3_splat(0.0);
    vec3 emission = colour.rgb * colour.a;

#ifdef RADIANCE_ENVMAP
    ambient += radiance_ambient(fragment.normal);
    specular += radiance_reflection(fragment.view, fragment.normal, material.roughness);
#else
	ambient += u_radiance_color * u_ambient;
#endif
	ambient *= material.albedo;
    
#ifdef AMBIENT_OCCLUSION
	ambient *= material.ao;
#endif

#ifdef DIRECT_LIGHT
	direct_light(fragment, material, fragment.depth, diffuse, specular);
#endif

    //apply_reflections(specular, ambient);
    
#ifdef CLUSTERED
    apply_cluster_lights(fragment, material, diffuse, specular);
#else
	apply_lights(fragment, material, diffuse, specular);
#endif
    
#ifdef DIFFUSE_TOON
	specular *= material.specular * material.metallic * material.albedo * 2.0;
#else
    specular *= brdf_specular_term(fragment, material);
#endif

#ifdef FOG
    //apply_fog(fragment, emission, ambient, diffuse, specular);
    apply_fog_0(fragment, emission);
#endif

#ifdef MRT
	gl_FragData[0] = vec4(emission + diffuse + ambient, surface.a);
	gl_FragData[1] = vec4(specular, material.metallic);
	gl_FragData[2] = vec4(normalize(fragment.normal) * 0.5 + 0.5, material.roughness);
#ifdef SUBSURFACE
	gl_FragData[3] = subsurface;
#endif

#else
	gl_FragColor = vec4(emission + ambient + diffuse + specular, surface.a);
	//gl_FragColor = vec4(normalize(fragment.normal) * 0.5 + 0.5, 1.0);
	//gl_FragColor = vec4(v_color.rgb, 1.0);
#endif

}
